#pragma once

//////////////////////////////////////////////////
//NanairoLib
//////////////////////////////////////////////////
#include <MainFunction.h>

//////////////////////////////////////////////////
//NanairoProject
//////////////////////////////////////////////////
#include <GestChara.h>

using namespace MYGAME;
using namespace NanairoLib;

namespace NanairoProject
{
	void Gest::Init()
	{
		this->isBattle = this->passing = this->foulFlag = false;
		this->parts.pos.SetMinVector();
		this->parts.scale.SetVector(1,1);
		this->parts.ang = 0.0f;
		this->parts.color.SetColor(1,1,1,1);
		this->trumps.clear();
		this->nowCardMax = this->winnerNumber = 0;
	}

	void Gest::playerContinue()
	{
		this->SetWinnerNumber(0);
		this->offFoul();
	}

	void Gest::SetCardPos(int dplayer, int dban)
	{
		switch( dplayer )
		{
		case 0:
			this->trumps[dban].parts.pos.SetVector( 190.0f + dban * 35.0f, 500.0f );
			this->trumps[dban].parts.ang = 0.0f;
			break;
		case 1:
			this->trumps[dban].parts.pos.SetVector( 740.0f, 140.0f + dban * 20.0f );
			this->trumps[dban].parts.ang = 1.57f;
			break;
		case 2:
			this->trumps[dban].parts.pos.SetVector( 170.0f + dban * 20.0f, 50.0f );
			this->trumps[dban].parts.ang = 3.14f;
			break;
		case 3:
			this->trumps[dban].parts.pos.SetVector( 60.0f, 460.0f - dban * 20.0f );
			this->trumps[dban].parts.ang = 4.71f;
			break;
		}

		if( dplayer > 0)
		{
			this->trumps[dban].parts.scale.x *= 0.5f;
			this->trumps[dban].parts.scale.y *= 0.5f;
			this->trumps[dban].ChangeDraw( CARD_STATUS_BACK );
		}
	}

	void Gest::SetSpecialCardPos(int dplayer)
	{
		switch( dplayer )
		{
		case 0:
			this->specialCard.parts.pos.SetVector( 650.0f, 450.0f );
			this->specialCard.parts.ang = 0.0f;
			break;
		case 1:
			this->specialCard.parts.pos.SetVector( 640.0f, 140.0f );
			this->specialCard.parts.ang = 4.71f;
			break;
		case 2:
			this->specialCard.parts.pos.SetVector( 520.0f, 50.0f );
			this->specialCard.parts.ang = 3.14f;
			break;
		case 3:
			this->specialCard.parts.pos.SetVector( 60.0f, 160.0f );
			this->specialCard.parts.ang = 1.57f;
			break;
		}

		if( dplayer > 0)
		{
			this->specialCard.parts.scale.SetVector( 80.0f, 100.0f );
			this->specialCard.parts.scale.x *= 0.5f;
			this->specialCard.parts.scale.y *= 0.5f;
		}
	}
	
	void Gest::allDelCard()
	{
		for( int i=0, siz = this->trumps.size(); i<siz; i++ )
			this->trumps[i].ChangeDraw( CARD_STATUS_DES );
	}

	//------------------------------------------------
	//ユーザー数の変更
	//------------------------------------------------
	void Gest::ChangeCardMax(int dplaymax)
	{
		int cardsum = CARD_MAX_PLUSJOCKER / dplaymax;
		if( CARD_MAX_FILTER != 0 && cardsum > CARD_MAX_FILTER )
			cardsum = CARD_MAX_FILTER;

		this->nowCardMax = cardsum;
		this->trumps.clear();
		this->trumps.resize(cardsum);
	}

	//-----------------------------------------------
	//シャッフル後のカードセット
	//-----------------------------------------------
	void Gest::SetCardNumber(int dban, int dnumber)
	{
		if( dban >= 0 && dban < this->nowCardMax )
			this->trumps[dban].SetCardNumber( dnumber );
	}

	void Gest::trumpDraw()
	{
		int siz = this->trumps.size();
		for(int i=0; i<siz; i++)
			this->trumps[i].Draw2D();	

		this->specialCard.Draw2D();
	}

	void Gest::cardStatusChange(int dstatus)
	{
		for(int i=0, siz=this->trumps.size(), st; i<siz; i++)
		{
			st = this->trumps[i].GetCardStatus(); 
			if( st != CARD_STATUS_DES && st != dstatus )
				this->trumps[i].ChangeDraw( dstatus );
		}
	}

