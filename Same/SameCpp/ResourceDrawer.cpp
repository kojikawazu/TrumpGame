#pragma once
//----------------------------------------------------
//
//２D画像の描画のメソッドを置いてますっ
//
//----------------------------------------------------
#include <ResourceDrawer.h>

namespace NanairoLib
{
	#pragma region デフォルトポリゴン情報
	//-------------------------------------------------------------------
	//デフォルト板ポリ情報
	//-------------------------------------------------------------------
	const static ArtisanVT_2D polgon[4] = 
	{
		{     0.5f,-0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f}, //右上10
		{     0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f}, //右下11
		{    -0.5f,-0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f}, //左上00
		{    -0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f}  //左下01
	};

	const static ArtisanVT_2D polgonLF[4] = 
	{
		{     1.0f,-0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f}, //右上10
		{     0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f}, //右下11
		{    -0.5f,-0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f}, //左上00
		{    -0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f}  //左下01
	};

	//-------------------------------------------------------------------
	//3Dワールド上に出したい板ポリ情報
	//-------------------------------------------------------------------
	const static ArtisanVT_3D polgon3D[4] = 
	{
		{     0.5f,-0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f}, //右上
		{     0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f}, //右下
		{    -0.5f,-0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f}, //左上
		{    -0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f}  //左下
	};
	#pragma endregion
	
	//--------------------------------------------------------------------------------------------------
	//分割した値に変換
	//--------------------------------------------------------------------------------------------------
	//@inout : 分割幅
	//@inout : 分割高さ
	//@inout : 横番号
	//@inout : 縦番号
	//@in : 幅
	//@in  高さ
	//@in : 分割幅数
	//@in : 分割高さ数
	void Division(float* divW,float* divH,int* sumW,int* sumH,int num,int wnum,int hnum,int wh,int hei)
	{
		(*divW) = (float)(wh / wnum);
		(*divH) = (float)(hei / hnum);

		if(num == 0)	(*sumW) = (*sumH) = 0;
		else
		{
			(*sumW) = (num % wnum);
			(*sumH) = (num / wnum);
		}
	}
	
	//----------------------------------------------------------------------------------------
	//UV設定
	//----------------------------------------------------------------------------------------
	//@inout : 頂点情報
	//@in : 分割幅
	//@in : 分割高さ
	//@in : 割り当て横番号
	//@in : 割り当て縦番号
	//@in : 幅
	//@in : 高さ
	void DefaultSetUV(PArtisanVT_2D vertex,float divW,float divH,int sx,int sy,int wid,int hei)
	{
		vertex[0].u = ((divW * sx) + divW) / wid;
		vertex[0].v = (divH * sy) / hei;

		vertex[1].u = ((divW * sx) + divW) / wid;
		vertex[1].v = ((divH * sy) + divH) / hei;
		
		vertex[2].u = (divW * sx) / wid;
		vertex[2].v = (divH * sy) / hei;

		vertex[3].u = (divW * sx) / wid;
		vertex[3].v = ((divH * sy) + divH) / hei;
	}
	
	//----------------------------------------------------------------------------------------
	//UV設定(3Dバージョン)
	//----------------------------------------------------------------------------------------
	//@inout : 頂点情報
	//@in : 分割幅
	//@in : 分割高さ
	//@in : 割り当て横番号
	//@in : 割り当て縦番号
	//@in : 幅
	//@in : 高さ
	void DefaultSetUV_3D(PArtisanVT_3D vertex,float divW,float divH,int sx,int sy,int wid,int hei)
	{
		vertex[0].u = ((divW * sx) + divW) / wid;
		vertex[0].v = (divH * sy) / hei;

		vertex[1].u = ((divW * sx) + divW) / wid;
		vertex[1].v = ((divH * sy) + divH) / hei;
		
		vertex[2].u = (divW * sx) / wid;
		vertex[2].v = (divH * sy) / hei;

		vertex[3].u = (divW * sx) / wid;
		vertex[3].v = ((divH * sy) + divH) / hei;
	}
	
	//-----------------------------------------------
	//デフォルトカラーUV設定
	//-----------------------------------------------
	//@inout : 頂点情報
	//@in : カラーアルファ
	void DefaultColUV(PArtisanVT_2D vertex,UINT alpha)
	{
		for(int i=0; i<4; i++)
		{
			vertex[i].dwColor = alpha;
			vertex[i].u = polgon[i].u;
			vertex[i].v = polgon[i].v;
		}
	}

