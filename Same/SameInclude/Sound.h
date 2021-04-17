#pragma once
#ifndef MYDIRECTX_SOUND_H
#define MYDIRECTX_SOUND_H

//-----------------------------------------------------------
//
//音楽制御クラス
//
//-----------------------------------------------------------
#include <DirectNeed.h>
#include <dsound.h>
#include <map>

namespace MyDirectX
{
	class BGMData;
	class SEData;

	typedef std::map<std::string, MyDirectX::SEData>				BGMMap;
	typedef std::map<std::string, MyDirectX::SEData>::iterator		BGMIterator;
	typedef std::map<std::string, MyDirectX::SEData>::value_type	BGMType;

	typedef std::map<std::string, MyDirectX::BGMData>				SEMap;
	typedef std::map<std::string, MyDirectX::BGMData>::iterator		SEIterator;
	typedef std::map<std::string, MyDirectX::BGMData>::value_type	SEType;

	//-------------------------------------------
	//BGM情報クラス
	//-------------------------------------------
	class BGMData
	{
		public:
			bool used,playFlag;
			IDirectSoundBuffer *secondBuffer;
		public:
			__IMPOETER BGMData();
			__IMPOETER BGMData(IDirectSound8 *Dsound8,LPSTR fileName);
			__IMPOETER ~BGMData();
	};

	//--------------------------------------------------
	//効果音情報クラス
	//--------------------------------------------------
	class SEData
	{
		public:
			bool used,playFlag;
			LPCSTR bgmName;
		public:
			__IMPOETER SEData();
			__IMPOETER SEData(LPCSTR fileName,LPCSTR name);
			__IMPOETER ~SEData();
	};

	//--------------------------------------------------
	//BGM管理制御クラス
	//--------------------------------------------------
	class BGMFunc
	{
		public:
			//---------------------------------------------------------
			//このクラスを使うときに初期化する関数
			//---------------------------------------------------------
			//@in : ウィンドウハンドル
			//@out : サウンドインターフェイス
			__IMPOETER	IDirectSound8* InitSound8(HWND hWnd);
			__IMPOETER	IDirectSoundBuffer* SetPrimary(IDirectSound8 *Dsound8,HWND hWnd);
			
			//------------------------------------------------------------------------------------
			//音楽のリリース
			//------------------------------------------------------------------------------------
			//@in : サウンド制御インターフェイス
			//@in : サウンドバッファ
			//@out : 成功 失敗
			__IMPOETER	HRESULT ClearSound(IDirectSound8 *Dsound8,IDirectSoundBuffer *soundBuffer);
			
			//-------------------------------------------------------------------------------
			//音楽のロード
			//-------------------------------------------------------------------------------
			//@in : サウンドインターフェイス
			//@in : ファイルパス
			//@out : サウンドバッファ
			__IMPOETER	IDirectSoundBuffer* LoadSoundMX(IDirectSound8 *Dsound8,LPSTR fileName);
			
			//-------------------------------------------------------------------------
			//音楽の再生
			//-------------------------------------------------------------------------
			//@in : サウンドバッファ
			//@in : 0(ループなし) それ以外(ループ)
			//@in : 0(最初に戻す) それ以外（途中から）
			//@out : 成功 失敗
			__IMPOETER	HRESULT PlaySound(IDirectSoundBuffer *buffer,int mode = 0,int posi = 0);
			
			//-------------------------------------------------------------
			//音楽の停止
			//-------------------------------------------------------------
			//@in : サウンドバッファ
			//out : 成功 失敗
			__IMPOETER	HRESULT StopSound(IDirectSoundBuffer *buffer);
			
			//---------------------------------------------------------------------------
			//バッファのチェック
			//---------------------------------------------------------------------------
			//@in : サウンドバッファ
			//@in : 再生したい位置
			//@out : 成功 失敗
			__IMPOETER	HRESULT ChangeBuffer(IDirectSoundBuffer *buffer,DWORD posi);
			
