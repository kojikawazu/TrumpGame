#ifndef MYDIRECTX_LIGHTCOLOR_H
#define MYDIRECTX_LIGHTCOLOR_H

//----------------------------------------------------------
//
//ライトと色クラスをここに格納
//
//----------------------------------------------------------
#ifndef _NanairoLib_MYVECTOR_H
#include <DirectParts.h>
#endif

//DXライトとカラークラス
namespace NanairoLib
{
	//---------------------------------
	//DXライト
	//固定パイプライン用ライト
	//---------------------------------
	class Light
	{
		private:	
			D3DLIGHT9 lighting;		//DXライト構造体
			short number,mode;		//DXライト番号、デフォルトセット番号

		public:		
			//----------------------------------------------------
			//コンストラクタ
			//----------------------------------------------------
			//@in : ライト番号
			//@in : デフォルト設定番号
			__IMPOETER		Light(int num,int mode = 1);
			__IMPOETER		Light();
			__IMPOETER		~Light();
		
		public:		
			//-----------------------------------------------------
			//設定・取得
			//-----------------------------------------------------
			//@in : DirectX用デバイス
			__IMPOETER		void Setlighting(PDirectDevice Device);
			__IMPOETER		D3DLIGHT9* GetLight();
	};
	
	//---------------------------------
	//テクスチャの色
	//(argb指定)
	//---------------------------------
	class Textcolor
	{
		public:	
			//-----------------------------------
			//色情報
			//(x : a) (y : r) (z : g) (w : b)
			//-----------------------------------
			Vector4 color, target;

		public:	
			//--------------------------------------------
			//ﾃﾞｺﾝ系
			//--------------------------------------------
			__IMPOETER		Textcolor();
			__IMPOETER		Textcolor(const Vector4* col);
			__IMPOETER		Textcolor(float da, float dr, float dg, float db);
			__IMPOETER		~Textcolor();

		public:	
			//-----------------------------------------------
			//コピー
			//-----------------------------------------------
			__IMPOETER Textcolor& operator = (const Textcolor* col);
			__IMPOETER Textcolor& operator = (const Textcolor col);
			__IMPOETER Textcolor& operator = (Vector4 col);	//コピー
			__IMPOETER Textcolor& operator = (PCVector4 col);	//コピー

			//----------------------------------------------------------------------
			//減算処理
			//----------------------------------------------------------------------
			__IMPOETER Textcolor operator - (int a);	//対象の値を減らす
			__IMPOETER Textcolor operator - (PCVector4 col);	//カラーを減らす
			__IMPOETER Textcolor& operator -= (int a);	//対象の値を減らす
			__IMPOETER Textcolor& operator -= (PCVector4 col);	//対象の値を減らす

			//----------------------------------------------------------------------
			//加算処理
			//----------------------------------------------------------------------
			__IMPOETER Textcolor operator + (int a);	//対象の値を増やす
			__IMPOETER Textcolor operator + (PCVector4 col);	//カラーを増やす
			__IMPOETER Textcolor& operator += (int a);	//対象の値を減らす
			__IMPOETER Textcolor& operator += (PCVector4 col);	//対象の値を減らす

			//----------------------------------------------------------------------
			//減算処理
			//----------------------------------------------------------------------
			__IMPOETER Textcolor& operator -- (int a);	//1減らす
			
			//----------------------------------------------------------------------
			//加算処理
			//----------------------------------------------------------------------
			__IMPOETER Textcolor& operator ++ (int a);	//1増やす
			
			//----------------------------------------------------------------------
			//合成処理
			//----------------------------------------------------------------------
			__IMPOETER void operator * (PCVector4 col);
			
			//----------------------------------------------------------------------
			//除算処理
			//----------------------------------------------------------------------
			__IMPOETER void operator / (PCVector4 col);

		public:	//設定・取得
			//----------------------------------------------------------------------
			//カラーのセッティング
			//----------------------------------------------------------------------
			__IMPOETER void SetColor(int a,int r,int g,int b);
			__IMPOETER void SetMaxColor();
			__IMPOETER void SetMinColor();
			__IMPOETER void SetColor(PCVector4 col);
			__IMPOETER void SetAlpha(int a);
			
			//----------------------------------------------------------------------
			//カラーの取得
			//----------------------------------------------------------------------
			__IMPOETER float GetColor(int mode);
			__IMPOETER Vector4 GetColor();
			__IMPOETER float GetAlpha();

			//----------------------------------------------------------------------
			//カラーのフェードイン
			//----------------------------------------------------------------------
			__IMPOETER bool FadeIn(float al);
			__IMPOETER bool FadeIn(PCVector4 col);

			//----------------------------------------------------------------------
			//カラーのフェードアウト
			//----------------------------------------------------------------------
			__IMPOETER bool FadeOut(float al);
			__IMPOETER bool FadeOut(PCVector4 col);
			
			//----------------------------------------------------------------------
			//カラーのフェードするためのセッティング
			//----------------------------------------------------------------------
			__IMPOETER void SettingFadeAlpha();
			__IMPOETER void SettingTextcolor();
	};

	typedef Textcolor*			PColor;
	typedef const Textcolor*	PCColor;
}
#endif