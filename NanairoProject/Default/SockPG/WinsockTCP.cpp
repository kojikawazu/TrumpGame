#pragma once
#include "WinsockTCP.h"

#pragma comment(lib, "ws2_32.lib")

namespace sockNW{
// srcbuff + offset����n�܂�T�C�Y���w�肵�Ď󂯎��B
// ���f�[�^�ɂ͉e�����Ȃ��B
char* getDataFromBuff( char* dstbuff, int dstbuff_size, char* srcbuff, int srcbuff_size, int offset ){
	if( dstbuff == NULL || srcbuff == NULL )
		return NULL;

	memcpy_s( dstbuff, dstbuff_size, srcbuff + offset, srcbuff_size );
	return dstbuff;
}
char* addDataToBuff(char* dstbuff, int dstbuff_size, char* srcbuff, int srcbuff_size){
	memcpy_s( dstbuff, dstbuff_size, srcbuff, srcbuff_size );
	return dstbuff + srcbuff_size; // buff�̍Ō��Ԃ�
}
int Recv_select(SOCKET* sock, char* buff, int size)
{
	fd_set  fds;
	TIMEVAL t; t.tv_sec = 0; t.tv_usec = 0;
	std::vector<char> local; local.resize(size);
	memset( &(local[0]), 0, sizeof(char)*size );

	FD_ZERO( &fds );
	FD_SET( *sock, &fds );

	// data�͂��Ă�H
	select( 1, &fds, NULL, NULL, &t );
	if( !FD_ISSET( *sock, &fds ) ){
		local.clear();
		return WINSOCK_UNRECIEVE;
	}

	// �󂯎��
	int nRcv = recv( *sock, &(local[0]), size, 0 );
	if( nRcv == SOCKET_ERROR ){
		SocketCloser( sock );
		local.clear();
		return WINSOCK_LOGOUT;
	}

	// ����ł���΃R�s�[
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
		name[0] = '\0'; // �z�X�g�����擾�ł��Ȃ�������
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

	// data�͂��Ă�H
	select( 1, &readfds, NULL, NULL, &t );
	if( !FD_ISSET( *sock, &readfds ) ){
		return WINSOCK_UNRECIEVE;
	}

	DATA_HEADER dataHead;
	// �󂯎��( Header��Data�ɕ����čs��
	int nRcv = recv( *sock, (char*)&dataHead, sizeof(DATA_HEADER), 0 );
	if( nRcv == SOCKET_ERROR ){
		SocketCloser( sock );
		return WINSOCK_LOGOUT;
	}
	// data�̓o�b�t�@��0���ᖳ���Ƃ���
	if( dataHead.size && (DATA_NONE <= dataHead.byte_sign && dataHead.byte_sign < DATA_FLAGS_MAX) ){
		local = new char[ dataHead.size ];
		nRcv = recv( *sock, local, dataHead.size, 0 );
		if( nRcv == SOCKET_ERROR ){
			SocketCloser( sock );
			delete[] local;
			return WINSOCK_LOGOUT;
		}
		// ����ł���΃R�s�[
		buff->set( local, dataHead.size );
		delete[] local;
	}
	// ����ł���΃R�s�[
	buff->header = dataHead;
	return WINSOCK_SUCCESS;
}
int WinSockStarter::SendOne(SOCKET* sock, DataStruct* buff)
{
	if( err_flg || (*sock) == INVALID_SOCKET )
		return WINSOCK_ERROR;

	std::vector<char> charbuff;
	charbuff.resize( buff->totalSize() );

	// �l�R�s�[( data�̓o�b�t�@��0���ᖳ���Ƃ���
	memcpy_s( &(charbuff[0]), charbuff.size(), &(buff->header), sizeof( DATA_HEADER ) );
	if( buff->size ){
		memcpy_s( &(charbuff[ sizeof(DATA_HEADER) ]), charbuff.size() - sizeof(DATA_HEADER), &(buff->data[0]), buff->size );
	}

	// ���M�͈ꊇ��
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

	// �T�[�o�p�ް�����
	*server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if( *server_socket == INVALID_SOCKET ){
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
	
	// ���Ɏg�p���̃\�P�b�g���ƃG���[���o��̂ł���̖h�~
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

	// 0 �̓T�o�Ȃ̂ł��������A�N�Z�X���Ȃ�
	for( unsigned int i=1; i < accept_cnt ; i++ ){
		// �������g�ɂ͐ڑ����Ȃ�
		// �A�h���X == 0 �Ȃ�ڑ�����
		if( client_id == i || (pfrom[i].sin_addr.s_addr == 0) )
			continue;

		// �\�P�b�g����
		recv_socket[i] = socket(AF_INET, SOCK_STREAM, 0);
		if( recv_socket[i] == INVALID_SOCKET ){
			continue;
		}
		// ���Ɏg�p���̃\�P�b�g���ƃG���[���o��̂ł���̖h�~
		BOOL yes = TRUE;
		setsockopt(recv_socket[i], SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

		// �R�l�N�g
		if( connect(recv_socket[i], (sockaddr*)&from_addr[i], sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
//			printf("error : %d\n", WSAGetLastError());
			SocketCloser( &recv_socket[i] );
			continue;
		}
		// �R�l�N�g���� => �f�[�^����
		_createRecieveData( i );
//		printf("%d �ɐڑ�\n", i);
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
	int itransbuff = 0; // �ϊ��pbuff

	do{
		// �V���ȃN���C�A���g�̒ʒm
		data.byte_sign = NEW_ACCEPT;
		SendOne( server_socket, &data );

		// �ʒm�ɑ΂���ԓ�(�������Ă��Ȃ���while)
		data.byte_sign = DATA_NONE;
		if( RecvOne( server_socket, &data) == WINSOCK_LOGOUT ){
			_happenError();
			break;
		}
	}while( data.byte_sign != NEW_ACCEPT );

	if( err_flg ){
		return WINSOCK_ERROR;
	}

	// recv_servser.data�ɂ� �ő�l,���݂̎Q���Ґ�,id�ԍ� ��csv�œ����Ă���
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
	// ��x�������
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

	// "s + �A�h���X�̐� + ... + e"
	// ADDRESS_DATA_END������܂ł͘A�����Ă��Ă�Ǝv���Ď󂯎����
	while( data.byte_sign != ADDRESS_DATA_END ){
		// �V���ȃN���C�A���g�̒ʒm
		data.byte_sign = ADDRESS_DATA;
		SendOne( server_socket, &data );

		// �ʒm�ɑ΂���ԓ�(�������Ă��Ȃ���while)
		result = RecvOne( server_socket, &data );
		// �T�[�o�Ƃ̉�����؂�Ă�
		if( result == WINSOCK_LOGOUT ) {
			_happenError(); // �����邵���Ȃ�
			break;
		}
		// �Ȃ�����ĂȂ�������continue
		if( result == WINSOCK_UNRECIEVE ||
			(data.byte_sign != ADDRESS_DATA &&
			 data.byte_sign != ADDRESS_DATA_END ) ) {
			continue;
		}
		// �I����Ă���break
		if( data.byte_sign == ADDRESS_DATA_END ) {
//			printf( "ADDRESS_DATA_END\n" );
			break;
		}

		// server�m��!
		// start �� s
		offset = 0;
		getDataFromBuff( buff, bufflen, data.data, sizeof(char), offset );
		if( buff[0] != 's' ){
			_happenError(); // �����邵���Ȃ�
			break;
		}
		// �����Ă����A�h���X�̐�
		offset += sizeof(char);
		getDataFromBuff( buff, bufflen, data.data, sizeof(char), offset );
		memcpy_s( &addr_size, sizeof(int), buff, sizeof(int) );
		addr_loop_start = addr_loop_end;
		addr_loop_end += addr_size;
		// �����Ă������v�����e�ʒ����Ƃ�
		if( (UINT)addr_loop_end > accept_cnt_max ){
			_happenError(); // �����邵���Ȃ�
			break;
		}
		// end �� e
		// ���������񂾂�����www
		// csv�Ƃ��g�����Ⴞ�߂�www
		offset += sizeof(SOCKADDR_IN) * addr_size + sizeof(char);
		getDataFromBuff( buff, bufflen, data.data, sizeof(char), offset );
		if( buff[0] != 'e' ){
			_happenError(); // �����邵���Ȃ�
			break;
		}

		// s��e���m�F�ł�����ʐM�͐����I
//		printf("address ok - ");
		// set�����!
		SOCKADDR_IN tmp = {};
		offset = sizeof(char)*2;
		for( int i=addr_loop_start ; i<addr_loop_end ; i++ ){
			getDataFromBuff( (char*)&tmp, sizeof(SOCKADDR_IN), data.data, sizeof(SOCKADDR_IN), offset );
			offset += sizeof(SOCKADDR_IN);
			// port ��client��������Ă�����̂ɕύX����set
			tmp.sin_port = htons( CLIENT_LISTEN_PORT );
			memcpy_s( &from_addr[i], sizeof(SOCKADDR_IN), &tmp, sizeof(SOCKADDR_IN) );
			//setFromAddress( i, &tmp );
		}
//		printf("for end\n");
	}

	// �I���̍��}
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
