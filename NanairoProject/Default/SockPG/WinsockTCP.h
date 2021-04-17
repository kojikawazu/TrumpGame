#pragma once
#ifndef _MYTCP_
#define _MYTCP_

///------------------------
// *cpp�ɋL�q���Ăق�����*
///------------------------
// #pragma comment(lib, "ws2_32.lib")
///------------------------

#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_CONIO
#include <conio.h>
#endif
#ifndef _WINSOCK2API_
#include <winsock2.h>
#endif
#ifndef _SSTREAM_
#include <sstream>
#endif
#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _LIST_
#include <list>
#endif


namespace sockNW{

//////////////////////////////////////////////////////////////////////////
//#define IP_ADDRESSLIST_PATH ".\ip_list.txt"
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
#define SERVER_LISTEN_PORT 8000 // �T�[�o�N���C�A���g�̃\�P�b�g
#define CLIENT_LISTEN_PORT 8100 // �N���C�A���g���m�̃\�P�b�g
#define SERVER_SEARCH_PORT   12000 // �N���C�A���g���u���[�h�L���X�g�ŃT�[�o��T���Ƃ��̃\�P�b�g
#define SERVER_RESPONSE_PORT 13000 // �T�[�o���u���[�h�L���X�g�ɔ������ĕԐM����Ƃ��̃\�P�b�g
char* getDataFromBuff(char* dstbuff, int dstbuff_size, char* srcbuff, int srcbuff_size, int offset);
char* addDataToBuff(char* dstbuff, int dstbuff_size, char* srcbuff, int srcbuff_size);
//////////////////////////////////////////////////////////////////////////


#define MAX_CLIENT 64
#define WINSOCK_UNRECIEVE  1
#define WINSOCK_SUCCESS    0
#define WINSOCK_ERROR     -1
#define WINSOCK_LOGOUT    -2

#define IP_ADDERSS_LENGTH 32
#define IP_ADDERSS_BUFFSIZE 32

// �����͎��R�ɂ������Ă����Ƃ���
enum eDATA_FLAGS{
	DATA_NONE   = 0,
	NEW_ACCEPT,
	ADDRESS_DATA,
	ADDRESS_DATA_END,
	NORMAL_DATA,
	SERVER_DATA,
	CLIENT_DATA,
	UNCONNECT_DATA,
	
	SEARCH_DATA,
	CHARAPRISET_DATA,
	ROOM_DATA_UPDATE,
	KICKOUT_DATA,
	READYON_DATA,
	READYOFF_DATA,
	GAMESTART_DATA,
	
	PLAY_DATA,
	NEWS_LIST,
	ENEM_DATA,
	ENEM_AI_NEWSIS,
	PRESET_DATA,
	ERRORCHECK_DATA,
	LOAD_END,
	DATA_FLAGS_MAX
};
int Recv_select(SOCKET* sock, char* buff, int size);
int SocketCloser(SOCKET* sock);



struct DATA_HEADER{
	unsigned int size;
	unsigned int id;
	eDATA_FLAGS byte_sign;
};
static const int DATA_HEADER_SIZE = sizeof(DATA_HEADER);
class DataStruct{
public:
	union{
		struct { unsigned int size; unsigned int id; eDATA_FLAGS byte_sign; };
		DATA_HEADER header;
	};
	std::vector<char> data;

	DataStruct();
	DataStruct* init();
	char* getData();
	DataStruct* set(char* buff, unsigned int size);
	DataStruct* append(char* buff, unsigned int size);
	DataStruct* copy(DataStruct* dist);
	unsigned int headerSize();
	unsigned int dataSize();
	unsigned int totalSize();
};


///-----
// �|�[�g�ԍ�
// wsa�ް�
// �\�P�b�gaddres(����)
// �G���[�t���O
///-----
class WinSockStarter{
protected:
	typedef std::vector<SOCKADDR_IN>  FROM_CONTAINER;
	typedef std::vector<SOCKET>       SOCK_CONTAINER;
//	typedef std::vector<DATA_STRUCT*> DATA_CONTAINER;
	typedef std::vector<DataStruct*> DATA_CONTAINER;

