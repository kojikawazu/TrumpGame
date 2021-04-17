#pragma once

//----------------------------------------------------
//
//インプット系のデバイス情報を取得し、管理するクラス
//
//----------------------------------------------------

#pragma region インクルード
#include <Directkey.h>
#include <Pad_wheel.h>
#include <XInput.h>
#include <windows.h>
#pragma endregion

#pragma warning(disable : 4800)

namespace NanairoLib
{
	//------------------------------------------------------------------------------
	//キーのマクロ
	//------------------------------------------------------------------------------
	#define KEYCHECK(_key)		_key & 0x80 
	#define MOUSECHECK(_key)	_key & 0x8000
	#define PADCHECK(_key)		_key != 0


	#pragma region コンストラクタ
	inline KEY::KEY()
	{
		for(int i=0; i< keySum; i++)
		{
			this->push[i] = this->pushed[i] = this->trg[i] = false;
			this->keycnt[i] = 0;
		}
	}

	inline KEY::~KEY(){}
	#pragma endregion

	//-------------------------------------------------
	//キーチェック
	//-------------------------------------------------
	void KEY::CheckKey()
	{
		BYTE keyData[256] = {};
		for(int i=0; i<keySum; i++)	pushed[i] = push[i];
		GetKeyboardState(keyData);

		push[KSPACE]	= (KEYCHECK(keyData[VK_SPACE]));
		push[KLEFT]		= (KEYCHECK(keyData[VK_LEFT]));
		push[KUP]		= (KEYCHECK(keyData[VK_UP]));
		push[KRIGHT]	= (KEYCHECK(keyData[VK_RIGHT]));
		push[KDOWN]		= (KEYCHECK(keyData[VK_DOWN]));
		push[KSHIFT]	= (KEYCHECK(keyData[VK_SHIFT]));	
		push[KCONTROL]	= (KEYCHECK(keyData[VK_CONTROL]));
		push[KESCAPE]	= (KEYCHECK(keyData[VK_ESCAPE]));
 		push[KA]		= (KEYCHECK(keyData[0x41]));
		push[KW]		= (KEYCHECK(keyData[0x57])); 
		push[KD]		= (KEYCHECK(keyData[0x44]));
		push[KX]		= (KEYCHECK(keyData[0x58])); 
		push[KI]		= (KEYCHECK(keyData[0x49]));
		push[KK]		= (KEYCHECK(keyData[0x48]));
		push[KQ]		= (KEYCHECK(keyData[0x51]));
		push[KS]		= (KEYCHECK(keyData[0x53]));
		push[KE]		= (KEYCHECK(keyData[0x45]));
		push[KZ]		= (KEYCHECK(keyData[0x5A]));
		push[KR]		= (KEYCHECK(keyData[0x52]));
		push[KV]		= (KEYCHECK(keyData[0x56]));
		push[KP]		= (KEYCHECK(keyData[0x50]));
		push[KC]		= (KEYCHECK(keyData[0x43]));

		for(int i=0; i<keySum; i++)
		{
			if(push[i])			this->keycnt[i]++;
			else if(pushed[i])	this->keycnt[i] = 0;

			this->trg[i] = (push[i] && !pushed[i] ? true : false);
		}
	}
	
	#pragma region コンストラクタ
	inline MOUSE::MOUSE() : mouseX(0) , mouseY(0) , oldMouseX(0), oldMouseY(0)
	{
		for(int i=0;i<mouseSum;i++)	
			push[i] = pushed[i] = trg[i] = false;
	}

	inline MOUSE::~MOUSE(){}
	#pragma endregion
	
