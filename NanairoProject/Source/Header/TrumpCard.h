#ifndef _NANAIRO_TRUMP_H
#define _NANAIRO_TRUMP_H

////////////////////////////////////
//MYGAME
////////////////////////////////////
#ifndef _MYGAME_UIPARTS_H
#include <UIParts.h>
#endif

#ifndef _NANAIRO_TRUMPDEFINE_H
#include <TrumpDefine.h>
#endif

namespace NanairoProject
{
	//-----------------------------
	//トランプカード
	//-----------------------------
	class TrumpCard
	{
	private:
		bool isSelectOK, isAction;
		int cardNumber, moveCnt, charaNumber;
		float offSetAng;
		CARD_TOUCHSTATUS_TOUCH_STATUS isMouseTouch;
		CARD_STATUS cardStatus;
		CARD_TYPE cardType;
		
	public:
		int offSetX, offSetY;
		NanairoLib::UIParts2D parts;
		NanairoLib::Vector2 offSet;

	private:		
		void (TrumpCard::*_draw)();
		void selectOKDraw();
		void normalDraw();
		void jockerDraw();
		void specialDraw();
		void backDraw();
		void desDraw(){}

		
		void waitAction(){}
		void centerMoveAction();
		void SetOffSetChange();
		void fadeInAction();
		void FadeOutAction();

		void Init();
		void SetObject(){}

		void (TrumpCard::*_action)();
		//タッチチェック
		void TouchAction(bool isOn);

	public:
	
		TrumpCard() : cardType(CARD_HEART), cardNumber(0), cardStatus(CARD_STATUS_DES), offSetY(0){	this->Init();	}
		~TrumpCard(){}

		//Getter
		bool GetSelectOK(){		return this->isSelectOK;	}
		CARD_TYPE GetCardType(){	return this->cardType;	}
		int GetMouseTouch(){	return this->isMouseTouch;	}
		int GetCardStatus(){	return this->cardStatus;	}
		int GetCardNumber(){	return this->cardNumber;	}
		int GetTrumpNumber(){	return TRUMP_POWER[ this->cardNumber ];		}
		int GetCharaNumber(){	return this->charaNumber;	}

		//Is
		bool isJocker(){		return ( this->cardType == CARD_JOCKER );	}
		bool isSpecial(){		return ( this->cardType == CARD_SPECIAL);	}
		bool isCardER(){	return (this->cardStatus == CARD_STATUS_DES || this->isSelectOK ); }
		bool isCardDes(){	return (this->cardStatus == CARD_STATUS_DES);						}

		//Setter
		void SetCardType(CARD_TYPE type){	this->cardType = type;	}
		void SetCharaNumber(int number);
		void SetCenterMove(int tempI, int siz);
		void onSelectOK(){		this->isSelectOK = true;	}
		void offSelectOK(){		this->isSelectOK = false;	}
		void SettingCardTouch(){	this->isMouseTouch = CARD_TOUCHSTATUS_CLICK;	}
		void SettingOffCardTouch(){	this->isMouseTouch = CARD_TOUCHSTATUS_NO_TOUCH;	}
		void SettingCardDel(){		this->cardStatus = CARD_STATUS_DES;				}
		void SetTouchActionS(){		this->_action = &TrumpCard::SetOffSetChange;	}
		void SetFadeIn(int number);
		void SetFadeInS();
		void SetFadeOut();
		void SetActionCard(bool isOn){		this->isAction = isOn;	}
		//カード番号のセッティング
		void SetCardNumber(int d_oneCardNumber);
		void SetCardNumber(int d_cardNumber, int d_cardType);
		void SetCardNumber_about(int dnumber){	this->cardNumber = dnumber;	}
		//ジョーカーモードのセッティング
		void SetJocker();
		//その他のセッティング
		void SetOnOrOff();

		bool checkTouch();

		//メインアクション
		void Step();

		//２D描画
		void Draw2D();
		void ChangeDraw(int status);

	public:
		TrumpCard& operator = (TrumpCard& in)
		{
			isSelectOK = in.isSelectOK;
			//isAction = in.isAction;
			cardNumber = in.cardNumber;
			moveCnt = in.moveCnt;
			offSetAng = in.offSetAng;
			isMouseTouch = in.isMouseTouch;
			cardStatus = in.cardStatus;
			cardType = in.cardType;
			offSetX = in.offSetX;
			offSetY = in.offSetY;
			parts = in.parts;
			offSet = (NanairoLib::Vector2)in.offSet;
			
			this->_action = in._action;
			this->_draw = in._draw;		

			return *this;
		}

	};

}

#endif