#pragma once

//////////////////////////////////////////////////
//MYGAME
//////////////////////////////////////////////////
#include <ResourceFactory.h>

//////////////////////////////////////////////////
//NanairoProject
//////////////////////////////////////////////////
#include <Rule_anime.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	////////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------------
	//がいこつ拡大エフェクト
	void GainEffect::Init()
	{
		this->parts.scale.SetVector( 100, 100 );
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->SetWord("gain");

		this->spd.x = 20.0f;
		this->spd.y = SET_PI( 10.0f );
	}

	void GainEffect::Step()
	{
		this->IncrementFrameCnt(1, this->cntSpd);

		this->parts.scale.x += this->spd.x;
		this->parts.scale.y += this->spd.x;
		this->parts.color.FadeOut(5);

		this->Step_and_Checking();
	}
	
	////////////////////////////////////////////////////////////////////////////////
	//ソードアニメーションエフェクト
	void SwordEffect::Init()
	{
		this->SetSumCnt( "sword", 12 );

		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetMaxScreen();
		this->parts.color.SetMaxColor();

		this->intervalCnt = 5;
	}

	void SwordEffect::Step()
	{
		this->Step_and_Checking();
		this->parts.color.FadeOut(5);
	}

	void SwordEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	//-----------------------------------------------------------------------------
	//カッターエフェクト
	void BrustEffect::Init()
	{
		this->SetSumCnt( "brust", 10 );

		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetVector( SCRW, SCRH_PERCENT(0.5f) );
		this->parts.color.SetMaxColor();
	}

	void BrustEffect::Step()
	{
		this->Step_and_Checking();
		this->parts.color.FadeOut(5);
	}

	void BrustEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	//---------------------------------------------------------------------

	void CardChangeEffect_small::Init()
	{
		this->parts.scale.SetVector( 400, 400 );
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->word = "rotaYaji";

		this->spd.x = 20.0f;
		this->spd.y = SET_PI( 10.0f );
	}

	void CardChangeEffect_small::Step()
	{
		this->IncrementFrameCnt(1, this->cntSpd);
		this->parts.ang += this->spd.y;

		this->parts.color.FadeOut(5);
		this->Step_and_Checking();
	}
	
	//-----------------------------------------------------------------------------

	
}