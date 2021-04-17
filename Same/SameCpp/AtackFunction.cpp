#pragma once

//---------------------------------------
//当たり判定型を格納する
//必要な時にどんどん増やしていく
//---------------------------------------
#include <AtackFunction.h>

namespace NanairoLib
{
	//------------------------------------------------------------
	//線と三角形の当たり判定(制作中)
	//------------------------------------------------------------
	//@in : 線の始点ベクトル
	//@in : 線の終点ベクトル
	//@in : 三角形点Ａポジション
	//@in : 三角形点Ｂポジション
	//@in : 三角形点Ｃポジション
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::Checkof_line_triangle(
		RCVector3 startPosi, RCVector3 endPosi, RCVector3 triPosiA, RCVector3 triPosiB, RCVector3 triPosiC )
	{
		VectorFunc vec3D;
		Vector3 t1_l1, t1_l2, normal;

		//lineA × lineB(法線ベクトル)
		normal = vec3D.GetCloss( vec3D.GetVecDistance( triPosiA, triPosiB ), 
									vec3D.GetVecDistance( triPosiA, triPosiC ) );
		normal.Normalize();

		//始点 - ⊿Ａ
		t1_l1 = vec3D.GetVecDistance( triPosiA, startPosi );
		t1_l1.Normalize();
		//終点 - ⊿Ａ
		t1_l2 = vec3D.GetVecDistance( triPosiA, endPosi );
		t1_l2.Normalize();

		//線分の両端が⊿を含む平面の表側と裏側に来ているか調査
		if( vec3D.GetDot( t1_l1 , normal ) == vec3D.GetDot( t1_l2, normal ) )
			return false;

		//始点 - ⊿Ａの距離
		t1_l1 = vec3D.GetVecDistance( triPosiA, startPosi );
		float disA = vec3D.GetDot( t1_l1, normal );
		//終点 - ⊿Ａの距離
		t1_l2 = vec3D.GetVecDistance( triPosiA, endPosi );
		float disB = vec3D.GetDot( t1_l2, normal );

		//disA : disB の比率で内分したベクトルを求める
		Vector3 atpos = vec3D.Inner_point( startPosi, endPosi, vec3D.GetAbs( disA ), vec3D.GetAbs( disB ) );

		//最後に交点と三角形の内部判定
		return ( this->Checkof_point_triangle( atpos, triPosiA, triPosiB, triPosiC ));
	}
	
	//----------------------------------------------------------------
	//点と三角形のあたり判定
	//@in : 点のベクトル
	//@in : 三角形点Ａポジション
	//@in : 三角形点Ｂポジション
	//@in : 三角形点Ｃポジション
	//@out : true(当たっている) false(当たっていない)
	//----------------------------------------------------------------
	bool CheckAtack::Checkof_point_triangle(RCVector3 point,
		RCVector3 triPosiA,RCVector3 triPosiB,RCVector3 triPosiC)
	{
		VectorFunc v3D;
		Vector3 t1, t2, t3;
		Vector3 n1, n2, n3;
		Vector3 normal;
		
		//⊿の法線を求める
		normal = v3D.GetCloss( v3D.GetVecDistance( triPosiA, triPosiB ), 
									v3D.GetVecDistance( triPosiA, triPosiC ) );

		//対象点からそれぞれの⊿の位置のベクトル
		t1 = v3D.GetVecDistance( point, triPosiA );
		t2 = v3D.GetVecDistance( point, triPosiB );
		t3 = v3D.GetVecDistance( point, triPosiC );
		n1 = v3D.GetCloss( t1, t2 );
		n2 = v3D.GetCloss( t2, t3 );
		n3 = v3D.GetCloss( t3, t1 );

		//符号判定
		float disA = v3D.GetDot( n1, normal );
		float disB = v3D.GetDot( n2, normal );
		float disC = v3D.GetDot( n3, normal );

		//符号が一致しているなら内部にいる
		//逆なら外部
		if( disA > 0.0f )
			return ( disC > 0.0f && disC > 0.0f);
		else if( v3D.GetDot( n1, normal ) < 0.0f )
			return ( disC < 0.0f && disC < 0.0f);
		else
			return ( disC == 0.0f && disC == 0.0f);
	}
	
