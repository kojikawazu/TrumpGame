#pragma once

/////////////////////////////////////////////
//NanairoLib
/////////////////////////////////////////////
#include <MainFunction.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <RoomScene.h>
#include <ChangeScene.h>
#include <Rule_effect.h>
#include <SelectRoomDialog.h>
#include <TrumpCard.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//-------------------------------------------------------------
	//プレイヤー選択型ダイアログ
	//-------------------------------------------------------------
	BoxExpansionDialog::BoxExpansionDialog()
	{
		this->Init();
	}

	BoxExpansionDialog::~BoxExpansionDialog(){}

	void BoxExpansionDialog::Init()
	{
		this->touchFlag = false;
		this->selectNumber = 0;
		this->ExpansionVector.SetVector(30, 15);
		this->SetObject( Vector2( SCRW_PERCENT( 0.5f ), SCRH_PERCENT(0.5f) ), 0.0f, Vector2( 0.0f, 0.0f ) );
		this->interval = 6;
		this->speed.SetVector( ((int)SCRW_PERCENT(0.2f)) / this->interval, SCRH_PERCENT(0.15f) / this->interval );
		this->SetDialogName( "selectPlate2" );
	}

	void BoxExpansionDialog::SetNumber(int num)
	{
		this->selectNumber = num;

		switch( this->selectNumber )
		{
			case 0:	this->parts.pos.SetVector( SCRW_PERCENT(0.3f), SCRH_PERCENT(0.9f) );	break;
			case 1:	this->parts.pos.SetVector( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.9f) );	break;
			case 2:	this->parts.pos.SetVector( SCRW_PERCENT(0.7f), SCRH_PERCENT(0.9f) );	break;
			case 3:	this->parts.pos.SetVector( SCRW_PERCENT(0.9f), SCRH_PERCENT(0.9f) );	break;
		}
	}

	void BoxExpansionDialog::onSelect()
	{
		this->selectFlag = true;
		this->offSetScale = (Vector2)this->ExpansionVector;
	}
	
	void BoxExpansionDialog::offSelect()
	{
		this->selectFlag = false;
		this->offSetScale.SetMinVector();
	}
		
	void BoxExpansionDialog::FadeIn()
	{
		this->parts.scale.Add( this->speed );
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void BoxExpansionDialog::FadeOut()
	{
		this->parts.scale.Sub( this->speed );
		this->parts.scale.SubCut();
		if( this->IncrementInterval(6) )	this->SetWait();
	}

	void BoxExpansionDialog::onTouch()
	{
		this->touchFlag = !this->touchFlag;
	}

	//-------------------------------------------------------------
	//プレイヤー選択型ダイアログ
	//-------------------------------------------------------------
	PlayerFukidasiDialog::PlayerFukidasiDialog()
	{
		this->Init();
	}

	PlayerFukidasiDialog::~PlayerFukidasiDialog()
	{
		for(int i=0; i<PLAYERNAME_MAX; i++)
			ES_SAFE_DELETE( this->playTag[i] );
		ES_SAFE_DELETE( this->checkBox );
		ES_SAFE_DELETE( this->CheckTag );
		ES_SAFE_DELETE( this->titleTag );
		ES_SAFE_DELETE( this->introduceTag );
	}

	void PlayerFukidasiDialog::Init()
	{
		this->selectNumber = 0;
		this->SetObject( Vector2( SCRW_PERCENT( 0.5f ), SCRH_PERCENT(0.5f) ), 0.0f, Vector2( 0.0f, 0.0f ) );
		this->interval = 6;
		this->speed.SetVector( ((int)SCRW_PERCENT(0.8f)) / this->interval, SCRH_PERCENT(0.8f) / this->interval );
		this->SetDialogName( "frame" );

		this->Input_playerTag();
		this->Input_checkBox();
		this->Input_checkTag();
		this->Input_titleTag();
		this->Input_IntroduceTag();
	}

	void PlayerFukidasiDialog::Input_IntroduceTag()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->introduceTag = new NoticeDialog();
		this->introduceTag->SetObject( Vector2(_pt->pos.x, _pt->pos.y + 150.0f), _pt->ang,
			Vector2(0, 0) );
		this->introduceTag->SetNameColor( _pt->color.color );
		this->introduceTag->SetDialogName("badge");
		this->introduceTag->SetName(PLAYERNAME_ENUM[0]);
		this->introduceTag->SetMoveObject_ofScale(Vector2(0,0), Vector2(400, 150), 10 );
	}

	void PlayerFukidasiDialog::Input_checkBox()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		//-----------------------------------------------
		//チェックタグ
		this->checkBox = new NameDialog();
		this->checkBox->SetObject(Vector2(_pt->pos.x - 200.0f + 100.0f * (this->selectNumber - 1), _pt->pos.x - 100.0f), _pt->ang,
									Vector2(150.0f + this->offSetScale.x, 150.0f + this->offSetScale.y) );
		this->checkBox->SetNameColor( _pt->color.color );
		this->checkBox->SetDialogName("checkBox");
	}
	
	void PlayerFukidasiDialog::Input_playerTag()
	{
		//プレイヤーの顔
		NanairoLib::PUIParts2D _pt = this->GetParts();
		for(int i=0; i<PLAYERNAME_MAX; i++)
		{
			this->playTag[i] = new PlayerPlate();
			this->playTag[i]->SetObject(Vector2(_pt->pos.x - 200.0f + 120.0f * i, _pt->pos.x - 100.0f), _pt->ang,
										Vector2( 100.0f + this->offSetScale.x, 100.0f + this->offSetScale.y ) );
			this->playTag[i]->SetName(NameTagString[i]);
			this->playTag[i]->SetNameColor( _pt->color.color );
			this->playTag[i]->SetFace(0);
		}
	}

	void PlayerFukidasiDialog::Input_titleTag()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		//-----------------------------------------------
		//タイトル
		this->titleTag = new NameDialog();
		this->titleTag->SetObject( Vector2(_pt->pos.x, _pt->pos.y - 150.0f), _pt->ang,
									Vector2( 400.0f + this->offSetScale.x, 150.0f + this->offSetScale.y ) );
		this->titleTag->SetDialogName("playerSelect");
		this->titleTag->SetNameColor(_pt->color.color);
	}

	void  PlayerFukidasiDialog::Input_checkTag()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		//-----------------------------------------------
		//チェックタグ
		this->CheckTag = new NoticeDialog();
		this->CheckTag->SetObject(Vector2(_pt->pos.x - 270.0f, _pt->pos.y - 170.0f), _pt->ang,
									Vector2( 0,0) );
		this->CheckTag->SetNameColor( _pt->color.color );
		this->CheckTag->SetDialogName("clickMap");
		this->CheckTag->SetName("lclickMap");
	}
	
	void PlayerFukidasiDialog::SetNumber(int num)
	{
		this->selectNumber = num+1;
	}
		
	void PlayerFukidasiDialog::FadeIn()
	{
		this->CheckTag->Step();
		this->introduceTag->Step();
		this->parts.scale.Add( this->speed );
		

		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void PlayerFukidasiDialog::Wait()
	{
		this->CheckTag->Step();
		this->introduceTag->Step();
	}

	bool PlayerFukidasiDialog::IsMouseAtack()
	{
		Vector2 ms((float)__MOUSEDATA->mouseX, (float)__MOUSEDATA->mouseY);
		for(int i=0; i<PLAYERNAME_MAX; i++)
		{
			if( this->playTag[i]->IsAtack_boundingbox_centerBox( &ms ) )
			{
				this->selectNumber = i+1;
				return true;
			}
		}
		return false;
	}

	void PlayerFukidasiDialog::FadeOut()
	{
		this->CheckTag->Step();
		this->introduceTag->Step();
		this->parts.scale.Sub( this->speed );
		this->parts.scale.SubCut();
		if( this->IncrementInterval(6) )	this->SetWait();
	}

	void PlayerFukidasiDialog::upPlayNameNumber()
	{
		this->selectNumber = INCREMENT_SPECIAL( this->selectNumber, playerNameSum );
		if( this->selectNumber == 0 )	this->selectNumber = 1;
	}
	
	void PlayerFukidasiDialog::downPlayNameNumber()
	{
		int st = playerNameSum;
		this->selectNumber = DECREMENT_SPECIAL(this->selectNumber, st);
		if( this->selectNumber == 0 )	this->selectNumber = st-1;
	}

	void PlayerFukidasiDialog::Draw2D()
	{
		//-----------------------------------------------------------------------------
		//タグの描画
		//-----------------------------------------------------------------------------
		this->drawDialog();

		//-----------------------------------------------------------------------------
		//プレイヤーの描画
		//-----------------------------------------------------------------------------
		this->PlayerDraw();

		//-----------------------------------------------------------------------------
		//自己紹介カードの描画
		//-----------------------------------------------------------------------------
		this->IntroduceDraw();

		//-----------------------------------------------------------------------------
		//セレクト枠の描画
		//-----------------------------------------------------------------------------
		this->SelecterDraw();

		//-----------------------------------------------------------------------------
		//タイトルの描画
		//-----------------------------------------------------------------------------
		this->TittleDraw();

		//-----------------------------------------------------------------------------
		//チェッカーの描画
		//-----------------------------------------------------------------------------
		this->CheckerDraw();
	}

	void PlayerFukidasiDialog::PlayerDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		for(int i=0; i<PLAYERNAME_MAX; i++)
		{
			this->playTag[i]->SetScl( Vector2(100.0f + this->offSetScale.x, 100.0f + this->offSetScale.y));
			this->playTag[i]->SetNameColor( _pt->color.color );
			this->playTag[i]->Draw2D();
		}
	}
	
	void PlayerFukidasiDialog::SelecterDraw()	
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->checkBox->SetPos( Vector2(_pt->pos.x - 200.0f + 120.0f * (this->selectNumber - 1), _pt->pos.x - 100.0f) );
		this->checkBox->SetScl( Vector2(150.0f + this->offSetScale.x, 150.0f + this->offSetScale.y));
		this->checkBox->SetNameColor( _pt->color.color );
		this->checkBox->Draw2D();
	}

	void PlayerFukidasiDialog::TittleDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->titleTag->SetScl( Vector2(400.0f + this->offSetScale.x, 150.0f + this->offSetScale.y));
		this->titleTag->SetNameColor( _pt->color.color );
		this->titleTag->Draw2D();
	}

	void PlayerFukidasiDialog::CheckerDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->CheckTag->SetNameColor( _pt->color.color );
		this->CheckTag->Draw2D();
	}

	void PlayerFukidasiDialog::IntroduceDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->introduceTag->SetName(PLAYERNAME_ENUM[this->selectNumber - 1]);
		this->introduceTag->SetNameColor( _pt->color.color );
		this->introduceTag->Draw2D();
	}

	//-------------------------------------------------------------
	//強さ選択型ダイアログ
	//-------------------------------------------------------------
	PowerFukidasiDialog::PowerFukidasiDialog()
	{
		this->Init();
	}

	PowerFukidasiDialog::~PowerFukidasiDialog()
	{
		for(int i=0; i<POWER_ENUM_SUM; i++)
			ES_SAFE_DELETE( this->powerTag[i] );
		ES_SAFE_DELETE( this->checkBox );
		ES_SAFE_DELETE( this->CheckTag );
		ES_SAFE_DELETE( this->titleTag );
	}

	void PowerFukidasiDialog::Init()
	{
		this->selectNumber = 0;
		this->parts.color.SetColor(255, 255, 255, 0 );

		this->SetObject( Vector2( SCRW_PERCENT( 0.5f ), SCRH_PERCENT(0.5f) ), 0.0f, Vector2( 0.0f, 0.0f ) );
		this->interval = 6;
		this->speed.SetVector( ((int)SCRW_PERCENT(0.8f)) / this->interval, SCRH_PERCENT(0.8f) / this->interval );
		this->SetDialogName( "frame" );

		this->Input_powerTag();
		this->Input_titleTag();
		this->Input_checkTag();
		this->Input_checkBox();		
	}

	void PowerFukidasiDialog::Input_powerTag()
	{
		//-----------------------------------------------
		//プレイヤーの顔
		NanairoLib::PUIParts2D _pt = this->GetParts();
		for(int i=0; i<POWER_ENUM_SUM; i++)
		{
			this->powerTag[i] = new NameDialog();
			this->powerTag[i]->SetObject(Vector2(_pt->pos.x - 200.0f + 120.0f * i, _pt->pos.x - 100.0f), _pt->ang,
										Vector2( 100.0f + this->offSetScale.x, 100.0f + this->offSetScale.y ) );
			this->powerTag[i]->SetDialogName(POWER_ENUM[i]);
			this->powerTag[i]->SetNameColor( _pt->color.color );
		}
	}

	void PowerFukidasiDialog::Input_titleTag()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		//-----------------------------------------------
		//タイトル
		this->titleTag = new NameDialog();
		this->titleTag->SetObject( Vector2(_pt->pos.x, _pt->pos.y - 150.0f), _pt->ang,
									Vector2( 400.0f + this->offSetScale.x, 150.0f + this->offSetScale.y ) );
		this->titleTag->SetDialogName("powerSelect");
		this->titleTag->SetNameColor(_pt->color.color);
	}

	void PowerFukidasiDialog::Input_checkTag()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		//-----------------------------------------------
		//チェックタグ
		this->CheckTag = new NoticeDialog();
		this->CheckTag->SetObject(Vector2(_pt->pos.x - 270.0f, _pt->pos.y - 170.0f), _pt->ang,
									Vector2( 0,0) );
		this->CheckTag->SetNameColor( _pt->color.color );
		this->CheckTag->SetDialogName("clickMap");
		this->CheckTag->SetName("lclickMap");
	}
	
	void PowerFukidasiDialog::Input_checkBox()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		//-----------------------------------------------
		//チェックボックス
		this->checkBox = new NameDialog();
		this->checkBox->SetObject( Vector2(_pt->pos.x - 200.0f + 120.0f * (this->selectNumber - 1), _pt->pos.x - 100.0f), _pt->ang,
									Vector2( 150.0f + this->offSetScale.x, 150.0f + this->offSetScale.y ) );
		this->checkBox->SetDialogName("checkBox");
		this->checkBox->SetNameColor(_pt->color.color);
	}

	void PowerFukidasiDialog::SetNumber(int num)
	{
		this->selectNumber = num+1;
	}
		
	void PowerFukidasiDialog::FadeIn()
	{
		this->CheckTag->Step();
		this->parts.scale.Add( this->speed );
		

		if( this->DecrementInterval(0) )
			this->SetWait();
	}

	void PowerFukidasiDialog::Wait()
	{
		this->CheckTag->Step();
	}

	bool PowerFukidasiDialog::IsMouseAtack()
	{
		Vector2 ms((float)__MOUSEDATA->mouseX, (float)__MOUSEDATA->mouseY);
		for(int i=0; i<POWER_ENUM_SUM; i++)
		{
			if( this->powerTag[i]->IsAtack_boundingbox_centerBox( &ms ) )
			{
				this->selectNumber = i+1;
				return true;
			}
		}
		return false;
	}

	void PowerFukidasiDialog::FadeOut()
	{
		this->CheckTag->Step();
		this->parts.scale.Sub( this->speed );
		this->parts.scale.SubCut();
		

		if( this->IncrementInterval(6) )	this->SetWait();
	}

	void PowerFukidasiDialog::upPlayNameNumber()
	{
		this->selectNumber = INCREMENT_SPECIAL( this->selectNumber, (playerNameSum-1) );
		if( this->selectNumber == 0 )	this->selectNumber = 1;
	}
	
	void PowerFukidasiDialog::downPlayNameNumber()
	{
		int st = playerNameSum-1;
		this->selectNumber = DECREMENT_SPECIAL(this->selectNumber, st);
		if( this->selectNumber == 0 )	this->selectNumber = st-1;
	}

	void PowerFukidasiDialog::Draw2D()
	{
		//-----------------------------------------------------------------------------
		//タグの描画
		//-----------------------------------------------------------------------------
		this->drawDialog();

		//-----------------------------------------------------------------------------
		//プレイヤーの描画
		//-----------------------------------------------------------------------------
		this->PlayerDraw();

		//-----------------------------------------------------------------------------
		//セレクト枠の描画
		//-----------------------------------------------------------------------------
		this->SelecterDraw();

		//-----------------------------------------------------------------------------
		//タイトルの描画
		//-----------------------------------------------------------------------------
		this->TittleDraw();

		//-----------------------------------------------------------------------------
		//チェックタグの描画
		//-----------------------------------------------------------------------------
		this->CheckerDraw();
	}

	void PowerFukidasiDialog::TittleDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->titleTag->SetScl( Vector2(400.0f + this->offSetScale.x, 150.0f + this->offSetScale.y));
		this->titleTag->SetNameColor( _pt->color.color );
		this->titleTag->Draw2D();
	}

	void PowerFukidasiDialog::PlayerDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		for(int i=0; i<POWER_ENUM_SUM; i++)
		{
			this->powerTag[i]->SetScl( Vector2(100.0f + this->offSetScale.x, 100.0f + this->offSetScale.y));
			this->powerTag[i]->SetNameColor( _pt->color.color );
			this->powerTag[i]->Draw2D();
		}
	}
	
	void PowerFukidasiDialog::SelecterDraw()	
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->checkBox->SetPos( Vector2(_pt->pos.x - 200.0f + 120.0f * (this->selectNumber - 1), _pt->pos.x - 100.0f) );
		this->checkBox->SetScl( Vector2(150.0f + this->offSetScale.x, 150.0f + this->offSetScale.y));
		this->checkBox->SetNameColor( _pt->color.color );
		this->checkBox->Draw2D();
	}

	void PowerFukidasiDialog::CheckerDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->CheckTag->SetNameColor( _pt->color.color );
		this->CheckTag->Draw2D();
	}

	//-------------------------------------------------------------
	//プレイヤー情報型ダイアログ
	//-------------------------------------------------------------
	PlayerMapDialog::PlayerMapDialog()
	{
		this->Init();
	}

	PlayerMapDialog::~PlayerMapDialog()
	{
		ES_SAFE_DELETE( this->fukidasiDialog );
		ES_SAFE_DELETE( this->powerDialog );
		ES_SAFE_DELETE( this->playTitleNameDialog );
		ES_SAFE_DELETE( this->playerNameDialog );
		ES_SAFE_DELETE( this->batuDialog );
		ES_SAFE_DELETE( this->allowDialog );
		ES_SAFE_DELETE( this->scoreNameDialog );
		ES_SAFE_DELETE( this->scoreNumber );
		ES_SAFE_DELETE( this->powerNameDialog );
		ES_SAFE_DELETE( this->runkerNameDialog );
	}

	void PlayerMapDialog::Init()
	{
		this->touchFlag = this->delFlag = this->scoreFlag = false;
		this->moveFlag = true;
		this->selectNumber = this->selectDialogNumber = 0;
		this->SetObject( Vector2( SCRW_PERCENT(0.9f), SCRH_PERCENT(0.5f) ), 0.0f, Vector2( 450.0f, 300.0f ) );
		this->interval = 10;
		this->speed.SetVector( (SCRW_PERCENT(0.7f) - this->parts.pos.x) / this->interval, 0.0f );
		this->yajiPos.SetVector(0,0);
		this->SetDialogName( "titleYousi" );
		
		this->parts.color.SettingFadeAlpha();
		
		this->fukidasiDialog = NULL;
		this->powerDialog = NULL;

		Vector4 col = Vector4(255, 255, 255, 255);
		this->playerNameDialog = new PlayerPlate();
		this->playerNameDialog->GetParts()->color = col;

		this->playTitleNameDialog = new NameDialog();
		this->playTitleNameDialog->SetNameColor( col );

		this->runkerNameDialog = new NameDialog();
		this->runkerNameDialog->SetNameColor( col );

		this->batuDialog = new NameDialog();
		this->batuDialog->SetNameColor( col );
		this->batuDialog->SetName( "noPlayer" );

		this->allowDialog = new NameDialog();
		this->allowDialog->SetNameColor( col );
		this->allowDialog->SetName( "yajirusi" );

		this->powerNameDialog = new NameDialog();
		this->powerNameDialog->SetNameColor( col );
		
		this->scoreNameDialog = new NameDialog();
		this->scoreNameDialog->SetNameColor( col );
		this->scoreNameDialog->SetName( "score:" );

		this->scoreNumber = new NumbersWord();
		this->scoreNumber->SetColor( col );
	}

	void PlayerMapDialog::SetNumber(CharaData* _data, int number, bool isMode, bool IsContinue)
	{
		this->continueFlag = IsContinue;
		this->selectNumber = 0;
		this->charaData = *_data;
		NanairoLib::PUIParts2D _pt = this->GetParts();

		switch( number )
		{
			case 0:	this->parts.color.SetColor(255, 200, 100,  100);	break;
			case 1:	this->parts.color.SetColor(255, 100, 200,  100);	break;
			case 2:	this->parts.color.SetColor(255, 100, 100,  200);	break;
			case 3:	this->parts.color.SetColor(255, 200, 200,  100);	break;
		}
		this->parts.color.SettingFadeAlpha();

		if( isMode )
		{
			switch( number )
			{
				case 0:	this->parts.pos.SetVector(SCRW_PERCENT(0.7f), SCRH_PERCENT(0.35f));	break;
				case 1:	this->parts.pos.SetVector(SCRW_PERCENT(1.0f), SCRH_PERCENT(0.35f));	break;
				case 2: this->parts.pos.SetVector(SCRW_PERCENT(0.7f), SCRH_PERCENT(0.65f));	break;
				case 3:	this->parts.pos.SetVector(SCRW_PERCENT(1.0f), SCRH_PERCENT(0.65f));	break;
			}
			this->parts.scale.SetVector( SCRW_PERCENT(0.28f), SCRH_PERCENT(0.28f) );
		}

		this->playTitleNameDialog->SetName( ( this->charaData.poreFlag ? "playerName": "computerName") );
		this->playTitleNameDialog->SetObject( Vector2(_pt->pos.x, _pt->pos.y - this->parts.scale.y * 0.3f), this->parts.ang, 
												Vector2( this->parts.scale.x * 0.7f + this->offSetScale.x, this->parts.scale.y * 0.5f + this->offSetScale.y ) );
		this->runkerNameDialog->SetObject( Vector2(_pt->pos.x, _pt->pos.y - this->parts.scale.y * 0.1f ), this->parts.ang, 
													Vector2( this->parts.scale.x * 0.5f + this->offSetScale.x, this->parts.scale.y * 0.2f + this->offSetScale.y ) );
		this->playerNameDialog->SetObject( Vector2(_pt->pos.x + this->parts.scale.x * 0.2f, _pt->pos.y + this->parts.scale.y * 0.2f), _pt->ang, 
											Vector2( this->parts.scale.x * 0.4f + this->offSetScale.x, this->parts.scale.y * 0.4f + this->offSetScale.y ) );
		this->powerNameDialog->SetObject( Vector2(_pt->pos.x - this->parts.scale.x * 0.2f, _pt->pos.y + this->parts.scale.y * 0.1f), _pt->ang, 
											Vector2( this->parts.scale.x * 0.4f + this->offSetScale.x, this->parts.scale.y * 0.2f + this->offSetScale.y ) );
		this->scoreNameDialog->SetObject( Vector2(_pt->pos.x - this->parts.scale.x * 0.25f, _pt->pos.y + this->parts.scale.y * 0.45f), _pt->ang, 
											Vector2( this->parts.scale.x * 0.6f + this->offSetScale.x, this->parts.scale.y * 0.6f + this->offSetScale.y ) );
		this->scoreNumber->SetObject( &Vector2( _pt->pos.x - this->parts.scale.x * 0.15f, _pt->pos.y + this->parts.scale.y * 0.35f ), _pt->ang,
											&Vector2( this->parts.scale.x * 0.2f + this->offSetScale.x, this->parts.scale.y * 0.2f + this->offSetScale.y ) );
		this->allowDialog->SetObject( Vector2(0,0), _pt->ang + 1.57f, 
											Vector2( this->parts.scale.x * 0.1f + this->offSetScale.x, this->parts.scale.y * 0.1f + this->offSetScale.y ) );
		this->batuDialog->SetObject( _pt->pos, _pt->ang, 
							Vector2( this->parts.scale.x * 0.8f + this->offSetScale.x, this->parts.scale.y * 0.8f + this->offSetScale.y ) );
	}

	void PlayerMapDialog::startDialogNumber()
	{
		this->selectDialogNumber = 1;
	}

	void PlayerMapDialog::upDialogNumber()
	{
		this->selectDialogNumber = INCREMENT_SPECIAL( this->selectDialogNumber, (playerMapPartsSum - (this->charaData.poreFlag ? 1 : 0)) );
		if( this->selectDialogNumber == 0 )	this->selectDialogNumber = 1;
	}

	void PlayerMapDialog::downDialogNumber()
	{
		int st = (playerMapPartsSum - (this->charaData.poreFlag ? 1 : 0));
		this->selectDialogNumber = DECREMENT_SPECIAL( this->selectDialogNumber,  st );
		if( this->selectDialogNumber == 0 )	this->selectDialogNumber = st-1;
	}

	void PlayerMapDialog::stopDialogNumber()
	{
		this->selectDialogNumber = 0;
	}

	void PlayerMapDialog::startPlayNameNumber()
	{
		this->fukidasiDialog = new PlayerFukidasiDialog();
		this->fukidasiDialog->SetNumber( this->charaData.charaNum );
	}
	
	void PlayerMapDialog::upPlayNameNumber()
	{
		if( !CHECK_NULL(this->fukidasiDialog) )
			this->fukidasiDialog->downPlayNameNumber();
	}

	void PlayerMapDialog::downPlayNameNumber()
	{
		if( !CHECK_NULL(this->fukidasiDialog) )
			this->fukidasiDialog->upPlayNameNumber();
	}

	void PlayerMapDialog::stopPlayNameNumber()
	{
		this->charaData.charaNum = this->fukidasiDialog->GetSelectNumber()-1;
		ES_SAFE_DELETE( this->fukidasiDialog );
	}

	void PlayerMapDialog::startPowerNumber()
	{
		this->powerDialog = new PowerFukidasiDialog();
		this->powerDialog->SetNumber( this->charaData.spec );
	}

	void PlayerMapDialog::upPowerNumber()
	{
		if( !CHECK_NULL(this->powerDialog) )
			this->powerDialog->downPlayNameNumber();
	}	

	void PlayerMapDialog::downPowerNumber()
	{
		if( !CHECK_NULL(this->powerDialog) )
			this->powerDialog->upPlayNameNumber();
	}

	void PlayerMapDialog::stopPowerNumber()
	{
		this->charaData.spec = this->powerDialog->GetSelectNumber()-1;
		ES_SAFE_DELETE( this->powerDialog );
	}

	void PlayerMapDialog::onFukidasi()
	{
		this->fukidasiDialog = new PlayerFukidasiDialog();
		this->fukidasiDialog->SetNumber( this->charaData.charaNum );
		this->fukidasiDialog->SetFadeIn();
	}

	void PlayerMapDialog::offFukidasi()
	{
		this->fukidasiDialog->GetSelectNumber();
		this->fukidasiDialog->SetFadeOut();
	}

	void PlayerMapDialog::FadeIn()
	{
		this->parts.pos.x += this->speed.x;
		this->parts.color.FadeIn(50.0f);
		if( this->DecrementInterval(0) )
		{
			this->SetWait();
			this->moveFlag = false;		
		}
	}

	//噴出しのアクション
	void PlayerMapDialog::FukidasiStep()
	{
		if( !CHECK_NULL(this->fukidasiDialog) )
			this->fukidasiDialog->Step();

		if( !CHECK_NULL(this->powerDialog) )
			this->powerDialog->Step();
	}

	void PlayerMapDialog::FadeOut()
	{
		this->parts.pos.x += this->speed.x;
		this->parts.color.FadeOut(50.0f);
		if( this->IncrementInterval(10) )
		{
			this->SetWait();
			this->moveFlag = false;
			this->OnDel( true );
		}
	}

	//スコア描画
	void PlayerMapDialog::ScoreDraw()
	{
		if( this->scoreFlag )
		{
			NanairoLib::PUIParts2D _pt = this->GetParts();
		
			//スコア文字の描画
			this->scoreNameDialog->SetPos( Vector2(_pt->pos.x - this->parts.scale.x * 0.25f, _pt->pos.y + this->parts.scale.y * 0.45f) );
			this->scoreNameDialog->SetNameAlpha( this->parts.color.color.x );
			this->scoreNameDialog->Draw2D();

			//スコアを描画
			this->scoreNumber->SetNumber( this->charaData.score );
			this->scoreNumber->SetPos( Vector2( _pt->pos.x - this->parts.scale.x * 0.15f, _pt->pos.y + this->parts.scale.y * 0.35f ) );
			this->scoreNumber->SetAlpha(this->parts.color.color.x);
			this->scoreNumber->Draw2D();
		}
	}

	//題名の描画
	void PlayerMapDialog::MapNameDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->playTitleNameDialog->SetPos( Vector2(_pt->pos.x, _pt->pos.y - this->parts.scale.y * 0.3f) );
		this->playTitleNameDialog->SetNameAlpha( this->parts.color.color.x );
		this->playTitleNameDialog->Draw2D();	
	}

	//大富豪プレートの描画
	void PlayerMapDialog::RunkerDraw()
	{
		if( this->scoreFlag )
		{
			NanairoLib::PUIParts2D _pt = this->GetParts();
			this->runkerNameDialog->SetPos( Vector2(_pt->pos.x, _pt->pos.y - this->parts.scale.y * 0.1f) );
			this->runkerNameDialog->SetNameAlpha( this->parts.color.color.x );
			this->runkerNameDialog->SetName( DaifugouString[this->charaData.runk] );
			this->runkerNameDialog->Draw2D();
		}
	}

	//敵の力の描画
	void PlayerMapDialog::PowerDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		std::string str[3] = {"Easy", "Normal", "Strong"};

		if( !this->charaData.poreFlag )
		{
			this->powerNameDialog->SetPos( Vector2(_pt->pos.x - this->parts.scale.x * 0.2f, _pt->pos.y + this->parts.scale.y * 0.1f) );
			this->powerNameDialog->SetNameAlpha( this->parts.color.color.x );
			this->powerNameDialog->SetName( str[this->charaData.spec].c_str() );
			this->powerNameDialog->Draw2D();
		}
	}

	//プレイヤーの絵描画
	void PlayerMapDialog::PlayerCharaDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->playerNameDialog->SetPos( Vector2(_pt->pos.x + this->parts.scale.x * 0.2f, _pt->pos.y + this->parts.scale.y * 0.2f) );
		this->playerNameDialog->SetNameAlpha( this->parts.color.color.x );
		this->playerNameDialog->SetName( NameTagString[this->charaData.charaNum] );
		this->playerNameDialog->Draw2D();
	}

	//矢印の描画
	void PlayerMapDialog::YajirushiDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		Vector2	vec;
		
		if( this->selectDialogNumber > 0 )
		{
			switch( this->selectDialogNumber )
			{
				case 1:	vec.SetVector( _pt->pos.x - 140.0f, _pt->pos.y - 100.0f );	break;
				case 2:	vec.SetVector( _pt->pos.x - 20.0f, _pt->pos.y + 70.0f );	break;
				case 3:	vec.SetVector( _pt->pos.x - 150.0f, _pt->pos.y + 30.0f );	break;
			}
			this->allowDialog->SetPos( vec );
			this->allowDialog->SetNameAlpha( this->parts.color.color.x );
			this->allowDialog->Draw2D();
		}
	}

	//罰点の描画
	void PlayerMapDialog::BatuDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->batuDialog->SetPos( _pt->pos );
		this->batuDialog->SetNameAlpha( this->parts.color.color.x );
		this->batuDialog->Draw2D();
	}

	void PlayerMapDialog::Draw2D()
	{
		//-----------------------------------------------------------------------------
		//タグの描画
		//-----------------------------------------------------------------------------
		this->drawDialog();
		
		//-----------------------------------------------------------------------------
		//名前の描画
		//-----------------------------------------------------------------------------
		this->ScoreDraw();

		if( this->charaData.selectFlag )
		{
			//-----------------------------------------------------------------------------
			//題名の描画
			//-----------------------------------------------------------------------------
			this->MapNameDraw();

			//-----------------------------------------------------------------------------
			//プレイヤキャラクターの描画
			//-----------------------------------------------------------------------------
			this->PlayerCharaDraw();

			//-----------------------------------------------------------------------------
			//何位かを描画
			//-----------------------------------------------------------------------------
			this->RunkerDraw();

			//-----------------------------------------------------------------------------
			//敵のパワーの描画
			//-----------------------------------------------------------------------------
			this->PowerDraw();

			//-----------------------------------------------------------------------------
			//矢印・噴出しの描画
			//-----------------------------------------------------------------------------
			this->YajirushiDraw();

			if( !CHECK_NULL(this->fukidasiDialog) )
				this->fukidasiDialog->Draw2D();

			if( !CHECK_NULL(this->powerDialog) )
				this->powerDialog->Draw2D();
		}
		else
		{
			//----------------------------------------------------------------------------------------
			//罰点表示
			//----------------------------------------------------------------------------------------
			this->BatuDraw();
		}
	}

	//-------------------------------------------------------------
	//→画面外から←へスライドするフェード型ダイアログ
	//-------------------------------------------------------------
	LookatRuleDialog::LookatRuleDialog()
	{
		this->Init();
	}

	LookatRuleDialog::~LookatRuleDialog(){}

	void LookatRuleDialog::Init()
	{
		this->touchFlag = false;
		this->selectNumber = 0;
		this->selectSpd = 5;
		this->interval = 10;
		
		this->ExpansionVector.SetVector(100,30);
		this->SetObject( Vector2( SCRW_PERCENT(1.3f), SCRH_PERCENT(0.9f)), 0.0f, Vector2( 120.0f, 70.0f ) );
		this->speed.SetVector( (SCRW_PERCENT(0.7f) - this->parts.pos.x) / this->interval, 0.0f );
		this->selectVec = (Vector2)this->parts.pos;
		this->SetDialogName( "selectPlate2" );	
	}

	void LookatRuleDialog::SetNumber(int num, int dialogSum)
	{
		this->selectNumber = num;
		this->dialogSum = dialogSum;
		this->SetDialogName( RulePlateGraphNames[this->dialogSum] );
		this->parts.pos.x = SCRW_PERCENT(0.95f) + (num) * 50.0f;
		this->selectVec = (Vector2)this->parts.pos;
	}

	void LookatRuleDialog::SetPosing(Vector2& start, Vector2& end, int interval, int number)
	{
		this->interval = interval;
		this->parts.pos = (Vector2)start;
		this->speed.SetVector( (end.x - start.x) / this->interval, (end.y - start.y) / this->interval );
		this->parts.pos.x = start.x + number * 50.0f;
	}

	void LookatRuleDialog::onSelect()
	{
		this->selectFlag = true;
		this->offSetScale = (Vector2)this->ExpansionVector;
	}
	
	void LookatRuleDialog::offSelect()
	{
		this->selectFlag = false;
		this->offSetScale.SetMinVector();
	}
	
	void LookatRuleDialog::onTouch()
	{
		this->touchFlag = !this->touchFlag;
	}

	void LookatRuleDialog::FadeIn()
	{
		this->parts.pos.x += this->speed.x;
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void LookatRuleDialog::Wait(){}

	void LookatRuleDialog::FadeOut()
	{
		this->parts.pos.x -= this->speed.x * 2.0f;
		if( this->IncrementInterval(10) )	this->SetWait();
	}

	//-----------------------------------------------------------------------------------
}