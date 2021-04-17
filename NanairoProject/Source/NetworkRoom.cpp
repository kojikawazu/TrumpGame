#pragma once

/////////////////////////////////////////////
//NanairoProject and std
/////////////////////////////////////////////
#include <string>
#include <fstream>
#include <MusicSound.h>
#include <MainFunction.h>
#include <DirectStd.h>
//#include <WinsockTCP.h>

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
	//-------------------------------------------------------------------------------
	//サーバーかクライアントかを決めるルームです。
	//-------------------------------------------------------------------------------
	ServerHostRoom::ServerHostRoom( MYGAME::SuperRoomScene* _pr )
	{
		_parent = _pr;
		this->Init();
	}
	
	ServerHostRoom::~ServerHostRoom()
	{
		this->Dispose();
	}

	void ServerHostRoom::Init()
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

	void ServerHostRoom::Input_SlidesideDialog()
	{
		this->updownWord = "ok_se";
		this->okWord = "go_se";

		SlidesideDialog* point;
		this->dialogSum = NETGAMEROOM_DIALOGSUM;
		for(int i=0; i<this->dialogSum; i++)
		{
			point = new SlidesideDialog();
			point->SetDialogName( "dialog1" );

			switch( i )
			{
				case NETGAMEROOM_SERVER:		point->SetName( "" );	break;
				case NETGAMEROOM_CLIENT:		point->SetName( "" );	break;
				case NETGAMEROOM_GOBACK:		point->SetName("");		break;
			}
			point->SetNumber( i );
			this->dialogList.Add( point );
		}
	}

	void ServerHostRoom::Input_TittleDialog()
	{
		ExpansionDialog* titleDialog = new ExpansionDialog();
		titleDialog->SetDialogName( "titleYousi" );
		titleDialog->SetName( "" );
		this->dialogList.Add( titleDialog );
	}

	void ServerHostRoom::Input_NoticeDialog()
	{
		NoticeDialog* noticeDialog = new NoticeDialog();
		noticeDialog->SetDialogName( "fuki" );
		noticeDialog->SetName( "pleasekey" );
		this->dialogList.Add( noticeDialog );
	}

	void ServerHostRoom::Dispose()
	{
		this->dialogList.ListClear();
	}

	void ServerHostRoom::FadeIn()
	{
		if( this->StandardStep() )	this->SetStep();
	}

	void ServerHostRoom::Step()
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

	bool ServerHostRoom::KeyCheck()
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

	bool ServerHostRoom::MouseClickCheck()
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

	void ServerHostRoom::Decision()
	{
		switch( this->selectNumber )
		{
			case NETGAMEROOM_SERVER:	//サーバーでプレイヤーセレクトへ
				_parent->SetServerFlag( true );
				_parent->SetChangeDialog( new PlayerSelectRoom( this->_parent, false ) );	
				break;
			case NETGAMEROOM_CLIENT:	//クライアントでプレイヤーセレクトへ
				_parent->SetServerFlag( false );	
				_parent->SetChangeDialog( new PlayerSelectRoom( this->_parent, false ) );		
				break;
			case NETGAMEROOM_GOBACK:	//総合画面へ
				_parent->SetChangeDialog( new SelectingRoom( this->_parent ) );
				break;
		}
	}
	
	void ServerHostRoom::AfterAction()
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

	void ServerHostRoom::FadeOut()
	{
		this->StandardStep();
	}

	void ServerHostRoom::Draw2D()
	{
		this->Standard_Draw2D();
	}

	void ServerHostRoom::SetFadeInS()
	{
		this->Standard_SetFadeIn();
	}

	void ServerHostRoom::SetFadeOutS()
	{
		this->Standard_SetFadeOut();
	}

	//-------------------------------------------------------------------------------
	//サーバーかクライアントかを決めるルームです。
	//-------------------------------------------------------------------------------
	ServerRoom::ServerRoom( MYGAME::SuperRoomScene* _pr )
	{
		_parent = _pr;
		this->Init();
	}
	
	ServerRoom::~ServerRoom()
	{
		this->Dispose();
	}

	void ServerRoom::Init()
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

	void ServerRoom::Input_SlidesideDialog()
	{
		this->updownWord = "ok_se";
		this->okWord = "go_se";

		SlidesideDialog* point;
		this->dialogSum = NETGAMEROOM_DIALOGSUM;
		for(int i=0; i<this->dialogSum; i++)
		{
			point = new SlidesideDialog();
			point->SetDialogName( "dialog1" );

			switch( i )
			{
				case NETGAMEROOM_SERVER:		point->SetName( "" );	break;
				case NETGAMEROOM_CLIENT:		point->SetName( "" );	break;
				case NETGAMEROOM_GOBACK:		point->SetName("");		break;
			}
			point->SetNumber( i );
			this->dialogList.Add( point );
		}
	}

	void ServerRoom::Input_TittleDialog()
	{
		ExpansionDialog* titleDialog = new ExpansionDialog();
		titleDialog->SetDialogName( "titleYousi" );
		titleDialog->SetName( "" );
		this->dialogList.Add( titleDialog );
	}

	void ServerRoom::Input_NoticeDialog()
	{
		NoticeDialog* noticeDialog = new NoticeDialog();
		noticeDialog->SetDialogName( "fuki" );
		noticeDialog->SetName( "pleasekey" );
		this->dialogList.Add( noticeDialog );
	}

	void ServerRoom::Dispose()
	{
		this->dialogList.ListClear();
	}

	void ServerRoom::FadeIn()
	{
		if( this->StandardStep() )	this->SetStep();
	}

	void ServerRoom::Step()
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

	bool ServerRoom::KeyCheck()
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

	bool ServerRoom::MouseClickCheck()
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

	void ServerRoom::Decision()
	{
		switch( this->selectNumber )
		{
			case NETGAMEROOM_SERVER:	//サーバーでプレイヤーセレクトへ
				_parent->SetServerFlag( true );
				_parent->SetChangeDialog( new PlayerSelectRoom( this->_parent, false ) );	
				break;
			case NETGAMEROOM_CLIENT:	//クライアントでプレイヤーセレクトへ
				_parent->SetServerFlag( false );	
				_parent->SetChangeDialog( new PlayerSelectRoom( this->_parent, false ) );		
				break;
			case NETGAMEROOM_GOBACK:	//総合画面へ
				_parent->SetChangeDialog( new SelectingRoom( this->_parent ) );
				break;
		}
	}
	
	void ServerRoom::AfterAction()
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

	void ServerRoom::FadeOut()
	{
		this->StandardStep();
	}

	void ServerRoom::Draw2D()
	{
		this->Standard_Draw2D();
	}

	void ServerRoom::SetFadeInS()
	{
		this->Standard_SetFadeIn();
	}

	void ServerRoom::SetFadeOutS()
	{
		this->Standard_SetFadeOut();
	}
}