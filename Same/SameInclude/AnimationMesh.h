#ifndef MYGAME_MESH_H
#define MYGAME_MESH_H

//-------------------------------------------------
//アニメーションスキンメッシュを管理するクラス
//-------------------------------------------------
#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

#if(D3D_SDK_VERSION >= 32)
	#define CONST_90C const
#else
	#define CONST_90C
#endif

namespace NanairoLib
{
	//----------------------------------------------------------------------
	//フレーム情報クラス
	//行列を保持
	//----------------------------------------------------------------------
	class MY_FRAME : public ::D3DXFRAME
	{
		public:
			//最初の状態を覚えておく。
			D3DXMATRIX originalMatrix;
	};

	//----------------------------------------------------------------------
	//メッシュコンテナクラス
	//----------------------------------------------------------------------
	class MY_HIERARCHY : public ::ID3DXAllocateHierarchy
	{
		private:
			IDirect3DDevice9*	_devices;
			Shader*				_shader;
		public:
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall CreateFrame(const char *filaName,D3DXFRAME **frame);
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall CreateMeshContainer(
				LPCSTR name,
				CONST_90C D3DXMESHDATA *meshData,
				CONST_90C D3DXMATERIAL *materials,
				CONST_90C D3DXEFFECTINSTANCE *effectInstances,
				DWORD materialNum,
				CONST_90C DWORD *pAdjacency,
				ID3DXSkinInfo *skinInfo,
				D3DXMESHCONTAINER **newMeshContainer);
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall DestroyFrame(D3DXFRAME *frame);
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall DestroyMeshContainer(D3DXMESHCONTAINER *meshContainer);
	
		public:
			__IMPOETER MY_HIERARCHY() : _devices(0), _shader(0){}
			__IMPOETER void SetDevice(IDirect3DDevice9* device){	this->_devices = device;	}
			__IMPOETER IDirect3DDevice9* GetDevice(){				return this->_devices;		}
			__IMPOETER void SetShader(Shader* sha){					this->_shader = sha;		}
			__IMPOETER Shader* GetShader(){							return this->_shader;		}
	};

	//----------------------------------------------------------------------
	//アニメーション用メッシュデータ構造体
	//----------------------------------------------------------------------
	class MY_D3DXMESHCONTAINER : public D3DXMESHCONTAINER
	{
	public:
		//アニメーション後メッシュデータ
		//表示用に、オリジナルメッシュデータにアニメーションを適用した状態を記憶
		ID3DXMesh *workMesh;

		//ボーンアニメーションマトリクス
		//状態更新関数呼び出し時に状態変更マトリックスが入ってくる。
		D3DXMATRIX *boneUpdateMatrix;

		//マテリアル数
		int materialNum;

		//マテリアル情報
		D3DMATERIAL9 *materials;

		//テクスチャ情報
		IDirect3DTexture9 **textures;
	
	public:
		__IMPOETER MY_D3DXMESHCONTAINER();
		__IMPOETER ~MY_D3DXMESHCONTAINER();
	};

	//----------------------------------------------------------------------
	//アニメーションメッシュ（動くモデルデータ）を扱うクラス
	//----------------------------------------------------------------------
	class MY_MESH
	{
		static MY_HIERARCHY hierarchy;	//初期化の実態はMY_HIERARCHYクラスに（使い回し可能）

		//データ
		//------------------------------------------------------
	protected:
		//メッシュルート（ポリゴン群のツリーのルート）
		D3DXFRAME *root;
		//アニメーションコントローラ
		ID3DXAnimationController *animController;

		//初期化
		//------------------------------------------------------
	public:
		__IMPOETER MY_MESH();
		__IMPOETER MY_MESH(IDirect3DDevice9 *device,const char *fileName);
		__IMPOETER ~MY_MESH();

		__IMPOETER static MY_HIERARCHY* GetHierarchy()
		{
			return &hierarchy;
		}
		
	protected:	//状態更新＆描画
		//----------------------------------------------------
		//アニメーションのバックアップ
		//----------------------------------------------------
		//@in : フレーム情報
		__IMPOETER void _backupAnimationMatrix(D3DXFRAME *frame);

		//----------------------------------------------------
		//アニメーションのリセット
		//----------------------------------------------------
		//@in : フレーム情報
		__IMPOETER void _reSetAnimationMatrix(D3DXFRAME *frame);

		//-----------------------------------------------------
		//アニメーション更新
		//------------------------------------------------------
		//@in : フレーム情報
		//@out : 変換行列
		__IMPOETER void _updateAnimationMatrix(D3DXFRAME *frame,D3DXMATRIX *mat);

		//---------------------------------------------------------------------
		//描画の呼び出し
		//---------------------------------------------------------------------
		//@in : フレーム情報
		//@in : 変換行列
		//@in : 色分けモード
		__IMPOETER void _callDrawMesh(D3DXFRAME *frame,D3DXMATRIX *m, int mode);

		//-----------------------------------------------------------------------------
		//コンテナに入っているデータをドロー
		//-----------------------------------------------------------------------------
		//@in : コンテナに入っている情報
		//@in : フレーム情報
		//@in : 変換行列
		//@in : 色分けモード
		__IMPOETER void _drawMeshContainer(MY_D3DXMESHCONTAINER *meshContainer,D3DXFRAME *frame,D3DXMATRIX *m, int mode);
	public:
		/*
			時間経過でアニメーションさせ、表示する
			@param Set　	アニメーション番号
			@param passTime 経過時間(ms)
			@param m		表示用マトリクス
		*/
		__IMPOETER void draw(int Set,unsigned int passTime,D3DXMATRIX *m, int mode = 0);

		
	protected:
		//------------------------------------------------------------------
		//コピーガード（ポインタを含むクラスなので、コピーできないように）
		//------------------------------------------------------------------
		__IMPOETER MY_MESH(MY_MESH &mesh){}
		__IMPOETER MY_MESH& operator = (MY_MESH &mesh){	return *this;	}
	};
}


#endif