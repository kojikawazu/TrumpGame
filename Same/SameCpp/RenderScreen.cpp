#pragma once
//-----------------------------------
//バックバッファ以外で書き込むクラス
//-----------------------------------
#include <RenderScreen.h>

namespace NanairoLib
{
	//-------------------------------------
	//デコン系
	//-------------------------------------
	#pragma region コンストラクタ
	inline RenderScreen::RenderScreen(){}

	inline RenderScreen::RenderScreen(PDirectDevice Device,DWORD num) :
								tarGetNumber(num) , useOK(false), screenSum(1), screenNum(1)
	{
		this->InitTarGet(Device);
		this->color = NanairoLib::Textcolor();
	}

	inline RenderScreen::~RenderScreen()
	{
		ES_SAFE_RELEASE( this->back );
		ES_SAFE_RELEASE( this->screen );
		ES_SAFE_RELEASE( this->texture );
		ES_SAFE_RELEASE( this->depthstencil );
		ES_SAFE_RELEASE( this->backofstencl );
	}
	#pragma endregion

	//-------------------------------------------------
	//初めのサーフェイスとテクスチャの作成
	//-------------------------------------------------
	//@in : DirectX用デバイス	
	void RenderScreen::InitTarGet(PDirectDevice Device)
	{
		//バックバッファのサーフェイスを取得
		Device->GetRenderTarget(0, &this->back);

		//バック深度バッファの取得
		Device->GetDepthStencilSurface(&this->backofstencl);

		//書き込む用のテクスチャを用意
		Device->CreateTexture(
			(UINT)SCRW,(UINT)SCRH,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&this->texture,
			NULL);

		//サーフェイスレベルの設定
		this->texture->GetSurfaceLevel(0,&this->screen);

		//ここのステンシルバッファを作成
		Device->CreateDepthStencilSurface((UINT)SCRW,(UINT)SCRH,
			D3DFMT_D24S8,
			D3DMULTISAMPLE_NONE,
			0,
			true,
			&this->depthstencil,
			NULL);
	}
	

	//--------------------------------------
	//保存したスクリーンのテクスチャの取得
	//--------------------------------------
	inline PTexture RenderScreen::GetTexture() const
	{	
		return this->texture;	
	}

	//------------------------------------------------------------------------------
	//サーフェイスのセット
	//------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : レンダーパス番号
	//@in : 0(バックバッファに戻す) 1(ターゲット番号の変更)
	void RenderScreen::ChangeTarGet(PDirectDevice Device, int renderPass, int mode)
	{
		switch(mode + 1)
		{
			case 1:	
				//ターゲットを戻す
				Device->SetRenderTarget( 0, this->back);
				//ステンシルターゲットを戻す
				Device->SetDepthStencilSurface(this->backofstencl);
				break;
			case 2:	
				//ターゲットの変更
				Device->SetRenderTarget(renderPass, this->screen);
				//ステンシルターゲットの変更
				Device->SetDepthStencilSurface(this->depthstencil);

				//クリアします
				Device->Clear(
					0,
					NULL,
					D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER| D3DCLEAR_STENCIL,
					D3DCOLOR_RGBA(0, 0, 0, 0),
					1.0f,0);
				break;
		}
	}
}