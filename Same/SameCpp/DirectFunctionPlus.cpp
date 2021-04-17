#pragma once

//--------------------------------------------------------------------------
//
//ほぼ割り当て系のメソッド
//DirectXビューパイプラインに割り当てていきます
//
//--------------------------------------------------------------------------
#include <DirectFunctionPlus.h>

namespace NanairoLib
{
	//-----------------------------------------------------------
	//デコン
	//-----------------------------------------------------------
	inline Direct3DFunc::Direct3DFunc(const Direct3DFunc& func){}
	inline Direct3DFunc::Direct3DFunc(){}
	inline Direct3DFunc::~Direct3DFunc(){}

	//---------------------------------------------------------------
	//デフォルトプロジェクション行列設定
	//---------------------------------------------------------------
	//@in : DirectX用デバイス
	//@out : プロジェクション行列
	D3DXMATRIX Direct3DFunc::SetDefaultProjParam(IDirect3DDevice9* Device)
	{	
		return this->SetProjectionParam( Device, GAKAKUS, NEERDIS, TALLDIS );
	}

	//--------------------------------------------------------
	//ビューポート行列取得
	//--------------------------------------------------------
	//@in : DirectX用デバイス
	//@out : ビューポート行列
	D3DXMATRIX Direct3DFunc::SetViewPort(IDirect3DDevice9* Device)
	{
		D3DVIEWPORT9 vp;
		MyMatrix mat;
		Device->GetViewport(&vp);
		mat = mat.GetViewPort( vp.Width , vp.Height );
		return mat.ChangeMatrixD3D();
	}

	//----------------------------------------------------------------------------------------------------------------------
	//プロジェクション設定
	//----------------------------------------------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : 画角
	//@in : アスペクト比
	//@in : 前方クリッピング幅
	//@in : 後方クリッピング幅
	//@out : プロジェクション行列
	D3DXMATRIX Direct3DFunc::SetProjectionParam(IDirect3DDevice9* Device,float dangle,float camera_frontDis,float camera_backDis)
	{
		//奥行き間の設定
		D3DXMATRIX proj;
		::D3DXMatrixPerspectiveFovLH(&proj,	SET_PI( dangle ), SCRW / SCRH, camera_frontDis, camera_backDis );
		Device->SetTransform(D3DTS_PROJECTION, &proj);
		return proj;
	}

	//----------------------------------------------------------------
	//ライト設定
	//----------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : ライトクラス
	void Direct3DFunc::SetLightParam(IDirect3DDevice9 *Device,Light* light)
	{
		//ライトの設定
		//０番はデフォルト
		light->Setlighting(Device);
	}

	//---------------------------------------------------------------------------------------------------------------------
	//ビュー設定
	//---------------------------------------------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : 視点ベクトル
	//@in : 注視点ベクトル
	//@in : 上方向ベクトル
	//@in : true(ビュー設定あり) false(ビュー設定なし)
	//@out : ビュー行列
	D3DXMATRIX Direct3DFunc::SetCamera(IDirect3DDevice9* Device,RVector3 eye,RVector3 at,RVector3 up,bool isTransform)
	{
		D3DXMATRIX camera;
		::D3DXMatrixLookAtLH(&camera, &eye.SetD3DVector3(), &at.SetD3DVector3(), &up.SetD3DVector3() );
		if( !isTransform )	Device->SetTransform(D3DTS_VIEW, &camera);
		return camera;
	}

	//-----------------------------------------------------------------------------------------------------------------------------------
	//ワールド変換
	//-----------------------------------------------------------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : 位置ベクトル
	//@in : 回転ベクトル
	//@in : 拡縮ベクトル
	//@in : 0(変換付き) それ以外(変換なし)
	//@in : 0(回転変換あり) それ以外(回転変換なし)
	//@out : ワールド行列
	D3DXMATRIX Direct3DFunc::SetWorldPos(IDirect3DDevice9* Device, RCVector3 pos, RCVector3 rota, RCVector3 scale,int mode,int anglemode)
	{
		D3DXMATRIX mat1,mat2,mat3,mat4,mat5,world;
	
		//位置行列
		::D3DXMatrixTranslation(&mat1,pos.x, pos.y, pos.z);

		//角度行列
		if(anglemode == 0)
		{
			::D3DXMatrixRotationX(&mat2, SET_PI(rota.x));
			::D3DXMatrixRotationY(&mat3, rota.y);
			::D3DXMatrixRotationZ(&mat4, SET_PI(rota.z));
		}
	
		//拡大行列
		::D3DXMatrixScaling(&mat5,scale.x, scale.y, scale.z); 
	
		world = ( mat5 * mat2 * mat3 * mat4 * mat1 );
		if(mode == 0)	
			Device->SetTransform(D3DTS_WORLD,&world);
		return world;
	}

	//-----------------------------------------------------------------------------
	//ワールド変換（設定用）
	//-----------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : ワールド行列
	//@out : ワールド行列
	D3DXMATRIX Direct3DFunc::SetWorldPos(IDirect3DDevice9* Device,PCMATRIX world)
	{
		Device->SetTransform(D3DTS_WORLD,world);
		return *world;
	}

	//-----------------------------------------------------------------------------------------------------------------
	//ワールドクォータニオン変換
	//-----------------------------------------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : 位置ベクトル
	//@in : 任意軸ベクトル
	//@in : 回転角度
	//@in : 拡縮ベクトル
	//@out : ワールド行列
	D3DXMATRIX Direct3DFunc::SetWorldQuat(IDirect3DDevice9* Device, RCVector3 pos,RCVector3 rotavec,float ang,RCVector3 scale)
	{
		VectorFunc vec3;
		D3DXMATRIX mat = vec3.SetworldQuaternion(pos, scale, rotavec, ang);
		Device->SetTransform(D3DTS_WORLD,&mat);
		return mat;
	}

	//-----------------------------------------------------------------------------------------------------------------
	//ワールド座標からスクリーン座標に変換
	//-----------------------------------------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : ローカル座標
	//@in : ワールド行列
	//@in : ビュー行列
	//@in : プロジェクション行列
	//@in : ビューポート行列
	//@out : スクリーン座標
	D3DXVECTOR3 Direct3DFunc::ChanGetoScreen_world(IDirect3DDevice9* Device, RCVector3 pos, PCMATRIX wo, PCMATRIX vi, PCMATRIX pr, PCMATRIX vp)
	{
		D3DXVECTOR3 vec;
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(pos.x, pos.y, pos.z), &((*wo) * (*vi) * (*pr) * (*vp)));
		return vec;
	}

	//-----------------------------------------------------------------------------------------------------------------
	//スクリーン座標からワールド座標に変換
	//-----------------------------------------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : スクリーン座標
	//@in : ビュー行列
	//@in : プロジェクション行列
	//@in : ビューポート行列
	//@out : ワールド座標
	D3DXVECTOR3 Direct3DFunc::ChanGetoWorld_screen(IDirect3DDevice9* Device, RCVector3 pos, PCMATRIX vi, PCMATRIX pr, PCMATRIX vp)
	{
		D3DXVECTOR3 vec;
		D3DXVec3TransformCoord(&vec, &((Vector3&)pos).SetD3DVector3(), &((*::D3DXMatrixInverse(NULL, NULL, vi)) * (*::D3DXMatrixInverse(NULL, NULL, pr)) * (*::D3DXMatrixInverse(NULL, NULL, vp))));
		return vec;
	}

}