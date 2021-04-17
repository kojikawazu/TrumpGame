#ifndef NanairoLib_GRAPH_H
#define NanairoLib_GRAPH_H

#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

//----------------------------------------------------------
//２D画像を専用板ポリに貼って描画するクラス
//----------------------------------------------------------
namespace NanairoLib
{

	class MyGraph
	{
		private:
			TEXTUREH	parts;
			Vector4		color;
			Artisan*	 art;

		private:
			//------------------------------
			//初期化
			//------------------------------
			__IMPOETER void sameInit();
		public:
			__IMPOETER MyGraph();
			__IMPOETER MyGraph(PTEXTUREH handle);
			__IMPOETER ~MyGraph();
		
			Artisan* GetArtisan() const{		return this->art;		}
			void SetArtisan(Artisan* in){	this->art = in;	}

		public:
			//----------------------------------------------------------------
			//テクスチャのセッティング
			//----------------------------------------------------------------
			//@in : テクスチャ
			//@in : 幅
			//@in : 高さ
			__IMPOETER void SetTexture(IDirect3DTexture9* gh, float wh, float ht);
			
			//----------------------------------------------
			//分割のセッティング
			//----------------------------------------------
			//@in : 分割横数
			//@in : 分割縦数
			__IMPOETER void SetDivision(int divX = 1, int divY = 1);

			//----------------------------------------------
			//ロードテクスチャ
			//----------------------------------------------
			//@in : DirectX用デバイス
			//@in : ファイルパス
			//@in : 幅
			//@in : 高さ
			//@in : 分割横数
			//@in : 分割縦数
			__IMPOETER bool LoadTexture(PDirectDevice Device,LPCSTR fileName,int width,int height,int sumW = 0,int sumH = 0);
			
			//----------------------------------------------
			//テクスチャのリリース
			//----------------------------------------------
			__IMPOETER void ReleaseTexture();
	
		public:
			//----------------------------------------------
			//テクスチャハンドルの取得
			//----------------------------------------------
			//@out : テクスチャハンドル
			__IMPOETER PCTEXTUREH GetTextureHandle();

			//----------------------------------------------
			//テクスチャハンドルポインタの取得
			//----------------------------------------------
			//@out : テクスチャハンドル
			__IMPOETER PTEXTUREH GetTexturePointer();

			//----------------------------------------------
			//テクスチャの取得
			//----------------------------------------------
			//@out : DirectX用テクスチャ
			__IMPOETER const IDirect3DTexture9* GetTexture();

			//----------------------------------------------
			//カラーの取得
			//----------------------------------------------
			__IMPOETER PCVector4 GetColor();

			//----------------------------------------------
			//カラーのセッティング
			//----------------------------------------------
			//@in : argb
			__IMPOETER void SetColor(float a, float r, float g, float b);
			__IMPOETER void SetColor(PCVector4 col);

			//----------------------------------------------
			//テクスチャの普通に描画
			//----------------------------------------------
			//@in : 描画専用クラス
			__IMPOETER void Draw_Graph(Artisan* Artisan);
			
			//----------------------------------------------
			//テクスチャのアニメーション描画
			//----------------------------------------------
			//@in : 描画専用クラス
			//@in : 割り当て番号
			__IMPOETER void Draw_Animation_Graph(int number);

			//----------------------------------------------
			//テクスチャの直座標設定・直分割描画
			//----------------------------------------------
			//@in : 描画専用クラス
			//@in : 四角の座標ベクトル
			//@in : 分割横数
			//@in : 分割縦数
			//@in : 割り当て番号
			__IMPOETER void Draw_Modi_div_Animation_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number, int divXSum, int divYSum);
			
			//----------------------------------------------
			//テクスチャの直座標設定・アニメーション描画
			//----------------------------------------------
			//@in : 描画専用クラス
			//@in : 四角の座標ベクトル
			//@in : 割り当て番号
			__IMPOETER void Draw_Modi_Animation_Graph( RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number);
			
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
			__IMPOETER void Draw_Grass_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot,int number, int divXSum, int divYSum, int width, int height, bool IsUp);

			//----------------------------------------------
			//描画のトランスフォーム
			//----------------------------------------------
			//@in : 描画専用クラス
			//@in : 位置
			//@in : スケール
			//@in : 角度
			//@in : 色情報
			//@in : スケールモード
			__IMPOETER void Transform(RCVector2 pos, RCVector2 scale, float angle,PCVector4 color,int mode);
			
			//----------------------------------------------
			//描画のトランスフォーム(3D用)
			//----------------------------------------------
			//@in : 描画専用クラス
			//@in : 位置
			//@in : スケール
			//@in : 角度
			//@in : 色情報
			//@in : スケールモード
			__IMPOETER void Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCVector4 color,int mode);
			
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
			__IMPOETER void TransformBillboard(PCVector3 pos, RCVector2 scale, float angle,PCVector4 color, PCMATRIX board, int mode);
	};
	
}
#endif