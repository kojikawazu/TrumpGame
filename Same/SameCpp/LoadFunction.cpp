#pragma once

//------------------------------------------------------------------------------
//
//�e�N�X�`���⃂�f���̃��[�h�֐��������Ɋi�[
//
//------------------------------------------------------------------------------
#include <ResourceFunction.h>
#include <tchar.h>

namespace NanairoLib
{
	inline TextFunc::TextFunc(){}

	inline TextFunc::~TextFunc(){}

	//-----------------------------------
	//���_����@����
	//-----------------------------------
	//@in : ���f���ڍ׃f�[�^�N���X
	void GetNomalLine(PATACKH atack)
	{
		VectorFunc vec3D;
		Vector3 vecA,vecB,normal;

		for(DWORD i=0; i<atack->meshSum; i++)
		{
			vecA.SetVector( atack->meshVertex[atack->meshIndex[(int)i][1]] - atack->meshVertex[atack->meshIndex[(int)i][0]] );
			vecB.SetVector( atack->meshVertex[atack->meshIndex[(int)i][2]] - atack->meshVertex[atack->meshIndex[(int)i][0]] );
			normal = vec3D.GetNormal(vec3D.GetCloss(vecA, vecB));

			atack->meshNormal[(int)i] = normal.SetD3DVector3();
		}
	}
	
	//***************************************************************************************************************************
	//�e�N�X�`���N���X�̊֐��Q

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
	int TextFunc::LoadGraphIndex(PDirectDevice Device,PTEXTUREH text,LPCSTR fileName,int width,int height,int sumW,int sumH)
	{
		if(FAILED(::D3DXCreateTextureFromFileA(Device,fileName,&text->graph)))	
			return -1;
		//���������Ă�
		//�摜�̓ǂݍ��ނɐ�������Ƃ������
		//�e�N�X�`���\���̂Ƀf�[�^��ۑ�
		//�����āA�g�p���ɐ؂�ւ�
		text->used = true;	
		text->width = width;
		text->height = height;
		return 1;
	}
	
	//--------------------------------------------
	//�摜��񓯊��ǂݍ��݂���
	//--------------------------------------------
	//@in : DirectX�̃f�o�C�X
	//@inout : �e�N�X�`���̍\����
	//@in : �ǂݍ��ފJ�n�ʒu
	//@in : �ǂݍ��ރT�C�Y
	//@out : ���s(-1) ����(1)
	int TextFunc::LoadGraphIndexASYN(PDirectDevice Device,PTEXTUREH text,LPCSTR point,int size)
	{
		if(FAILED(::D3DXCreateTextureFromFileInMemory(Device,point,size,&text->graph)))
		{
			text->used = false;
			return -1;
		}
		return 1;
	}

