#ifndef _NanairoLib_MYVECTOR_H
#define _NanairoLib_MYVECTOR_H

//-----------------------------------------------------
//
//����x�N�g���N���X
//
//-----------------------------------------------------

#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef _INC_MATH
#include <math.h>
#endif

namespace NanairoLib
{

	//-------------------------
	//�O���錾
	//-------------------------
	class Vector2;
	class Vector3;
	class Vector4;

	//���O�ȗ�//-----------------------
	typedef Vector3*		PVector3;
	typedef const Vector3*	PCVector3;
	typedef Vector3&		RVector3;
	typedef const Vector3&	RCVector3;
	typedef Vector2*		PVector2;
	typedef const Vector2*	PCVector2;
	typedef Vector2&		RVector2;
	typedef const Vector2&	RCVector2;
	typedef Vector4*		PVector4;
	typedef const Vector4*	PCVector4;
	typedef Vector4&		RVector4;
	typedef const Vector4&	RCVector4;
	//----------------------------------


	template<typename T = float>
	class SuperVector 
	{
	public:
		T x;

		__IMPOETER SuperVector();
		__IMPOETER SuperVector(T dx);
		__IMPOETER virtual ~SuperVector();

		//-----------------------------------------------------------
		//���
		//-----------------------------------------------------------
		__IMPOETER SuperVector& SetVector(T dx);
		__IMPOETER SuperVector& SetVector(SuperVector& in);
		__IMPOETER SuperVector& SetVector(const SuperVector* in);
		__IMPOETER SuperVector& SetPercentVector(T dx);
		__IMPOETER SuperVector& SetMaxScreen();
		__IMPOETER SuperVector& SetMinVector();
		__IMPOETER SuperVector& operator = (T in);
		__IMPOETER SuperVector& operator = (SuperVector& in);
		__IMPOETER SuperVector& operator = (const SuperVector* in);

		//-----------------------------------------------------------
		//��Βl�ϊ�
		//-----------------------------------------------------------
		__IMPOETER SuperVector& ChangeAbs();

		//-----------------------------------------------------------
		//���Z
		//-----------------------------------------------------------
		__IMPOETER SuperVector operator + (T val);
		__IMPOETER SuperVector operator + (SuperVector<T>& val);
		__IMPOETER SuperVector operator + (const SuperVector<T>* val);
		__IMPOETER SuperVector& operator += (T val);
		__IMPOETER SuperVector& operator += (SuperVector<T>& val);
		__IMPOETER SuperVector& operator += (const SuperVector<T>* val);
		__IMPOETER SuperVector& Add(T dx);
		__IMPOETER SuperVector& Add(SuperVector<T>& dx);
		__IMPOETER SuperVector& Add(const SuperVector<T>* dx);
		__IMPOETER SuperVector& operator ++();
		
		//-----------------------------------------------------------
		//���Z
		//-----------------------------------------------------------
		__IMPOETER SuperVector operator - (void);
		__IMPOETER SuperVector operator - (T val);
		__IMPOETER SuperVector operator - (SuperVector<T>& val);
		__IMPOETER SuperVector operator - (const SuperVector<T>* val);
		__IMPOETER SuperVector& operator -= (T val);
		__IMPOETER SuperVector& operator -= (SuperVector<T>& val);
		__IMPOETER SuperVector& operator -= (const SuperVector<T>* val);
		__IMPOETER SuperVector& Sub(T dx);
		__IMPOETER SuperVector& Sub(SuperVector<T>& dx);
		__IMPOETER SuperVector& Sub(const SuperVector<T>* dx);
		__IMPOETER SuperVector& operator--();
		__IMPOETER SuperVector& SubCut();