	//------------------------------------------------------------------------------------
	//メッシュと線分の当たり判定
	//------------------------------------------------------------------------------------
	//@in : モデルデータポインタ
	//@in : 始点ベクトル
	//@in : 終点ベクトル
	//@in : モデルのワールド座標
	//@in : 距離制限
	//@out : ポリゴンと線との距離
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::Checkof_line_mesh(PCMODELH model,PCVector3 startpos, PCVector3 endpos,
								PCMATRIX world,float distance,PFLOAT outdis)
	{

		float dis;
		BOOL judge;
		D3DXMATRIX matI;
		D3DXVECTOR3 stI,edI;
		DWORD wod;
		
		::D3DXMatrixInverse(&matI, NULL, world);		//ワールド座標の逆行列の取得

		::D3DXVec3TransformCoord(&stI,&((Vector3*)startpos)->SetD3DVector3(),&matI);	//ベクトルと行列で計算してベクトル値で返す
		::D3DXVec3TransformCoord(&edI,&((Vector3*)endpos)->SetD3DVector3(),&matI);
					
		//第3引数→帰ってきた始点と終点を引いてベクトルにする
		//そして、ジャッジ！
		::D3DXIntersect(model->mesh, &stI, &(edI - stI), &judge, &wod,
			NULL,NULL, &dis, NULL, NULL);
		*outdis = dis;

		//当たっている,しかも距離が任意値以下ならOK!
		return (judge == TRUE && dis < distance);
	}
	
	//------------------------------------------------------------------------------------------------------------------------
	//円同士との当たり判定(3D)
	//------------------------------------------------------------------------------------------------------------------------
	//@in : 円Ａの中心座標
	//@in : 円Ｂの中心座標
	//@in : 円Ａの半径
	//@in : 円Ｂの半径
	//@out : 距離
	//@in : true(2D) false(3D)
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::Check_circle_obobject(RCVector3 cirA,RCVector3 cirB,float radiusA,float radiusB, PFLOAT outdistance,bool is2D)
	{
		VectorFunc vec3D;
		if( !is2D )		return ((*outdistance = vec3D.GetVecDistanceAbsLong(cirA, cirB)) < radiusA + radiusB);
		else			return ((*outdistance = vec3D.GetVecDistanceAbsLong(Vector2(cirA.x,cirA.z), Vector2(cirB.x,cirB.z))) < radiusA + radiusB);
	}

	//-------------------------------------------------------------------------------------------------------------------------------
	//円同士の当たり判定(2D)
	//-------------------------------------------------------------------------------------------------------------------------------
	//@in : 円Ａの中心座標
	//@in : 円Ｂの中心座標
	//@in : 円Ａの半径
	//@in : 円Ｂの半径
	//@out : 距離
	//@in : true(2D) false(3D)
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::Check_circle_obobject(RCVector2 cirA, RCVector2 cirB,float radiusA,float radiusB, PFLOAT outdistance)
	{
		VectorFunc vec3D;
		return ((*outdistance = vec3D.GetVecDistanceAbsLong(cirA, cirB)) < radiusA + radiusB ? true : false);
	}

	//-----------------------------------------------------------------------------------------
	//点と四角形の当たり判定(AABB)
	//-----------------------------------------------------------------------------------------
	//@in : 点の座標
	//@in : 四角形の座標
	//@in : 幅
	//@in : 高さ
	//@in : 奥行き
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::point_boundingAtack(PCVector2 point, PCVector2 box,float wid,float hei)
	{
		return ((point->x > box->x - wid && point->x < box->x + wid && point->y > box->y - hei && point->y < box->y + hei) ? true : false);
	}	

	//-----------------------------------------------------------------------------------------
	//点と体積の当たり判定(AABB)
	//-----------------------------------------------------------------------------------------
	//@in : 点の座標
	//@in : 四角形の座標
	//@in : 幅
	//@in : 高さ
	//@in : 奥行き
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::point_boundingAtack(PCVector3 point, PCVector3 box,float wid,float hei,float tun)
	{
		return ((point->x > box->x - wid && point->x < box->x + wid && point->y > box->y - hei && point->y < box->y + hei && point->z > box->z - tun && point->z < box->z + tun) ? true : false);
	}	

