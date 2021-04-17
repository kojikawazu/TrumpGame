#pragma once

/////////////////////////////////////////////
//NanairoLib
/////////////////////////////////////////////
#include <string>
#include <MusicSound.h>
#include <MainFunction.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <RoomScene.h>
#include <ChangeScene.h>
#include <Rule_effect.h>
#include <TrumpCard.h>
#include <PE_the_matchScene.h>

using namespace NanairoLib;
using namespace MYGAME;

//------------------------------------------------
//セレクト画面で決めなきゃいけないことは
//１人対戦の場合、データ新規or既存 
//no
//プレイ人数
//キャラクター選択・コンピュータの強さ
//ルール
//------------------------------------------------

namespace NanairoProject
{
	RuleSelectRoom::RuleSelectRoom( MYGAME::SuperRoomScene* _pr, bool isSetData )
	{
		_parent = _pr;
		this->Init();
		if( isSetData )	
			this->inputRule( ((RoomScene*)(_parent))->GetRoomData()->rule, ((RoomScene*)(_parent))->GetRoomData()->rule2 );
	}

	void RuleSelectRoom::Init()
	{
		this->ruleSum = RULE_SUM;
		this->updownWord = "ok_se";
		this->okWord = "go_se";

		//-----------------------------------
		//スライドサイドダイアログの実装
		//-----------------------------------
		this->Input_SlidesideDialog();

		//-----------------------------------
		//スライドサイドダイアログの実装
		//-----------------------------------
		this->Input_LeftSlideDialog();

		//-----------------------------------
		//タイトルダイアログの実装
		//-----------------------------------
		this->Input_TittleDialog();

		//-----------------------------------
		//通知ダイアログの実装
		//-----------------------------------
		this->Input_NoticeDialog();

		this->SetFadeIn();
	}

	void RuleSelectRoom::Input_SlidesideDialog()
	{
		SlidesideDialog* point;
		this->dialogSum = (_parent->IsContinue() ? RULE_SELECTROOM_CONT_DIALOGSUM : RULE_SELECTROOM_NEW_DIALOGSUM );
		for(int i=0; i<this->dialogSum; i++)
		{
			point = new SlidesideDialog();
			point->SetDialogName( "dialog1" );

			switch( _parent->GetGameMode() )
			{
				case GAMEMODE_NEWGAME:		this->Input_SlidesideDialog_newGame(i, point);		break;
				case GAMEMODE_CONTINUEGAME:	this->Input_SlidesideDialog_continueGame(i, point);	break;
				case GAMEMODE_NETGAME:		this->Input_SlidesideDialog_netGame(i, point);		break;
			}

			point->SetNumber( i );
			this->dialogList.Add( point );
		}
	}
	
	void RuleSelectRoom::Input_SlidesideDialog_newGame(int i, SlidesideDialog* point)
	{
		switch( i )
		{
			case 0:	point->SetName( "gameStart" );		break;
			case 1:	point->SetName( "allSelect" );		break;
			case 2:	point->SetName( "backSelect" );		break;
			case 3:	point->SetName( "gobackTittle" );	break;
		}
	}

	void RuleSelectRoom::Input_SlidesideDialog_continueGame(int i, SlidesideDialog* point)
	{
		switch( i )
		{
			case 0:	point->SetName( "allSelect" );		break;
			case 1:	point->SetName( "backSelect" );		break;
		}
	}
	
	void RuleSelectRoom::Input_SlidesideDialog_netGame(int i, SlidesideDialog* point)
	{
		switch( i )
		{
			case 0:	point->SetName( "" );		break;
			case 1:	point->SetName( "allSelect" );		break;
			case 2:	point->SetName( "backSelect" );		break;
			case 3:	point->SetName( "gobackTittle" );	break;
		}
	}

	void RuleSelectRoom::Input_LeftSlideDialog()
	{
		SlidesideDialogLeft* leftpoint;
		for(int i=0; i<this->ruleSum; i++)
		{
			leftpoint = new SlidesideDialogLeft();
			leftpoint->SetName( RuleGraphNames[i] );
			leftpoint->SetNumber( i+this->dialogSum, this->dialogSum );

			this->dialogList.Add( leftpoint );
		}
	}
		
