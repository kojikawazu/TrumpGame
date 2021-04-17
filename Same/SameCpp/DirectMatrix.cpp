#pragma once

//-------------------------------------------------------------
//
//����}�g���b�N�X�N���X�������Ɋi�[
//
//-------------------------------------------------------------
#include <DirectParts.h>
#include <DirectFunction.h>

namespace NanairoLib
{
	//------------------------------------------------------------------//
	//////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------//
	//�s�������
	//--------------------------------------------------------------------
	MyMatrix::MyMatrix()
	{
		Identity();
	}

	MyMatrix::~MyMatrix(){}

	//--------------------------------------------------------------------
	//�P�ʉ�
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::Identity()
	{
		_12 = _13 = _14 = 0.0f;
		_21 = _23 = _24 = 0.0f;
		_31 = _32 = _34 = 0.0f;
		_41 = _42 = _43 = 0.0f;
		_11 = _22 = _33 = _44 = 1.0f;
		return *this;
	}

	//--------------------------------------------------------------------
	//������]
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::RotationX(float rad)
	{
		float cs = cosf( rad );
		float sn = sinf( rad );
		Identity();
		_22 = cs; _23 = -sn;
		_32 = sn; _33 = cs;
		return *this;
	}

	//--------------------------------------------------------------------
	//������]
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::RotationY(float rad)
	{
		float cs = cosf( rad );
		float sn = sinf( rad );
		Identity();
		_11 = cs;	_13 = sn;
		_31 = -sn;	_33 = cs;
		return *this;
	}
	
	//--------------------------------------------------------------------
	//������]
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::RotationZ(float rad)
	{
		float cs = cosf( rad );
		float sn = sinf( rad );
		Identity();
		_11 = cs;	_12 = -sn;
		_21 = sn;	_22 = cs;
		return *this;
	}

	//--------------------------------------------------------------------
	//���ꂼ��ŉ�]
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::RotationAxis(float rad, RVector3 v)
	{
		float cs = cosf( rad );
		float sn = sinf( rad );
		float tb = 1.f - cs;
		v.Normalize();
		Identity();
		_11 = tb * v.x * v.x + cs;
		_12 = tb * v.x * v.y + sn * v.z;
		_13 = tb * v.x * v.z - sn * v.y;
		_21 = tb * v.y * v.x - sn * v.z;
		_22 = tb * v.y * v.y + cs;
		_23 = tb * v.y * v.z + sn * v.x;
		_31 = tb * v.z * v.x + sn * v.y;
		_32 = tb * v.z * v.y - sn * v.x;
		_33 = tb * v.z * v.z + cs;
		return *this;
	}

#ifdef _USED_DIRECTX
	//--------------------------------------------------------------------
	//�N�H�[�^�j�I����]
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::RotationQuat(float rad, RVector3 v)
	{
		::D3DXQUATERNION quat;
		D3DXMATRIX mat = this->ChangeMatrixD3D();
		::D3DXQuaternionRotationAxis( &quat, &v.SetD3DVector3(), rad );
		::D3DXMatrixRotationQuaternion( &mat, &quat );
		*this = mat;

		return *this;
	}
#endif

	//--------------------------------------------------------------------
	//���ʂɈړ�
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::Translation(float x, float y, float z)
	{
		_41 = x, _42 = y, _43 = z;
		return *this;
	}

	MyMatrix& MyMatrix::Translation(RVector3 vec)
	{
		return Translation( vec.x, vec.y, vec.z );
	}

	//--------------------------------------------------------------------
	//�g�k
	//--------------------------------------------------------------------
	MyMatrix& MyMatrix::Scale(float x, float y, float z)
	{
		_11 = x, _12 = y, _13 = z;
		return *this;
	}
	MyMatrix& MyMatrix::Scale(float sc)
	{
		_11 = _12 = _13 = sc;
		return *this;
	}

	MyMatrix& MyMatrix::Scale(RVector3 v)
	{
		return Scale( v.x, v.y, v.z );
	}

