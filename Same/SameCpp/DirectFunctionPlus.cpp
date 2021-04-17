#pragma once

//--------------------------------------------------------------------------
//
//�قڊ��蓖�Čn�̃��\�b�h
//DirectX�r���[�p�C�v���C���Ɋ��蓖�ĂĂ����܂�
//
//--------------------------------------------------------------------------
#include <DirectFunctionPlus.h>

namespace NanairoLib
{
	//-----------------------------------------------------------
	//�f�R��
	//-----------------------------------------------------------
	inline Direct3DFunc::Direct3DFunc(const Direct3DFunc& func){}
	inline Direct3DFunc::Direct3DFunc(){}
	inline Direct3DFunc::~Direct3DFunc(){}

	//---------------------------------------------------------------
	//�f�t�H���g�v���W�F�N�V�����s��ݒ�
	//---------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@out : �v���W�F�N�V�����s��
	D3DXMATRIX Direct3DFunc::SetDefaultProjParam(IDirect3DDevice9* Device)
	{	
		return this->SetProjectionParam( Device, GAKAKUS, NEERDIS, TALLDIS );
	}

	//--------------------------------------------------------
	//�r���[�|�[�g�s��擾
	//--------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@out : �r���[�|�[�g�s��
	D3DXMATRIX Direct3DFunc::SetViewPort(IDirect3DDevice9* Device)
	{
		D3DVIEWPORT9 vp;
		MyMatrix mat;
		Device->GetViewport(&vp);
		mat = mat.GetViewPort( vp.Width , vp.Height );
		return mat.ChangeMatrixD3D();
	}

	//----------------------------------------------------------------------------------------------------------------------
	//�v���W�F�N�V�����ݒ�
	//----------------------------------------------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : ��p
	//@in : �A�X�y�N�g��
	//@in : �O���N���b�s���O��
	//@in : ����N���b�s���O��
	//@out : �v���W�F�N�V�����s��
	D3DXMATRIX Direct3DFunc::SetProjectionParam(IDirect3DDevice9* Device,float dangle,float camera_frontDis,float camera_backDis)
	{
		//���s���Ԃ̐ݒ�
		D3DXMATRIX proj;
		::D3DXMatrixPerspectiveFovLH(&proj,	SET_PI( dangle ), SCRW / SCRH, camera_frontDis, camera_backDis );
		Device->SetTransform(D3DTS_PROJECTION, &proj);
		return proj;
	}

	//----------------------------------------------------------------
	//���C�g�ݒ�
	//----------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : ���C�g�N���X
	void Direct3DFunc::SetLightParam(IDirect3DDevice9 *Device,Light* light)
	{
		//���C�g�̐ݒ�
		//�O�Ԃ̓f�t�H���g
		light->Setlighting(Device);
	}

	//---------------------------------------------------------------------------------------------------------------------
	//�r���[�ݒ�
	//---------------------------------------------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : ���_�x�N�g��
	//@in : �����_�x�N�g��
	//@in : ������x�N�g��
	//@in : true(�r���[�ݒ肠��) false(�r���[�ݒ�Ȃ�)
	//@out : �r���[�s��
	D3DXMATRIX Direct3DFunc::SetCamera(IDirect3DDevice9* Device,RVector3 eye,RVector3 at,RVector3 up,bool isTransform)
	{
		D3DXMATRIX camera;
		::D3DXMatrixLookAtLH(&camera, &eye.SetD3DVector3(), &at.SetD3DVector3(), &up.SetD3DVector3() );
		if( !isTransform )	Device->SetTransform(D3DTS_VIEW, &camera);
		return camera;
	}

