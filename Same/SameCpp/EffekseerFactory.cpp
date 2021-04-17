#pragma once
//--------------------------------------------------------------------------
///このプロジェクトは「effekseer」というツールで作った
///エフェクトを動画感覚で流している内面的なクラス
///effekseerの大部分の設定をここでしている。
///EffekseerManagerクラス(シングルトン)
//--------------------------------------------------------------------------
//インクルードやその他もろもろ～
//**************************************************************************
#include <EffekseerFactory.h>
#if _DEBUG
#pragma comment(lib, "Effekseer.Debug.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Debug.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Debug.lib" )
#else
#pragma comment(lib, "Effekseer.Release.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Release.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Release.lib" )
#endif


//static IXAudio2*							g_xa2 = NULL;
//static IXAudio2MasteringVoice*			g_xa2_master = NULL;
#pragma endregion
//**************************************************************************
namespace NanairoLib
{
	//インスタンス化
	NanairoLib::EffekseerClass* NanairoLib::EffekseerClass::efekseer;

	EffekseerClass::EffekseerClass()
	{
		this->InitXAudio();
	}

	EffekseerClass::~EffekseerClass()
	{
		this->Effektrelease();
		this->EffektDestory();
	}

	EffekseerClass* EffekseerClass::GetInstance()
	{
		if(efekseer == NULL)
			efekseer = new EffekseerClass();
		return efekseer;
	}

	void EffekseerClass::deleteInstance()
	{
		delete efekseer;
		efekseer = NULL;
	}

	//--------------------------------------------------------------------------
	//エフェクシアの初期化
	//--------------------------------------------------------------------------
	void EffekseerClass::InitXAudio()
	{
		// XAudio2の初期化を行う
		//XAudio2Create( &g_xa2 );

		//g_xa2->CreateMasteringVoice( &g_xa2_master );
	}

	//--------------------------------------------------------------------------
	//エフェクトの初期化
	//--------------------------------------------------------------------------
	//@in : directX用デバイス
	void EffekseerClass::EffektInit( PDirectDevice Device )
	{
		this->render = ::EffekseerRenderer::Renderer::Create(Device, 3000);			//描画用インスタンスの生成
		this->manager = ::Effekseer::Manager::Create(3000);							//エフェクト管理用インスタンスの生成
		this->manager->SetCoordinateSystem(::Effekseer::COORDINATE_SYSTEM_LH);		//左手系にチェンジ
		this->manager->SetSpriteRenderer(this->render->CreateSpriteRenderer());		//描画用インスタンスから描画機能を設定
		this->manager->SetRibbonRenderer(this->render->CreateRibbonRenderer());		//
		this->manager->SetRingRenderer(this->render->CreateRingRenderer());			//

		//描画用インスタンスからテクスチャの機能機能を設定
		//独自拡張可能、現在はファイルから読み込んでいる。
		this->manager->SetTextureLoader(this->render->CreateTextureLoader());

		//音再生用インスタンスの生成
		//g_sound = ::EffekseerSound::Sound::Create(g_xa2, 16, 16);

		//音再生用インスタンスから再生機能を指定
		//g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());

		//音再生用インスタンスからサウンドデータの読込機能を設定
		//独自拡張可能、現在はファイルから読み込んでいる。
		//g_manager->SetSoundLoader(g_sound->CreateSoundLoader());

		//投影行列を設定
		this->render->SetProjectionMatrix
			(
			::Effekseer::Matrix44().PerspectiveFovLH(GAKAKU,
			(float)(SCRW / SCRH), NEERDIS, TALLDIS)
			);
		this->effekMap.clear();
	}

	//--------------------------------------------------------------------------
	//アップデートの有無設定
	//--------------------------------------------------------------------------
	///@in : エフェクト再生中のハンドル
	///@in : 更新するか、否か
	void EffekseerClass::SetUpdateEnable(EffekHandle handle, bool isUpdate)
	{
		manager->SetPaused( handle, isUpdate );
	}

	//--------------------------------------------------------------------
	//描画の有無設定
	//--------------------------------------------------------------------
	//@in : エフェクト再生中のハンドル
	//@in : 描画するか、否か
	void EffekseerClass::SetDrawEnable(EffekHandle handle, bool isDraw)
	{
		manager->SetShown(handle, isDraw );
	}
	
	//----------------------------------------------------------
	//エフェクトの有無
	//----------------------------------------------------------
	///@in : エフェクト再生中のハンドル
	///@out : エフェクトが存在しているか
	bool EffekseerClass::IsEffektHandle(EffekHandle handling)
	{
		return this->manager->Exists( handling );
	}
	
	//---------------------------------------------------------
	//オブジェクトのデータを○○で変換
	//---------------------------------------------------------
	//@in : エフェクト再生中のハンドル 
	//@in : エフェクトの位置
	//@in : エフェクトの回転角度
	//@in : エフェクトの拡大率
	///</summary>
	void EffekseerClass::EffektUpdateVector(EffekHandle handle, PCVECTOR3 pos,PCVECTOR3 rota, PCVECTOR3 scale)
	{
		this->manager->SetRotation( handle, rota->x,rota->y,rota->z );
		this->manager->SetLocation( handle, Effekseer::Vector3D(pos->x,pos->y,pos->z ) );
		this->manager->SetScale( handle, scale->x, scale->y, scale->z );
	}
	
