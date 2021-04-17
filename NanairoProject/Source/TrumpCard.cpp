#pragma once

////////////////////////////////////
//MYGAME
////////////////////////////////////
#include <MainFunction.h>
#include <ResourceFactory.h>

////////////////////////////////////
//NanairoProject
////////////////////////////////////
#include <TrumpCard.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	LPCTSTR trumpGraphList[4][13] = 
	{
		{"tpA1", "tpA2", "tpA3", "tpA4", "tpA5", "tpA6", "tpA7", "tpA8", "tpA9", "tpA10", "tpA11", "tpA12", "tpA13"},
		{"tpB1", "tpB2", "tpB3", "tpB4", "tpB5", "tpB6", "tpB7", "tpB8", "tpB9", "tpB10", "tpB11", "tpB12", "tpB13"},
		{"tpC1", "tpC2", "tpC3", "tpC4", "tpC5", "tpC6", "tpC7", "tpC8", "tpC9", "tpC10", "tpC11", "tpC12", "tpC13"},
		{"tpD1", "tpD2", "tpD3", "tpD4", "tpD5", "tpD6", "tpD7", "tpD8", "tpD9", "tpD10", "tpD11", "tpD12", "tpD13"},
	};

	//-----------------------------------------------------------------
	//Init
	//-----------------------------------------------------------------
	void TrumpCard::Init()
	{
		this->_draw = &TrumpCard::desDraw;
		this->_action = &TrumpCard::SetOffSetChange;
		
		this->isSelectOK = false;
		this->isAction = true;
		this->offSetX = this->offSetY = this->moveCnt = this->charaNumber = 0;
		this->offSetAng = 0.0f;
		this->isMouseTouch = CARD_TOUCHSTATUS_NO_TOUCH;
		this->offSet.SetMinVector();
		this->parts.pos.SetMinVector();
		this->parts.scale.SetVector( 80.0f, 100.0f );
		this->parts.ang = 0.0f;
		this->parts.color.SetMaxColor();
		this->ChangeDraw( CARD_STATUS_DES );
	}

	void TrumpCard::SetCharaNumber(int number)
	{
		this->charaNumber = number;
		this->cardType = CARD_SPECIAL;
		this->ChangeDraw( CARD_STATUS_FRONT );
	}

	//-----------------------------------------------------------------
	//マウスのタッチが行われているかチェック
	//-----------------------------------------------------------------
	bool TrumpCard::checkTouch()
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		int msX = MFunc->GetKey()->GetMouse()->mouseX;
		int msY = MFunc->GetKey()->GetMouse()->mouseY;
		int scX = CHANGE_HALF_LIFE(this->parts.scale.x, OFFSET_CARD_ATACKCHECK);
		int scY = CHANGE_HALF_LIFE(this->parts.scale.y, (OFFSET_CARD_ATACKCHECK + 0.4f) );
		bool check = ( msX > this->parts.pos.x - scX && 
								msX < this->parts.pos.x + scX && 
								msY > (this->parts.pos.y + this->offSetY) - scY &&
								msY < (this->parts.pos.y + this->offSetY) + scY );
		this->TouchAction( check );
		return check;
	}

	//-----------------------------------------------------------------
	//Setter
	//-----------------------------------------------------------------
	void TrumpCard::SetOnOrOff()
	{
		( isMouseTouch == CARD_TOUCHSTATUS_TOUCH ?
			this->ChangeDraw( CARD_STATUS_FRONT ): this->ChangeDraw( CARD_STATUS_BACK ) );
	}
	
	//-----------------------------------------------------------------
	//マウスタッチの変化があった場合のアクション
	//-----------------------------------------------------------------
	void TrumpCard::TouchAction(bool isOn)
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		if( isOn )
		{
			if( MFunc->GetKey()->GetMouse()->trg[ LBUTTON ] )
			{	
				//セレクトできないやつはスキップ
				if( !this->isJocker() && !this->isSpecial() )
				{
					if( !this->isSelectOK )
						return ;
				}
				
				if( this->isMouseTouch == CARD_TOUCHSTATUS_CLICK )
				{
					this->isMouseTouch = CARD_TOUCHSTATUS_TOUCH;
					this->parts.color.SetMaxColor();
				}
				else
				{
					this->isMouseTouch = CARD_TOUCHSTATUS_CLICK;
					this->parts.color.SetColor(255,255,255,0);
				}
			}
			else if( this->isMouseTouch == CARD_TOUCHSTATUS_NO_TOUCH )
				this->isMouseTouch = CARD_TOUCHSTATUS_TOUCH;
		}
		else if( this->isMouseTouch == CARD_TOUCHSTATUS_TOUCH )
			this->isMouseTouch = CARD_TOUCHSTATUS_NO_TOUCH;
	}

	//-----------------------------------------------------------------
	//選択状態のアクション
	//-----------------------------------------------------------------
	void TrumpCard::SetOffSetChange()
	{
		if( !this->isAction )	return ;
		
		if( isMouseTouch > CARD_TOUCHSTATUS_NO_TOUCH )
		{
			if( this->offSetY < OFFSET_PLUS_Y )
				this->offSetY += OFFSET_SPD;
		}
		else
		{
			if( this->offSetY > 0 )
				this->offSetY -= OFFSET_SPD;
		}
	}

	//-----------------------------------------------------------------
	//フェードインアクション
	//-----------------------------------------------------------------
	void TrumpCard::fadeInAction()
	{
		if( this->parts.ang == 0.0f )
		{
			if( this->offSetY > 0.0f )
				this->offSetY -= (int)(OFFSET_SPD * 0.5f);
		}
		else if( this->parts.ang == RAD_ONE_OUARTER )
		{
			if( this->offSetX > 0.0f )
				this->offSetX -= (int)(OFFSET_SPD * 0.5f);
		}
		else if( this->parts.ang == RAD_TWO_OUARTER )
		{
			if( this->offSetY < 0.0f )
				this->offSetY += (int)(OFFSET_SPD * 0.5f);
		}
		else
		{
			if( this->offSetX < 0.0f )
				this->offSetX += (int)(OFFSET_SPD * 0.5f);	
		}

		if( this->parts.color.FadeIn( 5 ) &&
			this->offSetX == 0.0f && offSetY == 0.0f )
			this->_action = &TrumpCard::waitAction;	
	}

	//-----------------------------------------------------------------
	//フェードアウトアクション
	//-----------------------------------------------------------------
	void TrumpCard::FadeOutAction()
	{
		if( this->parts.ang == 0.0f )
		{
			if( this->offSetY < OFFSET_PLUS_Y )
				this->offSetY += (int)(OFFSET_SPD * 0.5f);
		}
		else if( this->parts.ang == RAD_ONE_OUARTER )
		{
			if( this->offSetX < OFFSET_PLUS_Y )
				this->offSetX += (int)(OFFSET_SPD * 0.5f);
		}
		else if( this->parts.ang == RAD_TWO_OUARTER )
		{
			if( this->offSetY > -OFFSET_PLUS_Y )
				this->offSetY -= (int)(OFFSET_SPD * 0.5f);
		}
		else
		{
			if( this->offSetX > -OFFSET_PLUS_Y )
				this->offSetX -= (int)(OFFSET_SPD * 0.5f);	
		}

		if( this->parts.color.FadeOut( 5 ) )
			this->_action = &TrumpCard::waitAction;	
	}
	
	//-----------------------------------------------------------------
	//フェードインアクションのセッティング
	//-----------------------------------------------------------------
	void TrumpCard::SetFadeIn(int number)
	{
		this->_action = &TrumpCard::fadeInAction;	

		this->parts.color.SetAlpha( 255 );
		this->parts.color.SettingFadeAlpha();
		switch( number )
		{
			case 0:	
				this->offSetX = 10;
				this->offSetY = OFFSET_PLUS_Y;
				break;
			case 1:
				this->offSetX = OFFSET_PLUS_Y;
				this->offSetY = 0;
				break;
			case 2:
				this->offSetX = 0;
				this->offSetY = -OFFSET_PLUS_Y;
				break;
			case 3:
				this->offSetX = -OFFSET_PLUS_Y;
				this->offSetY = 0;
				break;
		}
	}

	void TrumpCard::SetFadeInS()
	{
		this->_action = &TrumpCard::fadeInAction;	
	}

	//-----------------------------------------------------------------
	//フェードアウトアクションのセッティング
	//-----------------------------------------------------------------
	void TrumpCard::SetFadeOut()
	{
		this->_action = &TrumpCard::FadeOutAction;
		this->parts.color.SettingFadeAlpha();
		this->parts.color.SetColor( &this->parts.color.color );
	}

	//-----------------------------------------------------------------
	//中央に移動
	//-----------------------------------------------------------------
	void TrumpCard::centerMoveAction()
	{
		this->parts.pos.x	+= this->offSet.x;
		this->parts.pos.y	+= this->offSet.y;
		this->parts.ang		+= this->offSetAng;

		if( ++this->moveCnt >= OFFSET_CENTER_MOVESPD )
		{	
			this->_action = &TrumpCard::waitAction;
			this->offSet.SetMinVector();
			this->moveCnt = 0;
		}
	}

	//-----------------------------------------------------------------
	//カードを中央に移動するためのセッティング
	//-----------------------------------------------------------------
	void TrumpCard::SetCenterMove(int tempI, int siz)
	{	
		float fiz = 0.6f * tempI;
		switch( siz )
		{
			case 1:
				this->offSet.x = (CHANGE_HALF(SCRW) - this->parts.pos.x) / OFFSET_CENTER_MOVESPD;
				break;
			case 2:
				this->offSet.x = (CHANGE_HALF_LIFE(SCRW, (0.475f + 0.05f * tempI) ) - this->parts.pos.x) / OFFSET_CENTER_MOVESPD;	
				break;
			case 3:
				this->offSet.x = (CHANGE_HALF_LIFE(SCRW, (0.45f + 0.05f * tempI) ) - this->parts.pos.x) / OFFSET_CENTER_MOVESPD;	
				break;
			case 4:
				this->offSet.x = (CHANGE_HALF_LIFE(SCRW, (0.425f + 0.05f * tempI) ) - this->parts.pos.x) / OFFSET_CENTER_MOVESPD;	
				break;
		}

		this->offSetAng = (0.0f - this->parts.ang) / OFFSET_CENTER_MOVESPD;
		this->offSet.y = (CHANGE_HALF(SCRH) - this->parts.pos.y) / OFFSET_CENTER_MOVESPD;
		this->moveCnt = 0;
		this->parts.scale.SetVector( 80.0f, 100.0f );
		this->_action = &TrumpCard::centerMoveAction;				

		if( !this->isAction )
		{
			this->isAction = true;
			this->ChangeDraw( CARD_STATUS_FRONT );
		}
	}

	//-----------------------------------------------------
	//カード番号のセッティング
	//-----------------------------------------------------
	void TrumpCard::SetCardNumber(int d_oneCardNumber)
	{
		if( d_oneCardNumber < 0 )	return ;
		else if( d_oneCardNumber >= CARD_MAX_NOJOCKER )
			this->SetJocker();
		else
		{
			this->cardType = (CARD_TYPE)(d_oneCardNumber / CARD_ONETYPE_MAX);
			this->cardNumber = d_oneCardNumber % CARD_ONETYPE_MAX;
			this->ChangeDraw( CARD_STATUS_FRONT );
		}
	}

	void TrumpCard::SetCardNumber(int d_cardNumber, int d_cardType)
	{
		if( d_cardNumber < 0 )	return ;
		else if( d_cardType == CARD_JOCKER )
			this->SetJocker();
		else
		{
			this->cardType = (CARD_TYPE)d_cardType;
			this->cardNumber = d_cardNumber;
			this->ChangeDraw( CARD_STATUS_FRONT );
		}
	}

	//---------------------------------
	//ジョーカーモードセッティング
	//---------------------------------
	void TrumpCard::SetJocker()
	{
		this->cardType = CARD_JOCKER;
		this->cardNumber = 0;
		this->ChangeDraw( CARD_STATUS_FRONT );
	}

	//-------------------------------------------------------
	//全体的なステップ
	//-------------------------------------------------------
	void TrumpCard::Step()
	{
		(this->*_action)();
	}

	//-----------------------------------------------------------------
	//描画方法の変更
	//-----------------------------------------------------------------
	void TrumpCard::ChangeDraw(int status)
	{
		this->cardStatus = (CARD_STATUS)status;
		switch( this->cardStatus )
		{
			case CARD_STATUS_BACK:
				this->_draw = &TrumpCard::backDraw;
				break;
			case CARD_STATUS_FRONT:
				switch( this->cardType )
				{
				case CARD_JOCKER:	this->_draw = &TrumpCard::jockerDraw;	break;
				case CARD_SPECIAL:	this->_draw = &TrumpCard::specialDraw;	break;
				default:			this->_draw = &TrumpCard::normalDraw;
				}
				break;
			case CARD_STATUS_DES:
				this->_draw = &TrumpCard::desDraw;
				break;
		}
	}

	//-------------------------------------------------------
	//描画
	//-------------------------------------------------------
	void TrumpCard::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->SetAlpha(BLEND_ALPHA1);
		(this->*_draw)();

		//セレクトしているときに矢印描画
		if( this->isSelectOK && this->cardStatus != CARD_STATUS_BACK )
			this->selectOKDraw();
	}

	void TrumpCard::selectOKDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans( D3DXVECTOR2(this->parts.pos.x - offSetX, this->parts.pos.y - offSetY + 70.0f),
			D3DXVECTOR2(50.0f, 25.0f), 
			1.57f,
			"yubi", DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	void TrumpCard::backDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans( D3DXVECTOR2(this->parts.pos.x - offSetX, this->parts.pos.y - offSetY),
				this->parts.scale, 
				this->parts.ang,
				"backcard", DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	void TrumpCard::normalDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans( D3DXVECTOR2(this->parts.pos.x - offSetX, this->parts.pos.y - offSetY),
			this->parts.scale, 
			this->parts.ang,
			trumpGraphList[ this->cardType ][ this->cardNumber ], DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	void TrumpCard::jockerDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans( D3DXVECTOR2(this->parts.pos.x - offSetX, this->parts.pos.y - offSetY),
			this->parts.scale, 
			this->parts.ang,
			"jocker", DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	void TrumpCard::specialDraw()
	{
		
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans( D3DXVECTOR2(this->parts.pos.x - offSetX, this->parts.pos.y - offSetY),
			this->parts.scale, 
			this->parts.ang,
			NameSpecialCardString[this->charaNumber], DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

}