#ifndef _MYGAME_SHENE_H
#define _MYGAME_SHENE_H

//--------------------------------------------------------
//
//ゲームのシーンとシーンマネージャのクラスヘッダ
//
//--------------------------------------------------------

//std--------------
#ifndef _LIST_
#include <list>
#endif

//MYGAME-------------
#ifndef _MYGAME_UIPARTS_H
#include <UIParts.h>
#endif

#ifndef _MYGAME_SUPERSHENE_H
#include <SuperScene.h>
#endif

#ifndef _MYGAME_ONCEWORD_H
#include <OnceWord.h>
#endif

#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

#ifndef _MYGANE_DIALOG_H
#include <Dialog.h>
#endif

#ifndef MYGAME_REDORCE_H
#include <ResourceFactory.h>
#endif

namespace MYGAME
{
	//-----------------------------------------
	//シーンチェンジスーパークラス
	//-----------------------------------------
	#define TIMING_DEFAULT_CHANGE	120
	#define TIMING_DEFAULT_DISPOSE	240
	class SuperChangeScene : public MYGAME::Scene
	{
		protected:
			int							timingChange, timingDispose;
			MYGAME::BackGround_2D		back;
			MYGAME::Scene* oldScene,	*newScene;
		
		public:
			SuperChangeScene() : oldScene(NULL), newScene(NULL){}
			SuperChangeScene(MYGAME::Scene* newSC, MYGAME::Scene* oldSC = NULL){	this->sameInit( newSC, oldSC );	}
			virtual ~SuperChangeScene(){	ES_SAFE_DELETE( this->newScene );	}

		protected:
			void Draw3D(){}
			void Draw2D(){	back.Draw2D();	}
	
		public:
			void Init(){}
			void Recircle(){}
			void Draw();
			void Atack(){}

			//使用しているのはこの３つ！
			void Step();
			void Dispose();
			void Del(){}
		public:
			//static Scene* SettingChangeScene(LPCSTR fileName, LPCSTR sceneName, Scene* old);

		protected:
			void changeScene();
			void sameInit(MYGAME::Scene* newSC, MYGAME::Scene* oldSC);
	};

	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	//ロード関数の最大（マルチスレッド増やすとここも増やすこと）
	#define LOADING_SUM_MAX	1

	//ロードがすべて終わってもウェイトをつけておくようにする
	//そのウェイト時間
	#define TIMEOUT_MAX		60

	//非同期ロードに必要なパーツ
	struct LoadingField
	{
		HANDLE loadHandle;
		DWORD threadID;
	};

	enum GAMEMODE_ENUM
	{
		GAMEMODE_NEWGAME, GAMEMODE_CONTINUEGAME, GAMEMODE_NETGAME,
	};

	//長い型に新しい名前を付けること
	//今回はリストとイテレータ
	typedef std::list<LoadingField*>			LoaderList;
	typedef std::list<LoadingField*>::iterator	LoaderIterator;

	//---------------------------------------
	//ロードの基本型
	//これを継承してシーンを作る
	//---------------------------------------
	class SuperLoading : public MYGAME::Scene
	{
		protected:
			bool							isStep, isSucceess, isFinished;		//ロードの初期化成功？、ロード終了？
			int								timeoutCnt;							//タイムアウトカウンタ
			LoaderList						loader;								//ロードハンドルのリスト
			MYGAME::ObjectList<OnceWord*>	word;								//ロード中と示す文字
			MYGAME::LoaderGraphList*		graphLoader;
			MYGAME::Scene*					nextScene;

		public:
			SuperLoading() : isStep(false), isSucceess(false), isFinished(false), timeoutCnt(0), nextScene(NULL), graphLoader(NULL){}
			virtual ~SuperLoading();

		protected:
			void Draw3D(){}
			void Draw2D(){}
			void loadObject(std::ifstream& fs){}
	
		public:
			void Init(){}
			void Recircle(){}
			void Draw(){}
			void Atack(){}

			//使用しているのはこの３つ！
			void Step(){	this->LoadingStep();	}
			void Dispose(){	this->closeLoadingThread();	}
			void Del(){}