		//-----------------------------------------------------------
		//���ʂ̐ώZ
		//-----------------------------------------------------------
		__IMPOETER SuperVector operator * (T val);
		__IMPOETER SuperVector operator * (SuperVector& vec);
		__IMPOETER SuperVector operator * (const SuperVector* vec);
		__IMPOETER SuperVector& operator *= (T val);
		__IMPOETER SuperVector& operator *= (SuperVector& val);
		__IMPOETER SuperVector& operator *= (const SuperVector* val);

		//-----------------------------------------------------------
		//���Z
		//-----------------------------------------------------------
		__IMPOETER SuperVector operator / (T val);
		__IMPOETER SuperVector operator / (SuperVector& vec);
		__IMPOETER SuperVector operator / (const SuperVector* vec);
		__IMPOETER SuperVector& operator /= (T val);
		__IMPOETER SuperVector& operator /= (SuperVector& val);
		__IMPOETER SuperVector& operator /= (const SuperVector* val);

		//-----------------------------------------------------------
		//�x�N�g���̒���
		//-----------------------------------------------------------
		__IMPOETER float Length();

		//-----------------------------------------------------------
		//�x�N�g���̒����̓��
		//-----------------------------------------------------------
		__IMPOETER float LengthSquare();

		//-----------------------------------------------------------
		//�x�N�g���̒P�ʉ�
		//-----------------------------------------------------------
		__IMPOETER SuperVector& Normalize();
	};

	//-------------------------
	//2D�x�N�g��������
	//-------------------------
	class Vector2
	{
		public:
			float x,y;
		
		public:
			__IMPOETER Vector2();
			__IMPOETER Vector2(float dx, float dy);
			__IMPOETER ~Vector2();

		public:
			//-----------------------------------------------------------
			//�R���X�g���N�^�E�I�y���[�^�ȊO�ł̃x�N�g���Z�b�e�B���O
			//-----------------------------------------------------------
			__IMPOETER Vector2& SetVector(float dx, float dy);
			__IMPOETER Vector2& SetPercentVector(float dx, float dy);
			__IMPOETER Vector2& SetMaxScreen();
			__IMPOETER Vector2& SetMinVector();
			__IMPOETER Vector2& SetVector(Vector2& vec);
			__IMPOETER Vector2& SetVector(const Vector2* vec);
			__IMPOETER Vector2& SetVectorXY(Vector3& vec);
			__IMPOETER Vector2& SetVectorYZ(Vector3& vec);
			__IMPOETER Vector2& SetVectorZX(Vector3& vec);
			__IMPOETER Vector2& ChangeAbs();
			__IMPOETER Vector2& operator = (float val);
			__IMPOETER Vector2& operator = (Vector2& vec);
			__IMPOETER Vector2& operator = (const Vector2* vec);
			__IMPOETER Vector2& operator = (Vector3& vec);
			__IMPOETER Vector2& operator = (const Vector3* vec);
			__IMPOETER Vector2& operator = (Vector4& vec);
			__IMPOETER Vector2& operator = (const Vector4* vec);

			//-----------------------------------------------------------
			//�^�L���X�g
			//-----------------------------------------------------------
			__IMPOETER operator Vector2&();

			//-----------------------------------------------------------
			//���Z
			//-----------------------------------------------------------
			__IMPOETER Vector2 operator + (float val);
			__IMPOETER Vector2 operator + (Vector2& vec);
			__IMPOETER Vector2 operator + (const Vector2& vec);
			__IMPOETER Vector2 operator + (const Vector2* vec);
			__IMPOETER Vector2 operator + (Vector3& vec);
			__IMPOETER Vector2 operator + (const Vector3* vec);
			__IMPOETER Vector2 operator + (Vector4& vec);
			__IMPOETER Vector2 operator + (const Vector4* vec);
			__IMPOETER Vector2& operator += (float val);
			__IMPOETER Vector2& operator += (Vector2& vec);
			__IMPOETER Vector2& operator += (const Vector2* vec);
			__IMPOETER Vector2& operator += (Vector3& vec);
			__IMPOETER Vector2& operator += (const Vector3* vec);
			__IMPOETER Vector2& operator += (Vector4& vec);
			__IMPOETER Vector2& operator += (const Vector4* vec);
			__IMPOETER Vector2& Add(float dx, float dy);
			__IMPOETER Vector2& Add(Vector2& vec);
			__IMPOETER Vector2& Add(const Vector2* vec);
			__IMPOETER Vector2& Add(Vector3& vec);
			__IMPOETER Vector2& Add(const Vector3* vec);
			__IMPOETER Vector2& Add(Vector4& vec);
			__IMPOETER Vector2& Add(const Vector4* vec);

