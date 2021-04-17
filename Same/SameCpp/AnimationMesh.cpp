#pragma once
//-------------------------------------------------------------------------
//
//動くモデルのアニメーションを扱う
//
//-------------------------------------------------------------------------
#include <AnimationMesh.h>
#pragma comment(lib,"winmm.lib")

namespace NanairoLib
{
	//-----------------------------
	//コンテナ管理
	//-----------------------------
	MY_HIERARCHY MY_MESH::hierarchy;

	
	#pragma region コンストラクタ
	MY_D3DXMESHCONTAINER::MY_D3DXMESHCONTAINER()
	{
		::memset(this,0,sizeof(*this));
	}
	
	MY_D3DXMESHCONTAINER::~MY_D3DXMESHCONTAINER()
	{
		ES_SAFE_DELETE_ARRAY(materials);

		if(textures)
		{
			for(int i=0;i<materialNum;i++){	if(textures[i] != NULL)	textures[i]->Release();	}
			delete[] textures;
			textures = NULL;
		}

		ES_SAFE_RELEASE(pSkinInfo);
		ES_SAFE_RELEASE(MeshData.pMesh);
		ES_SAFE_RELEASE(workMesh);
		ES_SAFE_DELETE_ARRAY(boneUpdateMatrix);
	}
	#pragma endregion

	#pragma region メッシュコンストラクタ
	MY_MESH::MY_MESH()
	{
		memset(this,0,sizeof(*this));
	}

	///device	: デバイス
	///fileName	: ファイル名
	MY_MESH::MY_MESH(IDirect3DDevice9 *device,LPCSTR fileName)
	{
		memset(this,0,sizeof(*this));
		D3DXLoadMeshHierarchyFromX(fileName,D3DXMESH_SYSTEMMEM,device,&hierarchy,NULL,&root,&this->animController);
	}

	MY_MESH::~MY_MESH()
	{
		ES_SAFE_RELEASE(this->animController);
		if(this->root != NULL){				::D3DXFrameDestroy(root,&hierarchy); this->root = NULL; }
	}
	#pragma endregion
	
	//----------------------------------------------------
	//アニメーションのバックアップ
	//----------------------------------------------------
	//@in : フレーム情報
	void MY_MESH::_backupAnimationMatrix(D3DXFRAME *frame)
	{
		//バックアップ
		((MY_FRAME*)frame)->originalMatrix = frame->TransformationMatrix;
	
		//ツリー探査
		if(frame->pFrameSibling != NULL)	this->_backupAnimationMatrix(frame->pFrameSibling);
		if(frame->pFrameFirstChild != NULL)	this->_backupAnimationMatrix(frame->pFrameFirstChild);
	}
	
	//----------------------------------------------------
	//アニメーションのリセット
	//----------------------------------------------------
	//@in : フレーム情報
	void MY_MESH::_reSetAnimationMatrix(D3DXFRAME *frame)
	{
		//バックアップ
		frame->TransformationMatrix = ((MY_FRAME*)frame)->originalMatrix;
	
		//ツリー探査
		if(frame->pFrameSibling != NULL)	this->_reSetAnimationMatrix(frame->pFrameSibling);
		if(frame->pFrameFirstChild != NULL)	this->_reSetAnimationMatrix(frame->pFrameFirstChild);
	}
	
	//----------------------------------------------------------------------------------------
	//アニメーション更新
	///フレーム毎のアニメーション行列を、回帰しながら計算。
	///自分自身のTransformationMatrixにSetTimeによりアニメーションされた行列が入っているので、
	///親の行列をマージして最終的な行列を格納しておく。フレームは階層構造で
	///siblingには自分に適用した行列を、
	///chileには自分の行列をマージした行列を渡して再帰する。
	//-----------------------------------------------------------------------------------------
	//@in : フレーム情報
	//@out : 変換行列
	void MY_MESH::_updateAnimationMatrix(D3DXFRAME *frame,D3DXMATRIX *mat)
	{
		//フレーム毎のアニメーション行列作成
		if(mat != NULL)	::D3DXMatrixMultiply(&frame->TransformationMatrix,&frame->TransformationMatrix,mat);

		//ツリー探査
		if(frame->pFrameSibling != NULL)	this->_updateAnimationMatrix(frame->pFrameSibling,mat);
		if(frame->pFrameFirstChild != NULL)	this->_updateAnimationMatrix(frame->pFrameFirstChild,&frame->TransformationMatrix);
	}
	
	//---------------------------------------------------------------------
	//メッシュのドロー
	//---------------------------------------------------------------------
	//@in : モーション番号
	//@in : 現在のモーションフレーム時間
	//@in : 変換行列
	//@in : 色分けモード
	void MY_MESH::draw(int Set,unsigned int passTime,D3DXMATRIX *m, int mode)
	{
		//アニメーション経過時間の設定
		if(this->animController != NULL)
		{
			ID3DXAnimationSet *animSet = NULL;
			animController->GetAnimationSet(Set,&animSet);
			animController->SetTrackAnimationSet(0,animSet);

			//最初のアニメーションにセット
			//this->_reSetAnimationMatrix(root);

	#if(D3D_SDK_VERSION >= 32)
			//現在の時間からの経過時間を指定
			//(SetTrackPosition - ResetTime)の絶対時間
			animController->SetTrackPosition(0,0);
			animController->ResetTime();
			animController->AdvanceTime(passTime / 1000.0,NULL);
	#else
			//直接時間を設定
			animController->SetTime(passTime / 1000.0)
			if(animSet != NULL)	animSet->Release();
	#endif
			//アニメーションマトリックスの作成
			this->_updateAnimationMatrix(root,NULL);
		}
		//描画
		this->_callDrawMesh(root,m, mode);
	}
	
