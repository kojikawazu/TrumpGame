#ifndef MYGAME_MESH_H
#define MYGAME_MESH_H

//-------------------------------------------------
//�A�j���[�V�����X�L�����b�V�����Ǘ�����N���X
//-------------------------------------------------
#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

#if(D3D_SDK_VERSION >= 32)
	#define CONST_90C const
#else
	#define CONST_90C
#endif

namespace NanairoLib
{
	//----------------------------------------------------------------------
	//�t���[�����N���X
	//�s���ێ�
	//----------------------------------------------------------------------
	class MY_FRAME : public ::D3DXFRAME
	{
		public:
			//�ŏ��̏�Ԃ��o���Ă����B
			D3DXMATRIX originalMatrix;
	};

	//----------------------------------------------------------------------
	//���b�V���R���e�i�N���X
	//----------------------------------------------------------------------
	class MY_HIERARCHY : public ::ID3DXAllocateHierarchy
	{
		private:
			IDirect3DDevice9*	_devices;
			Shader*				_shader;
		public:
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall CreateFrame(const char *filaName,D3DXFRAME **frame);
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall CreateMeshContainer(
				LPCSTR name,
				CONST_90C D3DXMESHDATA *meshData,
				CONST_90C D3DXMATERIAL *materials,
				CONST_90C D3DXEFFECTINSTANCE *effectInstances,
				DWORD materialNum,
				CONST_90C DWORD *pAdjacency,
				ID3DXSkinInfo *skinInfo,
				D3DXMESHCONTAINER **newMeshContainer);
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall DestroyFrame(D3DXFRAME *frame);
			__IMPOETER virtual __declspec(nothrow) HRESULT __stdcall DestroyMeshContainer(D3DXMESHCONTAINER *meshContainer);
	
		public:
			__IMPOETER MY_HIERARCHY() : _devices(0), _shader(0){}
			__IMPOETER void SetDevice(IDirect3DDevice9* device){	this->_devices = device;	}
			__IMPOETER IDirect3DDevice9* GetDevice(){				return this->_devices;		}
			__IMPOETER void SetShader(Shader* sha){					this->_shader = sha;		}
			__IMPOETER Shader* GetShader(){							return this->_shader;		}
	};

	//----------------------------------------------------------------------
	//�A�j���[�V�����p���b�V���f�[�^�\����
	//----------------------------------------------------------------------
	class MY_D3DXMESHCONTAINER : public D3DXMESHCONTAINER
	{
	public:
		//�A�j���[�V�����チ�b�V���f�[�^
		//�\���p�ɁA�I���W�i�����b�V���f�[�^�ɃA�j���[�V������K�p������Ԃ��L��
		ID3DXMesh *workMesh;

		//�{�[���A�j���[�V�����}�g���N�X
		//��ԍX�V�֐��Ăяo�����ɏ�ԕύX�}�g���b�N�X�������Ă���B
		D3DXMATRIX *boneUpdateMatrix;

		//�}�e���A����
		int materialNum;

		//�}�e���A�����
		D3DMATERIAL9 *materials;

		//�e�N�X�`�����
		IDirect3DTexture9 **textures;
	
	public:
		__IMPOETER MY_D3DXMESHCONTAINER();
		__IMPOETER ~MY_D3DXMESHCONTAINER();
	};

	//----------------------------------------------------------------------
	//�A�j���[�V�������b�V���i�������f���f�[�^�j�������N���X
	//----------------------------------------------------------------------
	class MY_MESH
	{
		static MY_HIERARCHY hierarchy;	//�������̎��Ԃ�MY_HIERARCHY�N���X�Ɂi�g���񂵉\�j

		//�f�[�^
		//------------------------------------------------------
	protected:
		//���b�V�����[�g�i�|���S���Q�̃c���[�̃��[�g�j
		D3DXFRAME *root;
		//�A�j���[�V�����R���g���[��
		ID3DXAnimationController *animController;

		//������
		//------------------------------------------------------
	public:
		__IMPOETER MY_MESH();
		__IMPOETER MY_MESH(IDirect3DDevice9 *device,const char *fileName);
		__IMPOETER ~MY_MESH();

		__IMPOETER static MY_HIERARCHY* GetHierarchy()
		{
			return &hierarchy;
		}
		
	protected:	//��ԍX�V���`��
		//----------------------------------------------------
		//�A�j���[�V�����̃o�b�N�A�b�v
		//----------------------------------------------------
		//@in : �t���[�����
		__IMPOETER void _backupAnimationMatrix(D3DXFRAME *frame);

		//----------------------------------------------------
		//�A�j���[�V�����̃��Z�b�g
		//----------------------------------------------------
		//@in : �t���[�����
		__IMPOETER void _reSetAnimationMatrix(D3DXFRAME *frame);

		//-----------------------------------------------------
		//�A�j���[�V�����X�V
		//------------------------------------------------------
		//@in : �t���[�����
		//@out : �ϊ��s��
		__IMPOETER void _updateAnimationMatrix(D3DXFRAME *frame,D3DXMATRIX *mat);

		//---------------------------------------------------------------------
		//�`��̌Ăяo��
		//---------------------------------------------------------------------
		//@in : �t���[�����
		//@in : �ϊ��s��
		//@in : �F�������[�h
		__IMPOETER void _callDrawMesh(D3DXFRAME *frame,D3DXMATRIX *m, int mode);

		//-----------------------------------------------------------------------------
		//�R���e�i�ɓ����Ă���f�[�^���h���[
		//-----------------------------------------------------------------------------
		//@in : �R���e�i�ɓ����Ă�����
		//@in : �t���[�����
		//@in : �ϊ��s��
		//@in : �F�������[�h
		__IMPOETER void _drawMeshContainer(MY_D3DXMESHCONTAINER *meshContainer,D3DXFRAME *frame,D3DXMATRIX *m, int mode);
	public:
		/*
			���Ԍo�߂ŃA�j���[�V���������A�\������
			@param Set�@	�A�j���[�V�����ԍ�
			@param passTime �o�ߎ���(ms)
			@param m		�\���p�}�g���N�X
		*/
		__IMPOETER void draw(int Set,unsigned int passTime,D3DXMATRIX *m, int mode = 0);

		
	protected:
		//------------------------------------------------------------------
		//�R�s�[�K�[�h�i�|�C���^���܂ރN���X�Ȃ̂ŁA�R�s�[�ł��Ȃ��悤�Ɂj
		//------------------------------------------------------------------
		__IMPOETER MY_MESH(MY_MESH &mesh){}
		__IMPOETER MY_MESH& operator = (MY_MESH &mesh){	return *this;	}
	};
}


#endif