#pragma once
//----------------------------------------------------------------------
//
//ベクトル変換や様々な計算類を目的としたメソッドをここにおいてます
//
//----------------------------------------------------------------------
#include <DirectFunction.h>

namespace NanairoLib
{
	//-------------------------------------------------------
	//小さいか判定(Aを対象に、Ｂから大きいか)
	//-------------------------------------------------------
	//@in : 対象A 
	//@in : 対象B
	//@out :  大きい ? (true) : (false)
	bool VectorFunc::Min_hantei(float checkA,float checkB)
	{
		return (checkA < checkB);
	}
	
	//-------------------------------------------------------------
	//3次元ベクトルを2次元に
	//-------------------------------------------------------------
	//@in :	対象ベクトル
	//@out : 角軸による2次元ベクトルに変換させる
	#pragma region ３次元ベクトルを２次元に
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
	//始点から終点を引いた距離ベクトル
	//--------------------------------------------------------------
	//@in : 始点 
	//@in : 終点
	//@out : 出来上がった距離ベクトル
	#pragma region 始点から終点を引いた距離ベクトル
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
	//距離を求める
	//-------------------------------------------
	//@in : 対象
	//@out : 距離
	#pragma region 距離を求める
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
	//ベクトルの大きさ
	//--------------------------------------------------------------
	//@in : 対象のベクトル
	//@out : 角値の大きさ
	#pragma region ベクトルの大きさ
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
	//ベクトルの法線ベクトル
	//--------------------------------------------------------------
	//@in : 対象ベクトル,又は始点ベクトル
	//@in : もしくは終点ベクトル
	//@out : 法線ベクトル（単位かした状態で）
	#pragma region ３次元ベクトルの法線
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
	//ベクトルの内積
	//--------------------------------------------------------------
	//@in : 対象ベクトル１
	//@in : 対象ベクトル２
	//@out : 内積
	#pragma region 内積
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
	//ベクトルの外積
	//--------------------------------------------------------------
	//@in : 対象ベクトル１
	//@in : 対象ベクトル２
	//@out	: 2D → 外積
	//		: 3D → 法線ベクトル
	#pragma region 外積
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
	//行列の進行
	//------------------------------------------------------------------
	//@in : 掛け合わせる行列
	//@in : 移動ベクトル
	//@out : 変換行列
	D3DXMATRIXA16 VectorFunc::GetTransMat(const D3DXMATRIXA16 *mat,RCVector3 vec)
	{
		D3DXMATRIXA16 temp;
		D3DXMatrixTranslation(&temp,vec.x,vec.y,vec.z);
		return (*mat) * (temp);
	}

	//---------------------------------------------------------------------------
	//行列の回転(アフィン変換)
	//---------------------------------------------------------------------------
	//@in : 対象行列
	//@in : 原点へ戻すベクトル
	//@in : 回転角度
	//@out : 各軸での変換行列
	#pragma region 行列の回転
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
	//クォータニオンワールド座標変換
	//----------------------------------------------------------------------------------------------------
	//@posi(位置) @scale(拡大率) @rotavec(任意軸) @ang(回転角度)
	//戻	: すべてを掛け合わせた行列
	D3DXMATRIX VectorFunc::SetworldQuaternion(RCVector3 posi,RCVector3 scale,RCVector3 rotavec,float ang)
	{
		return (*::D3DXMatrixTransformation(NULL, NULL, NULL, &((Vector3&)scale).SetD3DVector3(), NULL, &this->GetQuaternion(rotavec, ang), &((Vector3&)posi).SetD3DVector3()));
	}
	
	//-----------------------------------------------------------------
	//クォータニオン変換
	//-----------------------------------------------------------------
	//@in : 任意軸 
	//@in : 回転角度
	//@out : クォータニオン行列
	D3DXQUATERNION VectorFunc::GetQuaternion(RCVector3 rota,float ang)
	{
		return (*::D3DXQuaternionRotationAxis(NULL, &((Vector3&)rota).SetD3DVector3(), ang));
	}
#endif

