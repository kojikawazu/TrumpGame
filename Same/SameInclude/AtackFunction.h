#ifndef _MYDIRECT_ATACK_H
#define _MYDIRECT_ATACK_H

#ifndef RESOURCE_FUNCTION_H
#include <ResourceFunction.h>
#endif

namespace NanairoLib
{
	//------------------------------------------------------------------
	//�����蔻��������Ɏ��[����
	//atack.cpp
	//------------------------------------------------------------------
	class CheckAtack
	{
	public:
		//-------------------------------------------------------------------------------------------------------------
		//���ƎO�p�`�Ƃ̓����蔻��
		//-------------------------------------------------------------------------------------------------------------
		//@in : ���̎n�_�x�N�g��
		//@in : ���̏I�_�x�N�g��
		//@in : �O�p�`�_�`�|�W�V����
		//@in : �O�p�`�_�a�|�W�V����
		//@in : �O�p�`�_�b�|�W�V����
		//@out : true(�������Ă���) false(�������Ă��Ȃ�)
		__IMPOETER bool Checkof_line_triangle(RCVector3 startPosi,RCVector3 endPosi,
															RCVector3 triPosiA,RCVector3 triPosiB,RCVector3 triPosiC);
		__IMPOETER bool Checkof_point_triangle(RCVector3 point,
															RCVector3 triPosiA,RCVector3 triPosiB,RCVector3 triPosiC);
		//--------------------------------------------------------------------------------------------------------------
		//�|���S���Ɛ��Ƃ̓����蔻��
		//(���̃��b�V���Ƃ̓����蔻����Q�Ƃ���)
		//--------------------------------------------------------------------------------------------------------------
		//@in : ���f���f�[�^�|�C���^
		//@in : �n�_�x�N�g��
		//@in : �I�_�x�N�g��
		//@in : ���f���̃��[���h���W
		//@in : ��������
		//@out : �|���S���Ɛ��Ƃ̋���
		//@out : true(�������Ă���) false(�������Ă��Ȃ�)
		__IMPOETER bool Checkof_line_mesh(PCMODELH model,PCVector3 startpos, PCVector3 endpos,
																		PCMATRIX world,float distance,PFLOAT outdis);

		//-------------------------------------------------------------------------------------------
		//�l�Ń��f���Ƃ̂x�̍��������߂�(�ۗ�)
		//-------------------------------------------------------------------------------------------
		//__IMPOETER VECTOR3 GetAtackSlantingPos(ATACKH at,D3DXVECTOR3 pos, int idx,int atacknum);

		//-------------------------------------------------------------------------------------------------------------------------------
		//�~���m�̓����蔻��
		//-------------------------------------------------------------------------------------------------------------------------------
		//@in : �~�`�̒��S���W
		//@in : �~�a�̒��S���W
		//@in : �~�`�̔��a
		//@in : �~�a�̔��a
		//@out : ����
		//@in : true(2D) false(3D)
		//@out : true(�������Ă���) false(�������Ă��Ȃ�)
		__IMPOETER bool Check_circle_obobject(RCVector3 cirA,RCVector3 cirB,float radiusA,float radiusB, PFLOAT outdistance,bool is2D = false);
		__IMPOETER bool Check_circle_obobject(RCVector2 cirA,RCVector2 cirB,float radiusA,float radiusB, PFLOAT outdistance);

		//--------------------------------------------------------------------------------------------------
		//�_�Ǝl�p�`�Ƃ̓����蔻��
		//--------------------------------------------------------------------------------------------------
		//@in : �_�̍��W
		//@in : �l�p�`�̍��W
		//@in : ��
		//@in : ����
		//@in : ���s��
		//@out : true(�������Ă���) false(�������Ă��Ȃ�)
		__IMPOETER bool point_boundingAtack(PCVector2 point, PCVector2 box,float wid,float hei);
		__IMPOETER bool point_boundingAtack(PCVector3 point,PCVector3 box,float wid,float hei,float tun);

		//-----------------------------------------------
		//�X�N���[���A�E�g
		//-----------------------------------------------
		//@in : �Ώۍ��W
		//@out : true(�������Ă���) false(�������Ă��Ȃ�)
		__IMPOETER bool Check_screenout(PCVector3 pos);
		__IMPOETER bool Check_screenout(PCVector2 pos);

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
		__IMPOETER bool Checkof_4thPoint_circle_atack(RCVector2 lup,RCVector2 rup,RCVector2 lbot,RCVector2 rbot,
																			RCVector2 pos, float pointWid, float circleWid);

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
		__IMPOETER bool Checkof_4thLine_circle_atack(RCVector2 lup, RCVector2 rup, RCVector2 lbot,
										RCVector2 rbot, RCVector2 pos, float pointWid, float circleWid);
		
		//-----------------------------------------------------------------------------------------------
		//�l�p�`�̓����ɂ��邩�ǂ������肷��
		//-----------------------------------------------------------------------------------------------
		//@in : ����̓_���W
		//@in : �E��̓_���W
		//@in : �����̓_���W
		//@in : �E���̓_���W
		//@in : �~�̍��W
		//@out : true(����) false(�O��)
		__IMPOETER bool Checkof_4thBox_circle_inAtack(RCVector2 p1,RCVector2 p2,RCVector2 p3,RCVector2 p4,
																			RCVector2 pos);
	};

}

#endif