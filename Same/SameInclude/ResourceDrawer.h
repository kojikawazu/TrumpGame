#ifndef NanairoLib_VERTEX_H
#define NanairoLib_VERTEX_H

#ifndef RESOURCE_FUNCTION_H
#include <ResourceFunction.h>
#endif

#ifndef MYRIECTX_RENDER_H
#include <RenderScreen.h>
#endif

#ifndef NanairoLib_MYFONT
#include <DirectFont.h>
#endif

//----------------------------------------------------------
//�QD�摜���p�|���ɓ\���ĕ`�悷��N���X
//----------------------------------------------------------
namespace NanairoLib
{
	//---------------------------------------------------
	//�`��p�C���v�b�g���[�h
	//---------------------------------------------------
	#define BACK_FVF		(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)
	#define FVF_Artisan3		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	#define FVF_Artisan		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

	//---------------------------------------------------
	//�N���A�������o�b�t�@�̎��
	//---------------------------------------------------
	#define CLEAR_FVF_3D_1	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER)
	#define CLEAR_FVF_3D_2	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL)
	#define CLEAR_FVF_2D	(D3DXSPRITE_SORT_DEPTH_BACKTOFRONT | D3DXSPRITE_ALPHABLEND)

	//-------------------------------------------------------
	//DirectX�p�V�F�[�_
	//-------------------------------------------------------
	class Shader
	{
		public:
			LPD3DXEFFECT Effect;
			D3DXHANDLE texhandle;
			D3DXMATRIX matWorldProj;
			D3DXHANDLE hMatWorldProj;
			bool doingShader;
		
		public:
			//�f�R���n
			__IMPOETER Shader();
			__IMPOETER ~Shader();

			//----------------------------------------------
			//�V�F�[�_�[������
			//----------------------------------------------
			//@in : DirectX�p�f�o�C�X
			__IMPOETER void InitShader(IDirect3DDevice9 *Device, LPCSTR pass);

	};
	
	typedef Shader*			PShader;
	typedef const Shader*	PCShader;

	//--------------------------------------------------------
	//�|���摜�Z�b�g�E�`��N���X
	//--------------------------------------------------------
	class Artisan
	{
		private:	//���\�b�h�͌���Ȃ��恄��
			PDirectDevice		Device;
			PVertexBuffer		vertexBuffer;
			Shader*				shader;
			ArtisanVT_2D			vertex[4];
			ArtisanVT_3D			vertex3D[4];
			D3DXMATRIX			trans, proj;
			UINT				alpha;
			bool				alphaFlag;

		private:	//��������
			//-------------------------------------------------------
			//���ʂɒ��S���Z�b�g���ĕϊ��s��ŕϊ��A�FUV�̓f�t�H���g	
			//-------------------------------------------------------
			__IMPOETER void TransNormal();	
			__IMPOETER void TransWorld();
			__IMPOETER void SetDrawShader(PTexture text);

			//----------------------------------------------------------------------------------------
			//���_���W�𒼐ڃZ�b�g���āA�FUV�̓f�t�H���g
			//----------------------------------------------------------------------------------------
			//@in : ������W
			//@in : �E����W
			//@in : �������W
			//@in : �E�����W
			__IMPOETER void TransVertex(RCVector2 lup,RCVector2 rup,RCVector2 lbot,RCVector2 rbot);

			//------------------------------------------------------------------------------------
			//�O�p�`�Ƃ��Ē��_���W�𒼐ڃZ�b�g���āA�FUV�̓f�t�H���g�i��ʃp���[��������邽�ߗp�j
			//------------------------------------------------------------------------------------
			//@in : ������W
			//@in : �E����W
			//@in : �c��O�p�`���W
			__IMPOETER void TransTriangle(RCVector2 lup,RCVector2 rup,RCVector2 rbot);

			//---------------------------------------------------
			//���ʒ��_�ϊ�
			//�����摜��UV���蓖�āiTEXTURE�\���̂ɕ��A�����A���������A���������������Ă���̂Łj
			//���蓖�Ă����ԍ����w�肷��΂���UV����������I
			//---------------------------------------------------
			//@in : ���蓖�Ĕԍ�
			//@in : �e�N�X�`�����
			__IMPOETER void TransDivisionPoint(int num,PCTEXTUREH  text);
			
			//----------------------------------------------------------------------
			//�����ŕ��������A���������������߂āA���蓖�Ă����ԍ����w�肷��
			//�������ł��ő�A�j���ԍ��̔���͂����I�@�O�Ŕ��f�I
			//----------------------------------------------------------------------
			//@in : ���蓖�Ĕԍ�
			//@in : ���ԍ����v
			//@in : �c�ԍ����v
			//@in : �e�N�X�`���f�[�^�N���X
			__IMPOETER void TransModi(int num,int wnum,int hnum,PCTEXTUREH  text);

