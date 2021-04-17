#ifndef NanairoLib_VERTEX_H
#define NanairoLib_VERTEX_H

#ifndef RESOURCE_FUNCTION_H
#include <ResourceFunction.h>
#endif

#ifndef MYRIECTX_RENDER_H
#include <RenderScreen.h>
#endif

#ifndef NanairoLib_MYFONT
#include <DirectFont.h>
#endif

//----------------------------------------------------------
//２D画像を専用板ポリに貼って描画するクラス
//----------------------------------------------------------
namespace NanairoLib
{
	//---------------------------------------------------
	//描画用インプットモード
	//---------------------------------------------------
	#define BACK_FVF		(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)
	#define FVF_Artisan3		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	#define FVF_Artisan		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

	//---------------------------------------------------
	//クリアしたいバッファの種類
	//---------------------------------------------------
	#define CLEAR_FVF_3D_1	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER)
	#define CLEAR_FVF_3D_2	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL)
	#define CLEAR_FVF_2D	(D3DXSPRITE_SORT_DEPTH_BACKTOFRONT | D3DXSPRITE_ALPHABLEND)

	//-------------------------------------------------------
	//DirectX用シェーダ
	//-------------------------------------------------------
	class Shader
	{
		public:
			LPD3DXEFFECT Effect;
			D3DXHANDLE texhandle;
			D3DXMATRIX matWorldProj;
			D3DXHANDLE hMatWorldProj;
			bool doingShader;
		
		public:
			//デコン系
			__IMPOETER Shader();
			__IMPOETER ~Shader();

			//----------------------------------------------
			//シェーダー初期化
			//----------------------------------------------
			//@in : DirectX用デバイス
			__IMPOETER void InitShader(IDirect3DDevice9 *Device, LPCSTR pass);

	};
	
	typedef Shader*			PShader;
	typedef const Shader*	PCShader;

	//--------------------------------------------------------
	//板ポリ画像セット・描画クラス
	//--------------------------------------------------------
	class Artisan
	{
		private:	//メソッドは見れないよ＞＜
			PDirectDevice		Device;
			PVertexBuffer		vertexBuffer;
			Shader*				shader;
			ArtisanVT_2D			vertex[4];
			ArtisanVT_3D			vertex3D[4];
			D3DXMATRIX			trans, proj;
			UINT				alpha;
			bool				alphaFlag;

		private:	//内部制御
			//-------------------------------------------------------
			//普通に中心をセットして変換行列で変換、色UVはデフォルト	
			//-------------------------------------------------------
			__IMPOETER void TransNormal();	
			__IMPOETER void TransWorld();
			__IMPOETER void SetDrawShader(PTexture text);

			//----------------------------------------------------------------------------------------
			//頂点座標を直接セットして、色UVはデフォルト
			//----------------------------------------------------------------------------------------
			//@in : 左上座標
			//@in : 右上座標
			//@in : 左下座標
			//@in : 右下座標
			__IMPOETER void TransVertex(RCVector2 lup,RCVector2 rup,RCVector2 lbot,RCVector2 rbot);

			//------------------------------------------------------------------------------------
			//三角形として頂点座標を直接セットして、色UVはデフォルト（画面パリーンｯをするため用）
			//------------------------------------------------------------------------------------
			//@in : 左上座標
			//@in : 右上座標
			//@in : 残り三角形座標
			__IMPOETER void TransTriangle(RCVector2 lup,RCVector2 rup,RCVector2 rbot);

			//---------------------------------------------------
			//普通頂点変換
			//分割画像のUV割り当て（TEXTURE構造体に幅、高さ、分割幅数、分割高さ数入っているので）
			//割り当てたい番号を指定すればそのUVが完成する！
			//---------------------------------------------------
			//@in : 割り当て番号
			//@in : テクスチャ情報
			__IMPOETER void TransDivisionPoint(int num,PCTEXTUREH  text);
			
			//----------------------------------------------------------------------
			//自分で分割幅数、分割高さ数を決めて、割り当てたい番号を指定する
			//※ここでも最大アニメ番号の判定はせず！　外で判断！
			//----------------------------------------------------------------------
			//@in : 割り当て番号
			//@in : 横番号合計
			//@in : 縦番号合計
			//@in : テクスチャデータクラス
			__IMPOETER void TransModi(int num,int wnum,int hnum,PCTEXTUREH  text);

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
			__IMPOETER void TransTriangleModi(int num,int wnum,int hnum,int width,int height,bool IsUp);
			
			//-------------------------------------------------------------
			//スクリーンの分割変換
			//(例)2人プレイの時に画面が横に２つ分かれる
			//-------------------------------------------------------------
			//@in : スクリーンの数
			//@in : 描画したいスクリーン番号
			__IMPOETER void TransScreenDivision(int screenSum, int screenNum);
		public:
			//ﾃﾞｺﾝ系
			__IMPOETER Artisan();
			__IMPOETER ~Artisan();

			//シェーダを使いたい時は↓のメソッドで初期化
			__IMPOETER void InitShader(LPCSTR pass);
			__IMPOETER void SetShader(Shader* in);
			__IMPOETER Shader* GetShader() const;

		public:
			__IMPOETER void SetScreenTrans(RenderScreen* sc); 

			//----------------------------------------------------------------
			//頂点バッファを格納
			//----------------------------------------------------------------
			__IMPOETER bool SetVertexBuffer();

			//--------------------------------------------------------------------------------------------------------------------
			// 行列に変換
			//--------------------------------------------------------------------------------------------------------------------
			//@in : 変換位置
			//@in : 変換拡大縮小
			//@in : 変換角度
			//@in : テクスチャデータクラス
			//@in : カラー情報
			//@in : スケールモード
			__IMPOETER D3DXMATRIX Transform(RCVector2 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,int mode = 0);
			