			//---------------------------------------------------------------
			//音楽が再生されているか
			//---------------------------------------------------------------
			//@in : サウンドバッファ
			//@out : 再生している 再生していない
			__IMPOETER	HRESULT CheckSound(IDirectSoundBuffer *buffer);
		public:

			__IMPOETER BGMFunc();
			__IMPOETER ~BGMFunc();
	};

	//--------------------------------------------------
	//効果音管理制御クラス
	//--------------------------------------------------
	class SEFunc
	{
		public:
			//------------------------------------------------------------
			//音楽のロード
			//------------------------------------------------------------
			//@in : ファイルパス
			//@in : 新しい名前
			//@out : 成功 失敗
			__IMPOETER HRESULT InitMusic(LPCSTR fileName,LPCSTR bgmName);
			
			//-------------------------------------------------
			//音楽の再生
			//-------------------------------------------------
			//@in : 再生したい名前
			//@out : 成功 失敗
			__IMPOETER HRESULT PlayMusic(LPCSTR fileName);
			
			//---------------------------------------------
			//音楽の停止
			//---------------------------------------------
			//@in : 再生している名前
			//@out : 成功 失敗
			__IMPOETER HRESULT StopMusic(LPCSTR fileName);
			
			//------------------------------------------------
			//音楽のリリース
			//------------------------------------------------
			//@in : 保存した名前
			//@out : 成功 失敗
			__IMPOETER HRESULT ReleaseMusic(LPCSTR fileName);
			
			//-------------------------------------------
			//音楽が再生されているか
			//-------------------------------------------
			//@in : 再生している名前
			//@out : true(再生中) false(再生していない)
			__IMPOETER bool CheckMusic(LPCSTR fileName);
		public:
			__IMPOETER SEFunc();
			__IMPOETER ~SEFunc();
	};

	//-----------------------------------------------------
	//BGM情報を保持・管理・操作するクラス
	//-----------------------------------------------------
	class BGMFactory
	{
		private:
			bool soundFlag;
			BGMMap	_bgm;
		public:
			//------------------------------------
			//デコン
			//------------------------------------
			__IMPOETER BGMFactory();
			__IMPOETER ~BGMFactory();
			__IMPOETER bool IsSound(){	return this->soundFlag;	}
			__IMPOETER void OnSound(){	this->soundFlag = true;	}
			__IMPOETER void OffSound(){	this->soundFlag = false;}
		
			//----------------------------------------------------------------------
			//音楽をロード
			//----------------------------------------------------------------------
			//@in : ファイルパス
			//@in : 保存名前
			//@out : true(成功) false(失敗)
			__IMPOETER bool LoadMusic(LPCTSTR str,LPCTSTR name);
			
			//----------------------------------------------------------------------
			//音楽をリリース
			//----------------------------------------------------------------------
			//@in : 保存名前
			__IMPOETER void ReleaseMusic(LPCSTR name);
			
			//-------------------------------------------------
			//オールリリース
			//-------------------------------------------------
			__IMPOETER void AllRelease();

			//----------------------------------------------------------------------
			//ミュージックの取得
			//----------------------------------------------------------------------
			//@in : 保存名前
			//@inout : 取得するポインタ
			//@out : true(成功) false(失敗)
			__IMPOETER bool GetMusic(LPCSTR name,const MyDirectX::SEData* bgm);

			//----------------------------------------------------------------------
			//存在しているか
			//----------------------------------------------------------------------
			//@in : 保存名前
			//@out : true(存在中) false(存在していない)
			__IMPOETER bool IsMusic(LPCSTR name);

			//----------------------------------------------------------------------
			//プレイ
			//----------------------------------------------------------------------
			//@in : 保存名前
			__IMPOETER void Play(LPCSTR name);
			
			//----------------------------------------------------------------------
			//ストップ
			//----------------------------------------------------------------------
			//@in : 保存名前
			__IMPOETER void Stop(LPCSTR name);