	//-----------------------------------------------
	//デフォルトカラーUV設定
	//-----------------------------------------------
	//@inout : 頂点情報
	//@in : カラーアルファ
	void DefaultColUV_3D(PArtisanVT_3D vertex,UINT alpha)
	{
		for(int i=0; i<4; i++)
		{
			vertex[i].dwColor = alpha;
			vertex[i].u = polgon3D[i].u;
			vertex[i].v = polgon3D[i].v;
		}
	}

	//-----------------------------------------------------------------------------
	//頂点情報の直入力
	//-----------------------------------------------------------------------------
	//@inout : 頂点情報
	//@in : 左上X座標
	//@in : 左上Y座標
	//@in : 右上X座標
	//@in : 右上Y座標
	//@in : 左下X座標
	//@in : 左下Y座標
	//@in : 右下X座標
	//@in : 右下Y座標
	void DirectSetUV(PArtisanVT_2D vx, float lupX,float lupY,float rupX,float rupY,
						float lbotX,float lbotY,float rbotX,float rbotY)
	{
		::memcpy( vx, polgon, sizeof( NanairoLib::ArtisanVT_2D) * 4);
		vx[0].x = rupX;
		vx[0].y = rupY;
		vx[1].x = rbotX;
		vx[1].y = rbotY;
		vx[2].x = lupX;
		vx[2].y = lupY;
		vx[3].x = lbotX;
		vx[3].y = lbotY;
	}

	//private---------------------------------------------------------------------------
	
	//-------------------------------------------------------
	//普通に中心をセットして変換行列で変換、色UVはデフォルト	
	//-------------------------------------------------------
	#pragma region 普通頂点変換
	void Artisan::TransNormal()
	{
		D3DXVECTOR3 po1,po2;
		po1.z = 0.0f;
		for(int i=0; i<4; i++)
		{
			po1.x = polgon[i].x;	po1.y = polgon[i].y;	
			D3DXVec3TransformCoord(&po2, &po1, &trans);
			vertex[i].x = po2.x;	vertex[i].y = po2.y;
		}
		DefaultColUV(&this->vertex[0], this->alpha);
	}

	void Artisan::TransWorld()
	{
		D3DXVECTOR3 po1, po2;
		for(int i=0; i<4; i++)
		{
			po1.x = polgon3D[i].x;	po1.y = polgon3D[i].y; po1.z = polgon3D[i].z;
			D3DXVec3TransformCoord(&po2, &po1, &trans);
			vertex3D[i].x = po2.x; vertex3D[i].y = po2.y; vertex3D[i].z = po2.z;
			
			vertex3D[i].norX = polgon3D[i].norX;
			vertex3D[i].norY = polgon3D[i].norY;
			vertex3D[i].norZ = polgon3D[i].norZ;
		}
		DefaultColUV_3D( &vertex3D[0], this->alpha );
	}
	#pragma endregion

	//----------------------------------------------------------------------------------------
	//頂点座標を直接セットして、色UVはデフォルト
	//----------------------------------------------------------------------------------------
	//@in : 左上座標
	//@in : 右上座標
	//@in : 左下座標
	//@in : 右下座標
	void Artisan::TransVertex(RCVector2 lup,RCVector2 rup,RCVector2 lbot,RCVector2 rbot)
	{
		::D3DXMatrixIdentity(&trans);

		this->vertex[0].x = rup.x;		this->vertex[0].y = rup.y;		this->vertex[0].z = 0.0f;
		this->vertex[1].x = rbot.x;	this->vertex[1].y = rbot.y;	this->vertex[1].z = 0.0f;
		this->vertex[2].x = lup.x;		this->vertex[2].y = lup.y;		this->vertex[2].z = 0.0f;
		this->vertex[3].x = lbot.x;	this->vertex[3].y = lbot.y;	this->vertex[3].z = 0.0f;

		DefaultColUV(&this->vertex[0], this->alpha);
	}
	
