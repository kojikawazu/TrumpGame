#pragma once

//---------------------------------------
//�����蔻��^���i�[����
//�K�v�Ȏ��ɂǂ�ǂ񑝂₵�Ă���
//---------------------------------------
#include <AtackFunction.h>

namespace NanairoLib
{
	//------------------------------------------------------------
	//���ƎO�p�`�̓����蔻��(���쒆)
	//------------------------------------------------------------
	//@in : ���̎n�_�x�N�g��
	//@in : ���̏I�_�x�N�g��
	//@in : �O�p�`�_�`�|�W�V����
	//@in : �O�p�`�_�a�|�W�V����
	//@in : �O�p�`�_�b�|�W�V����
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::Checkof_line_triangle(
		RCVector3 startPosi, RCVector3 endPosi, RCVector3 triPosiA, RCVector3 triPosiB, RCVector3 triPosiC )
	{
		VectorFunc vec3D;
		Vector3 t1_l1, t1_l2, normal;

		//lineA �~ lineB(�@���x�N�g��)
		normal = vec3D.GetCloss( vec3D.GetVecDistance( triPosiA, triPosiB ), 
									vec3D.GetVecDistance( triPosiA, triPosiC ) );
		normal.Normalize();

		//�n�_ - ���`
		t1_l1 = vec3D.GetVecDistance( triPosiA, startPosi );
		t1_l1.Normalize();
		//�I�_ - ���`
		t1_l2 = vec3D.GetVecDistance( triPosiA, endPosi );
		t1_l2.Normalize();

		//�����̗��[�������܂ޕ��ʂ̕\���Ɨ����ɗ��Ă��邩����
		if( vec3D.GetDot( t1_l1 , normal ) == vec3D.GetDot( t1_l2, normal ) )
			return false;

		//�n�_ - ���`�̋���
		t1_l1 = vec3D.GetVecDistance( triPosiA, startPosi );
		float disA = vec3D.GetDot( t1_l1, normal );
		//�I�_ - ���`�̋���
		t1_l2 = vec3D.GetVecDistance( triPosiA, endPosi );
		float disB = vec3D.GetDot( t1_l2, normal );

		//disA : disB �̔䗦�œ��������x�N�g�������߂�
		Vector3 atpos = vec3D.Inner_point( startPosi, endPosi, vec3D.GetAbs( disA ), vec3D.GetAbs( disB ) );

		//�Ō�Ɍ�_�ƎO�p�`�̓�������
		return ( this->Checkof_point_triangle( atpos, triPosiA, triPosiB, triPosiC ));
	}
	
	//----------------------------------------------------------------
	//�_�ƎO�p�`�̂����蔻��
	//@in : �_�̃x�N�g��
	//@in : �O�p�`�_�`�|�W�V����
	//@in : �O�p�`�_�a�|�W�V����
	//@in : �O�p�`�_�b�|�W�V����
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	//----------------------------------------------------------------
	bool CheckAtack::Checkof_point_triangle(RCVector3 point,
		RCVector3 triPosiA,RCVector3 triPosiB,RCVector3 triPosiC)
	{
		VectorFunc v3D;
		Vector3 t1, t2, t3;
		Vector3 n1, n2, n3;
		Vector3 normal;
		
		//���̖@�������߂�
		normal = v3D.GetCloss( v3D.GetVecDistance( triPosiA, triPosiB ), 
									v3D.GetVecDistance( triPosiA, triPosiC ) );

		//�Ώۓ_���炻�ꂼ��̇��̈ʒu�̃x�N�g��
		t1 = v3D.GetVecDistance( point, triPosiA );
		t2 = v3D.GetVecDistance( point, triPosiB );
		t3 = v3D.GetVecDistance( point, triPosiC );
		n1 = v3D.GetCloss( t1, t2 );
		n2 = v3D.GetCloss( t2, t3 );
		n3 = v3D.GetCloss( t3, t1 );

		//��������
		float disA = v3D.GetDot( n1, normal );
		float disB = v3D.GetDot( n2, normal );
		float disC = v3D.GetDot( n3, normal );

		//��������v���Ă���Ȃ�����ɂ���
		//�t�Ȃ�O��
		if( disA > 0.0f )
			return ( disC > 0.0f && disC > 0.0f);
		else if( v3D.GetDot( n1, normal ) < 0.0f )
			return ( disC < 0.0f && disC < 0.0f);
		else
			return ( disC == 0.0f && disC == 0.0f);
	}
	