			//-----------------------------------------------------------
			//���Z
			//-----------------------------------------------------------
			__IMPOETER Vector2 operator - ();
			__IMPOETER Vector2 operator - (float val);
			__IMPOETER Vector2 operator - (Vector2& vec);
			__IMPOETER Vector2 operator - (const Vector2& vec);
			__IMPOETER Vector2 operator - (const Vector2* vec);
			__IMPOETER Vector2& operator -= (float val);
			__IMPOETER Vector2& operator -= (Vector2& vec);
			__IMPOETER Vector2& operator -= (const Vector2* vec);
			__IMPOETER Vector2& operator -= (const Vector2& vec);
			__IMPOETER Vector2& operator -= (Vector3& vec);
			__IMPOETER Vector2& operator -= (const Vector3* vec);
			__IMPOETER Vector2& operator -= (Vector4& vec);
			__IMPOETER Vector2& operator -= (const Vector4* vec);
			__IMPOETER Vector2& Sub(float dx,float dy);
			__IMPOETER Vector2& Sub(Vector2& vec);
			__IMPOETER Vector2& Sub(const Vector2* vec);
			__IMPOETER Vector2& Sub(Vector3& vec);
			__IMPOETER Vector2& Sub(const Vector3* vec);
			__IMPOETER Vector2& Sub(Vector4& vec);
			__IMPOETER Vector2& Sub(const Vector4* vec);

			__IMPOETER Vector2& SubCut();

			//-----------------------------------------------------------
			//���ʂ̐ώZ
			//-----------------------------------------------------------
			__IMPOETER Vector2 operator * (float val);
			__IMPOETER Vector2& operator *= (float val);
			__IMPOETER float operator * (Vector2& vec);
			__IMPOETER float operator * (const Vector2* vec);

			//-----------------------------------------------------------
			//���Z
			//-----------------------------------------------------------
			__IMPOETER Vector2 operator / (float val);
			__IMPOETER Vector2& operator /= (float val);
			__IMPOETER float operator / (Vector2& vec);
			__IMPOETER float operator / (const Vector2* vec);

			//-----------------------------------------------------------
			//�x�N�g���̒���
			//-----------------------------------------------------------
			__IMPOETER float Length();

			//-----------------------------------------------------------
			//�x�N�g���̒����̓��
			//-----------------------------------------------------------
			__IMPOETER float LengthSquare();

			//-----------------------------------------------------------
			//�x�N�g���̒P�ʉ�
			//-----------------------------------------------------------
			__IMPOETER Vector2& Normalize();

			//-----------------------------------------------------------
			//�x�N�g���̓���
			//-----------------------------------------------------------
			__IMPOETER float Dot(Vector2& vec);

			//-----------------------------------------------------------
			//�x�N�g���̊O��
			//-----------------------------------------------------------
			__IMPOETER float Closs(Vector2& vec);

			//--------------------------------------------------
#ifdef _USED_DIRECTX
			//-----------------------------------------------------------
			//DirectX�p�̃x�N�g��
			//-----------------------------------------------------------
			__IMPOETER Vector2(VECTOR2& vec);
			__IMPOETER VECTOR2 SetD3DVector2();
			__IMPOETER Vector2& SetVector(VECTOR2& vec);
			__IMPOETER Vector2& operator = (VECTOR2& vec);
			__IMPOETER Vector2& operator = (const VECTOR2* vec);
			__IMPOETER Vector2& operator = (VECTOR2* vec);
			__IMPOETER Vector2 operator + (VECTOR2& vec);
			__IMPOETER Vector2 operator - (VECTOR2& vec);
#endif
			//--------------------------------------------------
	
	};


