#pragma once

#include <MusicSound.h>
#include <MainFunction.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>
#include <Rule_effect.h>
#include <TemplateEffectList.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//ƒ‹[ƒ‹‚É‚æ‚è•Ï‰»‚ ‚è
	void JudgementCard::judgement_rule()
	{
		bool hantei = false;
		//-------------------------------------------------------------------
		//8‚«‚èÌ—pŽž‚É‚W‚«‚è‚ªs‚í‚ê‚½‚Æ‚«
		if( this->isEightcut() )
		{
			this->changeEightcut( false );
			this->push_ruleEffect( TRUMP_RULE_EIGHTCUT );
			this->plateList.Pop( TRUMP_RULE_EIGHTCUT );
			hantei = true;
		}
		//-------------------------------------------------------------------
		//“¯‚¶orŠK’ior”›‚è‰ðœ
		if( hantei )
			this->reSet_toRule();
	}

	void JudgementCard::SettingRule(int r1, int r2)
	{
		this->inputRule = r1;
		this->inputRule2 = r2;
		this->gameCount = this->roomData.roundCount;
	}

	void JudgementCard::push_ruleEffect(int rule)
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		switch( rule )
		{
		case TRUMP_RULE_EIGHTCUT:
			this->effectList.Add( new EightCutEffect() );
			this->plateList.Push( TRUMP_RULE_EIGHTCUT );
			se->Play("kiri");
			break;
		case TRUMP_RULE_ELEVENBACK:
			this->effectList.Add( new ElevenbackEffect() );
			se->Play("back");
			break;
		case TRUMP_RULE_RESTRAINS:
			this->effectList.Add( new RestrainsEffect() );
			this->plateList.Push( TRUMP_RULE_RESTRAINS );
			se->Play("shakin");
			break;
		case TRUMP_RULE_REVOLUTION:
			this->effectList.Add( new RevolutionEffect() );
			se->Play("shock");
			break;
		case TRUMP_RULE_STAIRS:
			this->effectList.Add( new StairsEffect() );
			this->plateList.Push( TRUMP_RULE_STAIRS );
			se->Play("brake");
			break;
		case TRUMP_RULE_SPADE3:
			this->effectList.Add( new Spade3Effect() );
			this->plateList.Push( TRUMP_RULE_SPADE3 );
			se->Play("fuwari");
			break;
		case TRUMP_RULE_JOCKER:
			this->effectList.Add( new JockerEffect() );
			this->plateList.Push( TRUMP_RULE_JOCKER );
			se->Play("ban");
			break;
		}
	}

	void JudgementCard::push_specialEffect(int specNum)
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		switch( specNum )
		{
		case CHARA_ERISU:
			this->effectList.Add( new ErisuSpecialEffect() );
			break;
		case CHARA_YUI:
			break;
		case CHARA_RIN:
			break;
		case CHARA_AYANO:
			break;
		case CHARA_FIONA:
			break;
		}
	}

	void JudgementCard::push_starEffect(int number)
	{
		TemplateEffectList<StarEffect*>* point = new TemplateEffectList<StarEffect*>();
		WinnerEffect* winner = new WinnerEffect();
		TemplateEffectList<FireflowerEffect*>* fire = new TemplateEffectList<FireflowerEffect*>();
		winner->SetObject( number );
		switch( number )
		{
			case 0:		
				point->SetObject( Vector2( SCRW_PERCENT(0.9f), SCRH_PERCENT(0.9f) ) );	
				fire->SetObject( Vector2( SCRW_PERCENT(0.7f), SCRH_PERCENT(0.7f) ) );
				break;
			case 1:	
				point->SetObject( Vector2( SCRW_PERCENT(0.9f), SCRH_PERCENT(0.1f) ) );	
				fire->SetObject( Vector2( SCRW_PERCENT(0.7f), SCRH_PERCENT(0.3f) ) );
				break;
			case 2:		
				point->SetObject( Vector2( SCRW_PERCENT(0.1f), SCRH_PERCENT(0.1f) ) );	
				fire->SetObject( Vector2( SCRW_PERCENT(0.3f), SCRH_PERCENT(0.3f) ) );
				break;
			case 3:		
				point->SetObject( Vector2( SCRW_PERCENT(0.1f), SCRH_PERCENT(0.9f) ) );	
				fire->SetObject( Vector2( SCRW_PERCENT(0.3f), SCRH_PERCENT(0.7f) ) );
				break;
			default:	
				point->SetObject( Vector2( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f) ) );
				fire->SetObject( Vector2( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f) ) );
		}
		this->effectList.Add( fire );
		this->effectList.Add( point );
		this->effectList.Add( winner );
	}

	void JudgementCard::push_foulEffect(int number, int foulNumber)
	{
		CapitalDownEffect* effect;
		FoulUpEffect* foul;
		switch( foulNumber)
		{
		case FOUL_CAPITALDOWN:
			effect = new CapitalDownEffect();
			effect->SetObject( number );
			this->effectList.Add( effect );
			break;
		case FOUL_FOULUP:
			foul = new FoulUpEffect();
			foul->SetObject( number );
			this->effectList.Add( foul );
			break;
		}
	}

	void JudgementCard::push_cardChangeEffect()
	{
		CardChangeEffect* ef = new CardChangeEffect();
		this->effectList.Add( ef );
	}

	void JudgementCard::pushPassEffect(int number)
	{
		PassingEffect* ef = new PassingEffect();
		ef->SetObject( number );
		this->effectList.Add( ef );
	}

	void JudgementCard::pushRoundStart(int round)
	{
		RoundStartEffect* effect = new RoundStartEffect();
		effect->SetRound( round );
		this->effectList.Add( effect );
	}
}