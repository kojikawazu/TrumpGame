#pragma once
//-------------------------------------------------------------------------
//
//音楽情報を保持するファクトリー
//
//-------------------------------------------------------------------------
#include <MusicSound.h>
#include <DebugString.h>

namespace NanairoLib
{
	MusicFactory* MusicFactory::_music;

	#pragma region 音楽工場のコンストラクタ
	MusicFactory::MusicFactory()
	{
		this->_bgm = new BGMFactory();
		this->_sound = new SEFactory();
	}
	MusicFactory::~MusicFactory()
	{
		ES_SAFE_DELETE(this->_bgm);
		ES_SAFE_DELETE(this->_sound);
	}
	#pragma endregion

	#pragma region 効果音のコンストラクタ
	SEFactory::SEFactory()
	{
		this->_se.clear();
	}

	SEFactory::~SEFactory()
	{
		this->AllRelease();
	}
	#pragma endregion
	
	
	//----------------------------------------------------------------------
	//効果音のロード
	//----------------------------------------------------------------------
	//@in : ウィンドウハンドル
	void SEFactory::InitMusic(HWND hWnd)
	{
		BGMFunc func;
		this->_se.clear();

		this->Dsound8 = func.InitSound8(hWnd);
		this->soundBuffer = func.SetPrimary(this->Dsound8, hWnd);
	}

	//----------------------------------------------------------------------
	//効果音のロード
	//----------------------------------------------------------------------
	//@in : ファイル名
	//@in : 保存番号
	bool SEFactory::LoadMusic(LPCTSTR str,LPCSTR name)
	{
		OutPutStringFunction out;
		if( this->IsMusic( name ) )
		{
			out.SameOut_outputString( name );
			return false;
		}
		BGMFunc func;
		BGMData mc;
		mc.secondBuffer = func.LoadSoundMX( this->Dsound8,(LPSTR)str );
		
		if(mc.secondBuffer != NULL)
		{
			out.Success_outputString( str, name );
			mc.used = true;
			this->_se.insert( SEType( name, mc ) );
			return true;
		}
		else
		{
			out.Failed_outputString( str );
			return false;
		}
	}
	
