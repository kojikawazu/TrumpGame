#ifndef _NANAIRO_ROOMSCENE_H
#define _NANAIRO_ROOMSCENE_H

//#include <WinsockTCP.h>

#ifdef _VECTOR_
#include <vector>
#endif

///////////////////////////////////////////
//Default
///////////////////////////////////////////
#ifndef MYGAME_REDORCE_H
#include <ResourceFactory.h>
#endif

#ifndef _MYGAME_SHENE_H
#include <SceneMethod.h>
#endif

#ifndef _MYGAME_ONCEWORD_H
#include <OnceWord.h>
#endif

#ifndef _MYGANE_DIALOG_H
#include <Dialog.h>
#endif

///////////////////////////////////////////
//MYGAME
///////////////////////////////////////////
#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

///////////////////////////////////////////
//NanairoProject
///////////////////////////////////////////
#ifndef _NANAIRO_ROOMDIALOG_H
#include <SelectRoomDialog.h>
#endif

#ifndef _NANAIRO_TRUMPDEFINE_H
#include <TrumpDefine.h>
#endif

namespace NanairoProject
{
	//前方宣言ね
	class RoomScene;

	//データのパス情報
	const static char* DATAPASS = "./Resource/Data/GameData.gdata";
	
	/////////////////////////////////////////////////////////////////////////////////
	//総合ルームのダイアログの数
	#define SELECTIONROOM_DIALOGSUM  4

	//総合ルームのダイアログ番号
	enum SELECTROOM_SELECT_ENUM
	{
		SELECTROOM_NEW_GAME, SELECTROOM_CONTINUE_GAME, SELECTROOM_NET_GAME,
		SELECTROOM_GOBACK_TITTLE,
	};

	/////////////////////////////////////////////////////////////////////////////////
	//続きからルームのダイアログの数
	#define CONTINUEROOM_DIALOGSUM	4

	//続きからルームのダイアログ番号
	enum CONTINUEROOM_SELECT_ENUM
	{
		CONTINUEROOM_GAMESTART, CONTINUEROOM_SELECT_PLAYER, CONTINUEROOM_SELECT_RULE,
		CONTINUEROOM_GOBACK,
	};

	/////////////////////////////////////////////////////////////////////////////////
	//ネットゲームのダイアログ番号
	#define NETGAMEROOM_DIALOGSUM 3
	enum NETGAMEROOM_SELECT_ENUM
	{
		NETGAMEROOM_SERVER, NETGAMEROOM_CLIENT, NETGAMEROOM_GOBACK,
	};

	/////////////////////////////////////////////////////////////////////////////////
	//ルールセレクトのダイアログの数
	#define RULE_SELECTROOM_NEW_DIALOGSUM	4
	#define RULE_SELECTROOM_CONT_DIALOGSUM	2

	/////////////////////////////////////////////////////////////////////////////////
	//プレイヤーセレクトのダイアログ番号
	#define PLAYER_SELECTROOM_NEW_DIALOGSUM		3
	#define PLAYER_SELECTROOM_CONT_DIALOGSUM	2
	#define ROOM_PLAYERSUM						4
	enum PLAYERMAP_SELECT_NUM
	{
		PLAYERMAP_SELECT_NONE = 1, PLAYERMAP_SELECT_PLAYER, PLAYERMAP_SELECT_POWER
	};

	//----------------------------
	//一番最初のセレクトルーム
	//----------------------------
	class SelectingRoom : public MYGAME::SuperRoom
	{
	private:
		SelectingRoom(){}

	protected:
		void Input_SlidesideDialog();
		void Input_TittleDialog();
		void Input_NoticeDialog();
		bool KeyCheck();
		bool MouseClickCheck();
		void Decision();
		void AfterAction();
	
	public:
		SelectingRoom( MYGAME::SuperRoomScene* _pr );
		~SelectingRoom(){	this->Dispose();	}

		void Init();
		void Step();
		void Draw2D(){	this->Standard_Draw2D();	}
		void FadeIn(){	if( this->StandardStep() )	this->SetStep();	}
		void FadeOut(){	this->StandardStep();	}
		void SetFadeInS(){	this->Standard_SetFadeIn();	}
		void SetFadeOutS(){	this->Standard_SetFadeOut();	}
		
		void Dispose(){	this->dialogList.ListClear();	}
	};

	//----------------------------
	//続きから行うルーム
	//----------------------------
	class ContinueRoom : public MYGAME::SuperRoom
	{
	private:
		bool									outputFlag;
		RoomData								roomData;
		ContinueRoom(){}

	protected:
		void Input_SlidesideDialog();
		void Input_TittleDialog();
		void Input_PlayMapDialog();
		void Input_LookRuleDialog();
		void Input_DownSignDialog();
		void Input_NoticeDialog();

