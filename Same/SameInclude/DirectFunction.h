#ifndef NanairoLib_FUNC_H
#define NanairoLib_FUNC_H

#ifndef _NanairoLib_MYVECTOR_H
#include <DirectParts.h>
#endif

//-----------------------------------------
//���蓖�Č^�֐��N���X�������ɋL��
//�K�v�Ȋ֐��𑝂₵����g���������͂����̃N���X���g����
//���f�[�^�ێ����K�v�ȏꍇ�͂��̃N���X�ɂ͓���邱�Ƃ͂ł��܂��񁄁�
//-----------------------------------------
namespace NanairoLib
{
	//-------------------------------
	//�p�x�������Ƃ��̎��
	//-------------------------------
	enum RAD_NUMBER
	{
		_NONERAD, _ANGLE_RAD, _RAD_COS, _RAD_SIN, _RAD_TAN, _RAD_TAN2
	};

	//-------------------------------
	//��r���Z�q�Ŏg�����
	//-------------------------------
	enum CHECK_NUMBER
	{
		CK_EQUAL, _CK_BIG, _CK_SMALL,
	};

	//------------------------------------------------------------------
	//�x�N�g���₻�̑��v�Z�ނ͂����Ɏ��[����
	///���̃N���X���Ăяo���Čv�Z����̂��ړI�I
	//------------------------------------------------------------------
	class VectorFunc
	{
	public:
		//-------------------------------------------------------
		//������������(A��ΏۂɁA�a����傫����)
		//-------------------------------------------------------
		//@in : �Ώ�A 
		//@in : �Ώ�B
		//@out :  �傫�� ? (true) : (false)
		__IMPOETER	bool Min_hantei(float checkA, float checkB);
		
		//-------------------------------------------------------------
		//3�����x�N�g����2������
		//-------------------------------------------------------------
		//@in :	�Ώۃx�N�g���E���͎n�_�x�N�g��
		//@in : �������͏I�_�x�N�g��
		//@out : �p���ɂ��2�����x�N�g���ɕϊ�������
		__IMPOETER	Vector2 GetVectorXZ(RCVector3 vec);
		__IMPOETER	Vector2 GetVectorXZ(RCVector3 start,RCVector3 end);
		__IMPOETER	Vector2 GetVectorXY(RCVector3 vec);
		__IMPOETER	Vector2 GetVectorXY(RCVector3 start, RCVector3 end);

		//--------------------------------------------------------------
		//�n�_����I�_�������������x�N�g��
		//--------------------------------------------------------------
		//@in : �n�_ 
		//@in : �I�_
		//@out : �o���オ���������x�N�g��
		__IMPOETER	Vector3 GetVecDistance(RCVector3 st, RCVector3 end);
		__IMPOETER	Vector2 GetVecDistance(RCVector2 st, RCVector2 end);
		__IMPOETER	Vector2 GetVecDistanceNormalize(RCVector2 st, RCVector2 end);

		//-------------------------------------------
		//���������߂�
		//-------------------------------------------
		//@in : �Ώ�
		//@out : ����
		__IMPOETER	float GetDistance(RCVector3 pos);
		__IMPOETER	float GetDistance(RCVector2 pos);
		__IMPOETER	float GetDistance(float dis);

		//--------------------------------------------------------------
		//�x�N�g���̑傫��
		//--------------------------------------------------------------
		//@in : �Ώۂ̃x�N�g��
		//@out : �p�l�̑傫��
		__IMPOETER	float GetVecDistanceLong(RCVector3 one);
		__IMPOETER	float GetVecDistanceLong(RCVector2 one);
		__IMPOETER	float GetVecDistanceLong(const float dx);
		__IMPOETER	float GetVecDistanceLong(const float ax, const float ay);
		__IMPOETER	float GetVecDistanceAbsLong(RCVector3 vecA, RCVector3 vecB);
		__IMPOETER	float GetVecDistanceAbsLong(RCVector2 vecA, RCVector2 vecB);

		//--------------------------------------------------------------
		//�x�N�g���̖@���x�N�g��
		//--------------------------------------------------------------
		//@in : �Ώۃx�N�g��,���͎n�_�x�N�g��
		//@in : �������͏I�_�x�N�g��
		//@out : �@���x�N�g���i�P�ʂ�������ԂŁj
		__IMPOETER	Vector3 GetNormal(RCVector3 st ,RCVector3 end);
		__IMPOETER	Vector2 GetNormal(RCVector2 st, RCVector2 end);
		__IMPOETER	Vector3 GetNormal(RCVector3 pos);
		__IMPOETER	Vector2 GetNormal(RCVector2 pos);

		//--------------------------------------------------------------
		//�x�N�g���̓���
		//--------------------------------------------------------------
		//@in : �Ώۃx�N�g���P
		//@in : �Ώۃx�N�g���Q
		//@out : ����
		__IMPOETER	float GetDot(RCVector3 checkA, RCVector3 checkB);
		__IMPOETER	float GetDot(RCVector2 checkA, RCVector2 checkB);
		__IMPOETER	float GetDotProjection(RCVector3 checkA, RCVector3 checkB);
		__IMPOETER	float GetDotProjection(RCVector2 checkA, RCVector2 checkB);
			
