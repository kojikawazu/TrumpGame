#ifndef NanairoLib_FUNC_H
#define NanairoLib_FUNC_H

#ifndef _NanairoLib_MYVECTOR_H
#include <DirectParts.h>
#endif

//-----------------------------------------
//割り当て型関数クラスをここに記載
//必要な関数を増やしたり使いたい時はここのクラスを使うっ
//※データ保持が必要な場合はこのクラスには入れることはできません＞＜
//-----------------------------------------
namespace NanairoLib
{
	//-------------------------------
	//角度を扱うときの種類
	//-------------------------------
	enum RAD_NUMBER
	{
		_NONERAD, _ANGLE_RAD, _RAD_COS, _RAD_SIN, _RAD_TAN, _RAD_TAN2
	};

	//-------------------------------
	//比較演算子で使う種類
	//-------------------------------
	enum CHECK_NUMBER
	{
		CK_EQUAL, _CK_BIG, _CK_SMALL,
	};

	//------------------------------------------------------------------
	//ベクトルやその他計算類はここに収納する
	///このクラスを呼び出して計算するのが目的！
	//------------------------------------------------------------------
	class VectorFunc
	{
	public:
		//-------------------------------------------------------
		//小さいか判定(Aを対象に、Ｂから大きいか)
		//-------------------------------------------------------
		//@in : 対象A 
		//@in : 対象B
		//@out :  大きい ? (true) : (false)
		__IMPOETER	bool Min_hantei(float checkA, float checkB);
		
		//-------------------------------------------------------------
		//3次元ベクトルを2次元に
		//-------------------------------------------------------------
		//@in :	対象ベクトル・又は始点ベクトル
		//@in : もしくは終点ベクトル
		//@out : 角軸による2次元ベクトルに変換させる
		__IMPOETER	Vector2 GetVectorXZ(RCVector3 vec);
		__IMPOETER	Vector2 GetVectorXZ(RCVector3 start,RCVector3 end);
		__IMPOETER	Vector2 GetVectorXY(RCVector3 vec);
		__IMPOETER	Vector2 GetVectorXY(RCVector3 start, RCVector3 end);

		//--------------------------------------------------------------
		//始点から終点を引いた距離ベクトル
		//--------------------------------------------------------------
		//@in : 始点 
		//@in : 終点
		//@out : 出来上がった距離ベクトル
		__IMPOETER	Vector3 GetVecDistance(RCVector3 st, RCVector3 end);
		__IMPOETER	Vector2 GetVecDistance(RCVector2 st, RCVector2 end);
		__IMPOETER	Vector2 GetVecDistanceNormalize(RCVector2 st, RCVector2 end);

		//-------------------------------------------
		//距離を求める
		//-------------------------------------------
		//@in : 対象
		//@out : 距離
		__IMPOETER	float GetDistance(RCVector3 pos);
		__IMPOETER	float GetDistance(RCVector2 pos);
		__IMPOETER	float GetDistance(float dis);

		//--------------------------------------------------------------
		//ベクトルの大きさ
		//--------------------------------------------------------------
		//@in : 対象のベクトル
		//@out : 角値の大きさ
		__IMPOETER	float GetVecDistanceLong(RCVector3 one);
		__IMPOETER	float GetVecDistanceLong(RCVector2 one);
		__IMPOETER	float GetVecDistanceLong(const float dx);
		__IMPOETER	float GetVecDistanceLong(const float ax, const float ay);
		__IMPOETER	float GetVecDistanceAbsLong(RCVector3 vecA, RCVector3 vecB);
		__IMPOETER	float GetVecDistanceAbsLong(RCVector2 vecA, RCVector2 vecB);

		//--------------------------------------------------------------
		//ベクトルの法線ベクトル
		//--------------------------------------------------------------
		//@in : 対象ベクトル,又は始点ベクトル
		//@in : もしくは終点ベクトル
		//@out : 法線ベクトル（単位かした状態で）
		__IMPOETER	Vector3 GetNormal(RCVector3 st ,RCVector3 end);
		__IMPOETER	Vector2 GetNormal(RCVector2 st, RCVector2 end);
		__IMPOETER	Vector3 GetNormal(RCVector3 pos);
		__IMPOETER	Vector2 GetNormal(RCVector2 pos);

