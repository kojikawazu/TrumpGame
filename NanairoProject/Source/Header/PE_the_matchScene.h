#ifndef _NANAIRO_PEMATCH_SCENE_H
#define _NANAIRO_PEMATCH_SCENE_H

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

#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _LIST_
#include <list>
#endif

///////////////////////////////////////////
//NanairoProject
///////////////////////////////////////////
#ifndef _NANAIRO_GEST_H
#include <GestChara.h>
#endif

#ifndef _NANAIRO_PLATEEFFECT_H
#include <PlateEffect.h>
#endif

#ifndef _NANAIRO_ROOMSCENE_H
#include <RoomScene.h>
#endif

namespace NanairoProject
{
	class GameScene;

	//---------------------------------------------------------------
	//スコアマップ
	//---------------------------------------------------------------
	class ScoreMap
	{
	private:
		NanairoLib::UIParts2D	parts;
		NanairoLib::Vector2	offSet, offSetScale;
		std::vector<int>	score, runk, oldScore, oldRunk;
		std::vector<std::string>	playerName;
		
		PlayerPlate			*playerTag;
		MYGAME::NameDialog	*arrowTag, *mapPlateTag, *mapTag, *bigTag, *updownTag;
		MYGAME::NumbersWord *scoreTag, *runkNumberTag;

	private:
		int isRunkUpper(int i);
		void plusScore(std::vector<int>& nowRunkList, std::vector<int>& dscore, int capitalSum, int foelSum);
		
		void Input_playerTag();
		void Input_scoreNumberTag();
		void Input_arrowTag();
		void Input_mapTag();
		void Input_mapPlateTag();
		void Input_bigTag();
		void Input_scoreTag();
		void Input_updownTag();

		void (ScoreMap::*Action)();
		void fadeIn();
		void wait(){}
		void buttonWait(){	(this->*ScaleAction)();	}
		void fadeOut();

		void (ScoreMap::*ScaleAction)();
		void scaleFadeIn();
		void scaleFadeOut();

		void mapDraw();
		void plateDraw();
		void scoreDraw();
		void biggerDraw();
		void updownDraw(int i, int sc, float temp);
		void uppersSumDraw(int i, int sc, float temp);
		void arrowDraw(int i, int sc, float temp);

		void scoreDraw_inScore(int i, int sc, float temp);
		void scoreDraw_inUpper(int i, int sc, float temp);
		void scoreDraw_inRunker(int i, int sc, float temp);
		void scoreDraw_inPlayerName(int i, int sc, float temp);
		
	public:
		ScoreMap(){	this->Init();		}
		~ScoreMap(){	this->Dispose();	}


		std::vector<int>* GetOldRunk(){	return &this->oldRunk;	}
		void judgeRunk(std::vector<int>& nowRunkList, int capitalSum, int foelSum);
		void SetPlaySum(int sum);
		void inScoreMap();
		void outScoreMap();
		void scoreContinue();
		void Sort(bool isUp = false);
		void GetScoreAndRunk(RoomData& _data);
		void inputScoreData(RoomData& _data, bool IsContinue);
		int GetPlayerRunkNumber(int runk);
		void SetPlayerName(std::vector<std::string>& str);

		void Init();
		void Step(){	(this->*Action)();	}
		void Draw();
		void Dispose();
	};

	//---------------------------------------------------------------
	//ゲーム開始時に渡されるデータ
	//---------------------------------------------------------------
	struct CardgameRule
	{
		int playSum, inputRule;
		ENEMY_POWER power;
	};

	//////////////////////////////////////////
	//ジャッジメントで必要なデータ
	//////////////////////////////////////////
	//int		: 表に出したカードの枚数
	//int		: 何枚出せるかのカードの枚数
	//int		: チェックするカード番号
	//int		: ルール上のステータス
	//vector	: 表に出したカードリスト
	class JudgementCard
	{
	private:
		int playSum, nowPlayNumber, rule, inputRule, inputRule2, gameCount;
		ENEMY_POWER power;
		NanairoLib::Textcolor yourtornColor;
		GameScene* _game;
	public:
		bool foulFlag, gameStartFlag, gamewaitFlag;
		int frontCardSum, stateCardSum, nowCard, passCnt, winSum, foulSum;
		int specialCharaNum, specialRunkNum;
		std::vector<TrumpCard> frontCard;
		std::vector<CARD_TYPE> restrainsType;
		std::vector<int>	winnerList;
		PlateList<PlateEffect*>		plateList;
		PlateList<SuperMillionareEffect*>	runkList;
		PlateList<PlayerPlate*>		playerPlateList;
		ScoreMap			scoreMap;
		MYGAME::ObjectList<NanairoLib::PNormalObject>	effectList;
		RoomData			roomData;

