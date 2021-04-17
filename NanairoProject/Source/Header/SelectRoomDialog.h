#ifndef _NANAIRO_ROOMDIALOG_H
#define _NANAIRO_ROOMDIALOG_H

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

#ifndef _NANAIRO_TRUMPDEFINE_H
#include <TrumpDefine.h>
#endif

#ifndef _NANAIRO_PLATEEFFECT_H
#include <PlateEffect.h>
#endif

namespace NanairoProject
{
	class PlayerMapDialog;

	//------------------------------------
	//データ
	//------------------------------------
	//プレイヤーの人数	: int
	//ルール×２		: int
	//プレイヤー情報	: int
	//-キャラクター番号	: int
	//プレイヤーか敵か	: bool
	//-スコア			: int
	//-強さ				: int
	//-----------------------
	//キャラクターデータ
	//-----------------------
	class CharaData
	{
	public:
		bool poreFlag, selectFlag;
		int spec, charaNum, score, runk;

		CharaData()
		{
			poreFlag = selectFlag = false;
			spec = charaNum = score = runk = 0;
		}
	};
	
	//---------------------------------------------
	//ルームデータ
	//---------------------------------------------
	class RoomData
	{
	public:
		int						rule, rule2, playSum, roundCount;
		std::vector<CharaData>	charaData;

		RoomData() : rule(0), rule2(0), roundCount(0), playSum(1)
		{
			this->Init();
		}

		void Init()
		{
			this->rule = this->rule2 = this->roundCount = 0;
			this->playSum = 1;
			this->charaData.resize( PLAYER_MAX );
			for(int i=0; i<PLAYER_MAX; i++)
			{
				this->charaData[i].charaNum = i;
				this->charaData[i].poreFlag = (i==0);
				this->charaData[i].selectFlag = (i==0);
				this->charaData[i].spec = 0;
				this->charaData[i].score = 0;
				this->charaData[i].runk = i;
			}
		}
	};

	//-------------------------------------------------------------
	//ルール見るだけ型ダイアログ
	//-------------------------------------------------------------
	#define ONERULE_SUM 7
	#define RULE_SUM	10
	class LookatRuleDialog : public MYGAME::FadeNameDialog
	{
	private:
		bool selectFlag, touchFlag;
		int selectSpd, dialogSum;
		NanairoLib::Vector2 selectVec;
	
	public:
		LookatRuleDialog();
		~LookatRuleDialog();

		void SetNumber(int num, int dialogSum);
		bool isTouch(){	return this->touchFlag;	}

		void SetPosing(NanairoLib::Vector2& start, NanairoLib::Vector2& end, int interval, int number);

		void onTouch();		
		void onSelect();
		void offSelect();

	protected:
		void Init();
		void FadeIn();
		void Wait();
		void FadeOut();
	};

	//-------------------------------------------------------------
	//プレイヤー選択型ダイアログ
	//-------------------------------------------------------------
	class BoxExpansionDialog : public MYGAME::FadeNameDialog
	{
	private:
		bool touchFlag;

	public:
		BoxExpansionDialog();
		~BoxExpansionDialog();

		void SetNumber(int num);
		void onSelect();
		void offSelect();
		void onTouch();
	
	protected:
		void Init();
		void FadeIn();
		void Wait(){}
		void FadeOut();
	};

	//-------------------------------------------------------------
	//プレイヤー選択型ダイアログパート２
	//-------------------------------------------------------------
	class PlayerFukidasiDialog : public MYGAME::FadeNameDialog
	{
	private:
		PlayerPlate	*playTag[PLAYERNAME_MAX];
		MYGAME::NameDialog		*checkBox, *titleTag;
		MYGAME::NoticeDialog	*CheckTag, *introduceTag;
	public:
		PlayerFukidasiDialog();
		~PlayerFukidasiDialog();
		

		int GetSelectNumber(){	return this->selectNumber;	}
		void SetNumber(int num);
		void Draw2D();
		void upPlayNameNumber();
		void downPlayNameNumber();

		bool IsMouseAtack();

		void Input_titleTag();
		void Input_checkTag();
		void Input_checkBox();
		void Input_playerTag();
		void Input_IntroduceTag();

	protected:
		void Init();
		void FadeIn();
		void Wait();
		void FadeOut();

		void PlayerDraw();
		void SelecterDraw();
		void TittleDraw();
		void CheckerDraw();
		void IntroduceDraw();
	};