	//------------------------------------------------------------------------------------
	//三角形として頂点座標を直接セットして、色UVはデフォルト（画面パリーンｯをするため用）
	//------------------------------------------------------------------------------------
	//@in : 左上座標
	//@in : 右上座標
	//@in : 残り三角形座標
	void Artisan::TransTriangle(RCVector2 lup,RCVector2 rup,RCVector2 rbot)
	{
		::D3DXMatrixIdentity(&trans);

		this->vertex[0].x = rup.x;		this->vertex[0].y = rup.y;		this->vertex[0].z = 0.0f;
		this->vertex[1].x = rbot.x;	this->vertex[1].y = rbot.y;	this->vertex[1].z = 0.0f;
		this->vertex[2].x = lup.x;		this->vertex[2].y = lup.y;		this->vertex[2].z = 0.0f;

		DefaultColUV(&this->vertex[0], this->alpha);
	}
	
	//------------------------------------------------------------------------------------
	//分割画像のUV割り当て（TEXTURE構造体に幅、高さ、分割幅数、分割高さ数入っているので）
	//割り当てたい番号を指定すればそのUVが完成する！
	//※ただしここでは最大アニメ番号が来ても除外せず、判定は外でするべし！
	//理由は二重判定防止
	//------------------------------------------------------------------------------------	
	
	//---------------------------------------------------
	//普通頂点変換
	//---------------------------------------------------
	//@in : 割り当て番号
	//@in : テクスチャ情報
	void Artisan::TransDivisionPoint(int num,PCTEXTUREH text)
	{
		float divW,divH;
		int sx,sy;

		Division(&divW, &divH, &sx, &sy, num, text->sumX, text->sumY, text->width, text->height);
		DefaultSetUV(&this->vertex[0], divW, divH, sx, sy, text->width, text->height);
	}
	
	//----------------------------------------------------------------------
	//自分で分割幅数、分割高さ数を決めて、割り当てたい番号を指定する
	//※ここでも最大アニメ番号の判定はせず！　外で判断！
	//----------------------------------------------------------------------
	//@in : 割り当て番号
	//@in : 横番号合計
	//@in : 縦番号合計
	//@in : テクスチャデータクラス
	void Artisan::TransModi(int num,int wnum,int hnum,PCTEXTUREH  text)
	{
		float divW,divH;
		int sx,sy;

		Division(&divW, &divH, &sx, &sy, num, wnum, hnum, text->width, text->height);
		DefaultSetUV(&this->vertex[0], divW, divH, sx, sy, text->width, text->height);
	}
	
	//-------------------------------------------------------------------------------------------
	//三角形としてUVを変換する。
	//幅、高さ、分割幅数、分割高さ数アニメ番号を自分で決める
	//modeは△系か▼系か
	//-------------------------------------------------------------------------------------------
	//@in : 割り当て番号
	//@in : 横番号合計
	//@in : 縦番号合計
	//@in : 幅
	//@in : 高さ
	//@in : ↑のmode参照
	void Artisan::TransTriangleModi(int num,int wnum,int hnum,int width,int height,bool IsUp)
	{
		float divW,divH;
		int sx,sy;

		Division(&divW, &divH, &sx, &sy, num, wnum, hnum, width, height);

		if(!IsUp)
		{
			vertex[0].u = ((divW * sx) + divW) / width;
			vertex[0].v = (divH * sy) / height;

			vertex[1].u = ((divW * sx) + divW * 0.5f) / width;
			vertex[1].v = ((divH * sy) + divH) / height;
		
			vertex[2].u = (divW * sx) / width;
			vertex[2].v = (divH * sy) / height;
		}
		else
		{
			vertex[0].u = (divW * sx) / width;
			vertex[0].v = ((divH * sy) + divH) / height;

			vertex[1].u = ((divW * sx) + divW * 0.5f) / width;
			vertex[1].v = ((divH * sy)) / height;
		
			vertex[2].u = ((divW * sx) + divW) / width;
			vertex[2].v = ((divH * sy) + divH) / height;
		}
	}
	
