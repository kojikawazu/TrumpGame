#ifndef NanairoLib_KEYS_H
#define NanairoLib_KEYS_H

//-------------------------------------------------
//
//���͑��u���瓾����f�[�^���i�[���Ă�N���X
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
	//�L�[�{�[�h����
	//--------------------------------------------------------------
	typedef enum WIN_KEY
	{
		KSPACE,KUP,KDOWN,KLEFT,KRIGHT,KSHIFT,KCONTROL,KENTER,KESCAPE,
		KA,KW,KD,KX,KI,KK,KQ,KS,KE,KZ,KR,KV,KP,KC,
	}KEYNUM;

	//--------------------------------------------------------------
	//�p�b�h����
	//--------------------------------------------------------------
	typedef enum WIN_PAD
	{
		PADUP,PADDOWN,PADLEFT,PADRIGHT,PADSTART,PADBACK,PADA,PADB,
		PADX,PADY,PADLB,PADRB,
	}PADNUM;

	//--------------------------------------------------------------
	//�}�E�X����
	//--------------------------------------------------------------
	typedef enum WIN_MOUSE
	{
		LBUTTON,RBUTTON,MBUTTON,
	}MOUSENUM;

	//------------------------------
	//�C���v�b�g�L�[�ő吔
	//------------------------------
	#define keySum				 23
	#define mouseSum			  3
	#define padSum				 12

	#define DX_INPUT_PAD1		(0x0001)		// �p�b�h�P����
	#define DX_INPUT_PAD2		(0x0002)		// �p�b�h�Q����
	#define DX_INPUT_PAD3		(0x0003)		// �p�b�h�R����
	#define DX_INPUT_PAD4		(0x0004)		// �p�b�h�S����
	/*
	 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	 * 0x40 : unassigned
	 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	 */

	//----------------------------------------------------
	//�L�[
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
	//�}�E�X
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
	//�p�b�h�N���X
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
	//�L�[���܂Ƃ߂ĊǗ�����N���X
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
