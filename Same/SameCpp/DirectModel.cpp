#pragma once
//----------------------------------------------------
//
//３Ｄモデルの描画のメソッドを置いてますっ
//
//----------------------------------------------------
#include <DirectModel.h>
#include <DirectFunctionPlus.h>

namespace NanairoLib
{
	#pragma region デコン系
	inline MyModel::MyModel()
	{
		this->parts.used = false;
		this->parts.mesh = NULL;
		this->parts.matel = NULL;
		this->parts.atackNumber = 0;
		this->parts.matelSum = 0;
		this->color = D3DXVECTOR4(255,255,255,255);
	}

	MyModel::~MyModel()
	{
		this->releaseModel();
	}
	#pragma endregion

	//----------------------------------
	//そのモデルは存在しているか
	//----------------------------------
	//@out : true(成功) false(失敗)
	inline bool MyModel::isUse()
	{
		return this->parts.used;
	}

	//----------------------------------
	//そのモデルに対するあたり判定用データは存在しているか
	//----------------------------------
	//@out : true(成功) false(失敗)
	inline int MyModel::GetAtackPointNumber()
	{
		return this->parts.atackNumber;
	}

	//----------------------------------
	//そのモデルのマテリアルの数を取得
	//----------------------------------
	//@out : マテリアルの数
	inline int MyModel::GetMaterialSum()
	{
		return this->parts.matelSum;
	}

	//----------------------------------
	//そのモデルのメッシュを取得
	//----------------------------------
	//@out : メッシュインターフェイスポインタ
	inline const ID3DXMesh* MyModel::GetMesh()
	{
		return this->parts.mesh;
	}

	//----------------------------------
	//そのモデルのマテリアルを取得
	//----------------------------------
	//@out : マテリアルインターフェイスポインタ
	inline const D3DMATERIAL9* MyModel::GetMaterial()
	{
		return this->parts.matel;
	}

	//----------------------------------
	//そのモデルのデータポインタの取得
	//----------------------------------
	//@out : モデルのデータポインタ
	inline PMODELH MyModel::GetModelPoint() const
	{
		return (PMODELH const)&this->parts;
	}

	//----------------------------------
	//そのモデルのデータポインタのセッティング
	//----------------------------------
	//@in : モデルのデータポインタ
	void MyModel::SetModelH(MODELH* model)
	{
		if( model == NULL ) return ;
		::memcpy( &this->parts, model, sizeof(MODELH) );
		this->parts.used = true;
	}

	//----------------------------------
	//モデルのロード
	//----------------------------------
	//@in : DirectX用デバイス
	//@in : ファイルパス
	//@in : モード
	//@out : true(成功) false(失敗)
	bool MyModel::loadModel(PDirectDevice Device,LPCSTR fileName,int mode)
	{
		NanairoLib::TextFunc text;
		return (text.LoadModel3D( Device, fileName, &this->parts, mode ) ? true : false );
	}

	//----------------------------------
	//そのモデルのリリース
	//----------------------------------
	void MyModel::releaseModel()
	{
		if( this->parts.matel != NULL )
		{
			delete this->parts.matel;
			this->parts.matel = NULL;
		}

		if( this->parts.textureX != NULL )
		{
			int sum = this->parts.matelSum;
			for(int j=0; j<sum; j++)
				ES_SAFE_RELEASE( this->parts.textureX[j] );
		}
		ES_SAFE_RELEASE( this->parts.mesh );
		this->parts.used = false;
	}

	//----------------------------------
	//そのモデルのワールド行列のセッティング
	//----------------------------------
	//@in : DirectX用デバイス
	//@in : ワールド行列
	//@in : シェーダークラス
	void MyModel::SettingWorld(IDirect3DDevice9* Device,const D3DXMATRIX* mat,Shader* shader)
	{
#ifdef SHADER_DRAWER
		if(shader != NULL)
			shader->Effect->SetMatrix( SHADER_MATRIX_WORLD_ , mat );
		else
		{
			NanairoLib::Direct3DFunc func;
			func.SetWorldPos( Device, mat );
		}
#else
		NanairoLib::Direct3DFunc func;
		func.SetWorldPos( Device, mat );
#endif
	}

	//----------------------------------
	//そのモデルの描画
	//----------------------------------
	//@in : DirectX用デバイス
	//@in : シェーダークラス
	//@in : テクスチャデータポインタ
	//@in : モード
	void MyModel::drawModel(IDirect3DDevice9* Device,Shader* shader,TEXTUREH* text,int mode)
	{
#ifdef SHADER_DRAWER
		this->drawShaderModel( Device, shader, text, mode );
#else
		this->drawNoShaderModel( Device, text, mode );
#endif
	}

	void MyModel::drawNoShaderModel(IDirect3DDevice9* Device,TEXTUREH* text,int mode)
	{
		if( !this->parts.used )	 return ;
		Device->SetFVF( BACK_FVF );
		::D3DMATERIAL9 mt;
		bool hantei = false;
		if( mode == 1 && text != NULL )
		{
			Device->SetTexture( 0, text->graph );
			hantei = true;
		} 
		
		for(int i=0; i<this->parts.matelSum; i++)
		{
			mt = this->parts.matel[i];
			mt.Ambient.a = ( this->color.x < 1.0f ? 0.0f : mt.Ambient.a * (this->color.x / 255 ) );
			mt.Ambient.r = ( this->color.y < 1.0f ? 0.0f : mt.Ambient.r * (this->color.y / 255 ) );
			mt.Ambient.g = ( this->color.z < 1.0f ? 0.0f : mt.Ambient.g * (this->color.z / 255 ) );
			mt.Ambient.b = ( this->color.w < 1.0f ? 0.0f : mt.Ambient.b * (this->color.w / 255 ) );
			
			Device->SetMaterial( &mt );
			if( !hantei )
				Device->SetTexture( 0, this->parts.textureX[i] );
			this->parts.mesh->DrawSubset( i );
		}
	}

	void MyModel::drawShaderModel(IDirect3DDevice9* Device,Shader* shader,TEXTUREH* text,int mode)
	{
		if( !this->parts.used || shader == NULL )	 return ;
		Device->SetFVF( BACK_FVF );
		::D3DMATERIAL9 mt;
		bool hantei = false;
		if(mode == 1 && text != NULL)
		{
			shader->Effect->SetBool( SHADER_TEX_ABLE_, true );
			shader->Effect->SetTexture( SHADER_TEX1_, text->graph );
			hantei = true;
		}

		for(int i=0; i<this->parts.matelSum; i++)
		{
			mt = this->parts.matel[i];
			mt.Ambient.a = ( this->color.x < 1.0f ? 0.0f : mt.Ambient.a * (this->color.x / 255 ) );
			mt.Ambient.r = ( this->color.y < 1.0f ? 0.0f : mt.Ambient.r * (this->color.y / 255 ) );
			mt.Ambient.g = ( this->color.z < 1.0f ? 0.0f : mt.Ambient.g * (this->color.z / 255 ) );
			mt.Ambient.b = ( this->color.w < 1.0f ? 0.0f : mt.Ambient.b * (this->color.w / 255 ) );
			
			shader->Effect->SetFloatArray( SHADER_MATERIAL_, (float*)(&mt), 17 );
			if( !hantei )
			{
				shader->Effect->SetBool( SHADER_TEX_ABLE_, (this->parts.textureX[i] != NULL) );
				shader->Effect->SetTexture( SHADER_TEX1_, this->parts.textureX[i] );
			}

			shader->Effect->CommitChanges();
			this->parts.mesh->DrawSubset( i );
		}
	}
}