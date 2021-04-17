#pragma once

/////////////////////////////////////////////
//NanairoProject and std
/////////////////////////////////////////////
#include <string>
#include <fstream>
#include <MusicSound.h>
#include <MainFunction.h>
#include <DirectStd.h>

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

namespace NanairoProject
{
	//----------------------------------------------------------------------------
	//メインルームシーンクラス
	//いろいろなダイアログを制御します。
	//----------------------------------------------------------------------------
	void RoomScene::Init()
	{
		this->back.SetBackName("Selectroom");
		this->SetBGMWord( "viheart" );
		this->SEupdown = "ok_se";
		this->SEok = "go_se";

		//------------------------------------------
		//RoomPointerの初期化
		//------------------------------------------
		this->nowPoint = new SelectingRoom( this );

		//------------------------------------------
		//データの初期化
		//------------------------------------------
		this->BGMStart();
	}

	void RoomScene::InputKirariEffect()
	{
		MouseKirariEffect* ef = new MouseKirariEffect();
		ef->SetObject(Vector2((float)__MOUSEDATA->mouseX, (float)__MOUSEDATA->oldMouseY));
		this->afterEffectList.Add( ef );	
	}

	void RoomScene::TouchAction()
	{
		//--------------------------------------------------
		//現在使用しているポインタのステップ
		//--------------------------------------------------
		this->nowPoint->Action();
		
		//--------------------------------------------------
		//Qボタンを押すと自動的にタイトルへ戻ります
		//--------------------------------------------------
		if( __KEYDATA->trg[ KQ ] )
		{
			this->SetGoToGame();
			this->playSE_back();
		}

		if( __KEYDATA->trg[ KZ] || __MOUSEDATA->trg[LBUTTON])
			this->InputKirariEffect();

		//--------------------------------------------------
		//はい、いいえダイアログは独立して操作します。
		//--------------------------------------------------
		if( !CHECK_NULL( this->yesnoDialog ) )
		{
			this->yesnoDialog->Step();
			if( this->yesnoDialog->isDel() )
				ES_SAFE_DELETE( this->yesnoDialog );
		}
	}		
	
	void RoomScene::YesnoDialogAction()
	{
		//--------------------------------------------------
		//現在使用しているポインタのステップ
		//--------------------------------------------------
		this->yesnoDialog->Step();

		//--------------------------------------------------
		//Qボタンを押すと自動的にタイトルへ戻ります
		//--------------------------------------------------
		if( __KEYDATA->trg[ KLEFT ] || __KEYDATA->trg[ KRIGHT ] )
			this->playSE_updown();
		else if( __KEYDATA->trg[ KZ ] || 
			(__MOUSEDATA->trg[LBUTTON] && this->yesnoDialog->MouseCheck() ) )
		{
			( CHECK_ZERO( this->yesnoDialog->GetSelectNumber() ) ? 
				this->SetGoToGame() :
			this->SetTouchActions() );
			this->yesnoDialog->SetFadeOut();
			this->playSE_ok();
		}
	}

	void RoomScene::waitAndGoAction()
	{
		this->nowPoint->Action();

		if( !CHECK_NULL( this->yesnoDialog ) )
		{
			this->yesnoDialog->Step();
			if( this->yesnoDialog->isDel() )
				ES_SAFE_DELETE( this->yesnoDialog );
		}

		if( this->IncrementFrameCnt( 30 ) )
		{
			this->frameCnt = 0;
			this->SetChangeAction();
			
			PE_the_matchScene* scene = new PE_the_matchScene();
			scene->inputData( &this->roomData, this->IsContinue() );
			scene->player_Setting( this->IsContinue() );

			Scene* sc = NanairoProject::GetChangeScene(
			std::string( CHANGE_FADE ), scene,  this );
		
			( sc != NULL ? this->GetManager()->Add( sc ) : this->GetManager()->Dispose( this ) );
		}
	}	

	void RoomScene::WaitAndBackAction()
	{
		this->nowPoint->Action();

		if( this->IncrementFrameCnt( 30 ) )
		{
			this->frameCnt = 0;
			this->SetChangeAction();
			Scene* sc = NanairoProject::SettingChangeScene(
				CHANGE_FADE, SCENE_TITLE,  this );
			( sc != NULL ? this->GetManager()->Add( sc ) : this->GetManager()->Dispose( this ) );
		}
	}
	
	void RoomScene::WaitAndChangeDialogAction()
	{
		this->nowPoint->Action();

		if( this->IncrementFrameCnt( 30 ) )
		{
			this->frameCnt = 0;
			this->SetTouchActions();

			ES_SAFE_DELETE( this->nowPoint );
			this->nowPoint = this->nextPoint;
			this->nextPoint = NULL;
		}
	}

