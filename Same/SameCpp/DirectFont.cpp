#pragma once
//--------------------------------------------------------------------------------
//
//windows用フォントを描画するクラス
//
//--------------------------------------------------------------------------------

#pragma region インクルード
#include <DirectFont.h>
#include <tchar.h>
#include <strsafe.h>
#pragma endregion

namespace NanairoLib
{

	//----------------------------------------------------------------------------------
	//デコン系
	//----------------------------------------------------------------------------------
	#pragma region コンストラクタ系
	inline MyFont::MyFont() : OKFlag(false){}

	inline MyFont::MyFont(IDirect3DDevice9 *Device,PCUINT C)
	{
		OKFlag = this->createFont(Device, C);	
	}

	inline MyFont::~MyFont()
	{
		ES_SAFE_RELEASE(font.fontText);
	}
	#pragma endregion

	//----------------------------------------------------------------------------------
	//Getter Setter check
	//----------------------------------------------------------------------------------
	#pragma region Setter
	inline PFONTH MyFont::GetFont() const
	{
		return (PFONTH const)&font;			
	}

	inline const bool MyFont::isOK() const
	{
		return OKFlag;			
	}
	#pragma endregion

	//----------------------------------------------------------------------------------
	//高速用に作成したフォント
	//----------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : 文字コード
	//@out : true(成功) false(失敗)
	bool MyFont::createFont(IDirect3DDevice9 *Device,PCUINT cd)
	{
		//フォントの生成
		int fontSize = 500;
		LOGFONT Lf =  {
			fontSize, 0, 0, 0, 32, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,			
			CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, __WordFontType
		};

		HFONT hFont;
		//ここで失敗すれば使えず＞＜
		if(!(hFont = ::CreateFontIndirect(&Lf)))
			return false;
		
		//デバイスコンテキスト取得
		//デバイスにフォントを持たせないとGetGlyphOutline関数が使えないせいで・・・
		HDC hdc = ::GetDC(NULL);
		HFONT oldFont = (HFONT)::SelectObject(hdc, hFont);

		//文字コード取得
		UINT code = *cd;
	
		//フォントビットマップ取得
		TEXTMETRIC TM;

		//フォント情報の取得
		::GetTextMetrics( hdc, &TM);					
		GLYPHMETRICS GM;
		CONST MAT2 Mat = {{0,1}, {0,0}, {0,0}, {0,1}};

		//デバイスコンテキストで選択されている
		//TrueType フォント文字のビットマップまたはアウトラインを取得
		DWORD size = ::GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
		BYTE *ptr = new BYTE[size];
		::GetGlyphOutline(hdc, code , GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

		//デバイスコンテキストとフォントハンドルの開放
		::SelectObject(hdc, oldFont);
		::DeleteObject(hFont);
		::ReleaseDC(NULL, hdc);

		//テクスチャ作成
		if(FAILED(Device->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, 
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &this->font.fontText, NULL)))
		{
			if(FAILED(Device->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, 0, 
												D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &this->font.fontText, NULL)))
			{
				return false;									
			}
		}

		//テクスチャにフォントビットマップ書き込み
		::D3DLOCKED_RECT lockRect;
		if(FAILED(this->font.fontText->LockRect(0, &lockRect, NULL, D3DLOCK_DISCARD)))
		{
			if(FAILED(this->font.fontText->LockRect(0, &lockRect, NULL, 0)))
			{
				return false;
			}
		}

		//フォント情報の書きこみ
		int iOfs_x = GM.gmptGlyphOrigin.x;								//書き出し位置（左上）X
		int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;				//書き出し位置（左上）Y
		int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;	//フォントビットマップの幅高(4バイト幅に調整)
		int iBmp_h = GM.gmBlackBoxY;
		int Level = 17;
		int x, y;
		DWORD alpha, Color;
		font.fontW = iBmp_w;
		font.fontH = iBmp_h;

		FillMemory(lockRect.pBits, lockRect.Pitch * TM.tmHeight, 0);	//指定したところに書き込む！
		for(y = iOfs_y; y<iOfs_y + iBmp_h; y++)
		{
			for(x = iOfs_x; x<iOfs_x + iBmp_w; x++)
			{
				alpha = (255 * ptr[ (x - iOfs_x) + iBmp_w * (y - iOfs_y) ] ) / ( Level - 1 );
				Color = 0x00ffffff | (alpha << 24);
				::memcpy((BYTE*)lockRect.pBits + (lockRect.Pitch * y) + (4 * x), &Color, sizeof(DWORD));	
			}
		}

		this->font.fontText->UnlockRect(0);
		delete[] ptr;
		return true;
	}

}