	//-------------------------------------------------------------
	//敵ＡＩレベル選択型ダイアログパート
	//-------------------------------------------------------------
	class PowerFukidasiDialog: public MYGAME::FadeNameDialog
	{
	private:
		MYGAME::NameDialog		*powerTag[POWER_ENUM_SUM], *checkBox, *titleTag;
		MYGAME::NoticeDialog	*CheckTag;

	public:
		PowerFukidasiDialog();
		~PowerFukidasiDialog();

		int GetSelectNumber(){	return this->selectNumber;			}
		void SetSelectNumber(int num){	this->selectNumber = num;	}
		bool IsMouseAtack();
		void SetNumber(int num);
		void Draw2D();
		void upPlayNameNumber();
		void downPlayNameNumber();

		void Input_powerTag();
		void Input_titleTag();
		void Input_checkTag();
		void Input_checkBox();

	protected:
		void Init();
		void FadeIn();
		void Wait();
		void FadeOut();

		void TittleDraw();
		void PlayerDraw();
		void SelecterDraw();
		void CheckerDraw();
	}; 

	//------------------------------------------------------------
	//プレイヤー情報型ダイアログ
	//------------------------------------------------------------
	class PlayerMapDialog : public MYGAME::FadeNameDialog
	{
	private:
		bool					touchFlag, moveFlag, continueFlag, scoreFlag;
		int						selectNumber, selectDialogNumber;
		CharaData				charaData;
		NanairoLib::Vector2		yajiPos;
		PlayerFukidasiDialog*	fukidasiDialog;
		PowerFukidasiDialog*	powerDialog;
		MYGAME::NameDialog		*playTitleNameDialog, *batuDialog, 
								*allowDialog, *scoreNameDialog, *powerNameDialog, *runkerNameDialog;
		MYGAME::NumbersWord		*scoreNumber;
		PlayerPlate			*playerNameDialog;
	
	public:
		PlayerMapDialog();
		~PlayerMapDialog();
		
		bool isTouch(){					return this->touchFlag;	}
		bool isMove(){					return this->moveFlag;	}
		
		PlayerFukidasiDialog* GetPlayerFukidasiDialog() const{		return this->fukidasiDialog;						}
		PowerFukidasiDialog*  GetPowerFukidasiDialog() const{		return this->powerDialog;							}
		PlayerPlate* GetPlayerPlateDialog() const{			return this->playerNameDialog;						}
		MYGAME::NameDialog*	GetPowerPlateDialog() const{			return this->powerNameDialog;						}
		int GetSelectDialogNumber(){								return this->selectDialogNumber;					}
		CharaData* GetCharaData(){									return &this->charaData;							}
		
		void SetNumber(CharaData* _data, int number, bool IsContinue, bool isMode = false);
		void SetScore(bool IsOn){				this->scoreFlag = IsOn;				}
		void SetSelectDialogNumber(int number){	this->selectDialogNumber = number;	}
		void SetCharaNumber(int num){			this->charaData.charaNum = num;		}

		void onSelect(){	this->touchFlag = true;		}
		void offSelect(){	this->touchFlag = false;	}
		void onComputer(){	this->charaData.selectFlag = !this->charaData.selectFlag;	}
		
		void startDialogNumber();
		void upDialogNumber();
		void downDialogNumber();
		void stopDialogNumber();

		void startPlayNameNumber();
		void upPlayNameNumber();
		void downPlayNameNumber();
		void stopPlayNameNumber();

		void startPowerNumber();
		void upPowerNumber();
		void downPowerNumber();
		void stopPowerNumber();

		void onFukidasi();
		void offFukidasi();

		void FukidasiStep();
		void Draw2D();

	protected:
		void Init();
		void FadeIn();
		void Wait(){}
		void FadeOut();

		void ScoreDraw();
		void MapNameDraw();
		void PlayerCharaDraw();
		void PowerDraw();
		void YajirushiDraw();
		void RunkerDraw();
		void BatuDraw();
	};

	class DownSignDialog : public MYGAME::FadeNameDialog
	{
	private:
		int roundNumber;

	public:
		DownSignDialog();
		~DownSignDialog();
		void	SetRound(int dround){		this->roundNumber = dround + 1;			}
		void Draw2D();
		
	protected:
		void Init();
		void FadeIn();
		void Wait(){}
		void FadeOut();
	};
}

#endif