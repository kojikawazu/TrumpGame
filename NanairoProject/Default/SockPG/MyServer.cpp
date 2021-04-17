#pragma once
#include "WinsockTCP.h"

///-------------------------------------------///
///-------------------------------------------///
//--------------TCP-Server---------------------//
///-------------------------------------------///
///-------------------------------------------///

namespace sockNW{



MyServer::MyServer()
{
	uport = 0;
	accept_cnt = 0;
	accept_cnt_max = 0;
	accept_mutex = NULL;
	state = NOT_USED;
	listen_socket = INVALID_SOCKET;
	listen_stop_flg = false;
}
MyServer::~MyServer()
{
	Dispose();
}
int MyServer::_createRecieveData( int idx )
{
	_deleteRecieveData( idx );
	recv_data[idx] = new DataStruct();
	accept_cnt++;
	return 0;
}
int MyServer::_deleteRecieveData( int idx )
{
	// data������Ƃ�����socket���N���[�Y����
	// �������Ȃ��ƕs����N����
	if( recv_data[idx] != NULL ){
		delete recv_data[idx];
		recv_data[idx] = NULL;
		SocketCloser( &recv_socket[idx] );
		ZeroMemory( &(from_addr[ idx ]), sizeof(SOCKADDR_IN) );
		accept_cnt--;
	}
	return 0;
}
int MyServer::TrimDataList()
{
	if( recv_data.empty() )
		return 0;

	int ret = 0;
	// data��null�̎��A�l�߂�
	unsigned int next;
	for( unsigned int i=1 ; i < accept_cnt_max-1 ; i++){
		if( recv_data[i] == NULL ){
			// index [i] ����I�_�܂łɃf�[�^�͑��݂��邩
			for( next=i ; next < accept_cnt_max ; next++){
				if( recv_data[next] != NULL ){
					break; // ���݂�����break;
				}
			}
			if( next == accept_cnt_max )
				break; // ���݂��Ă��Ȃ��ꍇ�I������

			// next�ɂ�����̂�i�Ɉړ�
			from_addr[i] = from_addr[ next ];
			recv_data[i] = recv_data[ next ];
			recv_socket[i] = recv_socket[ next ];

			// next�ɂ�����̂�����
			ZeroMemory( &from_addr[ next ], sizeof(SOCKADDR_IN) );
			recv_data[ next ] = NULL;
			recv_socket[ next ] = INVALID_SOCKET;

			ret = 1;
		}
	}
	return ret;
}
int MyServer::_setupListen(unsigned int port)
{
	uport = port;
	
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_socket == INVALID_SOCKET){
		WSACleanup();
		return WINSOCK_ERROR;
	}

	SOCKADDR_IN bind_saddr = {};
	bind_saddr.sin_family = AF_INET;
	bind_saddr.sin_port   = htons(port);
	bind_saddr.sin_addr.s_addr = INADDR_ANY;

	// ���Ɏg�p���̃\�P�b�g���ƃG���[���o��̂ł���̖h�~
	BOOL yes = TRUE;
	setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

	// �o�C���h
	if( bind(listen_socket, (sockaddr*)&bind_saddr, sizeof(bind_saddr)) == SOCKET_ERROR ){
		SocketCloser( &listen_socket );
		WSACleanup();
		return WINSOCK_ERROR;
	}