	//-----------------------------------
	//マウスのチェック
	//-----------------------------------
	void MOUSE::CheckMouse(HWND hWnd)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hWnd, &point);

		this->oldMouseX = this->mouseX;
		this->oldMouseY = this->mouseY;
		for(int i=0; i<mouseSum; i++)
			this->pushed[i] = push[i];

		this->mouseX = point.x;
		this->mouseY = point.y;
		push[LBUTTON] = MOUSECHECK(::GetAsyncKeyState(VK_LBUTTON));
		push[RBUTTON] = MOUSECHECK(::GetAsyncKeyState(VK_RBUTTON));
		push[MBUTTON] = MOUSECHECK(::GetAsyncKeyState(VK_MBUTTON));
		
		for(int i=0; i<mouseSum; i++)
			this->trg[i] = ( push[i] && !pushed[i] ? true : false );
	}	

	#pragma region パッドのコンストラクタ
	inline Xpad::Xpad(int knd)
	{
		this->Init_pad(knd);
	}
	#pragma endregion

	#pragma region パッドの有無
	bool Xpad::Ispading()
	{
		XINPUT_STATE state = {};
		return this->ispad = ((XInputGetState(padnum,&state)) == ERROR_SUCCESS ? true : false);
	}
	#pragma endregion

	#pragma region チェックパッド
	void Xpad::Pad_inputCheck()
	{
		if(this->ispad)
		{
			for(int i=0; i<padSum; i++)
				this->oldpadbutton[i] = this->padbutton[i];

			XINPUT_STATE state = {};
			if((XInputGetState(padnum,&state)) == ERROR_SUCCESS){		
				this->ltrigger = state.Gamepad.bLeftTrigger;
				this->rtrigger = state.Gamepad.bRightTrigger;
				this->lanalogX = state.Gamepad.sThumbLX;
				this->lanalogY = state.Gamepad.sThumbLY;
				this->ranalogX = state.Gamepad.sThumbRX;
				this->ranalogY = state.Gamepad.sThumbRY;
				
				this->padbutton[PADUP] = PADCHECK(((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)));
				this->padbutton[PADDOWN] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN));
				this->padbutton[PADLEFT] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT));
				this->padbutton[PADRIGHT] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT));
				this->padbutton[PADSTART] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_START));
				this->padbutton[PADBACK] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK));
				this->padbutton[PADA] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_A));
				this->padbutton[PADB] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_B));
				this->padbutton[PADX] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_X));
				this->padbutton[PADY] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y));
				this->padbutton[PADLB] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER));
				this->padbutton[PADRB] = PADCHECK((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER));

				for(int i=0; i<padSum; i++)
					this->trg[i] = (this->padbutton[i] && !this->oldpadbutton[i] ? true : false);
			}
			else	
				this->Init_pad(this->padnum);
		}
		else	
			this->Ispading();
	}
	#pragma endregion

	#pragma region パッドのホイール検査
	void Xpad::IsPad_wheel()
	{
		isWheel = Is360WheelControler(this->padnum + 1);
	}
	#pragma endregion
	
	#pragma region 初期化	
	void Xpad::Init_pad(int knd)
	{
		this->padnum = knd;
		this->ispad = false;
		highPower = 200;
		lowPower  = 100;
		ranalogX = ranalogY = lanalogX = lanalogY = ltrigger = rtrigger = 0;	
		
		for(int i=0; i<padSum; i++)
			this->oldpadbutton[i] = this->padbutton[i] = this->trg[i] = false;
	}
	#pragma endregion

	#pragma region デバイスのコンストラクタ
	inline KEYS::KEYS() : mouse(MOUSE()), key(KEY())
	{
		for(int i=0;i<4;i++)	
			this->xpad[i] = Xpad(i);
	}
	inline KEYS::~KEYS(){}
	#pragma endregion

	#pragma region デバイスのチェック
	void KEYS::CheckKeys(HWND hWnd)
	{
		key.CheckKey();
		mouse.CheckMouse(hWnd);
		for(int i=0; i<4; i++)	xpad[i].Pad_inputCheck();
	}
	#pragma endregion
	
	#pragma region Getter
	inline MOUSE* KEYS::GetMouse() const
	{
		return (MOUSE*)&this->mouse;			
	}
	inline KEY*	KEYS::GetKey() const
	{
		return (KEY*)&this->key;
	}
	inline Xpad*	KEYS::GetXPad(int num) const
	{ 	
		return (Xpad*)&this->xpad[num];			
	}
	#pragma endregion

	/////////////////////////////////////////////////////////////////////////////////////
	//----------------------------------------------------------------------------------/
	/////////////////////////////////////////////////////////////////////////////////////

	//------------------------------------------------------------------------------
	///３６０コントローラ用関数
	//------------------------------------------------------------------------------
	int StartJoypadVibration360(int inputType,int power)
	{
		XINPUT_VIBRATION vib={power*64,power*64};
		inputType=(15&inputType)-1;
		return XInputSetState(inputType,&vib)!=ERROR_SUCCESS;
	}
	int StartJoypadVibration360(int inputType,int powerL,int powerR)
	{
		XINPUT_VIBRATION vib;
		vib.wLeftMotorSpeed = powerL*64;
		vib.wRightMotorSpeed = powerR*64;
		inputType=(15&inputType)-1;
		return XInputSetState(inputType,&vib)!=ERROR_SUCCESS;
	}

	bool Is360WheelControler(int inputType)
	{
		XINPUT_CAPABILITIES capabilities;
		XInputGetCapabilities((15&inputType)-1,XINPUT_FLAG_GAMEPAD,&capabilities);
		return false;
	}

	int StopJoypadVibration360(int inputType)
	{
		XINPUT_VIBRATION vib={0,0};
		inputType=(15&inputType)-1;
		return XInputSetState(inputType,&vib)!=ERROR_SUCCESS;
	}

	int GetJoypadAnalogInputTrigger(int* left,int* right,int inputType)
	{
		XINPUT_STATE state;
		inputType=(15&inputType)-1;
		if(XInputGetState(inputType,&state)==ERROR_SUCCESS)
		{
			*left=state.Gamepad.bLeftTrigger;
			*right=state.Gamepad.bRightTrigger;
			return 0;
		}else{
			return -1;
		}
	}

	int
	GetJoypadAnalogInput360( int* analogX, int* analogY,int* ltrigger, int* rtrigger, int inputType )
	{
		XINPUT_STATE state;
		inputType=(15&inputType)-1;
		if(XInputGetState(inputType,&state)==ERROR_SUCCESS)
		{
			*ltrigger=state.Gamepad.bLeftTrigger;
			*rtrigger=state.Gamepad.bRightTrigger;
			*analogX=state.Gamepad.sThumbLX;
			*analogY=state.Gamepad.sThumbLY;
			return 0;
		}else{
			return -1;
		}
	}
	
}