			void LoadingStep();
			void SetScene(MYGAME::Scene* in){	this->nextScene = in;	}

		protected:
			virtual bool initLoadingThread(){	return false;	}
			bool push(LoadingField* field);
			void closeLoadingThread();
			bool isFinish();
	};

	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	//----------------------------
	//ルームの基本型
	//----------------------------
	class SuperRoomScene;
	class SuperRoom
	{
	protected:
		SuperRoomScene* _parent;
		int dialogSum, selectNumber;
		std::string updownWord, okWord;
		MYGAME::ObjectList<NanairoLib::PNormalObject>	dialogList;
	protected:
		SuperRoom()	: _parent(NULL), dialogSum(0), selectNumber(0){	this->SetFadeIn();	}
		void (SuperRoom::*_Action)();
		

	public:
		
		SuperRoom( SuperRoomScene* _pr ) : _parent(_pr){	this->SetFadeIn();	}
		virtual ~SuperRoom(){	_parent = NULL;	}
		SuperRoomScene* GetParent(){	return _parent;	}

		virtual void Init() = 0;
		virtual void Draw2D() = 0;
		virtual void Step() = 0;
		virtual void FadeIn() = 0;
		virtual void FadeOut() = 0;
		virtual void SetFadeInS(){}
		virtual void SetFadeOutS(){}

		void UpdownMusic();
		void okMusic();
		bool StandardStep();
		void Standard_SetFadeIn();
		void Standard_SetFadeOut();
		void Standard_Draw2D();

		void Action(){	(this->*_Action)();	}
		void SetFadeIn(){	this->_Action = &SuperRoom::FadeIn;	this->SetFadeInS();	}
		void SetStep(){	this->_Action = &SuperRoom::Step;	}
		void SetFadeOut(){	this->_Action = &SuperRoom::FadeOut; this->SetFadeOutS();	}
	};

	class SuperRoomScene : public MYGAME::Scene
	{
		protected:
			bool										serverFlag;
			GAMEMODE_ENUM								gameMode;
			std::string									SEupdown, SEok,	SEback;
			SuperRoom									*nowPoint, *nextPoint;
			MYGAME::BackGround_2D						back;
			MYGAME::ObjectList<NanairoLib::PEffect2D>	effectList, afterEffectList;
			MYGAME::YesNoDialog*						yesnoDialog;

		public:
			SuperRoomScene(){			this->Init();	}
			virtual ~SuperRoomScene(){	this->Dispose();	}

			void SetBackToTittle();
			void SetGoToGame();
			void SetYesnoDialog();
			void SetChangeDialog(SuperRoom* next);
			void SetServerFlag(bool IsOn){						this->serverFlag = IsOn;	}
			bool			IsServer(){							return this->serverFlag;	}
			GAMEMODE_ENUM	 GetGameMode(){						return this->gameMode;		}
			void ChangeGameMode(GAMEMODE_ENUM mode){			this->gameMode = mode;		}
			bool IsContinue(){									return (this->gameMode == GAMEMODE_CONTINUEGAME);	}
			bool IsNetGame(){									return (this->gameMode == GAMEMODE_NETGAME);	}
			MYGAME::ObjectList<NanairoLib::PEffect2D>*	GetEffectList(){	return &this->effectList;	}
			void SetTouchActions(){	this->_action = &SuperRoomScene::TouchAction;	}
			void SetChangeAction(){	this->_action = &SuperRoomScene::ChangeSceneAction;	}

		private:
			void (SuperRoomScene::*_action)();
			virtual void TouchAction() = 0;
			virtual void waitAndGoAction() = 0;
			virtual void WaitAndBackAction() = 0;
			virtual void WaitAndChangeDialogAction() = 0;
			virtual void ChangeSceneAction() = 0;
			virtual void YesnoDialogAction() = 0;

		protected:
			void Draw3D(){}
			void Draw2D();

			
		public:
			void Init();
			void Recircle(){}
			void Draw();
			void Atack(){}

			//使用しているのはこの３つ！
			void Step();
			void Dispose();
			void Del(){}

			void playSE_updown();
			void playSE_ok();
			void playSE_back();
	};
}

#endif
