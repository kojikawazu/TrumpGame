#pragma once

///////////////////////////////////////////
//MYGAME
#include <ResourceFactory.h>
#include <UseEffect.h>
using namespace NanairoLib;

///////////////////////////////////////////
//
//使うだろうエフェクトを定義して
//再利用化できるようにしよう。
//
///////////////////////////////////////////

namespace MYGAME
{
	////////////////////////////////////////////////////////////////////////////////
	//切りエフェクト
	void CutEffect::Init()
	{
		this->SetSumCnt( "kiriEfect", 9 );
		this->intervalCnt = 2;

		this->parts.color.SetMaxColor();	
		this->SetNormalMode();
		this->SetDirection( 0 );
	}

	void CutEffect::SetNormalMode()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 1.5f, 1.5f );
	}

	void CutEffect::SetDirection(int directNum)
	{
		this->parts.ang = SET_PI( 45.0f + directNum * 90.0f );	
	}

	void CutEffect::Step()
	{
		this->Step_and_Checking();
	}

	void CutEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//万華鏡スクリーンエフェクト
	void KaleidoScopeScreenEffect::Init()
	{
		this->SetSumCnt( "kaleidoEfect", 8 );
		this->SetNormalMode();
		this->parts.color.SetMaxColor();
	}

	void KaleidoScopeScreenEffect::SetNormalMode()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetMaxScreen();
	}

	void KaleidoScopeScreenEffect::Step()
	{
		this->Step_and_Checking();
		this->parts.color.FadeOut(2);
	}

	void KaleidoScopeScreenEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//矢印エフェクト
	void ArrowEffect::Init()
	{
		this->parts.scale.SetVector( 300, 300 );
		this->SetWord( "yajirusi" );
	}
	
	void ArrowEffect::SetObject(int number)
	{
		switch( yajiNum = number )
		{
		case 0:
			this->spd.SetVector(0,-10);
			this->parts.pos.SetVector( SCRW_PERCENT(0.7f), SCRH );
			this->parts.color.SetColor(255,255,0,0);
			break;
		case 1:
			this->spd.SetVector(0,10);
			this->parts.pos.SetVector( SCRW_PERCENT(0.3f), 0.0f );
			this->parts.color.SetColor(255,0,0,255);
			this->parts.ang = SET_PI(180.0f);
			break;
		}
	}

	void ArrowEffect::SetYajirusiMove(NanairoLib::RVector2 dspd, NanairoLib::RVector2 dpos, NanairoLib::RVector4 dcol)
	{
		this->spd.SetVector(dspd.x, dspd.y);
		this->parts.pos.SetVector(dpos.x, dpos.y);
		this->parts.color.SetColor((int)dcol.x, (int)dcol.y, (int)dcol.z, (int)dcol.w);
	}

	void ArrowEffect::Step()
	{
		this->IncrementFrameCnt(1, this->cntSpd);

		this->parts.pos.Add( this->spd );
		this->parts.color.FadeOut(4);

		this->Step_and_Checking();
	}

	void ArrowEffect::Draw2D()
	{
		Vector2 dpos = this->parts.pos;

		for(int i=0; i<5; i++)
		{
			this->Action_draw();
			( !this->yajiNum ? this->parts.pos.y += 300.0f : this->parts.pos.y -= 300.0f );
		}

		this->parts.pos = (Vector2)dpos;
	}

	////////////////////////////////////////////////////////////////////////////////
	//伸ばし鎖エフェクト素材
	void LongChainEffect::Init()
	{
		this->parts.scale.SetVector( 2000, 600 );
		this->SetWord("longChain");
	}
	
	void LongChainEffect::SetObject(int number)
	{
		switch( yajiNum = number )
		{
		case 0:
			this->spd.SetVector( cos(SET_PI(225)) * 30.0f , -sin(SET_PI(225)) * 30.0f );
			this->parts.pos.SetPercentVector( 1.8f, -0.8f );
			this->parts.ang = SET_PI(135.0f);
			break;
		case 1:
			this->spd.SetVector( -cos(SET_PI(225)) * 30.0f , -sin(SET_PI(225)) * 30.0f );
			this->parts.pos.SetPercentVector( -0.8f, -0.8f );
			this->parts.ang = SET_PI(45.0f);
			break;
		case 2:
			this->spd.SetVector( cos(SET_PI(225)) * 30.0f , sin(SET_PI(225)) * 30.0f );
			this->parts.pos.SetPercentVector( 1.8f, 1.8f );
			this->parts.ang = SET_PI(45.0f);
			break;
		case 3:
			this->spd.SetVector( -cos(SET_PI(225)) * 30.0f , sin(SET_PI(225)) * 30.0f );
			this->parts.pos.SetPercentVector( -0.8f, 1.8f );
			this->parts.ang = SET_PI(135.0f);
			break;
		}
	}

	void LongChainEffect::SetMove(NanairoLib::RVector2 dspd, NanairoLib::RVector2 dpos, float dang)
	{
		this->spd.SetVector(dspd.x, dspd.y);
		this->parts.pos.SetVector(dpos.x, dpos.y);
		this->parts.ang = SET_PI(dang);
	}

	void LongChainEffect::Step()
	{
		this->parts.pos.Add( this->spd );
		if( this->IncrementFrameCnt(30, this->cntSpd) )
			this->parts.color.FadeOut(5);

		this->Step_and_Checking();
	}

	void LongChainEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Action_draw();	
		gh->SetAlpha(BLEND_ALPHA1);
	}
	
	////////////////////////////////////////////////////////////////////////////////
	//回し鎖エフェクト素材
	void CircleChainEffect::Init()
	{
		this->parts.scale.SetVector( 200, 200 );
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->SetWord("circleChain");

		this->spd.x = 20.0f;
		this->spd.y = SET_PI( 10.0f );
	}

	void CircleChainEffect::Step()
	{
		this->parts.scale.x += this->spd.x;
		this->parts.scale.y += this->spd.x;
		this->parts.ang += this->spd.y;
		if( this->IncrementFrameCnt(30, this->cntSpd) )
			this->parts.color.FadeOut(5);
		this->Step_and_Checking();
	}

	void CircleChainEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Action_draw();	
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//波紋エフェクト素材
	void RippleEffect::Init()
	{
		this->parts.scale.SetVector( 50, 25 );
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->SetWord("donut");
		this->spd.SetVector( 50.0f, 25.0f );
	}

	void RippleEffect::Step()
	{
		if( this->isDel() )	return ;

		this->parts.scale.Add( this->spd );
		if( this->IncrementFrameCnt(5, this->cntSpd) )
		{
			if(this->parts.color.FadeOut(5))
				this->OnDel(true);
		}
	}

	void RippleEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Action_draw();	
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//スクリーン上でボールが移動するエフェクト素材
	void BallScreenMoveEffect::Init()
	{
		this->parts.scale.SetVector( 100, 100 );
		this->parts.pos.SetPercentVector( 0.5f, 0.0f );
		this->parts.ang = 0.0f;
		this->SetWord("ball");
		this->rotaCnt = 0;
		this->ChangeRota();
	}

	void BallScreenMoveEffect::ChangeRota()
	{
		float rnd = 0;
		switch(this->rotaCnt)
		{
			case 0:	rnd = 75;	break;
			case 1:	rnd = 215;	break;
			case 2: rnd = 0;	break;
			case 3:	rnd = 150;	break;
			case 4:	rnd = 290;	break;
		}

		rnd = SET_PI(rnd);
		this->spd.SetVector(cos((float)rnd) * 20, sin((float)rnd) * 20);
	}

	void BallScreenMoveEffect::Step()
	{
		this->parts.pos.Add( this->spd );

		bool hantei = false;
		switch( this->rotaCnt )
		{
			case 0:if( this->parts.pos.y >= SCRH)	hantei = true;	break;
			case 1:if( this->parts.pos.x <= 0.0f)	hantei = true;	break;
			case 2:if( this->parts.pos.x >= SCRW)	hantei = true;	break;
			case 3:if( this->parts.pos.y >= SCRH)	hantei = true;	break;
			case 4:if( this->parts.pos.y <= 0.0f)	hantei = true;	break;
		}

		if( hantei )
			( this->Increment(this->rotaCnt, 5 ) ? this->OnDel(true) : this->ChangeRota() );
	}

	void BallScreenMoveEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ADD1);
		this->Action_draw();	
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//こうもりアニメーションエフェクト
	void DevilEffect::Init()
	{
		this->SetSumCnt( "devil", 10 );

		this->parts.pos.SetVector( SCRW_PERCENT(0.1f) + rand() % (int)SCRW_PERCENT(0.9f),
									SCRH_PERCENT(0.1f)+ rand() % (int)SCRH_PERCENT(0.9f) );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.2f, 0.2f );
		this->parts.color.SetMaxColor();
	}

	void DevilEffect::SetObject(int number)
	{
		this->waitCnt = (number * 5);
	}

	void DevilEffect::Step()
	{
		if( this->waitCnt-- <= 0 )
		{
			this->Step_and_Checking();
			this->parts.color.FadeOut(5);
		}
	}

	void DevilEffect::Draw2D()
	{
		if( this->waitCnt > 0 ) return ;
		this->Same_draw();
	}

	////////////////////////////////////////////////////////////////////////////////
	//炎切りエフェクト
	void FireCutEffect::Init()
	{
		this->SetSumCnt( "fireEfect", 10 );

		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetMaxScreen();
		this->parts.color.SetColor( 200, 150, 50, 255 );
	}

	void FireCutEffect::SetObject(int num)
	{
		this->SetSumCnt( ( num ? "fireEfect" : "fireEfect2"), 10 );
	}

	void FireCutEffect::Step()
	{
		this->Step_and_Checking();
		this->parts.color.FadeOut(2);
	}

	void FireCutEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//キラリエフェクト
	void KirariEffect::Init()
	{
		this->SetSumCnt( "kirari", 10 );

		this->parts.pos.SetVector( SCRW_PERCENT(0.3f) + rand() % (int)SCRW_PERCENT(0.5f),
									SCRH_PERCENT(0.3f)+ rand() % (int)SCRH_PERCENT(0.5f) );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.2f, 0.2f );
		this->parts.color.SetMaxColor();
	}

	void KirariEffect::SetObject(int number)
	{
		this->waitCnt = (number * 10);
	}

	void KirariEffect::Step()
	{
		if( this->waitCnt-- <= 0 )
		{
			this->Step_and_Checking();
			this->parts.color.FadeOut(5);
		}
	}

	void KirariEffect::Draw2D()
	{
		if( this->waitCnt > 0 ) return ;
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//星エフェクト（普通）
	void StarEffect::Init()
	{
		this->parts.scale.SetVector( 200, 200 );
		this->parts.pos.SetVector( 0, 0 );
		this->parts.ang = 0.0f;
		this->SetSumCnt( "starEffect", 20 );
		this->intervalCnt -= 4;

		this->offSetSpd.SetMinVector();
	}

	void StarEffect::SetMoveAng(float rad)
	{
		this->parts.ang = rad;
		this->offSetSpd.x = cos( this->parts.ang ) * this->speed;
		this->offSetSpd.y = sin( this->parts.ang ) * this->speed;
		this->parts.ang = atan2(-this->offSetSpd.x, this->offSetSpd.y) - SET_PI(45.0f);
	}

	void StarEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}
	
	////////////////////////////////////////////////////////////////////////////////
	//星エフェクト（ランダムに外へ逃げていく）
	void RandomStarEffect::SetObject(NanairoLib::Vector2& vec, int spd)
	{
		this->parts.pos = (Vector2)vec;
		this->speed = spd;
		this->OKFlag = true;

		this->SetMoveAng(SET_PI( rand() % 360 ));
	}
		
	void RandomStarEffect::Step()
	{
		this->Step_and_Checking_repeat();
		NanairoLib::PUIParts2D pt = this->GetParts();
		pt->pos.x += this->offSetSpd.x;
		pt->pos.y += this->offSetSpd.y;
		pt->color.FadeOut(2);

		if( pt->color.color.x <= 0.0f )
			this->OnDel(true);
	}

	////////////////////////////////////////////////////////////////////////////////
	//星エフェクト（↓へ落ちてバウンドする）
	void DownStarEffect::SetObject(NanairoLib::Vector2& vec, int spd)
	{
		this->topSpd = 0;
		this->parts.pos = (Vector2)vec;
		this->speed = spd;
		this->OKFlag = true;

		this->SetMoveAng(SET_PI( 90 ));
		this->_action = &DownStarEffect::FirstDown;
	}
		
	void DownStarEffect::Step()
	{
		Vector2 old = this->parts.pos, moveVec;

		(this->*_action)();

		moveVec.SetVector(this->parts.pos.x - old.x, this->parts.pos.y - old.y);
		this->parts.ang = atan2(-moveVec.x, moveVec.y) - SET_PI(45.0f);;
	}

	void DownStarEffect::FirstDown()
	{
		this->Step_and_Checking_repeat();
		this->parts.pos.x += this->offSetSpd.x;
		this->parts.pos.y += this->offSetSpd.y + this->topSpd;
		
		this->topSpd++;
		if( this->parts.pos.y >= SCRH )
		{
			this->parts.pos.y = SCRH;
			this->SetMoveAng(SET_PI( 180 + rand() % 180 ));
			this->topSpd = -(rand() % 20) - 10;
			this->_action = &DownStarEffect::Topping;
		}
	}

	void DownStarEffect::Topping()
	{
		this->Step_and_Checking_repeat();
		this->parts.pos.x += this->offSetSpd.x;
		this->parts.pos.y += this->offSetSpd.y + this->topSpd;
		this->topSpd += 1;

		if( this->parts.pos.y >= SCRH )
			this->_action = &DownStarEffect::SecondDown;
	}
	
	void DownStarEffect::SecondDown()
	{
		this->Step_and_Checking_repeat();
		this->parts.pos.x += this->offSetSpd.x;
		this->parts.pos.y += this->offSetSpd.y + this->topSpd;
		if( this->parts.pos.y >= SCRH )
			this->OnDel(true);
	}

	////////////////////////////////////////////////////////////////////////////////
	//花火エフェクト
	void FireflowerEffect::SetObject(Vector2& vec)
	{
		this->parts.pos = (Vector2)vec;
		this->parts.pos.Add( -100.0f + rand() % 200, -100.0f + rand() % 200 );	
	}

	void FireflowerEffect::Init()
	{
		this->parts.scale.SetVector( 150, 150 );
		this->parts.pos.SetVector( 0, 0 );
		this->parts.ang = 0.0f;
		this->SetSumCnt( "FireflowerEffect", 14 );
	}

	void FireflowerEffect::Step()
	{
		this->Step_and_Checking();
		this->parts.color.FadeOut(5);
	}
	
	void FireflowerEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}
	
	////////////////////////////////////////////////////////////////////////////////
	//勝利エフェクト
	void ConfettiEffect::SetObject(Vector2& vec)
	{
		this->parts.pos = (Vector2)vec;
		this->OKFlag = true;

		this->parts.ang = 0.0f;
		this->offSetSpd.SetVector( 0.0f, this->parts.pos.x );
	}

	void ConfettiEffect::Init()
	{
		this->parts.scale.SetVector( 50, 50 );
		this->parts.pos.SetVector( 0, 0 );
		this->parts.ang = 0.0f;
		this->SetSumCnt( "Confetti", 13 );
		this->intervalCnt -= 4;

		this->offSetSpd.SetMinVector();
	}

	void ConfettiEffect::Step()
	{
		this->Step_and_Checking_repeat();

		this->parts.pos.x = this->offSetSpd.y + sin( this->offSetSpd.x ) * 20.0f;
		this->offSetSpd.x += SET_PI( 10.0f );
		this->parts.pos.y += 1.0f;
		
		if( this->parts.pos.y > SCRW_PERCENT(1.2f) )
			this->delFlag = true;
	}
	
	void ConfettiEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//星魔法エフェクト素材
	void MagicstarEffect::SetObject(Vector2& vec)
	{
		this->parts.pos = (Vector2)vec;
	}

	void MagicstarEffect::Init()
	{
		this->parts.scale.SetVector( 250, 250 );
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->SetSumCnt( "magictstarEffect", 15 );
		this->intervalCnt -= 2;
	}

	void MagicstarEffect::Step()
	{
		this->Step_and_Checking();
		this->parts.color.FadeOut(2);
	}
	
	void MagicstarEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA2);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}

	////////////////////////////////////////////////////////////////////////////////
	//マウス星エフェクト素材
	void MouseKirariEffect::Init()
	{
		this->SetSumCnt( "kirari", 10 );

		this->parts.pos.SetVector( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f) );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.2f, 0.2f );
		this->parts.color.SetColor(255,200,200,0);
	}

	void MouseKirariEffect::Step()
	{
		this->Step_and_Checking();
		this->parts.color.FadeOut(5);
	}

	void MouseKirariEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ADD1);
		this->Same_draw();
		gh->SetAlpha(BLEND_ALPHA1);
	}
}