	public:
		JudgementCard(){	this->Init();		}
		void SetGame(GameScene* _in){	_game = _in;		}
		~JudgementCard(){	this->Dispose();	}

		void Init();
		void gameContinue();
		void Step();
		void Dispose();

		void Draw2D();

		void (JudgementCard::*yourtornAction)();
		void youtornFadeIn();
		void youtornFadeOut();
		void youtornDraw();

		bool checkPassCount();
		void reSet_toRule();

		void effectStep();
		void pushPassEffect(int number);
		void pushRoundStart(int round);
		void push_ruleEffect(int rule);
		void push_specialEffect(int specNum);
		void push_starEffect(int number);
		void push_foulEffect(int number, int foulNumber);
		void push_cardChangeEffect();

		void cardSort(int in, int out);
		void cardSord_sounyu(int in, int out);
		void push_winner(Gest* gest, int number);

		int GetGameCount(){				return this->gameCount;		}
		int GetPlaySum(){				return this->playSum;		}
		int GetNowPlayNum(){			return this->nowPlayNumber;	}
		ENEMY_POWER GetRulePower(){		return this->power;			}

		void runkList_ofRewrite();
		void SettingNowPlayer();
		void SettingNowPlayer2();
		void SetPlaySum(int sum){		this->playSum = sum;		}
		void SetNowPlayNum(int num){	this->nowPlayNumber = num;	}
		void playNumberPlus(int plus);
		void playNumberManu(int plus);
		//ルールチェック
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isUseRevolution(){	return ( (inputRule & TRUMP_RULE_REVOLUTION) > 0 );	}
		bool isUseSame(){		return ( (inputRule & TRUMP_RULE_SAME) > 0 );		}
		bool isUseStairs(){		return ( (inputRule & TRUMP_RULE_STAIRS) > 0 );		}
		bool isUseEightcut(){	return ( (inputRule & TRUMP_RULE_EIGHTCUT) > 0 );	}
		bool isUseElevenback(){	return ( (inputRule & TRUMP_RULE_ELEVENBACK) > 0 );	}
		bool isUseRestrains(){	return ( (inputRule & TRUMP_RULE_RESTRAINS) > 0 );	}
		bool isUseSpade3(){		return ( (inputRule & TRUMP_RULE_SPADE3) > 0 );		}
		bool isUseJocker(){		return ( (inputRule & TRUMP_RULE_JOCKER) > 0 );		}
		bool isUseCapitaldown(){	return ( (inputRule2 & TRUMP_RULE_CAPITALDOWN) > 0 );	}
		bool isUseFoul(){			return ( (inputRule2 & TRUMP_RULE_FOUL) > 0 );			}
		bool isUseCardChange(){		return ( (inputRule2 & TRUMP_RULE_CARDCHANGE) > 0 );	}

		bool isRevolution(){	return ( ( this->isUseRevolution() && (rule & TRUMP_RULE_REVOLUTION) > 0 ) ? !this->isElevenback() : this->isElevenback() );	}
		bool isSame(){			return ( this->isUseSame() && (rule & TRUMP_RULE_SAME ) > 0); }
		bool isStairs(){		return ( this->isUseStairs() && (rule & TRUMP_RULE_STAIRS ) > 0); }
		bool isEightcut(){		return ( this->isUseEightcut() && (rule & TRUMP_RULE_EIGHTCUT ) > 0); }
		bool isElevenback(){	return ( this->isUseElevenback() && (rule & TRUMP_RULE_ELEVENBACK ) > 0); }
		bool isRestrains(){		return ( this->isUseRestrains() && (rule & TRUMP_RULE_RESTRAINS ) > 0); }
		bool isSpade3(){		return ( this->isUseSpade3() && (rule & TRUMP_RULE_SPADE3 ) > 0); }
		bool isJocker(){		return ( this->isUseJocker() && (rule & TRUMP_RULE_JOCKER ) > 0); }

