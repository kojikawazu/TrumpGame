#pragma once

//-------------------------------------------------------------
//
//����N�H�[�^�j�I���N���X�������Ɋi�[
//
//-------------------------------------------------------------
#include <DirectNeed.h>
#include <DirectParts.h>

namespace NanairoLib
{
	//---------------------------------------------------
	//���O�N�H�[�^�j�I���ɃN�H�[�^�j�I�����|�����킹��
	//---------------------------------------------------
	MyQuatenion& MyQuatenion::operator * (MyQuatenion& quat)
	{
		MyQuatenion q;
		this->Dot( q, *this, quat );
		*this = q;
		return *this;
	}

	MyQuatenion& MyQuatenion::operator * (const MyQuatenion* quat)
	{
		MyQuatenion q;
		this->Dot( q, *this, (MyQuatenion)*quat );
		*this = q;
		return *this;
	}

	//---------------------------------------------------
	//�R�s�[
	//---------------------------------------------------
	MyQuatenion& MyQuatenion::operator = (MyQuatenion& quat)
	{
		this->t = quat.t;
		this->imaginaryNum = quat.imaginaryNum;
		return *this;
	}

	MyQuatenion& MyQuatenion::operator = (const MyQuatenion* quat)
	{
		this->t = quat->t;
		this->imaginaryNum = (Vector3)quat->imaginaryNum;
		return *this;
	}

	//---------------------------------------
	//�N�H�[�^�j�I�����m�̍���
	//---------------------------------------
	//@inout : �o�̓N�H�[�^�j�I��
	//@in : �������P
	//@in : �������Q
	//@out : �o�̓N�H�[�^�j�I��
	MyQuatenion& MyQuatenion::Dot(MyQuatenion& out, MyQuatenion& a, MyQuatenion& b)
	{
		float d1, d2, d3, d4;

		d1 = a.t * b.t;
		d2 = -a.imaginaryNum.x * b.imaginaryNum.x;
		d3 = -a.imaginaryNum.y * b.imaginaryNum.y;
		d4 = -a.imaginaryNum.z * b.imaginaryNum.z;
		out.t = d1 + d2 + d3 + d4;

		d1 = a.t * b.imaginaryNum.x;
		d2 = b.t * a.imaginaryNum.x;
		d3 = a.imaginaryNum.y * b.imaginaryNum.z;
		d4 = -a.imaginaryNum.z * b.imaginaryNum.y;
		out.imaginaryNum.x = d1 + d2 + d3 + d4;

		d1 = a.t * b.imaginaryNum.y;
		d2 = b.t * a.imaginaryNum.y;
		d3 = a.imaginaryNum.z * b.imaginaryNum.x;
		d4 = -a.imaginaryNum.x * b.imaginaryNum.z;
		out.imaginaryNum.y = d1 + d2 + d3 + d4;

		d1 = a.t * b.imaginaryNum.z;
		d2 = b.t * a.imaginaryNum.z;
		d3 = a.imaginaryNum.x * b.imaginaryNum.y;
		d4 = -a.imaginaryNum.y * b.imaginaryNum.x;
		out.imaginaryNum.z = d1 + d2 + d3 + d4;

		return out;
	}

	//---------------------------------------
	//��]�N�H�[�^�j�I��
	//---------------------------------------
	//@in : ���W�A���p
	//@in : �C�ӎ��w�l
	//@in : �C�ӎ��x�l
	//@in : �C�ӎ��y�l
	//@out : ��]�N�H�[�^�j�I��
	MyQuatenion& MyQuatenion::RotationQuatenion(float radian, float AxisX, float AxisY, float AxisZ)
	{
		MyQuatenion ans;
		float norm;
		float c, s;

		this->ChangeZero();
		ans.ChangeZero();
		norm = AxisX * AxisX + AxisY * AxisY + AxisZ * AxisZ;
		if( norm <= 0.0f )
			return *this;

		norm = 1.0f / sqrt( norm );
		AxisX *= norm;
		AxisY *= norm;
		AxisZ *= norm;

		c = cos( radian );
		s = sin( radian );

		ans.t = c;
		ans.imaginaryNum.x = s * AxisX;
		ans.imaginaryNum.y = s * AxisX;
		ans.imaginaryNum.z = s * AxisX;

		*this = ans;
		return *this;
	}

	//---------------------------------------
	//�[��������
	//---------------------------------------
	void MyQuatenion::ChangeZero()
	{
		this->t = this->imaginaryNum.x = this->imaginaryNum.y = this->imaginaryNum.z = 0.0f;
	}

