#pragma once

//////////////////////////////////////////////////
//NanairoLib
//////////////////////////////////////////////////
#include <MainFunction.h>

//////////////////////////////////////////////////
//NanairoProject
//////////////////////////////////////////////////
#include <GestChara.h>
#include <PE_the_matchScene.h>

using namespace MYGAME;
using namespace NanairoLib;

namespace NanairoProject
{
	void Enemy::AIStep(JudgementCard& judgement)
	{
		if( judgement.frontCard.empty() )
			this->action_empty( judgement );

		if( !this->isBattle )
		{
			this->passing = true;
			if( !this->action_Standard( judgement ) )
			{
				( this->nowCardMax > 5 ?
					this->action_NormalAtack( judgement ) :
					this->action_PinchAtack( judgement ) );
			}
		}
	}

	bool Enemy::action_Standard(JudgementCard& judgement)
	{
		//-------------------------------------------------------------------
		//ジョーカー出てたらスペ３返し！これ共通
		if( !judgement.frontCard.empty() && judgement.frontCardSum == 1 && 
			judgement.frontCard[ judgement.nowCard ].isJocker() )
		{
			for(int i=0, siz=this->nowCardMax; i<siz; i++)
			{
				if( this->trumps[i].GetCardNumber() == 2 && 
					this->trumps[i].GetCardType() == CARD_SPADE )
				{
					this->isBattle = true;
					this->passing = false;
					this->trumps[i].SettingCardTouch();
					return true;
				}
			}
		}
		//-------------------------------------------------------------------

		return false;
	}

	void Enemy::action_NormalAtack(JudgementCard& judgement)
	{
		if( judgement.frontCard.empty() )
			this->action_empty( judgement );
		else
			this->action_onceCard( judgement );
	}

	void Enemy::action_PinchAtack(JudgementCard& judgement)
	{
		bool OKFlag = false;
		int i=0, tarGetNumber = judgement.frontCard[judgement.nowCard].GetCardNumber()- 1, 
			siz = this->trumps.size();
		switch( judgement.GetRulePower() )
		{
		case ENEMY_POWER_EASY:
			do
			{
				tarGetNumber++;
				for(i=0; i<siz; i++)
				{
					if( !this->trumps[i].isJocker() &&
						(judgement.isRevolution() ? 
						CHECK_TRUMP_BIGGER( tarGetNumber, this->trumps[i].GetCardNumber() ) :
						CHECK_TRUMP_SMALLER( tarGetNumber, this->trumps[i].GetCardNumber() ) )
						)//&& CHECK_TRUMP_ABS( tarGetNumber, this->trumps[i].GetCardNumber() ) == 1 )
					{
						this->isBattle = OKFlag = true;
						this->passing = false;
						tarGetNumber = this->trumps[i].GetCardNumber();

						this->sameOnSelect( judgement, i, tarGetNumber );
					}
					if( OKFlag )
						break;
				}
			}while( !OKFlag && i < siz);
			break;
		case ENEMY_POWER_NORMAL:
			break;
		}
	}

	void Enemy::action_empty(JudgementCard& judgement)
	{
		bool OKFlag = false;
		int tarGetNumber = 0, siz = this->trumps.size();
		switch( judgement.GetRulePower() )
		{
		case ENEMY_POWER_EASY:
			for(int i=0; i<siz; i++)
			{
				if( !this->trumps[i].isJocker() )
				{
					this->isBattle = OKFlag = true;
					this->passing = false;
					tarGetNumber = this->trumps[i].GetCardNumber();

					this->sameOnSelect( judgement, i, tarGetNumber );
				}
				else
				{
					if( this->nowCardMax < 3 ) 
					{
						this->isBattle = OKFlag = true;
						this->passing = false;
						this->trumps[i].SettingCardTouch();
						break;
					}
				}
				if( OKFlag )
					break;
			}
			break;
		case ENEMY_POWER_NORMAL:
			tarGetNumber = 6;
			do
			{
				tarGetNumber++;
				for(int i=0; i<siz; i++)
				{
					if( !this->trumps[i].isCardER() &&
						abs( tarGetNumber - this->trumps[i].GetCardNumber() ) == 1 )
					{
						this->isBattle = OKFlag = true;
						this->passing = false;
						tarGetNumber = this->trumps[i].GetCardNumber();

						this->sameOnSelect( judgement, i, tarGetNumber );
					}
					if( OKFlag )
						break;
				}
			}while( !OKFlag );
			break;
		}
	}

	void Enemy::action_onceCard(JudgementCard& judgement)
	{
		bool OKFlag = false;
		int i=0, tarGetNumber = judgement.frontCard[judgement.nowCard].GetCardNumber()- 1, 
			siz = this->trumps.size();
		switch( judgement.GetRulePower() )
		{
		case ENEMY_POWER_EASY:
			do
			{
				tarGetNumber++;
				for(i=0; i<siz; i++)
				{
					if( !this->trumps[i].isJocker() &&
					(judgement.isRevolution() ? 
					CHECK_TRUMP_BIGGER( tarGetNumber, this->trumps[i].GetCardNumber() ) :
					CHECK_TRUMP_SMALLER( tarGetNumber, this->trumps[i].GetCardNumber() ) )
						)//&& CHECK_TRUMP_ABS( tarGetNumber, this->trumps[i].GetCardNumber() ) == 1 )
					{
						this->isBattle = OKFlag = true;
						this->passing = false;
						tarGetNumber = this->trumps[i].GetCardNumber();

						this->sameOnSelect( judgement, i, tarGetNumber );
					}
					else if( this->trumps[i].isJocker() && 
						this->nowCardMax < 4 && judgement.frontCardSum == 1)
					{
						this->isBattle = OKFlag = true;
						this->passing = false;
						this->trumps[i].SettingCardTouch();
					}
					if( OKFlag )
						break;
				}
			}while( !OKFlag && i < siz);
			break;
		case ENEMY_POWER_NORMAL:
			break;
		}
	}

	//--------------------------------------------------------------------------

	void Enemy::sameOnSelect(JudgementCard& judgement, int i, int tarGetNumber)
	{
		this->trumps[i].SettingCardTouch();
		if( judgement.frontCardSum == 1 )	return ;

		int sum = 0;
		for(int j=i+1, siz = this->trumps.size(); j<siz; j++)
		{
			if( tarGetNumber == this->trumps[j].GetCardNumber() )
				this->trumps[j].SettingCardTouch();
			else
				break;

			if( ++sum + 1 >= judgement.frontCardSum )
				break;
		}
	}
}