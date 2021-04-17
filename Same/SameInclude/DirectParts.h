#ifndef _NanairoLib_MYVECTOR_H
#define _NanairoLib_MYVECTOR_H

//-----------------------------------------------------
//
//自作ベクトルクラス
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
	//前方宣言
	//-------------------------
	class Vector2;
	class Vector3;
	class Vector4;

	//名前簡略//-----------------------
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
		//代入
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
		//絶対値変換
		//-----------------------------------------------------------
		__IMPOETER SuperVector& ChangeAbs();

		//-----------------------------------------------------------
		//加算
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
		//減算
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
		//普通の積算
		//-----------------------------------------------------------
		__IMPOETER SuperVector operator * (T val);
		__IMPOETER SuperVector operator * (SuperVector& vec);
		__IMPOETER SuperVector operator * (const SuperVector* vec);
		__IMPOETER SuperVector& operator *= (T val);
		__IMPOETER SuperVector& operator *= (SuperVector& val);
		__IMPOETER SuperVector& operator *= (const SuperVector* val);

		//-----------------------------------------------------------
		//除算
		//-----------------------------------------------------------
		__IMPOETER SuperVector operator / (T val);
		__IMPOETER SuperVector operator / (SuperVector& vec);
		__IMPOETER SuperVector operator / (const SuperVector* vec);
		__IMPOETER SuperVector& operator /= (T val);
		__IMPOETER SuperVector& operator /= (SuperVector& val);
		__IMPOETER SuperVector& operator /= (const SuperVector* val);

		//-----------------------------------------------------------
		//ベクトルの長さ
		//-----------------------------------------------------------
		__IMPOETER float Length();

		//-----------------------------------------------------------
		//ベクトルの長さの二乗
		//-----------------------------------------------------------
		__IMPOETER float LengthSquare();

		//-----------------------------------------------------------
		//ベクトルの単位化
		//-----------------------------------------------------------
		__IMPOETER SuperVector& Normalize();
	};

	//-------------------------
	//2Dベクトルを自作
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
			//コンストラクタ・オペレータ以外でのベクトルセッティング
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
			//型キャスト
			//-----------------------------------------------------------
			__IMPOETER operator Vector2&();

			//-----------------------------------------------------------
			//加算
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
			//減算
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
			//普通の積算
			//-----------------------------------------------------------
			__IMPOETER Vector2 operator * (float val);
			__IMPOETER Vector2& operator *= (float val);
			__IMPOETER float operator * (Vector2& vec);
			__IMPOETER float operator * (const Vector2* vec);

			//-----------------------------------------------------------
			//除算
			//-----------------------------------------------------------
			__IMPOETER Vector2 operator / (float val);
			__IMPOETER Vector2& operator /= (float val);
			__IMPOETER float operator / (Vector2& vec);
			__IMPOETER float operator / (const Vector2* vec);

			//-----------------------------------------------------------
			//ベクトルの長さ
			//-----------------------------------------------------------
			__IMPOETER float Length();

			//-----------------------------------------------------------
			//ベクトルの長さの二乗
			//-----------------------------------------------------------
			__IMPOETER float LengthSquare();

			//-----------------------------------------------------------
			//ベクトルの単位化
			//-----------------------------------------------------------
			__IMPOETER Vector2& Normalize();

			//-----------------------------------------------------------
			//ベクトルの内積
			//-----------------------------------------------------------
			__IMPOETER float Dot(Vector2& vec);

			//-----------------------------------------------------------
			//ベクトルの外積
			//-----------------------------------------------------------
			__IMPOETER float Closs(Vector2& vec);

			//--------------------------------------------------
