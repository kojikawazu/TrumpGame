#ifndef NanairoLib_GRAPH_H
#define NanairoLib_GRAPH_H

#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

//----------------------------------------------------------
//�QD�摜���p�|���ɓ\���ĕ`�悷��N���X
//----------------------------------------------------------
namespace NanairoLib
{

	class MyGraph
	{
		private:
			TEXTUREH	parts;
			Vector4		color;
			Artisan*	 art;

		private:
			//------------------------------
			//������
			//------------------------------
			__IMPOETER void sameInit();
		public:
			__IMPOETER MyGraph();
			__IMPOETER MyGraph(PTEXTUREH handle);
			__IMPOETER ~MyGraph();
		
			Artisan* GetArtisan() const{		return this->art;		}
			void SetArtisan(Artisan* in){	this->art = in;	}

		public:
			//----------------------------------------------------------------
			//�e�N�X�`���̃Z�b�e�B���O
			//----------------------------------------------------------------
			//@in : �e�N�X�`��
			//@in : ��
			//@in : ����
			__IMPOETER void SetTexture(IDirect3DTexture9* gh, float wh, float ht);
			
			//----------------------------------------------
			//�����̃Z�b�e�B���O
			//----------------------------------------------
			//@in : ��������
			//@in : �����c��
			__IMPOETER void SetDivision(int divX = 1, int divY = 1);

			//----------------------------------------------
			//���[�h�e�N�X�`��
			//----------------------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : �t�@�C���p�X
			//@in : ��
			//@in : ����
			//@in : ��������
			//@in : �����c��
			__IMPOETER bool LoadTexture(PDirectDevice Device,LPCSTR fileName,int width,int height,int sumW = 0,int sumH = 0);
			
			//----------------------------------------------
			//�e�N�X�`���̃����[�X
			//----------------------------------------------
			__IMPOETER void ReleaseTexture();
	
		public:
			//----------------------------------------------
			//�e�N�X�`���n���h���̎擾
			//----------------------------------------------
			//@out : �e�N�X�`���n���h��
			__IMPOETER PCTEXTUREH GetTextureHandle();

			//----------------------------------------------
			//�e�N�X�`���n���h���|�C���^�̎擾
			//----------------------------------------------
			//@out : �e�N�X�`���n���h��
			__IMPOETER PTEXTUREH GetTexturePointer();

			//----------------------------------------------
			//�e�N�X�`���̎擾
			//----------------------------------------------
			//@out : DirectX�p�e�N�X�`��
			__IMPOETER const IDirect3DTexture9* GetTexture();

			//----------------------------------------------
			//�J���[�̎擾
			//----------------------------------------------
			__IMPOETER PCVector4 GetColor();

			//----------------------------------------------
			//�J���[�̃Z�b�e�B���O
			//----------------------------------------------
			//@in : argb
			__IMPOETER void SetColor(float a, float r, float g, float b);
			__IMPOETER void SetColor(PCVector4 col);

			//----------------------------------------------
			//�e�N�X�`���̕��ʂɕ`��
			//----------------------------------------------
			//@in : �`���p�N���X
			__IMPOETER void Draw_Graph(Artisan* Artisan);
			
			//----------------------------------------------
			//�e�N�X�`���̃A�j���[�V�����`��
			//----------------------------------------------
			//@in : �`���p�N���X
			//@in : ���蓖�Ĕԍ�
			__IMPOETER void Draw_Animation_Graph(int number);

			//----------------------------------------------
			//�e�N�X�`���̒����W�ݒ�E�������`��
			//----------------------------------------------
			//@in : �`���p�N���X
			//@in : �l�p�̍��W�x�N�g��
			//@in : ��������
			//@in : �����c��
			//@in : ���蓖�Ĕԍ�
			__IMPOETER void Draw_Modi_div_Animation_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number, int divXSum, int divYSum);
			
			//----------------------------------------------
			//�e�N�X�`���̒����W�ݒ�E�A�j���[�V�����`��
			//----------------------------------------------
			//@in : �`���p�N���X
			//@in : �l�p�̍��W�x�N�g��
			//@in : ���蓖�Ĕԍ�
			__IMPOETER void Draw_Modi_Animation_Graph( RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number);
			
			//----------------------------------------------
			//�e�N�X�`���̃K���X�̂悤�ȕ`��
			//----------------------------------------------
			//@in : �`���p�N���X
			//@in : �O�p�`�̍��W�x�N�g��
			//@in : ������
			//@in : ��������
			//@in : ��������
			//@in : �����c��
			//@in : ���蓖�Ĕԍ�
			__IMPOETER void Draw_Grass_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot,int number, int divXSum, int divYSum, int width, int height, bool IsUp);

			//----------------------------------------------
			//�`��̃g�����X�t�H�[��
			//----------------------------------------------
			//@in : �`���p�N���X
			//@in : �ʒu
			//@in : �X�P�[��
			//@in : �p�x
			//@in : �F���
			//@in : �X�P�[�����[�h
			__IMPOETER void Transform(RCVector2 pos, RCVector2 scale, float angle,PCVector4 color,int mode);
			
			//----------------------------------------------
			//�`��̃g�����X�t�H�[��(3D�p)
			//----------------------------------------------
			//@in : �`���p�N���X
			//@in : �ʒu
			//@in : �X�P�[��
			//@in : �p�x
			//@in : �F���
			//@in : �X�P�[�����[�h
			__IMPOETER void Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCVector4 color,int mode);
			
			//----------------------------------------------
			//�`��̃g�����X�t�H�[��(�r���{�[�h�p)
			//----------------------------------------------
			//@in : �`���p�N���X
			//@in : �ʒu
			//@in : �X�P�[��
			//@in : �p�x
			//@in : �F���
			//@in : �r���{�[�h�s��
			//@in : �X�P�[�����[�h
			__IMPOETER void TransformBillboard(PCVector3 pos, RCVector2 scale, float angle,PCVector4 color, PCMATRIX board, int mode);
	};
	
}
#endif