	//-------------------------
	//3D�x�N�g��������
	//-------------------------
	class Vector3
	{
		public:
			float x,y,z;
		
		public:
			__IMPOETER Vector3();
			__IMPOETER Vector3(float dx, float dy, float dz);
			__IMPOETER ~Vector3();

		public:
			//------------------------------------------------------------
			//�R���X�g���N�^�E�I�y���[�^�ȊO�ł̃x�N�g���Z�b�e�B���O
			//------------------------------------------------------------
			__IMPOETER Vector3& SetVector(float dx, float dy, float dz);
			__IMPOETER Vector3& SetVector(Vector3& vec);
			__IMPOETER Vector3& SetVector(const Vector3* vec);
			__IMPOETER Vector3& operator = (float val);
			__IMPOETER Vector3& operator = (Vector3& vec);
			__IMPOETER Vector3& operator = (const Vector3* vec);
			__IMPOETER Vector3& operator = (Vector2& vec);
			__IMPOETER Vector3& operator = (const Vector2* vec);
			__IMPOETER Vector3& operator = (Vector4& vec);
			__IMPOETER Vector3& operator = (const Vector4* vec);

			//-----------------------------------------------------------
			//���L���X�g
			//-----------------------------------------------------------
			__IMPOETER operator Vector3&();

			//-----------------------------------------------------------
			//���Z
			//-----------------------------------------------------------
			__IMPOETER Vector3 operator + (float val);
			__IMPOETER Vector3 operator + (Vector3& vec);
			__IMPOETER Vector3 operator + (const Vector3& vec);
			__IMPOETER Vector3 operator + (Vector2& vec);
			__IMPOETER Vector3 operator + (const Vector2* vec);
			__IMPOETER Vector3 operator + (Vector4& vec);
			__IMPOETER Vector3 operator + (const Vector4* vec);
			__IMPOETER Vector3& operator += (float val);
			__IMPOETER Vector3& operator += (Vector3& vec);
			__IMPOETER Vector3& operator += (const Vector3& vec);
			__IMPOETER Vector3& operator += (Vector2& vec);
			__IMPOETER Vector3& operator += (const Vector2* vec);
			__IMPOETER Vector3& operator += (Vector4& vec);
			__IMPOETER Vector3& operator += (const Vector4* vec);
			__IMPOETER Vector3& Add(float dx, float dy, float dz);
			__IMPOETER Vector3& Add(Vector3& vec);
			__IMPOETER Vector3& Add(const Vector3* vec);
			__IMPOETER Vector3& Add(Vector2& vec);
			__IMPOETER Vector3& Add(const Vector2* vec);
			__IMPOETER Vector3& Add(Vector4& vec);
			__IMPOETER Vector3& Add(const Vector4* vec);

			//-----------------------------------------------------------
			//���Z
			//-----------------------------------------------------------
			__IMPOETER Vector3& operator - ();
			__IMPOETER Vector3 operator - (float val);
			__IMPOETER Vector3 operator - (Vector3& vec);
			__IMPOETER Vector3 operator - (const Vector3& vec);
			__IMPOETER Vector3 operator - (const Vector3* vec);
			__IMPOETER Vector3 operator - (Vector2& vec);
			__IMPOETER Vector3 operator - (const Vector2* vec);
			__IMPOETER Vector3 operator - (Vector4& vec);
			__IMPOETER Vector3 operator - (const Vector4* vec);
			__IMPOETER Vector3& operator -= (float val);
			__IMPOETER Vector3& operator -= (Vector3& vec);
			__IMPOETER Vector3& operator -= (const Vector3& vec);
			__IMPOETER Vector3& operator -= (Vector2& vec);
			__IMPOETER Vector3& operator -= (const Vector2& vec);
			__IMPOETER Vector3& operator -= (Vector4& vec);
			__IMPOETER Vector3& operator -= (const Vector4& vec);
			__IMPOETER Vector3& Sub(float dx,float dy, float dz);
			__IMPOETER Vector3& Sub(Vector3& vec);
			__IMPOETER Vector3& Sub(const Vector3* vec);
			__IMPOETER Vector3& Sub(Vector2& vec);
			__IMPOETER Vector3& Sub(const Vector2* vec);
			__IMPOETER Vector3& Sub(Vector4& vec);
			__IMPOETER Vector3& Sub(const Vector4* vec);