	//----------------------------------------------------------------------
	//効果音のリリース
	//----------------------------------------------------------------------
	//@in : 保存名前
	void SEFactory::ReleaseMusic(LPCSTR name)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() )
		{
			if ( this->Check( it->first.c_str() ) )
				func.StopSound( it->second.secondBuffer );
			ES_SAFE_RELEASE( it->second.secondBuffer );
			it = this->_se.erase( it );
		}
	}

	void SEFactory::AllRelease()
	{
		BGMFunc func;
		SEIterator it = this->_se.begin();
		while( it != this->_se.end() )
		{
			if ( this->Check( it->first.c_str() ) )
				func.StopSound( it->second.secondBuffer );
			ES_SAFE_RELEASE( it->second.secondBuffer );
			it++;
		}
		this->_se.clear();
		func.ClearSound(this->Dsound8,this->soundBuffer);
	}

	//----------------------------------------------------------------------
	//ミュージックの取得
	//----------------------------------------------------------------------
	//@in : 音楽保存番号
	//@inout : 保存ポインタ
	//@out : true(成功) fale(失敗)
	bool SEFactory::GetMusic(LPCSTR name,NanairoLib::BGMData* SEData)
	{
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() )
		{
			SEData = &(it->second);
			return true;
		}
		return false;
	}
	
	//----------------------------------------------------------------------
	///ミュージックは使っているか
	//----------------------------------------------------------------------	
	bool SEFactory::IsMusic(LPCSTR name)
	{
		SEIterator it = this->_se.find( name ); 
		return ( it != this->_se.end() ? true : false);
	}
	
	//----------------------------------------------------------------------
	//ミュージックのプレイ
	//----------------------------------------------------------------------
	//@in : 音楽保存番号
	//@in : 0←鳴らし切り それ以外←ループ再生
	//@in : 0←最初から	それ以外←止めた場所から
	void SEFactory::Play(LPCSTR name,int mode,int pos)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() )// && !this->Check( name ) )
			func.PlaySound(it->second.secondBuffer, mode, pos);
	}
	
	//----------------------------------------------------------------------
	//ミュージックのエンド
	//----------------------------------------------------------------------
	//@in : 音楽保存番号
	void SEFactory::Stop(LPCSTR name)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() && this->Check( name ) )
			func.StopSound( it->second.secondBuffer);
	}

	//----------------------------------------------------------------------
	//ミュージックのチェック
	//----------------------------------------------------------------------
	///S_OK		→　false 鳴ってない
	///S_FALSE	→	true  鳴ってる
	bool SEFactory::Check(LPCSTR name)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		return (it != this->_se.end() && func.CheckSound( it->second.secondBuffer ) != S_OK );
	}
	
	//-----------------------------------------------------------------------------------
	/////////////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------

	//----------------------------------------------------------------------
	//BGMコンストラクタ
	//----------------------------------------------------------------------
	BGMFactory::BGMFactory()
	{
		this->_bgm.clear();
		this->OnSound();
	}
	
	//----------------------------------------------------------------------
	//デストラクタ
	//----------------------------------------------------------------------
	BGMFactory::~BGMFactory()
	{
		this->AllRelease();
	}

	//----------------------------------------------------------------------
	//音楽をリリース
	//----------------------------------------------------------------------
	//@in : 保存名前
	void BGMFactory::ReleaseMusic(LPCSTR name)
	{
		BGMIterator it = this->_bgm.find( name );

		SEFunc func;
		while( it != this->_bgm.end() )
		{
			this->Stop( (*it).first.c_str() );
			func.ReleaseMusic( (*it).first.c_str() );	
			this->_bgm.erase( it );
		}
	}

	//----------------------------------------------------------------------
	//すべてリリース
	//----------------------------------------------------------------------
	void BGMFactory::AllRelease()
	{
		BGMIterator it = this->_bgm.begin();

		SEFunc func;
		while( it != this->_bgm.end() )
		{
			LPCSTR name = (*it).first.c_str();
			if( this->Check( name ) )
				this->Stop( name );
			func.ReleaseMusic( name );	
			it++;
		}
		this->_bgm.clear();
	}

	//----------------------------------------------------------------------
	//存在しているか
	//----------------------------------------------------------------------
	//@in : 保存名前
	//@out : true(存在中) false(存在していない)
	bool BGMFactory::IsMusic(LPCSTR name)
	{
		return !( this->_bgm.find( name ) != this->_bgm.end() );
	}

	//----------------------------------------------------------------------
	//ミュージックの取得
	//----------------------------------------------------------------------
	//@in : 保存名前
	//@inout : 取得するポインタ
	//@out : true(成功) false(失敗)
	bool BGMFactory::GetMusic(LPCSTR name,const SEData* bgm)
	{
		BGMIterator it = this->_bgm.find( name );
		if( it != this->_bgm.end() )
		{
			bgm = &(*it).second;
			return true;
		}
		return false;
	}
	
	//----------------------------------------------------------------------
	//音楽をロード
	//----------------------------------------------------------------------
	//@in : ファイルパス
	//@in : 保存名前
	//@out : true(成功) false(失敗)
	bool BGMFactory::LoadMusic(LPCTSTR str,LPCTSTR name)
	{
		OutPutStringFunction out;
		if( !IsMusic( name ) )
		{
			out.SameOut_outputString( name );
			return false;	
		}
		SEData bgm;
		if( ( bgm = SEData( str, name ) ).used )
		{
			out.Success_outputString( str, name );
			this->_bgm.insert( BGMType( name, SEData( str, name ) ) );
			return true;
		}
		else
		{
			out.Failed_outputString( str );
			return false;
		}
	}
	
	//----------------------------------------------------------------------
	//プレイ
	//----------------------------------------------------------------------
	//@in : 保存名前
	void  BGMFactory::Play(LPCSTR name)
	{
		if( !this->IsSound() )	return ;

		SEFunc func;
		BGMIterator it = this->_bgm.find( name );
		//使ってて、鳴っていなかったら
		if( it != this->_bgm.end() && this->Check( name ) )
			func.PlayMusic( it->second.bgmName );
	}

	//----------------------------------------------------------------------
	//ストップ
	//----------------------------------------------------------------------
	//@in : 保存名前
	void  BGMFactory::Stop(LPCSTR name)
	{
		SEFunc func;
		BGMIterator it = this->_bgm.find( name );
		//使ってて、鳴っていなかったら
		if( it != this->_bgm.end() && !this->Check( name ) )
			func.StopMusic( it->second.bgmName );
	}

	//----------------------------------------------------------------------
	//チェック
	//----------------------------------------------------------------------
	//@in : 保存名前
	///stopped	→　false 鳴ってない
	///noStop	→	true  鳴ってる
	bool  BGMFactory::Check(LPCSTR name)
	{
		SEFunc func;
		BGMIterator it = this->_bgm.find( name );
		return ( it != this->_bgm.end() && func.CheckMusic( it->second.bgmName ) );
	}
	
}