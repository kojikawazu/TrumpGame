#pragma once
//--------------------------------------
//BGMを扱うクラス
//--------------------------------------
#pragma region インクルード
#include <MusicSound.h>

#include <dsound.h>
#include <MMSystem.h>

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")
#pragma endregion

namespace NanairoLib
{
	//---------------------------------------------------------
	//デコン
	//---------------------------------------------------------
	inline BGMFunc::BGMFunc(){}
	inline BGMFunc::~BGMFunc(){}

	//---------------------------------------------------------
	//このクラスを使うときに初期化する関数
	//---------------------------------------------------------
	//@in : ウィンドウハンドル
	//@out : サウンドインターフェイス
	#pragma region 音楽の初期化
	 IDirectSound8* BGMFunc::InitSound8(HWND hWnd)
	 {
		IDirectSound8 *sound;
		 //IDirectSound8オブジェクトのポインタを取得
		::DirectSoundCreate8(
			NULL,		//GUIDによるデバイス指定。NULLでデフォルトデバイスを指定
			&sound,	//Directサウンドオブジェクトを受け取るポインタのアドレス
			NULL		//予約領域。常にNULL
			);
		if(sound == NULL)	
			return sound;

		sound->SetCooperativeLevel(
			hWnd,			//音を鳴らすウィンドウを指定
			DSSCL_NORMAL	//ハードウェア占有レベル。ほとんど占有しない設定
			);

		//これで出力の設定をデフォルト（8bits,22KHz,ｽﾃﾚｵ）
		return sound;
	}

	IDirectSoundBuffer* BGMFunc::SetPrimary(IDirectSound8 *Dsound8,HWND hWnd){
		IDirectSoundBuffer* sound;
		DSBUFFERDESC Desc;	//バッファ
		::memset(&Desc,0,sizeof(Desc));
		Desc.dwSize = sizeof(Desc);
		Desc.dwFlags = DSBCAPS_PRIMARYBUFFER;	//プライマリバッファ
		//後は晩やボリュームのコントロールが必要なときにフラグを設定する。

		Dsound8->CreateSoundBuffer(
			&Desc,			//DSBUFFERDESC型の変数
			&sound,	//IDirectSoundBufferオブジェクトを受け取るポインタアドレス
			NULL);			//予約。常にNULL	

		WAVEFORMATEX waveM;	//出力フォーマット
		::memset(&waveM,0,sizeof(waveM));
		waveM.cbSize			= sizeof(waveM);
		waveM.wFormatTag		= WAVE_FORMAT_PCM;	//波形フォーマットの指定。無圧縮の生波形
		waveM.nChannels			= DSSCL_NORMAL;	//出力チャンネル数の指定。２（ｽﾃﾚｵ）で固定
		waveM.nSamplesPerSec	= DSSCL_NORMAL;	//サンプリングレートの指定。22050(22KHz)で固定
		waveM.wBitsPerSample	= DSSCL_NORMAL;	//量子化レベルの指定。8ビット（256段階）で固定
	
		//ブロックサイズ。量子化（byte単位）* チャンネル数で指定
		waveM.nBlockAlign		= (waveM.wBitsPerSample >> 3) * waveM.nChannels;
		//１秒間のブロックサイズ。ブロックサイズ * サンプリングレートで指定。
		waveM.nAvgBytesPerSec	= waveM.cbSize * waveM.nSamplesPerSec;
	
		//フォーマット指定
		sound->SetFormat(&waveM);

		return sound;
	}
	#pragma endregion

	//------------------------------------------------------------------------------------
	//音楽のリリース
	//------------------------------------------------------------------------------------
	//@in : サウンド制御インターフェイス
	//@in : サウンドバッファ
	//@out : 成功 失敗
	HRESULT BGMFunc::ClearSound(IDirectSound8 *Dsound8,IDirectSoundBuffer *soundBuffer)
	{
		ES_SAFE_RELEASE( soundBuffer );
		ES_SAFE_RELEASE( Dsound8 );
		return S_OK;
	}
	