			//-----------------------------------------------------------
			//���ʂ̐ώZ
			//-----------------------------------------------------------
			__IMPOETER Vector3 operator * (float val);
			__IMPOETER Vector3& operator *= (float val);
			__IMPOETER float operator * (Vector3& vec);
			__IMPOETER float operator * (const Vector3* vec);

			//-----------------------------------------------------------
			//���Z
			//-----------------------------------------------------------
			__IMPOETER Vector3 operator / (float val);
			__IMPOETER Vector3& operator /= (float val);
			__IMPOETER Vector3 operator / (Vector3& vec);
			__IMPOETER Vector3 operator / (PCVector3 vec);

			//-----------------------------------------------------------
			//�x�N�g���̒���
			//-----------------------------------------------------------
			__IMPOETER float Length();

			//-----------------------------------------------------------
			//�x�N�g���̒����̓��
			//-----------------------------------------------------------
			__IMPOETER float LengthSquare();

			//-----------------------------------------------------------
			//�x�N�g���̒P�ʉ�
			//-----------------------------------------------------------
			__IMPOETER Vector3& Normalize();

			//-----------------------------------------------------------
			//�x�N�g���̓���
			//-----------------------------------------------------------
			__IMPOETER float Dot(Vector3& vec);

			//-----------------------------------------------------------
			//�x�N�g���̊O��
			//-----------------------------------------------------------
			__IMPOETER Vector3 Closs(Vector3& vec);

			//-----------------------------------------------------------
			//�x�N�g����2���������ύX���Ȃ��p
			//-----------------------------------------------------------
			__IMPOETER Vector3& SetVectorXY(float dx, float dy);
			__IMPOETER Vector3& SetVectorXZ(float dx, float dz);

			//-----------------------------------------------------------
			//�X�P�[�����O
			//-----------------------------------------------------------
			__IMPOETER void Scaling(float abs);

			//-----------------------------------------------------------
			//DirectX�p�̃x�N�g��
			//-----------------------------------------------------------
#ifdef _USED_DIRECTX
			__IMPOETER Vector3(VECTOR3& vec);
			__IMPOETER Vector3& operator = (const VECTOR3 vec);
			__IMPOETER VECTOR3 SetD3DVector3();
			__IMPOETER Vector3& SetVector(VECTOR3& vec);
			__IMPOETER Vector3& operator = (VECTOR3& vec);
			__IMPOETER Vector3& operator = (const VECTOR3* vec);
			__IMPOETER Vector3& operator = (VECTOR3* vec);
			__IMPOETER Vector3 operator + (VECTOR3& vec);
			__IMPOETER Vector3 operator - (VECTOR3& vec);
#endif
			//--------------------------------------------------
	
	};

	//-------------------------
	//4D�x�N�g��������
	//-------------------------
	class Vector4
	{
		public:
			float x, y, z, w;
		
		public:
			 __IMPOETER Vector4();
			 __IMPOETER Vector4(float dx, float dy,float dz,float dw);
			 __IMPOETER ~Vector4();

