#ifndef NanairoLib_EFFEKCLASS_H
#define NanairoLib_EFFEKCLASS_H

//-------------------------------------------------------------------------------------
//エフェクシアを導入
//エフェクシアマネージャー
//-------------------------------------------------------------------------------------

#pragma region インクルード

#ifndef	__EFFEKSEER_BASE_PRE_H__
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef NanairoLib_CAMERA_H
#include <DirectCamera.h>
#endif

#pragma endregion

namespace NanairoLib
{

#pragma region 名前変更
	//-------------------------------------------------------------------------------------
	//名前変更
	//-------------------------------------------------------------------------------------
	typedef Effekseer::Effect*										PEffekt;
	typedef EffekseerRenderer::Renderer*							PEffektRenderer;
	typedef Effekseer::Manager*										PEffektManager;
	typedef Effekseer::Handle										EffekHandle;
	typedef std::map<std::string, Effekseer::Effect*>				efkMap;
	typedef std::map<std::string, Effekseer::Effect*>::iterator		efkIte;
	typedef std::map<std::string, Effekseer::Effect*>::value_type	efkInput;
#pragma endregion

	//-------------------------------------------------------------------------------------
	//エフェクシアクラス(EffekseerManagerClass)
	//シングルトンクラス
	//-------------------------------------------------------------------------------------
	class EffekseerClass
	{
		private:
		//**************************************************************
			static EffekseerClass*			efekseer;				//シングルトンポインタ
			efkMap							effekMap;				//エフェクトマップ
			PEffektRenderer					render;					//エフェクトドロークラス
			PEffektManager					manager;				//エフェクト管理クラス
		
		//**************************************************************
		private:
		//ここは基本的に扱えない
		//**************************************************************
			
			//------------------------------------------------------------------------------------
			//コピーガード
			//------------------------------------------------------------------------------------
			__IMPOETER EffekseerClass();
			__IMPOETER EffekseerClass(const EffekseerClass& cl);
			__IMPOETER EffekseerClass& operator = (const EffekseerClass& cl){	return (*this);	}
			__IMPOETER ~EffekseerClass();

			//--------------------------------
			//初期時に一度だけ実行
			//--------------------------------
			__IMPOETER void InitXAudio();	
			__IMPOETER void EffektLoad();

			//--------------------------------
			//破棄時に一度だけ実行
			//--------------------------------
			__IMPOETER void EffektDestory();
			__IMPOETER void Effektrelease();
	
		//**************************************************************
		public:
			//---------------------------------------------------
			//シングルトン用メソッド
			//---------------------------------------------------
			__IMPOETER static EffekseerClass* GetInstance();
			__IMPOETER static void deleteInstance();
			__IMPOETER PEffektManager GetManager() const{	return manager;	}

		public:
			//**************************************************************
			//再生されているエフェクトの処理の有無を設定する。
			//画面とめたり、見えなくしたりとそういう時に使用。

			//--------------------------------------
			//更新の有無設定
			//--------------------------------------
			//@エフェクトを再生中のハンドル
			//@更新の有無
			__IMPOETER void SetUpdateEnable(EffekHandle handle, bool isUpdate = true);
	
			//--------------------------------------
			//描画の有無設定
			//--------------------------------------
			//@エフェクトを再生中のハンドル
			//@更新の有無
			__IMPOETER void SetDrawEnable(EffekHandle handle, bool isDraw = true);

			//**************************************************************
			//その再生されているエフェクトの位置・拡大率・角度の変更を更新
			//そして、ビュー更新
			//すべて変更されたときに更新すればＯＫ！

			//-----------------------------------------
			//エフェクトのベクトル型更新
			//-----------------------------------------
			//@エフェクトを再生しているハンドル
			//@エフェクトの最新位置
			//@エフェクトの最新角度
			//@エフェクトの最新拡縮
			__IMPOETER void EffektUpdateVector(EffekHandle handle, PCVECTOR3 pos, PCVECTOR3 rota, PCVECTOR3 scale);
	
