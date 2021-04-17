#ifndef NanairoLib_WINCREATE_H
#define NanairoLib_WINCREATE_H

//---------------------------------------------------------------
//
//WindowsやDirectXの初期化、リリース
//
//---------------------------------------------------------------
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

namespace NanairoLib
{
	//---------------------------------------
	//ウィンドウやDirectXの生成メソッド群
	//---------------------------------------
	class  WinCreate
	{
	private:
		__IMPOETER WinCreate(const WinCreate& win);
	
	public:
		//コンストラクタ
		__IMPOETER WinCreate();
		__IMPOETER ~WinCreate();

		//---------------------------------------------------------------
		//最初のウィンドウ系の初期化
		//---------------------------------------------------------------
		//@in : インスタンスハンドル
		//@inout : windows用ハンドル
		//@out : 成功、失敗
		__IMPOETER HRESULT CreateClassAndWin(HINSTANCE hInst,HWND *hWnd);

		//------------------------------------------------------------------------------------------
		//DirectXの初期化
		//------------------------------------------------------------------------------------------
		//@inout : DirectX9インターフェイス
		//@inout : DirectX9デバイス
		//@inout : Windowsハンドル
		//@out : DirectXデバイス
		__IMPOETER IDirect3DDevice9* InitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device,HWND hWnd);
		
		//-----------------------------------------------------------------------
		//DirectXゲームのリリース
		//-----------------------------------------------------------------------
		//inout : DirectX9インターフェイス
		//inout : DirectX9デバイス
		__IMPOETER void UnInitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device);
	};

}
#endif