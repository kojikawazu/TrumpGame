#ifndef NanairoLib_CAMERA_H
#define NanairoLib_CAMERA_H

//------------------------------------------------------
//
//�J��������舵���N���X
//
//------------------------------------------------------
#ifndef NanairoLib_FUNC_H
#include <DirectFunction.h>
#endif

#ifndef NanairoLib_KEYS_H
#include <Directkey.h>
#endif

namespace NanairoLib
{
	enum CAMERA_ANGLEMODE
	{
		CAMERAANGLE_NONE, CAMERAANGLE_NORMAL, CAMERAANGLE_DIRECTION, CAMERAANGLE_PLUSANGLE
	};

	enum CAMERA_TARGET_SCROLL
	{
		CAMERA_TARGETNONE, CAMERA_TARGETX, CAMERA_TARGETY, CAMERA_TARGETZ
	};

	enum CAMERA_VIEWMODE
	{
		CAMERA_VIEWNONE, CAMERA_VIEWBACK, CAMERA_VIEWZOOMS, CAMERA_VIEWZOOML, CAMERA_VIEW, CAMERA_VIEWUP
	};

	//-------------
	//�O���錾
	//-------------
	class KEYS;
	class Vector3;

	//-----------------------
	//��{�J�����N���X
	//-----------------------
	class SuperCamera
	{
		protected:
			float zoom, cameraAngle, cameraUp, flontAng;
			Vector3 eye, tarGet, up;
			MATRIX cameraMatrix, billboardMatrix;

		public:
			//�f�t�H���g�J�����ϊ�
			//__IMPOETER void			defaultChange();

			//�J�����̍X�V
			//__IMPOETER D3DXMATRIX	cameraUpdate(PDirectDevice Device);
	};

	//--------------------------------------------
	//DirectX�J�����N���X
	//--------------------------------------------
	class CAMERA
	{
		private:
		//-------------------------------------------------
			bool  cameramoveFlag;
			short cameraFrontMode, cameraNum, cameraViewMode;			//�J�������ʃ��[�h, �J�����ԍ��A�J�����r���[���[�h
			short cameranooupFlag;						//�J�������������t���O,�J�������グ�t���O
			float zoom, cameraAngle, cameraUp, frontAng;				//�Y�[�����A�J�����p�x�A�J�����A�b�v�A�����_�p�x
			Vector3 eye, tarGet, up;									//���_,�����_,�����
			MATRIX cameraMatrix,billboardMatrix;						//�r���[�s��A�r���{�[�h�s��
			
		public:	//�悭�g�����\�b�h
			//-----------------------------------------------------------------------
			//�L�[�`�F�b�N
			//-----------------------------------------------------------------------
			__IMPOETER void			Camera_keyCheck(PDirectDevice Device,PCKEYS keys);

			//--------------------------------------
			//�f�t�H���g�J�����ϊ�
			//--------------------------------------
			__IMPOETER void			DefaultChange();

			//-----------------------------------------------------
			//�J�����̍X�V
			//-----------------------------------------------------
			//@in : DirectX�p�f�o�C�X
			__IMPOETER D3DXMATRIX	CameraUpdate(PDirectDevice Device);

			//------------------------------------------------
			//�޺݌n
			//------------------------------------------------
			__IMPOETER			CAMERA(){}
			__IMPOETER			CAMERA(int cameraNum);
			__IMPOETER			~CAMERA();
			__IMPOETER void 		ZeroInit();
		
			//------------------------------------------------
			//�擾�n(�ǂݎ���p)
			//------------------------------------------------
			__IMPOETER PCVector3	GetEYE();
			__IMPOETER PCVector3	GetTARGET();
			__IMPOETER PCVector3	GetUP();
			__IMPOETER PCMATRIX		GetViewMatrix();
			__IMPOETER PCFLOAT		GetCameraUp();
			__IMPOETER PCMATRIX		GetBillboardMatrix();

			//-----------------------------------------------------------
			//�v���C���[�̐��ʎ��_�ɐ؂�ւ�
			//-----------------------------------------------------------
			//@in : ���ʂ̊p�x
			__IMPOETER void ChangePlayerCameraFrontLine(float flontang);
		
			//--------------------------------------------------------------
			//�J�����̒��ڐݒ�
			//--------------------------------------------------------------
			//@in : ���_�x�N�g��
			//@in : �����_�x�N�g��
			//@in : ������x�N�g��
			__IMPOETER void Seting_Camera(PCVECTOR3 e,PCVECTOR3 t,PCVECTOR3 u);
		
			//--------------------------------------------------------------------------------
			//�v���C���ɕς��������̃Z�b�g�J����
			//--------------------------------------------------------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : �����_
			//@in : �p�x
			//@in : ���[�h 1(���ʂ̊p�x) 2(���W�A���p) 3(���ʂ̊p�x���Z)
			__IMPOETER void SetPlayerCamera(PDirectDevice Device,PCVECTOR3 t,float angle = 0.0f,CAMERA_ANGLEMODE mode = CAMERAANGLE_NONE);
		
			//--------------------------------------------------------------------------
			//�ŏ���؂�ւ��ɕς��������̃Z�b�g�J����
			//--------------------------------------------------------------------------
			//@in : �����_
			//@in : �Y�[���l
			//@in : �p�x
			//@in : �A�b�v�l
			//@in : 1(�p�x�����) ����ȊO(���W�A���p)
			__IMPOETER void Seting_CameraS(PCVECTOR3 e,float zo,float ang,float up, bool IsDirectAngle = false);

			//------------------------------------------------
			//�^�[�Q�b�g���ƃX�N���[��
			//------------------------------------------------
			//0 : x, 1 : y, 2 : z
			__IMPOETER void tarGetScroll(float speed, int mode);

		private:	//�����̂�
			void (CAMERA::*key_action)(PDirectDevice Device,PCKEYS keys);
			
			//�֐��|�C���^�Ɋ��蓖�Ă�̂��ȉ��R��
			
			//----------------------------------------------------------------
			//�J�����`�F���W�A�N�V����
			//�L�[����ŃJ�����𓮂���
			//----------------------------------------------------------------
			//@in : �f�o�C�X
			//@in : �L�[
			__IMPOETER void	Keyof_CameraChange(PDirectDevice Device,PCKEYS keys);
			
			//--------------------------------------------------------------
			//�v���C���[�̐��ʐ؂�ւ�
			//--------------------------------------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : �L�[�N���X
			__IMPOETER void ChangeFrontLine(PDirectDevice Device,PCKEYS keys);

			//-------------------------------------------------------------
			//�r���[�ŃA�N�V�����������������Ɏ��s
			//-------------------------------------------------------------
			__IMPOETER void CameraVIEWMODE(PDirectDevice Device,PCKEYS keys);
			
			//--------------------------------------------------------------
			//�r���[�؂�ւ�
			//--------------------------------------------------------------
			//@in : DirectX�p�f�o�C�X
			//@in : ���[�h
			__IMPOETER void ChangeCameraVIEWMODE(PDirectDevice Device,int cameraviewMode);
	};

	typedef CAMERA*			PCAMERA;
	typedef const CAMERA*	PCCAMERA;

}
#endif