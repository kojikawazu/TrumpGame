#pragma once
#include <fstream>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>
#include <Rule_effect.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	void JudgementCard::Input_kirariEffect(NanairoLib::RVector2 vec)
	{
		MouseKirariEffect* ef = new MouseKirariEffect();
		ef->SetObject( vec );
		_game->GetEffectList()->Add( ef );
	}

	//自動革命
	void JudgementCard::Special_cardAutoRevolution()
	{
		this->changeRevolution( !this->isRevolution() );
	}

	//カードの無効化
	void JudgementCard::Special_cardDisables(Gest* point)
	{
		for(int i=0, siz=point->GetNowCardMax(), number, type; i<siz; i++)
		{
			number = point->trumps[i].GetCardNumber();
			type = point->trumps[i].GetCardType();
			//スペ３をクローバー３に
			if( number == 2 && type == CARD_SPADE )
			{
				point->trumps[i].SetCardType( CARD_CLOVER );
				this->Input_kirariEffect( point->trumps[i].parts.pos );
			}
			//ジョーカーもハート３に
			else if( type == CARD_JOCKER)
			{
				point->trumps[i].SetCardNumber( 2, CARD_HEART );
				this->Input_kirariEffect( point->trumps[i].parts.pos );
				if( point->GetPlayNumber() == 0 )
					point->trumps[i].ChangeDraw( CARD_STATUS_FRONT );
			}
			//8を7に,11を10に,
			else if( number == 7 || number == 10)
			{
				this->Input_kirariEffect( point->trumps[i].parts.pos );
				point->trumps[i].SetCardNumber( ( this->isJocker() ? number + 1 : number-1), type );
			}
		}
	}
	
	//down値以上をすべてdown以下のカードに変化
	void JudgementCard::Special_cardDisables_down(Gest* point, int down)
	{
		bool joc = this->isJocker();
		for(int i=0, siz=point->GetNowCardMax(), number, type, count=(joc ? 1 : 2); i<siz; i++)
		{
			number = point->trumps[i].GetCardNumber();
			type = point->trumps[i].GetCardType();
			if( type == CARD_JOCKER ) continue;
			if( (joc ? TRUMP_POWER[number] < TRUMP_POWER[down] : TRUMP_POWER[number] > TRUMP_POWER[down]) )
			{
				this->Input_kirariEffect( point->trumps[i].parts.pos );
				point->trumps[i].SetCardNumber( count, type );
				if( joc )
				{
					count = (count + (12)) % 13;
					if( count > 1 && count < down ) count = 1;
				}
				else
				{
					count = (count + 1) % down;
					if( count < 2) count = 2;
				}
			}
		}
	}

	//up値以下をすべてup以上のカードに変化
	void JudgementCard::Special_cardDisables_up(Gest* point, int up)
	{
		bool joc = !this->isJocker();
		for(int i=0, siz=point->GetNowCardMax(), number, type, count=(joc ? 1 : 2); i<siz; i++)
		{
			number = point->trumps[i].GetCardNumber();
			type = point->trumps[i].GetCardType();
			if( type == CARD_JOCKER ) continue;
			if( (joc ? TRUMP_POWER[number] < TRUMP_POWER[up] : TRUMP_POWER[number] > TRUMP_POWER[up]) )
			{
				this->Input_kirariEffect( point->trumps[i].parts.pos );
				point->trumps[i].SetCardNumber( count, type );
				if( joc )
				{
					count = (count + (12)) % 13;
					if( count > 1 && count < up ) count = 1;
				}
				else
				{
					count = (count + 1) % up;
					if( count < 2) count = 2;
				}
			}
		}
	}

	//down枚ｼﾞｮｰｶｰに
	void JudgementCard::Special_cardJocker(Gest* point, int down)
	{
		bool joc = this->isJocker();
		int siz = point->GetNowCardMax();
		for(int i=(joc ? siz-1 : 0), number, type, count=0; (joc ? i<siz : i>=0) && count<down; (joc ? i-- : i++), count++)
		{
			number = point->trumps[i].GetCardNumber();
			type = point->trumps[i].GetCardType();
			this->Input_kirariEffect( point->trumps[i].parts.pos );
			point->trumps[i].SetCardNumber( 0, CARD_JOCKER );
			if( point->GetPlayNumber() == 0 )
				point->trumps[i].ChangeDraw( CARD_STATUS_FRONT );
		}
	}

	//革命生成
	void JudgementCard::Special_cardCreateRevolution(Gest* point)
	{
		bool joc = this->isJocker();
		int siz = point->GetNowCardMax();
		if( siz < 4 )
		{
			this->Special_cardCreatePlus( point, 4 );
			int siz = point->GetNowCardMax();
		}
		int number = point->trumps[(joc ? siz-1 : 0)].GetCardNumber();
		int type = point->trumps[(joc ? siz-1 : 0)].GetCardType();
		for(int i=(joc ? siz-1 : 0), count=0; (joc ? i<siz : i>=0) && count<4; (joc ? i-- : i++), count++)
		{
			this->Input_kirariEffect( point->trumps[i].parts.pos );
			point->trumps[i].SetCardNumber( number , type );
			if( point->GetPlayNumber() == 0 )
				point->trumps[i].ChangeDraw( CARD_STATUS_FRONT );

			if( !joc )
				number = (number + (12)) % 13;
			else
				count = (count + 1) % 13;
		}
	}

	//同じ生成
	void JudgementCard::Special_cardCreateSame(Gest* point)
	{
		bool joc = this->isJocker();
		int siz = point->GetNowCardMax();
		for(int i=(joc ? siz-1 : 0), count=0, number, type; (joc ? i<siz : i>=0); (joc ? i-- : i++))
		{
			count = 0;
			number = point->trumps[i].GetCardNumber();
			type = point->trumps[i].GetCardType();
			for(int j=0; j<3 && (joc ? i<siz : i>=0); (joc ? i-- : i++), j++)
			{
				this->Input_kirariEffect( point->trumps[i].parts.pos );
				point->trumps[i].SetCardNumber( number , type );
				type = (type + 1) % 4;
			}
		}
	}

	//半分枚数減らし
	void JudgementCard::Special_cardHalf(Gest* point)
	{
		bool joc = this->isJocker();
		int siz = point->GetNowCardMax();
		int count = siz / 2;
		for(int i=(joc ? siz-1 : 0); (joc ? i<siz : i>=0) && count>=0; (joc ? i-- : i++), count--)
		{
			this->Input_kirariEffect( point->trumps[i].parts.pos );
			point->trumps[i].ChangeDraw( CARD_STATUS_DES );
			point->ManuNowCardMax();
		}
	}

	//少し復帰
	void JudgementCard::Special_cardCreatePlus(Gest* point, int plus)
	{
		int siz = point->GetNowCardMax(), size = point->trumps.size();
		if( siz >= size ) return ;

		for(int i=siz+1, count=0;i<size && count<plus; i++)
		{
			this->Input_kirariEffect( point->trumps[i].parts.pos );
			( point->GetPlayNumber() == 0 ?
				point->trumps[i].ChangeDraw( CARD_STATUS_FRONT ) :
				point->trumps[i].ChangeDraw( CARD_STATUS_BACK ) );
			point->PlusNowCardMax();
		}
	}

	//全部復帰
	void JudgementCard::Special_cardCreatePlusAll(Gest* point)
	{
		int siz = point->GetNowCardMax(), size = point->trumps.size();
		if( siz >= size ) return ;

		for(int i=siz+1; i<size; i++)
		{
			this->Input_kirariEffect( point->trumps[i].parts.pos );
			( point->GetPlayNumber() == 0 ?
				point->trumps[i].ChangeDraw( CARD_STATUS_FRONT ) :
				point->trumps[i].ChangeDraw( CARD_STATUS_BACK ) );
			point->PlusNowCardMax();
		}
	}

	//中間のカードをmid番号に
	void JudgementCard::Special_cardMidiam(Gest* point, int mid)
	{
		for(int i=0, siz=point->GetNowCardMax(), number, type; i<siz; i++)
		{
			number = point->trumps[i].GetCardNumber();
			type = point->trumps[i].GetCardType();
			if( type == CARD_JOCKER ) continue;
			if( TRUMP_POWER[number] >= TRUMP_POWER[4] && 
				TRUMP_POWER[number] <= TRUMP_POWER[9] )
			{
				point->trumps[i].SetCardNumber( mid, type );
				this->Input_kirariEffect( point->trumps[i].parts.pos );
			}
		}
	}

	//総合必殺技
	void JudgementCard::action_specialCard(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		switch( this->specialRunkNum )
		{
		case 0:	//大富豪
			this->action_specialCard_1st(p1st, p2nd, p3rd, p4th);
		break;
		case 1: //富豪
			this->action_specialCard_2nd(p1st, p2nd, p3rd, p4th);
			break;
		case 2:	//貧民
			this->action_specialCard_3rd(p1st, p2nd, p3rd, p4th);
			break;
		case 3:	//大貧民
			this->action_specialCard_4th(p1st, p2nd, p3rd, p4th);
			break;
		}
	}

	//大富豪の必殺技
	void JudgementCard::action_specialCard_1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		//大富豪の必殺技
		switch( this->specialCharaNum )
		{
		case CHARA_ERISU:
			this->Special_erisu1st( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_YUI:
			this->Special_yui1st( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_RIN:
			this->Special_rin1st( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_AYANO:
			this->Special_ayano1st( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_FIONA:
			this->Special_fiona1st( p1st, p2nd, p3rd, p4th );
			break;
		}
	}

	//富豪の必殺技
	void JudgementCard::action_specialCard_2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		
		switch( this->specialCharaNum )
		{
		case CHARA_ERISU:
			this->Special_erisu2nd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_YUI:
			this->Special_yui2nd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_RIN:
			this->Special_rin2nd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_AYANO:
			this->Special_ayano2nd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_FIONA:
			this->Special_fiona2nd( p1st, p2nd, p3rd, p4th );
			break;
		}
	}

	//貧民の必殺技
	void JudgementCard::action_specialCard_3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		switch( this->specialCharaNum )
		{
		case CHARA_ERISU:
			this->Special_erisu3rd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_YUI:
			this->Special_yui3rd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_RIN:
			this->Special_rin3rd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_AYANO:
			this->Special_ayano3rd( p1st, p2nd, p3rd, p4th );
			break;
		case CHARA_FIONA:
			this->Special_fiona3rd( p1st, p2nd, p3rd, p4th );
			break;
		}
	}

	//大貧民の必殺技
	void JudgementCard::action_specialCard_4th(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{	
		this->Special_4th( p1st, p2nd, p3rd, p4th );
	}

	//エリス大富豪版
	//すべての相手ルールカード無効化
	void JudgementCard::Special_erisu1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0)
				this->Special_cardDisables( ps[i] );
			if( i != 0 )
			{
				for(int j=0; j<ps[i]->GetNowCardMax(); j++)
					ps[i]->trumps[j].ChangeDraw( CARD_STATUS_BACK );
			}
		}
	}

	//エリス富豪版
	//２枚ジョーカーチェンジ
	void JudgementCard::Special_erisu2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardJocker( ps[i], 2 );
		}
	}

	void JudgementCard::Special_erisu3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		
	}

	//ゆい大富豪版
	//７以上をランダムに
	void JudgementCard::Special_yui1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_down( ps[i], 6 );
		}
	}

	//ゆい富豪版
	//中間カードを８に
	void JudgementCard::Special_yui2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardMidiam( ps[i], 7 );
		}
	}

	//ゆい貧民
	//１、２のカードをランダムに
	void JudgementCard::Special_yui3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_down( ps[i], 12 );
		}
	}
		
	//りん大富豪
	//１０以下のカードをJ以上に
	void JudgementCard::Special_rin1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_up( ps[i], 9 );
		}
	}

	//りん富豪
	//もう一度自分に回す
	void JudgementCard::Special_rin2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th){}
	
	//りん貧民
	//7以下のカードを8以上に
	void JudgementCard::Special_rin3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_up( ps[i], 6 );
		}
	}

	//あやの大富豪
	//半分枚数減らす
	void JudgementCard::Special_ayano1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardHalf( ps[i] );
		}
	}

	//あやの富豪
	//革命生成
	void JudgementCard::Special_ayano2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreateRevolution( ps[i] );
		}
	}

	//あやの貧民
	//同じ生成
	void JudgementCard::Special_ayano3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreateSame( ps[i] );
		}
	}

	//フィオナ大富豪
	//全部復帰
	void JudgementCard::Special_fiona1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreatePlusAll( ps[i] );
		}
	}

	//フィオナ富豪
	//自動革命
	void JudgementCard::Special_fiona2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		this->Special_cardAutoRevolution();
	}

	//フィオナ貧民
	//半分復帰
	void JudgementCard::Special_fiona3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreatePlus( ps[i], 4 );
		}
	}
	
	//大貧民は共通
	//中間カードを１１に
	void JudgementCard::Special_4th(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardMidiam( ps[i], 10 );
		}
	}

}