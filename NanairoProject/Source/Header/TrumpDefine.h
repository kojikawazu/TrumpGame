#ifndef _NANAIRO_TRUMPDEFINE_H
#define _NANAIRO_TRUMPDEFINE_H

namespace NanairoProject
{
	#define playerMapPartsSum	4 
	#define playerNameSum		6

	//-------------------------------------------------------------------------------------
	//表示で扱う文字列配列
	//-------------------------------------------------------------------------------------
	static LPCTSTR RuleGraphNames[] = 
	{
		"eightcut", "elevenback", "restrains", "revolution", "jockerEFF",
		"spade3", "stairs", "capitalDown", "foul", "cardChange"
	};

	static LPCTSTR RulePlateGraphNames[] = 
	{
		"plateEightcut", "plateElevenback", "plateRestrains", "plateRevolution", "plateJockerEFF",
		"plateSpade3", "plateStairs", "plateCapitaldown", "plateFoul", "plateCardchange"
	};

	#define PLAYERNAME_MAX 5
	static LPCTSTR NameTagString[PLAYERNAME_MAX] = 
	{
		"platePlayer1", "platePlayer2", "platePlayer3", "platePlayer4", "platePlayer5"
	};

	static LPCTSTR NameSpecialCardString[PLAYERNAME_MAX] = 
	{
		"erisuCard", "yuiCard", "rinCard", "ayanoCard", "fionaCard"
	};

	static LPCTSTR DaifugouString[PLAYERNAME_MAX] = 
	{
		"BigMillionaire", "SmallMillionaire", "SmallPoor", "BigPoor", ""
	};

	#define POWER_ENUM_SUM 3
	static LPCTSTR POWER_ENUM[POWER_ENUM_SUM] = 
	{
		"Easy", "Normal", "Strong"
	};

	static LPCTSTR PLAYERNAME_ENUM[PLAYERNAME_MAX] = 
	{
		"erisu", "yui", "rin", "ayano", "fiona"
	};

	static LPCTSTR PLAYERNAME_ENUM2[PLAYERNAME_MAX] = 
	{
		"erisu2", "yui2", "rin2", "ayano2", "fiona2"
	};

	//////////////////////////////////////////////////////////
	//カードタイプ
	//////////////////////////////////////////////////////////
	enum CARD_TYPE
	{
		CARD_HEART = 0, CARD_CLOVER, CARD_DIAMOND, CARD_SPADE, CARD_JOCKER, 
		CARD_SPECIAL
	};

	//////////////////////////////////////////////////////////
	//カードステータス
	//////////////////////////////////////////////////////////
	enum CARD_STATUS
	{
		CARD_STATUS_BACK = 0, CARD_STATUS_FRONT, CARD_STATUS_DES,
	};

	/////////////////////////////////////////////////////////
	//トランプの力
	/////////////////////////////////////////////////////////
	const int TRUMP_POWER[13] = 
	{
		12, 13, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 
	};

	/////////////////////////////////////////////////////////
	//カードタッチステータス
	/////////////////////////////////////////////////////////
	enum CARD_TOUCHSTATUS_TOUCH_STATUS
	{
		CARD_TOUCHSTATUS_NO_TOUCH, CARD_TOUCHSTATUS_TOUCH, CARD_TOUCHSTATUS_CLICK,
	};

	/////////////////////////////////////////////////////////
	//反則リスト
	/////////////////////////////////////////////////////////
	enum CARD_FOUL
	{
		FOUL_NONE, FOUL_CAPITALDOWN, FOUL_FOULUP, 
	};

	enum CHARA_TYPE
	{
		CHARA_ERISU, CHARA_YUI, CHARA_RIN, CHARA_AYANO, CHARA_FIONA,
	};

	enum LoadingNumber
	{
		ONCE_LOAD, CONTINUE_LOAD, NO_ROAD,
	};

	///////////////////////////////////////////////////////////////////////////////////////
	//ルールの状態
	///////////////////////////////////////////////////////////////////////////////////////
	//0:何もなし
	//1:8切り
	//2:縛り
	//3:革命
	//4:11バック
	//5:同じ
	//6:階段
	///////////////////////////////////////////////////////////////////////////////////////
	#define TRUMP_RULE_NOSTATUS		0x00000000
	#define TRUMP_RULE_EIGHTCUT		0x00000001
	#define TRUMP_RULE_RESTRAINS	0x00000010
	#define TRUMP_RULE_REVOLUTION	0x00000100
	#define TRUMP_RULE_ELEVENBACK	0x00001000
	#define TRUMP_RULE_SAME			0x00010000
	#define TRUMP_RULE_STAIRS		0x00100000
	#define TRUMP_RULE_SPADE3		0x01000000
	#define TRUMP_RULE_JOCKER		0x10000000