#ifdef _USED_DIRECTX
			//-----------------------------------------------------------
			//DirectX用のベクトル
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
	//3Dベクトルを自作
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
			//コンストラクタ・オペレータ以外でのベクトルセッティング
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
			//肩キャスト
			//-----------------------------------------------------------
			__IMPOETER operator Vector3&();

			//-----------------------------------------------------------
			//加算
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
			//減算
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
			//普通の積算
			//-----------------------------------------------------------
			__IMPOETER Vector3 operator * (float val);
			__IMPOETER Vector3& operator *= (float val);
			__IMPOETER float operator * (Vector3& vec);
			__IMPOETER float operator * (const Vector3* vec);

			//-----------------------------------------------------------
			//除算
			//-----------------------------------------------------------
			__IMPOETER Vector3 operator / (float val);
			__IMPOETER Vector3& operator /= (float val);
			__IMPOETER Vector3 operator / (Vector3& vec);
			__IMPOETER Vector3 operator / (PCVector3 vec);

			//-----------------------------------------------------------
			//ベクトルの長さ
			//-----------------------------------------------------------
			__IMPOETER float Length();

			//-----------------------------------------------------------
			//ベクトルの長さの二乗
			//-----------------------------------------------------------
			__IMPOETER float LengthSquare();

			//-----------------------------------------------------------
			//ベクトルの単位化
			//-----------------------------------------------------------
			__IMPOETER Vector3& Normalize();

			//-----------------------------------------------------------
			//ベクトルの内積
			//-----------------------------------------------------------
			__IMPOETER float Dot(Vector3& vec);

			//-----------------------------------------------------------
			//ベクトルの外積
			//-----------------------------------------------------------
			__IMPOETER Vector3 Closs(Vector3& vec);

			//-----------------------------------------------------------
			//ベクトルで2か所しか変更しない用
			//-----------------------------------------------------------
			__IMPOETER Vector3& SetVectorXY(float dx, float dy);
			__IMPOETER Vector3& SetVectorXZ(float dx, float dz);

			//-----------------------------------------------------------
			//スケーリング
			//-----------------------------------------------------------
			__IMPOETER void Scaling(float abs);

			//-----------------------------------------------------------
			//DirectX用のベクトル
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
	//4Dベクトルを自作
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
			//コンストラクタ・オペレータ以外でのベクトルセッティング
			//------------------------------------------------------------------
			__IMPOETER Vector4& SetVector(float dx, float dy,float dz,float dw);
			__IMPOETER Vector4& SetVector(Vector4& vec);
			__IMPOETER Vector4& SetVector(const Vector4* vec);
			__IMPOETER Vector4& ChangeAbs();
			__IMPOETER Vector4& operator = (Vector4& vec);
			__IMPOETER Vector4& operator = (const Vector4* vec);
			 
			//------------------------------------------------------------------
			//肩キャスト
			//------------------------------------------------------------------
			__IMPOETER operator Vector4&();

			//------------------------------------------------------------------
			//加算
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
			//減算
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
			//普通の積算
			//------------------------------------------------------------------
			__IMPOETER Vector4 operator * (float val);
			__IMPOETER Vector4& operator *= (float val);

			//------------------------------------------------------------------
			//除算
			//------------------------------------------------------------------
			__IMPOETER Vector4 operator / (float val);
			__IMPOETER Vector4& operator /= (float val);

			//------------------------------------------------------------------
			//ベクトルの長さ
			//------------------------------------------------------------------
			__IMPOETER float Length();

			//------------------------------------------------------------------
			//ベクトルの長さの二乗
			//------------------------------------------------------------------
			__IMPOETER float LengthSquare();

			//------------------------------------------------------------------
			//ベクトルの単位化
			//------------------------------------------------------------------
			__IMPOETER Vector4& Normalize();

			//--------------------------------------------------
#ifdef _USED_DIRECTX
			//------------------------------------------------------------------
			//DirectX用のベクトル
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
	//行列を自作
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
			//デコン
			//-------------------------
			__IMPOETER MyMatrix();
			__IMPOETER ~MyMatrix();

		public:
			//-------------------------
			//長さ
			//-------------------------
			__IMPOETER float Length();

			//-------------------------
			//単位化
			//-------------------------
			__IMPOETER MyMatrix& Identity();

			//-------------------------
			//X軸回転
			//-------------------------
			__IMPOETER MyMatrix& RotationX(float rad);

			//-------------------------
			//Y軸回転
			//-------------------------
			__IMPOETER MyMatrix& RotationY(float rad);

			//-------------------------
			//Z軸回転
			//-------------------------
			__IMPOETER MyMatrix& RotationZ(float rad);

			//-------------------------
			//任意軸回転
			//-------------------------
			__IMPOETER MyMatrix& RotationAxis(float rad, Vector3& v);
			__IMPOETER MyMatrix& RotationQuat(float rad, Vector3& v);

			//-------------------------
			//移動
			//-------------------------
			__IMPOETER MyMatrix& Translation(float x, float y, float z);
			__IMPOETER MyMatrix& Translation(Vector3& vec);
			
			//-------------------------
			//拡大・縮小
			//-------------------------
			__IMPOETER MyMatrix& Scale(float x, float y, float z);
			__IMPOETER MyMatrix& Scale(float sc);
			__IMPOETER MyMatrix& Scale(Vector3& v);

			//-------------------------
			//オペレータ
			//(合成、コピー)
			//-------------------------
			__IMPOETER MyMatrix& operator*=(MyMatrix& m);