		//--------------------------------------------------------------
		//�x�N�g���̊O��
		//--------------------------------------------------------------
		//@in : �Ώۃx�N�g���P
		//@in : �Ώۃx�N�g���Q
		//@out	: 2D �� �O��
		//		: 3D �� �@���x�N�g��
		__IMPOETER	Vector3 GetCloss(RCVector3 checkA, RCVector3 checkB);
		__IMPOETER	float GetCloss(RCVector2 checkA, RCVector2 checkB);
		__IMPOETER	float GetClossProjection(RCVector2 checkA, RCVector2 checkB);

#ifdef _USED_DIRECTX
		//------------------------------------------------------------------
		//�s��̐i�s
		//------------------------------------------------------------------
		//@in : �|�����킹��s��
		//@in : �ړ��x�N�g��
		//@out : �ϊ��s��
		__IMPOETER	D3DXMATRIXA16 GetTransMat(PCMATRIX16 mat,RCVector3 vec);
		
		//---------------------------------------------------------------------------
		//�s��̉�](�A�t�B���ϊ�)
		//---------------------------------------------------------------------------
		//@in : �Ώۍs��
		//@in : ���_�֖߂��x�N�g��
		//@in : ��]�p�x
		//@out : �e���ł̕ϊ��s��
		__IMPOETER 	D3DXMATRIXA16 GetRotaX(PCMATRIX16 mat,RCVector3 vec,float angle);
		__IMPOETER	D3DXMATRIXA16 GetRotaY(PCMATRIX16 mat,RCVector3 vec,float angle);
		__IMPOETER	D3DXMATRIXA16 GetRotaZ(PCMATRIX16 mat,RCVector3 vec,float angle);

		//----------------------------------------------------------------------------------------------------
		//�N�H�[�^�j�I�����[���h���W�ϊ�
		//----------------------------------------------------------------------------------------------------
		//@posi(�ʒu) @scale(�g�嗦) @rotavec(�C�ӎ�) @ang(��]�p�x)
		//��	: ���ׂĂ��|�����킹���s��
		__IMPOETER	D3DXMATRIX SetworldQuaternion(RCVector3 posi,RCVector3 scale,RCVector3 rotavec,float ang);
		
		//-----------------------------------------------------------------
		//�N�H�[�^�j�I���ϊ�
		//-----------------------------------------------------------------
		//@in : �C�ӎ� 
		//@in : ��]�p�x
		//@out : �N�H�[�^�j�I���s��
		__IMPOETER	D3DXQUATERNION GetQuaternion(RCVector3 rota,float ang);
#endif

		//-------------------------------------------------------------
		//�p�x�̃��W�A���p�����߂�
		//-------------------------------------------------------------
		//0(���ʂ̊p�x) 1(cos��) 2(sin��) 3(tan��)
		//@out : ���W�A���p
		__IMPOETER	float ChangeRad(float cosA,int _angle_number = 0);
		__IMPOETER	float ChangeRadAtan2(RCVector2 vec); 
		__IMPOETER	float ChangeRadAtan2(RCVector2 vecA, RCVector2 vecB); 
		__IMPOETER	float ChangeRadAtan2(float vecX, float vecY); 
		__IMPOETER	float ChangeRadAtan2XY(RCVector3 vecA, RCVector3 vecB); 
		__IMPOETER	float ChangeRadAtan2XZ(RCVector3 vecA, RCVector3 vecB); 

		//--------------------------------------------------------------
		//���W�A������p�x�����߂�
		//--------------------------------------------------------------
		//0(���ʂ̊p�x) 1(cos��) 2(sin��) 3(tan��)
		//@out : �p�x
		__IMPOETER	float ChangeAngle(float cosA,int _angle_number);
		__IMPOETER	float ChangeAngleAtan2(RCVector2 vec); 
		__IMPOETER	float ChangeAngleAtan2(RCVector2 vecA, RCVector2 vecB); 
		__IMPOETER	float ChangeAngleAtan2(float vecX, float vecY);
		__IMPOETER	float ChangeAngleAtan2XY(RCVector3 vecA, RCVector3 vecB);
		__IMPOETER	float ChangeAngleAtan2XZ(RCVector3 vecA, RCVector3 vecB);

		//-------------------------------------------------------------
		//�x�N�g������p�x�����߂�
		//-------------------------------------------------------------
		//@in : ���߂����x�N�g��
		//@out : �p�x
		__IMPOETER	float GetAngleAtan2(RCVector2 st, RCVector2 end);

		//------------------------------------------------
		//�x�N�g������p�x�����߂�
		//------------------------------------------------
		//@in : ���߂����x�N�g��
		//@out : �p�x
		__IMPOETER	float GetVectorOfAngleY(RCVector3 vec);
		
		//-----------------------------------------------------------------
		//2�_����x�N�g�������ߊp�x�����߂�
		//-----------------------------------------------------------------
		//@in : �n�_�x�N�g��
		//@in : �I�_�x�N�g��
		//@out : �p�x
		__IMPOETER	float GetVectorOfAngleY(RCVector3 vecontrolA,RCVector3 vecontrolB);
		