	//----------------------------------------------------------
	//行列で変換
	//----------------------------------------------------------
	//@in : エフェクト再生中のハンドル 
	//@in : エフェクトの位置
	//@in : エフェクトの回転角度
	//@in : エフェクトの拡大率
	void EffekseerClass::EffektUpdateMatrix(EffekHandle handle, PCVECTOR3 pos, PCVECTOR3 rota, PCVECTOR3 scale)
	{
		Effekseer::Matrix43 mat;
		Effekseer::Vector3D posi,scal;

		mat.RotationXYZ(rota->x,rota->y,rota->z);
		posi.X = pos->x;
		posi.Y = pos->y;
		posi.Z = pos->z;
		scal.X = scale->x;
		scal.Y = scale->y;
		scal.Z = scale->z;

		mat.SetSRT(scal, mat, posi);
		this->manager->SetMatrix(handle, mat);
	}

	//-----------------------------------------------------------
	//更新処理
	//-----------------------------------------------------------
	//@in : 更新速度
	///大抵は1.0fで充分
	void EffekseerClass::EffektUpdate(float updateSpd)
	{
		this->manager->Update( updateSpd );	//エフェクトの更新処理を行う
	}

	//----------------------------------------------------------
	//ビューの更新
	//----------------------------------------------------------
	//@in :  myカメラクラス
	void EffekseerClass::RenderUpdate(NanairoLib::CAMERA* camera)
	{
		const Vector3 *eye, *tar, *up;
		eye = (camera)->GetEYE();
		tar = (camera)->GetTARGET();
		up = (camera)->GetUP();

		//視点位置を確定
		//カメラ行列を設定
		this->render->SetCameraMatrix
			(
			::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(eye->x,eye->y,eye->z), 
												::Effekseer::Vector3D(tar->x,tar->y,tar->z), 
													::Effekseer::Vector3D(up->x,up->y,up->z))
			);
	}

	//----------------------------------------------------------
	//ビューの更新
	//----------------------------------------------------------
	//@in : 視点
	//@in : 注視点
	//@in : ↑方向
	void EffekseerClass::RenderUpdate(PCVECTOR3 eye, PCVECTOR3 tarGet, PCVECTOR3 up)
	{
		//視点位置を確定
		Effekseer::Vector3D eyes = ::Effekseer::Vector3D(eye->x,eye->y,eye->z);
		//カメラ行列を設定
		this->render->SetCameraMatrix
			(
			::Effekseer::Matrix44().LookAtLH( eyes, 
								::Effekseer::Vector3D(tarGet->x,tarGet->y,tarGet->z), 
								::Effekseer::Vector3D(up->x,up->y,up->z))
			);
	}
	
	//-----------------------------------
	//エフェクトの描画
	//-----------------------------------
	void EffekseerClass::EffektRender()
	{

		//エフェクトの描画開始処理を行う。
		this->render->BeginRendering();

		//エフェクトの描画を行う。
		this->manager->Draw();

		//エフェクトの描画終了処理を行う。
		this->render->EndRendering();
	}

	//-----------------------------------------
	//エフェクトの開始
	//-----------------------------------------
	//@in  : 保管してるエフェクトデータ番号
	//@in  : 最新位置
	//@out : エフェクトのハンドル
	Effekseer::Handle EffekseerClass::EffektPlay(LPCSTR name, PCVECTOR3 posi)
	{
		D3DXVECTOR3 worldpos = ( posi == NULL ? D3DXVECTOR3() : (*posi) );
		efkIte it = this->effekMap.find( name );
		return ( ( it != this->effekMap.end() ) ? manager->Play( (*it).second, worldpos.x, worldpos.y, worldpos.z ) : -1 );
	}

	//-----------------------------------------------
	//エフェクトの停止
	//-----------------------------------------------
	//@in : エフェクト再生中のハンドル 
	void EffekseerClass::EffektStop(EffekHandle handle)
	{
		// エフェクトの停止
		manager->StopEffect( handle );
	}

	//-----------------------------------
	//エフェクトのオール戻し
	//-----------------------------------
	void EffekseerClass::EffektAllstop()
	{
		manager->StopAllEffects();
	}
	
	//-----------------------------------------
	//エフェクトの廃棄
	//-----------------------------------------
	void EffekseerClass::Effektrelease()
	{
		// エフェクトの破棄
		efkIte it = this->effekMap.begin();
		while( it != this->effekMap.end() )
		{
			::Effekseer::Effect* efk = it->second;
			ES_SAFE_RELEASE( efk );
			it = this->effekMap.erase( it );
		}
	}
	
	//-------------------------------------
	//エフェクトクラスの破棄
	//-------------------------------------
	void EffekseerClass::EffektDestory()
	{
		this->manager->StopAllEffects();

		// 先にエフェクト管理用インスタンスを破棄
		this->manager->Destroy();

		// 次に音再生用インスタンスを破棄
		//g_sound->Destory();

		// 次に描画用インスタンスを破棄
		this->render->Destory();

		// XAudio2の解放
		/*if( g_xa2_master != NULL )
		{
			g_xa2_master->DestroyVoice();
			g_xa2_master = NULL;
		}*/
		//ES_SAFE_RELEASE( g_xa2 );
	}
	
	//--------------------------------------------------------------------
	//エフェクトの読み込み
	//--------------------------------------------------------------------
	//@in : パス
	//@in : 新しい名前
	void EffekseerClass::EffekLoader( ::LPCSTR filename, ::LPCSTR newname )
	{
		this->effekMap.insert( efkInput( newname, 
			( Effekseer::Effect::Create( this->manager, (const EFK_CHAR*)filename ) ) ) );
	}

}