#ifndef MYRIECTX_RENDER_H
#define MYRIECTX_RENDER_H

//-------------------------------------------------
//
//�X�N���[���V���b�g���B��Ƃ��Ɏg���N���X
//������g����2��ʕ������ʊ��Ȃǂ��ł���!
//
//-------------------------------------------------
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef MYDIRECTX_LIGHTCOLOR_H
#include <DirectLight.h>
#endif

namespace NanairoLib
{
	class RenderScreen
	{
		private:
			bool useOK;						//�����_�[���������t���O
			DWORD		tarGetNumber;		//�^�[�Q�b�g�ԍ�
			PSurface	back;				//�o�b�N�o�b�t�@
			PSurface	screen;				//�X�N���[���o�b�t�@
			PSurface	depthstencil;		//�X�N���[���[�x
			PSurface	backofstencl;		//�o�b�N�[�x
			PTexture	texture;			//�^�[�Q�b�g�e�N�X�`��

		public:
			short screenSum, screenNum;
			Textcolor	color;

		private:
			//-------------------------------------------------
			//���߂̃T�[�t�F�C�X�ƃe�N�X�`���̍쐬
			//-------------------------------------------------
			//@in : DirectX�p�f�o�C�X	
			__IMPOETER		void InitTarGet(PDirectDevice Device);
			
		public:

			__IMPOETER		RenderScreen();
			__IMPOETER		RenderScreen(PDirectDevice Device, DWORD num);
			__IMPOETER		~RenderScreen();
		
			//------------------------------------------------------------------------------
			//�T�[�t�F�C�X�̃Z�b�g
			//------------------------------------------------------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : �����_�[�p�X�ԍ�
			//@in : 0(�o�b�N�o�b�t�@�ɖ߂�) 1(�^�[�Q�b�g�ԍ��̕ύX)
			__IMPOETER		void		ChangeTarGet(PDirectDevice Device, int renderPass = 0, int mode = 0);
			
			//--------------------------------------
			//�ۑ������X�N���[���̃e�N�X�`���̎擾
			//--------------------------------------
			__IMPOETER		PTexture	GetTexture() const;											
	};

	typedef RenderScreen*		PRenderScreen;
	typedef const RenderScreen*	PCRenderScreen;
}
#endif