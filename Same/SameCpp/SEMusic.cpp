#pragma once
////------------------------------------------------
//
//���ʉ�����N���X
//
//---------------------------------------------------
#pragma region �C���N���[�h
#include <MusicSound.h>

#pragma warning(disable : 4995)
#pragma warning(disable : 4996)
#pragma endregion

namespace NanairoLib
{
	inline SEFunc::SEFunc(){}
	inline SEFunc::~SEFunc(){}

	//------------------------------------------------------------
	//���y�̃��[�h
	//------------------------------------------------------------
	//@in : �t�@�C���p�X
	//@in : �V�������O
	//@out : ���� ���s
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
	//���y�̍Đ�
	//-------------------------------------------------
	//@in : �Đ����������O
	//@out : ���� ���s
	HRESULT SEFunc::PlayMusic(LPCSTR fileName)
	{
		char name[256];
		strcpy(name,"play ");
		strcat(name,fileName);
		strcat(name," from 0");
		return ((::mciSendStringA(name,NULL,0,NULL) != 0) ? E_FAIL : S_OK);
	}
	
	//---------------------------------------------
	//���y�̒�~
	//---------------------------------------------
	//@in : �Đ����Ă��閼�O
	//@out : ���� ���s
	HRESULT SEFunc::StopMusic(LPCSTR fileName)
	{
		char name[256];
		strcpy(name,"stop ");
		strcat(name,fileName);
		return ((::mciSendStringA(name,NULL,0,NULL) != 0) ? E_FAIL : S_OK);
	}
	
	//------------------------------------------------
	//���y�̃����[�X
	//------------------------------------------------
	//@in : �ۑ��������O
	//@out : ���� ���s
	HRESULT SEFunc::ReleaseMusic(LPCSTR fileName)
	{
		char name[256];
		strcpy(name,"close ");
		strcat(name,fileName);
		return ((::mciSendStringA(name,NULL,0,NULL) != 0) ? E_FAIL : S_OK);
	}	
	
	//-------------------------------------------
	//���y���Đ�����Ă��邩
	//-------------------------------------------
	//@in : �Đ����Ă��閼�O
	//@out : true(�Đ���) false(�Đ����Ă��Ȃ�)
	bool SEFunc::CheckMusic(LPCSTR fileName)
	{
		char name[256],str[256];
		strcpy(name,"status ");
		strcat(name,fileName);
		strcat(name," mode");
		::mciSendStringA(name,str,sizeof(str),NULL);
		return (strcmp(str,"stopped") == 0);
	}
	
	#pragma region �R���X�g���N�^
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