	//------------------------------------------------------------------------------------
	//���b�V���Ɛ����̓����蔻��
	//------------------------------------------------------------------------------------
	//@in : ���f���f�[�^�|�C���^
	//@in : �n�_�x�N�g��
	//@in : �I�_�x�N�g��
	//@in : ���f���̃��[���h���W
	//@in : ��������
	//@out : �|���S���Ɛ��Ƃ̋���
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::Checkof_line_mesh(PCMODELH model,PCVector3 startpos, PCVector3 endpos,
								PCMATRIX world,float distance,PFLOAT outdis)
	{

		float dis;
		BOOL judge;
		D3DXMATRIX matI;
		D3DXVECTOR3 stI,edI;
		DWORD wod;
		
		::D3DXMatrixInverse(&matI, NULL, world);		//���[���h���W�̋t�s��̎擾

		::D3DXVec3TransformCoord(&stI,&((Vector3*)startpos)->SetD3DVector3(),&matI);	//�x�N�g���ƍs��Ōv�Z���ăx�N�g���l�ŕԂ�
		::D3DXVec3TransformCoord(&edI,&((Vector3*)endpos)->SetD3DVector3(),&matI);
					
		//��3�������A���Ă����n�_�ƏI�_�������ăx�N�g���ɂ���
		//�����āA�W���b�W�I
		::D3DXIntersect(model->mesh, &stI, &(edI - stI), &judge, &wod,
			NULL,NULL, &dis, NULL, NULL);
		*outdis = dis;

		//�������Ă���,�������������C�Ӓl�ȉ��Ȃ�OK!
		return (judge == TRUE && dis < distance);
	}
	
	//------------------------------------------------------------------------------------------------------------------------
	//�~���m�Ƃ̓����蔻��(3D)
	//------------------------------------------------------------------------------------------------------------------------
	//@in : �~�`�̒��S���W
	//@in : �~�a�̒��S���W
	//@in : �~�`�̔��a
	//@in : �~�a�̔��a
	//@out : ����
	//@in : true(2D) false(3D)
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::Check_circle_obobject(RCVector3 cirA,RCVector3 cirB,float radiusA,float radiusB, PFLOAT outdistance,bool is2D)
	{
		VectorFunc vec3D;
		if( !is2D )		return ((*outdistance = vec3D.GetVecDistanceAbsLong(cirA, cirB)) < radiusA + radiusB);
		else			return ((*outdistance = vec3D.GetVecDistanceAbsLong(Vector2(cirA.x,cirA.z), Vector2(cirB.x,cirB.z))) < radiusA + radiusB);
	}

	//-------------------------------------------------------------------------------------------------------------------------------
	//�~���m�̓����蔻��(2D)
	//-------------------------------------------------------------------------------------------------------------------------------
	//@in : �~�`�̒��S���W
	//@in : �~�a�̒��S���W
	//@in : �~�`�̔��a
	//@in : �~�a�̔��a
	//@out : ����
	//@in : true(2D) false(3D)
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::Check_circle_obobject(RCVector2 cirA, RCVector2 cirB,float radiusA,float radiusB, PFLOAT outdistance)
	{
		VectorFunc vec3D;
		return ((*outdistance = vec3D.GetVecDistanceAbsLong(cirA, cirB)) < radiusA + radiusB ? true : false);
	}

	//-----------------------------------------------------------------------------------------
	//�_�Ǝl�p�`�̓����蔻��(AABB)
	//-----------------------------------------------------------------------------------------
	//@in : �_�̍��W
	//@in : �l�p�`�̍��W
	//@in : ��
	//@in : ����
	//@in : ���s��
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::point_boundingAtack(PCVector2 point, PCVector2 box,float wid,float hei)
	{
		return ((point->x > box->x - wid && point->x < box->x + wid && point->y > box->y - hei && point->y < box->y + hei) ? true : false);
	}	

	//-----------------------------------------------------------------------------------------
	//�_�Ƒ̐ς̓����蔻��(AABB)
	//-----------------------------------------------------------------------------------------
	//@in : �_�̍��W
	//@in : �l�p�`�̍��W
	//@in : ��
	//@in : ����
	//@in : ���s��
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::point_boundingAtack(PCVector3 point, PCVector3 box,float wid,float hei,float tun)
	{
		return ((point->x > box->x - wid && point->x < box->x + wid && point->y > box->y - hei && point->y < box->y + hei && point->z > box->z - tun && point->z < box->z + tun) ? true : false);
	}	

