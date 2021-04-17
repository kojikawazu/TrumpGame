#ifndef NanairoLib_KEYS_H
#define NanairoLib_KEYS_H

//-------------------------------------------------
//
//入力装置から得られるデータを格納してるクラス
//
//-------------------------------------------------
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

namespace NanairoLib
{
	//--------------------------------------------------------------
	//キーボード識別
	//--------------------------------------------------------------
	typedef enum WIN_KEY
	{
		KSPACE,KUP,KDOWN,KLEFT,KRIGHT,KSHIFT,KCONTROL,KENTER,KESCAPE,
		KA,KW,KD,KX,KI,KK,KQ,KS,KE,KZ,KR,KV,KP,KC,
	}KEYNUM;

	//--------------------------------------------------------------
	//パッド識別
	//--------------------------------------------------------------
	typedef enum WIN_PAD
	{
		PADUP,PADDOWN,PADLEFT,PADRIGHT,PADSTART,PADBACK,PADA,PADB,
		PADX,PADY,PADLB,PADRB,
	}PADNUM;

	//--------------------------------------------------------------
	//マウス識別
	//--------------------------------------------------------------
	typedef enum WIN_MOUSE
	{
		LBUTTON,RBUTTON,MBUTTON,
	}MOUSENUM;

	//------------------------------
	//インプットキー最大数
	//------------------------------
	#define keySum				 23
	#define mouseSum			  3
	#define padSum				 12

	#define DX_INPUT_PAD1		(0x0001)		// パッド１入力
	#define DX_INPUT_PAD2		(0x0002)		// パッド２入力
	#define DX_INPUT_PAD3		(0x0003)		// パッド３入力
	#define DX_INPUT_PAD4		(0x0004)		// パッド４入力
	/*
	 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	 * 0x40 : unassigned
	 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	 */

	//----------------------------------------------------
	//キー
	//----------------------------------------------------
	class KEY
	{
	public:
		bool push[keySum], pushed[keySum], trg[keySum];
		int keycnt[keySum];
	public:
		__IMPOETER KEY();
		__IMPOETER ~KEY();
		__IMPOETER void CheckKey();
	};

	//----------------------------------------------------
	//マウス
	//----------------------------------------------------
	class MOUSE
	{
	public:
		bool push[mouseSum], pushed[mouseSum], trg[mouseSum];
		int mouseX, mouseY, oldMouseX, oldMouseY;
	public:
		__IMPOETER MOUSE();
		__IMPOETER ~MOUSE();
		__IMPOETER void CheckMouse(HWND hWnd);
	};

	//----------------------------------------------------
	//パッドクラス
	//----------------------------------------------------
	class Xpad
	{
	public:
		bool padbutton[padSum], oldpadbutton[padSum], trg[padSum], isWheel, ispad;
		int highPower, lowPower, padnum;
		int lanalogX, lanalogY, ranalogX, ranalogY, ltrigger, rtrigger;
	public:
		__IMPOETER Xpad(){}
		__IMPOETER Xpad(int knd);
		__IMPOETER ~Xpad(){}
		__IMPOETER void Pad_inputCheck();
		__IMPOETER void IsPad_wheel();
		__IMPOETER bool Ispading();
		__IMPOETER void Init_pad(int knd);
	};

	//----------------------------------------------------
	//キーをまとめて管理するクラス
	//----------------------------------------------------
	class KEYS
	{
	private:
		MOUSE mouse;
		KEY key;
		Xpad xpad[4];
	public:
		__IMPOETER KEYS();
		__IMPOETER ~KEYS();
		__IMPOETER void CheckKeys(HWND hWnd);
		__IMPOETER MOUSE*	GetMouse() const ;
		__IMPOETER KEY*		GetKey() const;
		__IMPOETER Xpad*	GetXPad(int num) const ;
	};

	typedef KEYS*			PKEYS;
	typedef const KEYS*		PCKEYS;
}
#endif