		void changeRevolution(bool inOn){	if( this->isUseRevolution() )	( inOn ? rule |= TRUMP_RULE_REVOLUTION	: rule ^= TRUMP_RULE_REVOLUTION); }
		void changeSame(bool inOn){			if( this->isUseSame() )			( inOn ? rule |= TRUMP_RULE_SAME		: rule ^= TRUMP_RULE_SAME); }
		void changeStairs(bool inOn){		if( this->isUseStairs() )		( inOn ? rule |= TRUMP_RULE_STAIRS		: rule ^= TRUMP_RULE_STAIRS); }
		void changeEightcut(bool inOn){		if( this->isUseEightcut() )		( inOn ? rule |= TRUMP_RULE_EIGHTCUT	: rule ^= TRUMP_RULE_EIGHTCUT); }
		void changeElevenback(bool inOn){	if( this->isUseElevenback() )	( inOn ? rule |= TRUMP_RULE_ELEVENBACK	: rule ^= TRUMP_RULE_ELEVENBACK); }
		void changeRestrains(bool inOn){	if( this->isUseRestrains() )	( inOn ? rule |= TRUMP_RULE_RESTRAINS	: rule ^= TRUMP_RULE_RESTRAINS); }
		void changeSpade3(bool inOn){		if( this->isUseSpade3() )		( inOn ? rule |= TRUMP_RULE_SPADE3		: rule ^= TRUMP_RULE_SPADE3); }
		void changeJocker(bool inOn){		if( this->isUseJocker() )		( inOn ? rule |= TRUMP_RULE_JOCKER		: rule ^= TRUMP_RULE_JOCKER); }
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void playerCardChange_fadeIn(Gest* p1, Gest* p2, Gest* p3 = NULL, Gest* p4 = NULL);
		void playerCardFadeIn(Gest* p1, int count);

		void playerCardChange_input(Gest* p1, Gest* p2, Gest* p3 = NULL, Gest* p4 = NULL);
		void playerCardChange(Gest* p1, Gest* p2, Gest* p3 = NULL, Gest* p4 = NULL);
		void cardChange(Gest* p1, Gest* p2, int count);

		void judgement_rule();
		void SettingRule(int r1, int r2);
		void WriteData();
		void Input_kirariEffect(NanairoLib::RVector2 vec);

		void Special_cardAutoRevolution();
		void Special_cardDisables(Gest* point);
		void Special_cardDisables_down(Gest* point, int down);
		void Special_cardDisables_up(Gest* point, int up);
		void Special_cardCreateRevolution(Gest* point);
		void Special_cardCreateSame(Gest* point);
		void Special_cardHalf(Gest* point);
		void Special_cardCreatePlus(Gest* point, int plus);
		void Special_cardCreatePlusAll(Gest* point);
		void Special_cardJocker(Gest* point, int down);
		void Special_cardMidiam(Gest* point, int mid);

		void action_specialCard(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void action_specialCard_1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void action_specialCard_2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void action_specialCard_3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void action_specialCard_4th(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);

		void Special_erisu1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_erisu2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_erisu3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		
		void Special_yui1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_yui2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_yui3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		
		void Special_rin1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_rin2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_rin3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);

		void Special_ayano1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_ayano2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_ayano3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);

		void Special_fiona1st(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_fiona2nd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
		void Special_fiona3rd(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);

		void Special_4th(Gest* p1st, Gest* p2nd, Gest* p3rd, Gest* p4th);
	};

	class GameScene : public MYGAME::Scene
	{
	protected:
		bool					waitFlag;
		MYGAME::BackGround_2D	back;
		JudgementCard			judgements;

	public:
		JudgementCard*	GetJudge(){	return &this->judgements;	}

