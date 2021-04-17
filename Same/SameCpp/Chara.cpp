#pragma once

//--------------------------------------------------------
//
//���ׂẴI�u�W�F�N�g�ɕK�v�Ȃ��̂��i�[����X�[�p�[�N���X
//
//--------------------------------------------------------
#include <Chara.h>
#include <DirectFunctionPlus.h>

namespace NanairoLib
{
	//-------------------------------------------------------------------------------------------------------------------
	//�Q�c�G�t�F�N�g�N���X
	//-------------------------------------------------------------------------------------------------------------------
	void Effect2D::SuperInitEffect2D()
	{
		this->cntSpd = 1;
	}

	void Effect2D::SetColor(NanairoLib::Textcolor& dcol)
	{
		this->parts.color = dcol;			
	}

	void Effect2D::SetObjectParts(NanairoLib::RVector2 dpos, float dang, NanairoLib::RVector2 dscl)
	{
		this->parts.pos = dpos;
		this->parts.ang = dang;
		this->parts.scale = dscl;
	}

	//-------------------------------------------------------------------------------------------------------------------
	//�R�c�L�����N���X
	//-------------------------------------------------------------------------------------------------------------------

	inline Chara3D::Chara3D() : scale(1.0f), angle(0.0f), atackCnt(0), resorceNum(0), moveMode(0), moveCnt(0) , 
							posi(D3DXVECTOR3()), oldposi(D3DXVECTOR3()), modelscale(D3DXVECTOR3()), world(D3DXMATRIX()),
							color(Textcolor())
	{							
		color.SetMaxColor();
	}

	inline Chara3D::~Chara3D(){}

	//--------------------------------------------
	//���[���h���W�̍X�V
	//--------------------------------------------
	//@in : DirectX�p�f�o�C�XS
	void Chara3D::UpdateWorld(PDirectDevice Device)
	{
		Direct3DFunc func;
		this->world = func.SetWorldPos(
			Device, posi, Vector3(0, angle, 0),
			Vector3(modelscale.x, modelscale.y, modelscale.z), 1, 0 );
	}
}