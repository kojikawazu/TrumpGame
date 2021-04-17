#pragma once
//-------------------------------------------------------------------------
//
//�������f���̃A�j���[�V����������
//
//-------------------------------------------------------------------------
#include <AnimationMesh.h>
#pragma comment(lib,"winmm.lib")

namespace NanairoLib
{
	//-----------------------------
	//�R���e�i�Ǘ�
	//-----------------------------
	MY_HIERARCHY MY_MESH::hierarchy;

	
	#pragma region �R���X�g���N�^
	MY_D3DXMESHCONTAINER::MY_D3DXMESHCONTAINER()
	{
		::memset(this,0,sizeof(*this));
	}
	
	MY_D3DXMESHCONTAINER::~MY_D3DXMESHCONTAINER()
	{
		ES_SAFE_DELETE_ARRAY(materials);

		if(textures)
		{
			for(int i=0;i<materialNum;i++){	if(textures[i] != NULL)	textures[i]->Release();	}
			delete[] textures;
			textures = NULL;
		}

		ES_SAFE_RELEASE(pSkinInfo);
		ES_SAFE_RELEASE(MeshData.pMesh);
		ES_SAFE_RELEASE(workMesh);
		ES_SAFE_DELETE_ARRAY(boneUpdateMatrix);
	}
	#pragma endregion

	#pragma region ���b�V���R���X�g���N�^
	MY_MESH::MY_MESH()
	{
		memset(this,0,sizeof(*this));
	}

	///device	: �f�o�C�X
	///fileName	: �t�@�C����
	MY_MESH::MY_MESH(IDirect3DDevice9 *device,LPCSTR fileName)
	{
		memset(this,0,sizeof(*this));
		D3DXLoadMeshHierarchyFromX(fileName,D3DXMESH_SYSTEMMEM,device,&hierarchy,NULL,&root,&this->animController);
	}

	MY_MESH::~MY_MESH()
	{
		ES_SAFE_RELEASE(this->animController);
		if(this->root != NULL){				::D3DXFrameDestroy(root,&hierarchy); this->root = NULL; }
	}
	#pragma endregion
	
	//----------------------------------------------------
	//�A�j���[�V�����̃o�b�N�A�b�v
	//----------------------------------------------------
	//@in : �t���[�����
	void MY_MESH::_backupAnimationMatrix(D3DXFRAME *frame)
	{
		//�o�b�N�A�b�v
		((MY_FRAME*)frame)->originalMatrix = frame->TransformationMatrix;
	
		//�c���[�T��
		if(frame->pFrameSibling != NULL)	this->_backupAnimationMatrix(frame->pFrameSibling);
		if(frame->pFrameFirstChild != NULL)	this->_backupAnimationMatrix(frame->pFrameFirstChild);
	}
	
	//----------------------------------------------------
	//�A�j���[�V�����̃��Z�b�g
	//----------------------------------------------------
	//@in : �t���[�����
	void MY_MESH::_reSetAnimationMatrix(D3DXFRAME *frame)
	{
		//�o�b�N�A�b�v
		frame->TransformationMatrix = ((MY_FRAME*)frame)->originalMatrix;
	
		//�c���[�T��
		if(frame->pFrameSibling != NULL)	this->_reSetAnimationMatrix(frame->pFrameSibling);
		if(frame->pFrameFirstChild != NULL)	this->_reSetAnimationMatrix(frame->pFrameFirstChild);
	}
	
	//----------------------------------------------------------------------------------------
	//�A�j���[�V�����X�V
	///�t���[�����̃A�j���[�V�����s����A��A���Ȃ���v�Z�B
	///�������g��TransformationMatrix��SetTime�ɂ��A�j���[�V�������ꂽ�s�񂪓����Ă���̂ŁA
	///�e�̍s����}�[�W���čŏI�I�ȍs����i�[���Ă����B�t���[���͊K�w�\����
	///sibling�ɂ͎����ɓK�p�����s����A
	///chile�ɂ͎����̍s����}�[�W�����s���n���čċA����B
	//-----------------------------------------------------------------------------------------
	//@in : �t���[�����
	//@out : �ϊ��s��
	void MY_MESH::_updateAnimationMatrix(D3DXFRAME *frame,D3DXMATRIX *mat)
	{
		//�t���[�����̃A�j���[�V�����s��쐬
		if(mat != NULL)	::D3DXMatrixMultiply(&frame->TransformationMatrix,&frame->TransformationMatrix,mat);

		//�c���[�T��
		if(frame->pFrameSibling != NULL)	this->_updateAnimationMatrix(frame->pFrameSibling,mat);
		if(frame->pFrameFirstChild != NULL)	this->_updateAnimationMatrix(frame->pFrameFirstChild,&frame->TransformationMatrix);
	}
	
	//---------------------------------------------------------------------
	//���b�V���̃h���[
	//---------------------------------------------------------------------
	//@in : ���[�V�����ԍ�
	//@in : ���݂̃��[�V�����t���[������
	//@in : �ϊ��s��
	//@in : �F�������[�h
	void MY_MESH::draw(int Set,unsigned int passTime,D3DXMATRIX *m, int mode)
	{
		//�A�j���[�V�����o�ߎ��Ԃ̐ݒ�
		if(this->animController != NULL)
		{
			ID3DXAnimationSet *animSet = NULL;
			animController->GetAnimationSet(Set,&animSet);
			animController->SetTrackAnimationSet(0,animSet);

			//�ŏ��̃A�j���[�V�����ɃZ�b�g
			//this->_reSetAnimationMatrix(root);

	#if(D3D_SDK_VERSION >= 32)
			//���݂̎��Ԃ���̌o�ߎ��Ԃ��w��
			//(SetTrackPosition - ResetTime)�̐�Ύ���
			animController->SetTrackPosition(0,0);
			animController->ResetTime();
			animController->AdvanceTime(passTime / 1000.0,NULL);
	#else
			//���ڎ��Ԃ�ݒ�
			animController->SetTime(passTime / 1000.0)
			if(animSet != NULL)	animSet->Release();
	#endif
			//�A�j���[�V�����}�g���b�N�X�̍쐬
			this->_updateAnimationMatrix(root,NULL);
		}
		//�`��
		this->_callDrawMesh(root,m, mode);
	}
	
