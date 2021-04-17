#ifndef _MYGANE_DIALOG_H
#define _MYGANE_DIALOG_H

#ifndef _MYGAME_ONCEWORD_H
#include <OnceWord.h>
#endif

namespace MYGAME
{
	//----------------------------------------------
	//ダイアログで扱う構造体
	//パーツはここに定義していく
	//----------------------------------------------
	class DialogParts : public MYGAME::WordParts
	{
	public:
		int						width, height, frameCnt;
		bool					delFlag;
		
		DialogParts() : width(0), height(0), frameCnt(0), delFlag(false){}
		~DialogParts(){}

		DialogParts& operator = (DialogParts& in)
		{
			width = in.width;
			height = in.height;
			frameCnt = in.frameCnt;
			delFlag = in.delFlag;
			return *this;
		}
	};

	//----------------------------------------------
	//ダイアログ基本型
	//----------------------------------------------
	class SuperDialog : public NanairoLib::NormalObject
	{
		protected:
			int							selectNumber;
			NanairoLib::Vector2			offSetScale;
			MYGAME::DialogParts			parts;
			
		public:
			SuperDialog(){	this->sameInit();	}
			virtual ~SuperDialog(){}

		public:
			void sameInit();
			void SetDialogName(LPCSTR graphName){	this->parts.word =  (LPSTR)graphName;	}
			int GetSelectNumber(){		return this->selectNumber;	}
			MYGAME::DialogParts* GetParts() const{	return (MYGAME::DialogParts* const)&this->parts;	}
			void SetPos(NanairoLib::Vector2& ps){	this->parts.pos = (NanairoLib::Vector2)ps;	}
			void SetAng(float ag){					this->parts.ang = ag;	}
			void SetScl(NanairoLib::Vector2& sc){	this->parts.scale = (NanairoLib::Vector2)sc;	}

		public:
			bool IsAtack_boundingbox_leftBox(NanairoLib::PCVector2 atackPoint);
			bool IsAtack_boundingbox_centerBox(NanairoLib::PCVector2 atackPoint);
			bool IsAtack_circle(NanairoLib::PCVector2 atackPoint, NanairoLib::PCVector2 widhei);

		protected:
			void drawDialog();

		public:
			void SetTagObject(NanairoLib::RVector2 pos, float ang, NanairoLib::RVector2 sc);	
			
			void Init(){}
			void Step(){}
			void Draw2D(){	this->drawDialog();	}
			void Dispose(){}
	};

	//----------------------------------------------
	//名前画像のダイアログ
	//----------------------------------------------
	class NameDialog : public SuperDialog
	{
		private:
			LPCSTR nameWord;
		public:
			NameDialog();
			virtual ~NameDialog(){}
	
			void SetName(LPCSTR graphName){	this->nameWord =  graphName;	}
			void SetObject(NanairoLib::RVector2 pos, float ang, NanairoLib::RVector2 sc);
			void SetNameColor(NanairoLib::RVector4 col){	this->parts.color = col;	}
			void SetNameAlpha(float alpha){		this->parts.color.SetAlpha( (int)alpha );	}

			void DrawNameTag();
		public:
			virtual void Step(){}
			virtual void Draw2D();
	};

	//----------------------------------------------
	//名前画像のフェード型ダイアログ
	//----------------------------------------------
	class FadeNameDialog : public NameDialog
	{
		protected:
			bool selectFlag, waitFlag;	
			int interval, saveInterval;
			float fadeSpd;
			NanairoLib::Vector2 speed, ExpansionVector;

		private:
			void (FadeNameDialog::*_action)();
			void FadeAction(){	(this->*_action)();	}

		protected:
			virtual void Init(){}
			virtual void FadeIn(){}
			virtual void Wait(){}
			virtual void FadeOut(){}
			virtual void Dispose(){}
			
		public:
			FadeNameDialog();
			virtual ~FadeNameDialog(){}

			bool IncrementInterval(int inter){	return ( ++this->interval >= inter );	}
			bool DecrementInterval(int inter){	return ( --this->interval <= inter );	}

			void SetMoveObject_ofPos(NanairoLib::RCVector2 start, NanairoLib::RCVector2 goal, int inInterval);
			void SetMoveObject_ofScale(NanairoLib::RCVector2 start, NanairoLib::RCVector2 goal, int inInterval);

			bool IsWait(){		return this->waitFlag;	}
			void SetFadeIn(){	this->_action = &FadeNameDialog::FadeIn;	this->waitFlag = true;	}
			void SetWait(){		this->_action = &FadeNameDialog::Wait;		this->waitFlag = false;	}
			void SetFadeOut(){	this->_action = &FadeNameDialog::FadeOut;	this->waitFlag = true;	}
			void Step(){	(this->*_action)();	}
	};