	//-------------------------------------------------------------
	//角度のラジアン角を求める
	//-------------------------------------------------------------
	//0(普通の角度) 1(cosθ) 2(sinθ) 3(tanθ)
	//@out : ラジアン角
	#pragma region 角度のラジアン角を出す
	//ラジアン角を求める
	float VectorFunc::ChangeRad(float cosA,int _angle_number)
	{
		float ang = 0.0f;
		switch(_angle_number + 1)
		{
			case _ANGLE_RAD:	//普通の角度変換
				ang = SET_PI(cosA);	break;
			case _RAD_COS:	//cosθがきた場合
				ang = acos(cosA);	break;
			case _RAD_SIN:	//sinθがきた場合
				ang = asin(cosA);	break;
			case _RAD_TAN:	//tanθがきた場合
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
	//ラジアンから角度を求める
	//--------------------------------------------------------------
	//0(普通の角度) 1(cosθ) 2(sinθ) 3(tanθ)
	//@out : 角度
	#pragma region 角度を求める
	//普通の角度を求める
	float VectorFunc::ChangeAngle(float cosA,int _angle_number)
	{
		float ang = 0.0f;
		switch(_angle_number + 1)
		{
		case _ANGLE_RAD:	//普通の角度変換
			ang = BACK_PI(cosA);
			break;
		case _RAD_COS:	//cosθがきた場合
			ang = BACK_PI(acos(cosA));
			break;
		case _RAD_SIN:	//sinθがきた場合
			ang = BACK_PI(asin(cosA));
			break;
		case _RAD_TAN:	//tanθがきた場合
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
	//ベクトルから角度を求める
	//-------------------------------------------------------------
	//@in : 求めたいベクトル
	//@out : 角度
	float VectorFunc::GetAngleAtan2(RCVector2 st, RCVector2 end)
	{
		//ラジアンから度に変換してから返す
		return this->ChangeAngleAtan2( st, end );
	}

	//------------------------------------------------
	//ベクトルから角度を求める
	//------------------------------------------------
	//@in : 求めたいベクトル
	//@out : 角度
	float VectorFunc::GetVectorOfAngleY(RCVector3 vec)
	{
		return this->ChangeAngleAtan2( vec.x, vec.z );
	}
	
	//-----------------------------------------------------------------
	//2点からベクトルを求め角度を求める
	//-----------------------------------------------------------------
	//@in : 始点ベクトル
	//@in : 終点ベクトル
	//@out : 角度
	float VectorFunc::GetVectorOfAngleY(RCVector3 vecontrolA,RCVector3 vecontrolB)
	{
		return this->ChangeAngleAtan2XZ( vecontrolA, vecontrolB );
	}

	//----------------------------------------------------------------------------------------------------
	//4点から2つのベクトルを求め、角度を求める
	//----------------------------------------------------------------------------------------------------
	//@in : ベクトルＡの始点
	//@in : ベクトルＡの終点
	//@in : ベクトルＢの始点
	//@in : ベクトルＢの終点
	//@out : 角度
	float VectorFunc::GetVectorOfAngleY(RCVector3 vecontrolA1,RCVector3 vecontrolA2,RCVector3 vecontrolB1,RCVector3 vecontrolB2)
	{
		return this->ChangeAngle( this->GetDot( this->GetVectorXZ( vecontrolA1, vecontrolA2 ).Normalize(), this->GetVectorXZ( vecontrolB1, vecontrolB2 ).Normalize() ) , _RAD_COS );
	}

	//------------------------------------------
	//絶対値を求める
	//------------------------------------------
	//@in : 対象
	//@out : 絶対値
	#pragma region 絶対値変換
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
	//次にいく方向ベクトルを求める
	//------------------------------------------------------------------------------------------
	//@in : 次のポイント 
	//@in : 前のポイント 
	//@out : 移動ベクトル
	//@out : 移動距離
	//@out : true(成功) false(失敗)
	bool VectorFunc::SetNextPointVector(RCVector3 point,RCVector3 oldpos,Vector3 *anspos,float *dis)
	{
		//ある地点までの距離を求める
		Vector3 pos = (Vector3)(point) - (oldpos);
		(*dis) = GetVecDistanceLong(pos);
		(*anspos) = GetNormal(pos);
		return true;
	}

	//------------------------------------------------------------------------------
	//方向ベクトルの進む角度を求める
	//------------------------------------------------------------------------------
	//@in : 始点 
	//@in : 終点 
	//@in : 対象角度
	//@out : 現在のベクトルからの角度の差を返す
	#pragma region 角度チェンジ角度の取得
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
	//角度チェンジ
	//--------------------------------------------------------------------------------
	//@in : 現在のベクトル
	//@in : 回転角度
	//@in : true(回転する)　false(回転しない)
	//@out : 回転したベクトル
	#pragma region ベクトルの回転
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
	//向き判定
	//----------------------------------------------------------------------------------
	//@in : ベクトルA
	//@in : ベクトルB
	//@in : 角度の大きさ 
	//@out : angより○○だったら保存
	//@in : 1(cos) 2(sin) 
	//@in : 1(大きいを狙うか) 2(小さいを狙うか)
	//@out : true(成功) false(失敗)
	#pragma region 向き判定
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
			case _CK_BIG:	//大きいか小さいかを求める
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
			case _CK_BIG:	//大きいか小さいかを求める
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
	//エルミート曲線
	//----------------------------------------------------------------------------------------------------------------
	//@in : 始点座標
	//@in : 始点ベクトル
	//@in : 終点座標
	//@in : 終点ベクトル
	//@in : 経過時間
	//@in : 所要時間
	//@inout : 計算された座標
	//@out : 経過が合計を達したら(false)
	bool VectorFunc::GetHermiteLine(RCVector2 start,RCVector2 v1,RCVector2 end,RCVector2 v2,int cnt,int time,PVECTOR2 ans)
	{
		//cnterは０～１の間にあります
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
		
		//もし所要時間が経過時間を超えたら終了
		return ( cnt > time ? false : true );
	}
#endif

	//-------------------------------------------------------------------------------------------------------------------------
	//ベジェ曲線
	//-------------------------------------------------------------------------------------------------------------------------
	//@in : 始点
	//@in : 終点
	//@in : 制御１
	//@in : 制御２
	//@in : 経過時間
	//@in : 合計時間
	//@inout : 変換ベクトル
	//@out : 経過が合計を増したらfalse
	bool VectorFunc::GetBjetLine(RCVector2 start,RCVector2 end,RCVector2 controlA,
								RCVector2 controlB,const int cnt,const int time,PVector2 ans)
	{
		Vector2 p[4] = {(start),(controlA),(controlB),(end)};
		float cnter = (float)(cnt / time);
		float m = cnter, n = 1.0f - cnter;
		Vector2 s1[3],s2[3];

		//1回目の内分点取得
		for(int i=0; i<3; i++)
			s1[i] = this->Inner_point(p[i], p[i+1],m,n);
		//2回目の内分点取得
		for(int i=0; i<2; i++)
			s2[i] = this->Inner_point(s1[i], s1[i+1],m,n);

		//3回目の内分点（現在点）取得
		//現在の座標設定
		(*ans) = this->Inner_point(s2[0],s2[1],m,n);

		return (cnt > time ? false : true);
	}

	//--------------------------------------------------------------------------------------
	//内分点を返す関数
	//--------------------------------------------------------------------------------------
	//@in   : 始点
	//@in   : 終点
	//@in    : 内分値
	//@in    : 内分値２
	//@out : 変換座標 
	#pragma region 内分点ベクトル
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
