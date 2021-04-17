#pragma once
//----------------------------------------------------------------------
//
//�x�N�g���ϊ���l�X�Ȍv�Z�ނ�ړI�Ƃ������\�b�h�������ɂ����Ă܂�
//
//----------------------------------------------------------------------
#include <DirectFunction.h>

namespace NanairoLib
{
	//-------------------------------------------------------
	//������������(A��ΏۂɁA�a����傫����)
	//-------------------------------------------------------
	//@in : �Ώ�A 
	//@in : �Ώ�B
	//@out :  �傫�� ? (true) : (false)
	bool VectorFunc::Min_hantei(float checkA,float checkB)
	{
		return (checkA < checkB);
	}
	
	//-------------------------------------------------------------
	//3�����x�N�g����2������
	//-------------------------------------------------------------
	//@in :	�Ώۃx�N�g��
	//@out : �p���ɂ��2�����x�N�g���ɕϊ�������
	#pragma region �R�����x�N�g�����Q������
	Vector2 VectorFunc::GetVectorXZ(RCVector3 vec)
	{
		return ( Vector2( vec.x,vec.z ) );
	}

	Vector2 VectorFunc::GetVectorXZ(RCVector3 start,RCVector3 end)
	{
		return ( Vector2( end.x - start.x, end.z - start.z ) );
	}

	Vector2 VectorFunc::GetVectorXY(RCVector3 vec)
	{
		return ( Vector2( vec.x, vec.y ) );
	}

	Vector2 GetVectorXY(RCVector3 start, RCVector3 end)
	{
		return ( Vector2( end.x - start.x, end.y - start.y ) );
	}
	#pragma endregion

	//--------------------------------------------------------------
	//�n�_����I�_�������������x�N�g��
	//--------------------------------------------------------------
	//@in : �n�_ 
	//@in : �I�_
	//@out : �o���オ���������x�N�g��
	#pragma region �n�_����I�_�������������x�N�g��
	Vector3 VectorFunc::GetVecDistance(RCVector3 st,RCVector3 end)
	{
		return ((Vector3)(end) - (st));
	}

	Vector2 VectorFunc::GetVecDistance(RCVector2 st,RCVector2 end)
	{
		return ((Vector2)(end) - (st));
	}

	Vector2 VectorFunc::GetVecDistanceNormalize(RCVector2 st,RCVector2 end)
	{
		return this->GetNormal((Vector2)(end) - (st));
	}
	#pragma endregion

	//-------------------------------------------
	//���������߂�
	//-------------------------------------------
	//@in : �Ώ�
	//@out : ����
	#pragma region ���������߂�
	float VectorFunc::GetDistance(RCVector3 pos)
	{
		return this->GetVecDistanceLong(pos);
	}

	float VectorFunc::GetDistance(RCVector2 pos)
	{
		return this->GetVecDistanceLong(pos);
	}

	float VectorFunc::GetDistance(float dis)
	{
		return dis;
	}
	#pragma endregion
	
	//--------------------------------------------------------------
	//�x�N�g���̑傫��
	//--------------------------------------------------------------
	//@in : �Ώۂ̃x�N�g��
	//@out : �p�l�̑傫��
	#pragma region �x�N�g���̑傫��
	float VectorFunc::GetVecDistanceLong(RCVector3 one)
	{
		return ( sqrt( this->GetDot( one, one ) ) );
	}

	float VectorFunc::GetVecDistanceLong(RCVector2 one)
	{
		return ( sqrt( this->GetDot( one,one ) ) );
	}

	float VectorFunc::GetVecDistanceLong(const float dx){
		return (sqrt(dx));
	}

	float VectorFunc::GetVecDistanceLong(const float ax,const float ay){
		return (sqrt(ax * ax + ay * ay));
	}

	float VectorFunc::GetVecDistanceAbsLong(RCVector3 vecA, RCVector3 vecB){
		return this->GetDistance(this->GetAbs(this->GetVecDistance(vecA, vecB)));
	}

	float VectorFunc::GetVecDistanceAbsLong(RCVector2 vecA, RCVector2 vecB){
		return this->GetDistance(this->GetAbs(this->GetVecDistance(vecA, vecB)));
	}
	#pragma endregion

