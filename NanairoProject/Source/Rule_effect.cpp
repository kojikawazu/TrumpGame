#pragma once
//////////////////////////////////////////////////
//MYGAME
//////////////////////////////////////////////////
#include <ResourceFactory.h>

//////////////////////////////////////////////////
//NanairoProject
//////////////////////////////////////////////////
#include <Rule_effect.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	void Rule_effect::Step_and_Checking()
	{
		if( this->IncrementFrameCnt( this->delCnt ) )
			this->delFlag = true;
	}

	void Rule_effect::super_ruleEffect()
	{
		this->stColor.SetMaxColor();
		this->offSet.SetMinVector();
		this->offSetSpd.SetVector(20, 16);
		this->fadeOutSpd = 10;
	}

	void Rule_effect::action_word()
	{
		//文字の拡大
		this->offSet.x += this->offSetSpd.x;
		this->offSet.y += this->offSetSpd.y;

		//フェードアウト
		this->parts.color.FadeOut( this->fadeOutSpd );
		this->stColor.FadeOut( this->fadeOutSpd * 0.5f);
	}

	void Rule_effect::Action_draw()
	{
		//フェードアウト文字
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos,
			D3DXVECTOR2( this->parts.scale.x + this->offSet.x,
							this->parts.scale.y + this->offSet.y), this->parts.ang,
							word.c_str() , DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();

		//文字
		gh->draw_SetTrans(this->parts.pos,
			this->parts.scale, this->parts.ang,
			word.c_str() , DIRECT_SCALE, this->stColor.color );
		gh->draw_graph();
	}

	//----------------------------------------------------------
	//8切りエフェクト
	//----------------------------------------------------------
	void EightCutEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.4f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "eightcut";

		this->smallEffect[0].Init();
		this->smallEffect[0].SetDirection(0);
	}

	void EightCutEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();

		//フェードのアクション
		this->action_word();

		//エフェクト（8切りミニ）のアクション
		for(int i=0; i<eightCutSmallSum; i++)
			this->smallEffect[i].Step();
	}

	void EightCutEffect::Draw2D()
	{
		this->Action_draw();

		//エフェクト
		for(int i=0; i<eightCutSmallSum; i++)
			this->smallEffect[i].Draw2D();
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//イレブンバックエフェクト
	//----------------------------------------------------------
	ElevenbackEffect::ElevenbackEffect()
	{
		this->yajirusi = new ArrowEffect[2];
		this->Init();
	}

	void ElevenbackEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.4f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "elevenback";

		this->smallEffect.Init();

		for(int i=0; i<2; i++)
		{
			this->yajirusi[i].Init();
			this->yajirusi[i].SetObject(i);
		}
	}

	void ElevenbackEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();

		//フェードのアクション
		this->action_word();
		this->smallEffect.Step();

		for(int i=0; i<2; i++)
			this->yajirusi[i].Step();
		
	}

	void ElevenbackEffect::Draw2D()
	{
		this->Action_draw();

		for(int i=0; i<2; i++)
			this->yajirusi[i].Draw2D();

		this->smallEffect.Draw2D();

	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//縛りエフェクト
	//----------------------------------------------------------
	RestrainsEffect::RestrainsEffect()
	{
		this->longChain = new LongChainEffect[LONGCHAIN_SUM];
		this->circleChain = new CircleChainEffect();
		this->Init();
	}

	RestrainsEffect::~RestrainsEffect()
	{
		ES_SAFE_DELETE_ARRAY( this->longChain );
		ES_SAFE_DELETE( this->circleChain );
	}

	void RestrainsEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.4f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->offSetSpd.SetVector( 30.0f, 26.0f );
		this->word = "restrains";

		this->circleChain->Init();

		for(int i=0; i<LONGCHAIN_SUM; i++)
		{
			this->longChain[i].Init();
			this->longChain[i].SetObject(i);
		}
	}

	void RestrainsEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();

		this->circleChain->Step();
		for(int i=0; i<LONGCHAIN_SUM; i++)
			this->longChain[i].Step();

	}

	void RestrainsEffect::Draw2D()
	{
		this->Action_draw();

		this->circleChain->Draw2D();
		for(int i=0; i<LONGCHAIN_SUM; i++)
			this->longChain[i].Draw2D();
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//革命エフェクト
	//----------------------------------------------------------
	RevolutionEffect::RevolutionEffect()
	{
		this->devilEffect = new DevilEffect[DEVIL_EFFECT_SUM];
		this->gainEffect = new GainEffect();
		this->Init();
	}

	RevolutionEffect::~RevolutionEffect()
	{
		ES_SAFE_DELETE_ARRAY( this->devilEffect );
		ES_SAFE_DELETE( gainEffect );
	}

	void RevolutionEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.4f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->offSetSpd.SetVector( 30.0f, 26.0f );
		this->word = "revolution";

		this->gainEffect->Init();
		for(int i=0; i<DEVIL_EFFECT_SUM; i++)
		{
			this->devilEffect[i].Init();
			this->devilEffect[i].SetObject(i);
		}
	}

	void RevolutionEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();

		this->gainEffect->Step();
		for(int i=0; i<DEVIL_EFFECT_SUM; i++)
			this->devilEffect[i].Step();
	}

	void RevolutionEffect::Draw2D()
	{
		for(int i=0; i<DEVIL_EFFECT_SUM; i++)
			this->devilEffect[i].Draw2D();
		this->Action_draw();
		this->gainEffect->Draw2D();
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//ジョーカーエフェクト
	//----------------------------------------------------------
	JockerEffect::JockerEffect()
	{
		this->fireEffect1 = new FireCutEffect[FIRE_EFFECT_SUM];
		this->Init();
	}

	JockerEffect::~JockerEffect()
	{
		ES_SAFE_DELETE_ARRAY(this->fireEffect1);
	}

	void JockerEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.4f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->offSetSpd.SetVector( 30.0f, 26.0f );
		this->word = "jockerEFF";

		for(int i=0; i<FIRE_EFFECT_SUM; i++)
		{
			this->fireEffect1[i].Init();
			this->fireEffect1[i].SetObject(i);
		}
	}

	void JockerEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();

		for(int i=0; i<FIRE_EFFECT_SUM; i++)
			this->fireEffect1[i].Step();
	}

	void JockerEffect::Draw2D()
	{
		for(int i=0; i<FIRE_EFFECT_SUM; i++)
			this->fireEffect1[i].Draw2D();

		this->Action_draw();
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//スペ３返しエフェクト
	//----------------------------------------------------------
	Spade3Effect::Spade3Effect()
	{
		this->swordEffect = new SwordEffect();
		this->kirariEffect = new KirariEffect[KIRARI_EFFECT_SUM];
		this->Init();
	}

	Spade3Effect::~Spade3Effect()
	{
		ES_SAFE_DELETE( this->swordEffect );
		ES_SAFE_DELETE_ARRAY(this->kirariEffect);
	}

	void Spade3Effect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.4f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "spade3";

		this->swordEffect->Init();

		for(int i=0; i<KIRARI_EFFECT_SUM; i++)
		{
			kirariEffect[i].Init();
			kirariEffect[i].SetObject(i);
		}
	}

	void Spade3Effect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();

		this->swordEffect->Step();
		for(int i=0; i<KIRARI_EFFECT_SUM; i++)
			kirariEffect[i].Step();
	}

	void Spade3Effect::Draw2D()
	{
		this->swordEffect->Draw2D();
		this->Action_draw();
		for(int i=0; i<KIRARI_EFFECT_SUM; i++)
			kirariEffect[i].Draw2D();
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//階段エフェクト
	//----------------------------------------------------------
	StairsEffect::StairsEffect()
	{
		this->brustEffect = new BrustEffect();
		this->Init();
	}

	StairsEffect::~StairsEffect()
	{
		ES_SAFE_DELETE( this->brustEffect );
	}

	void StairsEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.4f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "stairs";
		this->offSetSpd.SetVector( 30.0f, 26.0f );

		this->brustEffect->Init();
	}

	void StairsEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();

		this->brustEffect->Step();
	}

	void StairsEffect::Draw2D()
	{
		this->brustEffect->Draw2D();
		this->Action_draw();
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//パスエフェクト
	//----------------------------------------------------------
	void PassingEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.3f, 0.2f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "passing";
		this->offSetSpd.SetVector( 30.0f, 26.0f );
	}

	void PassingEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();
	}

	void PassingEffect::SetObject(int dnumber)
	{
		switch( dnumber )
		{
		case 0:
			this->parts.pos.SetPercentVector( 0.5f, 0.65f );
			break;
		case 1:
			this->parts.pos.SetPercentVector(0.85f, 0.5f );
			break;
		case 2:
			this->parts.pos.SetPercentVector(0.5f, 0.25f );
			break;
		case 3:
			this->parts.pos.SetPercentVector(0.15f , 0.5f );
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//勝利エフェクト
	//----------------------------------------------------------
	void WinnerEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.5f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "winnerName";
		this->offSetSpd.SetVector( 30.0f, 26.0f );
	}

	void WinnerEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();

		this->parts.scale.Add( 2.0f, 2.0f );
	}

	void WinnerEffect::SetObject(int dnumber)
	{
		switch( dnumber )
		{
		case 0:
			this->parts.pos.SetPercentVector( 0.75f, 0.75f );
			break;
		case 1:
			this->parts.pos.SetPercentVector( 0.75f, 0.25f );
			break;
		case 2:
			this->parts.pos.SetPercentVector( 0.25f, 0.25f );
			break;
		case 3:
			this->parts.pos.SetPercentVector( 0.25f, 0.75f );
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//都落ちエフェクト
	//----------------------------------------------------------
	void CapitalDownEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.5f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "capitalDown";
		this->offSetSpd.SetVector( 30.0f, 26.0f );
	}

	void CapitalDownEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();
	}

	void CapitalDownEffect::SetObject(int dnumber)
	{
		switch( dnumber )
		{
		case 0:
			this->parts.pos.SetPercentVector( 0.75f, 0.75f );
			break;
		case 1:
			this->parts.pos.SetPercentVector( 0.75f, 0.25f );
			break;
		case 2:
			this->parts.pos.SetPercentVector( 0.25f, 0.25f );
			break;
		case 3:
			this->parts.pos.SetPercentVector( 0.25f, 0.75f );
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//反則上がりエフェクト
	//----------------------------------------------------------
	void FoulUpEffect::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.5f, 0.5f );
		this->parts.color.SetMaxColor();
		this->super_ruleEffect();
		this->word = "foul";
		this->offSetSpd.SetVector( 30.0f, 26.0f );
	}

	void FoulUpEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();
	}

	void FoulUpEffect::SetObject(int dnumber)
	{
		switch( dnumber )
		{
		case 0:
			this->parts.pos.SetPercentVector( 0.75f, 0.75f );
			break;
		case 1:
			this->parts.pos.SetPercentVector( 0.75f, 0.25f );
			break;
		case 2:
			this->parts.pos.SetPercentVector( 0.25f, 0.25f );
			break;
		case 3:
			this->parts.pos.SetPercentVector( 0.25f, 0.75f );
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//ジョーカーエフェクト
	//----------------------------------------------------------
	void RoundStartEffect::Init()
	{
		this->super_ruleEffect();
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.8f, 0.5f );
		this->parts.color.SetMaxColor();
		this->stColor.SetMaxColor();
		
		this->word = "roundStart";
		this->offSetSpd.SetVector( 20.0f, 16.0f );
		this->delCnt = 200;
		this->fadeOutSpd = 3;

		this->roundNumber = 0;
		this->numbersWord.SetObject( &Vector2(SCRW_PERCENT(0.35f), SCRH_PERCENT(0.35f) ), 0.0f, &Vector2( 100, 100 ) );
	}

	void RoundStartEffect::Step()
	{
		//制限時間
		this->Step_and_Checking();
		this->action_word();
	}

	void RoundStartEffect::Draw2D()
	{
		this->Action_draw();

		if( this->roundNumber > 0 )
		{
			this->numbersWord.SetColor( this->parts.color.color );
			this->numbersWord.Draw2D();
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//カード交換エフェクト
	//----------------------------------------------------------
	void CardChangeEffect::Init()
	{
		this->super_ruleEffect();
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.8f, 0.5f );
		this->parts.color.SetMaxColor();
		this->stColor.SetMaxColor();
		
		this->word = "cardChange";

		this->changeEffect.Init();
	}

	void CardChangeEffect::Step()
	{
		this->changeEffect.Step();

		//制限時間
		this->Step_and_Checking();
		this->action_word();
	}

	void CardChangeEffect::Draw2D()
	{
		this->Action_draw();
		this->changeEffect.Draw2D();
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//スペシャルエフェクト
	//----------------------------------------------------------
	void SpecialEffect::SpecialInit()
	{
		this->slideSpd = 40.0f;
		this->specialInterval = 10;
		this->specialCnt = 0;
		this->charaWord = "";
		this->_SpecialAction = &SpecialEffect::SpecialFadeIn;
	}

	void SpecialEffect::SpecialFadeIn()
	{
		this->parts.pos.x += this->slideSpd;
		if( ++this->specialCnt >= this->specialInterval )
		{
			this->specialCnt = 0;
			this->_SpecialAction = &SpecialEffect::SpecialWait;
		}
	}

	void SpecialEffect::SpecialWait()
	{
		this->parts.pos.x += this->slideSpd * 0.1f;
		if( ++this->specialCnt >= 60 )
		{
			this->specialCnt = 0;
			this->_SpecialAction = &SpecialEffect::SpecialFadeOut;
		}
	}

	void SpecialEffect::SpecialFadeOut()
	{
		this->parts.pos.x += this->slideSpd;
		if( ++this->specialCnt >= this->specialInterval )
			this->delFlag = true;
	}

	void SpecialEffect::SpecialDraw()
	{
		//キャラ
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans( Vector2(this->parts.pos.x, this->parts.pos.y - 100.0f),
			this->parts.scale, this->parts.ang,
			this->charaWord , DIRECT_SCALE, this->stColor.color );
		gh->draw_graph();
	}

	//////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------
	//カード交換エフェクト
	//----------------------------------------------------------
	void ErisuSpecialEffect::Init()
	{
		this->super_ruleEffect();

		this->parts.pos.SetPercentVector( -0.1f, 0.6f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetPercentVector( 0.8f, 0.5f );
		this->parts.color.SetMaxColor();
		this->stColor.SetMaxColor();
		this->fadeOutSpd -= 5;
		this->charaWord = "erisu2";
		this->word = "erisu";
	}

	void ErisuSpecialEffect::Step()
	{
		this->SpecialStep();

		//制限時間
		this->action_word();
	}

	void ErisuSpecialEffect::Draw2D()
	{
		this->SpecialDraw();
		this->Action_draw();
	}
	//////////////////////////////////////////////////////////////////////////////////////
}