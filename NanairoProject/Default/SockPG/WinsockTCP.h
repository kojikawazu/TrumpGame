#pragma once
#ifndef _MYTCP_
#define _MYTCP_

///------------------------
// *cppに記述してほしいな*
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
#define SERVER_LISTEN_PORT 8000 // サーバクライアントのソケット
#define CLIENT_LISTEN_PORT 8100 // クライアント同士のソケット
#define SERVER_SEARCH_PORT   12000 // クライアントがブロードキャストでサーバを探すときのソケット
#define SERVER_RESPONSE_PORT 13000 // サーバがブロードキャストに反応して返信するときのソケット
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

// ここは自由にいじっていいところ
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
// ポート番号
// wsaﾃﾞｰﾀ
// ソケットaddres(相手)
// エラーフラグ
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
	// 通信中の全RecieveDataにデータが届いてるかどうか確認する
	virtual int AllRecieve() = 0;
	// 通信中の全RecieveSocketにデータを送る
	virtual int AllSend(DataStruct* buff) = 0;
	// listen_socketを生成、listenを開始し、acceptThreadを走らせる
	virtual int BeginAccept(unsigned int port = SERVER_LISTEN_PORT) = 0;
	// listen_socketを破棄し、acceptThreadを終了させる
	// 以降、acceptは無効になる。返り値は現在通信中の人数。
	virtual int EndAccept() = 0;
	// Disposeで全部破棄した後、WSAStartを実行。
	virtual int Initialize() = 0;
	// 現在保持しているアドレスリストを送信する
	virtual int SendAddrList(int client_idx) = 0;
	// 通信用のデータが虫食い状態のとき、並べ直す
	virtual int TrimDataList() = 0;
	// clientとの接続を切る.indexは接続順.
	virtual void UnConnectClient(int index) = 0;

	// getter
	virtual UINT getAcceptcnt() = 0;
	virtual UINT getAcceptcntMax() = 0;
	virtual DataStruct* getRecvData(int idx) = 0;
	virtual SOCKADDR_IN* getFromAddress(int idx) = 0;

	// setter
	virtual void setAcceptcntMax(unsigned int cnt_max);

	// 資源解放
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
	// 通信用のデータとソケットを生成する
	int _createRecieveData( int idx );
	// 通信用のデータとソケットを破棄する
	int _deleteRecieveData( int idx );
	// listen_socketを生成、listenを開始する
	int _setupListen(unsigned int port);

public: // Override
	// 通信中の全RecieveDataにデータが届いてるかどうか確認する
	int AllRecieve();
	// 通信中の全RecieveSocketにデータを送る
	int AllSend(DataStruct* buff);
	// listen_socketを生成、listenを開始し、acceptThreadを走らせる
	int BeginAccept(unsigned int port = SERVER_LISTEN_PORT);
	// listen_socketを破棄し、acceptThreadを終了させる
	// 以降、acceptは無効になる。返り値は現在通信中の人数。
	int EndAccept();
	// Disposeで全部破棄した後、WSAStartを実行。
	virtual int Initialize();
	// 現在保持しているアドレスリストを送信する
	int SendAddrList(int client_idx);
	// 通信用のデータが虫食い状態のとき、並べ直す
	int TrimDataList();
	// clientとの接続を切る.indexは接続順.
	void UnConnectClient(int index);
	// clientとの接続の確認
	bool IsConnect(int index);

	// getter
	UINT getAcceptcnt() const;
	UINT getAcceptcntMax() const;
	DataStruct* getRecvData(int idx) const;
	SOCKADDR_IN* getFromAddress(int idx) const;

	// setter
	void setAcceptcntMax(unsigned int cnt_max);

	// 資源解放
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

	// こいつらのどれと繋がりたい？
	std::list<char*> serverIPList;

	MyClient();
	~MyClient();

protected:
	int _setupConnect(unsigned int port);

public:
	// serverIPListに存在するか？
	bool CheckIPListMemb(char* ip_addr);
	// serverにconnectする
	int ConnectServer(unsigned int port = SERVER_LISTEN_PORT);
	// serverIPListの内容を削除する
	void DeleteIPList();
	// serverのconnectを切る
	void UnConnectServer();
	// serverに通知し、接続idを得る
	int NotifyNewAccept();
	// Disposeで全部破棄した後、WSAStartを実行。
	int Initialize();
	// Serverを一つ探し出してくれる
	// 新たなものが見つからない場合 WINSOCK_UNRECIEVE を返す
	int SearchServer();
	// Serverとつながっているかどうか
	bool IsConnected();


	
	// getter
	int getIDNumber() const;
	const unsigned int getIPListSize();
	const char* getIPListMemb(int index);

	// setter
	void setIDNumber(int id);
	void setServerIP(char* str_ip);
	void setServerIP(UINT v1, UINT v2, UINT v3, UINT v4);

	// 資源解放
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
	// serverから取得したアドレス群にacceptを求める
	int ConnectToAddressList();
	// serverにconnectする
	int ConnectServer(unsigned int port = SERVER_LISTEN_PORT);
	// serverに通知し、接続id、参加者数、最大参加者数を得る
	int NotifyNewAccept();
	// Disposeで全部破棄した後、WSAStartを実行。
	int Initialize();
	// serverに通知し、接続済み参加者のアドレス群を得る
	int RecieveConnectedAddress();

	// getter
	int getIDNumber() const;

	// setter
	void setIDNumber(int id);
	void setServerIP(char* str_ip);
	void setServerIP(UINT v1, UINT v2, UINT v3, UINT v4);

	// 資源解放
	int Dispose();
};
//*/

};


#endif /* _MYTCP_ */