			//-------------------------------------------------------------------------------------------
			//�O�p�`�Ƃ���UV��ϊ�����B
			//���A�����A���������A�����������A�j���ԍ��������Ō��߂�
			//mode�́��n�����n��
			//-------------------------------------------------------------------------------------------
			//@in : ���蓖�Ĕԍ�
			//@in : ���ԍ����v
			//@in : �c�ԍ����v
			//@in : ��
			//@in : ����
			//@in : ����mode�Q��
			__IMPOETER void TransTriangleModi(int num,int wnum,int hnum,int width,int height,bool IsUp);
			
			//-------------------------------------------------------------
			//�X�N���[���̕����ϊ�
			//(��)2�l�v���C�̎��ɉ�ʂ����ɂQ�������
			//-------------------------------------------------------------
			//@in : �X�N���[���̐�
			//@in : �`�悵�����X�N���[���ԍ�
			__IMPOETER void TransScreenDivision(int screenSum, int screenNum);
		public:
			//�޺݌n
			__IMPOETER Artisan();
			__IMPOETER ~Artisan();

			//�V�F�[�_���g���������́��̃��\�b�h�ŏ�����
			__IMPOETER void InitShader(LPCSTR pass);
			__IMPOETER void SetShader(Shader* in);
			__IMPOETER Shader* GetShader() const;

		public:
			__IMPOETER void SetScreenTrans(RenderScreen* sc); 

			//----------------------------------------------------------------
			//���_�o�b�t�@���i�[
			//----------------------------------------------------------------
			__IMPOETER bool SetVertexBuffer();

			//--------------------------------------------------------------------------------------------------------------------
			// �s��ɕϊ�
			//--------------------------------------------------------------------------------------------------------------------
			//@in : �ϊ��ʒu
			//@in : �ϊ��g��k��
			//@in : �ϊ��p�x
			//@in : �e�N�X�`���f�[�^�N���X
			//@in : �J���[���
			//@in : �X�P�[�����[�h
			__IMPOETER D3DXMATRIX Transform(RCVector2 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,int mode = 0);
			
			//--------------------------------------------------------------------------------------------------------------------
			// �s��ɕϊ�
			//--------------------------------------------------------------------------------------------------------------------
			//@in : �ϊ��ʒu
			//@in : �ϊ��g��k��
			//@in : �ϊ��p�x
			__IMPOETER D3DXMATRIX Transform(RCVector2 pos, RCVector2 scale, float angle);
			
			//--------------------------------------------------------------------------------------------------------------------
			// �s��ɕϊ�
			//--------------------------------------------------------------------------------------------------------------------
			//@in : �ϊ��ʒu
			//@in : �ϊ��g��k��
			//@in : �ϊ��p�x
			//@in : �t�H���g�f�[�^�N���X
			//@in : �J���[���
			//@in : �X�P�[�����[�h
			__IMPOETER D3DXMATRIX TransformW(RCVector2 pos, RCVector2 scale, float angle,PMyFont text,PCVector4 color,int mode = 0);
			
			//---------------------------------------------------------------------------------------------------------------------------
			//�R�c��ԏ�ɕ\��
			//---------------------------------------------------------------------------------------------------------------------------
			//@in : �ϊ��ʒu
			//@in : �ϊ��g��k��
			//@in : �ϊ��p�x
			//@in : �e�N�X�`���f�[�^�N���X
			//@in : �J���[���
			//@in : �X�P�[�����[�h
			__IMPOETER D3DXMATRIX Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCTEXTUREH text,PCVector4 color,int mode = 0);
			
			//---------------------------------------------------------------------------------------------------------------------------
			//�R�c��ԏ�ɕ\��(�r���{�[�h)
			//---------------------------------------------------------------------------------------------------------------------------
			//@in : �ϊ��ʒu
			//@in : �ϊ��g��k��
			//@in : �ϊ��p�x
			//@in : �e�N�X�`���f�[�^�N���X
			//@in : �J���[���
			//@in : �r���{�[�h�s��
			//@in : �X�P�[�����[�h
			__IMPOETER D3DXMATRIX Transform3D_ofBillboard(PCVector3 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,PCMATRIX board,int mode = 0);

		
			//-----------------------------------------------
			//�J���[���̃Z�b�g
			//-----------------------------------------------
			//@in : �J���[���
			__IMPOETER void SetColor(PCVector4 color);
			
			//-----------------------------------------------
			//�V�F�[�_�[��ŃJ���[���̃Z�b�g
			//-----------------------------------------------
			//@in : �J���[���
			__IMPOETER void SetShaderColor(PCVector4 color);
			
			//-----------------------------------------------
			//8bit(rgba)�̃J���[���ɕϊ����Đݒ�
			//-----------------------------------------------
			//@in : ����J���[���
			//@in : �E��J���[���
			//@in : �����J���[���
			//@in : �E���J���[���
			__IMPOETER void Set8BitColor(PCVector4 lup, PCVector4 rup, PCVector4 lbot, PCVector4 rbot);
			