			//----------------------------------------------------------------------
			//チェック
			//----------------------------------------------------------------------
			//@in : 保存名前
			///stopped	→　false 鳴ってない
			///noStop	→	true  鳴ってる
			__IMPOETER bool Check(LPCSTR name);
		
	};

	//-----------------------------------------------------
	//効果音情報を保持・管理・操作するクラス
	//-----------------------------------------------------
	class SEFactory
	{
		private:
			IDirectSound8		*Dsound8;		//メインサウンド
			IDirectSoundBuffer	*soundBuffer;	//バッファ
			SEMap				_se;
		private:
			__IMPOETER void AllRelease();

		public:
			__IMPOETER SEFactory();
			__IMPOETER ~SEFactory();
			__IMPOETER void InitMusic(HWND hWnd);

			//----------------------------------------------------------------------
			//効果音のロード
			//----------------------------------------------------------------------
			//@in : ファイル名
			//@in : 保存番号
			__IMPOETER bool LoadMusic(LPCTSTR str,LPCSTR name);

			//----------------------------------------------------------------------
			//効果音のリリース
			//----------------------------------------------------------------------
			//@in : 保存名前
			__IMPOETER void ReleaseMusic(LPCSTR name);
		
			//----------------------------------------------------------------------
			//ミュージックの取得
			//----------------------------------------------------------------------
			//@in : 音楽保存番号
			//@inout : 保存ポインタ
			//@out : true(成功) fale(失敗)
			__IMPOETER bool GetMusic(LPCSTR name,MyDirectX::BGMData* SEData);
		
			//----------------------------------------------------------------------
			///ミュージックは使っているか
			//----------------------------------------------------------------------	
			__IMPOETER bool IsMusic(LPCSTR name);
		
			//----------------------------------------------------------------------
			//ミュージックのプレイ
			//----------------------------------------------------------------------
			//@in : 音楽保存番号
			//@in : 0←鳴らし切り それ以外←ループ再生
			//@in : 0←最初から	それ以外←止めた場所から
			__IMPOETER void Play(LPCSTR name,int mode = 0,int pos = 0);
			
			//----------------------------------------------------------------------
			//ミュージックのエンド
			//----------------------------------------------------------------------
			//@in : 音楽保存番号
			__IMPOETER void Stop(LPCSTR name);

			//----------------------------------------------------------------------
			//ミュージックのチェック
			//----------------------------------------------------------------------
			///S_OK		→　false 鳴ってない
			///S_FALSE	→	true  鳴ってる
			__IMPOETER bool Check(LPCSTR name);
		
	};

	//--------------------------------------------------------
	//音楽再生工場クラス
	//<シングルトン>
	//音楽を管理するクラス
	//--------------------------------------------------------
	class MusicFactory{
		private:
		//********************************************************
			static MusicFactory* _music;	//シングルトンポインタ
			BGMFactory *_bgm;						//BGMポインタ
			SEFactory *_sound;				//効果音ポインタi
		//********************************************************
		private:
			//********************************************************
			//コピーガード＞＜
			__IMPOETER MusicFactory();
			__IMPOETER MusicFactory(const MusicFactory& text){}
			__IMPOETER MusicFactory& operator=(const MusicFactory& text){	return *this;	}
			__IMPOETER ~MusicFactory();

			//********************************************************
		public:
			//********************************************************
			//読み取り用
			__IMPOETER BGMFactory* GetBGM(){			return	_bgm;			}
			__IMPOETER SEFactory* GetMUSIC(){			return _sound;			}
			//********************************************************
			
			//********************************************************
			//インスタンス取得
			__IMPOETER static MusicFactory* getInstance(){
				if( _music == 0) _music = new MusicFactory();
				return  _music;
			}
			__IMPOETER static void deleteInstance(){
				delete _music;	_music = NULL;
			}
			//********************************************************
	};
}
#endif