	if( listen(listen_socket, 0) == SOCKET_ERROR ){
		SocketCloser( &listen_socket );
		WSACleanup();
		return WINSOCK_ERROR;
	}
	return WINSOCK_SUCCESS;
}
int MyServer::AllRecieve()
{
	if( err_flg )
		return WINSOCK_ERROR;

	int result = 0;
	bool anyLogout = false;
	for( unsigned int i=1 ; i < accept_cnt_max ; i++ ){
		if( recv_data[i] == NULL )
			continue;

		WaitForSingleObject( accept_mutex, INFINITE );
		result = RecvOne( &recv_socket[i], recv_data[i] );
		ReleaseMutex( accept_mutex );
		if( result == WINSOCK_LOGOUT ){
			// �����o�̒E��
			_deleteRecieveData( i );
			anyLogout = true;
		}
	}
//	if( anyLogout )
//		TrimDataList(); // �߂Ƃ���

	return WINSOCK_SUCCESS;
}
int MyServer::AllSend(DataStruct* buff)
{
	if( err_flg )
		return WINSOCK_ERROR;

	for(unsigned int i=1 ; i < accept_cnt_max ; i++){
		if( recv_data[i] == NULL )
			continue;

		if( SendOne( &recv_socket[i], buff ) < 0 ){
			_deleteRecieveData( i ); // ���݂��Ȃ����� == �폜
		}
	}
	return 0;
}
int MyServer::BeginAccept(unsigned int port)
{
	if( err_flg )
		return WINSOCK_ERROR;

	if( state == WAIT_ACCEPT )
		return 0; // ���d�N���h�~

	if( _setupListen(port) < 0 ){
		_happenError();
		return WINSOCK_ERROR;
	}

	state = WAIT_ACCEPT;
	CreateThread( NULL, 0, MyServer::AcceptThread, (void*)this, 0, NULL );
	return WINSOCK_SUCCESS;
}
int MyServer::EndAccept()
{
	if( err_flg )
		return WINSOCK_ERROR;

	if( state != WAIT_ACCEPT )
		return WINSOCK_SUCCESS; // ��쓮�h�~

	listen_stop_flg  = true;
	int checkTimeOut = 0;
	while( listen_stop_flg ){
		Sleep(10); // Thread�I���҂�
		if(checkTimeOut++ >= 100){
			break;
		}
	}
	SocketCloser( &listen_socket );
	state = NOT_USED;
	return accept_cnt;
}
int MyServer::Initialize()
{
	// ��x�������
	Dispose();

	listen_stop_flg = false;
	if( _beginWSA() < 0 ){
		_happenError();
		return WINSOCK_ERROR;
	}
	accept_mutex = CreateMutex( NULL, FALSE, NULL );
	return WINSOCK_SUCCESS;
}
int MyServer::SendAddrList(int client_idx)
{
	DataStruct transData; // �ʐM�pdata
	UCHAR sockaddr_size = 30; // �ő�30���炢�ł�����
	char* cp = NULL;
	char sockaddr_cnt = 0;   // ���ۂɑ���A�h���X�̐�
	int sendaddress_cnt = 0; // ���ɑ���ꂽ�A�h���X�̐�

	while( this->accept_cnt_max != sendaddress_cnt ){
		// �ő�l�𒴂��Ȃ��悤�ɃZ�[�u����
		// �����ő�� or (list�̐� - ���łɑ�������) <-�܂�]��̐�
		sockaddr_cnt = min(sockaddr_size, accept_cnt_max - sendaddress_cnt);

		transData.byte_sign = ADDRESS_DATA;
		transData.set( "s", 1 );
		transData.append( (&sockaddr_cnt), sizeof(sockaddr_cnt) );
		for( int i=0 ; i < sockaddr_cnt ; i++ ){
			transData.append( (char*)(&(from_addr[i + sendaddress_cnt])), sizeof(SOCKADDR_IN) );
		}
		transData.append( "e", 1 );

		SendOne( &recv_socket[ client_idx ], &transData );
		sendaddress_cnt += sockaddr_cnt; // ������������plus
	}
	transData.init();
	transData.byte_sign = ADDRESS_DATA_END;
	SendOne( &recv_socket[ client_idx ], &transData );

//	printf("send : from address");
	return WINSOCK_SUCCESS;
}
void MyServer::UnConnectClient(int index)
{
	if( 0 <= index && index < (int)recv_data.size() ){
		_deleteRecieveData( index );
	}
}
bool MyServer::IsConnect(int index)
{
	return (recv_data[index] != NULL || recv_socket[index] != INVALID_SOCKET);
}
UINT MyServer::getAcceptcnt() const
{
	return accept_cnt;
}
UINT MyServer::getAcceptcntMax() const
{
	return accept_cnt_max;
}
DataStruct* MyServer::getRecvData(int idx) const
{
	return recv_data[ idx ];
}
SOCKADDR_IN* MyServer::getFromAddress(int idx) const
{
	return (SOCKADDR_IN*)(&from_addr[ idx ]);
}
//void MyServer::setAcceptcnt(unsigned int cnt)
//{
//	accept_cnt = cnt;
//}
void MyServer::setAcceptcntMax(unsigned int cnt_max)
{
	accept_cnt_max = cnt_max;
	from_addr.resize(accept_cnt_max);
	recv_data.resize(accept_cnt_max);
	recv_socket.resize(accept_cnt_max);
	for( unsigned int i=0 ; i<accept_cnt_max ; i++ ){
		recv_socket[ i ] = INVALID_SOCKET;
	}
}
//void MyServer::setFromAddress(int idx, SOCKADDR_IN* from)
//{
//	memcpy_s( &from_addr[idx], sizeof(SOCKADDR_IN), from, sizeof(SOCKADDR_IN) );
//}
int MyServer::Dispose()
{
	EndAccept();

	for(unsigned int i=0 ; i<accept_cnt_max ; i++){
		_deleteRecieveData( i );
	}
	if( accept_mutex != NULL ){
		CloseHandle( accept_mutex );
		accept_mutex = NULL;
	}
	accept_cnt = 0;
	accept_cnt_max = 0;
	from_addr.clear();
	recv_socket.clear();
	recv_data.clear();

	WSACleanup();
	return 0;
}


