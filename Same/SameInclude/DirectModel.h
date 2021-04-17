#ifndef _NanairoLib_MODEL_H
#define _NanairoLib_MODEL_H

#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

namespace NanairoLib
{

	//----------------------------
	//3D静止状態のモデル
	//----------------------------
	class MyModel
	{
		private:
			MODELH parts;
			D3DXVECTOR4 color;
		public:
			__IMPOETER MyModel();
			__IMPOETER ~MyModel();
		public:
			//----------------------------------
			//そのモデルは存在しているか
			//----------------------------------
			//@out : true(成功) false(失敗)
			__IMPOETER bool isUse();
			//----------------------------------
			//そのモデルに対するあたり判定用データは存在しているか
			//----------------------------------
			//@out : true(成功) false(失敗)
			__IMPOETER int GetAtackPointNumber();

			//----------------------------------
			//そのモデルのマテリアルの数を取得
			//----------------------------------
			//@out : マテリアルの数
			__IMPOETER int GetMaterialSum();

			//----------------------------------
			//そのモデルのメッシュを取得
			//----------------------------------
			//@out : メッシュインターフェイスポインタ
			__IMPOETER const ID3DXMesh* GetMesh();

			//----------------------------------
			//そのモデルのマテリアルを取得
			//----------------------------------
			//@out : マテリアルインターフェイスポインタ
			__IMPOETER const D3DMATERIAL9* GetMaterial();

			//----------------------------------
			//そのモデルのデータポインタの取得
			//----------------------------------
			//@out : モデルのデータポインタ
			__IMPOETER PMODELH GetModelPoint() const;

			//----------------------------------
			//そのモデルのデータポインタのセッティング
			//----------------------------------
			//@in : モデルのデータポインタ
			__IMPOETER void SetModelH(MODELH* model);

		public:
			//----------------------------------
			//モデルのロード
			//----------------------------------
			//@in : DirectX用デバイス
			//@in : ファイルパス
			//@in : モード
			//@out : true(成功) false(失敗)
			__IMPOETER bool loadModel(PDirectDevice Device,LPCSTR fileName,int mode);
			
			//----------------------------------
			//そのモデルのリリース
			//----------------------------------
			__IMPOETER void releaseModel();
			
			//----------------------------------
			//そのモデルのワールド行列のセッティング
			//----------------------------------
			//@in : DirectX用デバイス
			//@in : ワールド行列
			//@in : シェーダークラス
			__IMPOETER void SettingWorld(IDirect3DDevice9* Device,const D3DXMATRIX* mat,Shader* shader = NULL);
			
			//----------------------------------
			//そのモデルの描画
			//----------------------------------
			//@in : DirectX用デバイス
			//@in : シェーダークラス
			//@in : テクスチャデータポインタ
			//@in : モード
			__IMPOETER void drawModel(IDirect3DDevice9* Device,Shader* shader = NULL,TEXTUREH* text = NULL,int mode = 0);
			__IMPOETER void drawNoShaderModel(IDirect3DDevice9* Device,TEXTUREH* text = NULL,int mode = 0);
			__IMPOETER void drawShaderModel(IDirect3DDevice9* Device,Shader* shader = NULL,TEXTUREH* text = NULL,int mode = 0);

	};

	typedef MyModel*		PMyModel;
	typedef const MyModel*	PCMyModel;
}

#endif