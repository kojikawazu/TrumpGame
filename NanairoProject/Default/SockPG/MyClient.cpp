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

	// �T�[�o�p�ް�����
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if( server_socket == INVALID_SOCKET ){
		WSACleanup();
		return WINSOCK_ERROR;
	}

	// Host�A�h���X����
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

	// ���Ɏg�p���̃\�P�b�g���ƃG���[���o��̂ł���̖h�~
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

	// �V���ȃN���C�A���g�̒ʒm
	data.byte_sign = NEW_ACCEPT;
	SendOne( &server_socket, &data );

	do{
		// �ʒm�ɑ΂���ԓ�(�������Ă��Ȃ���while)
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

	// ID���擾����
	client_id = data.id;

	return WINSOCK_SUCCESS;
}
int MyClient::SearchServer()
{
	BOOL yes = TRUE;
	int recv_result = 0;
	int timeout_frameCnt = 0, timeout_frame = 100;
	char buff[ 200 ] = {};

	// UDP �u���[�h�L���X�g
	SOCKET broadsock = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons( SERVER_SEARCH_PORT );
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");

	// �u���[�h�L���X�g TRUE
	setsockopt(broadsock, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));

	// UDP ��M
	SOCKET udprecvsock = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in udpRecvAddr = {};
	udpRecvAddr.sin_family = AF_INET;
	udpRecvAddr.sin_port = htons( SERVER_RESPONSE_PORT );
	udpRecvAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	// ���Ɏg�p���̃\�P�b�g���ƃG���[���o��̂ł���̖h�~
	setsockopt(udprecvsock, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

	// �o�C���h
	if( bind(udprecvsock, (sockaddr*)&udpRecvAddr, sizeof(udpRecvAddr)) == SOCKET_ERROR ){
		SocketCloser( &udprecvsock );
		SocketCloser( &broadsock );
		return WINSOCK_ERROR;
	}

	// toMyServer�𑗂�
	sendto(broadsock, "toMyServer", strlen("toMyServer")+1, 0, (struct sockaddr *)&addr, sizeof(addr));
	do{
		// toMyServer�𑗂��"res,IP�A�h���X"���Ԃ����
		recv_result = Recv_select( &udprecvsock, buff, sizeof(buff) );
		if( recv_result == WINSOCK_LOGOUT ){
			SocketCloser( &udprecvsock );
			SocketCloser( &broadsock );
			return WINSOCK_ERROR;
		}
		// �������ĂĂ�...
		if( recv_result == WINSOCK_SUCCESS ){
			if( CheckIPListMemb( strchr(buff, ',')+1 ) ){
			// ����͂�������񂾂�
				recv_result = WINSOCK_ERROR;
				continue;
			}else{
			// �R�s�[���Ƃ�
				char* cpbuff = new char[ strlen(buff) + 1 - 4 ];
				strcpy_s( cpbuff, sizeof(char)*(strlen(buff)-3), (strchr(buff, ',')+1) );
				serverIPList.push_front( cpbuff );// �R�s�[�����X�g�ɕۑ�����
			}
		}
	}while( /*recv_result != WINSOCK_SUCCESS &&*/ timeout_frame >= (timeout_frameCnt++) );

	// �^�C���A�E�g���Ă�
	if( timeout_frame <= timeout_frameCnt ){
		SocketCloser( &udprecvsock );
		SocketCloser( &broadsock );
		return WINSOCK_UNRECIEVE;
	}

	// �T�[�oIP���Z�b�g����
	setServerIP( (strchr(buff, ',')+1) );

	// ����I���������
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
	// ��x�������
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