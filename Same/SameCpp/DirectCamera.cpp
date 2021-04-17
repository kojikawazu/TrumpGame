#pragma once
//-----------------------------------------------
//�J�������ˁ`
//-----------------------------------------------
#include <DirectCamera.h>
#include <DirectFunctionPlus.h>

namespace NanairoLib
{
	//�r���[�̃��[�h
	//�r���[�͑S���łT��
	#define CAMERAVIEWSUM	5						

	//�r���[�l�f�t�H���g�ݒ�
	const float viewArtisan[5][6] = 
	{
		{0.0f, 0.0f, 0.0f, 1000.0f, 100.0f, 360.0f},
		{0.0f, 0.0f, 0.0f,  800.0f,   0.0f,   0.0f},
		{0.0f, 0.0f, 0.0f,  500.0f,   0.0f,   0.0f},
		{0.0f, 0.0f, 0.0f, 7000.0f,3000.0f, 360.0f},
		{0.0f, 0.0f, 0.0f,    0.1f,7000.0f, 360.0f},
	};

	//-------------------------------------------------------------------------------
	//�֐��|�C���^
	void CAMERA::Camera_keyCheck(PDirectDevice Device,PCKEYS keys)
	{
		(this->*key_action)(Device, keys);	
	}

	#pragma region �J�����̃R���X�g���N�^
	//@in : �J�����ԍ�
	inline CAMERA::CAMERA(int cameraNum) : 
				zoom(-500.0f) , cameraUp(100.0f) , cameraAngle(0.0f) , cameraNum(cameraNum) , cameraViewMode(0)
	{
		tarGet				= D3DXVECTOR3(0.0,    0.0f,   0.0f);
		up					= D3DXVECTOR3(0.0f,   1.0f,   0.0f);
		eye					= D3DXVECTOR3(0.0f, 100.0f, 500.0f);
		cameraMatrix		= D3DXMATRIX();

		this->DefaultChange();
		this->key_action = &CAMERA::Keyof_CameraChange;
	}

	//���ׂĂ̏�����
	inline void CAMERA::ZeroInit()
	{
		this->eye		= D3DXVECTOR3(0.0f,0.0f,0.0f);
		this->tarGet	= D3DXVECTOR3(0.0f,1.0f,0.0f);
		this->up		= D3DXVECTOR3(0.0f,0.0f,500.0f);
		cameramoveFlag = false;
		this->zoom = this->cameraUp = this->cameraAngle = 0.0f;
		cameranooupFlag = cameraViewMode = 0;

		zoom = -500.0f;
		cameraUp = 100.0f;

		this->key_action = &CAMERA::Keyof_CameraChange;
	}
	
	inline CAMERA::~CAMERA(){}
	#pragma endregion

	//--------------------------------------------------------------
	//�J�����̒��ڐݒ�
	//--------------------------------------------------------------
	//@in : ���_�x�N�g��
	//@in : �����_�x�N�g��
	//@in : ������x�N�g��
	void CAMERA::Seting_Camera(PCVECTOR3 e,PCVECTOR3 t,PCVECTOR3 u)
	{
		this->eye = (*e);	this->tarGet = (*t);	this->up = (*u);
	}
	
	#pragma region �t�B�[���h�̎擾(���邾�������ł��Ȃ�)
	//���_�̃Z�b�g
	PCVector3 CAMERA::GetEYE(){		return &eye;		}
		
	//�^�[�Q�b�g�̃Z�b�g
	PCVector3 CAMERA::GetTARGET(){		return &tarGet;	}

	//������̃Z�b�g
	PCVector3 CAMERA::GetUP(){			return &up;	}

	//�J�����s��̎擾
	PCMATRIX CAMERA::GetViewMatrix(){	return &this->cameraMatrix;	}

	//�J���������̎擾
	PCFLOAT		CAMERA::GetCameraUp(){			return &this->cameraUp;			}
	PCMATRIX	CAMERA::GetBillboardMatrix(){	return &this->billboardMatrix;	}
	#pragma endregion

	//--------------------------------------------------------
	//�����ŃJ�����̘M��
	//�^�[�Q�b�g����ǂꂾ��zoom(�����)���邩
	//�^�[�Q�b�g����ǂꂾ��cameraUp(�����낵��)���邩
	//�^�[�Q�b�g����ǂꂾ��cameraAngle(�p�x����)���邩
	//--------------------------------------------------------
	void CAMERA::DefaultChange()
	{
		this->eye.x = tarGet.x + (sin(this->cameraAngle) * this->zoom);
		this->eye.y = tarGet.y + this->cameraUp;
		this->eye.z = tarGet.z + (cos(this->cameraAngle) * this->zoom);
	}
	