	u_short      uport;
	WSADATA      wsaData;
	fd_set       readfds;
	bool         err_flg;
	std::ostringstream hostname;

	WinSockStarter();
	int  _beginWSA();
	void _happenError();
	void _setPort(u_short port);

public:
	std::string getHostName();
	bool IsError();

	int RecvOne(SOCKET* sock, DataStruct* buff);
	int SendOne(SOCKET* sock, DataStruct* buff);
};

enum SV_STATE{
	NOT_USED,
	WAIT_ACCEPT
};
class IMyServer{
public:
	virtual ~IMyServer(){};

public:
	// �ʐM���̑SRecieveData�Ƀf�[�^���͂��Ă邩�ǂ����m�F����
	virtual int AllRecieve() = 0;
	// �ʐM���̑SRecieveSocket�Ƀf�[�^�𑗂�
	virtual int AllSend(DataStruct* buff) = 0;
	// listen_socket�𐶐��Alisten���J�n���AacceptThread�𑖂点��
	virtual int BeginAccept(unsigned int port = SERVER_LISTEN_PORT) = 0;
	// listen_socket��j�����AacceptThread���I��������
	// �ȍ~�Aaccept�͖����ɂȂ�B�Ԃ�l�͌��ݒʐM���̐l���B
	virtual int EndAccept() = 0;
	// Dispose�őS���j��������AWSAStart�����s�B
	virtual int Initialize() = 0;
	// ���ݕێ����Ă���A�h���X���X�g�𑗐M����
	virtual int SendAddrList(int client_idx) = 0;
	// �ʐM�p�̃f�[�^�����H����Ԃ̂Ƃ��A���ג���
	virtual int TrimDataList() = 0;
	// client�Ƃ̐ڑ���؂�.index�͐ڑ���.
	virtual void UnConnectClient(int index) = 0;

	// getter
	virtual UINT getAcceptcnt() = 0;
	virtual UINT getAcceptcntMax() = 0;
	virtual DataStruct* getRecvData(int idx) = 0;
	virtual SOCKADDR_IN* getFromAddress(int idx) = 0;

	// setter
	virtual void setAcceptcntMax(unsigned int cnt_max);

	// �������
	virtual int Dispose();
};
class MyServer : public WinSockStarter/*, public IMyServer*/{
public:
	unsigned int accept_cnt;
	unsigned int accept_cnt_max;
	HANDLE       accept_mutex;

	SV_STATE     state;
	SOCKET       listen_socket;
	bool         listen_stop_flg;
	
	// list
	FROM_CONTAINER from_addr;
	SOCK_CONTAINER recv_socket;
	DATA_CONTAINER recv_data;

	MyServer();
	~MyServer();

protected:
	// �ʐM�p�̃f�[�^�ƃ\�P�b�g�𐶐�����
	int _createRecieveData( int idx );
	// �ʐM�p�̃f�[�^�ƃ\�P�b�g��j������
	int _deleteRecieveData( int idx );
	// listen_socket�𐶐��Alisten���J�n����
	int _setupListen(unsigned int port);

public: // Override
	// �ʐM���̑SRecieveData�Ƀf�[�^���͂��Ă邩�ǂ����m�F����
	int AllRecieve();
	// �ʐM���̑SRecieveSocket�Ƀf�[�^�𑗂�
	int AllSend(DataStruct* buff);
	// listen_socket�𐶐��Alisten���J�n���AacceptThread�𑖂点��
	int BeginAccept(unsigned int port = SERVER_LISTEN_PORT);
	// listen_socket��j�����AacceptThread���I��������
	// �ȍ~�Aaccept�͖����ɂȂ�B�Ԃ�l�͌��ݒʐM���̐l���B
	int EndAccept();
	// Dispose�őS���j��������AWSAStart�����s�B
	virtual int Initialize();
	// ���ݕێ����Ă���A�h���X���X�g�𑗐M����
	int SendAddrList(int client_idx);
	// �ʐM�p�̃f�[�^�����H����Ԃ̂Ƃ��A���ג���
	int TrimDataList();
	// client�Ƃ̐ڑ���؂�.index�͐ڑ���.
	void UnConnectClient(int index);
	// client�Ƃ̐ڑ��̊m�F
	bool IsConnect(int index);