	//--------------------------------------------------------------
	//�x�N�g���̖@���x�N�g��
	//--------------------------------------------------------------
	//@in : �Ώۃx�N�g��,���͎n�_�x�N�g��
	//@in : �������͏I�_�x�N�g��
	//@out : �@���x�N�g���i�P�ʂ�������ԂŁj
	#pragma region �R�����x�N�g���̖@��
	Vector3 VectorFunc::GetNormal(RCVector3 st,RCVector3 end)
	{
		Vector3 normal = GetVecDistance(st, end);
		return (normal /= GetVecDistanceLong(normal));
	}

	Vector2 VectorFunc::GetNormal(RCVector2 st,RCVector2 end)
	{
		Vector2 normal = GetVecDistance(st, end);
		return (normal /= GetVecDistanceLong(normal));
	}

	Vector3 VectorFunc::GetNormal(RCVector3 pos)
	{
		float length = this->GetVecDistanceLong(pos);
		return (length == 0 ? Vector3(0,0,0) :
				Vector3(pos.x / length, pos.y / length, pos.z / length));
	}

	Vector2 VectorFunc::GetNormal(RCVector2 pos)
	{
		float length = this->GetVecDistanceLong(pos);
		return (length == 0 ? Vector2(0,0) : 
					Vector2(pos.x / length, pos.y / length));
	}
	#pragma endregion

	//--------------------------------------------------------------
	//�x�N�g���̓���
	//--------------------------------------------------------------
	//@in : �Ώۃx�N�g���P
	//@in : �Ώۃx�N�g���Q
	//@out : ����
	#pragma region ����
	float VectorFunc::GetDot(RCVector3 checkA,RCVector3 checkB)
	{
		return (checkA.x * checkB.x + checkA.y * checkB.y + checkA.z * checkB.z);
	}

	float VectorFunc::GetDot(RCVector2 checkA,RCVector2 checkB){
		return (checkA.x * checkB.x + checkA.y * checkB.y);
	}

	float VectorFunc::GetDotProjection(RCVector3 checkA, RCVector3 checkB)
	{
		Vector3 vec = (checkB);
		vec.Normalize();
		return ( checkA.x * vec.x + checkA.y * vec.y + checkA.z * vec.z );
	}
	float VectorFunc::GetDotProjection(RCVector2 checkA, RCVector2 checkB)
	{
		Vector2 vec = (checkB);
		vec.Normalize();
		return ( checkA.x * vec.x + checkA.y * vec.y );
	}
	#pragma endregion

	//--------------------------------------------------------------
	//�x�N�g���̊O��
	//--------------------------------------------------------------
	//@in : �Ώۃx�N�g���P
	//@in : �Ώۃx�N�g���Q
	//@out	: 2D �� �O��
	//		: 3D �� �@���x�N�g��
	#pragma region �O��
	Vector3 VectorFunc::GetCloss(RCVector3 checkA,RCVector3 checkB)
	{
		return Vector3(checkA.y * checkB.z - checkB.y * checkA.z,
										checkA.z * checkB.x - checkB.z * checkA.x,
											checkA.x * checkB.y - checkB.x * checkA.y);
	}

	float VectorFunc::GetCloss(RCVector2 checkA,RCVector2 checkB)
	{
		return (checkA.x * checkB.y - checkB.x * checkA.y);
	}

	float VectorFunc::GetClossProjection(RCVector2 checkA, RCVector2 checkB)
	{
		Vector2 vec = (checkB);
		vec.Normalize();
		return ( checkA.x * vec.y - vec.x * checkA.y );
	}
	#pragma endregion

#ifdef _USED_DIRECTX
	//------------------------------------------------------------------
	//�s��̐i�s
	//------------------------------------------------------------------
	//@in : �|�����킹��s��
	//@in : �ړ��x�N�g��
	//@out : �ϊ��s��
	D3DXMATRIXA16 VectorFunc::GetTransMat(const D3DXMATRIXA16 *mat,RCVector3 vec)
	{
		D3DXMATRIXA16 temp;
		D3DXMatrixTranslation(&temp,vec.x,vec.y,vec.z);
		return (*mat) * (temp);
	}