	//--------------------------------------------------------------------------------
	//�v���C���ɕς��������̃Z�b�g�J����
	//--------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �����_
	//@in : �p�x
	//@in : ���[�h 1(���ʂ̊p�x) 2(���W�A���p) 3(���ʂ̊p�x���Z)
	void CAMERA::SetPlayerCamera(PDirectDevice Device,PCVECTOR3 t,float angle,CAMERA_ANGLEMODE mode)
	{
		//�r���[���[�h�R�ȏ�͖���
		if(this->cameraViewMode > 2)	return ;

		this->tarGet = (*t);

		switch(mode)
		{
			case CAMERAANGLE_NORMAL:	this->cameraAngle = (SET_PI(angle));	break;
			case CAMERAANGLE_DIRECTION:	this->cameraAngle = angle;				break;
			case CAMERAANGLE_PLUSANGLE:	this->cameraAngle += (SET_PI(angle));	break;
		}	

		this->DefaultChange();
	}
	
	//--------------------------------------------------------------------------
	//�ŏ���؂�ւ��ɕς��������̃Z�b�g�J����
	//--------------------------------------------------------------------------
	//@in : �����_
	//@in : �Y�[���l
	//@in : �p�x
	//@in : �A�b�v�l
	//@in : 1(�p�x�����) ����ȊO(���W�A���p)
	void CAMERA::Seting_CameraS(PCVECTOR3 e,float zo,float ang,float up, bool IsDirectAngle)
	{
		this->tarGet = (*e);

		this->zoom = zo;
		this->cameraUp = up;
		this->cameraAngle = ( IsDirectAngle ? SET_PI(ang) : ang );

		this->DefaultChange();
	}
	
	//-----------------------------------------------------------
	//�v���C���[�̐��ʎ��_�ɐ؂�ւ�
	//-----------------------------------------------------------
	//@in : ���ʂ̊p�x
	void CAMERA::ChangePlayerCameraFrontLine(float flontang)
	{
		if(this->cameraViewMode > 2)	return ;
		this->frontAng = flontang;	//�����������p�x�������Ă���
		this->cameraFrontMode = 1;	//���ʂނ����郂�[�h�����I

		this->key_action = &CAMERA::ChangeFrontLine;
	}
	
	//--------------------------------------------------------------
	//�v���C���[�̐��ʐ؂�ւ�
	//--------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �L�[�N���X
	void CAMERA::ChangeFrontLine(PDirectDevice Device,PCKEYS keys)
	{
		VectorFunc vec3D;

		//���ʂ̃x�N�g��
		Vector2 vecA = Vector2(1.0f * sin(this->frontAng), 1.0f * cos(this->frontAng));

		//�����_���王�_�ւ̃x�N�g��
		Vector2 vecB = vec3D.GetNormal(vec3D.GetVecDistance(vec3D.GetVectorXZ(this->eye), vec3D.GetVectorXZ(this->tarGet)));

		//B �~ A
		float ang = vec3D.GetCloss(vecB, vecA);
		
		//�p�x�o��
		ang = vec3D.ChangeAngle(ang, 2);

		//(��)�����Ă���(��)��
		if(ang > 0.1f)			this->cameraAngle -= SET_PI(10.0f);
		//(��)�����Ă���(��)��
		else if(ang < -0.1f)	this->cameraAngle += SET_PI(10.0f);
		//���ʂ�������I���t���O
		else
		{
			this->cameraFrontMode = 0;
			this->key_action = &CAMERA::Keyof_CameraChange;
		}
	}