	// getter
	UINT getAcceptcnt() const;
	UINT getAcceptcntMax() const;
	DataStruct* getRecvData(int idx) const;
	SOCKADDR_IN* getFromAddress(int idx) const;

	// setter
	void setAcceptcntMax(unsigned int cnt_max);

	// �������
	virtual int Dispose();
	
private: // static
	static DWORD __stdcall AcceptThread(void* lpvoid);
};
/*
class IMyClient{
public:
	virtual int BeginConnect()            PURE;
	virtual int Recieve()                 PURE;
	virtual int Release()                 PURE;
	virtual int SendServer(char* buff, int size) PURE;
	virtual int getIDNumber()             PURE;
	virtual DATA_STRUCT* getRecvData()    PURE;
	virtual int setServerIP(char* str_ip) PURE;
	virtual int setServerIP(UINT v1, UINT v2, UINT v3, UINT v4) PURE;
};
//*/
class MyClient : public WinSockStarter{
public:
	int client_id;
	char buffServerIp[IP_ADDERSS_LENGTH];
	SOCKET server_socket;
	DataStruct* server_data;

	// ������̂ǂ�ƌq���肽���H
	std::list<char*> serverIPList;

	MyClient();
	~MyClient();

protected:
	int _setupConnect(unsigned int port);

public:
	// serverIPList�ɑ��݂��邩�H
	bool CheckIPListMemb(char* ip_addr);
	// server��connect����
	int ConnectServer(unsigned int port = SERVER_LISTEN_PORT);
	// serverIPList�̓��e���폜����
	void DeleteIPList();
	// server��connect��؂�
	void UnConnectServer();
	// server�ɒʒm���A�ڑ�id�𓾂�
	int NotifyNewAccept();
	// Dispose�őS���j��������AWSAStart�����s�B
	int Initialize();
	// Server����T���o���Ă����
	// �V���Ȃ��̂�������Ȃ��ꍇ WINSOCK_UNRECIEVE ��Ԃ�
	int SearchServer();
	// Server�ƂȂ����Ă��邩�ǂ���
	bool IsConnected();


	
	// getter
	int getIDNumber() const;
	const unsigned int getIPListSize();
	const char* getIPListMemb(int index);

	// setter
	void setIDNumber(int id);
	void setServerIP(char* str_ip);
	void setServerIP(UINT v1, UINT v2, UINT v3, UINT v4);

	// �������
	int Dispose();
};

/*
class MyClient2 : public MyServer {
public:
	int client_id;
	char buffServerIp[IP_ADDERSS_LENGTH];
	SOCKET* server_socket;

	MyClient2();
	~MyClient2();

protected:
	int _setupConnect(unsigned int port);

public:
	// server����擾�����A�h���X�Q��accept�����߂�
	int ConnectToAddressList();
	// server��connect����
	int ConnectServer(unsigned int port = SERVER_LISTEN_PORT);
	// server�ɒʒm���A�ڑ�id�A�Q���Ґ��A�ő�Q���Ґ��𓾂�
	int NotifyNewAccept();
	// Dispose�őS���j��������AWSAStart�����s�B
	int Initialize();
	// server�ɒʒm���A�ڑ��ςݎQ���҂̃A�h���X�Q�𓾂�
	int RecieveConnectedAddress();

	// getter
	int getIDNumber() const;

	// setter
	void setIDNumber(int id);
	void setServerIP(char* str_ip);
	void setServerIP(UINT v1, UINT v2, UINT v3, UINT v4);

	// �������
	int Dispose();
};
//*/

};


#endif /* _MYTCP_ */

