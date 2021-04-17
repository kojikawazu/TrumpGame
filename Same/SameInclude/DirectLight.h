#ifndef MYDIRECTX_LIGHTCOLOR_H
#define MYDIRECTX_LIGHTCOLOR_H

//----------------------------------------------------------
//
//���C�g�ƐF�N���X�������Ɋi�[
//
//----------------------------------------------------------
#ifndef _NanairoLib_MYVECTOR_H
#include <DirectParts.h>
#endif

//DX���C�g�ƃJ���[�N���X
namespace NanairoLib
{
	//---------------------------------
	//DX���C�g
	//�Œ�p�C�v���C���p���C�g
	//---------------------------------
	class Light
	{
		private:	
			D3DLIGHT9 lighting;		//DX���C�g�\����
			short number,mode;		//DX���C�g�ԍ��A�f�t�H���g�Z�b�g�ԍ�

		public:		
			//----------------------------------------------------
			//�R���X�g���N�^
			//----------------------------------------------------
			//@in : ���C�g�ԍ�
			//@in : �f�t�H���g�ݒ�ԍ�
			__IMPOETER		Light(int num,int mode = 1);
			__IMPOETER		Light();
			__IMPOETER		~Light();
		
		public:		
			//-----------------------------------------------------
			//�ݒ�E�擾
			//-----------------------------------------------------
			//@in : DirectX�p�f�o�C�X
			__IMPOETER		void Setlighting(PDirectDevice Device);
			__IMPOETER		D3DLIGHT9* GetLight();
	};
	
	//---------------------------------
	//�e�N�X�`���̐F
	//(argb�w��)
	//---------------------------------
	class Textcolor
	{
		public:	
			//-----------------------------------
			//�F���
			//(x : a) (y : r) (z : g) (w : b)
			//-----------------------------------
			Vector4 color, target;

		public:	
			//--------------------------------------------
			//�޺݌n
			//--------------------------------------------
			__IMPOETER		Textcolor();
			__IMPOETER		Textcolor(const Vector4* col);
			__IMPOETER		Textcolor(float da, float dr, float dg, float db);
			__IMPOETER		~Textcolor();

		public:	
			//-----------------------------------------------
			//�R�s�[
			//-----------------------------------------------
			__IMPOETER Textcolor& operator = (const Textcolor* col);
			__IMPOETER Textcolor& operator = (const Textcolor col);
			__IMPOETER Textcolor& operator = (Vector4 col);	//�R�s�[
			__IMPOETER Textcolor& operator = (PCVector4 col);	//�R�s�[

			//----------------------------------------------------------------------
			//���Z����
			//----------------------------------------------------------------------
			__IMPOETER Textcolor operator - (int a);	//�Ώۂ̒l�����炷
			__IMPOETER Textcolor operator - (PCVector4 col);	//�J���[�����炷
			__IMPOETER Textcolor& operator -= (int a);	//�Ώۂ̒l�����炷
			__IMPOETER Textcolor& operator -= (PCVector4 col);	//�Ώۂ̒l�����炷

			//----------------------------------------------------------------------
			//���Z����
			//----------------------------------------------------------------------
			__IMPOETER Textcolor operator + (int a);	//�Ώۂ̒l�𑝂₷
			__IMPOETER Textcolor operator + (PCVector4 col);	//�J���[�𑝂₷
			__IMPOETER Textcolor& operator += (int a);	//�Ώۂ̒l�����炷
			__IMPOETER Textcolor& operator += (PCVector4 col);	//�Ώۂ̒l�����炷

			//----------------------------------------------------------------------
			//���Z����
			//----------------------------------------------------------------------
			__IMPOETER Textcolor& operator -- (int a);	//1���炷
			
			//----------------------------------------------------------------------
			//���Z����
			//----------------------------------------------------------------------
			__IMPOETER Textcolor& operator ++ (int a);	//1���₷
			
			//----------------------------------------------------------------------
			//��������
			//----------------------------------------------------------------------
			__IMPOETER void operator * (PCVector4 col);
			
			//----------------------------------------------------------------------
			//���Z����
			//----------------------------------------------------------------------
			__IMPOETER void operator / (PCVector4 col);

		public:	//�ݒ�E�擾
			//----------------------------------------------------------------------
			//�J���[�̃Z�b�e�B���O
			//----------------------------------------------------------------------
			__IMPOETER void SetColor(int a,int r,int g,int b);
			__IMPOETER void SetMaxColor();
			__IMPOETER void SetMinColor();
			__IMPOETER void SetColor(PCVector4 col);
			__IMPOETER void SetAlpha(int a);
			
			//----------------------------------------------------------------------
			//�J���[�̎擾
			//----------------------------------------------------------------------
			__IMPOETER float GetColor(int mode);
			__IMPOETER Vector4 GetColor();
			__IMPOETER float GetAlpha();

			//----------------------------------------------------------------------
			//�J���[�̃t�F�[�h�C��
			//----------------------------------------------------------------------
			__IMPOETER bool FadeIn(float al);
			__IMPOETER bool FadeIn(PCVector4 col);

			//----------------------------------------------------------------------
			//�J���[�̃t�F�[�h�A�E�g
			//----------------------------------------------------------------------
			__IMPOETER bool FadeOut(float al);
			__IMPOETER bool FadeOut(PCVector4 col);
			
			//----------------------------------------------------------------------
			//�J���[�̃t�F�[�h���邽�߂̃Z�b�e�B���O
			//----------------------------------------------------------------------
			__IMPOETER void SettingFadeAlpha();
			__IMPOETER void SettingTextcolor();
	};

	typedef Textcolor*			PColor;
	typedef const Textcolor*	PCColor;
}
#endif