	//-----------------------------------------------
	//フィールドアウト(3D)
	//-----------------------------------------------
	//@in : 対象座標
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::Check_screenout(PCVector3 pos)
	{
		//画面外にいたら成功！
		return ((pos->x < -50 || pos->x > SCRW + 50 || pos->y < -50 || pos->y > SCRW + 50) ? true : false);
	}

	//-----------------------------------------------
	//スクリーンアウト(2D)
	//-----------------------------------------------
	//@in : 対象座標
	//@out : true(当たっている) false(当たっていない)
	bool CheckAtack::Check_screenout(PCVector2 pos)
	{
		//画面外にいたら成功！
		return ((pos->x < -50 || pos->x > SCRW + 50 || pos->y < -50 || pos->y > SCRW + 50) ? true : false);
	}

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
	bool CheckAtack::Checkof_4thPoint_circle_atack(RCVector2 lup, RCVector2 rup, RCVector2 lbot,
											RCVector2 rbot, RCVector2 pos, float pointWid, float circleWid)
	{
		PCVector2 list[4] = {&lup, &rup, &lbot, &rbot};
		float dis = 0.0f;

		for(int i=0; i<4; i++)
		{
			//どこか1つでも接触していたら成功！
			if( this->Check_circle_obobject(*list[i], pos, pointWid, circleWid, &dis) )
				return true;
		}
		//どこも当たらなければ失敗・・・。
		return false;
	}
	
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
	bool CheckAtack::Checkof_4thLine_circle_atack(RCVector2 lup, RCVector2 rup, RCVector2 lbot,
											RCVector2 rbot, RCVector2 pos, float pointWid, float circleWid)
	{
		PCVector2 list[4] = {&lup, &rup, &lbot, &rbot};
		const int n[][4] = {{0,1,3,2}, {1,3,2,0}};
		NanairoLib::VectorFunc vecfunc;
		Vector2 vec1, vec2;
		float inner, pdis1, pdis2, k;

		for(int i=0; i<4; i++)
		{
			//四角形のベクトル
			vec1 = vecfunc.GetVecDistance(*list[n[0][i]], *list[n[1][i]]);
			//四角形から円までのベクトル
			vec2 = vecfunc.GetVecDistance(*list[n[0][i]], pos);

			inner = vecfunc.GetDot(vec1, vec2);	//内積
			pdis1 = vecfunc.GetDot(vec1, vec1);	//大きさの2倍
			pdis2 = vecfunc.GetDot(vec2, vec2);	//大きさの2倍

			k = inner / pdis2;
			if(k < 0 || 1 < k)	continue;			//対象が線分を超えてたらアウト！

			pdis1 = inner * k;						//射影部分の大きさの2乗

			//垂線の大きさの2乗
			if(pdis2 - pdis1 < pointWid * circleWid)	return true;	//比較して垂線が幅集合より小さいと当たった！
		}
		return false;
	}
	
	//-----------------------------------------------------------------------------------------------
	//四角形の内部にいるかどうか判定する
	//-----------------------------------------------------------------------------------------------
	//@in : 左上の点座標
	//@in : 右上の点座標
	//@in : 左下の点座標
	//@in : 右下の点座標
	//@in : 円の座標
	//@out : true(内部) false(外部)
	 bool CheckAtack::Checkof_4thBox_circle_inAtack(RCVector2 lup, RCVector2 rup, RCVector2 lbot,
														RCVector2 rbot,RCVector2 pos)
	 {
		PCVector2 list[4] = {&lup, &rup, &lbot, &rbot};
		NanairoLib::VectorFunc vecfunc;
		float theta[2];
		Vector2 vec1, vec2;

		for(int i=0; i<2; i++)
		{
			vec1 = vecfunc.GetVecDistance(*list[i * 3], *list[1 + i]);
			vec2 = vecfunc.GetVecDistance(*list[i * 3], pos);

			//外積/内積でtanθが出る！
			theta[i] = BACK_PI( atan2( vecfunc.GetCloss(vec1, vec2), vecfunc.GetDot(vec1, vec2) ) );		
		}

		//四角形の内部にいるということは、角度は鋭角であることが前提！
		//鋭角ならあたり！
		return ((0 <= theta[0] && theta[0] <= 90 && 0 <= theta[1] && theta[1] <= 90) ? true : false);
	 }
}