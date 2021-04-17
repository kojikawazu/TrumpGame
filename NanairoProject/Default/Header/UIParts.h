#ifndef _MYGAME_UIPARTS_H
#define _MYGAME_UIPARTS_H

////////////////////////////////////
//std
#ifndef _STRING_
#include <string>
#endif

////////////////////////////////////
//NanairoLib
#ifndef _NanairoLib_MYVECTOR_H
#include <DirectParts.h>
#endif

#ifndef MYDIRECTX_LIGHTCOLOR_H
#include <DirectLight.h>
#endif

////////////////////////////////////
//MYGAME
#ifndef MYGAME_OBJECTLIST_H
#include <OBjectList.h>
#endif

//---------------------------------------------------------
//
//ここには必要なパーツを置いていきます～
//このヘッダはインクルード必須です
//
//---------------------------------------------------------
//
//バックグラウンドクラスは汎用オブジェクトを継承しているので
//テンプレートリストに追加可能
//
//----------------------------------------------------

namespace MYGAME
{
	//------------------------------------------------------
	//簡易背景を表示したい時に使用
	//------------------------------------------------------
	class BackGround_2D : public NanairoLib::NormalObject
	{
	public:
		std::string				backName;
		NanairoLib::UIParts2D	ui;

	public:
		BackGround_2D(){	this->Init();	}
		BackGround_2D(LPCSTR name);
		virtual	~BackGround_2D(){	this->backName.clear();	}
		
	public:
		///////////////////////////////////////////
		//setter
		//背景の画像名
		void SetBackName(LPCSTR name){				this->backName = (LPSTR)name;	}
		//カラーのセット
		void SetColor(NanairoLib::Vector4& col){	this->ui.color = col;			}
		///////////////////////////////////////////
		
		//ﾌｧｲﾙﾎﾟｲﾝﾀからロード
		void loadParts(std::ifstream& fs);

		//ﾌｧｲﾙから読み込んだデータからほしい情報を取得
		void readParts(std::string& str);

		//ボツになるかもしれない描画
		//テクスチャなし板ポリ描画
		void DrawScreen_NoTexture();

		/////////////////////////////////////////////////
		//virtual
		void Init();
		void Draw2D();
		void Step(){}
		void Dispose(){}
		void Del(){}
	};
	//------------------------------------------------------
}

#endif