	#define TRUMP_RULE_CAPITALDOWN	0x00000001
	#define TRUMP_RULE_FOUL			0x00000010
	#define TRUMP_RULE_CARDCHANGE	0x00000100

	#define TRUMP_RULE_ALL			0x11111111
	#define TRUMP_RULE_STANDARD		0x11111111

	#define TRUMP_RULE_BACKFRONT	0x00111000
	#define TRUMP_RULE_CHECKBACK	0x00001100


	///////////////////////////////////////////////////////////
	//カードの中で色んな最大数を設定
	///////////////////////////////////////////////////////////
	#define CARD_ONETYPE_MAX	13
	#define CARD_TYPE_MAX		 4
	#define CARD_MAX_NOJOCKER	52
	#define CARD_MAX_PLUSJOCKER	54
	#define CARD_MAX_FILTER		 13
	#define PLAYER_MAX			 4

	///////////////////////////////////////////////////////////
	//オフセット群
	///////////////////////////////////////////////////////////
	#define OFFSET_CARD_ATACKCHECK	0.2
	#define OFFSET_PLUS_Y			30
	#define OFFSET_SPD				5
	#define OFFSET_CENTER_MOVESPD	5

	//////////////////////////////////////////
	//セレクトの仕方
	//////////////////////////////////////////
	enum SELECT_STATUS_TYPE
	{
		SELECT_STATUS_NO = 0, SELECT_STATUS_SAME = 0, SELECT_STATUS_KAIDAN, 
	};

	//////////////////////////////////////////
	//敵の強さ
	//////////////////////////////////////////
	enum ENEMY_POWER
	{
		ENEMY_POWER_EASY, ENEMY_POWER_NORMAL, ENEMY_POWER_STRONG, 
	};

	//////////////////////////////////////////
	//順位によるスコアの割合
	//////////////////////////////////////////
	#define SCORE_VALUE				  1000
	#define SCORE_BIG_MILLIONAIRE		10
	#define SCORE_SMALL_MILLIONAIRE		 7
	#define SCORE_SMALL_POOR			 4
	#define SCORE_BIG_POOR				 2
	#define SCORE_CAPITALDOWN			0.8
	#define SCORE_FOEL					0.5

	//////////////////////////////////////////
	//スコアデータ
	//////////////////////////////////////////
	#define OFFSET_SCALE_PLUS_SPDX 21.0f
	#define OFFSET_SCALE_PLUS_SPDY 14.0f
	#define OFFSET_SCALE_MANU_SPDX 15.0f
	#define OFFSET_SCALE_MANU_SPDY 10.0f

	#define CHECK_TRUMP_BIGGER(x,y)		( TRUMP_POWER[x] != TRUMP_POWER[y] && TRUMP_POWER[x] > TRUMP_POWER[y])
	#define CHECK_TRUMP_SMALLER(x,y)	( TRUMP_POWER[x] != TRUMP_POWER[y] && TRUMP_POWER[x] < TRUMP_POWER[y])
	#define CHECK_TRUMP_ABS(x, y)		abs(TRUMP_POWER[x] - TRUMP_POWER[y])

	static bool isDataRule(int rule, int i)
	{
		bool hantei = false;
		switch( i )
		{
			case 0:		if( (rule & TRUMP_RULE_EIGHTCUT) > 0 )		hantei = true;	break;
			case 1:		if( (rule & TRUMP_RULE_ELEVENBACK) > 0 )	hantei = true;	break;
			case 2:		if( (rule & TRUMP_RULE_RESTRAINS) > 0 )		hantei = true;	break;
			case 3:		if( (rule & TRUMP_RULE_REVOLUTION) > 0 )	hantei = true;	break;
			case 4:		if( (rule & TRUMP_RULE_JOCKER) > 0 )		hantei = true;	break;
			case 5:		if( (rule & TRUMP_RULE_SPADE3) > 0 )		hantei = true;	break;
			case 6:		if( (rule & TRUMP_RULE_STAIRS) > 0 )		hantei = true;	break;
						
			case 7:		if( (rule & TRUMP_RULE_CAPITALDOWN) > 0 )	hantei = true;	break;
			case 8:		if( (rule & TRUMP_RULE_FOUL) > 0 )			hantei = true;	break;
			case 9:		if( (rule & TRUMP_RULE_CARDCHANGE) > 0 )	hantei = true;	break;
		}
		return hantei;
	}

}


#endif