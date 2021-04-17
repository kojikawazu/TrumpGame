#pragma once

//------------------------------------------------------------------------------
//
//テクスチャやモデルのロード関数をここに格納
//
//------------------------------------------------------------------------------
#include <ResourceFunction.h>
#include <tchar.h>

namespace NanairoLib
{
	inline TextFunc::TextFunc(){}

	inline TextFunc::~TextFunc(){}

	//-----------------------------------
	//頂点から法線に
	//-----------------------------------
	//@in : モデル詳細データクラス
	void GetNomalLine(PATACKH atack)
	{
		VectorFunc vec3D;
		Vector3 vecA,vecB,normal;

		for(DWORD i=0; i<atack->meshSum; i++)
		{
			vecA.SetVector( atack->meshVertex[atack->meshIndex[(int)i][1]] - atack->meshVertex[atack->meshIndex[(int)i][0]] );
			vecB.SetVector( atack->meshVertex[atack->meshIndex[(int)i][2]] - atack->meshVertex[atack->meshIndex[(int)i][0]] );
			normal = vec3D.GetNormal(vec3D.GetCloss(vecA, vecB));

			atack->meshNormal[(int)i] = normal.SetD3DVector3();
		}
	}
	
	//***************************************************************************************************************************
	//テクスチャクラスの関数群

	//--------------------------------------------
	//テクスチャのロード
	//画像をテクスチャとして読み込む
	//--------------------------------------------
	//@in : DirectXのデバイス
	//@inout : テクスチャの構造体
	//@in : ファイル名
	//@in : 画像の幅
	//@in : 画像の高さ
	//@in : (分割するとき)画像の横に並ぶ数
	//@in : (分割するとき)画像の縦に並ぶ数
	//@out : 失敗すると(-1) 成功すると(1)
	int TextFunc::LoadGraphIndex(PDirectDevice Device,PTEXTUREH text,LPCSTR fileName,int width,int height,int sumW,int sumH)
	{
		if(FAILED(::D3DXCreateTextureFromFileA(Device,fileName,&text->graph)))	
			return -1;
		//↓成功してる
		//画像の読み込むに成功するとこちらに
		//テクスチャ構造体にデータを保存
		//そして、使用中に切り替え
		text->used = true;	
		text->width = width;
		text->height = height;
		return 1;
	}
	
	//--------------------------------------------
	//画像を非同期読み込みする
	//--------------------------------------------
	//@in : DirectXのデバイス
	//@inout : テクスチャの構造体
	//@in : 読み込む開始位置
	//@in : 読み込むサイズ
	//@out : 失敗(-1) 成功(1)
	int TextFunc::LoadGraphIndexASYN(PDirectDevice Device,PTEXTUREH text,LPCSTR point,int size)
	{
		if(FAILED(::D3DXCreateTextureFromFileInMemory(Device,point,size,&text->graph)))
		{
			text->used = false;
			return -1;
		}
		return 1;
	}

	//--------------------------------------------
	//モデルのロード
	//--------------------------------------------
	//@in : DirectX用デバイス
	//@in : ファイル名
	//@out : モデル保存クラス
	//@in : 保存番号
	//@out : true(成功) false(失敗)
	bool TextFunc::LoadModel3D(PDirectDevice Device,LPCSTR fileName,PMODELH model,int mode)
	{
		ID3DXBuffer *pMatel;
		//Xファイルからモデルデータロード
		//マテリアル数、メッシュゲッツ！
		if(FAILED(
			::D3DXLoadMeshFromXA(
				fileName,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,(DWORD*)&model->matelSum,&model->mesh)))
				return false;

		int num = model->matelSum;
		//データ受け取りバッファ作成
		model->matel = new D3DMATERIAL9[num];
		model->textureX = new IDirect3DTexture9*[num];
	
		//マテリアルのコピー
		D3DXMATERIAL* org = (D3DXMATERIAL*)pMatel->GetBufferPointer();
		for(int i=0;i<num;i++)
		{
			model->matel[i] = org[i].MatD3D;
			if(mode == 0)	model->matel[i].Ambient = model->matel[i].Diffuse;
			//アンビエントとデフューズは一緒
			model->textureX[i] = NULL;
			if(org[i].pTextureFilename != NULL)
				::D3DXCreateTextureFromFileA(Device,org[i].pTextureFilename,&model->textureX[i]);
		}

		pMatel->Release();
		model->used = true;
		return true;
	}
	