	//--------------------------------------------
	//���f���̃��[�h
	//--------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �t�@�C����
	//@out : ���f���ۑ��N���X
	//@in : �ۑ��ԍ�
	//@out : true(����) false(���s)
	bool TextFunc::LoadModel3D(PDirectDevice Device,LPCSTR fileName,PMODELH model,int mode)
	{
		ID3DXBuffer *pMatel;
		//X�t�@�C�����烂�f���f�[�^���[�h
		//�}�e���A�����A���b�V���Q�b�c�I
		if(FAILED(
			::D3DXLoadMeshFromXA(
				fileName,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,(DWORD*)&model->matelSum,&model->mesh)))
				return false;

		int num = model->matelSum;
		//�f�[�^�󂯎��o�b�t�@�쐬
		model->matel = new D3DMATERIAL9[num];
		model->textureX = new IDirect3DTexture9*[num];
	
		//�}�e���A���̃R�s�[
		D3DXMATERIAL* org = (D3DXMATERIAL*)pMatel->GetBufferPointer();
		for(int i=0;i<num;i++)
		{
			model->matel[i] = org[i].MatD3D;
			if(mode == 0)	model->matel[i].Ambient = model->matel[i].Diffuse;
			//�A���r�G���g�ƃf�t���[�Y�͈ꏏ
			model->textureX[i] = NULL;
			if(org[i].pTextureFilename != NULL)
				::D3DXCreateTextureFromFileA(Device,org[i].pTextureFilename,&model->textureX[i]);
		}

		pMatel->Release();
		model->used = true;
		return true;
	}
	
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
	int TextFunc::LoadModel3DASYN(PDirectDevice Device,LPCSTR point,int size,PMODELH model,HWND wnd,int mode)
	{
		ID3DXBuffer *pMatel;
		//���������烂�f�������[�h
		//�}�e���A�����A���b�V�������o��
		if(FAILED(
			::D3DXLoadMeshFromXInMemory(
				point,size,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,(DWORD*)&model->matelSum,&model->mesh)))
		{
				::MessageBoxA(wnd,_T("�t�@�C���ǂݍ��ݎ��s"),_T("error"),MB_OK);
				return -1;
		}

		int num = model->matelSum;
		//�f�[�^�󂯎��o�b�t�@�쐬
		model->matel = new D3DMATERIAL9[num];
		model->textureX = new IDirect3DTexture9*[num];
	
		//�}�e���A���̃R�s�[
		D3DXMATERIAL* org = (D3DXMATERIAL*)pMatel->GetBufferPointer();
		for(int i=0;i<num;i++)
		{
			model->matel[i] = org[i].MatD3D;
			if(mode == 0)	model->matel[i].Ambient = model->matel[i].Diffuse;
			//�A���r�G���g�ƃf�t���[�Y�͈ꏏ
			model->textureX[i] = NULL;
			if(org[i].pTextureFilename != NULL)
				::D3DXCreateTextureFromFileA(Device,org[i].pTextureFilename,&model->textureX[i]);
		}

		pMatel->Release();
		model->used = true;
		return 1;
	}