	//----------------------------------------
	//�����̎擾
	//----------------------------------------
	float MyMatrix::Length()
	{
		return (_11 * _22 * _33 * _44 + _11 * _23 * _34 * _42 + _11 * _24 * _32 * _43 + 
				_12 * _21 * _34 * _43 + _12 * _23 * _31 * _44 + _12 * _24 * _33 * _41 + 
				_13 * _31 * _32 * _44 + _13 * _22 * _34 * _41 + _13 * _24 * _31 * _42 + 
				_14 * _21 * _33 * _42 + _14 * _22 * _31 * _43 + _14 * _23 * _32 * _41 -
				_11 * _22 * _34 * _43 - _11 * _23 * _32 * _44 - _11 * _24 * _33 * _42 -
				_12 * _21 * _33 * _44 - _12 * _23 * _34 * _41 - _12 * _24 * _31 * _43 -
				_13 * _21 * _34 * _42 - _13 * _22 * _31 * _44 - _13 * _24 * _32 * _41 -
				_14 * _21 * _32 * _43 - _14 * _22 * _33 * _41 - _14 * _23 * _31 * _42 );
	}

	//----------------------------------------
	//�ʒu�̎擾
	//----------------------------------------
	Vector3 MyMatrix::GetPos()
	{
		Vector3 pos;
		pos.SetVector( _41, _42, _43 );
		return pos;
	}

	//----------------------------------------
	//�t�s��
	//----------------------------------------
	MyMatrix MyMatrix::GetInverse()
	{
		//�������O�ȊO�̂Ƃ������t�s�񂪑��݂���
		if( this->Length() == 0 )
			return this->Identity();

		float det = 1.0f, p = 0.0f, d = 0.0f;
		for(int i=0; i<MATRIX_HEIGHT; i++)
		{
			p = m[i][i];
			det *= p;
			for(int j=0; j<MATRIX_HEIGHT; j++)
				m[i][j] /= p;
			m[i][i] = 1.0f / p;
			for(int j=0; j<MATRIX_HEIGHT; j++)
			{
				if(j != i)
				{
					d = m[j][i];
					for(int k=0; k<MATRIX_WIDTH; k++)
						(k != i ? m[j][k] -= m[i][k] * d : m[j][k] = -d / p );
				}
			}
		}

		return *this;
	}

	//----------------------------
	//�]�u�s��
	//----------------------------
	MyMatrix& MyMatrix::Transposed()
	{
		MyMatrix mat;
		for(int i=0; i<MATRIX_HEIGHT; i++)
		{
			for(int j=0; j<MATRIX_WIDTH; j++)
				mat.m[j][i] = this->m[i][j];
		}
		*this = mat;
		return *this;
	}

	//----------------------------------------
	//�s�񍇐�
	//----------------------------------------
	MyMatrix& MyMatrix::operator*=(MyMatrix& m)
	{
		MyMatrix& mt = *this;
		mt = mt * m;
		return mt;
	}

	//----------------------------------------
	//�����I�y���[�^
	//----------------------------------------
	MyMatrix MyMatrix::operator*(MyMatrix& m)
	{
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				this->m[i][j] = this->m[i][0] * m.m[0][j] + 
								this->m[i][1] * m.m[1][j] + 
								this->m[i][2] * m.m[2][j] +
								this->m[i][3] * m.m[3][j];
			}
		}
		return *this;
	}

#ifdef _USED_DIRECTX
	//----------------------------------------
	//�R�s�[�I�y���[�^
	//----------------------------------------
	MyMatrix& MyMatrix::operator=(D3DXMATRIX& m)
	{
		memcpy_s( this, sizeof( D3DXMATRIX ), &m, sizeof( D3DXMATRIX ) );
		return *this;
	}