	//---------------------------------------
	//�N�H�[�^�j�I���ݒ�
	//---------------------------------------
	MyQuatenion& MyQuatenion::SetQuatenion(float X,float Y,float Z)
	{
		this->t = 0.0f;
		this->imaginaryNum.x = X;
		this->imaginaryNum.y = Y;
		this->imaginaryNum.z = Z;
		return *this;
	}

	//---------------------------------------
	//�P�ʉ�
	//---------------------------------------
	MyQuatenion& MyQuatenion::Identity()
	{
		this->t = 0.0f;
		this->imaginaryNum.x = this->imaginaryNum.y = this->imaginaryNum.z = 1.0f;
		return *this;
	}

	//---------------------------------------
	//�N�H�[�^�j�I���ݒ�
	//---------------------------------------
	//@in : ���̓N�H�[�^�j�I��
	MyQuatenion& MyQuatenion::SetQuatenion(MyQuatenion& quat)
	{
		this->t = 2.0f * acos( quat.t );
		this->imaginaryNum.x = quat.imaginaryNum.x;
		this->imaginaryNum.y = quat.imaginaryNum.y;
		this->imaginaryNum.z = quat.imaginaryNum.z;
		this->imaginaryNum.Normalize();
		
		return *this;
	}

	//---------------------------------------
	//�N�H�[�^�j�I������s������o��
	//---------------------------------------
	//@inout : ���o����s��
	//@out : ���o����s��
	MyMatrix& MyQuatenion::GetMatrix(MyMatrix& out)
	{
		
		out.Identity();

		out.m[0][0] = 1 - 2 * ( this->imaginaryNum.y * this->imaginaryNum.y + this->imaginaryNum.z * this->imaginaryNum.z );
		out.m[0][1] = 2 * ( this->imaginaryNum.x * this->imaginaryNum.y - this->t * this->imaginaryNum.z );
		out.m[0][2] = 2 * ( this->t * this->imaginaryNum.y + this->imaginaryNum.x * this->imaginaryNum.z );

		out.m[1][0] = 2 * ( this->imaginaryNum.x * this->imaginaryNum.y + this->t * this->imaginaryNum.z );
		out.m[1][1] = 1 - 2 * ( this->imaginaryNum.x * this->imaginaryNum.x + this->imaginaryNum.z * this->imaginaryNum.z );
		out.m[1][2] = 2 * ( this->imaginaryNum.y * this->imaginaryNum.z - this->t * this->imaginaryNum.x );

		out.m[1][0] = 2 * ( this->imaginaryNum.x * this->imaginaryNum.z - this->t * this->imaginaryNum.y );
		out.m[1][1] = 2 * ( this->imaginaryNum.y * this->imaginaryNum.z + this->t * this->imaginaryNum.x );
		out.m[1][2] = 1 - 2 * ( this->imaginaryNum.x * this->imaginaryNum.x + this->imaginaryNum.y * this->imaginaryNum.y );

		return out;
	}

#ifdef _USED_DIRECTX
	//---------------------------------------
	//�s����N�H�[�^�j�I���ō���
	//---------------------------------------
	//@inout : �o�͍s��
	//@in : �N�H�[�^�j�I��
	//@in : ���͍s��
	//@out : �o�͍s��
	MyMatrix& MyQuatenion::RotationQuatanion(MyMatrix& out, MyQuatenion& quat, MyMatrix& in)
	{
		quat.GetMatrix(out);
		out = in * out;
		return out;

		struct Artisan3D
		{
			Vector3 pos;
			Vector3 normal;
			Vector2 UV;
		};
		
		D3DVERTEXELEMENT9 v[4];
		v[0].Stream = 0;
		v[0].Offset = 0;
		v[0].Type = ::D3DDECLTYPE_FLOAT3;
		v[0].Method = ::D3DDECLMETHOD_DEFAULT;
		v[0].Usage = ::D3DDECLUSAGE_POSITION;
		v[0].UsageIndex = 0;

		v[1].Stream = 0;
		v[1].Offset = sizeof(Vector3);
		v[1].Type = ::D3DDECLTYPE_FLOAT3;
		v[1].Method = ::D3DDECLMETHOD_DEFAULT;
		v[1].Usage = ::D3DDECLUSAGE_NORMAL;
		v[1].UsageIndex = 0;

		v[2].Stream = 0;
		v[2].Offset = sizeof(Vector3);
		v[2].Type = ::D3DDECLTYPE_FLOAT2;
		v[2].Method = ::D3DDECLMETHOD_DEFAULT;
		v[2].Usage = ::D3DDECLUSAGE_TEXCOORD;
		v[2].UsageIndex = 0;

		v[3].Stream = 0xff;
		v[3].Offset = 0;
		v[3].Type = ::D3DDECLTYPE_UNUSED;
		v[3].Method = 0;
		v[3].Usage = 0;
		v[3].UsageIndex = 0;
	}
#endif

}