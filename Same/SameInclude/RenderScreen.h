#ifndef MYRIECTX_RENDER_H
#define MYRIECTX_RENDER_H

//-------------------------------------------------
//
//スクリーンショットを撮るときに使うクラス
//これを使って2画面分割や画面割などができる!
//
//-------------------------------------------------
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef MYDIRECTX_LIGHTCOLOR_H
#include <DirectLight.h>
#endif

namespace NanairoLib
{
	class RenderScreen
	{
		private:
			bool useOK;						//レンダー準備完了フラグ
			DWORD		tarGetNumber;		//ターゲット番号
			PSurface	back;				//バックバッファ
			PSurface	screen;				//スクリーンバッファ
			PSurface	depthstencil;		//スクリーン深度
			PSurface	backofstencl;		//バック深度
			PTexture	texture;			//ターゲットテクスチャ

		public:
			short screenSum, screenNum;
			Textcolor	color;

		private:
			//-------------------------------------------------
			//初めのサーフェイスとテクスチャの作成
			//-------------------------------------------------
			//@in : DirectX用デバイス	
			__IMPOETER		void InitTarGet(PDirectDevice Device);
			
		public:

			__IMPOETER		RenderScreen();
			__IMPOETER		RenderScreen(PDirectDevice Device, DWORD num);
			__IMPOETER		~RenderScreen();
		
			//------------------------------------------------------------------------------
			//サーフェイスのセット
			//------------------------------------------------------------------------------
			//@in : DirectX用デバイス
			//@in : レンダーパス番号
			//@in : 0(バックバッファに戻す) 1(ターゲット番号の変更)
			__IMPOETER		void		ChangeTarGet(PDirectDevice Device, int renderPass = 0, int mode = 0);
			
			//--------------------------------------
			//保存したスクリーンのテクスチャの取得
			//--------------------------------------
			__IMPOETER		PTexture	GetTexture() const;											
	};

	typedef RenderScreen*		PRenderScreen;
	typedef const RenderScreen*	PCRenderScreen;
}
#endif