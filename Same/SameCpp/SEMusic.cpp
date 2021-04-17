#pragma once
////------------------------------------------------
//
//効果音制御クラス
//
//---------------------------------------------------
#pragma region インクルード
#include <MusicSound.h>

#pragma warning(disable : 4995)
#pragma warning(disable : 4996)
#pragma endregion

namespace NanairoLib
{
	inline SEFunc::SEFunc(){}
	inline SEFunc::~SEFunc(){}

	//------------------------------------------------------------
	//音楽のロード
	//------------------------------------------------------------
	//@in : ファイルパス
	//@in : 新しい名前
	//@out : 成功 失敗
	HRESULT SEFunc::InitMusic(LPCSTR fileName,LPCSTR bgmName)
	{
		char name[256];
		char check[128];

		sizeof(name,0,sizeof(name));
		strcpy(name,"open \"");
		strcat(name,fileName);
		strcat(name,"\" alias ");
		strcat(name,bgmName);
		DWORD hr = ::mciSendStringA(name,NULL,0,NULL);
		memset(check,0,sizeof(check));
		mciGetErrorString(hr,check,sizeof(check));
		return S_OK;
	}
	
	//-------------------------------------------------
	//音楽の再生
	//-------------------------------------------------
	//@in : 再生したい名前
	//@out : 成功 失敗
	HRESULT SEFunc::PlayMusic(LPCSTR fileName)
	{
		char name[256];
		strcpy(name,"play ");
		strcat(name,fileName);
		strcat(name," from 0");
		return ((::mciSendStringA(name,NULL,0,NULL) != 0) ? E_FAIL : S_OK);
	}
	
	//---------------------------------------------
	//音楽の停止
	//---------------------------------------------
	//@in : 再生している名前
	//@out : 成功 失敗
	HRESULT SEFunc::StopMusic(LPCSTR fileName)
	{
		char name[256];
		strcpy(name,"stop ");
		strcat(name,fileName);
		return ((::mciSendStringA(name,NULL,0,NULL) != 0) ? E_FAIL : S_OK);
	}
	
	//------------------------------------------------
	//音楽のリリース
	//------------------------------------------------
	//@in : 保存した名前
	//@out : 成功 失敗
	HRESULT SEFunc::ReleaseMusic(LPCSTR fileName)
	{
		char name[256];
		strcpy(name,"close ");
		strcat(name,fileName);
		return ((::mciSendStringA(name,NULL,0,NULL) != 0) ? E_FAIL : S_OK);
	}	
	
	//-------------------------------------------
	//音楽が再生されているか
	//-------------------------------------------
	//@in : 再生している名前
	//@out : true(再生中) false(再生していない)
	bool SEFunc::CheckMusic(LPCSTR fileName)
	{
		char name[256],str[256];
		strcpy(name,"status ");
		strcat(name,fileName);
		strcat(name," mode");
		::mciSendStringA(name,str,sizeof(str),NULL);
		return (strcmp(str,"stopped") == 0);
	}
	
	#pragma region コンストラクタ
	inline SEData::SEData() : bgmName(NULL) , used(false) , playFlag(false){}
	inline SEData::~SEData(){}

	SEData::SEData(LPCSTR fileName,LPCSTR name) : bgmName(name)
	{
		SEFunc mm;
		used = !( FAILED( mm.InitMusic(fileName,name) ) );
		playFlag = false;
	}
	#pragma endregion

}