	//----------------------------------------------------------------
	//�J�����`�F���W�A�N�V����
	//----------------------------------------------------------------
	//@in : �f�o�C�X
	//@in : �L�[
	void CAMERA::Keyof_CameraChange(PDirectDevice Device, PCKEYS keys)
	{
		bool hantei = false;
		//�J�����L�[���삠�肾������
		//�Q�ȉ��͂���I
		
		//����������
		if(keys->GetKey()->push[KQ] || keys->GetXPad(this->cameraNum - 1)->ranalogX < -10000)
		{
			hantei = true;
			this->cameraAngle += SET_PI(0.5f);
		}
		//�E��������
		else if(keys->GetKey()->push[KA] || keys->GetXPad(this->cameraNum - 1)->ranalogX > 10000)
		{
			hantei = true;
			this->cameraAngle -= SET_PI(0.5f);
		}

		//�����낵����
		if(keys->GetKey()->push[KW] || keys->GetXPad(this->cameraNum - 1)->ranalogY > 10000)
		{
			hantei = true;
			this->cameraUp += 3.0f;
		}
		//���グ����
		else if(keys->GetKey()->push[KS] || keys->GetXPad(this->cameraNum - 1)->ranalogY < -10000)
		{
			//���グ�Ăn�j�Ȃ�
			if(this->cameranooupFlag == 0)
			{
				hantei = true;
				this->cameraUp -= 3.0f;
			}
			//���߂Ȃ�ł��Ȃ�
			else	this->cameranooupFlag = 0;
		}
	
		//�Y�[���C��������
		if(keys->GetKey()->push[KE])
		{
			hantei = true;
			this->zoom += 3.0f;
		}
		//�Y�[���A�E�g������
		else if(keys->GetKey()->push[KD])
		{
			hantei = true;
			this->zoom -= 3.0f;
		}

		//�J�����̃r���[�؂�ւ�����
		if( (keys->GetKey()->trg[KP] ||
			(keys->GetXPad(this->cameraNum - 1)->trg[PADBACK])) )
		{
			this->ChangeCameraVIEWMODE(Device, this->cameraViewMode + 1);
			hantei = true;
		}

		//��������������J�����̃Z�b�g�`�F���W
		if(this->cameramoveFlag = hantei)
			this->DefaultChange();
	
	}
	
	//-----------------------------------------------------
	//�J�����̍X�V
	//-----------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	D3DXMATRIX CAMERA::CameraUpdate(PDirectDevice Device)
	{
		Direct3DFunc func;
		this->cameraMatrix = func.SetCamera(Device, eye, tarGet, up);

		//�r���{�[�h�v�Z--------------------------------------------------
		D3DXMATRIX mat;  
		D3DXMatrixLookAtLH(&mat, &tarGet.SetD3DVector3(), &tarGet.SetD3DVector3(), &tarGet.SetD3DVector3() );
		D3DXMatrixInverse( &this->billboardMatrix, NULL, &mat );
		//----------------------------------------------------------------

		return this->cameraMatrix;
	}
	
	//--------------------------------------------------------------
	//�r���[�؂�ւ�
	//--------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : ���[�h
	void CAMERA::ChangeCameraVIEWMODE(PDirectDevice Device,int cameraviewMode){
		this->cameraViewMode = cameraviewMode;
		switch(cameraviewMode + 1)
		{
			case CAMERA_VIEWBACK:	//���ɖ߂�
			case CAMERA_VIEW:	//�t�B�[���h���f��
			case CAMERA_VIEWUP:	//�^�ォ�璭�߂�
				this->tarGet = D3DXVECTOR3(viewArtisan[cameraviewMode][0],viewArtisan[cameraviewMode][1], viewArtisan[cameraviewMode][2]);
				zoom = viewArtisan[cameraviewMode][3];
				cameraUp = viewArtisan[cameraviewMode][4];
				cameraAngle = SET_PI(viewArtisan[cameraviewMode][5]);
				break;
			case CAMERA_VIEWZOOMS:	//���Y�[��
			case CAMERA_VIEWZOOML:	//�߂�����Y�[��
				zoom = viewArtisan[cameraviewMode][3];
				break;
		}

		this->DefaultChange();
		this->key_action = (cameraviewMode >= CAMERA_VIEWZOOML ? &CAMERA::CameraVIEWMODE : &CAMERA::Keyof_CameraChange);
	}

	//-------------------------------------------------------------
	//�r���[�ŃA�N�V�����������������Ɏ��s
	//-------------------------------------------------------------
	void CAMERA::CameraVIEWMODE(PDirectDevice Device,PCKEYS keys)
	{
		switch(this->cameraViewMode+1)
		{
			case CAMERA_VIEW:	//�t�B�[���h���� ���邭��񂵂�����
				cameraAngle += SET_PI(1.0f);
				this->cameramoveFlag = true;
				break;
		}
		
		this->DefaultChange();

		//�J�����̃r���[�ύX����������
		if( (keys->GetKey()->trg[KP] ||
			(keys->GetXPad(this->cameraNum - 1)->trg[PADBACK])) )
			this->ChangeCameraVIEWMODE(Device, (this->cameraViewMode + 1) % CAMERAVIEWSUM);
	}
	
	//------------------------------------------------
	//�^�[�Q�b�g���ƃX�N���[��
	//------------------------------------------------
	void CAMERA::tarGetScroll(float speed, int mode)
	{
		switch(mode + 1){
			//x���₷
			case CAMERA_TARGETX:	this->tarGet.x += speed;	break;
			//y���₷
			case CAMERA_TARGETY:	this->tarGet.y += speed;	break;
			//z���₷
			case CAMERA_TARGETZ:	this->tarGet.z += speed;	break;
		}
	}
}