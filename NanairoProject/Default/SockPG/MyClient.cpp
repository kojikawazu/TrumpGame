#pragma once
#include "WinsockTCP.h"

///-------------------------------------------///
///-------------------------------------------///
//--------------TCP-Client---------------------//
///-------------------------------------------///
///-------------------------------------------///

namespace sockNW{



MyClient::MyClient()
{
	client_id = 0;
	memset( buffServerIp, 0, sizeof(buffServerIp) );
	server_socket = INVALID_SOCKET;
	server_data = NULL;
}
MyClient::~MyClient()
{
	Dispose();
}
int MyClient::_setupConnect(unsigned int port)
{
	uport = port;

	// サーバ用ﾃﾞｰﾀ生成
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if( server_socket == INVALID_SOCKET ){
		WSACleanup();
		return WINSOCK_ERROR;
	}

	// Hostアドレス生成
	HOSTENT* lpHost = gethostbyname(buffServerIp);
	if( lpHost == NULL ){
		unsigned int addr = inet_addr(buffServerIp);
		lpHost = gethostbyaddr((char*)&addr, 4, AF_INET);
	}
	if( lpHost == NULL ){
		SocketCloser( &server_socket );
		WSACleanup();
		return WINSOCK_ERROR;
	}

	// connect
	SOCKADDR_IN connect_saddr = {};
	connect_saddr.sin_family = lpHost->h_addrtype;
	connect_saddr.sin_port = htons(port);
	connect_saddr.sin_addr.s_addr = *((u_long*)lpHost->h_addr);

	// 既に使用中のソケットだとエラーが出るのでそれの防止
	BOOL yes = TRUE;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

	if( connect(server_socket, (sockaddr*)&connect_saddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
		SocketCloser( &server_socket );
		WSACleanup();
		return WINSOCK_ERROR;
	}
	return WINSOCK_SUCCESS;
}
bool MyClient::CheckIPListMemb(char* ip_addr)
{
	if( err_flg || serverIPList.empty() )
		return false;

	bool found = false;
	std::list<char*>::iterator ite = serverIPList.begin();
	std::list<char*>::iterator end = serverIPList.end();

	for( ite ; ite != end ; ite++ ){
		if(strcmp( *ite, ip_addr ) == 0){
			found = true;
			break;
		}
	}
	return found;
}
int MyClient::ConnectServer(unsigned int port)
{
	if( err_flg )
		return WINSOCK_ERROR;

	if( _setupConnect(port) < 0 ){
		_happenError();
		return WINSOCK_ERROR;
	}
	if( server_data == NULL ){
		server_data = new DataStruct();
	}
	return WINSOCK_SUCCESS;
}
void MyClient::DeleteIPList()
{
	if( serverIPList.empty() )
		return;

	std::list<char*>::iterator ite = serverIPList.begin();
	std::list<char*>::iterator end = serverIPList.end();

	for( ite ; ite != end ; ite++ ){
		if( *ite ){
			delete[] (*ite);
			(*ite) = NULL;
		}
	}
}
void MyClient::UnConnectServer()
{
	if( server_data ){
		delete server_data;
		server_data = NULL;
		SocketCloser( &server_socket );
	}
}
int MyClient::NotifyNewAccept()
{
	if( err_flg )
		return WINSOCK_ERROR;

	DataStruct data;
	char buff[64] = {};
	int timeout_frameCnt = 0, timeout_frame = 100;

	// 新たなクライアントの通知
	data.byte_sign = NEW_ACCEPT;
	SendOne( &server_socket, &data );

	do{
		// 通知に対する返答(何も来ていない間while)
		data.byte_sign = DATA_NONE;
		if( RecvOne( &server_socket, &data) == WINSOCK_LOGOUT ){
			_happenError(); break;
		}
	}while( data.byte_sign != NEW_ACCEPT && timeout_frame >= (timeout_frameCnt++)  );

	// AnyEvent Happened
	if( err_flg ){
		return WINSOCK_ERROR; // Error
	}else if( timeout_frame <= timeout_frameCnt ){
		return WINSOCK_UNRECIEVE; // Timeout
	}

	// IDを取得する
	client_id = data.id;

	return WINSOCK_SUCCESS;
}
int MyClient::SearchServer()
{
	BOOL yes = TRUE;
	int recv_result = 0;
	int timeout_frameCnt = 0, timeout_frame = 100;
	char buff[ 200 ] = {};

	// UDP ブロードキャスト
	SOCKET broadsock = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons( SERVER_SEARCH_PORT );
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");

	// ブロードキャスト TRUE
	setsockopt(broadsock, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));

	// UDP 受信
	SOCKET udprecvsock = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in udpRecvAddr = {};
	udpRecvAddr.sin_family = AF_INET;
	udpRecvAddr.sin_port = htons( SERVER_RESPONSE_PORT );
	udpRecvAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	// 既に使用中のソケットだとエラーが出るのでそれの防止
	setsockopt(udprecvsock, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

	// バインド
	if( bind(udprecvsock, (sockaddr*)&udpRecvAddr, sizeof(udpRecvAddr)) == SOCKET_ERROR ){
		SocketCloser( &udprecvsock );
		SocketCloser( &broadsock );
		return WINSOCK_ERROR;
	}

	// toMyServerを送る
	sendto(broadsock, "toMyServer", strlen("toMyServer")+1, 0, (struct sockaddr *)&addr, sizeof(addr));
	do{
		// toMyServerを送ると"res,IPアドレス"が返される
		recv_result = Recv_select( &udprecvsock, buff, sizeof(buff) );
		if( recv_result == WINSOCK_LOGOUT ){
			SocketCloser( &udprecvsock );
			SocketCloser( &broadsock );
			return WINSOCK_ERROR;
		}
		// 成功してても...
		if( recv_result == WINSOCK_SUCCESS ){
			if( CheckIPListMemb( strchr(buff, ',')+1 ) ){
			// それはもうあるんだよ
				recv_result = WINSOCK_ERROR;
				continue;
			}else{
			// コピーをとる
				char* cpbuff = new char[ strlen(buff) + 1 - 4 ];
				strcpy_s( cpbuff, sizeof(char)*(strlen(buff)-3), (strchr(buff, ',')+1) );
				serverIPList.push_front( cpbuff );// コピーをリストに保存する
			}
		}
	}while( /*recv_result != WINSOCK_SUCCESS &&*/ timeout_frame >= (timeout_frameCnt++) );

	// タイムアウトしてる
	if( timeout_frame <= timeout_frameCnt ){
		SocketCloser( &udprecvsock );
		SocketCloser( &broadsock );
		return WINSOCK_UNRECIEVE;
	}

	// サーバIPをセットする
	setServerIP( (strchr(buff, ',')+1) );

	// 送り終わったら解放
	SocketCloser( &udprecvsock );
	SocketCloser( &broadsock );
	return WINSOCK_SUCCESS;
}
bool MyClient::IsConnected()
{
	return (server_socket != INVALID_SOCKET);
}
int MyClient::Initialize()
{
	// 一度資源解放
	Dispose();

	if( _beginWSA() < 0 ){
		_happenError();
		return WINSOCK_ERROR;
	}
	return WINSOCK_SUCCESS;
}
	
int MyClient::getIDNumber() const
{
	return client_id;
}
const unsigned int MyClient::getIPListSize()
{
	return serverIPList.size();
}
const char* MyClient::getIPListMemb(int index)
{
	if( serverIPList.empty() )
		return NULL;

	index = ( index <= (int)(serverIPList.size()-1) ) ? index : serverIPList.size()-1 ;

	char* cp = NULL;
	int cnt = 0;
	std::list<char*>::iterator ite = serverIPList.begin();
	std::list<char*>::iterator end = serverIPList.end();

	for( ite ; ite != end ; ite++, cnt++ ){
		if( cnt == index ){
			cp = (*ite);
			break;
		}
	}
	return cp;
}
void MyClient::setIDNumber(int id)
{
	client_id = id;
}
void MyClient::setServerIP(char* str_ip)
{
	strcpy_s(buffServerIp, IP_ADDERSS_BUFFSIZE, str_ip );
}
void MyClient::setServerIP(UINT v1, UINT v2, UINT v3, UINT v4)
{
	sprintf_s(buffServerIp, IP_ADDERSS_BUFFSIZE, "%d.%d.%d.%d", v1, v2, v3, v4 );
}

int MyClient::Dispose()
{
	client_id = 0;
	memset( buffServerIp, 0, sizeof(char)*IP_ADDERSS_LENGTH );
	UnConnectServer();
	DeleteIPList();
	WSACleanup();
	return 0;
}



};