	void Gest::cardSort()
	{
		///////////////////////////////////////////////////////
		//並べ替える時はトランプデータとUIの構造体を入れ替える
		///////////////////////////////////////////////////////
		int tempI = this->nowCardMax, count = 0;

		//////////////////////////////////////////
		//まずはいらないカードを後ろに詰めて
		//////////////////////////////////////////
		for(int i=0; i<this->nowCardMax; i++)
		{
			//カウントしますね
			//そのデータが使用済み、かつ使用中済み添え字＞添え字だったら
			if( this->trumps[i].GetCardStatus() == CARD_STATUS_DES &&
				tempI > i)
			{
				for(int j=tempI-1; j>=0 && i<j;j--)
				{
					if( this->trumps[j].GetCardStatus() != CARD_STATUS_DES )
					{
						this->__Sort( i, j );
						tempI--;
						break;
					}
					else
						tempI--;
				}
			}
		}

		count = this->nowCardMax;
		for(int i=count-1; i>=0;i--)
		{
			if( this->trumps[i].GetCardStatus() == CARD_STATUS_DES )
				count--;
		}
		this->nowCardMax = count;

		int temp = 0;
		tempI--;
		this->nowCardMax = count;
		//////////////////////////////////////////
		//そして大きい数字に並べ替える
		//////////////////////////////////////////
		for(int i=0; i<this->nowCardMax; i++)
		{
			//比較対象Aがジョーカーなら飛ばして！
			if( this->trumps[i].isJocker() ||
				this->trumps[i].GetCardStatus() == CARD_STATUS_DES )
				continue;
			
			temp = i;
			for(int j=i+1; j<count; j++)
			{
				//比較対象Bがジョーカーなら確実に入れ替える
				if( this->trumps[j].isJocker() )
				{
					temp = j;
					break;
				}
				//大小表にのっとって！
				else if( TRUMP_POWER[ this->trumps[temp].GetCardNumber() ] < 
					TRUMP_POWER[ this->trumps[j].GetCardNumber() ] )
					temp = j;
				else
				{
					//ソート回す
				}
			}
			if( temp != i )
				this->__Sort( temp, i );
		}
	}

	void Gest::__Sort(int in, int out)
	{
		TrumpCard tempC;
		NanairoLib::UIParts2D tempUI;
		Textcolor col;

		tempC = this->trumps[in];
		this->trumps[in] = this->trumps[out];
		this->trumps[out] = tempC;

		tempUI = this->trumps[in].parts;
		this->trumps[in].parts = this->trumps[out].parts;
		this->trumps[out].parts = tempUI;

		col = this->trumps[in].parts.color;
		this->trumps[in].parts.color = this->trumps[out].parts.color;
		this->trumps[out].parts.color = col;
	}

	void Gest::cardOnlyStep()
	{
		int siz = this->trumps.size();
		for(int i=0; i<siz; i++)
			this->trumps[i].Step();
	}

	void Gest::cardAllFadeIn()
	{
		int siz = this->nowCardMax;
		for(int i=0; i<siz; i++)
			this->trumps[i].SetFadeInS();
	}

	///////////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------------//
	///////////////////////////////////////////////////////////////////////////////
	void Player::Step()
	{
		int siz = this->trumps.size();
		for(int i=0; i<siz; i++)
		{
			this->trumps[i].checkTouch();
			this->trumps[i].Step();
		}

		this->specialCard.checkTouch();
		this->specialCard.Step();

		//右クリック押したらバトル開始
		if( !this->isBattle )
		{
			MainFunction* MFunc = MainFunction::GetInstance();
			if( MFunc->GetKey()->GetMouse()->trg[ RBUTTON ] )
				this->isBattle = true;
			else if( MFunc->GetKey()->GetKey()->trg[ KX] )
				this->passing = true;
			
		}
	}

	void Player::TrumpStep()
	{
		int siz = this->trumps.size();
		for(int i=0; i<siz; i++)
		{
			if( this->trumps[i].GetMouseTouch() == CARD_TOUCHSTATUS_CLICK ||
				this->trumps[i].GetMouseTouch() == CARD_TOUCHSTATUS_TOUCH )
				this->trumps[i].SettingOffCardTouch();
			this->trumps[i].Step();
		}
	}

	void Player::SetTouchActions()
	{
		for(int i=0, siz=this->nowCardMax; i<siz; i++ )
			this->trumps[i].SetTouchActionS();
	}

	///////////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------------//
	///////////////////////////////////////////////////////////////////////////////
	void Enemy::Step()
	{
		int siz = this->trumps.size();
		for(int i=0; i<siz; i++)
			this->trumps[i].Step();

		this->specialCard.checkTouch();
		this->specialCard.Step();
	}
}