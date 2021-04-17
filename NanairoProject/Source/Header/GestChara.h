#ifndef _NANAIRO_GEST_H
#define _NANAIRO_GEST_H

/////////////////////////////////////////
//std
/////////////////////////////////////////
#ifndef _VECTOR_
#include <vector>
#endif

/////////////////////////////////////////
//MYGAME
/////////////////////////////////////////
#ifndef _MYGAME_UIPARTS_H
#include <UIParts.h>
#endif

/////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////
#ifndef _NANAIRO_TRUMP_H
#include <TrumpCard.h>
#endif

namespace NanairoProject
{
	class JudgementCard;
	
	class Gest
	{
	protected:
		bool isBattle, passing, foulFlag;
		int nowCardMax, winnerNumber, playNumber;
		NanairoLib::UIParts2D parts;
		TrumpCard specialCard;

	public:
		std::vector<TrumpCard> trumps;
		
	private:
		void __Sort(int in, int out);

	public:
		Gest(){	this->Init();	}
		virtual ~Gest(){}

		virtual void Init();
		virtual void Step() = 0;
		virtual void Draw() = 0;

		void onFoul(){					this->foulFlag = true;	}
		void offFoul(){					this->foulFlag = false;	}
		bool isFoul(){					return this->foulFlag;	}
		bool isPass(){				return this->passing;	}
		bool isBattleMethod(){		return this->isBattle;	}
		
		TrumpCard* GetSpecialCard(){	return &this->specialCard;	}
		int GetPlayNumber(){	return this->playNumber;	}
		int GetNowCardMax(){		return this->nowCardMax;	}
		int GetWinnerNumber(){		return this->winnerNumber;	}
		void PlusNowCardMax(){		this->nowCardMax++;	}
		void ManuNowCardMax(){		this->nowCardMax--;	}
		void SetCardPos(int dplayer, int dban);
		void SetSpecialCardPos(int dplayer);
		void SetCardNumber(int dban, int dnumber);
		void SetPlayNumber(int dnum){	this->playNumber = dnum;	}
		void ChangeCardMax(int dplaymax);
		void SetPassing(bool isPass){	this->passing = isPass;	}
		void change_offBattle(){	this->isBattle = false;	}
		void SetWinnerNumber(int number){		this->winnerNumber = number;	}
		void SetPos(NanairoLib::RVector2 dpos){	this->parts.pos = (NanairoLib::Vector2)dpos;	}

		void playerContinue();
		void cardSort();
		void cardAllFadeIn();
		void cardStatusChange(int dstatus);
		void cardOnlyStep();
		void allDelCard();

		void trumpDraw();
	};

	class Player : public Gest
	{
	public:
		Player(){	this->Init();	}
		~Player(){}

		void Init(){	this->SetPlayNumber( 0 );	}
		void Step();
		void Draw(){	this->trumpDraw();			}

		void TrumpStep();
		void SetTouchActions();
	};

	class Enemy : public Gest
	{
	public:
		Enemy(){		this->Init();	}
		~Enemy(){}

		void Init(){}
		void Step();
		void Draw(){	this->trumpDraw();	}

		void AIStep(JudgementCard& judgement);
	private:
		
		bool action_Standard(JudgementCard& judgement);
		void action_NormalAtack(JudgementCard& judgement);
		void action_PinchAtack(JudgementCard& judgement);

		void action_empty(JudgementCard& judgement);
		void action_onceCard(JudgementCard& judgement);

		void sameOnSelect(JudgementCard& judgement, int i, int tarGetNumber);
	};
}

#endif