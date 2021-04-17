#pragma once

//-----------------------------------------------------------------------
//
//WindowsやDirectXの初期化、リリースをセッティング
//
//-----------------------------------------------------------------------
#include <DirectWindow.h>

namespace NanairoLib
{
	//---------------------------------------------
	//ウィンドウの生成
	//---------------------------------------------
	HRESULT createWin(HINSTANCE hInst,HWND *wnd)
	{
		RECT rt = {0,0,SCRW,SCRH};
		::AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,false);
		*wnd = ::CreateWindow(
			appName,appName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,CW_USEDEFAULT,
			rt.right - rt.left,rt.bottom - rt.top,
			NULL,NULL,hInst,NULL);
		if(*wnd == NULL)
		{
			::MessageBoxA(::GetDesktopWindow(),
				"ウィンドウの作成に失敗しました。",appName,MB_OK);
			return E_FAIL;
		}
		return S_OK;
	}
	
	//--------------------------------------------------------------------------------

	#pragma region コンストラクタ
	inline WinCreate::WinCreate(){}
	inline WinCreate::~WinCreate(){}
	inline WinCreate::WinCreate(const WinCreate& win){}
	#pragma endregion
	
	//------------------------------------------------------------------------
	//ウィンドウプロシージャ
	//------------------------------------------------------------------------
	HRESULT CALLBACK MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
	{
		switch(msg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}
		return ::DefWindowProcA(hWnd,msg,wParam,lParam);
	}
	
	//---------------------------------------------------------------
	//最初のウィンドウ系の初期化
	//---------------------------------------------------------------
	//@in : インスタンスハンドル
	//@inout : windows用ハンドル
	//@out : 成功、失敗
	HRESULT WinCreate::CreateClassAndWin(HINSTANCE hInst,HWND *hWnd)
	{
		if(((*hWnd) = ::FindWindowA(appName,appName)) != NULL)
		{
			::ShowWindow(*hWnd,SW_SHOWNORMAL);
			return -1;
		}
	
		//ウィンドウクラスの作成
		WNDCLASSEX wnd;
		memset(&wnd,0,sizeof(wnd));
	
		wnd.cbSize = sizeof(WNDCLASSEX);
		wnd.lpfnWndProc = MsgProc;
		wnd.hInstance = hInst;
		wnd.lpszClassName = appName;

		::RegisterClassExA(&wnd);

		return (FAILED(createWin(hInst,hWnd)) ? E_FAIL : S_OK);
	}

	//------------------------------------------------------------------------------------------
	//DirectXの初期化
	//------------------------------------------------------------------------------------------
	//@inout : DirectX9インターフェイス
	//@inout : DirectX9デバイス
	//@inout : Windowsハンドル
	//@out : DirectXデバイス
	IDirect3DDevice9* WinCreate::InitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device,HWND hWnd)
	{
		D3d = ::Direct3DCreate9(D3D_SDK_VERSION);

		//初期化設定
		D3DPRESENT_PARAMETERS d3dpp;
		::memset(&d3dpp,0,sizeof(d3dpp));

		d3dpp.Windowed = true;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferWidth = SCRW;
		d3dpp.BackBufferHeight = SCRH;
		d3dpp.BackBufferCount = D3DFMT_UNKNOWN;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

		if(FAILED(D3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&Device)))
		{
				::MessageBoxA(hWnd,"Direct3Dの初期化に失敗しました。",
								"Direct3Dエラー",MB_OK);
				exit(-1);
		}

		Device->SetRenderState(D3DRS_ZENABLE,true);
	
		//(ポリゴン表示の設定)
		//グローシェーディング
		Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
		//頂点が反時計回りの三角形は表示しない
		Device->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

		//(半透明表示の設定)
		//アルファテストを有効
		Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);
		//アルファが0より大きいときにのみ描画
		Device->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
		//アルファブレンドを有効
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		//アルファブレンド時、上書きデータ側の計算はアルファ値を使用
		Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		//アルファブレンド時、元データ側の計算は上書きデータのアルファ値の逆の値を使用
		Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
		//(フォグの設定)
		//フォグを無効にする
		Device->SetRenderState(D3DRS_FOGENABLE,false);

		//(ライティングの設定)
		//ライティングを有効にする
		Device->SetRenderState(D3DRS_LIGHTING,true);
		//アンビエント（環境光）の色。最初は適当に)
		Device->SetRenderState( D3DRS_AMBIENT,0xFFFFFFFF);
		//(ヘルパー)
		//シェーディングの際に法線を自動でノーマライズ（正規化）
		Device->SetRenderState(D3DRS_NORMALIZENORMALS,true);
	
		::ShowWindow(hWnd,SW_SHOW);

		return Device;
	}

	//-----------------------------------------------------------------------
	//DirectXゲームのリリース
	//-----------------------------------------------------------------------
	//inout : DirectX9インターフェイス
	//inout : DirectX9デバイス
	void WinCreate::UnInitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device)
	{
		ES_SAFE_RELEASE( Device );
		ES_SAFE_RELEASE( D3d );
	}

}