			//--------------------------------------
			//エフェクトの行列型更新
			//--------------------------------------
			//@エフェクトを再生しているハンドル
			//@エフェクトの最新位置
			//@エフェクトの最新角度
			//@エフェクトの最新拡縮
			__IMPOETER void EffektUpdateMatrix(EffekHandle handle, PCVECTOR3 pos, PCVECTOR3 rota, PCVECTOR3 scale);
	
			//------------------------------------------
			//カメラクラスでビュー更新
			//------------------------------------------
			__IMPOETER void RenderUpdate(PCAMERA camera);
	
			//------------------------------------------
			//直接代入ビュー更新
			//------------------------------------------
			//@更新する視点
			//@更新する注視点
			//@更新する↑方向
			__IMPOETER void RenderUpdate(PCVECTOR3 eye, PCVECTOR3 tarGet, PCVECTOR3 up);
	
			//**************************************************************
			//（一サイクルに一度の処理）

			//--------------------------------
			//エフェクトのオール描画
			//--------------------------------
			__IMPOETER void EffektRender();

			//--------------------------------
			//エフェクトの更新
			//--------------------------------
			//@in : 更新するテンポ
			__IMPOETER void EffektUpdate(float updateSpd = 1.0f);
	
			//**************************************************************
			//エフェクトを再生したらハンドルが手に入り、
			//そのハンドルを操作する。
			//再生中だとハンドルは存在していて、再生終わるとそのハンドルは使えなくなる。

			//---------------------------------------------------------------
			//エフェクトの再生
			//---------------------------------------------------------------
			//@in	: 再生したい名前(ロードした名前を入れてください
			//@in	: 再生する位置（基本的に原点）
			//@out	: エフェクトを制御するハンドル
			__IMPOETER Effekseer::Handle EffektPlay( LPCSTR name, PCVECTOR3 posi = NULL );
	
			//-------------------------------------------------
			//エフェクトの停止
			//-------------------------------------------------
			//@in : 停止したいエフェクトハンドル
			__IMPOETER void EffektStop(EffekHandle handle);

			//------------------------------------------------------------
			//エフェクトのそのハンドルはまだ顕在か？、再生されているか？
			//------------------------------------------------------------
			//@in : チェックしたいエフェクトハンドル
			//out : true(再生中) false(再生していない)
			__IMPOETER bool IsEffektHandle(EffekHandle handling);
	
			//-------------------------------
			//エフェクトのオールストップ
			//-------------------------------
			__IMPOETER void EffektAllstop();

			//------------------------------------------------
			//始めの初期化
			//------------------------------------------------
			//@in : directX用デバイス
			__IMPOETER void EffektInit(PDirectDevice Device);

			//------------------------------------------------
			//エフェクトのロード
			//------------------------------------------------
			//@in : ロードしたいパス
			//@in : 新しい名前を付ける
			__IMPOETER void EffekLoader(::LPCSTR filename, ::LPCSTR newname);
			//**************************************************************
	};

	#define Effek EffekseerClass::GetInstance()->

	//-----------------------------------------------------------------
	//使用例
	//-----------------------------------------------------------------
	//※必ずしなきゃならないこと
	//まずはこのシングルトンの初期化っ
	//Effek effectInit( DirectX用デバイス );
	//
	//全体エフェクトの更新
	//Effek effectUpdate( 再生スピード 基準は1ミリs );
	//
	//全体エフェクトの描画
	//Effek effectRender();
	//-----------------------------------------------------------------

	//エフェクト(.efk)ファイルをロード
	//Effek effekLoader( ファイルパス , 新しい名前を付ける );
	//
	//読み込んだエフェクトを再生
	//（戻り値）ハンドル = Effek effectPlay( つけた名前 , 再生したいポジション );
	//
	//再生したエフェクトのポジションやアングル、スケールを変更
	//Effek effectUpdateVector( 再生したハンドル, ポジション、アングル、スケール );
	//
	//カメラの更新
	//Effek renderUpdate( 再生したハンドル, 視点, 注視点, 上方向 );
	//
	//再生しているかチェック
	//Effek isEffectHandle(　再生したハンドル ) ? 再生している : 再生終了
	//
	//エフェクトの停止（一時停止じゃない）
	//Effek effectStop();
	//-----------------------------------------------------------------
}

#endif