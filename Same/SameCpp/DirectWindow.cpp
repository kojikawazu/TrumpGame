#pragma once

//-----------------------------------------------------------------------
//
//Windows��DirectX�̏������A�����[�X���Z�b�e�B���O
//
//-----------------------------------------------------------------------
#include <DirectWindow.h>

namespace NanairoLib
{
	//---------------------------------------------
	//�E�B���h�E�̐���
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
				"�E�B���h�E�̍쐬�Ɏ��s���܂����B",appName,MB_OK);
			return E_FAIL;
		}
		return S_OK;
	}
	
	//--------------------------------------------------------------------------------

	#pragma region �R���X�g���N�^
	inline WinCreate::WinCreate(){}
	inline WinCreate::~WinCreate(){}
	inline WinCreate::WinCreate(const WinCreate& win){}
	#pragma endregion
	
	//------------------------------------------------------------------------
	//�E�B���h�E�v���V�[�W��
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
	//�ŏ��̃E�B���h�E�n�̏�����
	//---------------------------------------------------------------
	//@in : �C���X�^���X�n���h��
	//@inout : windows�p�n���h��
	//@out : �����A���s
	HRESULT WinCreate::CreateClassAndWin(HINSTANCE hInst,HWND *hWnd)
	{
		if(((*hWnd) = ::FindWindowA(appName,appName)) != NULL)
		{
			::ShowWindow(*hWnd,SW_SHOWNORMAL);
			return -1;
		}
	
		//�E�B���h�E�N���X�̍쐬
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
	//DirectX�̏�����
	//------------------------------------------------------------------------------------------
	//@inout : DirectX9�C���^�[�t�F�C�X
	//@inout : DirectX9�f�o�C�X
	//@inout : Windows�n���h��
	//@out : DirectX�f�o�C�X
	IDirect3DDevice9* WinCreate::InitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device,HWND hWnd)
	{
		D3d = ::Direct3DCreate9(D3D_SDK_VERSION);

		//�������ݒ�
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
				::MessageBoxA(hWnd,"Direct3D�̏������Ɏ��s���܂����B",
								"Direct3D�G���[",MB_OK);
				exit(-1);
		}

		Device->SetRenderState(D3DRS_ZENABLE,true);
	
		//(�|���S���\���̐ݒ�)
		//�O���[�V�F�[�f�B���O
		Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
		//���_�������v���̎O�p�`�͕\�����Ȃ�
		Device->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

		//(�������\���̐ݒ�)
		//�A���t�@�e�X�g��L��
		Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);
		//�A���t�@��0���傫���Ƃ��ɂ̂ݕ`��
		Device->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
		//�A���t�@�u�����h��L��
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
		//�A���t�@�u�����h���A�㏑���f�[�^���̌v�Z�̓A���t�@�l���g�p
		Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		//�A���t�@�u�����h���A���f�[�^���̌v�Z�͏㏑���f�[�^�̃A���t�@�l�̋t�̒l���g�p
		Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
		//(�t�H�O�̐ݒ�)
		//�t�H�O�𖳌��ɂ���
		Device->SetRenderState(D3DRS_FOGENABLE,false);

		//(���C�e�B���O�̐ݒ�)
		//���C�e�B���O��L���ɂ���
		Device->SetRenderState(D3DRS_LIGHTING,true);
		//�A���r�G���g�i�����j�̐F�B�ŏ��͓K����)
		Device->SetRenderState( D3DRS_AMBIENT,0xFFFFFFFF);
		//(�w���p�[)
		//�V�F�[�f�B���O�̍ۂɖ@���������Ńm�[�}���C�Y�i���K���j
		Device->SetRenderState(D3DRS_NORMALIZENORMALS,true);
	
		::ShowWindow(hWnd,SW_SHOW);

		return Device;
	}

	//-----------------------------------------------------------------------
	//DirectX�Q�[���̃����[�X
	//-----------------------------------------------------------------------
	//inout : DirectX9�C���^�[�t�F�C�X
	//inout : DirectX9�f�o�C�X
	void WinCreate::UnInitDirect3D(IDirect3D9 *D3d,IDirect3DDevice9* Device)
	{
		ES_SAFE_RELEASE( Device );
		ES_SAFE_RELEASE( D3d );
	}

}

