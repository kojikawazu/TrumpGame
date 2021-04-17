#pragma once

//-------------------------------------------------------------
//
//自作ベクトルクラスをここに格納
//
//-------------------------------------------------------------
#include <DirectParts.h>
#include <DirectFunction.h>

namespace NanairoLib
{
	//-------------------------------------------------------------
	//スーパーベクトルクラス
	//-------------------------------------------------------------
#pragma region デコンストラクタ
	template<typename T>SuperVector<T>::SuperVector() : x(0){}
		
	template<typename T>SuperVector<T>::SuperVector(T dx) : x(dx){}
		
	template<typename T>SuperVector<T>::~SuperVector()
	{
		this->x = 0;
	}
#pragma endregion

#pragma region インプット
	template<typename T> SuperVector<T>& SuperVector<T>::SetVector(T dx)
	{
		x = dx;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::SetPercentVector(T dx)
	{
		x = SCRW_PERCENT( dx );
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::SetMaxScreen()
	{
		x = SCRW;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::SetMinVector()
	{
		x = 0.0f;
		return *this;
	}

	
	template<typename T> SuperVector<T>& SuperVector<T>::operator = (T in)
	{
		x = in;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator = (SuperVector& in)
	{
		x = in.x;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator = (const SuperVector* in)
	{
		x = in->x;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::ChangeAbs()
	{
		if( x < 0.0f )	x *= -1.0f;
		return *this;
	}
#pragma endregion

#pragma region 加算
	template<typename T> SuperVector<T> SuperVector<T>::operator + (T val)
	{
		SuperVector<T> v;
		v.x = x + val;
		return v;
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator + (SuperVector<T>& val)
	{
		SuperVector<T> v;
		v.x = x + val.x;
		return v;
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator + (const SuperVector<T>* val)
	{
		SuperVector<T> v;
		v.x = x + (*val).x;
		return v;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator += (T val)
	{
		x += val;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator += (SuperVector<T>& val)
	{
		x += val.x;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator += (const SuperVector<T>* val)
	{
		x += (*val).x;
		return *this;
	}
	
	template<typename T> SuperVector<T>& SuperVector<T>::Add(T dx)
	{
		x += dx;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::Add(SuperVector<T>& dx)
	{
		x += dx;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::Add(const SuperVector<T>* dx)
	{
		x += dx;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator--()
	{
		x--;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator ++()
	{
		x++;
		return *this;
	}
	#pragma endregion

#pragma region 減算
	template<typename T> SuperVector<T> SuperVector<T>::operator - ()
	{
		return SuperVector<T>(-x, -y);
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator - (T val)
	{
		SuperVector<T> v;
		v.x = x - val;
		return v;
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator - (SuperVector<T>& val)
	{
		SuperVector<T> v;
		v.x = x - val;
		return v;
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator - (const SuperVector<T>* val)
	{
		SuperVector<T> v;
		v.x = x - val;
		return v;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator -= (T val)
	{
		x -= val;
		y -= val;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator -= (SuperVector<T>& val)
	{
		x -= val;
		y -= val;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator -= (const SuperVector<T>* val)
	{
		x -= val;
		y -= val;
		return *this;
	}
	
	template<typename T> SuperVector<T>& SuperVector<T>::Sub(T dx)
	{
		x -= dx;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::Sub(SuperVector<T>& dx)
	{
		x -= dx;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::Sub(const SuperVector<T>* dx)
	{
		x -= dx;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::SubCut()
	{
		if( x < 0)	x = 0;
		return *this;
	}
#pragma endregion

#pragma region 積算
	template<typename T> SuperVector<T> SuperVector<T>::operator * (T val)
	{
		SuperVector<T> v;
		v.x = x * val;
		return v;
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator * (SuperVector<T>& vec)
	{
		SuperVector<T> out;
		out.x = x * vec.x; 
		return out;
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator * (const SuperVector<T>* vec)
	{
		SuperVector<T> out;
		out.x = x * vec->x; 
		return out;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator *= (T val)
	{
		x *= val;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator *= (SuperVector<T>& val)
	{
		x *= val.x;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator *= (const SuperVector<T>* val)
	{
		x *= val->x;
		return *this;
	}
	#pragma endregion

#pragma region 除算
	template<typename T> SuperVector<T> SuperVector<T>::operator / (T val)
	{
		if( val == 0.0f )	return *this;
		SuperVector<T> v;
		v.x = x / val;
		return v;
	}

	template<typename T> SuperVector<T> SuperVector<T>::operator / (SuperVector<T>& vec)
	{
		if( vec.x == 0.0f )	return *this;
		SuperVector<T> v;
		v.x = x / vec.x;
		return v;
	}
	
	template<typename T> SuperVector<T> SuperVector<T>::operator / (const SuperVector<T>* vec)
	{
		if( vec->x == 0.0f )	return *this;
		SuperVector<T> v;
		v.x = x / vec->x;
		return v;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator /= (T val)
	{
		if( val == 0.0f )	return *this;
		x /= val;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator /= (SuperVector<T>& val)
	{
		if( val.x == 0.0f )	return *this;
		x /= val.x;
		return *this;
	}

	template<typename T> SuperVector<T>& SuperVector<T>::operator /= (const SuperVector<T>* val)
	{
		if( val->x == 0.0f )	return *this;
		x /= val->x;
		return *this;
	}
	#pragma endregion

#pragma region 長さ
	template<typename T> float SuperVector<T>::Length()
	{
		return sqrt( x * x );
	}

	template<typename T> float SuperVector<T>::LengthSquare()
	{
		return ( x * x );	
	}
#pragma endregion

	//---------------------------------------------------------
	//単位化
	//---------------------------------------------------------
	template<typename T> SuperVector<T>& SuperVector<T>::Normalize()
	{
		float len = this->Length();
		x /= len;
		return *this;
	}

	//---------------------------------------------------------------------------
	//3次元ベクトルメソッドをここに
	//---------------------------------------------------------------------------
	Vector3::Vector3() : x(0), y(0), z(0){}
	Vector3::Vector3(float dx, float dy, float dz) : x(dx), y(dy), z(dz){}	
	Vector3::~Vector3(){}

	//-------------------------------------------------------------------
	//ベクトルや値を代入させる
	//-------------------------------------------------------------------
	Vector3& Vector3::SetVector(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
		return *this;
	}

	Vector3& Vector3::SetVector(Vector3& vec)
	{
		x= vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}
	
	Vector3& Vector3::SetVector(const Vector3* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		return *this;
	}

	//-------------------------------------------------------------
	//自らベクトル代入
	//-------------------------------------------------------------------
	#pragma region 代入
	Vector3& Vector3::operator = (float val)
	{
		x = val;
		y = val;
		z = val;
		return *this;
	}

	Vector3& Vector3::operator = (Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	Vector3& Vector3::operator = (const Vector3* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		return *this;
	}

	Vector3& Vector3::operator = (Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector3& Vector3::operator = (const Vector2* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector3& Vector3::operator = (Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& Vector3::operator = (const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		return *this;
	}
	#pragma endregion

	//-----------------------------------------------------
	//型キャスト
	//-----------------------------------------------------
	Vector3::operator Vector3&()
	{
		return *this;
	}

	//-----------------------------------------------------
	//加算
	//-----------------------------------------------------
	#pragma region 加算
	Vector3 Vector3::operator + (float val)
	{
		Vector3 v;
		v.x = x + val;
		v.y = y + val;
		v.z = z + val;
		return v;
	}
	Vector3 Vector3::operator + (Vector3& vec)
	{
		Vector3 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		return v;
	}

	Vector3 Vector3::operator + (const Vector3& vec)
	{
		Vector3 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		return v;
	}

	Vector3 Vector3::operator + (Vector2& vec)
	{
		Vector3 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		return v;
	}

	Vector3 Vector3::operator + (const Vector2* vec)
	{
		Vector3 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		return v;
	}

	Vector3 Vector3::operator + (Vector4& vec)
	{
		Vector3 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		return v;
	}

	Vector3 Vector3::operator + (const Vector4* vec)
	{
		Vector3 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		v.z = z + vec->z;
		return v;
	}

	Vector3& Vector3::operator += (float val)
	{
		x += val;
		y += val;
		z += val;
		return *this;
	}

	Vector3& Vector3::operator += (Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& Vector3::operator += (const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& Vector3::operator += (Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector3& Vector3::operator += (const Vector2* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector3& Vector3::operator += (Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& Vector3::operator += (const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		return *this;
	}

	Vector3& Vector3::Add(float dx, float dy, float dz)
	{
		x += dx;
		y += dy;
		z += dz;
		return *this;
	}

	Vector3& Vector3::Add(Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& Vector3::Add(const Vector3* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		return *this;
	}

	Vector3& Vector3::Add(Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector3& Vector3::Add(const Vector2* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector3& Vector3::Add(Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& Vector3::Add(const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		return *this;
	}
	#pragma endregion

	//---------------------------------------------------------
	//減算
	//---------------------------------------------------------
	#pragma region 減算
	Vector3& Vector3::operator - ()
	{
		return Vector3(-x,-y,-z);
	}

	Vector3 Vector3::operator - (float val)
	{
		Vector3 vec;
		vec.x = x - val;
		vec.y = y - val;
		vec.z = z - val;
		return vec;
	}

	Vector3 Vector3::operator - (Vector3& vec)
	{
		Vector3 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		return v;
	}

	Vector3 Vector3::operator - (const Vector3& vec)
	{
		Vector3 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		return v;
	}

	Vector3 Vector3::operator - (const Vector3* vec)
	{
		Vector3 v;
		v.x = x - vec->x;
		v.y = y - vec->y;
		v.z = z - vec->z;
		return v;
	}

	Vector3 Vector3::operator - (Vector2& vec)
	{
		Vector3 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		return v;
	}

	Vector3 Vector3::operator - (const Vector2* vec)
	{
		Vector3 v;
		v.x = x - vec->x;
		v.y = y - vec->y;
		return v;
	}

	Vector3 Vector3::operator - (Vector4& vec)
	{
		Vector3 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		return v;
	}

	Vector3 Vector3::operator - (const Vector4* vec)
	{
		Vector3 v;
		v.x = x - vec->x;
		v.y = y - vec->y;
		v.z = z - vec->z;
		return v;
	}

	Vector3& Vector3::operator -= (float val)
	{
		x -= val;
		y -= val;
		z -= val;
		return *this;
	}

	Vector3&Vector3:: operator -= (Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	
	Vector3& Vector3::operator -= (const Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector3&Vector3:: operator -= (Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	
	Vector3& Vector3::operator -= (const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector3&Vector3:: operator -= (Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	
	Vector3& Vector3::operator -= (const Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector3& Vector3::Sub(float dx,float dy, float dz)
	{
		x -= dx;
		y -= dy;
		z -= dz;
		return *this;
	}

	Vector3& Vector3::Sub(Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector3& Vector3::Sub(const Vector3* vec)
	{
		x -= vec->x;
		y -= vec->y;
		z -= vec->z;
		return *this;
	}

	Vector3& Vector3::Sub(Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector3& Vector3::Sub(const Vector2* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}

	Vector3& Vector3::Sub(Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector3& Vector3::Sub(const Vector4* vec)
	{
		x -= vec->x;
		y -= vec->y;
		z -= vec->z;
		return *this;
	}
	#pragma endregion

	//---------------------------------------------------------
	//積算
	//---------------------------------------------------------
	#pragma region 積算
	Vector3 Vector3::operator * (float val)
	{
		Vector3 v;
		v.x = x * val;
		v.y = y * val;
		v.z = z * val;
		return v;
	}

	Vector3& Vector3::operator *= (float val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	float Vector3::operator * (Vector3& vec)
	{
		return ( x * vec.x + y * vec.y + z * vec.z );
	}

	float Vector3::operator * (const Vector3* vec)
	{
		return ( x * vec->x + y * vec->y + z * vec->z );
	}
	#pragma endregion

	//---------------------------------------------------------
	//除算
	//---------------------------------------------------------
	#pragma region 除算
	Vector3 Vector3::operator / (float val)
	{
		if( val == 0 )	
			return *this;
		Vector3 v;
		v.x = x / val;
		v.y = y / val;
		v.z = z / val;
		return v;
	}
	
	Vector3& Vector3::operator /= (float val)
	{
		if( val == 0)
			return *this;
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	Vector3 Vector3::operator / (Vector3& vec)
	{
		Vector3 v = *this;
		VectorFunc func;
		v = func.GetCloss( v, vec );
		return v;
	}

	Vector3 Vector3::operator / (PCVector3 vec)
	{
		Vector3 v = *this;
		VectorFunc func;
		v = func.GetCloss( v, *vec );
		return v;
	}
	#pragma endregion

	//---------------------------------------------------------
	//長さ
	//---------------------------------------------------------
	float Vector3::Length()
	{
		return sqrt( x * x + y * y + z * z );
	}

	float Vector3::LengthSquare()
	{
		return ( x * x + y * y + z * z );	
	}

	//---------------------------------------------------------
	//単位化
	//---------------------------------------------------------
	Vector3& Vector3::Normalize()
	{
		float len = this->Length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}
	
	//---------------------------------------------------------
	//ベクトルの内積
	//---------------------------------------------------------
	float Vector3::Dot( Vector3& vec )
	{
		return ( x * vec.x + y * vec.y + z * vec.z );
	}
	
	//---------------------------------------------------------
	//ベクトルの外積
	//---------------------------------------------------------
	Vector3 Vector3::Closs(Vector3& vec)
	{
		return Vector3( ( y * vec.z - vec.y * z ), 
						( z * vec.x - vec.z * x ),
						( x * vec.y - vec.x * y ) );
	}
	
	//---------------------------------------------------------
	//2か所だけ変えたい時用
	#pragma region 部分代入
	Vector3& Vector3::SetVectorXY(float dx, float dy)
	{
		x = dx;
		y = dy;
		return *this;
	}
	Vector3& Vector3::SetVectorXZ(float dx, float dz)
	{
		x = dx;
		z = dz;
		return *this;
	}

	void Vector3::Scaling(float abs)
	{
		x *= abs;
		y *= abs;
		z *= abs;
	}
	#pragma endregion

	//---------------------------------------------------------------//
	///////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------//
	//2次元用ベクトルをここに
	Vector2::Vector2() : x(0), y(0){}
	Vector2::Vector2(float dx, float dy) : x(dx), y(dy){}
	Vector2::~Vector2(){}

	//---------------------------------------------------------------
	//Setter
	//---------------------------------------------------------------
	#pragma region Setter
	Vector2& Vector2::SetVector(float dx, float dy)
	{
		x = dx;
		y = dy;
		return *this;
	}

	Vector2& Vector2::SetPercentVector(float dx, float dy)
	{
		x = SCRW_PERCENT( dx );
		y = SCRH_PERCENT( dy );
		return *this;
	}

	Vector2& Vector2::SetMaxScreen()
	{
		x = SCRW;
		y = SCRH;
		return *this;
	}

	Vector2& Vector2::SetMinVector()
	{
		x = 0.0f;
		y = 0.0f;
		return *this;
	}

	Vector2& Vector2::SetVector(Vector2& vec)
	{
		x= vec.x;
		y = vec.y;
		return *this;
	}
	
	Vector2& Vector2::SetVector(const Vector2* vec)
	{
		x = vec->x;
		y = vec->y;
		return *this;
	}

	Vector2& Vector2::SetVectorXY(Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	Vector2& Vector2::SetVectorYZ(Vector3& vec)
	{
		x = vec.y;
		y = vec.z;
		return *this;
	}
	
	Vector2& Vector2::SetVectorZX(Vector3& vec)
	{
		x = vec.z;
		y = vec.x;
		return *this;
	}
	#pragma endregion

	//------------------------------------------------------------------
	//代入
	//------------------------------------------------------------------
	#pragma region 代入
	Vector2& Vector2::operator = (float val)
	{
		x = val;
		y = val;
		return *this;
	}

	Vector2& Vector2::ChangeAbs()
	{
		if( x < 0.0f )	x *= -1.0f;
		if( y < 0.0f )	y *= -1.0f;
		return *this;
	}
	
	Vector2& Vector2::operator = (Vector2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	Vector2& Vector2::operator = (const Vector2* vec)
	{
		x = vec->x;
		y = vec->y;
		return *this;
	}
	

	Vector2& Vector2::operator = (Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	Vector2& Vector2::operator = (const Vector3* vec)
	{
		x = vec->x;
		y = vec->y;
		return *this;
	}

	Vector2& Vector2::operator = (Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2& Vector2::operator = (const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	#pragma endregion

	//------------------------------------------------------------------
	//型キャスト
	//------------------------------------------------------------------
	Vector2::operator Vector2&()
	{
		return *this;
	}

	//------------------------------------------------------------------
	//加算
	//------------------------------------------------------------------
	#pragma region 加算
	Vector2 Vector2::operator + (float val)
	{
		Vector2 v;
		v.x = x + val;
		v.y = y + val;
		return v;
	}
	
	Vector2 Vector2::operator + (Vector2& vec)
	{
		Vector2 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		return v;
	}

	Vector2 Vector2::operator + (const Vector2& vec)
	{
		Vector2 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		return v;
	}

	Vector2 Vector2::operator + (const Vector2* vec)
	{
		Vector2 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		return v;
	}

	Vector2 Vector2::operator + (Vector3& vec)
	{
		Vector2 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		return v;
	}

	Vector2 Vector2::operator + (const Vector3* vec)
	{
		Vector2 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		return v;
	}

	Vector2 Vector2::operator + (Vector4& vec)
	{
		Vector2 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		return v;
	}

	Vector2 Vector2::operator + (const Vector4* vec)
	{
		Vector2 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		return v;
	}

	Vector2& Vector2::operator += (Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	
	Vector2& Vector2::operator += (const Vector2* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector2& Vector2::operator += (Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	
	Vector2& Vector2::operator += (const Vector3* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}
	
	Vector2& Vector2::operator += (Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	
	Vector2& Vector2::operator += (const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}
	
	Vector2& Vector2::Add(float dx, float dy)
	{
		x += dx;
		y += dy;
		return *this;
	}

	Vector2& Vector2::Add(Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2& Vector2::Add(const Vector2* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector2& Vector2::Add(Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2& Vector2::Add(const Vector3* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector2& Vector2::Add(Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2& Vector2::Add(const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}
	#pragma endregion

	//------------------------------------------------------------------
	//減算
	//------------------------------------------------------------------
	#pragma region 減算
	Vector2 Vector2::operator - ()
	{
		return Vector2(-x, -y);
	}

	Vector2 Vector2::operator - (float val)
	{
		Vector2 v;
		v.x = x - val;
		v.y = y - val;
		return v;
	}
	
	Vector2 Vector2::operator - (Vector2& vec)
	{
		Vector2 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		return v;
	}
	
	Vector2 Vector2::operator - (const Vector2& vec)
	{
		Vector2 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		return v;
	}

	Vector2 Vector2::operator - (const Vector2* vec)
	{
		Vector2 v;
		v.x = x - vec->x;
		v.y = y - vec->y;
		return v;
	}

	Vector2& Vector2::operator -= (float val)
	{
		x -= val;
		y -= val;
		return *this;
	}

	Vector2& Vector2::operator -= (Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::operator -= (const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::operator -= (const Vector2* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}

	Vector2& Vector2::operator -= (Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::operator -= (const Vector3* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}

	Vector2& Vector2::operator -= (Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::operator -= (const Vector4* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}
	
	Vector2& Vector2::Sub(float dx,float dy)
	{
		x -= dx;
		y -= dy;
		return *this;
	}

	Vector2& Vector2::Sub(Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::Sub(const Vector2* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}

	Vector2& Vector2::Sub(Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::Sub(const Vector3* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}

	Vector2& Vector2::Sub(Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::Sub(const Vector4* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}

	Vector2& Vector2::SubCut()
	{
		if( x < 0.0f)	x = 0.0f;
		if( y < 0.0f)	y = 0.0f;
		return *this;
	}
	#pragma endregion

	//------------------------------------------------------------------
	//普通の積算
	//------------------------------------------------------------------
	#pragma region 積算
	Vector2 Vector2::operator * (float val)
	{
		Vector2 v;
		v.x = x * val;
		v.y = y * val;
		return v;
	}

	Vector2& Vector2::operator *= (float val)
	{
		x *= val;
		y *= val;
		return *this;
	}

	float Vector2::operator * (Vector2& vec)
	{
		return ( x * vec.x + y * vec.y );
	}

	float Vector2::operator * (const Vector2* vec)
	{
		return ( x * vec->x + y * vec->y );
	}
	#pragma endregion

	//------------------------------------------------------------------
	//除算
	//------------------------------------------------------------------
	#pragma region 除算
	Vector2 Vector2::operator / (float val)
	{
		if( val == 0.0f ) 
			return *this;
		Vector2 v;
		v.x = x / val;
		v.y = y / val;
		return v;
	}
	Vector2& Vector2::operator /= (float val)
	{
		if( val == 0.0f ) 
			return *this;
		x /= val;
		y /= val;
		return *this;
	}

	float Vector2::operator / (Vector2& vec)
	{
		return ( x * vec.y - vec.x * y );
	}
	
	float Vector2::operator / (const Vector2* vec)
	{
		return ( x * vec->y - vec->x * y );
	}
	#pragma endregion

	//------------------------------------------------------------------
	//ベクトルの長さ
	//------------------------------------------------------------------
	float Vector2::Length()
	{
		return (x * x + y * y);
	}

	//------------------------------------------------------------------
	//ベクトルの長さの二乗
	//------------------------------------------------------------------
	float Vector2::LengthSquare()
	{
		return sqrt(x * x + y * y);
	}
	
	//------------------------------------------------------------------
	//ベクトルの単位化
	//------------------------------------------------------------------
	Vector2& Vector2::Normalize()
	{
		float len = this->Length();
		x /= len;
		y /= len;
		return *this;
	}

	//------------------------------------------------------------------
	//ベクトルの内積
	//------------------------------------------------------------------
	float Vector2::Dot(Vector2& vec)
	{
		return (x * vec.x + y * vec.y);
	}
	
	//------------------------------------------------------------------
	//ベクトルの外積
	//------------------------------------------------------------------
	float Vector2::Closs(Vector2& vec)
	{
		return (x * vec.y - vec.x * y);
	}

	//------------------------------------------------------------------

	//---------------------------------------------------------------//
	///////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------//
	//4次元用ベクトルをここに
	Vector4::Vector4() : x(0), y(0), z(0), w(0){}
	Vector4::Vector4(float dx, float dy,float dz,float dw) : x(dx), y(dy), z(dz), w(dw){}
	Vector4::~Vector4(){}

	//------------------------------------------------------------------
	//代入
	//------------------------------------------------------------------
	Vector4& Vector4::SetVector(float dx, float dy,float dz,float dw)
	{
		x = dx;
		y = dy;
		z = dz;
		w = dw;
		return *this;
	}

	Vector4& Vector4::SetVector(Vector4& vec)
	{
		x= vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		return *this;
	}
	
	Vector4& Vector4::SetVector(const Vector4* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		w = vec->w;
		return *this;
	}

	Vector4& Vector4::ChangeAbs()
	{
		if( x < 0.0f )	x *= -1.0f;
		if( y < 0.0f )	y *= -1.0f;
		if( z < 0.0f )	z *= -1.0f;
		if( w < 0.0f )	w *= -1.0f;
		return *this;
	}
	
	Vector4& Vector4::operator = (Vector4& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		return *this;
	}

	Vector4& Vector4::operator = (const Vector4* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		w = vec->w;
		return *this;
	}

	//------------------------------------------------------------------
	//型キャスト
	//------------------------------------------------------------------
	Vector4::operator Vector4&()
	{
		return *this;
	}
	

	//------------------------------------------------------------------
	//加算
	//------------------------------------------------------------------
	#pragma region 加算
	Vector4 Vector4::operator + (float val)
	{
		Vector4 v;
		v.x = x + val;
		v.y = y + val;
		v.z = z + val;
		v.w = w + val;
		return v;
	}
	
	Vector4 Vector4::operator + (Vector4& vec)
	{
		Vector4 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		v.w = w + vec.w;
		return v;
	}

	Vector4 Vector4::operator + (const Vector4& vec)
	{
		Vector4 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		v.w = w + vec.w;
		return v;
	}

	Vector4 Vector4::operator + (const Vector4* vec)
	{
		Vector4 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		v.z = z + vec->z;
		v.w = w + vec->w;
		return v;
	}

	Vector4 Vector4::operator + (Vector2& vec)
	{
		Vector4 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		return v;
	}

	Vector4 Vector4::operator + (const Vector2* vec)
	{
		Vector4 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		return v;
	}

	Vector4 Vector4::operator + (Vector3& vec)
	{
		Vector4 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		return v;
	}

	Vector4 Vector4::operator + (const Vector3* vec)
	{
		Vector4 v;
		v.x = x + vec->x;
		v.y = y + vec->y;
		v.z = z + vec->z;
		return v;
	}

	Vector4& Vector4::operator += (float val)
	{
		x += val;
		y += val;
		z += val;
		w += val;
		return *this;
	}

	Vector4& Vector4::operator += (Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}
	
	Vector4& Vector4::operator += (const Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}

	Vector4& Vector4::operator += (const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		w += vec->w;
		return *this;
	}
	
	Vector4& Vector4::operator += (Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector4& Vector4::operator += (const Vector2* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector4& Vector4::operator += (Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector4& Vector4::operator += (const Vector3* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		return *this;
	}

	Vector4& Vector4::Add(float dx, float dy,float dz,float dw)
	{
		x += dx;
		y += dy;
		z += dz;
		w += dw;
		return *this;
	}

	Vector4& Vector4::Add(Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}

	Vector4& Vector4::Add(const Vector4* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		w += vec->w;
		return *this;
	}

	Vector4& Vector4::Add(Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector4& Vector4::Add(const Vector2* vec)
	{
		x += vec->x;
		y += vec->y;
		return *this;
	}

	Vector4& Vector4::Add(Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector4& Vector4::Add(const Vector3* vec)
	{
		x += vec->x;
		y += vec->y;
		z += vec->z;
		return *this;
	}
	#pragma endregion

	//------------------------------------------------------------------
	//減算
	//------------------------------------------------------------------
	#pragma region 減算
	Vector4 Vector4::operator - ()
	{
		return Vector4(-x, -y, -z, -w);
	}

	Vector4 Vector4::operator - (float val)
	{
		Vector4 v;
		v.x = x - val;
		v.y = y - val;
		v.z = z - val;
		v.w = w - val;
		return v;
	}
	
	Vector4 Vector4::operator - (Vector4& vec)
	{
		Vector4 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		v.w = w - vec.w;
		return v;
	}
	
	Vector4 Vector4::operator - (const Vector4& vec)
	{
		Vector4 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		v.w = w - vec.w;
		return v;
	}

	Vector4 Vector4::operator - (const Vector4* vec)
	{
		Vector4 v;
		v.x = x - vec->x;
		v.y = y - vec->y;
		v.z = z - vec->z;
		v.w = w - vec->w;
		return v;
	}

	Vector4 Vector4::operator - (Vector2& vec)
	{
		Vector4 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		return v;
	}

	Vector4 Vector4::operator - (const Vector2* vec)
	{
		Vector4 v;
		v.x = x - vec->x;
		v.y = y - vec->y;
		return v;
	}

	Vector4 Vector4::operator - (Vector3& vec)
	{
		Vector4 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		return v;
	}

	Vector4 Vector4::operator - (const Vector3* vec)
	{
		Vector4 v;
		v.x = x - vec->x;
		v.y = y - vec->y;
		v.z = z - vec->z;
		return v;
	}

	Vector4& Vector4::operator -= (float val)
	{
		x -= val;
		y -= val;
		z -= val;
		w -= val;
		return *this;
	}

	Vector4& Vector4::operator -= (Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}

	Vector4& Vector4::operator -= (const Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}

	Vector4& Vector4::operator -= (const Vector4* vec)
	{
		x -= vec->x;
		y -= vec->y;
		z -= vec->z;
		w -= vec->w;
		return *this;
	}

	Vector4& Vector4::operator -= (Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector4& Vector4::operator -= (const Vector2* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}

	Vector4& Vector4::operator -= (Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector4& Vector4::operator -= (const Vector3* vec)
	{
		x -= vec->x;
		y -= vec->y;
		z -= vec->z;
		return *this;
	}
	
	Vector4& Vector4::Sub(float dx,float dy,float dz,float dw)
	{
		x -= dx;
		y -= dy;
		z -= dz;
		w -= dw;
		return *this;
	}

	Vector4& Vector4::Sub(Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}

	Vector4& Vector4::Sub(const Vector4* vec)
	{
		x -= vec->x;
		y -= vec->y;
		z -= vec->z;
		w -= vec->w;
		return *this;
	}

	Vector4& Vector4::Sub(Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector4& Vector4::Sub(const Vector3* vec)
	{
		x -= vec->x;
		y -= vec->y;
		z -= vec->z;
		return *this;
	}

	Vector4& Vector4::Sub(Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector4& Vector4::Sub(const Vector2* vec)
	{
		x -= vec->x;
		y -= vec->y;
		return *this;
	}
	#pragma endregion

	//------------------------------------------------------------------
	//普通の積算
	//------------------------------------------------------------------
	#pragma region 積算
	Vector4 Vector4::operator * (float val)
	{
		Vector4 v;
		v.x = x * val;
		v.y = y * val;
		v.z = z * val;
		v.w = w * val;
		return v;
	}

	Vector4& Vector4::operator *= (float val)
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}
	#pragma endregion

	//------------------------------------------------------------------
	//普通の除算
	//------------------------------------------------------------------
	#pragma region 除算
	Vector4 Vector4::operator / (float val)
	{
		if( val == 0.0f ) 
			return *this;

		Vector4 v;
		v.x = x / val;
		v.y = y / val;
		v.z = z / val;
		v.w = w / val;
		return v;
	}
	Vector4& Vector4::operator /= (float val)
	{
		if( val == 0.0f ) 
			return *this;
		x /= val;
		y /= val;
		z /= val;
		w /= val;
		return *this;
	}
	#pragma endregion

	//------------------------------------------------------------------
	//ベクトルの長さ
	//------------------------------------------------------------------
	float Vector4::Length()
	{
		return (x * x + y * y + z * z + w * w);
	}
	//------------------------------------------------------------------
	//ベクトルの長さの二乗
	//------------------------------------------------------------------
	float Vector4::LengthSquare()
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}
	
	//------------------------------------------------------------------
	//ベクトルの単位化
	//------------------------------------------------------------------
	Vector4& Vector4::Normalize()
	{
		float len = this->Length();
		x /= len;
		y /= len;
		z /= len;
		w /= len;
		return *this;
	}

	//------------------------------------------------------------------
#ifdef _USED_DIRECTX 
	//-------------------------------------------------------------------
	Vector3::Vector3(VECTOR3& vec) : x(vec.x), y(vec.y), z(vec.z){}
	Vector3& Vector3::operator = (const VECTOR3 vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}
	VECTOR3 Vector3::SetD3DVector3()
	{
		return D3DXVECTOR3( x, y, z );
	}
	Vector3& Vector3::SetVector(VECTOR3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}
	//オペレータでD3DXVECTOR3のベクトルから代入させる
	Vector3& Vector3::operator = (VECTOR3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	Vector3& Vector3::operator = (const VECTOR3* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		return *this;
	}
	Vector3& Vector3::operator = (VECTOR3* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		return *this;
	}
	Vector3 Vector3::operator + (VECTOR3& vec)
	{
		Vector3 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		return v;
	}
	Vector3 Vector3::operator - (VECTOR3& vec)
	{
		Vector3 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		return v;
	}

	//DirectX用ベクトルを使用したとき
	Vector2::Vector2(VECTOR2& vec)
	{
		x = vec.x;
		y = vec.y;
	}
	VECTOR2 Vector2::SetD3DVector2()
	{
		return VECTOR2(x,y); 
	}

	Vector2& Vector2::SetVector(VECTOR2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}
	Vector2& Vector2::operator = (VECTOR2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}
	Vector2& Vector2::operator = (const VECTOR2* vec)
	{
		x = vec->x;
		y = vec->y;
		return *this;
	}
	Vector2& Vector2::operator = (VECTOR2* vec)
	{
		x = vec->x;
		y = vec->y;
		return *this;
	}
	Vector2 Vector2::operator + (VECTOR2& vec)
	{
		Vector2 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		return v;
	}
	Vector2 Vector2::operator - (VECTOR2& vec)
	{
		Vector2 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		return v;
	}

	//-----------------------------------------
	//DirectX用ベクトルを使用したとき
	//-----------------------------------------
	Vector4::Vector4(VECTOR4& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}
	VECTOR4 Vector4::SetD3DVector4()
	{
		return VECTOR4(x,y,z,w); 
	}

	Vector4& Vector4::SetVector(VECTOR4& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		return *this;
	}
	Vector4& Vector4::operator = (VECTOR4& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		return *this;
	}
	Vector4& Vector4::operator = (const VECTOR4* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		w = vec->w;
		return *this;
	}
	Vector4& Vector4::operator = (VECTOR4* vec)
	{
		x = vec->x;
		y = vec->y;
		z = vec->z;
		w = vec->w;
		return *this;
	}
	Vector4 Vector4::operator + (VECTOR4& vec)
	{
		Vector4 v;
		v.x = x + vec.x;
		v.y = y + vec.y;
		v.z = z + vec.z;
		v.w = w + vec.w;
		return v;
	}
	Vector4 Vector4::operator - (VECTOR4& vec)
	{
		Vector4 v;
		v.x = x - vec.x;
		v.y = y - vec.y;
		v.z = z - vec.z;
		v.w = w - vec.w;
		return v;
	}
#endif

}