	//--------------------------------------------
	//非同期用モデルのロード
	//--------------------------------------------
	//@in: DirectX用デバイス
	//@in : アドレスポインタ
	//@in : データサイズ
	//@inout : モデルデータ
	//@in : ウィンドウクラス
	//@in : 0(アンビエント = ディフューズ)
	//@out : 1(成功) -1(失敗)
	int TextFunc::LoadModel3DASYN(PDirectDevice Device,LPCSTR point,int size,PMODELH model,HWND wnd,int mode)
	{
		ID3DXBuffer *pMatel;
		//メモリからモデルをロード
		//マテリアル数、メッシュを取り出す
		if(FAILED(
			::D3DXLoadMeshFromXInMemory(
				point,size,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,(DWORD*)&model->matelSum,&model->mesh)))
		{
				::MessageBoxA(wnd,_T("ファイル読み込み失敗"),_T("error"),MB_OK);
				return -1;
		}

		int num = model->matelSum;
		//データ受け取りバッファ作成
		model->matel = new D3DMATERIAL9[num];
		model->textureX = new IDirect3DTexture9*[num];
	
		//マテリアルのコピー
		D3DXMATERIAL* org = (D3DXMATERIAL*)pMatel->GetBufferPointer();
		for(int i=0;i<num;i++)
		{
			model->matel[i] = org[i].MatD3D;
			if(mode == 0)	model->matel[i].Ambient = model->matel[i].Diffuse;
			//アンビエントとデフューズは一緒
			model->textureX[i] = NULL;
			if(org[i].pTextureFilename != NULL)
				::D3DXCreateTextureFromFileA(Device,org[i].pTextureFilename,&model->textureX[i]);
		}

		pMatel->Release();
		model->used = true;
		return 1;
	}

