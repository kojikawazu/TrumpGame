#ifndef RESOURCE_FUNCTION_H
#define RESOURCE_FUNCTION_H

//-----------------------------------------
//���蓖�Č^�֐��N���X�������ɋL��
//�K�v�Ȋ֐��𑝂₵����g���������͂����̃N���X���g����
//���f�[�^�ێ����K�v�ȏꍇ�͂��̃N���X�ɂ͓���邱�Ƃ͂ł��܂��񁄁�
//-----------------------------------------
#ifndef NanairoLib_FUNC_H
#include <DirectFunction.h>
#endif

namespace NanairoLib
{
	//�e�N�X�`���\����
	typedef struct TEXTUREHH
	{
		//�g�p���A������
		bool used, division;
		//���A�����A�����v�A�c���v
		int width, height, sumX, sumY, oneW, oneH;
		//�e�N�X�`��
		IDirect3DTexture9* graph;
	}TEXTUREH;

	//���f���\����
	typedef struct MODELHH
	{
		bool used;
		int atackNumber;
		int matelSum;
		ID3DXMesh *mesh;
		D3DMATERIAL9 *matel;
		IDirect3DTexture9 **textureX;
	}MODELH;

	//�����蔻��\����
	typedef struct MODELATACKH
	{
		bool		used;
		int			meshIndex[2000][3];
		DWORD		meshSum;
		DWORD		vertexSum;
		D3DXVECTOR3 meshVertex[1000];
		D3DXVECTOR3 meshNormal[1000];
	}ATACKH;

	//�t�H���g�\����
	typedef struct MYFONT
	{
		int fontW,fontH;
		IDirect3DTexture9* fontText;	
	}FONTH;

	//�W�����_�V�F�[�_�\����
	typedef struct COSTOMVERTEX_2D
	{
		float x,y,z;					//���_���W
		float rhw;						//���Z
		DWORD dwColor;					//���_�̐F
		float u,v;						//�e�N�X�`�����W
	}ArtisanVT_2D;

	typedef struct COSTOMVERTEX_3D
	{
		float x,y,z;					//���_���W
		float norX, norY, norZ;			//�@�����
		DWORD dwColor;					//���_�̐F
		float u,v;						//�e�N�X�`�����W
	}ArtisanVT_3D;

	typedef MODELH*					PMODELH;
	typedef const MODELH*			PCMODELH;
	typedef TEXTUREH*				PTEXTUREH;
	typedef const TEXTUREH*			PCTEXTUREH;
	typedef const ATACKH*			PCATACKH;
	typedef ATACKH*					PATACKH;

	typedef FONTH*					PFONTH;
	typedef ArtisanVT_2D*			PArtisanVT_2D;
	typedef ArtisanVT_3D*			PArtisanVT_3D;

	//------------------------------------------------------------------
	//�e�N�X�`���⃂�f���̃��[�h���������\�b�h��������
	//------------------------------------------------------------------
	class TextFunc
	{
	public:
		//--------------------------------------------
		//�e�N�X�`���̃��[�h
		//�摜���e�N�X�`���Ƃ��ēǂݍ���
		//--------------------------------------------
		//@in : DirectX�̃f�o�C�X
		//@inout : �e�N�X�`���̍\����
		//@in : �t�@�C����
		//@in : �摜�̕�
		//@in : �摜�̍���
		//@in : (��������Ƃ�)�摜�̉��ɕ��Ԑ�
		//@in : (��������Ƃ�)�摜�̏c�ɕ��Ԑ�
		//@out : ���s�����(-1) ���������(1)
		__IMPOETER int LoadGraphIndex(PDirectDevice Device,PTEXTUREH text,LPCSTR fileName,int width,int height,int sumW = 0,int sumH = 0);
		
		//--------------------------------------------
		//�摜��񓯊��ǂݍ��݂���
		//--------------------------------------------
		//@in : DirectX�̃f�o�C�X
		//@inout : �e�N�X�`���̍\����
		//@in : �ǂݍ��ފJ�n�ʒu
		//@in : �ǂݍ��ރT�C�Y
		//@out : ���s(-1) ����(1)
		__IMPOETER int LoadGraphIndexASYN(PDirectDevice Device,PTEXTUREH text,LPCSTR point,CINT size);
		
		//--------------------------------------------
		//���f���̃��[�h
		//--------------------------------------------
		//@in : DirectX�p�f�o�C�X
		//@in : �t�@�C����
		//@out : ���f���ۑ��N���X
		//@in : �ۑ��ԍ�
		//@out : true(����) false(���s)
		__IMPOETER bool LoadModel3D(PDirectDevice Device,LPCSTR fileName,MODELH *model,int mode = 0);
		
		//--------------------------------------------
		//�񓯊��p���f���̃��[�h
		//--------------------------------------------
		//@in: DirectX�p�f�o�C�X
		//@in : �A�h���X�|�C���^
		//@in : �f�[�^�T�C�Y
		//@inout : ���f���f�[�^
		//@in : �E�B���h�E�N���X
		//@in : 0(�A���r�G���g = �f�B�t���[�Y)
		//@out : 1(����) -1(���s)
		__IMPOETER int LoadModel3DASYN(PDirectDevice Device,LPCSTR point,int size,PMODELH model,HWND wnd,int mode);
		
		//--------------------------------------------
		//�����蔻��p���f���̃��[�h
		//--------------------------------------------
		//@in : DirectX�p�f�o�C�X
		//@in : �t�@�C���p�X
		//@input : �����蔻��p���f���f�[�^�N���X
		//@out : true(����) false(���s)
		__IMPOETER bool LoadModelAtack(PDirectDevice Device,LPCSTR fileName,PATACKH atack);

		//--------------------------------------------
		//�񓯊��p�����蔻��̃��[�h
		//--------------------------------------------
		//@in : DirectX�p�f�o�C�X
		//@in : �t�@�C���p�X
		//@in : �T�C�Y
		//@out : �����蔻��p�f�[�^�N���X
		//@in : �E�B���h�E�N���X
		//@out : 1(����) -1(���s)
		__IMPOETER int LoadModelAtackASYN(PDirectDevice Device,LPCSTR point,int size,PATACKH atack,HWND wnd);
			
		//-----------------------------------------------------------
		//�e�N�X�`�����畝�ƍ������擾
		//-----------------------------------------------------------
		//@in : �e�N�X�`���C���^�[�t�F�C�X
		//@out : ��
		//@out : ����
		__IMPOETER void SetTextureLong(IDirect3DTexture9* gh, int* wh, int* ht);
			

		//�f�t�H���g�R���X�g���N�^
		__IMPOETER TextFunc();
		//�f�t�H���g�f�X�g���N�^
		__IMPOETER ~TextFunc();
	};

}

#endif