	//---------------------------------------------------------------------
	//描画の呼び出し
	//---------------------------------------------------------------------
	//@in : フレーム情報
	//@in : 変換行列
	//@in : 色分けモード
	void MY_MESH::_callDrawMesh(D3DXFRAME *frame,D3DXMATRIX *m, int mode)
	{
		//フレーム毎の描画（持っているメッシュを全部書き出す）
		MY_D3DXMESHCONTAINER *meshContainer = (MY_D3DXMESHCONTAINER*)frame->pMeshContainer;
	
		//リストが終端じゃなければ
		while(meshContainer != NULL)
		{
			//毎ボーン毎ボーンやってく
			_drawMeshContainer(meshContainer,frame,m, mode);
			meshContainer = (MY_D3DXMESHCONTAINER*)meshContainer->pNextMeshContainer;
		}

		//ツリー探査
		if(frame->pFrameSibling != NULL)	this->_callDrawMesh(frame->pFrameSibling,m, mode);
		if(frame->pFrameFirstChild != NULL)	this->_callDrawMesh(frame->pFrameFirstChild,m, mode);
	}
	
	//-----------------------------------------------------------------------------
	//コンテナに入っているデータをドロー
	//-----------------------------------------------------------------------------
	//@in : コンテナに入っている情報
	//@in : フレーム情報
	//@in : 変換行列
	//@in : 色分けモード
	void MY_MESH::_drawMeshContainer(MY_D3DXMESHCONTAINER *meshContainer,D3DXFRAME *frame,D3DXMATRIX *m, int mode)
	{
		//バックアップの取得
		MY_D3DXMESHCONTAINER *mc = (MY_D3DXMESHCONTAINER*)meshContainer;

		//頂点バッファにボーン変形を適用
		if(meshContainer->pSkinInfo != NULL){
			//ボーン合計の取得
			int boneNum = mc->pSkinInfo->GetNumBones();

			//ボーン変形マトリクスを算出
			for(int i=0;i<boneNum;i++)
			{
				D3DXFRAME *f = ::D3DXFrameFind(root,mc->pSkinInfo->GetBoneName(i));
				if(f != NULL)
				{
					::D3DXMatrixMultiply(&mc->boneUpdateMatrix[i],
									mc->pSkinInfo->GetBoneOffsetMatrix(i),
									&f->TransformationMatrix);
				}
			}

			//頂点バッファのポインタを取得する
			void* org;
			//オリジナル頂点データ（変換元）
			mc->MeshData.pMesh->LockVertexBuffer(D3DLOCK_READONLY,(void**)&org);
			//変形頂点データ（出力先）
			void** work;
			mc->workMesh->LockVertexBuffer(0,(void**)&work);

			//スキンメッシュの更新
			HRESULT hr = mc->pSkinInfo->UpdateSkinnedMesh(meshContainer->boneUpdateMatrix,NULL,org,work);

			mc->MeshData.pMesh->UnlockVertexBuffer();
			mc->workMesh->UnlockVertexBuffer();

			//スキンメッシュに更新したところで
			//ここからが描画---------------------------------------------------------------------------------------------
			
			Shader* sh = this->hierarchy.GetShader();
#ifdef SHADER_DRAWER
			if( sh == NULL )
				this->hierarchy.GetDevice()->SetTransform(D3DTS_WORLD,m);
			else
				sh->Effect->SetMatrix( SHADER_MATRIX_WORLD_, m );
#else
			this->hierarchy.GetDevice()->SetTransform(D3DTS_WORLD,m);
#endif
			for(int i=0;i<mc->materialNum;i++)
			{
				if( sh == NULL )
				{
					//マテリアル情報セット
					this->hierarchy.GetDevice()->SetTexture(0,mc->textures[i]);
					this->hierarchy.GetDevice()->SetMaterial(&mc->materials[i]);
				}
				else{
#ifdef SHADER_DRAWER
					sh->Effect->SetFloatArray( SHADER_MATERIAL_, (float*)(&mc->materials[i]), 17 );
					sh->Effect->SetTexture( SHADER_TEX1_, mc->textures[i] );
					sh->Effect->SetBool( SHADER_TEX_ABLE_, (mc->textures[i] != NULL) );
					sh->Effect->CommitChanges();
#else
					this->hierarchy.GetDevice()->SetMaterial( &mc->materials[i] );
					if( mc->textures[i] != NULL ) 
						this->hierarchy.GetDevice()->SetTexture( 0, mc->textures[i] );
#endif
				}
				//描画どーん！
				mc->workMesh->DrawSubset(i);
			}
		}
	}
	
}