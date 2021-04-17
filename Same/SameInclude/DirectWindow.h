#ifndef NanairoLib_WINCREATE_H
#define NanairoLib_WINCREATE_H

//---------------------------------------------------------------
//
//Windows��DirectX�̏������A�����[�X
//
//---------------------------------------------------------------
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

namespace NanairoLib
{
	//---------------------------------------
	//�E�B���h�E��DirectX�̐������\�b�h�Q
	//---------------------------------------
	class  WinCreate
	{
	private:
		__IMPOETER WinCreate(const WinCreate& win);
	
	public:
		//�R���X�g���N�^
		__IMPOETER WinCreate();
		__IMPOETER ~WinCreate();

		//---------------------------------------------------------------
		//�ŏ��̃E�B���h�E�n�̏�����
		//---------------------------------------------------------------
		//@in : �C���X�^���X�n���h��
		//@inout : windows�p�n���h��
		//@out : �����A���s
		__IMPOETER HRESULT CreateClassAndWin(HINSTANCE hInst,HWND *hWnd);

		//------------------------------------------------------------------------------------------
		//DirectX�̏�����
		//------------------------------------------------------------------------------------------
		//@inout : DirectX9�C���^�[�t�F�C�X
		//@inout : DirectX9�f�o�C�X
		//@inout : Windows�n���h��
		//@out : DirectX�f�o�C�X
		__IMPOETER IDirect3DDevice9* InitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device,HWND hWnd);
		
		//-----------------------------------------------------------------------
		//DirectX�Q�[���̃����[�X
		//-----------------------------------------------------------------------
		//inout : DirectX9�C���^�[�t�F�C�X
		//inout : DirectX9�f�o�C�X
		__IMPOETER void UnInitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device);
	};

}
#endif