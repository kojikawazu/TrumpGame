#pragma once

#ifndef _FSTREAM_
#include <fstream>
#endif

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>
#include <Rule_effect.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	void JudgementCard::Init()
	{
		power = ENEMY_POWER_EASY;
		this->foulFlag = this->gameStartFlag = false;
		this->frontCardSum = this->stateCardSum = this->nowCard = 
			this->playSum = this->nowPlayNumber = this->passCnt = this->winSum = 
			this->foulSum = this->gameCount = 0;
		this->rule = TRUMP_RULE_NOSTATUS;
		this->frontCard.clear();
		this->winnerList.clear();
		this->restrainsType.clear();
		this->inputRule = TRUMP_RULE_STANDARD;
		this->yourtornColor.SetMaxColor();
		this->yourtornColor.SettingFadeAlpha();
		this->specialCharaNum = this->specialRunkNum = 0;

		this->plateList.Init();
		this->runkList.Init();
		this->playerPlateList.Init();
		this->effectList.Init();
		this->yourtornAction = &JudgementCard::youtornFadeIn;	
	}

	void JudgementCard::Dispose()
	{
		this->_game = NULL;
		this->frontCard.clear();
		this->restrainsType.clear();
		this->winnerList.clear();
		this->plateList.Clear();
		this->runkList.Clear();
		this->playerPlateList.Clear();
		this->effectList.ListClear();
		this->roomData.charaData.clear();
		this->scoreMap.Dispose();
	}
	
	void JudgementCard::gameContinue()
	{
		this->foulFlag =  this->gameStartFlag = false;
		this->frontCardSum = this->stateCardSum = this->nowCard = 
			this->nowPlayNumber = this->passCnt = this->winSum = 
			this->foulSum = 0;
		this->rule = TRUMP_RULE_NOSTATUS;
		this->yourtornColor.SetMaxColor();
		this->yourtornColor.SettingFadeAlpha();
		this->gameCount++;

		this->frontCard.clear();
		this->winnerList.clear();
		this->restrainsType.clear();
		this->plateList.Init();
		this->runkList.Init();
		this->effectList.Init();
		this->playerPlateList.SetContinue();
		this->SettingNowPlayer();

		this->scoreMap.GetScoreAndRunk( this->roomData );
		this->yourtornAction = &JudgementCard::youtornFadeIn;
	}

	void JudgementCard::SettingNowPlayer()
	{
		int runker = this->playerPlateList.GetPlayNumber_runk4();
		this->nowPlayNumber = ( !runker ? 0 : runker - 1 );
	}

	void JudgementCard::SettingNowPlayer2()
	{
		int ruk = this->scoreMap.GetPlayerRunkNumber( this->playSum - 1 );
		if( ruk == -1 )	return ;
		else			this->nowPlayNumber = ruk;	
	}

	void JudgementCard::runkList_ofRewrite()
	{
		this->winnerList.clear();
		this->winnerList = this->runkList.GetRunk();
	}

	void JudgementCard::Step()
	{
		int siz = this->frontCard.size();
		for(int i=0; i<siz; i++)
			this->frontCard[i].Step();
		this->plateList.Step();
		this->runkList.Step();
		this->playerPlateList.Step();
		this->scoreMap.Step();

		if( !this->nowPlayNumber )
			(this->*yourtornAction)();

		this->plateList.Del();
	}

	void JudgementCard::effectStep()
	{
		this->effectList.Step();
		this->effectList.Del();
	}

	void JudgementCard::youtornFadeIn()
	{
		if( this->yourtornColor.FadeIn( 5.0f ) )
			this->yourtornAction = &JudgementCard::youtornFadeOut;
	}

	void JudgementCard::youtornFadeOut()
	{
		if( this->yourtornColor.FadeOut( 5.0f ) )
			this->yourtornAction = &JudgementCard::youtornFadeIn;
	}

	void JudgementCard::playNumberPlus(int plus)
	{	
		this->nowPlayNumber = (this->nowPlayNumber + plus ) % this->playSum;
		this->yourtornColor.SetAlpha(0);
		this->yourtornAction = &JudgementCard::youtornFadeIn;
	}

	void JudgementCard::playNumberManu(int plus)
	{
		this->nowPlayNumber = (this->nowPlayNumber + 4 - plus ) % 4;
		this->yourtornColor.SetAlpha(0);
		this->yourtornAction = &JudgementCard::youtornFadeIn;
	}

	void JudgementCard::cardSort(int in, int out)
	{
		TrumpCard tempC;
		NanairoLib::UIParts2D tempUI;
		Textcolor col;
		
		tempC = this->frontCard[in];
		this->frontCard[in] = this->frontCard[out];
		this->frontCard[out] = tempC;

		tempUI = this->frontCard[in].parts;
		this->frontCard[in].parts = this->frontCard[out].parts;
		this->frontCard[out].parts = tempUI;

		col = this->frontCard[in].parts.color;
		this->frontCard[in].parts.color = this->frontCard[out].parts.color;
		this->frontCard[out].parts.color = col;
	}

	void JudgementCard::cardSord_sounyu(int in, int out)
	{
		int tempX = (int)abs((this->frontCard[out].parts.pos.x - this->frontCard[out+1].parts.pos.x) * 0.5f);
		int offX = (int)abs((this->frontCard[out].offSet.x - this->frontCard[out+1].offSet.x) * 0.5f);

		TrumpCard tempC = this->frontCard[in];
		NanairoLib::UIParts2D tempUI = this->frontCard[in].parts;
		Textcolor col = this->frontCard[in].parts.color;

		for(int i=in; i<in+out; i++)
		{
			this->frontCard[i]				= this->frontCard[i+1];
			this->frontCard[i].parts		= this->frontCard[i+1].parts;
			this->frontCard[i].parts.color	= this->frontCard[i+1].parts.color;
		}

		this->frontCard[out] = tempC;
		this->frontCard[out].parts = tempUI;
		this->frontCard[out].parts.color = col;

		for(int i=in; i<in+out;i++)
		{
			this->frontCard[i+1].parts.pos.x = this->frontCard[i].parts.pos.x + tempX;
			this->frontCard[i+1].offSet.x = this->frontCard[i].offSet.x - offX;
		}
	}

	void JudgementCard::playerCardChange_input(Gest* p1, Gest* p2, Gest* p3, Gest* p4)
	{
		std::vector<Gest*> lis;
		lis.push_back( p1 );
		lis.push_back( p2 );
		if( p3 != NULL )	lis.push_back( p3 );
		if( p4 != NULL )	lis.push_back( p4 );

		this->playerCardChange( lis[ this->playerPlateList.GetPlayNumber_runk(1) - 1 ], 
								lis[ this->playerPlateList.GetPlayNumber_runk(2) - 1 ],
								( p3 != NULL ? lis[ this->playerPlateList.GetPlayNumber_runk(3) - 1 ] : NULL ),
								( p4 != NULL ? lis[ this->playerPlateList.GetPlayNumber_runk(4) - 1 ] : NULL ) );
	}

	void JudgementCard::playerCardChange(Gest* p1, Gest* p2, Gest* p3, Gest* p4)
	{
		switch( this->playSum )
		{
			case 4:
				this->cardChange( p1, p4, 2);
				this->cardChange( p2, p3, 1);
				break;
			case 3:
				this->cardChange( p1, p3, 2);
				break;
			case 2:
				this->cardChange( p1, p2, 2);
				break;
		}
	}

	void JudgementCard::cardChange(Gest* p1, Gest* p2, int count)
	{
		TrumpCard tempC;
		NanairoLib::UIParts2D tempUI;
		Textcolor col;

		for(int i=0, siz = p2->trumps.size()-1; i<count; i++)
		{
			tempC = p2->trumps[i];
			p2->trumps[i] = p1->trumps[ siz - i ];
			p1->trumps[ siz - i ] = tempC;

			tempUI = p2->trumps[i].parts;
			p2->trumps[i].parts = p1->trumps[ siz - i ].parts;
			p1->trumps[ siz - i ].parts = tempUI;

			col = p2->trumps[i].parts.color;
			p2->trumps[i].parts.color = p1->trumps[ siz - i ].parts.color;
			p1->trumps[ siz - i ].parts.color = col;

			p1->trumps[ siz - i ].SetFadeIn( p1->GetPlayNumber() );
			p2->trumps[ i ].SetFadeIn( p2->GetPlayNumber() );
		}
	}

	void JudgementCard::playerCardChange_fadeIn(Gest* p1, Gest* p2, Gest* p3, Gest* p4)
	{
		std::vector<Gest*> lis;
		lis.push_back( p1 );
		lis.push_back( p2 );
		if( p3 )	lis.push_back( p3 );
		if( p4 )	lis.push_back( p4 );

		for( int i=0, siz=lis.size(); i<siz; i++ )
			this->playerCardFadeIn( lis[ this->playerPlateList.GetPlayNumber_runk(i+1) - 1 ], i+1 );
	}
	
	void JudgementCard::playerCardFadeIn(Gest* p1, int count)
	{
		int siz = p1->GetNowCardMax();
		switch( count )
		{
		case 4:
			if( this->playSum > 1 )
			{
				p1->trumps[0].SetFadeOut();
				p1->trumps[1].SetFadeOut();
			}
			break;
		case 3:
			if( this->playSum > 3 )
				p1->trumps[0].SetFadeOut();
			break;
		case 2:
			if( this->playSum > 3 )
				p1->trumps[siz-1].SetFadeOut();
			break;
		case 1:
			if( this->playSum > 1 )
			{
				p1->trumps[siz-1].SetFadeOut();
				p1->trumps[siz-2].SetFadeOut();
			}
			break;
		}
	}

	bool JudgementCard::checkPassCount()
	{
		//(人数ー抜けた人数ー１)がリセットする基準
		if( this->passCnt == this->playSum - this->winSum - this->foulSum - 1 )
		{
			this->passCnt = 0;
			this->reSet_toRule();
			return true;
		}
		else
			return false;
	}

	void JudgementCard::reSet_toRule()
	{
		if( isSame() )
			changeSame( false );
		if( isStairs() )
		{
			changeStairs( false );
			plateList.Pop( TRUMP_RULE_STAIRS );
		}
		if( isRestrains() )
		{
			changeRestrains( false );
			plateList.Pop( TRUMP_RULE_RESTRAINS );
			restrainsType.clear();
		}
		if( isElevenback() )
		{
			changeElevenback( false );
			plateList.Pop( TRUMP_RULE_ELEVENBACK );
		}
		if( isSpade3() )
		{
			changeSpade3( false );
			plateList.Pop( TRUMP_RULE_SPADE3 );
		}
		if( isJocker() )
		{
			changeJocker( false );
			plateList.Pop( TRUMP_RULE_JOCKER );
		}
		frontCard.clear();
		frontCardSum = nowCard = 0;
	}

	void JudgementCard::WriteData()
	{
		std::fstream fs("./Resource/Data/GameData.gdata");
		this->roomData.roundCount = this->gameCount;

		if( fs.eof() || fs.fail() )	return ;

		fs.write( (char*)&this->roomData.rule,	sizeof(int) );
		fs.write( (char*)&this->roomData.rule2,	sizeof(int) );
		fs.write( (char*)&this->roomData.playSum,sizeof(int) );
		fs.write( (char*)&this->roomData.roundCount,sizeof(int) );

		for(int i=0;i<4;i++)
		{
			fs.write( (char*)&this->roomData.charaData[i].selectFlag,	sizeof(bool) );
			fs.write( (char*)&this->roomData.charaData[i].poreFlag,		sizeof(bool) );
			fs.write( (char*)&this->roomData.charaData[i].charaNum,		sizeof(int) );
			fs.write( (char*)&this->roomData.charaData[i].spec,			sizeof(int) );
			fs.write( (char*)&this->roomData.charaData[i].score,		sizeof(int) );
			fs.write( (char*)&this->roomData.charaData[i].runk,			sizeof(int) );
		}
	}

	void JudgementCard::push_winner(Gest* gest, int number)
	{
		bool isFoul = gest->isFoul();
		gest->SetWinnerNumber( (isFoul ? this->playSum - this->foulSum++ - 1: ++this->winSum) );
		this->winnerList.push_back( number );
		this->passCnt--;
		this->runkList.Push( number, (isFoul ? this->playSum - this->foulSum: this->winSum - 1) );
		this->playerPlateList.Push( number, (isFoul ? this->playSum - this->foulSum: this->winSum - 1) );	
	}

	void JudgementCard::Draw2D()
	{		
		this->youtornDraw();

		for(int i=this->nowCard; i<this->nowCard + this->frontCardSum; i++)
			this->frontCard[i].Draw2D();

		this->playerPlateList.Draw2D();
		this->runkList.Draw2D();
		this->plateList.Draw2D();
		this->scoreMap.Draw();
	}

	void JudgementCard::youtornDraw()
	{
		if( !this->nowPlayNumber && this->gameStartFlag )
		{
			Text2DFactory* gh = __GRAPHFACTORY;
			gh->draw_SetTrans(D3DXVECTOR2( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.65f) ),
				D3DXVECTOR2(200,100), 0.0f, "yourtorn" , DIRECT_SCALE, this->yourtornColor.color );
			gh->draw_graph();
		}
	}
}