#ifdef _USED_DIRECTX
			__IMPOETER MyMatrix& operator=(D3DXMATRIX& m);
#endif

			//-------------------------
			//ビューポート行列の生成
			//-------------------------
			__IMPOETER MyMatrix& GetViewPort(int width, int height);

			//-------------------------
			//逆行列
			//-------------------------
			__IMPOETER MyMatrix GetInverse();
			__IMPOETER MyMatrix operator*(MyMatrix& m);
			
			//-------------------------
			//行列から長さを求める
			//-------------------------
			__IMPOETER Vector3 GetPos();

			//----------------------------
			//ベクトルを行列で変形
			//@out :　変換先ベクトル
			//@in : 変換元ベクトル
			//@out : 変換先ベクトル
			//----------------------------
			__IMPOETER Vector4 Transform(Vector4* out, Vector3* in);

			//----------------------------
			//転置行列
			//----------------------------
			MyMatrix& Transposed();

			MyMatrix& ChangePerspective(float fovy, float aspect, float zNear, float zFar);
			MyMatrix& ChangelookAt(const Vector3* eye, const Vector3* tarGet, const Vector3* up);
#ifdef _USED_DIRECTX
			__IMPOETER D3DXMATRIX ChangeMatrixD3D();
#endif
	};

	//クォータニオンクラス
	class MyQuatenion
	{
	public:
		float t;				//実数部
		Vector3 imaginaryNum;	//虚数部

	public:
		//--------------------------------------
		//デコン
		//--------------------------------------
		__IMPOETER MyQuatenion(){}
		__IMPOETER ~MyQuatenion(){}

		//---------------------------------------
		//ゼロ初期化
		//---------------------------------------
		__IMPOETER void ChangeZero();

		//---------------------------------------
		//クォータニオン設定
		//---------------------------------------
		__IMPOETER MyQuatenion& SetQuatenion(float X,float Y,float Z);
		__IMPOETER MyQuatenion& SetQuatenion(MyQuatenion& quat);

		//---------------------------------------
		//単位化
		//---------------------------------------
		__IMPOETER MyQuatenion& Identity();
		
		//---------------------------------------
		//クォータニオン同士の合成
		//---------------------------------------
		//@inout : 出力クォータニオン
		//@in : 合成元１
		//@in : 合成元２
		//@out : 出力クォータニオン
		__IMPOETER MyQuatenion& Dot(MyQuatenion& out, MyQuatenion& a, MyQuatenion& b);

		//---------------------------------------
		//回転クォータニオン
		//---------------------------------------
		//@in : ラジアン角
		//@in : 任意軸Ｘ値
		//@in : 任意軸Ｙ値
		//@in : 任意軸Ｚ値
		//@out : 回転クォータニオン
		__IMPOETER MyQuatenion& RotationQuatenion(float radian, float AxisX, float AxisY, float AxisZ);

		//---------------------------------------
		//クォータニオンから行列を取り出す
		//---------------------------------------
		__IMPOETER MyMatrix& GetMatrix(MyMatrix& out);

		//---------------------------------------
		//行列をクォータニオンで合成
		//---------------------------------------
		//@inout : 出力行列
		//@in : クォータニオン
		//@in : 入力行列
		//@out : 出力行列
		__IMPOETER MyMatrix& RotationQuatanion(MyMatrix& out, MyQuatenion& quat, MyMatrix& in);

		//---------------------------------------
		//オペレータ系をここに
		//---------------------------------------
		__IMPOETER MyQuatenion& operator = (MyQuatenion& quat);
		__IMPOETER MyQuatenion& operator = (const MyQuatenion* quat);
		__IMPOETER MyQuatenion& operator * (MyQuatenion& quat);
		__IMPOETER MyQuatenion& operator * (const MyQuatenion* quat);
	};
}
#endif