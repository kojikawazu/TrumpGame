#ifndef NanairoLib_MYFONT
#define NanairoLib_MYFONT
//------------------------------------------------------------
//DirectXで扱うフォント（1文字）を
//デバイスコンテキストでテクスチャにペイントするクラス
//------------------------------------------------------------
#ifndef RESOURCE_FUNCTION_H
#include <ResourceFunction.h>
#endif

namespace NanairoLib
{
	#define __WordFontType "メイリオ"

	//フォント構造体のフィールドを載せておきます
	//★フォントをペイントしてテクスチャ
	//★そのテクスチャの幅と高さ
	//typedef struct{
	//	int fontW,fontH;
	//	IDirect3DTexture9* fontText;	
	//}FONTH;

	//フォント（1文字）クラス
	//これをリストに入れて管理していく感じ！
	class MyFont
	{
		private:
			FONTH font;
			bool OKFlag;

		private:
			//------------------------------------------------------------------------------------
			//フォントを構築します
			//成功するとtrueが帰ってきます
			//しかしこれは内部での処理なので気にしなくてよし！
			__IMPOETER bool createFont(PDirectDevice Device,PCUINT cd);

		public:
			//フォントクラスを生成すると同時にフォントを作ります。
			//一度作ると変更はきかないので
			//変更あるときは他のポインタとしてnewして作ってください。
			//-----------------------------------------------------------------------------------
			__IMPOETER MyFont();
			__IMPOETER MyFont(PDirectDevice Device,PCUINT C);
			__IMPOETER ~MyFont();
			
			//取得タイプ--------------------------------------------------------------------------
			__IMPOETER PFONTH GetFont() const;
			__IMPOETER const bool isOK() const;
			//------------------------------------------------------------------------------------
	};

	typedef MyFont*	PMyFont;

	//～フォントの作り方～
	//MMyFont font = new MyFont( DirectXのDevice, 生成したい文字 );
	
	//～フォントの消去～
	//delete font;
	//でテクスチャも消えるので問題なし！
	//それとOKがfalseだとその文字は使えないので自分で消してね～
}

#endif