	//---------------------------------------------------------------------------
	//�s��̉�](�A�t�B���ϊ�)
	//---------------------------------------------------------------------------
	//@in : �Ώۍs��
	//@in : ���_�֖߂��x�N�g��
	//@in : ��]�p�x
	//@out : �e���ł̕ϊ��s��
	#pragma region �s��̉�]
	D3DXMATRIXA16 VectorFunc::GetRotaX(const D3DXMATRIXA16 *mat,RCVector3 vec,float angle)
	{
		return (*mat) * (*D3DXMatrixTranslation(NULL,-vec.x,-vec.y,-vec.z)) *
						    (*D3DXMatrixRotationX(NULL,angle)) * 
							  (*D3DXMatrixTranslation(NULL,vec.x,vec.y,vec.z));
	}

	D3DXMATRIXA16 VectorFunc::GetRotaY(const D3DXMATRIXA16 *mat,RCVector3 vec,float angle)
	{

		return (*mat) * (*D3DXMatrixTranslation(NULL,-vec.x,-vec.y,-vec.z)) *
						    (*D3DXMatrixRotationY(NULL,angle)) * 
							  (*D3DXMatrixTranslation(NULL,vec.x,vec.y,vec.z));
	}

	D3DXMATRIXA16 VectorFunc::GetRotaZ(const D3DXMATRIXA16 *mat,RCVector3 vec,float angle)
	{
		return (*mat) * (*D3DXMatrixTranslation(NULL,-vec.x,-vec.y,-vec.z)) *
						    (*D3DXMatrixRotationZ(NULL,angle)) * 
							  (*D3DXMatrixTranslation(NULL,vec.x,vec.y,vec.z));
	}
	#pragma endregion

	//----------------------------------------------------------------------------------------------------
	//�N�H�[�^�j�I�����[���h���W�ϊ�
	//----------------------------------------------------------------------------------------------------
	//@posi(�ʒu) @scale(�g�嗦) @rotavec(�C�ӎ�) @ang(��]�p�x)
	//��	: ���ׂĂ��|�����킹���s��
	D3DXMATRIX VectorFunc::SetworldQuaternion(RCVector3 posi,RCVector3 scale,RCVector3 rotavec,float ang)
	{
		return (*::D3DXMatrixTransformation(NULL, NULL, NULL, &((Vector3&)scale).SetD3DVector3(), NULL, &this->GetQuaternion(rotavec, ang), &((Vector3&)posi).SetD3DVector3()));
	}
	
	//-----------------------------------------------------------------
	//�N�H�[�^�j�I���ϊ�
	//-----------------------------------------------------------------
	//@in : �C�ӎ� 
	//@in : ��]�p�x
	//@out : �N�H�[�^�j�I���s��
	D3DXQUATERNION VectorFunc::GetQuaternion(RCVector3 rota,float ang)
	{
		return (*::D3DXQuaternionRotationAxis(NULL, &((Vector3&)rota).SetD3DVector3(), ang));
	}
#endif

	//-------------------------------------------------------------
	//�p�x�̃��W�A���p�����߂�
	//-------------------------------------------------------------
	//0(���ʂ̊p�x) 1(cos��) 2(sin��) 3(tan��)
	//@out : ���W�A���p
	#pragma region �p�x�̃��W�A���p���o��
	//���W�A���p�����߂�
	float VectorFunc::ChangeRad(float cosA,int _angle_number)
	{
		float ang = 0.0f;
		switch(_angle_number + 1)
		{
			case _ANGLE_RAD:	//���ʂ̊p�x�ϊ�
				ang = SET_PI(cosA);	break;
			case _RAD_COS:	//cos�Ƃ������ꍇ
				ang = acos(cosA);	break;
			case _RAD_SIN:	//sin�Ƃ������ꍇ
				ang = asin(cosA);	break;
			case _RAD_TAN:	//tan�Ƃ������ꍇ
				ang = atan(cosA);	break;
		}
		return ang;
	}

	float VectorFunc::ChangeRadAtan2(RCVector2 vec)
	{
		return atan2( vec.y, vec.x );
	}

	float VectorFunc::ChangeRadAtan2(RCVector2 vecA, RCVector2 vecB)
	{
		return atan2( vecB.y - vecA.y, vecB.x - vecA.x );
	}

	float VectorFunc::ChangeRadAtan2(float vecX, float vecY)
	{
		return atan2( vecY, vecX );
	}

	float VectorFunc::ChangeRadAtan2XY(RCVector3 vecA, RCVector3 vecB)
	{
		return atan2( vecB.y - vecA.y, vecB.x - vecA.x );
	}