	void RoomScene::ChangeSceneAction(){}

	void RoomScene::SetRuleData(int r1, int r2)
	{
		this->roomData.rule = r1;
		this->roomData.rule2 = r2;
	}

	void RoomScene::LoadData()
	{
		std::fstream fs(DATAPASS);

		if( fs.eof() || fs.fail() )	return ;

		fs.read( (char*)&this->roomData.rule,	sizeof(int) );
		fs.read( (char*)&this->roomData.rule2,	sizeof(int) );
		fs.read( (char*)&this->roomData.playSum,sizeof(int) );
		fs.read( (char*)&this->roomData.roundCount,sizeof(int) );

		this->roomData.charaData.resize(4);
		int count = 0;
		while( !(fs.eof() || fs.fail()) )
		{
			fs.read( (char*)&this->roomData.charaData[count].selectFlag,	sizeof(bool) );
			fs.read( (char*)&this->roomData.charaData[count].poreFlag,		sizeof(bool) );
			fs.read( (char*)&this->roomData.charaData[count].charaNum,		sizeof(int) );
			fs.read( (char*)&this->roomData.charaData[count].spec,			sizeof(int) );
			fs.read( (char*)&this->roomData.charaData[count].score,			sizeof(int) );
			fs.read( (char*)&this->roomData.charaData[count].runk,			sizeof(int) );

			if( ++count >= 4 )
				break;
		}
	}

	void RoomScene::WriteData()
	{
		std::fstream fs(DATAPASS);

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

	//-------------------------------------------------------------------------------
	//最初のルームです。
	//始めからか続きかを決めるルームです。
	//-------------------------------------------------------------------------------
	SelectingRoom::SelectingRoom( MYGAME::SuperRoomScene* _pr )
	{
		_parent = _pr;
		this->Init();
	}

	void SelectingRoom::Init()
	{
		//-----------------------------------
		//スライドサイドダイアログの実装
		//-----------------------------------
		this->Input_SlidesideDialog();

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

	void SelectingRoom::Input_SlidesideDialog()
	{
		this->updownWord = "ok_se";
		this->okWord = "go_se";

		SlidesideDialog* point;
		this->dialogSum = SELECTIONROOM_DIALOGSUM;
		for(int i=0; i<this->dialogSum; i++)
		{
			point = new SlidesideDialog();
			point->SetDialogName( "dialog1" );

			switch( i )
			{
				case SELECTROOM_NEW_GAME:		point->SetName( "newGame" );		break;
				case SELECTROOM_CONTINUE_GAME:	point->SetName( "continueGame" );	break;
				case SELECTROOM_NET_GAME:		point->SetName("netGame");					break;
				case SELECTROOM_GOBACK_TITTLE:	point->SetName( "gobackTittle" );	break;
			}
			point->SetNumber( i );
			this->dialogList.Add( point );
		}
	}

	void SelectingRoom::Input_TittleDialog()
	{
		ExpansionDialog* titleDialog = new ExpansionDialog();
		titleDialog->SetDialogName( "titleYousi" );
		titleDialog->SetName( "mainSelect" );
		this->dialogList.Add( titleDialog );
	}

	void SelectingRoom::Input_NoticeDialog()
	{
		NoticeDialog* noticeDialog = new NoticeDialog();
		noticeDialog->SetDialogName( "fuki" );
		noticeDialog->SetName( "pleasekey" );
		this->dialogList.Add( noticeDialog );
	}

	void SelectingRoom::Step()
	{
		//-------------------------------------------------------------------------------------------
		//キーセレクト
		//-------------------------------------------------------------------------------------------
		if( this->KeyCheck() )	return ;

		//----------------------------------------------------------------------
		//セレクトによるタグのオフセット値変更
		//----------------------------------------------------------------------
		this->AfterAction();
	}

	bool SelectingRoom::KeyCheck()
	{
		//下に下げる
		if( __KEYDATA->trg[ KDOWN ] )
		{
			this->selectNumber = INCREMENT_SPECIAL( this->selectNumber, this->dialogSum );
			this->UpdownMusic();
		}
		//上に上げる
		else if( __KEYDATA->trg[ KUP ] )
		{
			this->selectNumber = DECREMENT_SPECIAL( this->selectNumber, this->dialogSum );
			this->UpdownMusic();
		}
		//決定
		else if( __KEYDATA->trg[ KZ ] ||
			(__MOUSEDATA->trg[LBUTTON] && this->MouseClickCheck() ) )
		{
			this->Decision();
			this->okMusic();
			return true;
		}
		return false;
	}

	bool SelectingRoom::MouseClickCheck()
	{
		SlidesideDialog* slide;
		int count =0;
		int mouseX = __MOUSEDATA->mouseX, mouseY = __MOUSEDATA->mouseY;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count<this->dialogSum; it++, count++)
		{
			slide = (SlidesideDialog*)(*it);
			if( slide-> IsAtack_boundingbox_centerBox( &Vector2((float)mouseX, (float)mouseY) ) )
			{
				this->selectNumber = count;
				return true;
			}
		}
		return false;
	}

	void SelectingRoom::Decision()
	{
		switch( this->selectNumber )
		{
			case SELECTROOM_NEW_GAME:	//プレイヤーセレクトルームへ	
				_parent->ChangeGameMode( GAMEMODE_NEWGAME );
				_parent->SetChangeDialog( new PlayerSelectRoom( this->_parent, false ) );	
				break;
			case SELECTROOM_CONTINUE_GAME:	//続きからルームへ
				_parent->ChangeGameMode( GAMEMODE_CONTINUEGAME );
				_parent->SetChangeDialog( new ContinueRoom( this->_parent, true, false ) );		
				break;
			case SELECTROOM_NET_GAME:	//ネットゲームへ
				_parent->ChangeGameMode( GAMEMODE_NETGAME );
				_parent->SetChangeDialog( new ServerHostRoom( this->_parent ) );	
				break;
			case SELECTROOM_GOBACK_TITTLE:	//タイトルへ戻ろう
				_parent->SetBackToTittle();		
				break;
		}
	}
	
	void SelectingRoom::AfterAction()
	{
		int count = 0;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++)
		{
			(*it)->Step();
			if( count < this->dialogSum )
				(this->selectNumber == count++ ? ((SlidesideDialog*)(*it))->onSelect() : ((SlidesideDialog*)(*it))->offSelect() );
		}
	}

