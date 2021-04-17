#ifndef _NanairoLib_MODEL_H
#define _NanairoLib_MODEL_H

#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

namespace NanairoLib
{

	//----------------------------
	//3D�Î~��Ԃ̃��f��
	//----------------------------
	class MyModel
	{
		private:
			MODELH parts;
			D3DXVECTOR4 color;
		public:
			__IMPOETER MyModel();
			__IMPOETER ~MyModel();
		public:
			//----------------------------------
			//���̃��f���͑��݂��Ă��邩
			//----------------------------------
			//@out : true(����) false(���s)
			__IMPOETER bool isUse();
			//----------------------------------
			//���̃��f���ɑ΂��邠���蔻��p�f�[�^�͑��݂��Ă��邩
			//----------------------------------
			//@out : true(����) false(���s)
			__IMPOETER int GetAtackPointNumber();

			//----------------------------------
			//���̃��f���̃}�e���A���̐����擾
			//----------------------------------
			//@out : �}�e���A���̐�
			__IMPOETER int GetMaterialSum();

			//----------------------------------
			//���̃��f���̃��b�V�����擾
			//----------------------------------
			//@out : ���b�V���C���^�[�t�F�C�X�|�C���^
			__IMPOETER const ID3DXMesh* GetMesh();

			//----------------------------------
			//���̃��f���̃}�e���A�����擾
			//----------------------------------
			//@out : �}�e���A���C���^�[�t�F�C�X�|�C���^
			__IMPOETER const D3DMATERIAL9* GetMaterial();

			//----------------------------------
			//���̃��f���̃f�[�^�|�C���^�̎擾
			//----------------------------------
			//@out : ���f���̃f�[�^�|�C���^
			__IMPOETER PMODELH GetModelPoint() const;

			//----------------------------------
			//���̃��f���̃f�[�^�|�C���^�̃Z�b�e�B���O
			//----------------------------------
			//@in : ���f���̃f�[�^�|�C���^
			__IMPOETER void SetModelH(MODELH* model);

		public:
			//----------------------------------
			//���f���̃��[�h
			//----------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : �t�@�C���p�X
			//@in : ���[�h
			//@out : true(����) false(���s)
			__IMPOETER bool loadModel(PDirectDevice Device,LPCSTR fileName,int mode);
			
			//----------------------------------
			//���̃��f���̃����[�X
			//----------------------------------
			__IMPOETER void releaseModel();
			
			//----------------------------------
			//���̃��f���̃��[���h�s��̃Z�b�e�B���O
			//----------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : ���[���h�s��
			//@in : �V�F�[�_�[�N���X
			__IMPOETER void SettingWorld(IDirect3DDevice9* Device,const D3DXMATRIX* mat,Shader* shader = NULL);
			
			//----------------------------------
			//���̃��f���̕`��
			//----------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : �V�F�[�_�[�N���X
			//@in : �e�N�X�`���f�[�^�|�C���^
			//@in : ���[�h
			__IMPOETER void drawModel(IDirect3DDevice9* Device,Shader* shader = NULL,TEXTUREH* text = NULL,int mode = 0);
			__IMPOETER void drawNoShaderModel(IDirect3DDevice9* Device,TEXTUREH* text = NULL,int mode = 0);
			__IMPOETER void drawShaderModel(IDirect3DDevice9* Device,Shader* shader = NULL,TEXTUREH* text = NULL,int mode = 0);

	};

	typedef MyModel*		PMyModel;
	typedef const MyModel*	PCMyModel;
}

#endif