	//-----------------------------------------------------------------------------------------------------------------------------------
	//���[���h�ϊ�
	//-----------------------------------------------------------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �ʒu�x�N�g��
	//@in : ��]�x�N�g��
	//@in : �g�k�x�N�g��
	//@in : 0(�ϊ��t��) ����ȊO(�ϊ��Ȃ�)
	//@in : 0(��]�ϊ�����) ����ȊO(��]�ϊ��Ȃ�)
	//@out : ���[���h�s��
	D3DXMATRIX Direct3DFunc::SetWorldPos(IDirect3DDevice9* Device, RCVector3 pos, RCVector3 rota, RCVector3 scale,int mode,int anglemode)
	{
		D3DXMATRIX mat1,mat2,mat3,mat4,mat5,world;
	
		//�ʒu�s��
		::D3DXMatrixTranslation(&mat1,pos.x, pos.y, pos.z);

		//�p�x�s��
		if(anglemode == 0)
		{
			::D3DXMatrixRotationX(&mat2, SET_PI(rota.x));
			::D3DXMatrixRotationY(&mat3, rota.y);
			::D3DXMatrixRotationZ(&mat4, SET_PI(rota.z));
		}
	
		//�g��s��
		::D3DXMatrixScaling(&mat5,scale.x, scale.y, scale.z); 
	
		world = ( mat5 * mat2 * mat3 * mat4 * mat1 );
		if(mode == 0)	
			Device->SetTransform(D3DTS_WORLD,&world);
		return world;
	}

	//-----------------------------------------------------------------------------
	//���[���h�ϊ��i�ݒ�p�j
	//-----------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : ���[���h�s��
	//@out : ���[���h�s��
	D3DXMATRIX Direct3DFunc::SetWorldPos(IDirect3DDevice9* Device,PCMATRIX world)
	{
		Device->SetTransform(D3DTS_WORLD,world);
		return *world;
	}

	//-----------------------------------------------------------------------------------------------------------------
	//���[���h�N�H�[�^�j�I���ϊ�
	//-----------------------------------------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �ʒu�x�N�g��
	//@in : �C�ӎ��x�N�g��
	//@in : ��]�p�x
	//@in : �g�k�x�N�g��
	//@out : ���[���h�s��
	D3DXMATRIX Direct3DFunc::SetWorldQuat(IDirect3DDevice9* Device, RCVector3 pos,RCVector3 rotavec,float ang,RCVector3 scale)
	{
		VectorFunc vec3;
		D3DXMATRIX mat = vec3.SetworldQuaternion(pos, scale, rotavec, ang);
		Device->SetTransform(D3DTS_WORLD,&mat);
		return mat;
	}

	//-----------------------------------------------------------------------------------------------------------------
	//���[���h���W����X�N���[�����W�ɕϊ�
	//-----------------------------------------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : ���[�J�����W
	//@in : ���[���h�s��
	//@in : �r���[�s��
	//@in : �v���W�F�N�V�����s��
	//@in : �r���[�|�[�g�s��
	//@out : �X�N���[�����W
	D3DXVECTOR3 Direct3DFunc::ChanGetoScreen_world(IDirect3DDevice9* Device, RCVector3 pos, PCMATRIX wo, PCMATRIX vi, PCMATRIX pr, PCMATRIX vp)
	{
		D3DXVECTOR3 vec;
		D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(pos.x, pos.y, pos.z), &((*wo) * (*vi) * (*pr) * (*vp)));
		return vec;
	}

	//-----------------------------------------------------------------------------------------------------------------
	//�X�N���[�����W���烏�[���h���W�ɕϊ�
	//-----------------------------------------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �X�N���[�����W
	//@in : �r���[�s��
	//@in : �v���W�F�N�V�����s��
	//@in : �r���[�|�[�g�s��
	//@out : ���[���h���W
	D3DXVECTOR3 Direct3DFunc::ChanGetoWorld_screen(IDirect3DDevice9* Device, RCVector3 pos, PCMATRIX vi, PCMATRIX pr, PCMATRIX vp)
	{
		D3DXVECTOR3 vec;
		D3DXVec3TransformCoord(&vec, &((Vector3&)pos).SetD3DVector3(), &((*::D3DXMatrixInverse(NULL, NULL, vi)) * (*::D3DXMatrixInverse(NULL, NULL, pr)) * (*::D3DXMatrixInverse(NULL, NULL, vp))));
		return vec;
	}

}