#ifndef _MYDIRECT_ATACK_H
#define _MYDIRECT_ATACK_H

#ifndef RESOURCE_FUNCTION_H
#include <ResourceFunction.h>
#endif

namespace NanairoLib
{
	//------------------------------------------------------------------
	//当たり判定をここに収納する
	//atack.cpp
	//------------------------------------------------------------------
	class CheckAtack
	{
	public:
		//-------------------------------------------------------------------------------------------------------------
		//線と三角形との当たり判定
		//-------------------------------------------------------------------------------------------------------------
		//@in : 線の始点ベクトル
		//@in : 線の終点ベクトル
		//@in : 三角形点Ａポジション
		//@in : 三角形点Ｂポジション
		//@in : 三角形点Ｃポジション
		//@out : true(当たっている) false(当たっていない)
		__IMPOETER bool Checkof_line_triangle(RCVector3 startPosi,RCVector3 endPosi,
															RCVector3 triPosiA,RCVector3 triPosiB,RCVector3 triPosiC);
		__IMPOETER bool Checkof_point_triangle(RCVector3 point,
															RCVector3 triPosiA,RCVector3 triPosiB,RCVector3 triPosiC);
		//--------------------------------------------------------------------------------------------------------------
		//ポリゴンと線との当たり判定
		//(下のメッシュとの当たり判定を参照する)
		//--------------------------------------------------------------------------------------------------------------
		//@in : モデルデータポインタ
		//@in : 始点ベクトル
		//@in : 終点ベクトル
		//@in : モデルのワールド座標
		//@in : 距離制限
		//@out : ポリゴンと線との距離
		//@out : true(当たっている) false(当たっていない)
		__IMPOETER bool Checkof_line_mesh(PCMODELH model,PCVector3 startpos, PCVector3 endpos,
																		PCMATRIX world,float distance,PFLOAT outdis);

		//-------------------------------------------------------------------------------------------
		//値でモデルとのＹの高さを求める(保留)
		//-------------------------------------------------------------------------------------------
		//__IMPOETER VECTOR3 GetAtackSlantingPos(ATACKH at,D3DXVECTOR3 pos, int idx,int atacknum);

		//-------------------------------------------------------------------------------------------------------------------------------
		//円同士の当たり判定
		//-------------------------------------------------------------------------------------------------------------------------------
		//@in : 円Ａの中心座標
		//@in : 円Ｂの中心座標
		//@in : 円Ａの半径
		//@in : 円Ｂの半径
		//@out : 距離
		//@in : true(2D) false(3D)
		//@out : true(当たっている) false(当たっていない)
		__IMPOETER bool Check_circle_obobject(RCVector3 cirA,RCVector3 cirB,float radiusA,float radiusB, PFLOAT outdistance,bool is2D = false);
		__IMPOETER bool Check_circle_obobject(RCVector2 cirA,RCVector2 cirB,float radiusA,float radiusB, PFLOAT outdistance);

		//--------------------------------------------------------------------------------------------------
		//点と四角形との当たり判定
		//--------------------------------------------------------------------------------------------------
		//@in : 点の座標
		//@in : 四角形の座標
		//@in : 幅
		//@in : 高さ
		//@in : 奥行き
		//@out : true(当たっている) false(当たっていない)
		__IMPOETER bool point_boundingAtack(PCVector2 point, PCVector2 box,float wid,float hei);
		__IMPOETER bool point_boundingAtack(PCVector3 point,PCVector3 box,float wid,float hei,float tun);

		//-----------------------------------------------
		//スクリーンアウト
		//-----------------------------------------------
		//@in : 対象座標
		//@out : true(当たっている) false(当たっていない)
		__IMPOETER bool Check_screenout(PCVector3 pos);
		__IMPOETER bool Check_screenout(PCVector2 pos);

		//-----------------------------------------------------------------------------------------------------------------
		//四角形4点の端と円との接触を判定する
		//-----------------------------------------------------------------------------------------------------------------
		//@in : 左上の点座標
		//@in : 右上の点座標
		//@in : 左下の点座標
		//@in : 右下の点座標
		//@in : 円の座標
		//@in : 点の半径
		//@in : 円の半径
		//@out : true(当たっている) false(当たっていない)
		__IMPOETER bool Checkof_4thPoint_circle_atack(RCVector2 lup,RCVector2 rup,RCVector2 lbot,RCVector2 rbot,
																			RCVector2 pos, float pointWid, float circleWid);

		//----------------------------------------------------------------------------------------------
		//四角形4点の線分と円との接触を判定する
		//----------------------------------------------------------------------------------------------
		//@in : 左上の点座標
		//@in : 右上の点座標
		//@in : 左下の点座標
		//@in : 右下の点座標
		//@in : 円の座標
		//@in : 点の半径
		//@in : 円の半径
		//@out : true(当たっている) false(当たっていない)
		__IMPOETER bool Checkof_4thLine_circle_atack(RCVector2 lup, RCVector2 rup, RCVector2 lbot,
										RCVector2 rbot, RCVector2 pos, float pointWid, float circleWid);
		
		//-----------------------------------------------------------------------------------------------
		//四角形の内部にいるかどうか判定する
		//-----------------------------------------------------------------------------------------------
		//@in : 左上の点座標
		//@in : 右上の点座標
		//@in : 左下の点座標
		//@in : 右下の点座標
		//@in : 円の座標
		//@out : true(内部) false(外部)
		__IMPOETER bool Checkof_4thBox_circle_inAtack(RCVector2 p1,RCVector2 p2,RCVector2 p3,RCVector2 p4,
																			RCVector2 pos);
	};

}

#endif