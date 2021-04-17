#ifndef MYDXFUNC_H
#define MYDXFUNC_H

//------------------------------------------------------
//
//DLLの中で保持していきたいクラスやデータをここに格納
//シングルトン呼び出しすることで使える
//
//------------------------------------------------------
#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

#ifndef NanairoLib_KEYS_H
#include <DirectKey.h>
#endif

namespace NanairoLib
{
	//--------------
	//前方宣言	
	//--------------
	class MYDXData;
	class KEYS;

	class MYDXData
	{
		private:
			short				usedCount;		//使った回数
			HWND				hWnd;			//ウィンドウハンドル
			IDirect3D9			*D3d;			//DirectXのクラス
			IDirect3DDevice9	*Device;		//デバイス
			
		private:
			__IMPOETER void init()
			{
				D3d = 0;
				Device = 0;
				this->usedCount++;
			}

		public:
			__IMPOETER MYDXData() : usedCount(0) 
			{
				if(usedCount == 0)	this->init();
			}

			__IMPOETER MYDXData(int counts){
				if(counts == 0)	this->init();
			}

			__IMPOETER ~MYDXData(){}
			
			__IMPOETER  IDirect3DDevice9* GetDevice() const{		return Device;	}
			__IMPOETER  IDirect3DDevice9** GetDeviceT() const{		return (IDirect3DDevice9** const)&Device;	}
			__IMPOETER  IDirect3D9* Get3D9(){					return D3d;		}
			__IMPOETER  IDirect3D9** Get3D9T(){				return &D3d;	}
			__IMPOETER  HWND GetWindow(){						return hWnd;	}
			__IMPOETER  HWND* GetWindowT(){					return &hWnd;	}

			__IMPOETER  void SetDevice(IDirect3DDevice9* D){	this->Device = D;	}
			__IMPOETER  void Set3D9(IDirect3D9* D){			this->D3d = D;		}
			__IMPOETER  void SetWindow(HWND H){				this->hWnd = H;		}
			
	};

	class MainFunction
	{
	private:	
		//----------------------------
		//シングルポインタ
		//----------------------------
		static MainFunction* MainFunc;
	private:	
		//内部で使うフィールドはプライベートに
		//例外はデバイスくらい
		NanairoLib::MYDXData*	DXData;
		NanairoLib::Artisan*	custom;
		
	public:
		//よくつかうのはパブリックで保留
		D3DXMATRIX				viewMatrix, projMatrix, portMatrix;
		KEYS*					keys;
	private:	
		//------------------------------------------------------
		//コピーガード
		//------------------------------------------------------
		__IMPOETER MainFunction();
		__IMPOETER MainFunction(const MainFunction& mmmm){}
		__IMPOETER MainFunction& operator= (MainFunction& mmmm)
		{
			return *MainFunc;
		}
	public:	
		//------------------------------------------------------
		//インスタンス取得
		//------------------------------------------------------
		__IMPOETER static MainFunction* GetInstance()
		{
			if(MainFunc == 0)
				MainFunc = new MainFunction();
			return MainFunc;
		}

		__IMPOETER static void deleteInstance()
		{
			delete MainFunc;
			MainFunc = NULL;
		}

		__IMPOETER ~MainFunction();
	
	public:	
		//-----------------------------------------------------------------------
		//Getter
		//-----------------------------------------------------------------------
		__IMPOETER MYDXData*	GetMYdevice() const{	return this->DXData;	}
		__IMPOETER Artisan*		GetArtisan() const{		return this->custom;	}
		__IMPOETER KEYS*		GetKey() const{			return this->keys;		}
	public:	
		//座標変換

		//----------------------------------------------------------------------------------------
		//ワールド座標からスクリーン座標に変換
		//----------------------------------------------------------------------------------------
		//@in : 位置ベクトル
		//@in : 回転ベクトル
		//@in : 拡縮ベクトル
		//@out : スクリーン座標
		__IMPOETER D3DXVECTOR3 ChangeToScreen_world(RCVector3 pos,RCVector3 ang,RCVector3 sc);

		//------------------------------------------------------------
		//スクリーン座標からワールド座標に変換
		//------------------------------------------------------------
		//@in : スクリーン座標
		//@out : ワールド座標
		__IMPOETER D3DXVECTOR3 ChangeToWorld_screen(RCVector3 pos);
		
		//---------------------------------------------
		//DirectXの初期化
		//---------------------------------------------
		//@in : インスタンスハンドル
		//@out : true(成功) false(失敗)
		__IMPOETER bool InitDirectX(HINSTANCE hInst);
			
		//----------------------------------------------
		//デフォルト設定をまとめて
		//----------------------------------------------
		__IMPOETER void SetDefaultMatrix(); 

		//----------------------------------------------
		//ライトのデフォルト設定
		//----------------------------------------------
		__IMPOETER void SetDefaultLight();

		//----------------------------------------------
		//デフォルトのカメラ設定
		//----------------------------------------------
		__IMPOETER void SetDefaultCamera();
	};

	#define DirectFunc	MainFunction::GetInstance()->
	#define __KEYDATA	MainFunction::GetInstance()->GetKey()->GetKey()
	#define __MOUSEDATA	MainFunction::GetInstance()->GetKey()->GetMouse()
}

#endif