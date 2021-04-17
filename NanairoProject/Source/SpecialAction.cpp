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

	//�����v��
	void JudgementCard::Special_cardAutoRevolution()
	{
		this->changeRevolution( !this->isRevolution() );
	}

	//�J�[�h�̖�����
	void JudgementCard::Special_cardDisables(Gest* point)
	{
		for(int i=0, siz=point->GetNowCardMax(), number, type; i<siz; i++)
		{
			number = point->trumps[i].GetCardNumber();
			type = point->trumps[i].GetCardType();
			//�X�y�R���N���[�o�[�R��
			if( number == 2 && type == CARD_SPADE )
			{
				point->trumps[i].SetCardType( CARD_CLOVER );
				this->Input_kirariEffect( point->trumps[i].parts.pos );
			}
			//�W���[�J�[���n�[�g�R��
			else if( type == CARD_JOCKER)
			{
				point->trumps[i].SetCardNumber( 2, CARD_HEART );
				this->Input_kirariEffect( point->trumps[i].parts.pos );
				if( point->GetPlayNumber() == 0 )
					point->trumps[i].ChangeDraw( CARD_STATUS_FRONT );
			}
			//8��7��,11��10��,
			else if( number == 7 || number == 10)
			{
				this->Input_kirariEffect( point->trumps[i].parts.pos );
				point->trumps[i].SetCardNumber( ( this->isJocker() ? number + 1 : number-1), type );
			}
		}
	}
	
	//down�l�ȏ�����ׂ�down�ȉ��̃J�[�h�ɕω�
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

	//up�l�ȉ������ׂ�up�ȏ�̃J�[�h�ɕω�
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

	//down���ޮ�����
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

	//�v������
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

	//��������
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

	//�����������炵
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

	//�������A
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

	//�S�����A
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

	//���Ԃ̃J�[�h��mid�ԍ���
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

	//�����K�E�Z
	void JudgementCard::action_specialCard(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		switch( this->specialRunkNum )
		{
		case 0:	//��x��
			this->action_specialCard_1st(p1st, p2nd, p3rd, p4th);
		break;
		case 1: //�x��
			this->action_specialCard_2nd(p1st, p2nd, p3rd, p4th);
			break;
		case 2:	//�n��
			this->action_specialCard_3rd(p1st, p2nd, p3rd, p4th);
			break;
		case 3:	//��n��
			this->action_specialCard_4th(p1st, p2nd, p3rd, p4th);
			break;
		}
	}

	//��x���̕K�E�Z
	void JudgementCard::action_specialCard_1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		//��x���̕K�E�Z
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

	//�x���̕K�E�Z
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

	//�n���̕K�E�Z
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

	//��n���̕K�E�Z
	void JudgementCard::action_specialCard_4th(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{	
		this->Special_4th( p1st, p2nd, p3rd, p4th );
	}

	//�G���X��x����
	//���ׂĂ̑��胋�[���J�[�h������
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

	//�G���X�x����
	//�Q���W���[�J�[�`�F���W
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

	//�䂢��x����
	//�V�ȏ�������_����
	void JudgementCard::Special_yui1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_down( ps[i], 6 );
		}
	}

	//�䂢�x����
	//���ԃJ�[�h���W��
	void JudgementCard::Special_yui2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardMidiam( ps[i], 7 );
		}
	}

	//�䂢�n��
	//�P�A�Q�̃J�[�h�������_����
	void JudgementCard::Special_yui3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_down( ps[i], 12 );
		}
	}
		
	//����x��
	//�P�O�ȉ��̃J�[�h��J�ȏ��
	void JudgementCard::Special_rin1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_up( ps[i], 9 );
		}
	}

	//���x��
	//������x�����ɉ�
	void JudgementCard::Special_rin2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th){}
	
	//���n��
	//7�ȉ��̃J�[�h��8�ȏ��
	void JudgementCard::Special_rin3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardDisables_up( ps[i], 6 );
		}
	}

	//����̑�x��
	//�����������炷
	void JudgementCard::Special_ayano1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardHalf( ps[i] );
		}
	}

	//����̕x��
	//�v������
	void JudgementCard::Special_ayano2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreateRevolution( ps[i] );
		}
	}

	//����̕n��
	//��������
	void JudgementCard::Special_ayano3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() == i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreateSame( ps[i] );
		}
	}

	//�t�B�I�i��x��
	//�S�����A
	void JudgementCard::Special_fiona1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreatePlusAll( ps[i] );
		}
	}

	//�t�B�I�i�x��
	//�����v��
	void JudgementCard::Special_fiona2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		this->Special_cardAutoRevolution();
	}

	//�t�B�I�i�n��
	//�������A
	void JudgementCard::Special_fiona3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th)
	{
		Gest* ps[] = { p1st, p2nd, p3rd, p4th };
		for(int i=0; i<this->playSum; i++)
		{
			if( this->GetNowPlayNum() != i && ps[i] != NULL && ps[i]->GetNowCardMax() > 0 )
				this->Special_cardCreatePlus( ps[i], 4 );
		}
	}
	
	//��n���͋���
	//���ԃJ�[�h���P�P��
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