	//-------------------------------------------------------------
	//スクリーンの分割変換
	//(例)2人プレイの時に画面が横に２つ分かれる
	//-------------------------------------------------------------
	//@in : スクリーンの数
	//@in : 描画したいスクリーン番号
	void Artisan::TransScreenDivision(int screenSum, int screenNum)
	{
		switch( screenSum )
		{
			case 1:
				DirectSetUV( &vertex[0], 0,0, SCRW, 0, 0, SCRH, SCRW, SCRH);
				break;
			case 2:
				( screenNum == 0 ? DirectSetUV( &vertex[0], 0,0, SCRW_PERCENT(0.5f),0, 0,SCRH, SCRW_PERCENT(0.5f),SCRH) : 
									DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f),0, SCRW,0, SCRW_PERCENT(0.5f),SCRH, SCRW, SCRH) );
				break;
			case 3:
				switch( screenNum )
				{
					case 1:
						DirectSetUV( &vertex[0], 0,0, SCRW,0, 0,SCRH_PERCENT(0.5f), SCRW,SCRH_PERCENT(0.5f) );
						break;
					case 2:
						DirectSetUV( &vertex[0], 0,SCRH_PERCENT(0.5f), SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f), 0, SCRH, SCRW_PERCENT(0.5f), SCRH);
						break;
					case 3:
						DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f), SCRW,SCRH_PERCENT(0.5f), SCRW_PERCENT(0.5f), SCRH, SCRW, SCRH);
						break;
				}
				break;
			case 4:
				switch( screenNum )
				{
					case 1:
						DirectSetUV( &vertex[0], 0,0, SCRW_PERCENT(0.5f),0, 0,SCRH_PERCENT(0.5f), SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f));
						break;
					case 2:
						DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f),0, SCRW,0, SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f), SCRW,SCRH_PERCENT(0.5f));
						break;
					case 3:
						DirectSetUV( &vertex[0], 0,SCRH_PERCENT(0.5f),SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f),0,SCRH,SCRW_PERCENT(0.5f),SCRH);
						break;
					case 4:
						DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f),SCRW,SCRH_PERCENT(0.5f),SCRW_PERCENT(0.5f),SCRH,SCRW,SCRH);
						break;
				}
				break;
		}
	}

	//public----------------------------------------------------------------------------

	#pragma region コンストラクタ
	inline Artisan::Artisan() : alpha(0) , alphaFlag(false), vertexBuffer(NULL), shader( NULL ), Device(NULL)
	{
		memcpy( &vertex[0], &polgon[0], sizeof(ArtisanVT_2D) * 4 );
		memcpy( &vertex3D[0], &polgon3D[0], sizeof(ArtisanVT_3D) * 4 );
	}

	inline Artisan::~Artisan()
	{
		ES_SAFE_RELEASE( this->vertexBuffer );	
		ES_SAFE_DELETE( this->shader );
	}

	inline void Artisan::InitShader(LPCSTR pass)
	{
		if(Device == NULL)	return ;
		this->shader = new Shader();
		this->shader->InitShader( Device, pass );
		if( !this->shader->doingShader )
			ES_SAFE_DELETE( shader );
	}

	void Artisan::SetDrawShader(PTexture text)
	{
		Device->SetFVF(FVF_Artisan);
#ifdef SHADER_DRAWER
		if( !CHECK_NULL(this->shader) )
		{
			this->shader->Effect->SetMatrix( SHADER_MATRIX_WORLD_, &D3DXMATRIX() );
			this->shader->Effect->SetTexture( SHADER_TEX1_, text );
			this->shader->Effect->SetBool( SHADER_TEX_ABLE_, ( text != NULL ) );
			this->shader->Effect->CommitChanges();
		}
		else
			Device->SetTexture(0, text);
#else
		Device->SetTexture(0, text);					//テクスチャ
#endif
	}

	void Artisan::SetShader(Shader* in)
	{
		this->shader = in;
	}

	Shader* Artisan::GetShader() const
	{
		return this->shader;
	}
	#pragma endregion

	void Artisan::SetScreenTrans(RenderScreen* sc)
	{
		this->TransScreenDivision( sc->screenSum, sc->screenNum );
		this->SetColor( &sc->color.color );
	}

	//----------------------------------------------------------------
	//頂点バッファを格納
	//----------------------------------------------------------------
	bool Artisan::SetVertexBuffer()
	{
		if(Device == NULL)
			return false;

		//板ポリを制作
		if(FAILED(Device->CreateVertexBuffer(
					sizeof(ArtisanVT_2D) * 4,	D3DUSAGE_WRITEONLY,
					FVF_Artisan,				D3DPOOL_MANAGED,
					&this->vertexBuffer,	NULL)))
		{
					return false;
		}

		void *pData;
		if(SUCCEEDED(this->vertexBuffer->Lock(0, sizeof(ArtisanVT_2D) * 4,
										(void**)&pData,0)))
		{
			memcpy(pData, vertex, sizeof(ArtisanVT_2D) * 4);
			this->vertexBuffer->Unlock();
			return true;
		}
		return false;
	}
	
	//---------------------------------------------
	//プロジェクションの設定
	//---------------------------------------------
	//@in : プロジェクション行列
	inline void Artisan::SetProjection(PCMATRIX p)
	{	
		this->proj = (*p);	

#ifdef SHADER_DRAWER
		if( this->shader != NULL)
			this->shader->Effect->SetMatrix( SHADER_MATRIX_PROJ_, p );
#endif
	}

	//--------------------------------------------------------------------------------------------------------------------
	// 行列に変換
	//--------------------------------------------------------------------------------------------------------------------
	//@in : 変換位置
	//@in : 変換拡大縮小
	//@in : 変換角度
	//@in : テクスチャデータクラス
	//@in : カラー情報
	//@in : スケールモード
	D3DXMATRIX Artisan::Transform(RCVector2 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,int mode)
	{
		D3DXMATRIX p,r,ps;
		::D3DXMatrixTranslation(&p, pos.x, pos.y, 0.0f);	//位置の行列
		::D3DXMatrixRotationZ(&r, angle);					//回転の行列
		switch(mode)	//拡大の行列
		{	
			case GRAPH_SCALE:	//デフォルトの画像変換
				::D3DXMatrixScaling(&ps, scale.x * (float)text->width, scale.y * (float)text->height, 1.0f);
				break;
			case DIV_SCALE:	//アニメーション画像等分割用変換
				::D3DXMatrixScaling(&ps, scale.x * (float)(text->width / text->sumX), scale.y * (float)(text->height / text->sumY), 1.0f);
				break;
			default://直代入
				::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		}

		this->SetColor(color);
		return this->trans = ((ps * r *  p));
	}

	//--------------------------------------------------------------------------------------------------------------------
	// 行列に変換
	//--------------------------------------------------------------------------------------------------------------------
	//@in : 変換位置
	//@in : 変換拡大縮小
	//@in : 変換角度
	D3DXMATRIX Artisan::Transform(RCVector2 pos, RCVector2 scale, float angle)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos.x, pos.y, 0.0f);	//位置の行列
		::D3DXMatrixRotationZ(&r, angle);					//回転の行列
		::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		
		return this->trans = ((ps * r *  p));
	}

	//--------------------------------------------------------------------------------------------------------------------
	// 行列に変換
	//--------------------------------------------------------------------------------------------------------------------
	//@in : 変換位置
	//@in : 変換拡大縮小
	//@in : 変換角度
	//@in : フォントデータクラス
	//@in : カラー情報
	//@in : スケールモード
	D3DXMATRIX Artisan::TransformW(RCVector2 pos, RCVector2 scale, float angle,MyFont* text,PCVector4 color,int mode)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos.x, pos.y, 0.0f);	//位置の行列
		::D3DXMatrixRotationZ(&r, angle);					//回転の行列
		::D3DXMatrixScaling(&ps, scale.x * (float)(text->GetFont()->fontW), scale.y * (float)(text->GetFont()->fontH), 1.0f);

		this->SetColor(color);
		return this->trans = ((ps * r * p));
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//３Ｄ空間上に表示
	//---------------------------------------------------------------------------------------------------------------------------
	//@in : 変換位置
	//@in : 変換拡大縮小
	//@in : 変換角度
	//@in : テクスチャデータクラス
	//@in : カラー情報
	//@in : スケールモード
	D3DXMATRIX Artisan::Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCTEXTUREH text,PCVector4 color,int mode)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos->x, pos->y, pos->z);	//位置の行列
		::D3DXMatrixRotationZ(&r, angle->z);					//回転の行列
		switch(mode)
		{	//拡大の行列
			case GRAPH_SCALE:	//デフォルトの画像変換
				::D3DXMatrixScaling(&ps, scale.x * (float)text->width, scale.y * (float)text->height, 1.0f);
				break;
			case DIV_SCALE:	//アニメーション画像等分割用変換
				::D3DXMatrixScaling(&ps, scale.x * (float)(text->width / text->sumX), scale.y * (float)(text->height / text->sumY), 1.0f);
				break;
			default://直代入
				::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		}

		this->SetColor(color);
		return this->trans = ((ps * r *  p));
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//３Ｄ空間上に表示(ビルボード)
	//---------------------------------------------------------------------------------------------------------------------------
	//@in : 変換位置
	//@in : 変換拡大縮小
	//@in : 変換角度
	//@in : テクスチャデータクラス
	//@in : カラー情報
	//@in : ビルボード行列
	//@in : スケールモード
	D3DXMATRIX Artisan::Transform3D_ofBillboard(PCVector3 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,PCMATRIX board,int mode)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos->x, pos->y, pos->z);	//位置の行列
		::D3DXMatrixRotationZ(&r, angle);					//回転の行列
		switch(mode)
		{	//拡大の行列
			case GRAPH_SCALE:	//デフォルトの画像変換
				::D3DXMatrixScaling(&ps, scale.x * (float)text->width, scale.y * (float)text->height, 1.0f);
				break;
			case DIV_SCALE:	//アニメーション画像等分割用変換
				::D3DXMatrixScaling(&ps, scale.x * (float)(text->width / text->sumX), scale.y * (float)(text->height / text->sumY), 1.0f);
				break;
			default://直代入
				::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		}

		this->SetColor(color);
		return this->trans = (( ps * r * (*board) * p));
	}

	//-----------------------------------------------
	//カラー情報のセット
	//-----------------------------------------------
	//@in : カラー情報
	void Artisan::SetColor(PCVector4 color)
	{	//カラーだけセットしたいときにこれ！
		this->alpha = ((((int)color->x) & 0xff) << 24) + ((((int)color->y) & 0xff) << 16) + 
				((((int)color->z) & 0xff) << 8) + ((((int)color->w) & 0xff)); 
		this->SetShaderColor( color );
	}

	//-----------------------------------------------
	//シェーダー上でカラー情報のセット
	//-----------------------------------------------
	//@in : カラー情報
	void Artisan::SetShaderColor(PCVector4 color)
	{
		if( this->shader != NULL )
		{
#ifdef SHADER_DRAWER
			D3DMATERIAL9 mt = {};
			mt.Ambient.a = ( color->x <= 1.0f ? 0.0f : (int)(color->x) / 255);
			mt.Ambient.r = ( color->y <= 1.0f ? 0.0f : (int)(color->y) / 255);
			mt.Ambient.g = ( color->z <= 1.0f ? 0.0f : (int)(color->z) / 255);
			mt.Ambient.b = ( color->w <= 1.0f ? 0.0f : (int)(color->w) / 255);
			this->shader->Effect->SetFloatArray( SHADER_MATERIAL_, (float*)(&mt), 17 );
#endif
		}
	}

	//-----------------------------------------------
	//8bit(rgba)のカラー情報に変換して設定
	//-----------------------------------------------
	//@in : カラー情報
	void Change8BitColor(ArtisanVT_2D* vertex, PCVector4 col)
	{
		UINT al = ((((int)col->x) & 0xff) << 24) + ((((int)col->y) & 0xff) << 16) + 
				((((int)col->z) & 0xff) << 8) + ((((int)col->w) & 0xff));
		vertex->dwColor = al;
	}

	//-----------------------------------------------
	//8bit(rgba)のカラー情報に変換して設定
	//-----------------------------------------------
	//@in : 左上カラー情報
	//@in : 右上カラー情報
	//@in : 左下カラー情報
	//@in : 右下カラー情報
	void Artisan::Set8BitColor(PCVector4 lup, PCVector4 rup, PCVector4 lbot, PCVector4 rbot)
	{
		Change8BitColor( &this->vertex[0], rup );
		Change8BitColor( &this->vertex[1], rbot );
		Change8BitColor( &this->vertex[2], lup );
		Change8BitColor( &this->vertex[3], lbot );
	}
	
	//-------------------------------------------------------------------------------------------------

	//------------------------------------------------
	//DirectX用テクスチャを直設定して描画
	//------------------------------------------------
	//@in : DirectX用テクスチャ
	void Artisan::DrawVertexBuffer(PTexture text)
	{
		if( Device == NULL || CHECK_NULL(text) ) return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text );

		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//描画
	}

	//--------------------------------------------------------
	//設定し終えた状態で後は画像を描画するだけの時はこれ！
	//--------------------------------------------------------
	//@in : テクスチャ情報
	void Artisan::DrawVertexBuffer(PCTEXTUREH text)
	{
		if( Device == NULL || CHECK_NULL(text->graph) ) return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//描画
	}

	//--------------------------------------------------------
	//フォント情報の描画
	//--------------------------------------------------------
	//@in : フォントテクスチャ情報
	void Artisan::DrawVertexBuffer(PMyFont text)
	{
		if(Device == NULL || CHECK_NULL(text))	return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);	//２Dカスタムにチェンジ
		this->SetDrawShader( text->GetFont()->fontText );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//描画
	}

	//--------------------------------------------------------
	//スクリーン全体の描画
	//--------------------------------------------------------
	void Artisan::DrawVertexWall()
	{
		if( Device == NULL ) return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( NULL );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//描画
	}

	//--------------------------------------------------------
	//スクリーン全体の描画
	//--------------------------------------------------------
	//@in : テクスチャ情報
	void Artisan::DrawScreen(PTexture text)
	{
		if( Device == NULL || CHECK_NULL(text) ) return ;
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//描画
	}

	//--------------------------------------------------------
	//3D空間上の描画
	//--------------------------------------------------------
	void Artisan::DrawVertexGraph_3D(PCTEXTUREH text)
	{
		if(Device == NULL || CHECK_NULL(text))	return ;
		this->TransWorld();
		Device->SetFVF( FVF_Artisan3 );
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, this->vertex3D, sizeof(ArtisanVT_3D) );
	}
	
	//--------------------------------------------------------------------------
	//設定し終えた状態でアニメ画像の番号を設定するだけでアニメーション可能に！
	//分割描画
	//--------------------------------------------------------------------------
	//@in : テクスチャ情報
	//@in : 割り当て番号
	void Artisan::DrawVertexBufferIndex(PCTEXTUREH text, int number)
	{
		if( Device == NULL || CHECK_NULL(text) || !text->division)	return ;	
		this->TransNormal();
		this->TransDivisionPoint(number, text);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));
	}

	//---------------------------------------------------------------------------------
	//自分で頂点座標を設定して、且つ分割幅も設定、そしてアニメーション番号を入れて描画
	//直接弄りたい用
	//---------------------------------------------------------------------------------
	//@in : テクスチャ情報
	//@in : 左上座標
	//@in : 右上座標
	//@in : 左下座標
	//@in : 右下座標
	void Artisan::DrawVertexBufferIndexModi(PCTEXTUREH text,RCVector2 p1,
											RCVector2 p2,RCVector2 p3,RCVector2 p4,
												int number, int wnum, int hnum)
	{
		if(Device == NULL || CHECK_NULL(text) || wnum == 0 || hnum == 0)	return ;
		this->TransVertex(p2,p1,p3,p4);
		this->TransModi(number, wnum, hnum, text);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));
	}

	//-------------------------------------------------------------------
	//自分で頂点座標を設定して、そしてアニメーション番号を入れて描画
	//アニメーション幅はデフォルトになります
	//-------------------------------------------------------------------
	//@in : 左上座標
	//@in : 右上座標
	//@in : 左下座標
	//@in : 右下座標
	//@in : 割り当て番号
	//@in : テクスチャ情報
	void Artisan::DrawRectDepGraph(RCVector2 lup,RCVector2 rup,RCVector2 lbot,
								RCVector2 rbot,int num,PCTEXTUREH  text)
	{
		if(Device == NULL || CHECK_NULL(text) || !text->division)	return ;	
		this->TransVertex(lup,rup,lbot,rbot);
		this->TransDivisionPoint(num, text);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));
	}

	//-------------------------------------------------------------------------------------------------------------------------
	//頂点座標、最大幅高さ、分割幅高さ、割り当て番号等
	//画面を割るためだけにあるメソッド
	//-------------------------------------------------------------------------------------------------------------------------
	//@in : テクスチャ情報
	//@in : 左上座標
	//@in : 右上座標
	//@in : 左下座標
	//@in : 割り当て番号
	//@in : 分割横合計数
	//@in : 分割縦合計数
	//@in : 幅
	//@in : 高さ
	//@in : モード
	void Artisan::DrawIndexGlassHopper(PTexture text, RCVector2 p1,
										RCVector2 p2,RCVector2 p3,int number, int wnum, int hnum,int width,int height,bool IsUp)
	{
		if(Device == NULL || CHECK_NULL(text) || wnum == 0 || hnum == 0)	return ;
		this->TransTriangle(p2,p1,p3);
		this->TransTriangleModi(number, wnum, hnum, width, height,IsUp);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, vertex, sizeof(ArtisanVT_2D));
	 }
	
	//D3DXMATRIX mat1,mat2,mat3;
	//	Device->GetTransform(D3DTS_VIEW, &mat1);
	//	Device->GetTransform(D3DTS_PROJECTION, &mat2);
	//	D3DXMatrixInverse(&mat3, NULL, &(mat1 * mat2));
	//	
	//	//::D3DXMatrixIdentity(&mat2);
	//	//mat2 = mat1 * mat2;
	//	//D3DXMatrixInverse(&mat2, NULL, &mat1);
	//	//Device->SetTransform(D3DTS_VIEW, &mat3);
	//	
	//	evice->SetStreamSource(0,this->vertexBuffer, 0, sizeof(ArtisanVT_2D));
	//	Device->SetFVF(FVF_Artisan);
	//	Device->SetTransform(D3DTS_WORLD, &(this->trans));			//変換行列
	//	Device->SetTexture(0, text.graph);					//テクスチャ
	//	//Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//Device->SetTransform(D3DTS_VIEW, &mat3);

	//------------------------------------------------
	//アルファモードのセッティング
	//------------------------------------------------
	void Artisan::SetAlphaMode(COLOR_BLEND_NUM mode,DWORD dwal)
	{
		if( Device == NULL )	return ;
		switch(mode)
		{
			case 1:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:
			case 9:	case 10: case 11: case 12:
				Device->SetRenderState( D3DRS_ZENABLE, TRUE );						//zテスト有効
				Device->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				//アルファテスト有効
				Device->SetRenderState( D3DRS_ALPHAREF, 0x01 );						//アルファ参照値
				Device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL  );		//アルファテスト基準
				break;
			case 2:
				Device->SetRenderState( D3DRS_ZENABLE, FALSE );						//zテスト無効
				Device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );				//アルファテスト無効
				break;
		}

		switch(mode)
		{
			case BLEND_ALPHA1:	//普通のアルファブレンド
				//普通のアルファ
				Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );				//アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );			//加算合成
				Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//SRCの設定
				Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//DESTの設定
				break;
			case BLEND_ADD1: //デフォルト加算合成
				Device->SetRenderState( D3DRS_ALPHABLENDENABLE,TRUE);				//アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );			//加算合成
				Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE);				//SRCの設定
				Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);				//DESTの設定
				break;
			case BLEND_ALPHA2:	//不透明
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);					//アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA  );			//SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA  );			//DESTの
				break;
			case BLEND_FACTOR1:	//自由ブレンド
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);        //アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);   //ブレンドファクターの値
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);   //ブレンドファクターの逆の値
				Device->SetRenderState(D3DRS_BLENDFACTOR,dwal);          //ブレンディング係数の設定

				/*
					元画像(argb) - dwal(argb)
					入画像(argb) を dwal(argb)　に改造して変換
				*/
				break;
			case BLEND_FACTOR2:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);        //アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVBLENDFACTOR);   //ブレンドファクターの値
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);   //ブレンドファクターの逆の値
				Device->SetRenderState(D3DRS_BLENDFACTOR,dwal);          //ブレンディング係数の設定
				/*
					入画像(argb) - dwal(argb)
					元画像(argb) を dwal(argb)　に改造して変換
				*/
				
				break;
			case BLEND_SUB1:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);//DESTの設定
				break;
			case BLEND_COLORADD1:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);//DESTの設定
				break;
			case BLEND_ALPHA3:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);//DESTの設定
				break;
			case BLEND_SUB2:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);//DESTの設定
				break;
			case BLEND_BLACK:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);//DESTの設定
				break;
			case BLEND_SUB3:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);//DESTの設定
				break;
			case BLEND_BLACK2:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//DESTの設定
				break;
			case 13:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //アルファブレンディングの有効化
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);//DESTの設定
				break;
			case 14:	//半加算合成
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//アルファブレンディングの有効化
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);			//SRCの設定
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//DESTの
				break;
			default:
				Device->SetRenderState( D3DRS_ZENABLE, TRUE );
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);		//あルふぁブレンドの無効
				Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//アルファテストの無効
				break;
		}
	}

	//-----------------------------------------
	//デバイスをセットする
	//-----------------------------------------
	void Artisan::SetDevice(PDirectDevice Device)
	{
		this->Device = Device;
	}
	
	//------------------------------
	//変換行列の初期化
	//------------------------------
	void Artisan::InitMatrix()
	{
		this->trans = D3DXMATRIX();
	}

}