	//-------------------------------------------------------------------------------

	ContinueRoom::ContinueRoom( MYGAME::SuperRoomScene* _pr, bool isSetData, bool IsOutput)
	{
		_parent = _pr;
		this->Init();
		this->outputFlag = IsOutput;
		
		//ロードandインプットデータ
		if( isSetData ) ((RoomScene*)(_parent))->LoadData();
		RoomData* dt = ((RoomScene*)(_parent))->GetRoomData();
		this->InputRule( dt->rule, dt->rule2, &dt->charaData );

		this->Input_PlayMapDialog();
		this->Input_LookRuleDialog();
		this->Input_DownSignDialog();
	}
	
	ContinueRoom::~ContinueRoom()
	{
		if( this->outputFlag ) ((RoomScene*)(_parent))->WriteData();
		this->Dispose();
	}

	void ContinueRoom::Init()
	{
		this->updownWord = "ok_se";
		this->okWord = "go_se";

		this->outputFlag = false;
		this->dialogSum = CONTINUEROOM_DIALOGSUM;
		this->roomData.Init();

		//-----------------------------------
		//スライドサイドダイアログの実装
		//-----------------------------------
		this->Input_SlidesideDialog();
		
		//-----------------------------------
		//通知ダイアログの実装
		//-----------------------------------
		this->Input_NoticeDialog();

		//-----------------------------------
		//タイトルダイアログの実装
		//-----------------------------------
		this->Input_TittleDialog();
		
		this->SetFadeIn();
	}

	void ContinueRoom::Input_SlidesideDialog()
	{
		SlidesideDialog* point;
		for(int i=0; i<this->dialogSum; i++)
		{
			point = new SlidesideDialog();
			point->SetDialogName( "dialog1" );

			switch( i )
			{
				case CONTINUEROOM_GAMESTART:		point->SetName( "gameStart" );			break;
				case CONTINUEROOM_SELECT_PLAYER:	point->SetName( "playerSelect2" );		break;
				case CONTINUEROOM_SELECT_RULE:		point->SetName( "ruleSelect2" );		break;
				case CONTINUEROOM_GOBACK:			point->SetName( "gobackTittle" );		break;
			}
			point->SetNumber( i );

			this->dialogList.Add( point );
		}
	}

	void ContinueRoom::Input_NoticeDialog()
	{
		NoticeDialog* noticeDialog = new NoticeDialog();
		noticeDialog->SetPos(Vector2(SCRW_PERCENT(0.3f), SCRH_PERCENT(0.25f)));
		noticeDialog->SetMoveObject_ofScale( Vector2(SCRW_PERCENT(0.0f), SCRH_PERCENT(0.0f)), 
												Vector2(SCRW_PERCENT(0.2f), SCRH_PERCENT(0.2f)), 10 );
		noticeDialog->SetDialogName( "fuki" );
		noticeDialog->SetName( "pleasekey" );
		this->dialogList.Add( noticeDialog );
	}