	//-----------------------------------------------
	//�t�B�[���h�A�E�g(3D)
	//-----------------------------------------------
	//@in : �Ώۍ��W
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::Check_screenout(PCVector3 pos)
	{
		//��ʊO�ɂ����琬���I
		return ((pos->x < -50 || pos->x > SCRW + 50 || pos->y < -50 || pos->y > SCRW + 50) ? true : false);
	}

	//-----------------------------------------------
	//�X�N���[���A�E�g(2D)
	//-----------------------------------------------
	//@in : �Ώۍ��W
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::Check_screenout(PCVector2 pos)
	{
		//��ʊO�ɂ����琬���I
		return ((pos->x < -50 || pos->x > SCRW + 50 || pos->y < -50 || pos->y > SCRW + 50) ? true : false);
	}

	//-----------------------------------------------------------------------------------------------------------------
	//�l�p�`4�_�̒[�Ɖ~�Ƃ̐ڐG�𔻒肷��
	//-----------------------------------------------------------------------------------------------------------------
	//@in : ����̓_���W
	//@in : �E��̓_���W
	//@in : �����̓_���W
	//@in : �E���̓_���W
	//@in : �~�̍��W
	//@in : �_�̔��a
	//@in : �~�̔��a
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
	bool CheckAtack::Checkof_4thPoint_circle_atack(RCVector2 lup, RCVector2 rup, RCVector2 lbot,
											RCVector2 rbot, RCVector2 pos, float pointWid, float circleWid)
	{
		PCVector2 list[4] = {&lup, &rup, &lbot, &rbot};
		float dis = 0.0f;

		for(int i=0; i<4; i++)
		{
			//�ǂ���1�ł��ڐG���Ă����琬���I
			if( this->Check_circle_obobject(*list[i], pos, pointWid, circleWid, &dis) )
				return true;
		}
		//�ǂ���������Ȃ���Ύ��s�E�E�E�B
		return false;
	}
	
	//----------------------------------------------------------------------------------------------
	//�l�p�`4�_�̐����Ɖ~�Ƃ̐ڐG�𔻒肷��
	//----------------------------------------------------------------------------------------------
	//@in : ����̓_���W
	//@in : �E��̓_���W
	//@in : �����̓_���W
	//@in : �E���̓_���W
	//@in : �~�̍��W
	//@in : �_�̔��a
	//@in : �~�̔��a
	//@out : true(�������Ă���) false(�������Ă��Ȃ�)
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
			//�l�p�`�̃x�N�g��
			vec1 = vecfunc.GetVecDistance(*list[n[0][i]], *list[n[1][i]]);
			//�l�p�`����~�܂ł̃x�N�g��
			vec2 = vecfunc.GetVecDistance(*list[n[0][i]], pos);

			inner = vecfunc.GetDot(vec1, vec2);	//����
			pdis1 = vecfunc.GetDot(vec1, vec1);	//�傫����2�{
			pdis2 = vecfunc.GetDot(vec2, vec2);	//�傫����2�{

			k = inner / pdis2;
			if(k < 0 || 1 < k)	continue;			//�Ώۂ������𒴂��Ă���A�E�g�I

			pdis1 = inner * k;						//�ˉe�����̑傫����2��

			//�����̑傫����2��
			if(pdis2 - pdis1 < pointWid * circleWid)	return true;	//��r���Đ��������W����菬�����Ɠ��������I
		}
		return false;
	}
	
	//-----------------------------------------------------------------------------------------------
	//�l�p�`�̓����ɂ��邩�ǂ������肷��
	//-----------------------------------------------------------------------------------------------
	//@in : ����̓_���W
	//@in : �E��̓_���W
	//@in : �����̓_���W
	//@in : �E���̓_���W
	//@in : �~�̍��W
	//@out : true(����) false(�O��)
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

			//�O��/���ς�tan�Ƃ��o��I
			theta[i] = BACK_PI( atan2( vecfunc.GetCloss(vec1, vec2), vecfunc.GetDot(vec1, vec2) ) );		
		}

		//�l�p�`�̓����ɂ���Ƃ������Ƃ́A�p�x�͉s�p�ł��邱�Ƃ��O��I
		//�s�p�Ȃ炠����I
		return ((0 <= theta[0] && theta[0] <= 90 && 0 <= theta[1] && theta[1] <= 90) ? true : false);
	 }
}