///---------------------------------------
//             static
///---------------------------------------
DWORD __stdcall MyServer::AcceptThread(void* lpvoid)
{
	if( lpvoid == NULL )
		return WINSOCK_ERROR;

	//server
	MyServer*   server = (MyServer*)lpvoid;
	SOCKET*     sock   = &(server->recv_socket[0]);
	SOCKADDR_IN from    = {};
	int         fromlen = sizeof(SOCKADDR_IN);
	
	//select
	fd_set  fds;
	TIMEVAL tv = {};

	// UDP �u���[�h�L���X�g��M�p
	BOOL yes = TRUE;
	int recv_result = 0;
	char buff[ 200 ] = {}; // "res." + "[name]"

	char sendbuff[100] = {};
	strcpy_s(sendbuff, "res,");
	strcat_s(sendbuff, server->getHostName().c_str());

	// �u���[�h�L���X�g ���M
	SOCKET broadsock = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons( SERVER_RESPONSE_PORT );
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");
	
	// �u���[�h�L���X�g TRUE
	setsockopt(broadsock, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));

	// UDP ��M
	SOCKET udprecvsock = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in udpRecvAddr = {};
	udpRecvAddr.sin_family = AF_INET;
	udpRecvAddr.sin_port = htons( SERVER_SEARCH_PORT );
	udpRecvAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	// ���Ɏg�p���̃\�P�b�g���ƃG���[���o��̂ł���̖h�~
	setsockopt(udprecvsock, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

	// �o�C���h
	if( bind(udprecvsock, (sockaddr*)&udpRecvAddr, sizeof(udpRecvAddr)) == SOCKET_ERROR ){
		SocketCloser( &udprecvsock );
		SocketCloser( &broadsock );
		server->_happenError();
		return WINSOCK_ERROR;
	}

	while( !server->listen_stop_flg )
	{
		if( server->accept_cnt_max - 1 <= server->accept_cnt ){
			continue;
		}

		// �u���[�h�L���X�g
		memset( buff, 0, sizeof(buff) );
		recv_result = Recv_select( &udprecvsock, buff, sizeof(buff) );
		if( recv_result == WINSOCK_SUCCESS ){
			if( strcmp(buff, "toMyServer") == 0 ){
				sendto(broadsock, sendbuff, strlen(sendbuff)+1, 0, (struct sockaddr *)&addr, sizeof(addr));
			}
		}

		// �}���`�L���X�g
		// 1�`max �܂ł̃\�P�b�g�ɋ󂫂�T��
		// 0 ��HOST���\��ς�
		int idx = 1;
		for(unsigned int i = idx ; i < server->accept_cnt_max ; i++ ){
			if( sock[ i ] == INVALID_SOCKET ){
				idx = i;
				break;
			}
		}

		// select�Ń\�P�b�g��T��
		FD_ZERO( &fds );
		FD_SET( server->listen_socket, &fds );
		select( FD_SETSIZE, &fds, NULL, NULL, &tv );
		if( !FD_ISSET( server->listen_socket, &fds ) ){
			continue;
		}

		// recv_data ��M��̂� mutex lock
		WaitForSingleObject( server->accept_mutex, INFINITE );
		sock[ idx ] = accept( server->listen_socket, (sockaddr*)&from, &fromlen );
		if( sock[ idx ] != INVALID_SOCKET ) {
			// from address���擾 / �ʐM�̈�m��
			memcpy_s( &(server->from_addr[ idx ]), fromlen, &from, fromlen );
			server->_createRecieveData( idx );
		}
		ReleaseMutex( server->accept_mutex );
	}
	// �I����������FALSE
	server->listen_stop_flg = false;

	SocketCloser( &udprecvsock );
	SocketCloser( &broadsock );
	return 0;
}

};