#endif

	//----------------------------
	//�x�N�g�����s��ŕό`
	//----------------------------
	//@out :�@�ϊ���x�N�g��
	//@in : �ϊ��s��
	//@in : �ϊ����x�N�g��
	//@out : �ϊ���x�N�g��
	Vector4 MyMatrix::Transform(Vector4* out, Vector3* in)
	{
		Vector4 vec;
		vec.x = in->x * this->_11 + in->y * this->_12 + in->z * this->_13 + this->_14;
		vec.y = in->x * this->_21 + in->y * this->_22 + in->z * this->_23 + this->_24;
		vec.z = in->x * this->_31 + in->y * this->_32 + in->z * this->_33 + this->_34;
		vec.w = in->x * this->_41 + in->y * this->_42 + in->z * this->_43 + this->_44;

		if( out != NULL )	(*out) = vec;
		return vec;
	}

	//----------------------------------------------------------------------------------
	//�v���W�F�N�V�����s��ɕϊ�
	//----------------------------------------------------------------------------------
	//@in : ��p
	//@in : �A�X�y�N�g��
	//@in : �O���N���b�s���O����
	//@in : ����N���b�s���O����
	//@out : ���e�s��
	MyMatrix& MyMatrix::ChangePerspective(float fovy, float aspect, float zNear, float zFar)
	{
		this->Identity();
		float xmin, xmax, ymin, ymax;

		ymax = zNear * (float)::tan( fovy * 3.14f / 180.0f );
		ymin = -ymax;
		xmin = ymin * aspect;
		xmax = ymax * aspect;
		
		this->_11 = (2 * zNear) / (xmax - xmin);
		this->_22 = (2 * zNear) / (ymax - ymin);

		this->_13 = (xmax + xmin) / (xmax - xmin);
		this->_23 = (ymax + ymin) / (ymax - ymin);
		this->_33 = -(zFar + zNear) / (zFar - zNear);
		this->_43 = -2 * zFar * zNear / ( zFar - zNear );
		
		this->_34 = -1.0f;
		this->_44 = 0.0f;

		return *this;
	}

	//-------------------------------------------------------------------------------------------
	//�r���[�s��ɕϊ�
	//-------------------------------------------------------------------------------------------
	//@in : ���_�x�N�g��
	//@in : �����_�x�N�g��
	//@in : ������x�N�g��
	//@out : �r���[�s��
	MyMatrix& MyMatrix::ChangelookAt(const Vector3* eye, const Vector3* tarGet, const Vector3* up)
	{
		VectorFunc func;
		this->Identity();
		Vector3 X,Y,Z;

		//Z���x�N�g��
		Z.x = eye->x - tarGet->x;
		Z.y = eye->y - tarGet->y;
		Z.z = eye->z - tarGet->z;
		Z.Normalize();

		//Y���x�N�g��
		Y.x = up->x;
		Y.y = up->y;
		Y.z = up->z;

		//X���x�N�g�� = Y �~ Z
		X = func.GetCloss( Y, Z );

		//Y���x�N�g�� = Z �~ X
		Y = func.GetCloss( Z, X );

		X.Normalize();
		Y.Normalize();

		this->_11 = X.x; this->_12 = X.y; this->_13 = X.z;
		this->_21 = Y.x; this->_22 = Y.y; this->_23 = Y.z;
		this->_31 = Z.x; this->_32 = Z.y; this->_33 = Z.z;
		this->_14 = -eye->x;
		this->_24 = -eye->y;
		this->_34 = -eye->z;
		return *this;
	}

	//----------------------------------------
	//�r���[�|�[�g���ȒP�ɍ��
	//----------------------------------------
	MyMatrix& MyMatrix::GetViewPort(int width, int height)
	{
		*this = this->Identity();
		this->_11 = width * 0.5f;
		this->_22 = -(height * 0.5f);
		this->_33 = 1.0f;
		this->_41 = width * 0.5f;
		this->_42 = height * 0.5f;
		this->_44 = 1.0f;
		return *this;
	}

#ifdef _USED_DIRECTX
	//----------------------------------------
	//DirectX�p�s��֕ϊ�
	//----------------------------------------
	D3DXMATRIX MyMatrix::ChangeMatrixD3D()
	{
		D3DXMATRIX mat;
		::memcpy_s( this, sizeof( MyMatrix ), &mat, sizeof( D3DXMATRIX ) );
		return mat;
	}
#endif

}