	float VectorFunc::ChangeRadAtan2XZ(RCVector3 vecA, RCVector3 vecB)
	{
		return atan2( vecB.z - vecA.z, vecB.x - vecA.x );
	}
	#pragma endregion

	//--------------------------------------------------------------
	//���W�A������p�x�����߂�
	//--------------------------------------------------------------
	//0(���ʂ̊p�x) 1(cos��) 2(sin��) 3(tan��)
	//@out : �p�x
	#pragma region �p�x�����߂�
	//���ʂ̊p�x�����߂�
	float VectorFunc::ChangeAngle(float cosA,int _angle_number)
	{
		float ang = 0.0f;
		switch(_angle_number + 1)
		{
		case _ANGLE_RAD:	//���ʂ̊p�x�ϊ�
			ang = BACK_PI(cosA);
			break;
		case _RAD_COS:	//cos�Ƃ������ꍇ
			ang = BACK_PI(acos(cosA));
			break;
		case _RAD_SIN:	//sin�Ƃ������ꍇ
			ang = BACK_PI(asin(cosA));
			break;
		case _RAD_TAN:	//tan�Ƃ������ꍇ
			ang = BACK_PI(atan(cosA));
			break;
		}
		return ang;
	}

	float VectorFunc::ChangeAngleAtan2(RCVector2 vec)
	{
		return BACK_PI( atan2( vec.y, vec.x ) );
	}

	float VectorFunc::ChangeAngleAtan2(RCVector2 vecA, RCVector2 vecB)
	{
		return BACK_PI( atan2( vecB.y - vecA.y, vecB.x - vecA.x ) );
	}

	float VectorFunc::ChangeAngleAtan2(float vecX, float vecY)
	{
		return BACK_PI( atan2( vecY, vecX ) );
	}

	float VectorFunc::ChangeAngleAtan2XY(RCVector3 vecA, RCVector3 vecB)
	{
		return BACK_PI( atan2( vecB.y - vecA.y, vecB.x - vecA.x ) );
	}

	float VectorFunc::ChangeAngleAtan2XZ(RCVector3 vecA, RCVector3 vecB)
	{
		return BACK_PI( atan2( vecB.z - vecA.z, vecB.x - vecA.x ) );
	}
	#pragma endregion

	//-------------------------------------------------------------
	//�x�N�g������p�x�����߂�
	//-------------------------------------------------------------
	//@in : ���߂����x�N�g��
	//@out : �p�x
	float VectorFunc::GetAngleAtan2(RCVector2 st, RCVector2 end)
	{
		//���W�A������x�ɕϊ����Ă���Ԃ�
		return this->ChangeAngleAtan2( st, end );
	}

	//------------------------------------------------
	//�x�N�g������p�x�����߂�
	//------------------------------------------------
	//@in : ���߂����x�N�g��
	//@out : �p�x
	float VectorFunc::GetVectorOfAngleY(RCVector3 vec)
	{
		return this->ChangeAngleAtan2( vec.x, vec.z );
	}
	
	//-----------------------------------------------------------------
	//2�_����x�N�g�������ߊp�x�����߂�
	//-----------------------------------------------------------------
	//@in : �n�_�x�N�g��
	//@in : �I�_�x�N�g��
	//@out : �p�x
	float VectorFunc::GetVectorOfAngleY(RCVector3 vecontrolA,RCVector3 vecontrolB)
	{
		return this->ChangeAngleAtan2XZ( vecontrolA, vecontrolB );
	}

	//----------------------------------------------------------------------------------------------------
	//4�_����2�̃x�N�g�������߁A�p�x�����߂�
	//----------------------------------------------------------------------------------------------------
	//@in : �x�N�g���`�̎n�_
	//@in : �x�N�g���`�̏I�_
	//@in : �x�N�g���a�̎n�_
	//@in : �x�N�g���a�̏I�_
	//@out : �p�x
	float VectorFunc::GetVectorOfAngleY(RCVector3 vecontrolA1,RCVector3 vecontrolA2,RCVector3 vecontrolB1,RCVector3 vecontrolB2)
	{
		return this->ChangeAngle( this->GetDot( this->GetVectorXZ( vecontrolA1, vecontrolA2 ).Normalize(), this->GetVectorXZ( vecontrolB1, vecontrolB2 ).Normalize() ) , _RAD_COS );
	}

