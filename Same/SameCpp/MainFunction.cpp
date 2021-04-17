#pragma once

//-------------------------------------------------------------
//
//DLLの中で保持したいデータなどをここに格納
//シングルトンで管理していくクラス
//
//-------------------------------------------------------------
#include <MainFunction.h>
#include <DirectFunctionPlus.h>
#include <DirectWindow.h>
#include <DirectCamera.h>


namespace NanairoLib
{
	//シングルトンなので、その中のポインタをインスタンス化
	MainFunction* MainFunction::MainFunc = 0;

	//----------------------------------------
	//コンストラクタ
	//----------------------------------------
	inline MainFunction::MainFunction()
	{
		DXData	= new NanairoLib::MYDXData();
		keys	= new NanairoLib::KEYS();
		custom	= new NanairoLib::Artisan();
	}
	
	//----------------------------------------
	//デストラクタ
	//----------------------------------------
	inline MainFunction::~MainFunction()
	{
		ES_SAFE_DELETE( DXData );
		ES_SAFE_DELETE( keys );
		ES_SAFE_DELETE( custom );
	}

	//----------------------------------------------------------------------------------------
	//ワールド座標からスクリーン座標に変換
	//----------------------------------------------------------------------------------------
	//@in : 位置ベクトル
	//@in : 回転ベクトル
	//@in : 拡縮ベクトル
	//@out : スクリーン座標
	D3DXVECTOR3 MainFunction::ChangeToScreen_world(RCVector3 pos,RCVector3 ang,RCVector3 sc)
	{
		Direct3DFunc func;
		//スクリーン座標へ変換
		return func.ChanGetoScreen_world(DXData->GetDevice(), pos, &func.SetWorldPos(DXData->GetDevice(),
										pos, ang, sc, 1), &this->viewMatrix, &this->projMatrix, &this->portMatrix);
	}
	
	//------------------------------------------------------------
	//スクリーン座標からワールド座標に変換
	//------------------------------------------------------------
	//@in : スクリーン座標
	//@out : ワールド座標
	D3DXVECTOR3 MainFunction::ChangeToWorld_screen(RCVector3 pos)
	{
		Direct3DFunc func;
		return func.ChanGetoWorld_screen(DXData->GetDevice(), pos, &this->viewMatrix, &this->projMatrix, &this->portMatrix);
	}
	
	//---------------------------------------------
	//DirectXの初期化
	//---------------------------------------------
	//@in : インスタンスハンドル
	//@out : true(成功) false(失敗)
	bool MainFunction::InitDirectX(HINSTANCE hInst)
	{
		NanairoLib::WinCreate win;

		if( FAILED( win.CreateClassAndWin( hInst, this->DXData->GetWindowT() ) ) )
			return false;

		this->DXData->SetDevice( win.InitDirect3D( this->DXData->Get3D9(),
			this->DXData->GetDevice(), this->DXData->GetWindow() ) );
		this->custom->SetDevice( this->DXData->GetDevice() );
		this->custom->SetVertexBuffer();
		
		return true;
	}

	//----------------------------------------------
	//デフォルト設定をまとめて
	//----------------------------------------------
	void MainFunction::SetDefaultMatrix()
	{
		NanairoLib::Direct3DFunc func;
		this->projMatrix = func.SetDefaultProjParam( this->DXData->GetDevice() );
		this->custom->SetProjection( &this->projMatrix );
		this->portMatrix = func.SetViewPort( this->DXData->GetDevice());

		this->SetDefaultLight();
		this->SetDefaultCamera();
	}

	//----------------------------------------------
	//ライトのデフォルト設定
	//----------------------------------------------
	void MainFunction::SetDefaultLight()
	{
		//デフォルトライトの設定
		NanairoLib::Light light = NanairoLib::Light( 0 );
		light.Setlighting( this->DXData->GetDevice() );

#ifdef SHADER_DRAWER		
		Shader* sh = this->custom->GetShader();
		if( sh != NULL )
		{
			sh->Effect->SetBool( SHADER_LIGHTING_ABLE_, true );
			sh->Effect->SetFloatArray( SHADER_LIGHT_DIR_, (float*)&light.GetLight()->Direction , 17 );
			sh->Effect->SetFloatArray( SHADER_LIGHT_DIR_DIFFUSE_, (float*)&light.GetLight()->Diffuse, 17 );
			sh->Effect->SetFloatArray( SHADER_LIGHT_DIR_AMBIENT_, (float*)&light.GetLight()->Ambient, 17 );
		}
#endif
	}

	//----------------------------------------------
	//デフォルトのカメラ設定
	//----------------------------------------------
	void MainFunction::SetDefaultCamera()
	{
		//通常のカメラの更新
		NanairoLib::CAMERA camera = NanairoLib::CAMERA(0);
		camera.CameraUpdate( this->DXData->GetDevice() );

#ifdef SHADER_DRAWER
		//シェーダカメラのセッティング
		Shader* sh = this->custom->GetShader();
		if( sh != NULL )
			sh->Effect->SetMatrix( SHADER_MATRIX_VIEW_, camera.GetViewMatrix() );
#endif
	}


}