	//---------------------------------------------------------------------
	//�`��̌Ăяo��
	//---------------------------------------------------------------------
	//@in : �t���[�����
	//@in : �ϊ��s��
	//@in : �F�������[�h
	void MY_MESH::_callDrawMesh(D3DXFRAME *frame,D3DXMATRIX *m, int mode)
	{
		//�t���[�����̕`��i�����Ă��郁�b�V����S�������o���j
		MY_D3DXMESHCONTAINER *meshContainer = (MY_D3DXMESHCONTAINER*)frame->pMeshContainer;
	
		//���X�g���I�[����Ȃ����
		while(meshContainer != NULL)
		{
			//���{�[�����{�[������Ă�
			_drawMeshContainer(meshContainer,frame,m, mode);
			meshContainer = (MY_D3DXMESHCONTAINER*)meshContainer->pNextMeshContainer;
		}

		//�c���[�T��
		if(frame->pFrameSibling != NULL)	this->_callDrawMesh(frame->pFrameSibling,m, mode);
		if(frame->pFrameFirstChild != NULL)	this->_callDrawMesh(frame->pFrameFirstChild,m, mode);
	}
	
	//-----------------------------------------------------------------------------
	//�R���e�i�ɓ����Ă���f�[�^���h���[
	//-----------------------------------------------------------------------------
	//@in : �R���e�i�ɓ����Ă�����
	//@in : �t���[�����
	//@in : �ϊ��s��
	//@in : �F�������[�h
	void MY_MESH::_drawMeshContainer(MY_D3DXMESHCONTAINER *meshContainer,D3DXFRAME *frame,D3DXMATRIX *m, int mode)
	{
		//�o�b�N�A�b�v�̎擾
		MY_D3DXMESHCONTAINER *mc = (MY_D3DXMESHCONTAINER*)meshContainer;

		//���_�o�b�t�@�Ƀ{�[���ό`��K�p
		if(meshContainer->pSkinInfo != NULL){
			//�{�[�����v�̎擾
			int boneNum = mc->pSkinInfo->GetNumBones();

			//�{�[���ό`�}�g���N�X���Z�o
			for(int i=0;i<boneNum;i++)
			{
				D3DXFRAME *f = ::D3DXFrameFind(root,mc->pSkinInfo->GetBoneName(i));
				if(f != NULL)
				{
					::D3DXMatrixMultiply(&mc->boneUpdateMatrix[i],
									mc->pSkinInfo->GetBoneOffsetMatrix(i),
									&f->TransformationMatrix);
				}
			}

			//���_�o�b�t�@�̃|�C���^���擾����
			void* org;
			//�I���W�i�����_�f�[�^�i�ϊ����j
			mc->MeshData.pMesh->LockVertexBuffer(D3DLOCK_READONLY,(void**)&org);
			//�ό`���_�f�[�^�i�o�͐�j
			void** work;
			mc->workMesh->LockVertexBuffer(0,(void**)&work);

			//�X�L�����b�V���̍X�V
			HRESULT hr = mc->pSkinInfo->UpdateSkinnedMesh(meshContainer->boneUpdateMatrix,NULL,org,work);

			mc->MeshData.pMesh->UnlockVertexBuffer();
			mc->workMesh->UnlockVertexBuffer();

			//�X�L�����b�V���ɍX�V�����Ƃ����
			//�������炪�`��---------------------------------------------------------------------------------------------
			
			Shader* sh = this->hierarchy.GetShader();
#ifdef SHADER_DRAWER
			if( sh == NULL )
				this->hierarchy.GetDevice()->SetTransform(D3DTS_WORLD,m);
			else
				sh->Effect->SetMatrix( SHADER_MATRIX_WORLD_, m );
#else
			this->hierarchy.GetDevice()->SetTransform(D3DTS_WORLD,m);
#endif
			for(int i=0;i<mc->materialNum;i++)
			{
				if( sh == NULL )
				{
					//�}�e���A�����Z�b�g
					this->hierarchy.GetDevice()->SetTexture(0,mc->textures[i]);
					this->hierarchy.GetDevice()->SetMaterial(&mc->materials[i]);
				}
				else{
#ifdef SHADER_DRAWER
					sh->Effect->SetFloatArray( SHADER_MATERIAL_, (float*)(&mc->materials[i]), 17 );
					sh->Effect->SetTexture( SHADER_TEX1_, mc->textures[i] );
					sh->Effect->SetBool( SHADER_TEX_ABLE_, (mc->textures[i] != NULL) );
					sh->Effect->CommitChanges();
#else
					this->hierarchy.GetDevice()->SetMaterial( &mc->materials[i] );
					if( mc->textures[i] != NULL ) 
						this->hierarchy.GetDevice()->SetTexture( 0, mc->textures[i] );
#endif
				}
				//�`��ǁ[��I
				mc->workMesh->DrawSubset(i);
			}
		}
	}
	
}