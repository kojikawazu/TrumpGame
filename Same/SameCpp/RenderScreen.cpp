#pragma once
//-----------------------------------
//�o�b�N�o�b�t�@�ȊO�ŏ������ރN���X
//-----------------------------------
#include <RenderScreen.h>

namespace NanairoLib
{
	//-------------------------------------
	//�f�R���n
	//-------------------------------------
	#pragma region �R���X�g���N�^
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
	//���߂̃T�[�t�F�C�X�ƃe�N�X�`���̍쐬
	//-------------------------------------------------
	//@in : DirectX�p�f�o�C�X	
	void RenderScreen::InitTarGet(PDirectDevice Device)
	{
		//�o�b�N�o�b�t�@�̃T�[�t�F�C�X���擾
		Device->GetRenderTarget(0, &this->back);

		//�o�b�N�[�x�o�b�t�@�̎擾
		Device->GetDepthStencilSurface(&this->backofstencl);

		//�������ޗp�̃e�N�X�`����p��
		Device->CreateTexture(
			(UINT)SCRW,(UINT)SCRH,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&this->texture,
			NULL);

		//�T�[�t�F�C�X���x���̐ݒ�
		this->texture->GetSurfaceLevel(0,&this->screen);

		//�����̃X�e���V���o�b�t�@���쐬
		Device->CreateDepthStencilSurface((UINT)SCRW,(UINT)SCRH,
			D3DFMT_D24S8,
			D3DMULTISAMPLE_NONE,
			0,
			true,
			&this->depthstencil,
			NULL);
	}
	

	//--------------------------------------
	//�ۑ������X�N���[���̃e�N�X�`���̎擾
	//--------------------------------------
	inline PTexture RenderScreen::GetTexture() const
	{	
		return this->texture;	
	}

	//------------------------------------------------------------------------------
	//�T�[�t�F�C�X�̃Z�b�g
	//------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �����_�[�p�X�ԍ�
	//@in : 0(�o�b�N�o�b�t�@�ɖ߂�) 1(�^�[�Q�b�g�ԍ��̕ύX)
	void RenderScreen::ChangeTarGet(PDirectDevice Device, int renderPass, int mode)
	{
		switch(mode + 1)
		{
			case 1:	
				//�^�[�Q�b�g��߂�
				Device->SetRenderTarget( 0, this->back);
				//�X�e���V���^�[�Q�b�g��߂�
				Device->SetDepthStencilSurface(this->backofstencl);
				break;
			case 2:	
				//�^�[�Q�b�g�̕ύX
				Device->SetRenderTarget(renderPass, this->screen);
				//�X�e���V���^�[�Q�b�g�̕ύX
				Device->SetDepthStencilSurface(this->depthstencil);

				//�N���A���܂�
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