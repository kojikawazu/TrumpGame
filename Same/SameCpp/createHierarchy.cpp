#pragma once
//--------------------------------------------------------------------------
//�A�j���[�V���������Ǘ�����R���e�i
//--------------------------------------------------------------------------
#pragma region �C���N���[�h
#define _NEED_FUNCI
#pragma warning(disable : 4996)
#include <AnimationMesh.h>
#pragma endregion

namespace NanairoLib
{

	//----------------------------------------------------------------
	//�t���[���f�[�^�̍쐬
	//----------------------------------------------------------------
	//@in : �t�@�C����
	//@in : �t���[�����
	__declspec(nothrow) HRESULT __stdcall 
	MY_HIERARCHY::CreateFrame(const char *fileName,D3DXFRAME **frame)
	{
		*frame = new MY_FRAME();
	
		//���O�t����
		if(fileName != NULL)
		{
			(*frame)->Name = new char[strlen(fileName) + 1];
			strcpy((*frame)->Name,fileName);
		}
		else	(*frame)->Name = NULL;
		return S_OK;
	}

	//-------------------------------------
	//���b�V���R���e�i�̐���
	//-------------------------------------
	__declspec(nothrow) HRESULT __stdcall
	MY_HIERARCHY::CreateMeshContainer(
			LPCSTR name,
			CONST_90C D3DXMESHDATA *meshData,
			CONST_90C D3DXMATERIAL *materials,
			CONST_90C D3DXEFFECTINSTANCE *effectInstances,
			DWORD materialNum,
			CONST_90C DWORD *pAdjacency,
			ID3DXSkinInfo *skinInfo,
			D3DXMESHCONTAINER **newMeshContainer)
	{
		*newMeshContainer = NULL;
		//�f�[�^�ۑ��p�̍쐬		
		MY_D3DXMESHCONTAINER *m = new MY_D3DXMESHCONTAINER();
	
		//Name���\�b�h�ɖ��O������----------------
		if(name != NULL)
		{
			m->Name = new char[strlen(name) + 1];
			strcpy(m->Name,name);
		}
		//------------------------------------------

		//���b�V���^�C�v�̃`�F�b�N------------------
		if(meshData->Type != D3DXMESHTYPE_MESH)
		{	
			this->DestroyMeshContainer(m);	
			return E_FAIL;	
		}

		int FVF = meshData->pMesh->GetFVF();
		if(FVF == 0){	
			this->DestroyMeshContainer(m);	
			return E_FAIL;	
		}
		//------------------------------------------

		//���b�V���f�[�^�̑��
		m->MeshData = *meshData;
		//�֐��I������meshData���j�������̂ŁA����ŏ����Ȃ��悤�ɂȂ�I
		meshData->pMesh->AddRef();

		//�A�j���[�V������̒��_�f�[�^��ۑ����郏�[�N�Ƃ���workMesh���쐬
		m->MeshData.pMesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM,m->MeshData.pMesh->GetFVF(),this->_devices, &m->workMesh);
	
		//�A�j���[�V�����f�[�^������ꍇ�̏���-----------------
		//�X�L�����b�V����ۑ�
		if(skinInfo != NULL)
		{
			m->pSkinInfo = skinInfo;
			//�����Ȃ��悤��
			skinInfo->AddRef();

			//�{�[���̐��̎擾
			//���_�v�Z�p���[�N�̍쐬
			int boneNum = skinInfo->GetNumBones();
			m->boneUpdateMatrix = new D3DXMATRIX[boneNum];
		}
		//-----------------------------------------------------

		//�}�e���A���̕ۑ�-------------------------------------------------------------------------
		//�����̓A�j���[�V�����Ȃ����b�V���̓ǂݍ��݂ƈꏏ
		m->materialNum = materialNum;
		m->materials = new D3DMATERIAL9[m->materialNum];
		m->textures = new IDirect3DTexture9*[m->materialNum];
		for(int i=0;i<m->materialNum;i++)
		{
			m->materials[i] = materials[i].MatD3D;
			m->textures[i] = NULL;
			if(materials[i].pTextureFilename != NULL)
				::D3DXCreateTextureFromFileA(this->_devices, materials[i].pTextureFilename,&m->textures[i]);
		}
		//-----------------------------------------------------------------------------------------

		//���̃R���e�i�֕ۑ�
		*newMeshContainer = m;
		return S_OK;
	}

	//--------------------------------------------------
	//�t���[���I�u�W�F�N�g������΁A���O�p��������j��
	//--------------------------------------------------
	__declspec(nothrow) HRESULT __stdcall 
	MY_HIERARCHY::DestroyFrame(D3DXFRAME *frame)
	{
		if(frame != NULL)
		{
			delete frame->Name;
			delete (MY_FRAME*)frame;
			frame = NULL;
		}
		return S_OK;
	}

	//----------------------------------------------------------------------
	//���b�V���R���e�i������΁A�������������������폜���Ă����B
	//----------------------------------------------------------------------
	__declspec(nothrow) HRESULT __stdcall 
	MY_HIERARCHY::DestroyMeshContainer(D3DXMESHCONTAINER *meshContainer)
	{
		if(meshContainer != NULL)
		{
			if(meshContainer->Name != NULL)	delete meshContainer->Name;
			delete (MY_D3DXMESHCONTAINER*)meshContainer;
			meshContainer = NULL;
		}
		return S_OK;
	}

}