		bool throwPlayerCard_inJudgmentCard(std::vector<TrumpCard>& plcards);
		bool throwPlayerCard_inJudgmentCard_sameSum(std::vector<TrumpCard>& plcards);
		bool throwPlayerCard_inJudgmentCard_check(std::vector<TrumpCard>& judCard, std::vector<int>& sej );
		bool throwPlayerCard_inJudgmentCard_checkOut(std::vector<TrumpCard>& judCard, int count, int jockerCnt, int temp, bool hantei, bool kakutei, bool same_or_stairs);

		void throwJudgement(std::vector<TrumpCard>& plcards);
		void throwJudgement_byno(std::vector<TrumpCard>& plcards, int selectNumber = -1, int selectCount = 0, int jockerCnt = 0, bool same_or_stairs = false);
		void throwJudgement_bysame(std::vector<TrumpCard>& plcards, int selectNumber = -1, int selectCount = 0, int jockerCnt = 0, bool same_or_stairs = false);
		void throwJudgement_bystairs(std::vector<TrumpCard>& plcards, int selectNumber = -1, int selectCount = 0, int jockerCnt = 0, bool same_or_stairs = false);

		void throwJudgement_byno_selectSame(std::vector<TrumpCard>& plcards, int selectNumber = -1, int selectCount = 0, int jockerCnt = 0, bool same_or_stairs = false);
		void throwJudgement_byno_selectStairs(std::vector<TrumpCard>& plcards, int selectNumber = -1, int selectCount = 0, int jockerCnt = 0, bool same_or_stairs = false);
		void throwJudgement_byno_selecting(std::vector<TrumpCard>& plcards, int selectNumber = -1, int selectCount = 0, int jockerCnt = 0, bool same_or_stairs = false);

		bool check_resTrains(CARD_TYPE type, std::vector<int>& typeList);
		void changeJocker_resTrains(std::vector<TrumpCard>& judCard, int jockerCnt);

		//同じものを出す時のチェック関数
		bool judgement_same(std::vector<TrumpCard>& judCard,int temp, int i, int jockerCnt );

		bool judgement_bysame_twoJocker(std::vector<TrumpCard>& judCard,int count, int jockerCnt);
		bool judgement_byno_onfront(std::vector<TrumpCard>& judCard,int count, int jockerCnt);
		bool judgement_bystairs_onecard(std::vector<TrumpCard>& judCard,int count, int jockerCnt);

		//--------------------------------------------------------------------------------------------------------------------------------------
	};

	#define GAMEWAIT_DIALOGSUM	2
	class PE_the_matchScene : public GameScene
	{
	private:
		int									selectNumber;
		MYGAME::NameDialog					*passDialog, *selecterDialog;
		MYGAME::NoticeDialog				*clickDialog, *passclickDialog;
		Player								player;
		Gest*								enemy;
		std::list<MYGAME::FadeNameDialog*>	dialogList;

	private:
		void Input_clickDialog();
		void Input_passClickDialog();
		void Input_judgements();
		void Input_passDialog();
		void Input_selecterDialog();

		void (PE_the_matchScene::*_action)();
		void action_judgement();
		void action_player();
		void action_enemy(int number);
		bool action_judgement_trump(Gest* gest);
		void action_pass(int number);
		void action_wait();
		void action_winnerJump();
		void action_continue();
		void action_score();
		void action_reSet();
		void action_winner(int number);
		void action_roundStart();
		void action_gobackToTittle();
		void action_notting(){}
		void action_specialTime();

		void Set_gamewaitFadeIn();
		void Set_gamewaitFadeOut();
		void action_gamewaitFadeIn();
		void action_gamewaitFadeOut();
		void action_gameWait();
		bool action_gameWait_mouseCheck();

		void Set_gameFinish();
		void check_clickDialog();
		void Set_playerFace(int playNum, int faceNum);

	protected:
		void Draw3D(){}
		void Draw2D();
	
	public:
		PE_the_matchScene();
		~PE_the_matchScene();

		void Init();
		void Recircle(){}
		void Draw();
		void Atack(){}

		//使用しているのはこの３つ！
		void Step();
		void Dispose(){}
		void Del(){}

	public:
		void player_Setting(bool IsContinue);
		void card_Setting(int sum);
		void card_change(int sum);
		void card_change_fadeIn(int sum);

		void inputData(RoomData* _data, bool IsContinue);

	};

}

#endif