	void RuleSelectRoom::Input_TittleDialog()
	{
		ExpansionDialog* titleDialog = new ExpansionDialog();
		titleDialog->SetDialogName( "titleYousi" );
		titleDialog->SetName( "ruleSelect" );
		this->dialogList.Add( titleDialog );
	}

	void RuleSelectRoom::Input_NoticeDialog()
	{
		NoticeDialog* noticeDialog = new NoticeDialog();
		noticeDialog->SetPos(Vector2(SCRW_PERCENT(0.9f), SCRH_PERCENT(0.1f)));
		noticeDialog->SetMoveObject_ofScale( Vector2(SCRW_PERCENT(0.0f), SCRH_PERCENT(0.0f)), 
												Vector2(SCRW_PERCENT(0.2f), SCRH_PERCENT(0.2f)), 10 );
		noticeDialog->SetDialogName( "fuki" );
		noticeDialog->SetName( "pleasekey" );
		this->dialogList.Add( noticeDialog );
	}

	void RuleSelectRoom::Step()
	{
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++)
			(*it)->Step();	

		int selface = 0, count = 0, oldNum = this->selectNumber;
		if( this->KeyCheck( &selface ) )	return ;
		if( selface > 0 )	this->DialogChange( selface, oldNum );

		//----------------------------------------------------------------------
		//セレクトによるタグのオフセット値変更
		//----------------------------------------------------------------------
		this->AfterAction();
	}

	bool RuleSelectRoom::KeyCheck(int *selface)
	{
		int checkSum = (this->dialogSum + this->ruleSum);
		//-------------------------------------------------------------------------------------------
		//キーセレクト
		//-------------------------------------------------------------------------------------------
		if( __KEYDATA->trg[ KDOWN ] )
		{
			this->selectNumber = INCREMENT_SPECIAL(this->selectNumber, checkSum );
			*selface = 1;
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KUP ] )
		{
			this->selectNumber = DECREMENT_SPECIAL(this->selectNumber, checkSum );
			*selface = 2;
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KLEFT ] )
		{
			this->selectNumber = 0;
			*selface = 3;
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KRIGHT ] )
		{
			this->selectNumber = this->dialogSum;
			this->UpdownMusic();
			*selface = 4;
		}
		else if( __KEYDATA->trg[ KZ ] ||
			__MOUSEDATA->trg[LBUTTON] && this->MouseCheck() )
		{
			this->MoveAction();
			this->okMusic();
			return true;
		}
		else if( __MOUSEDATA->push[LBUTTON] && __MOUSEDATA->pushed[LBUTTON])
			this->MouseSlideCheck(selface);
		return false;
	}

	bool RuleSelectRoom::MouseCheck()
	{
		SlidesideDialog* slide;
		SlidesideDialogLeft* slideLeft;

		int count =0;
		int mouseX = __MOUSEDATA->mouseX, mouseY = __MOUSEDATA->mouseY;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count<this->dialogSum+this->ruleSum; it++, count++)
		{
			if( count < this->dialogSum)
			{
				slide = (SlidesideDialog*)(*it);
				if( slide-> IsAtack_boundingbox_centerBox( &Vector2((float)mouseX, (float)mouseY) ) )
				{
					this->selectNumber = count;
					return true;
				}
			}
			else if( count < this->dialogSum + this->ruleSum )
			{
				slideLeft = (SlidesideDialogLeft*)(*it);
				if( slideLeft-> IsAtack_boundingbox_centerBox( &Vector2((float)mouseX, (float)mouseY) ) )
				{
					this->selectNumber = count;
					return true;
				}
			}
		}
		return false;
	}

	bool RuleSelectRoom::MouseSlideCheck(int *selface)
	{
		if( this->selectNumber < this->dialogSum)
			this->selectNumber = this->dialogSum;

		Vector2 vec(0, (float)(__MOUSEDATA->mouseY - __MOUSEDATA->oldMouseY) );
		if( abs(vec.y) > 40 )
		{
			if( vec.y < 0 && this->selectNumber - 1 >= this->dialogSum)
			{
				this->selectNumber--;
				*selface = 2;
				this->UpdownMusic();
			}
			else if( this->selectNumber + 1 < this->dialogSum + this->ruleSum)
			{
				this->selectNumber++;
				*selface = 1;
				this->UpdownMusic();
			}
			return true;
		}
		return false;
	}

	void RuleSelectRoom::MoveAction()
	{
		switch( _parent->GetGameMode() )
		{
			case GAMEMODE_NEWGAME:		this->MoveAction_newGame();			break;
			case GAMEMODE_CONTINUEGAME:	this->MoveAction_continueGame();	break;
			case GAMEMODE_NETGAME:		this->MoveAction_netGame();			break;
		}
	}

	void RuleSelectRoom::MoveAction_newGame()
	{
		switch( this->selectNumber )
		{
			case 0:	this->gotoGame();			break;
			case 1:	this->AllSelect();			break;
			case 2:	this->goPlaySelectRoom();	break;
			case 3:	this->gobacktoTittle();		break;
			default:	this->EachOtherAction();
		}
	}
	
	void RuleSelectRoom::MoveAction_continueGame()
	{
		switch( this->selectNumber )
		{
			case 0:	this->AllSelect();			break;
			case 1:	this->goContinueRoom();		break;
			default:	this->EachOtherAction();
		}
	}
		
	void RuleSelectRoom::MoveAction_netGame()
	{
		switch( this->selectNumber )
		{
			case 0:				break;
			case 1:	this->AllSelect();			break;
			case 2:	this->goPlaySelectRoom();	break;
			case 3:	this->gobacktoTittle();		break;
			default:	this->EachOtherAction();
		}
	}

	void RuleSelectRoom::gotoGame()
	{
		this->OutputRule( &((RoomScene*)(_parent))->GetRoomData()->rule, &((RoomScene*)(_parent))->GetRoomData()->rule2 );
		_parent->SetYesnoDialog();
	}

	void RuleSelectRoom::goPlaySelectRoom()
	{
		this->OutputRule( &((RoomScene*)(_parent))->GetRoomData()->rule, &((RoomScene*)(_parent))->GetRoomData()->rule2 );
		_parent->SetChangeDialog( new PlayerSelectRoom( this->_parent ) );
	}

	void RuleSelectRoom::goContinueRoom()
	{
		this->OutputRule( &((RoomScene*)(_parent))->GetRoomData()->rule, &((RoomScene*)(_parent))->GetRoomData()->rule2 );
		_parent->SetChangeDialog( new ContinueRoom( this->_parent, false, false ) );
	}
		
	void RuleSelectRoom::gobacktoTittle()
	{
		_parent->SetChangeDialog( new SelectingRoom( this->_parent ) );
	}	

	void RuleSelectRoom::EachOtherAction()
	{
		int count = 0;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count < this->dialogSum+this->ruleSum; it++)
		{
			if( count++ >= this->dialogSum )
			{
				if( this->selectNumber == count-1 )
				{
					((SlidesideDialogLeft*)(*it))->onTouch();
					break;
				}
			}
		}
	}

	void RuleSelectRoom::DialogChange(int selface, int oldNum)
	{
		int count = 0;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count < this->dialogSum+this->ruleSum; it++)
		{
			if( count++ >= this->dialogSum )
			{
				switch ( selface ) 
				{
					case 1:
						( this->selectNumber > this->dialogSum ? 
						((SlidesideDialogLeft*)(*it))->upSelect() :
							((SlidesideDialogLeft*)(*it))->normalSelect() );
						break;
					case 2:
						if( oldNum == 0 && this->selectNumber == this->ruleSum + this->dialogSum - 1 )
							((SlidesideDialogLeft*)(*it))->specSelect();
						else
						{
							( this->selectNumber >= this->dialogSum ? 
							((SlidesideDialogLeft*)(*it))->downSelect() :
								((SlidesideDialogLeft*)(*it))->normalSelect() );
						}
						break;
					case 3:
						((SlidesideDialogLeft*)(*it))->normalSelect();
						break;
				}
			}
		}
	}

	void RuleSelectRoom::AfterAction()
	{
		int count = 0;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count < this->dialogSum+this->ruleSum; it++, count++)
		{
			if( count < this->dialogSum )
			{
				( this->selectNumber == count ? 
				((SlidesideDialog*)(*it))->onSelect() : ((SlidesideDialog*)(*it))->offSelect() );
			}
			else
			{
				( this->selectNumber == count ? 
				((SlidesideDialogLeft*)(*it))->onSelect() : ((SlidesideDialogLeft*)(*it))->offSelect() );
			}
		}
	}	

	void RuleSelectRoom::AllSelect()
	{
		int count = 0;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count < this->dialogSum + this->ruleSum; it++, count++)
		{
			 if( count >= this->dialogSum ) 
				 ((SlidesideDialogLeft*)(*it))->onTouch();
		}
	}

	void RuleSelectRoom::OutputRule(int* inputRule, int* inputRule2)
	{
		int count = 0;
		(*inputRule) = (*inputRule2) = 0;
		
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count < this->dialogSum+this->ruleSum; it++, count++)
		{
			if( count >= this->dialogSum )
			{
				if( ((SlidesideDialogLeft*)(*it))->isTouch() )
				{
					switch( count-this->dialogSum )
					{
						case 0:	*inputRule |= TRUMP_RULE_EIGHTCUT;		break;
						case 1:	*inputRule |= TRUMP_RULE_ELEVENBACK;	break;
						case 2:	*inputRule |= TRUMP_RULE_RESTRAINS;		break;
						case 3:	*inputRule |= TRUMP_RULE_REVOLUTION;	break;
						case 4:	*inputRule |= TRUMP_RULE_JOCKER;		break;
						case 5:	*inputRule |= TRUMP_RULE_SPADE3;		break;
						case 6:	*inputRule |= TRUMP_RULE_STAIRS;		break;
						
						case 7:	*inputRule2 |= TRUMP_RULE_CAPITALDOWN;	break;
						case 8:	*inputRule2 |= TRUMP_RULE_FOUL;			break;
						case 9: *inputRule2 |= TRUMP_RULE_CARDCHANGE;	break;
					}
				}
			}
		}
	}

	void RuleSelectRoom::inputRule(int inputRule, int inputRule2)
	{
		int count = 0;
		bool hantei = false;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count < this->dialogSum+this->ruleSum; it++, count++)
		{
		
			if( count >= this->dialogSum )
			{	
				hantei = false;
				switch( count-this->dialogSum )
				{
					case 0:		if( (inputRule & TRUMP_RULE_EIGHTCUT) > 0 )		hantei = true;	break;
					case 1:		if( (inputRule & TRUMP_RULE_ELEVENBACK) > 0 )	hantei = true;	break;
					case 2:		if( (inputRule & TRUMP_RULE_RESTRAINS) > 0 )	hantei = true;	break;
					case 3:		if( (inputRule & TRUMP_RULE_REVOLUTION) > 0 )	hantei = true;	break;
					case 4:		if( (inputRule & TRUMP_RULE_JOCKER) > 0 )		hantei = true;	break;
					case 5:		if( (inputRule & TRUMP_RULE_SPADE3) > 0 )		hantei = true;	break;
					case 6:		if( (inputRule & TRUMP_RULE_STAIRS) > 0 )		hantei = true;	break;
						
					case 7:		if( (inputRule2 & TRUMP_RULE_CAPITALDOWN) > 0 )		hantei = true;	break;
					case 8:		if( (inputRule2 & TRUMP_RULE_FOUL) > 0 )			hantei = true;	break;
					case 9:		if( (inputRule2 & TRUMP_RULE_CARDCHANGE) > 0 )		hantei = true;	break;
				}
				if( hantei )	((SlidesideDialogLeft*)(*it))->onTouch();
			}
			
		}
	}

	//-------------------------------------------------------------------------------
	//プレイヤー選択セレクト
	//-------------------------------------------------------------------------------
	PlayerSelectRoom::PlayerSelectRoom( MYGAME::SuperRoomScene* _pr, bool isSetData )
	{
		_parent = _pr;
		this->Init();
		if( isSetData )	this->control->InputRule( &((RoomScene*)(_parent))->GetRoomData()->charaData );

		//-----------------------------------
		//プレイヤーダイアログの実装
		//-----------------------------------
		this->control->Input_playerMapDialog(this->playerSum);
	}

	void PlayerSelectRoom::Init()
	{
		this->dialogSum = (_parent->IsContinue() ? PLAYER_SELECTROOM_CONT_DIALOGSUM : PLAYER_SELECTROOM_NEW_DIALOGSUM );
		this->waitCnt = 0;
		this->playerSum = (_parent->IsNetGame() ? 1 : PLAYER_MAX );
		this->updownWord = "ok_se";
		this->okWord = "go_se";

		this->_selectAction = &PlayerSelectRoom::select_normalAction;
		this->control = new PlayerMapControl((RoomScene*)this->_parent);
		this->control->Init(this->playerSum);

		//-----------------------------------
		//スライドサイドダイアログの実装
		//-----------------------------------
		this->Input_SlidesideDialog();

		//-----------------------------------
		//ボックス型ダイアログの実装
		//-----------------------------------
		this->Input_BoxDialog();

		//-----------------------------------
		//タイトルダイアログの実装
		//-----------------------------------
		this->Input_TittleDialog();

		//-----------------------------------
		//通知ダイアログの実装
		//-----------------------------------
		this->Input_NoticeDialog();

		this->SetFadeIn();
	}

	void PlayerSelectRoom::Input_SlidesideDialog()
	{
		SlidesideDialog* point;
		for(int i=0; i<this->dialogSum; i++)
		{
			point = new SlidesideDialog();
			point->SetDialogName( "dialog1" );

			switch( _parent->GetGameMode() )
			{
				case GAMEMODE_NEWGAME:		this->Input_SlidesideDialog_newGame(i, point);		break;
				case GAMEMODE_CONTINUEGAME:	this->Input_SlidesideDialog_continueGame(i, point);	break;
				case GAMEMODE_NETGAME:		this->Input_SlidesideDialog_netGame(i, point);		break;
			}
			point->SetNumber( i );

			this->dialogList.Add( point );
		}
	}

	void PlayerSelectRoom::Input_SlidesideDialog_newGame(int i, SlidesideDialog* point)
	{
		switch( i )
		{
			case 0:	point->SetName( "ruleSelect2" );break;
			case 1:	point->SetName( "allSelect" );	break;
			case 2:	point->SetName( "backSelect" );	break;
		}
	}

	void PlayerSelectRoom::Input_SlidesideDialog_continueGame(int i, SlidesideDialog* point)
	{
		switch( i )
		{
			case 0:	point->SetName( "allSelect" );	break;
			case 1:	point->SetName( "backSelect" );	break;
		}
	}
	
	void PlayerSelectRoom::Input_SlidesideDialog_netGame(int i, SlidesideDialog* point)
	{
		switch( i )
		{
			case 0:	point->SetName( "ruleSelect2" );break;
			case 1:	point->SetName( "allSelect" );	break;
			case 2:	point->SetName( "backSelect" );	break;
		}
	}

	void PlayerSelectRoom::Input_BoxDialog()
	{
		BoxExpansionDialog* box;
		for(int i=0; i<this->playerSum; i++)
		{
			box = new BoxExpansionDialog();
			box->SetNumber(i);
			box->SetName( (i==0 ? "playerName" : "computerName" ) );
			this->dialogList.Add( box );
		}
	}

	void PlayerSelectRoom::Input_TittleDialog()
	{
		ExpansionDialog* titleDialog = new ExpansionDialog();
		titleDialog->SetDialogName( "titleYousi" );
		titleDialog->SetName( "playerSelect" );
		this->dialogList.Add( titleDialog );
	}

	void PlayerSelectRoom::Input_NoticeDialog()
	{
		noticeDialog = new NoticeDialog();
		noticeDialog->SetPos(Vector2(SCRW_PERCENT(0.1f), SCRH_PERCENT(0.8f)));
		noticeDialog->SetMoveObject_ofScale( Vector2(SCRW_PERCENT(0.0f), SCRH_PERCENT(0.0f)), 
												Vector2(SCRW_PERCENT(0.2f), SCRH_PERCENT(0.2f)), 10 );
		noticeDialog->SetDialogName( "fuki" );
		noticeDialog->SetName( "pleasekey" );
	}

	void PlayerSelectRoom::Dispose()
	{
		this->dialogList.ListClear();
		ES_SAFE_DELETE( this->control );
		ES_SAFE_DELETE( this->noticeDialog );
	}

	void PlayerSelectRoom::FadeIn()
	{
		this->noticeDialog->Step();
		bool hantei = this->StandardStep();
		hantei = this->control->FadeIn();
		if( hantei )	this->SetStep();
	}

	void PlayerSelectRoom::select_normalAction()
	{
		//-------------------------------------
		//プレイヤーマップアクション
		//-------------------------------------
		if( this->PlayerMapAction() )	return ;

		//-------------------------------
		//キーセレクト
		//-------------------------------
		if( this->KeyCheck() )	return ;

		//-------------------------------------
		//セレクトによるタグのオフセット値変更
		//-------------------------------------
		this->AfterAction();
	}

	bool PlayerSelectRoom::MouseCheck()
	{
		FadeNameDialog* fade;
		int count =0;
		int mouseX = __MOUSEDATA->mouseX, mouseY = __MOUSEDATA->mouseY;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count<this->dialogSum+this->playerSum; it++, count++)
		{
			if( count < this->dialogSum + this->playerSum)
			{
				fade = (FadeNameDialog*)(*it);
				if( fade-> IsAtack_boundingbox_centerBox( &Vector2((float)mouseX, (float)mouseY) ) )
				{
					this->selectNumber = count;
					return true;
				}
			}
		}
		return false;
	}

	bool PlayerSelectRoom::KeyCheck()
	{
		if( this->waitCnt > 0 )
		{
			if( ++this->waitCnt > 5 )	this->waitCnt = 0;
			else						return true;
		}

		bool hantei = false;
		int checkSum = (this->dialogSum + this->playerSum), oldNum = this->selectNumber, count = 0;
		this->oldSelectNumber = this->selectNumber;
		
		if( __KEYDATA->trg[ KDOWN ] )
		{
			this->selectNumber = INCREMENT_SPECIAL( this->selectNumber, checkSum );
			hantei = true;
			this->waitCnt = 1;
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KUP ] )
		{
			this->selectNumber = DECREMENT_SPECIAL( this->selectNumber, checkSum );
			hantei = true;
			this->waitCnt++;
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KLEFT ] )
		{
			this->selectNumber = 0;
			hantei = true;
			this->waitCnt++;
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KRIGHT ] )
		{
			this->selectNumber = this->dialogSum;
			hantei = true;
			this->waitCnt++;
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KZ ] ||
			(__MOUSEDATA->trg[LBUTTON] && this->MouseCheck()))
		{
			if(__MOUSEDATA->trg[LBUTTON])
			{
				this->control->SetNowPlayerMap_FadeOut();
				if( (this->oldSelectNumber < this->dialogSum && this->selectNumber >= this->dialogSum) ||
					(this->oldSelectNumber >= this->dialogSum && this->selectNumber >= this->dialogSum) )
				{
					this->control->NewSelectPlayerMap(this->selectNumber - this->dialogSum, _parent->IsContinue() );
					this->control->GetNextPlayerMap()->SetSelectDialogNumber(PLAYERMAP_SELECT_NONE);
				}
			}

			this->MoveChange();
			this->okMusic();
			return true;
		}
		else if( __KEYDATA->trg[ KX ] || __MOUSEDATA->trg[RBUTTON] )
		{
			this->okMusic();
			this->waitCnt++;

			//---------------------------------------------------------------
			//プレイヤーのon/off切り替え
			//---------------------------------------------------------------
			if( this->selectNumber > this->dialogSum )
				this->control->ChangePlayerMap( this->selectNumber-this->dialogSum, _parent->IsContinue() );
			return true;
		}

		return (!hantei);
	}

	void PlayerSelectRoom::AllSelecting()
	{
		this->control->ChangeAllPlayerMap();
		if( (this->selectNumber - this->dialogSum) >= 0 )	return ;
		
		this->control->SetFadeOutList();
		this->control->Input_playerMapDialog(this->playerSum);
	}

	void PlayerSelectRoom::MoveChange()
	{
		switch( _parent->GetGameMode() )
		{
			case GAMEMODE_NEWGAME:		this->MoveChange_newGame();			break;
			case GAMEMODE_CONTINUEGAME:	this->MoveChange_continueGame();	break;
			case GAMEMODE_NETGAME:		this->MoveChange_netGame();			break;
		}
	}

	void PlayerSelectRoom::MoveChange_newGame()
	{
		switch( this->selectNumber )
		{
			case 0:	this->goPlaySelect();	break;
			case 1:	this->AllSelecting();	break;
			case 2:	this->gobacktoOnce();	break;
			default:	this->EachOtherAction();
		}
	}

	void PlayerSelectRoom::MoveChange_continueGame()
	{
		switch( this->selectNumber )
		{
			case 0:	this->AllSelecting();	break;
			case 1:	this->gobacktoContinue();	break;
			default:	this->EachOtherAction();
		}
	}
			
	void PlayerSelectRoom::MoveChange_netGame()
	{
		switch( this->selectNumber )
		{
			case 0:	this->goPlaySelect();		break;
			case 1:	this->AllSelecting();		break;
			case 2:	this->gobacktoServerHost();	break;
			default:	this->EachOtherAction();
		}
	}

	void PlayerSelectRoom::goPlaySelect()
	{
		((RoomScene*)(_parent))->GetRoomData()->playSum = this->control->OutputRule( &((RoomScene*)(_parent))->GetRoomData()->charaData );
		if( ((RoomScene*)(_parent))->GetRoomData()->playSum <= 2 &&
			!_parent->IsNetGame() )	return ;
		_parent->SetChangeDialog( new RuleSelectRoom( this->_parent, false ) );	
	}

	void PlayerSelectRoom::gobacktoOnce()
	{
		((RoomScene*)(_parent))->GetRoomData()->playSum = this->control->OutputRule( &((RoomScene*)(_parent))->GetRoomData()->charaData );
		_parent->SetChangeDialog( new SelectingRoom( this->_parent ) );	
	}

	void PlayerSelectRoom::gobacktoServerHost()
	{
		this->control->OutputRule( &((RoomScene*)(_parent))->GetRoomData()->charaData );
		_parent->SetChangeDialog( new ServerHostRoom( this->_parent ) );	
	}

	void PlayerSelectRoom::gobacktoContinue()
	{
		((RoomScene*)(_parent))->GetRoomData()->playSum = this->control->OutputRule( &((RoomScene*)(_parent))->GetRoomData()->charaData );
		_parent->SetChangeDialog( new ContinueRoom( this->_parent, false, false ) );	
	}

	void PlayerSelectRoom::EachOtherAction()
	{
		if( (*this->control->GetCharaDataList())[this->selectNumber-this->dialogSum].selectFlag )
		{
			this->_selectAction = &PlayerSelectRoom::select_playerAction;
			this->control->SetFadeOutList();
			this->control->SwitchDialog();
			this->control->GetNowPlayerMap()->startDialogNumber();

			int count = 0;
			for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
				count<this->dialogSum + this->playerSum; it++, count++ )
			{
				if( this->selectNumber == count )
				{
					((BoxExpansionDialog*)(*it))->onTouch();
					break;
				}
			}
		}
	}

	void PlayerSelectRoom::AfterAction()
	{
		int count = 0;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++, count++ )
		{
			(*it)->Step();
			if( count < this->dialogSum )
			{
				( this->selectNumber == count ? 
					((SlidesideDialog*)(*it))->onSelect() : ((SlidesideDialog*)(*it))->offSelect() );
			}
			else if(count < this->dialogSum + this->playerSum)
			{
				if( this->selectNumber == count ) 
				{
					((BoxExpansionDialog*)(*it))->onSelect();
					this->control->SetNowPlayerMap_FadeOut();
					this->control->NewSelectPlayerMap(this->selectNumber - this->dialogSum, _parent->IsContinue() );
				}
				else
					((BoxExpansionDialog*)(*it))->offSelect();
			}
		}

		if(this->oldSelectNumber < this->dialogSum &&
				this->selectNumber >= this->dialogSum)
			this->control->SetFadeOutList();
		else if(this->oldSelectNumber >= this->dialogSum &&
				this->selectNumber < this->dialogSum)
		{
				this->control->NewAllPlayerMap();
				this->control->SetNowPlayerMap_FadeOut();
		}
	}

	void PlayerSelectRoom::OnTouch(int touchNum)
	{
		int count = 0;
		int slt = (touchNum == -1 ? this->selectNumber : touchNum);
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
				count<this->dialogSum + this->playerSum; it++, count++ )
		{
			if( this->selectNumber == count )
			{
				((BoxExpansionDialog*)(*it))->onTouch();
				break;
			}
		}
	}
	
	void PlayerSelectRoom::select_playerAction()
	{
		this->control->Step();

		//-------------------------------------------------------------------------------------------
		//キーセレクト
		//-------------------------------------------------------------------------------------------
		PlayerMapDialog* map = this->control->GetNowPlayerMap();
		if( CHECK_NULL(map) )	return ;

		if( __KEYDATA->trg[ KDOWN ] )
		{
			map->downDialogNumber();
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KUP ] )
		{
			map->upDialogNumber();
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KZ ] || (
				__MOUSEDATA->trg[LBUTTON] && (this->MouseCheck_playerSelect() || this->MouseCheck_ruleSelect() ) ) )
		{			
			this->okMusic();
			switch( map->GetSelectDialogNumber() )
			{
			case PLAYERMAP_SELECT_POWER:
				this->_selectAction = &PlayerSelectRoom::select_powerAction;
				map->startPowerNumber();
				return ;
			case PLAYERMAP_SELECT_PLAYER:
				this->_selectAction = &PlayerSelectRoom::select_playerNameAction;
				map->startPlayNameNumber();
				return ;
			}
		}
		else if(__MOUSEDATA->trg[LBUTTON] && this->MouseCheck())
		{
			if( this->selectNumber < this->dialogSum )
			{
				map->stopDialogNumber();
				this->selectNumber = 1;
				this->KeyCheck();
				this->_selectAction = &PlayerSelectRoom::select_normalAction;
			}
			else
			{
				if( this->selectNumber == this->oldSelectNumber )
				{
					map->stopDialogNumber();
					this->OnTouch();
				}
				else
				{
					this->oldSelectNumber = this->selectNumber;
					this->OnTouch(this->oldSelectNumber);
					this->KeyCheck();
				}
			}

			this->okMusic();
			return ;
		}
		else if( __KEYDATA->trg[ KX ] || __MOUSEDATA->trg[RBUTTON])
		{
			this->okMusic();
			map->stopDialogNumber();
			this->_selectAction = &PlayerSelectRoom::select_normalAction;
			this->OnTouch();
			return ;
		}
	}

	bool PlayerSelectRoom::MouseCheck_playerSelect()
	{
		PlayerPlate* nd = this->control->GetNowPlayerMap()->GetPlayerPlateDialog();
		if( nd->IsAtack_boundingbox_centerBox( &Vector2((float)__MOUSEDATA->mouseX,(float)__MOUSEDATA->mouseY) ) )
		{
			this->control->GetNowPlayerMap()->SetSelectDialogNumber(PLAYERMAP_SELECT_PLAYER);
			return true;
		}
		return false;
	}

	bool PlayerSelectRoom::MouseCheck_ruleSelect()
	{
		NameDialog* nd = this->control->GetNowPlayerMap()->GetPowerPlateDialog();
		if( nd->IsAtack_boundingbox_centerBox( &Vector2((float)__MOUSEDATA->mouseX,(float)__MOUSEDATA->mouseY) ) )
		{
			this->control->GetNowPlayerMap()->SetSelectDialogNumber(PLAYERMAP_SELECT_POWER);
			return true;
		}
		return false;
	}
	
	void PlayerSelectRoom::select_playerNameAction()
	{
		if( this->control->Step_SelectPlayer( this->selectNumber - this->dialogSum ) )
			this->_selectAction = &PlayerSelectRoom::select_playerAction;
	}
	
	void PlayerSelectRoom::select_powerAction()
	{
		if( this->control->Step_SelectRule(this->selectNumber - this->dialogSum) )
			this->_selectAction = &PlayerSelectRoom::select_playerAction;
	}

	void PlayerSelectRoom::Step()
	{
		this->noticeDialog->Step();
		(this->*_selectAction)();
	}

	void PlayerSelectRoom::FadeOut()
	{
		this->noticeDialog->Step();
		bool hantei = this->StandardStep();
		this->control->FadeOut();
	}

	void PlayerSelectRoom::Draw2D()
	{
		this->Standard_Draw2D();
		this->noticeDialog->Draw2D();
		this->control->Draw2D();
	}

	void PlayerSelectRoom::SetFadeInS()
	{
		this->Standard_SetFadeIn();
		this->control->SetFadeIn();
	}

	void PlayerSelectRoom::SetFadeOutS()
	{
		this->Standard_SetFadeOut();
		this->control->SetFadeOut();
	}

	
	//-------------------------------------------------------------------------------

}