	void ContinueRoom::Input_TittleDialog()
	{
		ExpansionDialog* titleDialog = new ExpansionDialog();
		titleDialog->SetDialogName( "titleYousi" );
		titleDialog->SetName( "continueSelect" );
		this->dialogList.Add( titleDialog );
	}
	
	void ContinueRoom::Input_PlayMapDialog()
	{	
		PlayerMapDialog* map;
		for( int i=0; i<PLAYER_MAX; i++ )
		{
			map = new PlayerMapDialog();
			map->SetNumber( &this->roomData.charaData[i], i, true );
			map->SetScore(true);
			this->dialogList.Add( map );
		}
	}

	void ContinueRoom::Input_LookRuleDialog()
	{
		LookatRuleDialog* look;
		for( int i=0, count=0; i<RULE_SUM; i++ )
		{
			if( (i < ONERULE_SUM && isDataRule( this->roomData.rule, i ) ) || 
				(i >= ONERULE_SUM && isDataRule( this->roomData.rule2, i) ) )
			{
				look = new LookatRuleDialog();
				look->SetNumber( count++, i );
				this->dialogList.Add( look );
			}
		}

	}

	void ContinueRoom::Input_DownSignDialog()
	{
		DownSignDialog* sign = new DownSignDialog();
		sign->SetRound( ((RoomScene*)(_parent))->GetRoomData()->roundCount );
		this->dialogList.Add( sign );
	}

	void ContinueRoom::Dispose()
	{
		this->dialogList.ListClear();
	}

	void ContinueRoom::FadeIn()
	{
		if( this->StandardStep() )
			this->SetStep();
	}

	void ContinueRoom::Step()
	{
		//-------------------------------------------------------------------------------------------
		//キーセレクト
		//-------------------------------------------------------------------------------------------
		if( this->KeyCheck() )	return ;

		//----------------------------------------------------------------------
		//セレクトによるタグのオフセット値変更
		//----------------------------------------------------------------------
		this->AfterAction();
	}

	bool ContinueRoom::KeyCheck()
	{
		if( __KEYDATA->trg[ KDOWN ] )
		{
			this->selectNumber = INCREMENT_SPECIAL( this->selectNumber, this->dialogSum );
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KUP ] )
		{
			this->selectNumber = DECREMENT_SPECIAL( this->selectNumber, this->dialogSum );
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KZ ] ||
			( __MOUSEDATA->trg[LBUTTON] && this->MouseCheck()) )
		{
			this->Decision();
			this->okMusic();
			return true;
		}
		return false;
	}

	bool ContinueRoom::MouseCheck()
	{
		SlidesideDialog* slide;
		int count =0;
		int mouseX = __MOUSEDATA->mouseX, mouseY = __MOUSEDATA->mouseY;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			count<this->dialogSum; it++, count++)
		{
			slide = (SlidesideDialog*)(*it);
			if( slide-> IsAtack_boundingbox_centerBox( &Vector2((float)mouseX, (float)mouseY) ) )
			{
				this->selectNumber = count;
				return true;
			}
		}
		return false;
	}

	void ContinueRoom::Decision()
	{
		switch( this->selectNumber )
		{
			case CONTINUEROOM_GAMESTART:	
				_parent->SetYesnoDialog();												
				this->outputFlag = true;
				break;
			case CONTINUEROOM_SELECT_PLAYER:_parent->SetChangeDialog( new PlayerSelectRoom( this->_parent ) );	break;
			case CONTINUEROOM_SELECT_RULE:	_parent->SetChangeDialog( new RuleSelectRoom( this->_parent ) );	break;
			case CONTINUEROOM_GOBACK:		_parent->SetChangeDialog( new SelectingRoom( this->_parent ) );		break;
		}
	}
	
	void ContinueRoom::AfterAction()
	{
		int count = 0;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++)
		{
			if( count < this->dialogSum+1 ) 
				(*it)->Step();

			if( count < this->dialogSum ) 
			{
				if( this->selectNumber == count++ )	((SlidesideDialog*)(*it))->onSelect();
				else								((SlidesideDialog*)(*it))->offSelect();
			}
		}
	}

	void ContinueRoom::InputRule(int r1, int r2, std::vector<CharaData>* _list)
	{
		this->roomData.rule = r1;
		this->roomData.rule2 = r2;
		for(int i=0, siz=this->roomData.charaData.size(); i<siz; i++)
			this->roomData.charaData[i] = (*_list)[i];
	}

	void ContinueRoom::OutputRule(int* r1, int* r2, std::vector<CharaData>* _list)
	{
		(*r1) = this->roomData.rule;
		(*r2) = this->roomData.rule2;
		for(int i=0, siz=this->roomData.charaData.size(); i<siz; i++)
			(*_list)[i] = this->roomData.charaData[i];
	}
	
}