	//-----------------------------------------------
	//基本的にフェード型ダイアログを継承して
	//操作を作る。
	//-----------------------------------------------
	class NormalSelectDialog : public FadeNameDialog
	{
	public:
		NormalSelectDialog(){}
		~NormalSelectDialog(){}

		void FadeIn(){}
		void Wait(){}
		void FadeOut(){}
	};
	
	//-------------------------------------------------------------
	//はい・いいえ型ダイアログ
	//-------------------------------------------------------------
	class YesNoDialog : public MYGAME::FadeNameDialog
	{
	private:	
		NameDialog *checkBox, *okBox;
	public:
		YesNoDialog(){	this->Init();	}
		~YesNoDialog();

		void Draw2D();
		void upPlayNameNumber(){	this->selectNumber = INCREMENT_SPECIAL( this->selectNumber, 2 );	}
		void downPlayNameNumber(){	this->selectNumber = DECREMENT_SPECIAL(this->selectNumber, 2);		}

		void Input_checkBox();
		void Input_okBox();
		bool MouseCheck();

	protected:
		void Init();
		void FadeIn();
		void Wait();
		void FadeOut();

		void PlayerDraw();
		void SelecterDraw();
	};

	//-------------------------------------------------------------
	//待機背景型ダイアログ
	//-------------------------------------------------------------
	class WaitBackDialog : public MYGAME::FadeNameDialog
	{
	private:
		float fadeSpd;

	public:
		WaitBackDialog(){	this->Init();	}
		~WaitBackDialog(){}

		void Draw2D();
		
	protected:
		void Init();
		void FadeIn();
		void Wait(){}
		void FadeOut();
	};

	//-------------------------------------------------------------
	//点滅ダイアログ
	//-------------------------------------------------------------
	class FlushingDialog : public MYGAME::FadeNameDialog
	{
	private:
		float fadeSpd;

	public:
		FlushingDialog(){	this->Init();	}
		~FlushingDialog(){}
		
	protected:
		void Init();
		void FadeIn(){	if( this->parts.color.FadeIn( this->fadeSpd ) )	this->SetFadeOut();	}
		void Wait(){}
		void FadeOut(){	if( this->parts.color.FadeOut( this->fadeSpd ) )	this->SetFadeIn();	}
	};

	//-------------------------------------------------------------
	//→画面外から←へスライドするフェード型ダイアログ
	//-------------------------------------------------------------
	class SlidesideDialog : public MYGAME::FadeNameDialog
	{
	public:
		SlidesideDialog(){	this->Init();	}
		~SlidesideDialog(){}

		void SetNumber(int num){	this->parts.pos.y = 200.0f + num * 100.0f;	}
		void onSelect();
		void offSelect();
	
	protected:
		void Init();
		void FadeIn();
		void Wait(){}
		void FadeOut();
	};

	//-------------------------------------------------------------
	//羊皮紙拡大型ダイアログ
	//-------------------------------------------------------------
	class ExpansionDialog : public MYGAME::FadeNameDialog
	{
	public:
		ExpansionDialog(){	this->Init();	}
		~ExpansionDialog(){}

		void SetNumber(int num){}
		void onSelect(){	this->selectFlag = true;	}
		void offSelect(){	this->selectFlag = false;	}
		
	protected:
		void Init();
		void FadeIn();
		void Wait(){}
		void FadeOut();
	};

	//-------------------------------------------------------------
	//→画面外から←へスライドするフェード型ダイアログ
	//-------------------------------------------------------------
	class SlidesideDialogLeft : public MYGAME::FadeNameDialog
	{
	private:
		bool				selectFlag, touchFlag;
		int					selectSpd, dialogSum;
		NanairoLib::Vector2	selectVec;
		std::string			touchisWord, touchnoWord;
	
	public:
		SlidesideDialogLeft(){	this->Init();	}
		~SlidesideDialogLeft(){}

		void SetNumber(int num, int dialogSum);
		bool isTouch(){	return this->touchFlag;	}

		void onTouch();		
		void onSelect();
		void offSelect();

		void upSelect();
		void downSelect();
		void normalSelect();
		void specSelect();

	protected:
		void Init();
		void FadeIn();
		void Wait();
		void FadeOut();
	};

	class NoticeDialog : public MYGAME::FadeNameDialog
	{
	private:
		bool boundFlag;
	public:
		NoticeDialog(){	this->Init();	}
		~NoticeDialog(){}

	protected:
		void Init();
		void FadeIn();
		void Wait();
		void FadeOut();
	};

	class ClickDialog : public FadeNameDialog
	{
	private:
		bool boundFlag;
	public:
		ClickDialog();
		~ClickDialog();

	protected:
		void Init();
		void FadeIn();
		void Wait();
		void FadeOut();


	};
}

#endif