		public:
			//------------------------------------------------------------------
			//�R���X�g���N�^�E�I�y���[�^�ȊO�ł̃x�N�g���Z�b�e�B���O
			//------------------------------------------------------------------
			__IMPOETER Vector4& SetVector(float dx, float dy,float dz,float dw);
			__IMPOETER Vector4& SetVector(Vector4& vec);
			__IMPOETER Vector4& SetVector(const Vector4* vec);
			__IMPOETER Vector4& ChangeAbs();
			__IMPOETER Vector4& operator = (Vector4& vec);
			__IMPOETER Vector4& operator = (const Vector4* vec);
			 
			//------------------------------------------------------------------
			//���L���X�g
			//------------------------------------------------------------------
			__IMPOETER operator Vector4&();

			//------------------------------------------------------------------
			//���Z
			//------------------------------------------------------------------
			__IMPOETER Vector4 operator + (float val);
			__IMPOETER Vector4 operator + (Vector4& vec);
			__IMPOETER Vector4 operator + (const Vector4& vec);
			__IMPOETER Vector4 operator + (const Vector4* vec);
			__IMPOETER Vector4 operator + (Vector2& vec);
			__IMPOETER Vector4 operator + (const Vector2* vec);
			__IMPOETER Vector4 operator + (Vector3& vec);
			__IMPOETER Vector4 operator + (const Vector3* vec);
			__IMPOETER Vector4& operator += (float val);
			__IMPOETER Vector4& operator += (Vector4& vec);
			__IMPOETER Vector4& operator += (const Vector4& vec);
			__IMPOETER Vector4& operator += (const Vector4* vec);
			__IMPOETER Vector4& operator += (Vector2& vec);
			__IMPOETER Vector4& operator += (const Vector2* vec);
			__IMPOETER Vector4& operator += (Vector3& vec);
			__IMPOETER Vector4& operator += (const Vector3* vec);
			__IMPOETER Vector4& Add(float dx, float dy,float dz,float dw);
			__IMPOETER Vector4& Add(Vector4& vec);
			__IMPOETER Vector4& Add(const Vector4* vec);
			__IMPOETER Vector4& Add(Vector2& vec);
			__IMPOETER Vector4& Add(const Vector2* vec);
			__IMPOETER Vector4& Add(Vector3& vec);
			__IMPOETER Vector4& Add(const Vector3* vec);

			//------------------------------------------------------------------
			//���Z
			//------------------------------------------------------------------
			__IMPOETER Vector4 operator - ();
			__IMPOETER Vector4 operator - (float val);
			__IMPOETER Vector4 operator - (Vector4& vec);
			__IMPOETER Vector4 operator - (const Vector4& vec);
			__IMPOETER Vector4 operator - (const Vector4* vec);
			__IMPOETER Vector4 operator - (Vector2& vec);
			__IMPOETER Vector4 operator - (const Vector2* vec);
			__IMPOETER Vector4 operator - (Vector3& vec);
			__IMPOETER Vector4 operator - (const Vector3* vec);
			__IMPOETER Vector4& operator -= (float val);
			__IMPOETER Vector4& operator -= (Vector4& vec);
			__IMPOETER Vector4& operator -= (const Vector4& vec);
			__IMPOETER Vector4& operator -= (const Vector4* vec);
			__IMPOETER Vector4& operator -= (Vector2& vec);
			__IMPOETER Vector4& operator -= (const Vector2* vec);
			__IMPOETER Vector4& operator -= (Vector3& vec);
			__IMPOETER Vector4& operator -= (const Vector3* vec);
			__IMPOETER Vector4& Sub(float dx,float dy,float dz,float dw);
			__IMPOETER Vector4& Sub(Vector4& vec);
			__IMPOETER Vector4& Sub(const Vector4* vec);
			__IMPOETER Vector4& Sub(Vector3& vec);
			__IMPOETER Vector4& Sub(const Vector3* vec);
			__IMPOETER Vector4& Sub(Vector2& vec);
			__IMPOETER Vector4& Sub(const Vector2* vec);

