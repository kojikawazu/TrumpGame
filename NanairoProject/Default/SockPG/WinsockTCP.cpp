#pragma once
#include "WinsockTCP.h"

#pragma comment(lib, "ws2_32.lib")

namespace sockNW{
// srcbuff + offsetから始まるサイズを指定して受け取る。
// 元データには影響しない。
char* getDataFromBuff( char* dstbuff, int dstbuff_size, char* srcbuff, int srcbuff_size, int offset ){
	if( dstbuff == NULL || srcbuff == NULL )
		return NULL;

	memcpy_s( dstbuff, dstbuff_size, srcbuff + offset, srcbuff_size );
	return dstbuff;
}
char* addDataToBuff(char* dstbuff, int dstbuff_size, char* srcbuff, int srcbuff_size){
	memcpy_s( dstbuff, dstbuff_size, srcbuff, srcbuff_size );
	return dstbuff + srcbuff_size; // buffの最後を返す
}
int Recv_select(SOCKET* sock, char* buff, int size)
{
	fd_set  fds;
	TIMEVAL t; t.tv_sec = 0; t.tv_usec = 0;
	std::vector<char> local; local.resize(size);
	memset( &(local[0]), 0, sizeof(char)*size );

	FD_ZERO( &fds );
	FD_SET( *sock, &fds );

	// data届いてる？
	select( 1, &fds, NULL, NULL, &t );
	if( !FD_ISSET( *sock, &fds ) ){
		local.clear();
		return WINSOCK_UNRECIEVE;
	}

	// 受け取り
	int nRcv = recv( *sock, &(local[0]), size, 0 );
	if( nRcv == SOCKET_ERROR ){
		SocketCloser( sock );
		local.clear();
		return WINSOCK_LOGOUT;
	}

	// 正常であればコピー
	memcpy_s( buff, size, &(local[0]), size);
	local.clear();
	return WINSOCK_SUCCESS;
}
int SocketCloser(SOCKET* sock)
{
	if( (*sock) != INVALID_SOCKET ){
		closesocket( *sock );
		(*sock) = INVALID_SOCKET;
	}
	return 0;
}


DataStruct::DataStruct()
{
	id = 0;
	byte_sign = DATA_NONE;
	size = 0;
	data.clear();
}
DataStruct* DataStruct::init()
{
	id = 0;
	byte_sign = DATA_NONE;
	size = 0;
	data.clear();
	return this;
}
char* DataStruct::getData()
{
	if( data.empty() )
		return NULL;

	return &(data[0]);
}
DataStruct* DataStruct::set(char* buff, unsigned int size)
{
	if( buff == NULL ){
		this->size = 0;
		this->data.clear();
	}else{
		this->size = size;
		this->data.resize(size);
		memcpy_s( &(data[0]), size, buff, size );
	}
	return this;
}
DataStruct* DataStruct::append(char* buff, unsigned int size)
{
	if( buff == NULL ){
		return this;
	}
	this->data.resize( this->size + size );
	memcpy_s( &(data[this->size]), size, buff, size );

	this->size += size;
	return this;
}
DataStruct* DataStruct::copy(DataStruct* dist)
{
	if( dist == NULL )
		return NULL;

	dist->id = id;
	dist->byte_sign = byte_sign;
	dist->set( &(data[0]), size );
	return this;
}
unsigned int DataStruct::headerSize()
{
	return sizeof(DATA_HEADER);
}
unsigned int DataStruct::dataSize()
{
	return data.size();
}
unsigned int DataStruct::totalSize()
{
	return sizeof(DATA_HEADER) + data.size();
}


///-------------------------------------------///
///-------------------------------------------///
//------------WinSockStarter-------------------//
///-------------------------------------------///
///-------------------------------------------///
WinSockStarter::WinSockStarter()
{
	hostname.str("");
	uport   = 0;
	err_flg = false;
}
int WinSockStarter::_beginWSA()
{
	if( WSAStartup(MAKEWORD(2, 0), &wsaData) ){
		WSACleanup();
		return WINSOCK_ERROR;
	}
	char name[NI_MAXHOST + 1] = {};
	if( gethostname(name, sizeof(name)) ){
		name[0] = '\0'; // ホスト名を取得できなかったら
	}
	hostname << name << '\0';
	return WINSOCK_SUCCESS;
}
void WinSockStarter::_happenError()
{
	err_flg = true;
}
void WinSockStarter::_setPort(u_short port)
{
	uport = port;
}
std::string WinSockStarter::getHostName()
{
	return hostname.str();
}
bool WinSockStarter::IsError()
{
	return err_flg;
}
int WinSockStarter::RecvOne(SOCKET* sock, DataStruct* buff)
{
	if( err_flg || (*sock) == INVALID_SOCKET )
		return WINSOCK_ERROR;

	char* local = NULL;
	TIMEVAL t = {};
	FD_ZERO( &readfds );
	FD_SET( *sock, &readfds );

	// data届いてる？
	select( 1, &readfds, NULL, NULL, &t );
	if( !FD_ISSET( *sock, &readfds ) ){
		return WINSOCK_UNRECIEVE;
	}

	DATA_HEADER dataHead;
	// 受け取り( HeaderとDataに分けて行う
	int nRcv = recv( *sock, (char*)&dataHead, sizeof(DATA_HEADER), 0 );
	if( nRcv == SOCKET_ERROR ){
		SocketCloser( sock );
		return WINSOCK_LOGOUT;
	}
	// dataはバッファが0じゃ無いときな
	if( dataHead.size && (DATA_NONE <= dataHead.byte_sign && dataHead.byte_sign < DATA_FLAGS_MAX) ){
		local = new char[ dataHead.size ];
		nRcv = recv( *sock, local, dataHead.size, 0 );
		if( nRcv == SOCKET_ERROR ){
			SocketCloser( sock );
			delete[] local;
			return WINSOCK_LOGOUT;
		}
		// 正常であればコピー
		buff->set( local, dataHead.size );
		delete[] local;
	}
	// 正常であればコピー
	buff->header = dataHead;
	return WINSOCK_SUCCESS;
}
int WinSockStarter::SendOne(SOCKET* sock, DataStruct* buff)
{
	if( err_flg || (*sock) == INVALID_SOCKET )
		return WINSOCK_ERROR;

	std::vector<char> charbuff;
	charbuff.resize( buff->totalSize() );

	// 値コピー( dataはバッファが0じゃ無いときな
	memcpy_s( &(charbuff[0]), charbuff.size(), &(buff->header), sizeof( DATA_HEADER ) );
	if( buff->size ){
		memcpy_s( &(charbuff[ sizeof(DATA_HEADER) ]), charbuff.size() - sizeof(DATA_HEADER), &(buff->data[0]), buff->size );
	}

	// 送信は一括で
	if( send(*sock, &(charbuff[0]), charbuff.size(), 0) == SOCKET_ERROR ){
		SocketCloser( sock );
		return WINSOCK_LOGOUT;
	}
	return WINSOCK_SUCCESS;
}




//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
/*

MyClient2::MyClient2()
{
	server_socket = &(recv_socket[0]);
}
MyClient2::~MyClient2()
{
	Dispose();
}
int MyClient2::_setupConnect(unsigned int port)
{
	uport = port;

	// サーバ用ﾃﾞｰﾀ生成
	*server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if( *server_socket == INVALID_SOCKET ){
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
		SocketCloser( server_socket );
		WSACleanup();
		return WINSOCK_ERROR;
	}

	// connect
//	SOCKADDR_IN connect_saddr = {};
//	connect_saddr.sin_family = lpHost->h_addrtype;
//	connect_saddr.sin_port = htons(port);
//	connect_saddr.sin_addr.s_addr = *((u_long*)lpHost->h_addr);
	from_addr[0].sin_family = lpHost->h_addrtype;
	from_addr[0].sin_port = htons(port);
	from_addr[0].sin_addr.s_addr = *((u_long*)lpHost->h_addr);
	
	// 既に使用中のソケットだとエラーが出るのでそれの防止
	BOOL yes = TRUE;
	setsockopt(*server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

//	if( connect(server_socket, (sockaddr*)&connect_saddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
	if( connect(*server_socket, (sockaddr*)&(from_addr[0]), sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
		SocketCloser( server_socket );
		WSACleanup();
		return WINSOCK_ERROR;
	}
	return WINSOCK_SUCCESS;
}
int MyClient2::ConnectToAddressList()
{
	if( err_flg )
		return WINSOCK_ERROR;

//	CreateThread( NULL, 0, MyClient2::ConnectThread, (void*)this, 0, NULL );
//	return WINSOCK_SUCCESS;

	DATA_STRUCT** pdata = &(recv_data[0]);
	SOCKADDR_IN* pfrom = &(from_addr[0]);

	// 0 はサバなのでそもそもアクセスしない
	for( unsigned int i=1; i < accept_cnt ; i++ ){
		// 自分自身には接続しない
		// アドレス == 0 なら接続無理
		if( client_id == i || (pfrom[i].sin_addr.s_addr == 0) )
			continue;

		// ソケット生成
		recv_socket[i] = socket(AF_INET, SOCK_STREAM, 0);
		if( recv_socket[i] == INVALID_SOCKET ){
			continue;
		}
		// 既に使用中のソケットだとエラーが出るのでそれの防止
		BOOL yes = TRUE;
		setsockopt(recv_socket[i], SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

		// コネクト
		if( connect(recv_socket[i], (sockaddr*)&from_addr[i], sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
//			printf("error : %d\n", WSAGetLastError());
			SocketCloser( &recv_socket[i] );
			continue;
		}
		// コネクト成功 => データ生成
		_createRecieveData( i );
//		printf("%d に接続\n", i);
	}
	return WINSOCK_SUCCESS;
}
int MyClient2::ConnectServer(unsigned int port)
{
	if( err_flg )
		return WINSOCK_ERROR;

	if( _setupConnect(port) < 0 ){
		_happenError();
		return WINSOCK_ERROR;
	}
	return WINSOCK_SUCCESS;
}
int MyClient2::NotifyNewAccept()
{
	if( err_flg )
		return WINSOCK_ERROR;

	DATA_STRUCT data = {};
	char buff[64] = {};
	int bufflen = sizeof(char)*64;
	int offset = 0;
	int itransbuff = 0; // 変換用buff

	do{
		// 新たなクライアントの通知
		data.byte_sign = NEW_ACCEPT;
		SendOne( server_socket, &data );

		// 通知に対する返答(何も来ていない間while)
		data.byte_sign = DATA_NONE;
		if( RecvOne( server_socket, &data) == WINSOCK_LOGOUT ){
			_happenError();
			break;
		}
	}while( data.byte_sign != NEW_ACCEPT );

	if( err_flg ){
		return WINSOCK_ERROR;
	}

	// recv_servser.dataには 最大値,現在の参加者数,id番号 がcsvで入っている
	// accept count max
	getDataFromBuff( buff, bufflen, data.data, sizeof(int), offset);
	memcpy_s( &itransbuff, sizeof(int), buff, sizeof(int) );
	setAcceptcntMax( itransbuff );
	// accept count
	offset += sizeof(int);
	getDataFromBuff( buff, bufflen, data.data, sizeof(int), offset);
	memcpy_s( &itransbuff, sizeof(int), buff, sizeof(int) );
	accept_cnt = itransbuff;
	// ID
	offset += sizeof(int);
	getDataFromBuff( buff, bufflen, data.data, sizeof(int), offset);
	memcpy_s( &itransbuff, sizeof(int), buff, sizeof(int) );
	client_id = itransbuff;

	return WINSOCK_SUCCESS;
}
int MyClient2::Initialize()
{
	// 一度資源解放
	Dispose();

	if( _beginWSA() < 0 ){
		_happenError();
		return WINSOCK_ERROR;
	}
	return WINSOCK_SUCCESS;
}
int MyClient2::RecieveConnectedAddress()
{
	if( err_flg )
		return WINSOCK_ERROR;

	DATA_STRUCT data = {};
	char buff[64] = {};
	int bufflen = sizeof(char)*64;
	int offset = 0;
	int result = 0;
	int addr_size = 0;
	int addr_loop_start = 0;
	int addr_loop_end = 0;

	// "s + アドレスの数 + ... + e"
	// ADDRESS_DATA_ENDが来るまでは連投してきてると思って受け取って
	while( data.byte_sign != ADDRESS_DATA_END ){
		// 新たなクライアントの通知
		data.byte_sign = ADDRESS_DATA;
		SendOne( server_socket, &data );

		// 通知に対する返答(何も来ていない間while)
		result = RecvOne( server_socket, &data );
		// サーバとの回線が切れてる
		if( result == WINSOCK_LOGOUT ) {
			_happenError(); // 落ちるしかない
			break;
		}
		// なんも来てなかったらcontinue
		if( result == WINSOCK_UNRECIEVE ||
			(data.byte_sign != ADDRESS_DATA &&
			 data.byte_sign != ADDRESS_DATA_END ) ) {
			continue;
		}
		// 終わってたらbreak
		if( data.byte_sign == ADDRESS_DATA_END ) {
//			printf( "ADDRESS_DATA_END\n" );
			break;
		}

		// server確立!
		// start の s
		offset = 0;
		getDataFromBuff( buff, bufflen, data.data, sizeof(char), offset );
		if( buff[0] != 's' ){
			_happenError(); // 落ちるしかない
			break;
		}
		// 送られてきたアドレスの数
		offset += sizeof(char);
		getDataFromBuff( buff, bufflen, data.data, sizeof(char), offset );
		memcpy_s( &addr_size, sizeof(int), buff, sizeof(int) );
		addr_loop_start = addr_loop_end;
		addr_loop_end += addr_size;
		// 送られてきた合計が許容量超えとる
		if( (UINT)addr_loop_end > accept_cnt_max ){
			_happenError(); // 落ちるしかない
			break;
		}
		// end の e
		// ここがもんだいだわwww
		// csvとか使っちゃだめねwww
		offset += sizeof(SOCKADDR_IN) * addr_size + sizeof(char);
		getDataFromBuff( buff, bufflen, data.data, sizeof(char), offset );
		if( buff[0] != 'e' ){
			_happenError(); // 落ちるしかない
			break;
		}

		// sとeが確認できたら通信は成功！
//		printf("address ok - ");
		// setするよ!
		SOCKADDR_IN tmp = {};
		offset = sizeof(char)*2;
		for( int i=addr_loop_start ; i<addr_loop_end ; i++ ){
			getDataFromBuff( (char*)&tmp, sizeof(SOCKADDR_IN), data.data, sizeof(SOCKADDR_IN), offset );
			offset += sizeof(SOCKADDR_IN);
			// port をclientが解放しているものに変更してset
			tmp.sin_port = htons( CLIENT_LISTEN_PORT );
			memcpy_s( &from_addr[i], sizeof(SOCKADDR_IN), &tmp, sizeof(SOCKADDR_IN) );
			//setFromAddress( i, &tmp );
		}
//		printf("for end\n");
	}

	// 終了の合図
	InitDATA_STRUCT( &data );
	data.byte_sign = ADDRESS_DATA_END;
	SendOne( server_socket, &data );

	if( err_flg ){
		return WINSOCK_ERROR;
	}
	return WINSOCK_SUCCESS;
}
int MyClient2::getIDNumber() const
{
	return client_id;
}
void MyClient2::setIDNumber(int id)
{
	client_id = id;
}
void MyClient2::setServerIP(char* str_ip)
{
	strcpy_s(buffServerIp, IP_ADDERSS_BUFFSIZE, str_ip );
}
void MyClient2::setServerIP(UINT v1, UINT v2, UINT v3, UINT v4)
{
	sprintf_s(buffServerIp, IP_ADDERSS_BUFFSIZE, "%d.%d.%d.%d", v1, v2, v3, v4 );
}
int MyClient2::Dispose()
{
	EndAccept();

	for(unsigned int i=0 ; i<accept_cnt_max ; i++){
		_deleteRecieveData( i );
	}
	if( accept_mutex != NULL ){
		CloseHandle( accept_mutex );
		accept_mutex = NULL;
	}
	client_id = -1;
	SocketCloser( server_socket );
	ZeroMemory(buffServerIp, IP_ADDERSS_BUFFSIZE);

	accept_cnt = 0;
	accept_cnt_max = 0;
	from_addr.clear();
	recv_data.clear();
	recv_socket.clear();

	WSACleanup();
	return 0;
}
//*/

};