	//--------------------------------------------
	//�����蔻��p���f���̃��[�h
	//--------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �t�@�C���p�X
	//@input : �����蔻��p���f���f�[�^�N���X
	//@out : true(����) false(���s)
	bool TextFunc::LoadModelAtack(PDirectDevice Device,LPCSTR fileName,PATACKH atack)
	{
		ID3DXBuffer *pMatel;
		ID3DXMesh *mesh;
		if(FAILED(
			::D3DXLoadMeshFromXA(
				fileName,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,NULL,&mesh)))
		{		
			return false;
		}
		pMatel->Release();

		//���_�o�b�t�@�̎擾
		BYTE* pVertex;
		BYTE* pIndex;
		//���b�N�������Ď擾
		if(FAILED(mesh->LockVertexBuffer(D3DLOCK_READONLY,(void**) &pVertex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD,(void**) &pVertex)))		
				return false;
		}
		if(FAILED(mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**) &pIndex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD, (void**) &pIndex)))
			{
				mesh->UnlockVertexBuffer();
				return false;
			}
		}

		atack->vertexSum	= mesh->GetNumVertices();			//���_�̐�
		atack->meshSum		= mesh->GetNumFaces();				//�ʂ̐�	
		DWORD FVF			= mesh->GetFVF();					//���_�t�H�[�}�b�g���擾����B
		DWORD vertexSize	= D3DXGetFVFVertexSize( FVF );		// ���_�̃T�C�Y���擾����B
		for( DWORD i = 0; i < atack->vertexSum; i++ )
		{
			atack->meshVertex[(int)i] = *(D3DXVECTOR3*)pVertex;	// ���_���W���擾����B
			pVertex += vertexSize;									// ���̒��_�Ƀ|�C���^���ړ�����B
		}

		for( DWORD i = 0; i < atack->meshSum; i++ )
		{
			//int�^ : size 2 ���i�ނ��낤
			atack->meshIndex[(int)i][0] = *(pIndex);	// ���_���W���擾����B
			atack->meshIndex[(int)i][1] = *(pIndex + 2);
			atack->meshIndex[(int)i][2] = *(pIndex + 4);
			pIndex += 6;									// ���̒��_�Ƀ|�C���^���ړ�����B
		}
	
		//�A�����b�N
		mesh->UnlockVertexBuffer();
		mesh->UnlockIndexBuffer();

		NanairoLib::GetNomalLine(atack);
		mesh->Release();
		atack->used = true;
		return true;
	}

	//--------------------------------------------
	//�񓯊��p�����蔻��̃��[�h
	//--------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �t�@�C���p�X
	//@in : �T�C�Y
	//@out : �����蔻��p�f�[�^�N���X
	//@in : �E�B���h�E�N���X
	//@out : 1(����) -1(���s)
	int TextFunc::LoadModelAtackASYN(PDirectDevice Device,LPCSTR point,int size,PATACKH atack,HWND wnd)
	{
		ID3DXBuffer *pMatel;
		ID3DXMesh *mesh;
		if(FAILED(
			::D3DXLoadMeshFromXInMemory(
				point,size,D3DXMESH_MANAGED,
				Device,NULL,&pMatel,
				NULL,(DWORD*)NULL,&mesh)))
		{
				::MessageBoxA(wnd,_T("�t�@�C���ǂݍ��ݎ��s"),_T("error"),MB_OK);
				return E_FAIL;
		}
		pMatel->Release();

		//���_�o�b�t�@�̎擾
		BYTE* pVertex;
		BYTE* pIndex;
		//���b�N�������Ď擾
		if(FAILED(mesh->LockVertexBuffer(D3DLOCK_READONLY,(void**) &pVertex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD,(void**) &pVertex)))
			{
				::MessageBoxA(wnd,_T("���b�V���ǂݍ��ݎ��s"),_T("error"),MB_OK);
				return -1;
			}
		}
		if(FAILED(mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**) &pIndex)))
		{
			if(FAILED(mesh->LockVertexBuffer(D3DLOCK_DISCARD, (void**) &pIndex)))
			{
				mesh->UnlockVertexBuffer();
				::MessageBoxA(wnd,_T("���b�V���ǂݍ��ݎ��s"),_T("error"),MB_OK);
				return -1;
			}
		}

		atack->vertexSum	= mesh->GetNumVertices();			//���_�̐�
		atack->meshSum		= mesh->GetNumFaces();				//�ʂ̐�	
		DWORD FVF				= mesh->GetFVF();					//���_�t�H�[�}�b�g���擾����B
		DWORD vertexSize		= D3DXGetFVFVertexSize( FVF );		// ���_�̃T�C�Y���擾����B
		for( DWORD i = 0; i < atack->vertexSum; i++ )
		{
			atack->meshVertex[(int)i] = *(D3DXVECTOR3*)pVertex;	// ���_���W���擾����B
			pVertex += vertexSize;									// ���̒��_�Ƀ|�C���^���ړ�����B
		}

		for( DWORD i = 0; i < atack->meshSum; i++ )
		{
			//int�^ : size 2 ���i�ނ��낤
			atack->meshIndex[(int)i][0] = *(pIndex);	// ���_���W���擾����B
			atack->meshIndex[(int)i][1] = *(pIndex + 2);
			atack->meshIndex[(int)i][2] = *(pIndex + 4);
			pIndex += 6;									// ���̒��_�Ƀ|�C���^���ړ�����B
		}
	
		//�A�����b�N
		mesh->UnlockVertexBuffer();
		mesh->UnlockIndexBuffer();

		NanairoLib::GetNomalLine(atack);
		mesh->Release();
		atack->used = true;
		return 1;
	}

	//-----------------------------------------------------------
	//�e�N�X�`�����畝�ƍ������擾
	//-----------------------------------------------------------
	//@in : �e�N�X�`���C���^�[�t�F�C�X
	//@out : ��
	//@out : ����
	void SetTextureLong(IDirect3DTexture9* gh, int* wh, int* ht)
	{
		if(wh == NULL || ht == NULL)	return ;

		::IDirect3DSurface9* suf;
		D3DSURFACE_DESC desc;
		gh->GetSurfaceLevel( 0, &suf );
		suf->GetDesc( &desc );
		(*wh) = (int)desc.Width;
		(*ht) = (int)desc.Height;
		suf->Release();
	}
}