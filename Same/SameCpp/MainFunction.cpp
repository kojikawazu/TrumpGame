#pragma once

//-------------------------------------------------------------
//
//DLL�̒��ŕێ��������f�[�^�Ȃǂ������Ɋi�[
//�V���O���g���ŊǗ����Ă����N���X
//
//-------------------------------------------------------------
#include <MainFunction.h>
#include <DirectFunctionPlus.h>
#include <DirectWindow.h>
#include <DirectCamera.h>


namespace NanairoLib
{
	//�V���O���g���Ȃ̂ŁA���̒��̃|�C���^���C���X�^���X��
	MainFunction* MainFunction::MainFunc = 0;

	//----------------------------------------
	//�R���X�g���N�^
	//----------------------------------------
	inline MainFunction::MainFunction()
	{
		DXData	= new NanairoLib::MYDXData();
		keys	= new NanairoLib::KEYS();
		custom	= new NanairoLib::Artisan();
	}
	
	//----------------------------------------
	//�f�X�g���N�^
	//----------------------------------------
	inline MainFunction::~MainFunction()
	{
		ES_SAFE_DELETE( DXData );
		ES_SAFE_DELETE( keys );
		ES_SAFE_DELETE( custom );
	}

	//----------------------------------------------------------------------------------------
	//���[���h���W����X�N���[�����W�ɕϊ�
	//----------------------------------------------------------------------------------------
	//@in : �ʒu�x�N�g��
	//@in : ��]�x�N�g��
	//@in : �g�k�x�N�g��
	//@out : �X�N���[�����W
	D3DXVECTOR3 MainFunction::ChangeToScreen_world(RCVector3 pos,RCVector3 ang,RCVector3 sc)
	{
		Direct3DFunc func;
		//�X�N���[�����W�֕ϊ�
		return func.ChanGetoScreen_world(DXData->GetDevice(), pos, &func.SetWorldPos(DXData->GetDevice(),
										pos, ang, sc, 1), &this->viewMatrix, &this->projMatrix, &this->portMatrix);
	}
	
	//------------------------------------------------------------
	//�X�N���[�����W���烏�[���h���W�ɕϊ�
	//------------------------------------------------------------
	//@in : �X�N���[�����W
	//@out : ���[���h���W
	D3DXVECTOR3 MainFunction::ChangeToWorld_screen(RCVector3 pos)
	{
		Direct3DFunc func;
		return func.ChanGetoWorld_screen(DXData->GetDevice(), pos, &this->viewMatrix, &this->projMatrix, &this->portMatrix);
	}
	
	//---------------------------------------------
	//DirectX�̏�����
	//---------------------------------------------
	//@in : �C���X�^���X�n���h��
	//@out : true(����) false(���s)
	bool MainFunction::InitDirectX(HINSTANCE hInst)
	{
		NanairoLib::WinCreate win;

		if( FAILED( win.CreateClassAndWin( hInst, this->DXData->GetWindowT() ) ) )
			return false;

		this->DXData->SetDevice( win.InitDirect3D( this->DXData->Get3D9(),
			this->DXData->GetDevice(), this->DXData->GetWindow() ) );
		this->custom->SetDevice( this->DXData->GetDevice() );
		this->custom->SetVertexBuffer();
		
		return true;
	}

	//----------------------------------------------
	//�f�t�H���g�ݒ���܂Ƃ߂�
	//----------------------------------------------
	void MainFunction::SetDefaultMatrix()
	{
		NanairoLib::Direct3DFunc func;
		this->projMatrix = func.SetDefaultProjParam( this->DXData->GetDevice() );
		this->custom->SetProjection( &this->projMatrix );
		this->portMatrix = func.SetViewPort( this->DXData->GetDevice());

		this->SetDefaultLight();
		this->SetDefaultCamera();
	}

	//----------------------------------------------
	//���C�g�̃f�t�H���g�ݒ�
	//----------------------------------------------
	void MainFunction::SetDefaultLight()
	{
		//�f�t�H���g���C�g�̐ݒ�
		NanairoLib::Light light = NanairoLib::Light( 0 );
		light.Setlighting( this->DXData->GetDevice() );

#ifdef SHADER_DRAWER		
		Shader* sh = this->custom->GetShader();
		if( sh != NULL )
		{
			sh->Effect->SetBool( SHADER_LIGHTING_ABLE_, true );
			sh->Effect->SetFloatArray( SHADER_LIGHT_DIR_, (float*)&light.GetLight()->Direction , 17 );
			sh->Effect->SetFloatArray( SHADER_LIGHT_DIR_DIFFUSE_, (float*)&light.GetLight()->Diffuse, 17 );
			sh->Effect->SetFloatArray( SHADER_LIGHT_DIR_AMBIENT_, (float*)&light.GetLight()->Ambient, 17 );
		}
#endif
	}

	//----------------------------------------------
	//�f�t�H���g�̃J�����ݒ�
	//----------------------------------------------
	void MainFunction::SetDefaultCamera()
	{
		//�ʏ�̃J�����̍X�V
		NanairoLib::CAMERA camera = NanairoLib::CAMERA(0);
		camera.CameraUpdate( this->DXData->GetDevice() );

#ifdef SHADER_DRAWER
		//�V�F�[�_�J�����̃Z�b�e�B���O
		Shader* sh = this->custom->GetShader();
		if( sh != NULL )
			sh->Effect->SetMatrix( SHADER_MATRIX_VIEW_, camera.GetViewMatrix() );
#endif
	}


}