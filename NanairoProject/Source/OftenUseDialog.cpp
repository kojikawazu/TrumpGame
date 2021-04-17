#pragma once

/////////////////////////////////////////////
//NanairoLib
/////////////////////////////////////////////
#include <MainFunction.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <RoomScene.h>
#include <ChangeScene.h>
#include <Rule_effect.h>
#include <SelectRoomDialog.h>
#include <TrumpCard.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//-------------------------------------------------------------
	//たて看板型ダイアログ
	//-------------------------------------------------------------
	DownSignDialog::DownSignDialog()
	{
		this->Init();
	}

	DownSignDialog::~DownSignDialog(){}

	void DownSignDialog::Init()
	{
		this->roundNumber = 0;
		this->delFlag = false;
		this->parts.color.SettingFadeAlpha();
		
		this->SetObject( Vector2( SCRW_PERCENT(0.8f), -SCRH_PERCENT(0.1f) ), 0.0f, Vector2( SCRW_PERCENT(0.3f), SCRH_PERCENT(0.25f) ) );
		this->interval = 10;
		this->speed.SetVector( 0.0f, (this->parts.pos.y + SCRH_PERCENT(0.275f)) / this->interval );
		this->SetDialogName( "signs" );
	}
	
	void DownSignDialog::FadeIn()
	{
		this->parts.pos.y += this->speed.y;
		this->parts.color.FadeIn(255.0f/6);
		if( --this->interval <= 0 )	this->SetWait();
	}

	void DownSignDialog::FadeOut()
	{
		this->parts.pos.y -= this->speed.y;
		this->parts.color.FadeOut(255.0f/6);
		if( ++this->interval >= 6 )	
		{
			this->SetWait();
			this->delFlag = true;
		}
	}

	void DownSignDialog::Draw2D()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		Vector2 dpos;
		this->drawDialog();

		//-----------------------------------------------------------------------------
		//タグの描画
		//-----------------------------------------------------------------------------
		NumbersWord numbers;
		numbers.SetNumber( this->roundNumber );
		numbers.SetObject( &Vector2( _pt->pos.x, _pt->pos.y + this->parts.scale.y * 0.1f ), 
			_pt->ang, &Vector2( this->parts.scale.x * 0.4f + this->offSetScale.x, this->parts.scale.y * 0.4f + this->offSetScale.y ) );
		numbers.SetColor( this->parts.color.color );
		numbers.Draw2D();
	}
}