		//--------------------------------------------------------------
		//ベクトルの内積
		//--------------------------------------------------------------
		//@in : 対象ベクトル１
		//@in : 対象ベクトル２
		//@out : 内積
		__IMPOETER	float GetDot(RCVector3 checkA, RCVector3 checkB);
		__IMPOETER	float GetDot(RCVector2 checkA, RCVector2 checkB);
		__IMPOETER	float GetDotProjection(RCVector3 checkA, RCVector3 checkB);
		__IMPOETER	float GetDotProjection(RCVector2 checkA, RCVector2 checkB);
			
		//--------------------------------------------------------------
		//ベクトルの外積
		//--------------------------------------------------------------
		//@in : 対象ベクトル１
		//@in : 対象ベクトル２
		//@out	: 2D → 外積
		//		: 3D → 法線ベクトル
		__IMPOETER	Vector3 GetCloss(RCVector3 checkA, RCVector3 checkB);
		__IMPOETER	float GetCloss(RCVector2 checkA, RCVector2 checkB);
		__IMPOETER	float GetClossProjection(RCVector2 checkA, RCVector2 checkB);

#ifdef _USED_DIRECTX
		//------------------------------------------------------------------
		//行列の進行
		//------------------------------------------------------------------
		//@in : 掛け合わせる行列
		//@in : 移動ベクトル
		//@out : 変換行列
		__IMPOETER	D3DXMATRIXA16 GetTransMat(PCMATRIX16 mat,RCVector3 vec);
		
		//---------------------------------------------------------------------------
		//行列の回転(アフィン変換)
		//---------------------------------------------------------------------------
		//@in : 対象行列
		//@in : 原点へ戻すベクトル
		//@in : 回転角度
		//@out : 各軸での変換行列
		__IMPOETER 	D3DXMATRIXA16 GetRotaX(PCMATRIX16 mat,RCVector3 vec,float angle);
		__IMPOETER	D3DXMATRIXA16 GetRotaY(PCMATRIX16 mat,RCVector3 vec,float angle);
		__IMPOETER	D3DXMATRIXA16 GetRotaZ(PCMATRIX16 mat,RCVector3 vec,float angle);

		//----------------------------------------------------------------------------------------------------
		//クォータニオンワールド座標変換
		//----------------------------------------------------------------------------------------------------
		//@posi(位置) @scale(拡大率) @rotavec(任意軸) @ang(回転角度)
		//戻	: すべてを掛け合わせた行列
		__IMPOETER	D3DXMATRIX SetworldQuaternion(RCVector3 posi,RCVector3 scale,RCVector3 rotavec,float ang);
		
		//-----------------------------------------------------------------
		//クォータニオン変換
		//-----------------------------------------------------------------
		//@in : 任意軸 
		//@in : 回転角度
		//@out : クォータニオン行列
		__IMPOETER	D3DXQUATERNION GetQuaternion(RCVector3 rota,float ang);
#endif

		//-------------------------------------------------------------
		//角度のラジアン角を求める
		//-------------------------------------------------------------
		//0(普通の角度) 1(cosθ) 2(sinθ) 3(tanθ)
		//@out : ラジアン角
		__IMPOETER	float ChangeRad(float cosA,int _angle_number = 0);
		__IMPOETER	float ChangeRadAtan2(RCVector2 vec); 
		__IMPOETER	float ChangeRadAtan2(RCVector2 vecA, RCVector2 vecB); 
		__IMPOETER	float ChangeRadAtan2(float vecX, float vecY); 
		__IMPOETER	float ChangeRadAtan2XY(RCVector3 vecA, RCVector3 vecB); 
		__IMPOETER	float ChangeRadAtan2XZ(RCVector3 vecA, RCVector3 vecB); 

		//--------------------------------------------------------------
		//ラジアンから角度を求める
		//--------------------------------------------------------------
		//0(普通の角度) 1(cosθ) 2(sinθ) 3(tanθ)
		//@out : 角度
		__IMPOETER	float ChangeAngle(float cosA,int _angle_number);
		__IMPOETER	float ChangeAngleAtan2(RCVector2 vec); 
		__IMPOETER	float ChangeAngleAtan2(RCVector2 vecA, RCVector2 vecB); 
		__IMPOETER	float ChangeAngleAtan2(float vecX, float vecY);
		__IMPOETER	float ChangeAngleAtan2XY(RCVector3 vecA, RCVector3 vecB);
		__IMPOETER	float ChangeAngleAtan2XZ(RCVector3 vecA, RCVector3 vecB);