	//--------------------------------------------
	//当たり判定用モデルのロード
	//--------------------------------------------
	//@in : DirectX用デバイス
	//@in : ファイルパス
	//@input : あたり判定用モデルデータクラス
	//@out : true(成功) false(失敗)
	bool TextFunc::LoadModelAtack(PDirectDevice Device,LPCSTR fileName,PATACKH atack)
	{
		ID3DXBuffer *pMatel;
		ID3DXMesh *mesh;
		if(FAILED(
			::D3DXLoadMeshFromXA(
				fileName,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,NULL,&mesh)))
		{		
			return false;
		}
		pMatel->Release();

		//頂点バッファの取得
		BYTE* pVertex;
		BYTE* pIndex;
		//ロックをかけて取得
		if(FAILED(mesh->LockVertexBuffer(D3DLOCK_READONLY,(void**) &pVertex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD,(void**) &pVertex)))		
				return false;
		}
		if(FAILED(mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**) &pIndex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD, (void**) &pIndex)))
			{
				mesh->UnlockVertexBuffer();
				return false;
			}
		}

		atack->vertexSum	= mesh->GetNumVertices();			//頂点の数
		atack->meshSum		= mesh->GetNumFaces();				//面の数	
		DWORD FVF			= mesh->GetFVF();					//頂点フォーマットを取得する。
		DWORD vertexSize	= D3DXGetFVFVertexSize( FVF );		// 頂点のサイズを取得する。
		for( DWORD i = 0; i < atack->vertexSum; i++ )
		{
			atack->meshVertex[(int)i] = *(D3DXVECTOR3*)pVertex;	// 頂点座標を取得する。
			pVertex += vertexSize;									// 次の頂点にポインタを移動する。
		}

		for( DWORD i = 0; i < atack->meshSum; i++ )
		{
			//int型 : size 2 ずつ進むだろう
			atack->meshIndex[(int)i][0] = *(pIndex);	// 頂点座標を取得する。
			atack->meshIndex[(int)i][1] = *(pIndex + 2);
			atack->meshIndex[(int)i][2] = *(pIndex + 4);
			pIndex += 6;									// 次の頂点にポインタを移動する。
		}
	
		//アンロック
		mesh->UnlockVertexBuffer();
		mesh->UnlockIndexBuffer();

		NanairoLib::GetNomalLine(atack);
		mesh->Release();
		atack->used = true;
		return true;
	}

	//--------------------------------------------
	//非同期用当たり判定のロード
	//--------------------------------------------
	//@in : DirectX用デバイス
	//@in : ファイルパス
	//@in : サイズ
	//@out : あたり判定用データクラス
	//@in : ウィンドウクラス
	//@out : 1(成功) -1(失敗)
	int TextFunc::LoadModelAtackASYN(PDirectDevice Device,LPCSTR point,int size,PATACKH atack,HWND wnd)
	{
		ID3DXBuffer *pMatel;
		ID3DXMesh *mesh;
		if(FAILED(
			::D3DXLoadMeshFromXInMemory(
				point,size,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,(DWORD*)NULL,&mesh)))
		{
				::MessageBoxA(wnd,_T("ファイル読み込み失敗"),_T("error"),MB_OK);
				return E_FAIL;
		}
		pMatel->Release();

		//頂点バッファの取得
		BYTE* pVertex;
		BYTE* pIndex;
		//ロックをかけて取得
		if(FAILED(mesh->LockVertexBuffer(D3DLOCK_READONLY,(void**) &pVertex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD,(void**) &pVertex)))
			{
				::MessageBoxA(wnd,_T("メッシュ読み込み失敗"),_T("error"),MB_OK);
				return -1;
			}
		}
		if(FAILED(mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**) &pIndex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD, (void**) &pIndex)))
			{
				mesh->UnlockVertexBuffer();
				::MessageBoxA(wnd,_T("メッシュ読み込み失敗"),_T("error"),MB_OK);
				return -1;
			}
		}

		atack->vertexSum	= mesh->GetNumVertices();			//頂点の数
		atack->meshSum		= mesh->GetNumFaces();				//面の数	
		DWORD FVF				= mesh->GetFVF();					//頂点フォーマットを取得する。
		DWORD vertexSize		= D3DXGetFVFVertexSize( FVF );		// 頂点のサイズを取得する。
		for( DWORD i = 0; i < atack->vertexSum; i++ )
		{
			atack->meshVertex[(int)i] = *(D3DXVECTOR3*)pVertex;	// 頂点座標を取得する。
			pVertex += vertexSize;									// 次の頂点にポインタを移動する。
		}

		for( DWORD i = 0; i < atack->meshSum; i++ )
		{
			//int型 : size 2 ずつ進むだろう
			atack->meshIndex[(int)i][0] = *(pIndex);	// 頂点座標を取得する。
			atack->meshIndex[(int)i][1] = *(pIndex + 2);
			atack->meshIndex[(int)i][2] = *(pIndex + 4);
			pIndex += 6;									// 次の頂点にポインタを移動する。
		}
	
		//アンロック
		mesh->UnlockVertexBuffer();
		mesh->UnlockIndexBuffer();

		NanairoLib::GetNomalLine(atack);
		mesh->Release();
		atack->used = true;
		return 1;
	}

	//-----------------------------------------------------------
	//テクスチャから幅と高さを取得
	//-----------------------------------------------------------
	//@in : テクスチャインターフェイス
	//@out : 幅
	//@out : 高さ
	void SetTextureLong(IDirect3DTexture9* gh, int* wh, int* ht)
	{
		if(wh == NULL || ht == NULL)	return ;

		::IDirect3DSurface9* suf;
		D3DSURFACE_DESC desc;
		gh->GetSurfaceLevel( 0, &suf );
		suf->GetDesc( &desc );
		(*wh) = (int)desc.Width;
		(*ht) = (int)desc.Height;
		suf->Release();
	}
}