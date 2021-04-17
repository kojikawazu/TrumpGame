#pragma once
//--------------------------------------------------------------------------
//アニメーション情報を管理するコンテナ
//--------------------------------------------------------------------------
#pragma region インクルード
#define _NEED_FUNCI
#pragma warning(disable : 4996)
#include <AnimationMesh.h>
#pragma endregion

namespace NanairoLib
{

	//----------------------------------------------------------------
	//フレームデータの作成
	//----------------------------------------------------------------
	//@in : ファイル名
	//@in : フレーム情報
	__declspec(nothrow) HRESULT __stdcall 
	MY_HIERARCHY::CreateFrame(const char *fileName,D3DXFRAME **frame)
	{
		*frame = new MY_FRAME();
	
		//名前付ける
		if(fileName != NULL)
		{
			(*frame)->Name = new char[strlen(fileName) + 1];
			strcpy((*frame)->Name,fileName);
		}
		else	(*frame)->Name = NULL;
		return S_OK;
	}

	//-------------------------------------
	//メッシュコンテナの生成
	//-------------------------------------
	__declspec(nothrow) HRESULT __stdcall
	MY_HIERARCHY::CreateMeshContainer(
			LPCSTR name,
			CONST_90C D3DXMESHDATA *meshData,
			CONST_90C D3DXMATERIAL *materials,
			CONST_90C D3DXEFFECTINSTANCE *effectInstances,
			DWORD materialNum,
			CONST_90C DWORD *pAdjacency,
			ID3DXSkinInfo *skinInfo,
			D3DXMESHCONTAINER **newMeshContainer)
	{
		*newMeshContainer = NULL;
		//データ保存用の作成		
		MY_D3DXMESHCONTAINER *m = new MY_D3DXMESHCONTAINER();
	
		//Nameメソッドに名前をつける----------------
		if(name != NULL)
		{
			m->Name = new char[strlen(name) + 1];
			strcpy(m->Name,name);
		}
		//------------------------------------------

		//メッシュタイプのチェック------------------
		if(meshData->Type != D3DXMESHTYPE_MESH)
		{	
			this->DestroyMeshContainer(m);	
			return E_FAIL;	
		}

		int FVF = meshData->pMesh->GetFVF();
		if(FVF == 0){	
			this->DestroyMeshContainer(m);	
			return E_FAIL;	
		}
		//------------------------------------------

		//メッシュデータの代入
		m->MeshData = *meshData;
		//関数終了時にmeshDataが破棄されるので、これで消えないようになる！
		meshData->pMesh->AddRef();

		//アニメーション後の頂点データを保存するワークとしてworkMeshを作成
		m->MeshData.pMesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM,m->MeshData.pMesh->GetFVF(),this->_devices, &m->workMesh);
	
		//アニメーションデータがある場合の処理-----------------
		//スキンメッシュを保存
		if(skinInfo != NULL)
		{
			m->pSkinInfo = skinInfo;
			//消さないように
			skinInfo->AddRef();

			//ボーンの数の取得
			//頂点計算用ワークの作成
			int boneNum = skinInfo->GetNumBones();
			m->boneUpdateMatrix = new D3DXMATRIX[boneNum];
		}
		//-----------------------------------------------------

		//マテリアルの保存-------------------------------------------------------------------------
		//ここはアニメーションなしメッシュの読み込みと一緒
		m->materialNum = materialNum;
		m->materials = new D3DMATERIAL9[m->materialNum];
		m->textures = new IDirect3DTexture9*[m->materialNum];
		for(int i=0;i<m->materialNum;i++)
		{
			m->materials[i] = materials[i].MatD3D;
			m->textures[i] = NULL;
			if(materials[i].pTextureFilename != NULL)
				::D3DXCreateTextureFromFileA(this->_devices, materials[i].pTextureFilename,&m->textures[i]);
		}
		//-----------------------------------------------------------------------------------------

		//次のコンテナへ保存
		*newMeshContainer = m;
		return S_OK;
	}

	//--------------------------------------------------
	//フレームオブジェクトがあれば、名前用メモリを破棄
	//--------------------------------------------------
	__declspec(nothrow) HRESULT __stdcall 
	MY_HIERARCHY::DestroyFrame(D3DXFRAME *frame)
	{
		if(frame != NULL)
		{
			delete frame->Name;
			delete (MY_FRAME*)frame;
			frame = NULL;
		}
		return S_OK;
	}

	//----------------------------------------------------------------------
	//メッシュコンテナがあれば、それを作ったメモリを削除しておく。
	//----------------------------------------------------------------------
	__declspec(nothrow) HRESULT __stdcall 
	MY_HIERARCHY::DestroyMeshContainer(D3DXMESHCONTAINER *meshContainer)
	{
		if(meshContainer != NULL)
		{
			if(meshContainer->Name != NULL)	delete meshContainer->Name;
			delete (MY_D3DXMESHCONTAINER*)meshContainer;
			meshContainer = NULL;
		}
		return S_OK;
	}

}