	//------------------------------------------
	//��Βl�����߂�
	//------------------------------------------
	//@in : �Ώ�
	//@out : ��Βl
	#pragma region ��Βl�ϊ�
	Vector3 VectorFunc::GetAbs(RCVector3 pos)
	{
		return Vector3((float)abs(pos.x),(float)abs(pos.y),(float)abs(pos.z));
	}

	Vector2 VectorFunc::GetAbs(RCVector2 pos)
	{
		return Vector2((float)abs(pos.x),(float)abs(pos.y));
	}
	float VectorFunc::GetAbs(float pos)
	{
		return (float)abs(pos);
	}
	#pragma endregion

	//------------------------------------------------------------------------------------------
	//���ɂ��������x�N�g�������߂�
	//------------------------------------------------------------------------------------------
	//@in : ���̃|�C���g 
	//@in : �O�̃|�C���g 
	//@out : �ړ��x�N�g��
	//@out : �ړ�����
	//@out : true(����) false(���s)
	bool VectorFunc::SetNextPointVector(RCVector3 point,RCVector3 oldpos,Vector3 *anspos,float *dis)
	{
		//����n�_�܂ł̋��������߂�
		Vector3 pos = (Vector3)(point) - (oldpos);
		(*dis) = GetVecDistanceLong(pos);
		(*anspos) = GetNormal(pos);
		return true;
	}

	//------------------------------------------------------------------------------
	//�����x�N�g���̐i�ފp�x�����߂�
	//------------------------------------------------------------------------------
	//@in : �n�_ 
	//@in : �I�_ 
	//@in : �Ώۊp�x
	//@out : ���݂̃x�N�g������̊p�x�̍���Ԃ�
	#pragma region �p�x�`�F���W�p�x�̎擾
	float VectorFunc::GetChangeAngleSin(RCVector2 stpos,RCVector2 endpos,float ang)
	{
		return ChangeRad(this->GetCloss(GetNormal((this->GetVecDistance(stpos, endpos))), Vector2(1.0f * sin(ang),1.0f * cos(ang))), 2);
	}

	float VectorFunc::GetChangeAngleCos(RCVector2 stpos,RCVector2 endpos,float ang)
	{
		return ChangeRad(this->GetDot(this->GetNormal(this->GetVecDistance(stpos, endpos)), Vector2(1.0f * sin(ang),1.0f * cos(ang))), 1);
	}
	#pragma endregion

	//--------------------------------------------------------------------------------
	//�p�x�`�F���W
	//--------------------------------------------------------------------------------
	//@in : ���݂̃x�N�g��
	//@in : ��]�p�x
	//@in : true(��]����)�@false(��]���Ȃ�)
	//@out : ��]�����x�N�g��
	#pragma region �x�N�g���̉�]
	Vector3 VectorFunc::VectorRotationXZ(RCVector3 vec,float ang,bool isRota)
	{
		Vector3 a;
		if( isRota )
		{
			a.x = vec.x * cos(ang) - vec.z * sin(ang);
			a.z = vec.x * sin(ang) + vec.z * cos(ang);
			a.y = vec.y;
			return a;
		}
		else	
			return (vec);
	}

	Vector2 VectorFunc::VectorRotationXZ(RCVector2 vec,float ang,bool isRota)
	{
		Vector2 a;
		if( isRota )
		{
			a.x = vec.x * cos(ang) - vec.y * sin(ang);
			a.y = vec.x * sin(ang) + vec.y * cos(ang);
			return a;
		}
		else	
			return (vec);
	}
	#pragma endregion

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
	#pragma region ��������
	bool VectorFunc::Check_Direction(RCVector3 posA,RCVector3 posB,float ang,float *out,int _angle_number,int equalNumber)
	{ 
		Vector2 A,B;
		float dis;

		A = GetNormal(GetVectorXZ(posA));
		B = GetNormal(GetVectorXZ(posB));
		
		switch( _angle_number )
		{
			case NanairoLib::_RAD_COS:	dis = GetDot(A,B);	break;
			case NanairoLib::_RAD_SIN:	dis = GetCloss(A,B);	break;
			default:						return false;
		}

		switch( equalNumber )
		{
			case _CK_BIG:	//�傫�����������������߂�
				if(dis >= ang)
				{
					*out = dis;
					return true;
				}
				else			
					return false;
			case _CK_SMALL:
				if(dis <= ang)
				{
					*out = dis;
					return true;
				}
				else			
					return false;
			default:			
				return false;
		}
	}