			//------------------------------------------------------------------
			//���ʂ̐ώZ
			//------------------------------------------------------------------
			__IMPOETER Vector4 operator * (float val);
			__IMPOETER Vector4& operator *= (float val);

			//------------------------------------------------------------------
			//���Z
			//------------------------------------------------------------------
			__IMPOETER Vector4 operator / (float val);
			__IMPOETER Vector4& operator /= (float val);

			//------------------------------------------------------------------
			//�x�N�g���̒���
			//------------------------------------------------------------------
			__IMPOETER float Length();

			//------------------------------------------------------------------
			//�x�N�g���̒����̓��
			//------------------------------------------------------------------
			__IMPOETER float LengthSquare();

			//------------------------------------------------------------------
			//�x�N�g���̒P�ʉ�
			//------------------------------------------------------------------
			__IMPOETER Vector4& Normalize();

			//--------------------------------------------------
#ifdef _USED_DIRECTX
			//------------------------------------------------------------------
			//DirectX�p�̃x�N�g��
			//------------------------------------------------------------------
			 __IMPOETER Vector4(VECTOR4& vec);
			 __IMPOETER VECTOR4 SetD3DVector4();
			 __IMPOETER Vector4& SetVector(VECTOR4& vec);
			 __IMPOETER Vector4& operator = (VECTOR4& vec);
			 __IMPOETER Vector4& operator = (const VECTOR4* vec);
			 __IMPOETER Vector4& operator = (VECTOR4* vec);
			 __IMPOETER Vector4 operator + (VECTOR4& vec);
			 __IMPOETER Vector4 operator - (VECTOR4& vec);
#endif
			//--------------------------------------------------
	
	};

	//-------------------------
	//�s�������
	//-------------------------
	class MyMatrix 
	{
		public:
			static const int MATRIX_WIDTH = 3;
			static const int MATRIX_HEIGHT = 3;
			union
			{
				struct
				{
					float	_11, _12, _13, _14,
							_21, _22, _23, _24, 
							_31, _32, _33, _34,
							_41, _42, _43, _44;
				};
				float m[MATRIX_HEIGHT][MATRIX_WIDTH];
			};

		public:
			//-------------------------
			//�f�R��
			//-------------------------
			__IMPOETER MyMatrix();
			__IMPOETER ~MyMatrix();

		public:
			//-------------------------
			//����
			//-------------------------
			__IMPOETER float Length();

			//-------------------------
			//�P�ʉ�
			//-------------------------
			__IMPOETER MyMatrix& Identity();

			//-------------------------
			//X����]
			//-------------------------
			__IMPOETER MyMatrix& RotationX(float rad);

			//-------------------------
			//Y����]
			//-------------------------
			__IMPOETER MyMatrix& RotationY(float rad);

			//-------------------------
			//Z����]
			//-------------------------
			__IMPOETER MyMatrix& RotationZ(float rad);

			//-------------------------
			//�C�ӎ���]
			//-------------------------
			__IMPOETER MyMatrix& RotationAxis(float rad, Vector3& v);
			__IMPOETER MyMatrix& RotationQuat(float rad, Vector3& v);

			//-------------------------
			//�ړ�
			//-------------------------
			__IMPOETER MyMatrix& Translation(float x, float y, float z);
			__IMPOETER MyMatrix& Translation(Vector3& vec);
			
			//-------------------------
			//�g��E�k��
			//-------------------------
			__IMPOETER MyMatrix& Scale(float x, float y, float z);
			__IMPOETER MyMatrix& Scale(float sc);
			__IMPOETER MyMatrix& Scale(Vector3& v);

			//-------------------------
			//�I�y���[�^
			//(�����A�R�s�[)
			//-------------------------
			__IMPOETER MyMatrix& operator*=(MyMatrix& m);
#ifdef _USED_DIRECTX
			__IMPOETER MyMatrix& operator=(D3DXMATRIX& m);
#endif

