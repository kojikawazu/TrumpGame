#ifndef NanairoLib_MYFONT
#define NanairoLib_MYFONT
//------------------------------------------------------------
//DirectX�ň����t�H���g�i1�����j��
//�f�o�C�X�R���e�L�X�g�Ńe�N�X�`���Ƀy�C���g����N���X
//------------------------------------------------------------
#ifndef RESOURCE_FUNCTION_H
#include <ResourceFunction.h>
#endif

namespace NanairoLib
{
	#define __WordFontType "���C���I"

	//�t�H���g�\���̂̃t�B�[���h���ڂ��Ă����܂�
	//���t�H���g���y�C���g���ăe�N�X�`��
	//�����̃e�N�X�`���̕��ƍ���
	//typedef struct{
	//	int fontW,fontH;
	//	IDirect3DTexture9* fontText;	
	//}FONTH;

	//�t�H���g�i1�����j�N���X
	//��������X�g�ɓ���ĊǗ����Ă��������I
	class MyFont
	{
		private:
			FONTH font;
			bool OKFlag;

		private:
			//------------------------------------------------------------------------------------
			//�t�H���g���\�z���܂�
			//���������true���A���Ă��܂�
			//����������͓����ł̏����Ȃ̂ŋC�ɂ��Ȃ��Ă悵�I
			__IMPOETER bool createFont(PDirectDevice Device,PCUINT cd);

		public:
			//�t�H���g�N���X�𐶐�����Ɠ����Ƀt�H���g�����܂��B
			//��x���ƕύX�͂����Ȃ��̂�
			//�ύX����Ƃ��͑��̃|�C���^�Ƃ���new���č���Ă��������B
			//-----------------------------------------------------------------------------------
			__IMPOETER MyFont();
			__IMPOETER MyFont(PDirectDevice Device,PCUINT C);
			__IMPOETER ~MyFont();
			
			//�擾�^�C�v--------------------------------------------------------------------------
			__IMPOETER PFONTH GetFont() const;
			__IMPOETER const bool isOK() const;
			//------------------------------------------------------------------------------------
	};

	typedef MyFont*	PMyFont;

	//�`�t�H���g�̍����`
	//MMyFont font = new MyFont( DirectX��Device, �������������� );
	
	//�`�t�H���g�̏����`
	//delete font;
	//�Ńe�N�X�`����������̂Ŗ��Ȃ��I
	//�����OK��false���Ƃ��̕����͎g���Ȃ��̂Ŏ����ŏ����Ăˁ`
}

#endif