	//-------------------------------------------------------------------------------
	//音楽のロード
	//-------------------------------------------------------------------------------
	//@in : サウンドインターフェイス
	//@in : ファイルパス
	//@out : サウンドバッファ
	IDirectSoundBuffer* BGMFunc::LoadSoundMX(IDirectSound8 *Dsound8,LPSTR fileName)
	{
		IDirectSoundBuffer *secondBuffer = NULL;
		//waveファイルの読み込み
		HMMIO mio = ::mmioOpenA(
			fileName,	//読み込みWAVファイル名
			NULL,		//追加パラメータ設定。NULLで
			MMIO_ALLOCBUF | MMIO_READ);
		//MMIO_READ - ファイルを読み込みモードで開く
		//MMIO_ALLOCBUF - ファイルIOバッファを自動で作成する
		if(mio == NULL)	
			return NULL;

		//WAVファイルのフォーマット部分を探索し読み込む
		MMCKINFO info;
		::mmioDescend(
			mio,	//オープンしたファイルのハンドル
			&info,	//チャンク情報の入出力先
			NULL,	//親チャンク情報
			0);		//検索フラグ
		//探索フラグ① : 0 最初に見つけたチャンク
		//② : MMIO_FINDCHUNK lpck内に検索チャンク情報がある。
		if(info.ckid != FOURCC_RIFF || info.fccType != mmioFOURCC('W','A','V','E'))
			goto LOAD_SE_EXIT;

		MMCKINFO check;
		//フォーマット部分に↓が入っているので、ここかどうか調べる
		check.ckid = mmioFOURCC('f','m','t',' ');
		int err = ::mmioDescend(mio,&check,&info,MMIO_FINDCHUNK);
		if(err != 0)	
			goto LOAD_SE_EXIT;
		if(check.cksize < (long)sizeof(PCMWAVEFORMAT))	
			goto LOAD_SE_EXIT;
	
		//フォーマット部分の読み込み
		WAVEFORMATEX w; 
		::memset(&w,0,sizeof(w));
		//データの読み込み
		::mmioRead(
			mio,			//読み取るファイルのファイルハンドル
			(char*)&w,		//ファイルから読み取られたデータが入るバッファのアドレス
			check.cksize);	//ファイルから読み取るバイト数
		::mmioAscend(mio,&check,0);

		//データ部分まで進み、音声データ部分を格納
		check.ckid = mmioFOURCC('d','a','t','a');
		::mmioDescend(mio,&check,&info,MMIO_FINDCHUNK);

		//データ格納先バッファを作成
		DSBUFFERDESC desk;
		::memset(&desk,0,sizeof(desk));
		desk.dwSize			= sizeof(desk);
		desk.dwFlags		= DSBCAPS_GETCURRENTPOSITION2;	//エミュレーション時により正確な再生カーソルを取得
		desk.dwBufferBytes	= check.cksize;
		desk.lpwfxFormat	= &w;

		Dsound8->CreateSoundBuffer(
			&desk,			//バッファの設定
			&secondBuffer,	//セカンダリバッファにアドレスを指定
			NULL);			//予約
		if(secondBuffer == NULL)	
			goto LOAD_SE_EXIT;

		//WAVのデータを作成したバッファに読み込む
		void *p;	//ロックされたバッファのポインタ格納先
		DWORD size;	//ロックされた部分のサイズ
		secondBuffer->Lock(
			0,					//ロック開始位置
			desk.dwBufferBytes,	//ロックサイズを指定
			&p,					//最初にロックされた部分へのポインタを受け取る
			&size,				//サイズを受け取る
			NULL,				//第②ロック、NULL
			NULL,				//第②サイズ、NULL
			0);					//ロックイベントを変更するフラグ、０

		//ロック先のアドレスにデータを読み込む
		::mmioRead(mio,(HPSTR)p,check.cksize);

		//アンロック
		secondBuffer->Unlock(&p,size,NULL,NULL);

	//エラーもしくは成功したら必ずここを通って閉じる。
	LOAD_SE_EXIT:
		::mmioClose(mio,0);
		return secondBuffer;
	}

	//-------------------------------------------------------------------------
	//音楽の再生
	//-------------------------------------------------------------------------
	//@in : サウンドバッファ
	//@in : 0(ループなし) それ以外(ループ)
	//@in : 0(最初に戻す) それ以外（途中から）
	//@out : 成功 失敗
	HRESULT BGMFunc::PlaySound(IDirectSoundBuffer *buffer,int mode,int posi)
	{
		//鳴らし切り//ループ再生
		DWORD flag = ((mode == 0) ? 0 : DSBPLAY_LOOPING);

		if(posi == 0)	
			this->ChangeBuffer(buffer,0);

		HRESULT check = buffer->Play(
			0,		//予約済み
			0,		//サウンドの優先度
			flag);	//バッファの再生方法
		return check;
	}
	
	//-------------------------------------------------------------
	//音楽の停止
	//-------------------------------------------------------------
	//@in : サウンドバッファ
	//out : 成功 失敗
	inline HRESULT BGMFunc::StopSound(IDirectSoundBuffer *buffer)
	{
		return buffer->Stop();
	}
	
	//---------------------------------------------------------------------------
	//バッファのチェック
	//---------------------------------------------------------------------------
	//@in : サウンドバッファ
	//@in : 再生したい位置
	//@out : 成功 失敗
	inline HRESULT BGMFunc::ChangeBuffer(IDirectSoundBuffer *buffer,DWORD posi)
	{
		return (*buffer).SetCurrentPosition(posi);
	}
	
	//---------------------------------------------------------------
	//音楽が再生されているか
	//---------------------------------------------------------------
	//@in : サウンドバッファ
	//@out : 再生している 再生していない
	inline HRESULT BGMFunc::CheckSound(IDirectSoundBuffer *buffer)
	{
		ULONG status;
		buffer->GetStatus(&status);
		return ((DSBSTATUS_PLAYING & status) != 0);
	}
	
	#pragma region コンストラクタ
	inline BGMData::BGMData(){}
	inline BGMData::~BGMData(){}

	BGMData::BGMData(IDirectSound8 *Dsound8,LPSTR fileName) : used(true) , playFlag(false)
	{
		BGMFunc mm;
		this->secondBuffer = mm.LoadSoundMX(Dsound8,fileName);
		this->used = true;
		this->playFlag = false;
	}
	#pragma endregion

}