			//-------------------------
			//�r���[�|�[�g�s��̐���
			//-------------------------
			__IMPOETER MyMatrix& GetViewPort(int width, int height);

			//-------------------------
			//�t�s��
			//-------------------------
			__IMPOETER MyMatrix GetInverse();
			__IMPOETER MyMatrix operator*(MyMatrix& m);
			
			//-------------------------
			//�s�񂩂璷�������߂�
			//-------------------------
			__IMPOETER Vector3 GetPos();

			//----------------------------
			//�x�N�g�����s��ŕό`
			//@out :�@�ϊ���x�N�g��
			//@in : �ϊ����x�N�g��
			//@out : �ϊ���x�N�g��
			//----------------------------
			__IMPOETER Vector4 Transform(Vector4* out, Vector3* in);

			//----------------------------
			//�]�u�s��
			//----------------------------
			MyMatrix& Transposed();

			MyMatrix& ChangePerspective(float fovy, float aspect, float zNear, float zFar);
			MyMatrix& ChangelookAt(const Vector3* eye, const Vector3* tarGet, const Vector3* up);
#ifdef _USED_DIRECTX
			__IMPOETER D3DXMATRIX ChangeMatrixD3D();
#endif
	};

	//�N�H�[�^�j�I���N���X
	class MyQuatenion
	{
	public:
		float t;				//������
		Vector3 imaginaryNum;	//������

	public:
		//--------------------------------------
		//�f�R��
		//--------------------------------------
		__IMPOETER MyQuatenion(){}
		__IMPOETER ~MyQuatenion(){}

		//---------------------------------------
		//�[��������
		//---------------------------------------
		__IMPOETER void ChangeZero();

		//---------------------------------------
		//�N�H�[�^�j�I���ݒ�
		//---------------------------------------
		__IMPOETER MyQuatenion& SetQuatenion(float X,float Y,float Z);
		__IMPOETER MyQuatenion& SetQuatenion(MyQuatenion& quat);

		//---------------------------------------
		//�P�ʉ�
		//---------------------------------------
		__IMPOETER MyQuatenion& Identity();
		
		//---------------------------------------
		//�N�H�[�^�j�I�����m�̍���
		//---------------------------------------
		//@inout : �o�̓N�H�[�^�j�I��
		//@in : �������P
		//@in : �������Q
		//@out : �o�̓N�H�[�^�j�I��
		__IMPOETER MyQuatenion& Dot(MyQuatenion& out, MyQuatenion& a, MyQuatenion& b);

		//---------------------------------------
		//��]�N�H�[�^�j�I��
		//---------------------------------------
		//@in : ���W�A���p
		//@in : �C�ӎ��w�l
		//@in : �C�ӎ��x�l
		//@in : �C�ӎ��y�l
		//@out : ��]�N�H�[�^�j�I��
		__IMPOETER MyQuatenion& RotationQuatenion(float radian, float AxisX, float AxisY, float AxisZ);

		//---------------------------------------
		//�N�H�[�^�j�I������s������o��
		//---------------------------------------
		__IMPOETER MyMatrix& GetMatrix(MyMatrix& out);

		//---------------------------------------
		//�s����N�H�[�^�j�I���ō���
		//---------------------------------------
		//@inout : �o�͍s��
		//@in : �N�H�[�^�j�I��
		//@in : ���͍s��
		//@out : �o�͍s��
		__IMPOETER MyMatrix& RotationQuatanion(MyMatrix& out, MyQuatenion& quat, MyMatrix& in);

		//---------------------------------------
		//�I�y���[�^�n��������
		//---------------------------------------
		__IMPOETER MyQuatenion& operator = (MyQuatenion& quat);
		__IMPOETER MyQuatenion& operator = (const MyQuatenion* quat);
		__IMPOETER MyQuatenion& operator * (MyQuatenion& quat);
		__IMPOETER MyQuatenion& operator * (const MyQuatenion* quat);
	};
}
#endif