			//---------------------------------------------
			//�v���W�F�N�V�����̐ݒ�
			//---------------------------------------------
			//@in : �v���W�F�N�V�����s��
			__IMPOETER void SetProjection(PCMATRIX p);
		public:
			//------------------------------------------------
			//DirectX�p�e�N�X�`���𒼐ݒ肵�ĕ`��
			//------------------------------------------------
			//@in : DirectX�p�e�N�X�`��
			__IMPOETER void DrawVertexBuffer(PTexture text );
			
			//--------------------------------------------------------
			//�ݒ肵�I������ԂŌ�͉摜��`�悷�邾���̎��͂���I
			//--------------------------------------------------------
			//@in : �e�N�X�`�����
			__IMPOETER void DrawVertexBuffer(PCTEXTUREH text);
			
			//--------------------------------------------------------
			//�t�H���g���̕`��
			//--------------------------------------------------------
			//@in : �t�H���g�e�N�X�`�����
			__IMPOETER void DrawVertexBuffer(PMyFont text);
			
			//--------------------------------------------------------
			//�X�N���[���S�̂̕`��
			//--------------------------------------------------------
			__IMPOETER void DrawVertexWall();

			//--------------------------------------------------------
			//�X�N���[���S�̂̕`��
			//--------------------------------------------------------
			__IMPOETER void DrawScreen(PTexture text);

			//--------------------------------------------------------------------------
			//�ݒ肵�I������ԂŃA�j���摜�̔ԍ���ݒ肷�邾���ŃA�j���[�V�����\�ɁI
			//�����`��
			//--------------------------------------------------------------------------
			//@in : �e�N�X�`�����
			//@in : ���蓖�Ĕԍ�
			__IMPOETER void DrawVertexBufferIndex(PCTEXTUREH text, int number);

			//---------------------------------------------------------------------------------
			//�����Œ��_���W��ݒ肵�āA�����������ݒ�A�����ăA�j���[�V�����ԍ������ĕ`��
			//���ژM�肽���p
			//---------------------------------------------------------------------------------
			//@in : �e�N�X�`�����
			//@in : ������W
			//@in : �E����W
			//@in : �������W
			//@in : �E�����W
			__IMPOETER void DrawVertexBufferIndexModi(PCTEXTUREH text, RCVector2 p1,
																	RCVector2 p2,RCVector2 p3,RCVector2 p4,
																		int number, int wnum, int hnum);

			//-------------------------------------------------------------------
			//�����Œ��_���W��ݒ肵�āA�����ăA�j���[�V�����ԍ������ĕ`��
			//�A�j���[�V�������̓f�t�H���g�ɂȂ�܂�
			//-------------------------------------------------------------------
			//@in : ������W
			//@in : �E����W
			//@in : �������W
			//@in : �E�����W
			//@in : ���蓖�Ĕԍ�
			//@in : �e�N�X�`�����
			__IMPOETER void DrawRectDepGraph(RCVector2 lup,RCVector2 rup,
														RCVector2 lbot,RCVector2 rbot,int num,PCTEXTUREH  text);
			
			//-------------------------------------------------------------------------------------------------------------------------
			//���_���W�A�ő啝�����A�����������A���蓖�Ĕԍ���
			//��ʂ����邽�߂����ɂ��郁�\�b�h
			//-------------------------------------------------------------------------------------------------------------------------
			//@in : �e�N�X�`�����
			//@in : ������W
			//@in : �E����W
			//@in : �������W
			//@in : ���蓖�Ĕԍ�
			//@in : ���������v��
			//@in : �����c���v��
			//@in : ��
			//@in : ����
			//@in : ���[�h
			__IMPOETER void DrawIndexGlassHopper(PTexture text, RCVector2 p1,
											RCVector2 p2,RCVector2 p3,int number, int wnum, int hnum,int width,int height,bool IsUp);
			
			//--------------------------------------------------------
			//3D��ԏ�̕`��
			//--------------------------------------------------------
			__IMPOETER void DrawVertexGraph_3D(PCTEXTUREH text);

		public:	//�A���t�@�n
			//�A���t�@�u�����h�̃Z�b�g
			//1~14 ���A���t�@�u�����h���[�h
			//15�͂Ȃ����[�h
			//------------------------------------------------
			//�A���t�@���[�h�̃Z�b�e�B���O
			//------------------------------------------------
			__IMPOETER void SetAlphaMode(COLOR_BLEND_NUM mode = BNONE,DWORD dwal = 0x00888888);	
			
			//-----------------------------------------
			//�f�o�C�X���Z�b�g����
			//-----------------------------------------
			__IMPOETER void SetDevice(PDirectDevice Device);
			
			//------------------------------
			//�ϊ��s��̏�����
			//------------------------------
			__IMPOETER void InitMatrix();
	};

	typedef Artisan*			PArtisan;
	typedef const Artisan*	PCArtisan;

}
#endif