		//-------------------------------------------------------------
		//ベクトルから角度を求める
		//-------------------------------------------------------------
		//@in : 求めたいベクトル
		//@out : 角度
		__IMPOETER	float GetAngleAtan2(RCVector2 st, RCVector2 end);

		//------------------------------------------------
		//ベクトルから角度を求める
		//------------------------------------------------
		//@in : 求めたいベクトル
		//@out : 角度
		__IMPOETER	float GetVectorOfAngleY(RCVector3 vec);
		
		//-----------------------------------------------------------------
		//2点からベクトルを求め角度を求める
		//-----------------------------------------------------------------
		//@in : 始点ベクトル
		//@in : 終点ベクトル
		//@out : 角度
		__IMPOETER	float GetVectorOfAngleY(RCVector3 vecontrolA,RCVector3 vecontrolB);
		
		//----------------------------------------------------------------------------------------------------
		//4点から2つのベクトルを求め、角度を求める
		//----------------------------------------------------------------------------------------------------
		//@in : ベクトルＡの始点
		//@in : ベクトルＡの終点
		//@in : ベクトルＢの始点
		//@in : ベクトルＢの終点
		//@out : 角度
		__IMPOETER	 float GetVectorOfAngleY(RCVector3 vecontrolA1,RCVector3 vecontrolA2,RCVector3 vecontrolB1,RCVector3 vecontrolB2);

		//------------------------------------------
		//絶対値を求める
		//------------------------------------------
		//@in : 対象
		//@out : 絶対値
		__IMPOETER	Vector3 GetAbs(RCVector3 pos);
		__IMPOETER	Vector2 GetAbs(RCVector2 pos);
		__IMPOETER	float GetAbs(float pos);

		//------------------------------------------------------------------------------------------
		//次にいく方向ベクトルを求める
		//------------------------------------------------------------------------------------------
		//@in : 次のポイント 
		//@in : 前のポイント 
		//@out : 移動ベクトル
		//@out : 移動距離
		//@out : true(成功) false(失敗)
		__IMPOETER	bool SetNextPointVector(RCVector3 point,RCVector3 oldpos,Vector3 *anspos,float *dis);

		//------------------------------------------------------------------------------
		//方向ベクトルの進む角度を求める
		//------------------------------------------------------------------------------
		//@in : 始点 
		//@in : 終点 
		//@in : 対象角度
		//@out : 現在のベクトルからの角度の差を返す
		__IMPOETER	float GetChangeAngleSin(RCVector2 stpos,RCVector2 endpos,float ang);
		__IMPOETER	float GetChangeAngleCos(RCVector2 stpos,RCVector2 endpos,float ang);

		//--------------------------------------------------------------------------------
		//角度チェンジ
		//--------------------------------------------------------------------------------
		//@in : 現在のベクトル
		//@in : 回転角度
		//@out : 回転したベクトル
		__IMPOETER	Vector3	VectorRotationXZ(RCVector3 vec,float ang,bool isRota = false);
		__IMPOETER	Vector2 VectorRotationXZ(RCVector2 vec,float ang,bool isRota);
		
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
		__IMPOETER	bool Check_Direction(RCVector3 posA,RCVector3 posB,float ang,float *out,int _angle_number,int equalNumber);
		__IMPOETER	bool Check_Direction(RCVector2 posA,RCVector2 posB,float ang,float *out,int _angle_number,int equalNumber);

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
		__IMPOETER	bool GetHermiteLine(RCVector2 start,RCVector2 v1,RCVector2 end,RCVector2 v2,int cnt,int time,PVECTOR2 ans);
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
		__IMPOETER	bool GetBjetLine(RCVector2 start,RCVector2 end,RCVector2 controlA,RCVector2 controlB,const int cnt,const int time,PVector2 ans);
		
		//--------------------------------------------------------------------------------------
		//内分点を返す関数
		//--------------------------------------------------------------------------------------
		//@in   : 始点
		//@in   : 終点
		//@in    : 内分値
		//@in    : 内分値２
		//@out : 変換座標 
		__IMPOETER	Vector2 Inner_point(RCVector2 start,RCVector2 end,const float m,const float n);
		__IMPOETER	Vector3 Inner_point(RCVector3 start,RCVector3 end,const float m,const float n);
	};

}

#endif