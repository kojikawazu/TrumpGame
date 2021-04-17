#pragma once
//----------------------------------------------------
//２Ｄ画像の描画のメソッドを置いてますっ
//----------------------------------------------------
#include <DirectGraph.h>

namespace NanairoLib
{
	//------------------------------
	//初期化
	//------------------------------
	inline void MyGraph::sameInit()
	{
		this->parts.used = this->parts.division = false;
		this->parts.graph = NULL;
		this->parts.height = this->parts.width = this->parts.sumX = 
			this->parts.sumY = this->parts.oneH = this->parts.oneW = 0;
		this->color = D3DXVECTOR4( 255,255,255,255 );
		this->art = NULL;
	}

	//------------------------------
	//デコン系
	//------------------------------
	#pragma region デコン系
	inline MyGraph::MyGraph()
	{
		this->sameInit();
	}

	MyGraph::MyGraph(PTEXTUREH handle)
	{
		this->sameInit();
		this->SetTexture( handle->graph, (float)handle->width, (float)handle->height );
		this->SetDivision( handle->sumX, handle->sumY );
	}


	inline MyGraph::~MyGraph()
	{
		ES_SAFE_RELEASE( this->parts.graph );
	}
	#pragma endregion

	//----------------------------------------------------------------
	//テクスチャのセッティング
	//----------------------------------------------------------------
	//@in : テクスチャ
	//@in : 幅
	//@in : 高さ
	void MyGraph::SetTexture(IDirect3DTexture9* gh, float wh, float ht)
	{
		if(gh == NULL)	return ;
		ES_SAFE_RELEASE( this->parts.graph );
		this->parts.graph = gh;
		this->parts.graph->AddRef();

		if( wh == 0 || ht == 0)
		{
			::IDirect3DSurface9* suf;
			D3DSURFACE_DESC desc;
			gh->GetSurfaceLevel( 0, &suf );
			suf->GetDesc( &desc );
			this->parts.width = (int)desc.Width;
			this->parts.height = (int)desc.Height;
			suf->Release();
		}
		else
		{
			this->parts.width = (int)wh;
			this->parts.height = (int)ht;
		}
	}

	//----------------------------------------------
	//分割のセッティング
	//----------------------------------------------
	//@in : 分割横数
	//@in : 分割縦数
	void MyGraph::SetDivision(int divX, int divY)
	{
		if( divX == 0 || divY == 0 ||
			this->parts.width == 0 || this->parts.height == 0 )	
			return ;
		this->parts.sumX = divX;
		this->parts.sumY = divY;

		this->parts.oneW = this->parts.width / this->parts.sumX;
		this->parts.oneH = this->parts.height / this->parts.sumY;

		this->parts.division = true;
	}

	//----------------------------------------------
	//ロードテクスチャ
	//----------------------------------------------
	//@in : DirectX用デバイス
	//@in : ファイルパス
	//@in : 幅
	//@in : 高さ
	//@in : 分割横数
	//@in : 分割縦数
	bool MyGraph::LoadTexture(PDirectDevice Device,PCSTR fileName,int width,int height,int sumW,int sumH)
	{
		TextFunc text;
		if( text.LoadGraphIndex(Device, &this->parts, fileName, width, height, sumW, sumH) == -1)
			return this->parts.used = false;
		return (this->parts.used = true);
	}

	//----------------------------------------------
	//テクスチャのリリース
	//----------------------------------------------
	void MyGraph::ReleaseTexture()
	{
		ES_SAFE_RELEASE( this->parts.graph );
	}

	//----------------------------------------------
	//テクスチャハンドルの取得
	//----------------------------------------------
	//@out : テクスチャハンドル
	PCTEXTUREH MyGraph::GetTextureHandle()
	{
		return &this->parts;
	}

	//----------------------------------------------
	//テクスチャハンドルポインタの取得
	//----------------------------------------------
	//@out : テクスチャハンドル
	PTEXTUREH MyGraph::GetTexturePointer()
	{
		return &this->parts;
	}

	//----------------------------------------------
	//テクスチャの取得
	//----------------------------------------------
	//@out : DirectX用テクスチャ
	const IDirect3DTexture9* MyGraph::GetTexture()
	{
		return this->parts.graph;
	}