	bool VectorFunc::Check_Direction(RCVector2 posA,RCVector2 posB,float ang,float *out,int _angle_number,int equalNumber){
		float dis;
		switch( _angle_number ){
			case NanairoLib::_RAD_COS:	//cos
				dis = GetDot(posA,posB);	break;
			case NanairoLib::_RAD_SIN:	//sin
				dis = GetCloss(posA,posB);	break;
			default:						return false;
		}

		switch( equalNumber ){
			case _CK_BIG:	//�傫�����������������߂�
				if(dis >= ang){
					*out = dis;
					return true;
				}
				else			
					return false;
			case _CK_SMALL:
				if(dis <= ang){
					*out = dis;
					return true;
				}
				else			
					return false;
			default:			
				return false;
		}
	}
	#pragma endregion

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
	bool VectorFunc::GetHermiteLine(RCVector2 start,RCVector2 v1,RCVector2 end,RCVector2 v2,int cnt,int time,PVECTOR2 ans)
	{
		//cnter�͂O�`�P�̊Ԃɂ���܂�
		float cnter = (float)cnt / time;
		float s[3] = {cnter * cnter * cnter, cnter * cnter, cnter};
		float mx[4] = {start.x, v1.x, end.x, v2.y};
		float my[4] = {start.y, v1.y, end.y, v2.y};

		ans->x = ( ( 2 * mx[0] ) + ( mx[1] ) - ( 2 * mx[2] ) + ( mx[3] )) * s[0] + 
				 ( (-3 * mx[0] ) - ( 2 * mx[1] ) + ( 3 * mx[2] ) - ( mx[3] )) * s[1] +
				 ( mx[1] ) * s[2] + ( mx[0] );

		ans->y = ( ( 2 * my[0] ) + ( my[1] ) - ( 2 * my[2] ) + ( my[3] )) * s[0] + 
				 ( (-3 * my[0] ) - ( 2 * my[1] ) + ( 3 * my[2] ) - ( my[3] )) * s[1] +
				 ( my[1] ) * s[2] + ( my[0] );
		
		//�������v���Ԃ��o�ߎ��Ԃ𒴂�����I��
		return ( cnt > time ? false : true );
	}
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
	bool VectorFunc::GetBjetLine(RCVector2 start,RCVector2 end,RCVector2 controlA,
								RCVector2 controlB,const int cnt,const int time,PVector2 ans)
	{
		Vector2 p[4] = {(start),(controlA),(controlB),(end)};
		float cnter = (float)(cnt / time);
		float m = cnter, n = 1.0f - cnter;
		Vector2 s1[3],s2[3];

		//1��ڂ̓����_�擾
		for(int i=0; i<3; i++)
			s1[i] = this->Inner_point(p[i], p[i+1],m,n);
		//2��ڂ̓����_�擾
		for(int i=0; i<2; i++)
			s2[i] = this->Inner_point(s1[i], s1[i+1],m,n);

		//3��ڂ̓����_�i���ݓ_�j�擾
		//���݂̍��W�ݒ�
		(*ans) = this->Inner_point(s2[0],s2[1],m,n);

		return (cnt > time ? false : true);
	}

	//--------------------------------------------------------------------------------------
	//�����_��Ԃ��֐�
	//--------------------------------------------------------------------------------------
	//@in   : �n�_
	//@in   : �I�_
	//@in    : �����l
	//@in    : �����l�Q
	//@out : �ϊ����W 
	#pragma region �����_�x�N�g��
	Vector2 VectorFunc::Inner_point(RCVector2 start,RCVector2 end,const float m,const float n)
	{
		return Vector2((n * start.x + m * end.x) / (m + n) , (n * start.y + m * end.y) / (m + n));
	}

	Vector3 VectorFunc::Inner_point(RCVector3 start,RCVector3 end,const float m,const float n)
	{
		return Vector3(	(n * start.x + m * end.x) / (m + n), (n * start.y + m * end.y) / (m + n), (n * start.z + m * end.z) / (m + n)	);
	}
	#pragma endregion
}