		bool KeyCheck();
		bool MouseCheck();
		void Decision();
		void AfterAction();
	
	public:
		ContinueRoom( MYGAME::SuperRoomScene* _pr, bool isSetData = true, bool IsOutput = true );
		~ContinueRoom();

		void Init();
		void Step();
		void Draw2D(){	this->Standard_Draw2D();	}
		void FadeIn();
		void FadeOut(){	this->StandardStep();	}
		void SetFadeInS(){	this->Standard_SetFadeIn();	}
		void SetFadeOutS(){	this->Standard_SetFadeOut();	}

		void InputRule(int r1, int r2, std::vector<CharaData>* _list);
		void OutputRule(int* r1, int* r2, std::vector<CharaData>* _list);

		void Dispose();
	};

	//---------------------------------------
	//サーバかクライアントかを選択するルーム
	//---------------------------------------
	class ServerHostRoom : public MYGAME::SuperRoom
	{
	private:
		ServerHostRoom(){}

	protected:
		void Input_SlidesideDialog();
		void Input_TittleDialog();
		void Input_NoticeDialog();
		bool KeyCheck();
		bool MouseClickCheck();
		void Decision();
		void AfterAction();
	
	public:
		ServerHostRoom( MYGAME::SuperRoomScene* _pr );
		~ServerHostRoom();

		void Init();
		void Step();
		void Draw2D();
		void FadeIn();
		void FadeOut();
		void SetFadeInS();
		void SetFadeOutS();
		
		void Dispose();
	};

	class ServerRoom : public MYGAME::SuperRoom
	{
	private:
		int searchIndex;
		bool isServer;
		bool isRunning;

		

	private:
		ServerRoom(){}

	protected:
		void Input_SlidesideDialog();
		void Input_TittleDialog();
		void Input_NoticeDialog();
		bool KeyCheck();
		bool MouseClickCheck();
		void Decision();
		void AfterAction();
	
	public:
		ServerRoom( MYGAME::SuperRoomScene* _pr );
		~ServerRoom();

		void Init();
		void Step();
		void Draw2D();
		void FadeIn();
		void FadeOut();
		void SetFadeInS();
		void SetFadeOutS();
		
		void Dispose();
	};

	//----------------------------
	//ルールセレクトルーム
	//----------------------------
	class RuleSelectRoom : public MYGAME::SuperRoom
	{
	private:
		int ruleSum;
		RuleSelectRoom(){}

	protected:
		void Input_SlidesideDialog();
		void Input_SlidesideDialog_newGame(int i, SlidesideDialog* point);
		void Input_SlidesideDialog_continueGame(int i, SlidesideDialog* point);
		void Input_SlidesideDialog_netGame(int i, SlidesideDialog* point);
		void Input_LeftSlideDialog();
		void Input_TittleDialog();
		void Input_NoticeDialog();

		bool KeyCheck(int *selface);
		bool MouseCheck();
		bool MouseSlideCheck(int *selface);

		void MoveAction();
		void MoveAction_newGame();
		void MoveAction_continueGame();
		void MoveAction_netGame();
		void DialogChange(int selface, int oldNum);
		void AfterAction();
	
	public:
		RuleSelectRoom( MYGAME::SuperRoomScene* _pr, bool isSetData = true );
		~RuleSelectRoom(){		this->Dispose();	}

		void Init();
		void Step();
		void Draw2D(){	this->Standard_Draw2D();	}
		void FadeIn(){	if( this->StandardStep() )	this->SetStep();	}
		void FadeOut(){	this->StandardStep();	}
		void SetFadeInS(){	this->Standard_SetFadeIn();	}
		void SetFadeOutS(){	this->Standard_SetFadeOut();	}

		void AllSelect();
		void OutputRule(int* inputRule, int* inputRule2);
		void inputRule(int inputRule, int inputRule2);

		void gotoGame();
		void goPlaySelectRoom();
		void goContinueRoom();
		void gobacktoTittle();
		void EachOtherAction();

		void Dispose(){	this->dialogList.ListClear();	}
	};

	//----------------------------
	//ルールセレクトルーム
	//----------------------------
	//----------------------------
	//一番最初のセレクトルーム
	//----------------------------
	class GameWaitRoom : public MYGAME::SuperRoom
	{
	private:
		int									ruleData1, ruleData2;
		MYGAME::ExpansionDialog*			titleDialog;
		std::vector<CharaData>				charaData;
		GameWaitRoom(){}

	protected:
		void Input_SlidesideDialog();
		void Input_TittleDialog();
		bool KeyCheck();
		void AfterAction();
	
	public:
		GameWaitRoom( MYGAME::SuperRoomScene* _pr, bool isSetData = true );
		~GameWaitRoom();