	//----------------------------------------------
	//カラーの取得
	//----------------------------------------------
	PCVector4 MyGraph::GetColor()
	{
		return &this->color;
	}

	//----------------------------------------------
	//カラーのセッティング
	//----------------------------------------------
	//@in : argb
	void MyGraph::SetColor(float a, float r, float g, float b)
	{
		this->color.x = a;
		this->color.y = r;
		this->color.z = g;
		this->color.w = b;
	}

	//----------------------------------------------
	//カラーのセッティング
	//----------------------------------------------
	//@in : argbカラーベクトル
	void MyGraph::SetColor(PCVector4 col)
	{
		this->color = col;
	}

	//----------------------------------------------
	//テクスチャの普通に描画
	//----------------------------------------------
	//@in : 描画専用クラス
	void MyGraph::Draw_Graph(Artisan* Artisan)
	{
		Artisan->DrawVertexBuffer( &this->parts );
	}

	//----------------------------------------------
	//テクスチャのアニメーション描画
	//----------------------------------------------
	//@in : 描画専用クラス
	//@in : 割り当て番号
	void MyGraph::Draw_Animation_Graph(int number)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawVertexBufferIndex( &this->parts, number );
	}

	//----------------------------------------------
	//テクスチャの直座標設定・直分割描画
	//----------------------------------------------
	//@in : 描画専用クラス
	//@in : 四角の座標ベクトル
	//@in : 分割横数
	//@in : 分割縦数
	//@in : 割り当て番号
	void MyGraph::Draw_Modi_div_Animation_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number, int divXSum, int divYSum)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawVertexBufferIndexModi( &this->parts, lup, rup, lbot, rbot, number, divXSum, divYSum );
	}

	//----------------------------------------------
	//テクスチャの直座標設定・アニメーション描画
	//----------------------------------------------
	//@in : 描画専用クラス
	//@in : 四角の座標ベクトル
	//@in : 割り当て番号
	void MyGraph::Draw_Modi_Animation_Graph( RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawRectDepGraph( lup, rup, lbot, rbot, number, &this->parts );
	}

	//----------------------------------------------
	//テクスチャのガラスのような描画
	//----------------------------------------------
	//@in : 描画専用クラス
	//@in : 三角形の座標ベクトル
	//@in : 分割幅
	//@in : 分割高さ
	//@in : 分割横数
	//@in : 分割縦数
	//@in : 割り当て番号
	void MyGraph::Draw_Grass_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot,int number, int divXSum, int divYSum, int width, int height,bool IsUp)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawIndexGlassHopper( this->parts.graph, lup, rup, lbot, number, divXSum, divYSum , width, height, IsUp );
	}

	//----------------------------------------------
	//描画のトランスフォーム
	//----------------------------------------------
	//@in : 描画専用クラス
	//@in : 位置
	//@in : スケール
	//@in : 角度
	//@in : 色情報
	//@in : スケールモード
	void MyGraph::Transform(RCVector2 pos, RCVector2 scale, float angle,PCVector4 color,int mode)
	{
		if( CHECK_NULL(art) )	return ;
		art->Transform( pos, scale, angle, &this->parts, color, mode );
		this->color = (color);
	}

	//----------------------------------------------
	//描画のトランスフォーム(3D用)
	//----------------------------------------------
	//@in : 描画専用クラス
	//@in : 位置
	//@in : スケール
	//@in : 角度
	//@in : 色情報
	//@in : スケールモード
	void MyGraph::Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCVector4 color,int mode)
	{
		if( CHECK_NULL(art) )	return ;
		art->Transform3D( pos, scale, angle, &this->parts, color, mode );
		this->color = color;

	}

	//----------------------------------------------
	//描画のトランスフォーム(ビルボード用)
	//----------------------------------------------
	//@in : 描画専用クラス
	//@in : 位置
	//@in : スケール
	//@in : 角度
	//@in : 色情報
	//@in : ビルボード行列
	//@in : スケールモード
	void MyGraph::TransformBillboard(PCVector3 pos, RCVector2 scale, float angle,PCVector4 color, PCMATRIX board, int mode)
	{
		if( CHECK_NULL(art) )	return ;
		art->Transform3D_ofBillboard( pos, scale, angle, &this->parts, color, board, mode );
		this->color = color;
	}
}