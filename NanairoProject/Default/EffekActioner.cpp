#pragma once

//MYGAME
//**************************************************************************
#include <EffekActioner.h>
using namespace NanairoLib;
//**************************************************************************

//--------------------------------------------------------------------------
//Effekseerのエフェクトを再生制御するクラス
//--------------------------------------------------------------------------

namespace MYGAME
{

	inline EffekActioner::EffekActioner(LPCSTR name) : 
		delFlag(false), moveFlag(false)
	{
		effName = (LPSTR)name;
		pos		= Vector3(0.0f,0.0f,0.0f);
		rota	= Vector3(0.0f,0.0f,0.0f);
		scale	= Vector3(1.0f,1.0f,1.0f);
		Axis	= Vector3(0.0f,0.0f,0.0f);
		this->SameInit();
	}

	inline EffekActioner::EffekActioner(LPCSTR name, PCVector3 pos, PCVector3 rota, PCVector3 scale) :
		delFlag(false), moveFlag(false)
	{
		effName = (LPSTR)name;
		this->pos.SetVector( (Vector3&)*pos );
		this->rota.SetVector( (Vector3&)*rota );
		this->scale = Vector3(scale->x, scale->y, scale->z);
		Axis = Vector3(0.0f,0.0f,0.0f);
		this->SameInit();
	}

	inline EffekActioner::~EffekActioner()
	{
		this->EfekStop();
	}

	inline void EffekActioner::DeleteOBJ()
	{
		delete this;
	}

	inline void EffekActioner::SameInit()
	{
		animationCnt = AxisMode = 0;
		this->drawEna = this->updateEna = true;
		this->moveFlag = this->delFlag = false;
	}

	inline void EffekActioner::SetPosi(PCVector3 pos){		(this->pos) = (pos);		}
	inline void EffekActioner::SetRota(PCVector3 rota){		(this->rota) = (rota);		}
	inline void EffekActioner::SetScale(PCVector3 scale){	(this->scale) = (scale);	}

	PVector3 EffekActioner::GetPosi() const{						return (PVector3 const)&this->pos;		}
	PVector3 EffekActioner::GetAngle() const{						return (PVector3 const)&this->rota;		}
	PVector3 EffekActioner::GetScale() const{						return (PVector3 const)&this->scale;	}

	//**************************************************************************
	//エフェクトの再生操作
	//**************************************************************************

	//-------------------------------------------------------------------------------
	//エフェクトのプレイ
	//-------------------------------------------------------------------------------
	void EffekActioner::EfekPlay()
	{
		this->handle = Effek EffektPlay( this->effName, &this->pos.SetD3DVector3() );
		( this->handle == -1 ? this->delFlag = true : this->moveFlag = true );
	}
	
	//------------------------------------------------------------------------------
	//エフェクトのプレイ中か
	//------------------------------------------------------------------------------
	bool EffekActioner::IsPlaying()
	{
		return ( Effek IsEffektHandle(handle) );
	}
	
	//------------------------------------------------------------------------------
	//エフェクトのストップ
	//------------------------------------------------------------------------------
	void EffekActioner::EfekStop()
	{
		PEffektManager mana = EffekseerClass::GetInstance()->GetManager();
		if( mana->Exists(handle) )	
			mana->StopEffect( this->handle );
	}

	//**************************************************************************

	//---------------------------------------------------------------------------------
	//エフェクトの位置等変更
	//---------------------------------------------------------------------------------
	void EffekActioner::ChangePosAngSclEffect()
	{
		( Effek IsEffektHandle(handle) ? this->moveFlag = true : this->delFlag = true );
	}

	//**************************************************************************
	//描画処理
	//**************************************************************************
	
	//---------------------------------------------------------------------------------
	//エフェクトの更新
	//---------------------------------------------------------------------------------
	void EffekActioner::EfekObjectUpdate()
	{
		EffekseerClass* efek = EffekseerClass::GetInstance();
		if( this->moveFlag && this->drawEna && efek->IsEffektHandle(handle))
			efek->EffektUpdateMatrix(this->handle, &this->pos.SetD3DVector3(), &this->rota.SetD3DVector3(), &this->scale.SetD3DVector3());
	}

	//---------------------------------------------------------------------------------
	//アップデートするかしないかを変える
	//---------------------------------------------------------------------------------
	void EffekActioner::ChangeUpdateEnable(bool isUpdate)
	{
		EffekseerClass* efek = EffekseerClass::GetInstance();
		if(efek->IsEffektHandle(handle))
		{
			this->updateEna = isUpdate;
			efek->SetUpdateEnable(this->handle, this->updateEna);
		}
		else
			this->delFlag = true;
	}

	//---------------------------------------------------------------------------------
	//描画するかしないか設定
	//---------------------------------------------------------------------------------
	void EffekActioner::ChangeDrawsEnable(bool isDraw)
	{
		EffekseerClass* efek = EffekseerClass::GetInstance();
		if(efek->IsEffektHandle(handle))
		{
			this->drawEna = isDraw;
			efek->SetUpdateEnable(this->handle, this->drawEna );
		}
		else
			this->delFlag = true;
	}
}