		void Init();
		void Step();
		void Draw2D();
		void FadeIn();
		void FadeOut();
		void SetFadeInS();
		void SetFadeOutS();

		void InputRule(int r1, int r2, std::vector<CharaData>* _list);
		void OutputRule(int* r1, int* r2, std::vector<CharaData>* _list);

		void Dispose();
	};

	//----------------------------
	//プレイヤーセレクトルーム
	//----------------------------
	class PlayerMapControl
	{
	private:
		
		int playSum;
		std::vector<CharaData>							charaDataList;
		PlayerMapDialog*								nowPlayermap, *nextPlayerMap;
		MYGAME::ObjectList<NanairoLib::PNormalObject>	Playermaplist, nextPlayermaplist;
		std::string										updownWord, okWord;
	public:
		RoomScene*										_parent;
		PlayerMapControl(RoomScene* _in);
		~PlayerMapControl();
		
		std::vector<CharaData>* GetCharaDataList() const{	return (std::vector<CharaData>* const)&this->charaDataList;	}
		PlayerMapDialog* GetNowPlayerMap() const{			return this->nowPlayermap;	}
		PlayerMapDialog* GetNextPlayerMap() const{			return this->nextPlayerMap;	}

		void Init(int playSum);
		void Dispose();
		bool Step();
		bool FadeIn();
		bool FadeOut();
		void Draw2D();

		void Input_playerMapDialog(int playSum);
		void SetFadeIn();
		void SetFadeOut();
		void SetFadeOutList();
		void SetNowPlayerMap_FadeOut();

		void NewAllPlayerMap();
		void NewSelectPlayerMap(int selectNum, bool IsContinue);
		void ChangeAllPlayerMap();
		void ChangePlayerMap(int selectNum, bool IsContinue);
		void SwitchDialog();
		bool MouseCheck();

		bool Step_SelectPlayer(int selectNum);
		bool Step_SelectRule(int selectNum);

		void UpdownMusic();
		void okMusic();

		void InputRule(std::vector<CharaData>* _list);
		int OutputRule(std::vector<CharaData>* _list);
	};

	class PlayerSelectRoom : public MYGAME::SuperRoom
	{
	private:
		int					playerSum, oldSelectNumber, waitCnt;
		PlayerMapControl*	control;	
		MYGAME::NoticeDialog*		noticeDialog;

	private:
		PlayerSelectRoom(){}

		void Input_SlidesideDialog();
		void Input_SlidesideDialog_newGame(int i, SlidesideDialog* point);
		void Input_SlidesideDialog_continueGame(int i, SlidesideDialog* point);
		void Input_SlidesideDialog_netGame(int i, SlidesideDialog* point);
		void Input_BoxDialog();
		void Input_TittleDialog();
		void Input_NoticeDialog();

		bool KeyCheck();
		bool MouseCheck();
		bool MouseCheck_playerSelect();
		bool MouseCheck_ruleSelect();
		bool PlayerMapAction(){	return this->control->Step();	}
		void MoveChange();
		void MoveChange_newGame();
		void MoveChange_continueGame();
		void MoveChange_netGame();
		void AfterAction();
		void AllSelecting();

		void goPlaySelect();
		void gobacktoOnce();
		void gobacktoServerHost();
		void gobacktoContinue();
		void EachOtherAction();
		void OnTouch(int touchNum = -1);
	
		void (PlayerSelectRoom::*_selectAction)();
		void select_normalAction();
		void select_playerAction();
		void select_playerNameAction();
		void select_powerAction();

		void FadeIn();
		void FadeOut();
	public:
		PlayerSelectRoom( MYGAME::SuperRoomScene* _pr, bool isSetData = true );
		~PlayerSelectRoom(){	this->Dispose();	}

		void Init();
		void Step();
		void Draw2D();
		void SetFadeInS();
		void SetFadeOutS(); 

		void Dispose();
	};

	///////////////////////////////////////////////////////////////////////////

	//-------------------------------------------------------------------------
	//ルームシーン
	//-------------------------------------------------------------------------
	class RoomScene : public MYGAME::SuperRoomScene
	{
		private:
			RoomData				roomData;
			
		public:
			RoomScene(){	this->Init();	}
			~RoomScene(){	this->Dispose();	}

			void SetRuleData(int r1, int r2);
			RoomData*	GetRoomData(){				return &this->roomData;		}

		private:
			void InputKirariEffect();

			void TouchAction();
			void waitAndGoAction();
			void WaitAndBackAction();
			void WaitAndChangeDialogAction();
			void ChangeSceneAction();
			void YesnoDialogAction();
			
		public:
			void Init();
			void LoadData();
			void WriteData();
	};
}

#endif