		//----------------------------------------------------------------------------------------------------
		//4�_����2�̃x�N�g�������߁A�p�x�����߂�
		//----------------------------------------------------------------------------------------------------
		//@in : �x�N�g���`�̎n�_
		//@in : �x�N�g���`�̏I�_
		//@in : �x�N�g���a�̎n�_
		//@in : �x�N�g���a�̏I�_
		//@out : �p�x
		__IMPOETER	 float GetVectorOfAngleY(RCVector3 vecontrolA1,RCVector3 vecontrolA2,RCVector3 vecontrolB1,RCVector3 vecontrolB2);

		//------------------------------------------
		//��Βl�����߂�
		//------------------------------------------
		//@in : �Ώ�
		//@out : ��Βl
		__IMPOETER	Vector3 GetAbs(RCVector3 pos);
		__IMPOETER	Vector2 GetAbs(RCVector2 pos);
		__IMPOETER	float GetAbs(float pos);

		//------------------------------------------------------------------------------------------
		//���ɂ��������x�N�g�������߂�
		//------------------------------------------------------------------------------------------
		//@in : ���̃|�C���g 
		//@in : �O�̃|�C���g 
		//@out : �ړ��x�N�g��
		//@out : �ړ�����
		//@out : true(����) false(���s)
		__IMPOETER	bool SetNextPointVector(RCVector3 point,RCVector3 oldpos,Vector3 *anspos,float *dis);

		//------------------------------------------------------------------------------
		//�����x�N�g���̐i�ފp�x�����߂�
		//------------------------------------------------------------------------------
		//@in : �n�_ 
		//@in : �I�_ 
		//@in : �Ώۊp�x
		//@out : ���݂̃x�N�g������̊p�x�̍���Ԃ�
		__IMPOETER	float GetChangeAngleSin(RCVector2 stpos,RCVector2 endpos,float ang);
		__IMPOETER	float GetChangeAngleCos(RCVector2 stpos,RCVector2 endpos,float ang);

		//--------------------------------------------------------------------------------
		//�p�x�`�F���W
		//--------------------------------------------------------------------------------
		//@in : ���݂̃x�N�g��
		//@in : ��]�p�x
		//@out : ��]�����x�N�g��
		__IMPOETER	Vector3	VectorRotationXZ(RCVector3 vec,float ang,bool isRota = false);
		__IMPOETER	Vector2 VectorRotationXZ(RCVector2 vec,float ang,bool isRota);
		
		//----------------------------------------------------------------------------------
		//��������
		//----------------------------------------------------------------------------------
		//@in : �x�N�g��A
		//@in : �x�N�g��B
		//@in : �p�x�̑傫�� 
		//@out : ang��聛����������ۑ�
		//@in : 1(cos) 2(sin) 
		//@in : 1(�傫����_����) 2(��������_����)
		//@out : true(����) false(���s)
		__IMPOETER	bool Check_Direction(RCVector3 posA,RCVector3 posB,float ang,float *out,int _angle_number,int equalNumber);
		__IMPOETER	bool Check_Direction(RCVector2 posA,RCVector2 posB,float ang,float *out,int _angle_number,int equalNumber);

#ifdef _USED_DIRECTX
		//----------------------------------------------------------------------------------------------------------------
		//�G���~�[�g�Ȑ�
		//----------------------------------------------------------------------------------------------------------------
		//@in : �n�_���W
		//@in : �n�_�x�N�g��
		//@in : �I�_���W
		//@in : �I�_�x�N�g��
		//@in : �o�ߎ���
		//@in : ���v����
		//@inout : �v�Z���ꂽ���W
		//@out : �o�߂����v��B������(false)
		__IMPOETER	bool GetHermiteLine(RCVector2 start,RCVector2 v1,RCVector2 end,RCVector2 v2,int cnt,int time,PVECTOR2 ans);
#endif		
		//-------------------------------------------------------------------------------------------------------------------------
		//�x�W�F�Ȑ�
		//-------------------------------------------------------------------------------------------------------------------------
		//@in : �n�_
		//@in : �I�_
		//@in : ����P
		//@in : ����Q
		//@in : �o�ߎ���
		//@in : ���v����
		//@inout : �ϊ��x�N�g��
		//@out : �o�߂����v�𑝂�����false
		__IMPOETER	bool GetBjetLine(RCVector2 start,RCVector2 end,RCVector2 controlA,RCVector2 controlB,const int cnt,const int time,PVector2 ans);
		
		//--------------------------------------------------------------------------------------
		//�����_��Ԃ��֐�
		//--------------------------------------------------------------------------------------
		//@in   : �n�_
		//@in   : �I�_
		//@in    : �����l
		//@in    : �����l�Q
		//@out : �ϊ����W 
		__IMPOETER	Vector2 Inner_point(RCVector2 start,RCVector2 end,const float m,const float n);
		__IMPOETER	Vector3 Inner_point(RCVector3 start,RCVector3 end,const float m,const float n);
	};

}

#endif