			//--------------------------------------------------------------------------------------------------------------------
			// 行列に変換
			//--------------------------------------------------------------------------------------------------------------------
			//@in : 変換位置
			//@in : 変換拡大縮小
			//@in : 変換角度
			__IMPOETER D3DXMATRIX Transform(RCVector2 pos, RCVector2 scale, float angle);
			
			//--------------------------------------------------------------------------------------------------------------------
			// 行列に変換
			//--------------------------------------------------------------------------------------------------------------------
			//@in : 変換位置
			//@in : 変換拡大縮小
			//@in : 変換角度
			//@in : フォントデータクラス
			//@in : カラー情報
			//@in : スケールモード
			__IMPOETER D3DXMATRIX TransformW(RCVector2 pos, RCVector2 scale, float angle,PMyFont text,PCVector4 color,int mode = 0);
			
			//---------------------------------------------------------------------------------------------------------------------------
			//３Ｄ空間上に表示
			//---------------------------------------------------------------------------------------------------------------------------
			//@in : 変換位置
			//@in : 変換拡大縮小
			//@in : 変換角度
			//@in : テクスチャデータクラス
			//@in : カラー情報
			//@in : スケールモード
			__IMPOETER D3DXMATRIX Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCTEXTUREH text,PCVector4 color,int mode = 0);
			
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
			__IMPOETER D3DXMATRIX Transform3D_ofBillboard(PCVector3 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,PCMATRIX board,int mode = 0);

		
			//-----------------------------------------------
			//カラー情報のセット
			//-----------------------------------------------
			//@in : カラー情報
			__IMPOETER void SetColor(PCVector4 color);
			
			//-----------------------------------------------
			//シェーダー上でカラー情報のセット
			//-----------------------------------------------
			//@in : カラー情報
			__IMPOETER void SetShaderColor(PCVector4 color);
			
			//-----------------------------------------------
			//8bit(rgba)のカラー情報に変換して設定
			//-----------------------------------------------
			//@in : 左上カラー情報
			//@in : 右上カラー情報
			//@in : 左下カラー情報
			//@in : 右下カラー情報
			__IMPOETER void Set8BitColor(PCVector4 lup, PCVector4 rup, PCVector4 lbot, PCVector4 rbot);
			
			//---------------------------------------------
			//プロジェクションの設定
			//---------------------------------------------
			//@in : プロジェクション行列
			__IMPOETER void SetProjection(PCMATRIX p);
		public:
			//------------------------------------------------
			//DirectX用テクスチャを直設定して描画
			//------------------------------------------------
			//@in : DirectX用テクスチャ
			__IMPOETER void DrawVertexBuffer(PTexture text );
			
			//--------------------------------------------------------
			//設定し終えた状態で後は画像を描画するだけの時はこれ！
			//--------------------------------------------------------
			//@in : テクスチャ情報
			__IMPOETER void DrawVertexBuffer(PCTEXTUREH text);
			
			//--------------------------------------------------------
			//フォント情報の描画
			//--------------------------------------------------------
			//@in : フォントテクスチャ情報
			__IMPOETER void DrawVertexBuffer(PMyFont text);
			
			//--------------------------------------------------------
			//スクリーン全体の描画
			//--------------------------------------------------------
			__IMPOETER void DrawVertexWall();

			//--------------------------------------------------------
			//スクリーン全体の描画
			//--------------------------------------------------------
			__IMPOETER void DrawScreen(PTexture text);

			//--------------------------------------------------------------------------
			//設定し終えた状態でアニメ画像の番号を設定するだけでアニメーション可能に！
			//分割描画
			//--------------------------------------------------------------------------
			//@in : テクスチャ情報
			//@in : 割り当て番号
			__IMPOETER void DrawVertexBufferIndex(PCTEXTUREH text, int number);

			//---------------------------------------------------------------------------------
			//自分で頂点座標を設定して、且つ分割幅も設定、そしてアニメーション番号を入れて描画
			//直接弄りたい用
			//---------------------------------------------------------------------------------
			//@in : テクスチャ情報
			//@in : 左上座標
			//@in : 右上座標
			//@in : 左下座標
			//@in : 右下座標
			__IMPOETER void DrawVertexBufferIndexModi(PCTEXTUREH text, RCVector2 p1,
																	RCVector2 p2,RCVector2 p3,RCVector2 p4,
																		int number, int wnum, int hnum);

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
			__IMPOETER void DrawRectDepGraph(RCVector2 lup,RCVector2 rup,
														RCVector2 lbot,RCVector2 rbot,int num,PCTEXTUREH  text);
			
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
			__IMPOETER void DrawIndexGlassHopper(PTexture text, RCVector2 p1,
											RCVector2 p2,RCVector2 p3,int number, int wnum, int hnum,int width,int height,bool IsUp);
			
			//--------------------------------------------------------
			//3D空間上の描画
			//--------------------------------------------------------
			__IMPOETER void DrawVertexGraph_3D(PCTEXTUREH text);

		public:	//アルファ系
			//アルファブレンドのセット
			//1~14 がアルファブレンドモード
			//15はなしモード
			//------------------------------------------------
			//アルファモードのセッティング
			//------------------------------------------------
			__IMPOETER void SetAlphaMode(COLOR_BLEND_NUM mode = BNONE,DWORD dwal = 0x00888888);	
			
			//-----------------------------------------
			//デバイスをセットする
			//-----------------------------------------
			__IMPOETER void SetDevice(PDirectDevice Device);
			
			//------------------------------
			//変換行列の初期化
			//------------------------------
			__IMPOETER void InitMatrix();
	};

	typedef Artisan*			PArtisan;
	typedef const Artisan*	PCArtisan;

}
#endif