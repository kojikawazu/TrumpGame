#pragma once

#include <MainFunction.h>
#include <MusicSound.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>
#include <Rule_effect.h>
#include <ChangeScene.h>
#include <TemplateEffectList.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	PE_the_matchScene::PE_the_matchScene()
	{
		this->Init();
	}
	
	PE_the_matchScene::~PE_the_matchScene()
	{
		ES_SAFE_DELETE( this->clickDialog );
		ES_SAFE_DELETE( this->passclickDialog );
		ES_SAFE_DELETE( this->passDialog );
		ES_SAFE_DELETE( this->selecterDialog );
		ES_SAFE_DELETE_ARRAY( this->enemy );
		this->judgements.effectList.ListClear();
		this->judgements.Dispose();
		this->player.trumps.clear();

		BGMFactory* bgm = MusicFactory::GetInstance()->GetBGM();
		bgm->Stop("cafe");

		std::list<MYGAME::FadeNameDialog*>::iterator it = this->dialogList.begin();
		while(it != this->dialogList.end())
		{
			ES_SAFE_DELETE( (*it) );
			it = this->dialogList.erase(it);
		}
	}

	void PE_the_matchScene::Init()
	{
		this->judgements.SetGame( this );
		//--------------------------
		//back
		//--------------------------
		this->back.SetBackName("back");

		this->Input_clickDialog();
		this->Input_passClickDialog();
		this->Input_judgements();
		this->Input_passDialog();
		this->Input_selecterDialog();

		//--------------------------------------------------
		//ゲームスタート
		//--------------------------------------------------
		this->_action = &PE_the_matchScene::action_roundStart;
		BGMFactory* bgm = MusicFactory::GetInstance()->GetBGM();
		bgm->Play("cafe");
	}

	void PE_the_matchScene::Input_clickDialog()
	{
		//--------------------------
		//click
		//--------------------------
		this->clickDialog = new NoticeDialog();
		this->clickDialog->SetObject(Vector2(SCRW_PERCENT(0.2f), SCRH_PERCENT(0.7f)), 0.0f, Vector2(0,0));
		this->clickDialog->SetNameColor(GetMaxColor());
		this->clickDialog->SetDialogName("clickMap");
		this->clickDialog->SetName("lclickMap");
	}
	
	void PE_the_matchScene::Input_passClickDialog()
	{
		//--------------------------
		//passClick
		//--------------------------
		this->passclickDialog = new NoticeDialog();
		this->passclickDialog->SetObject(Vector2(SCRW_PERCENT(0.9f), SCRH_PERCENT(0.55f)), 0.0f, Vector2(0,0));
		this->passclickDialog->SetNameColor(GetMaxColor());
		this->passclickDialog->SetDialogName("clickMapR");
		this->passclickDialog->SetName("mclickMap");
	}

	void PE_the_matchScene::Input_judgements()
	{
		//--------------------------
		//Judgement
		//--------------------------
		this->judgements.Init();
		this->judgements.SetPlaySum(4);
		this->judgements.scoreMap.SetPlaySum(4);
	}

	void PE_the_matchScene::Input_passDialog()
	{
		//----------------------------------------------
		//クリックの通知ダイアログ
		//----------------------------------------------
		this->passDialog = new NameDialog();
		this->passDialog->SetName("passing");
		this->passDialog->SetDialogName("selectPlate1");
		this->passDialog->SetObject(Vector2(SCRW_PERCENT(0.7f), SCRH_PERCENT(0.7f) ), 0.0f, Vector2(100.0f, 50.0f) );
	}

	void PE_the_matchScene::Input_selecterDialog()
	{
		//----------------------------------------------
		//クリックの通知ダイアログ
		//----------------------------------------------
		this->selecterDialog = new NameDialog();
		this->selecterDialog->SetName("");
		this->selecterDialog->SetDialogName("selectBlock");
		this->selecterDialog->SetObject(Vector2(SCRW_PERCENT(0.5f), SCRH_PERCENT(0.7f) ), 0.0f, Vector2(100.0f, 50.0f) );
	}

	void PE_the_matchScene::player_Setting(bool IsContinue)
	{
		int sum = this->judgements.GetPlaySum();
		enemy = new Enemy[sum-1];
		
		for( int i=0,count=0; i<sum; i++)
		{
			while( count < 4 && !this->judgements.roomData.charaData[count].selectFlag )
				count++;
			if( count < 4 )
			{
				( count == 0 ? 
					this->player.GetSpecialCard()->SetCharaNumber(this->judgements.roomData.charaData[count].charaNum) :
					this->enemy[i-1].GetSpecialCard()->SetCharaNumber(this->judgements.roomData.charaData[count].charaNum) );
			}


			( count < 4 ? 
				this->judgements.playerPlateList.Pusher( i, this->judgements.roomData.charaData[count++].charaNum ) :
				this->judgements.playerPlateList.Pusher( i, i ) );
			
				this->judgements.playerPlateList.Push( i, i+1-( IsContinue ? 1 : 0) );
		}

		this->card_Setting( sum );
		
		if( IsContinue )	this->judgements.playerPlateList.SetContinue();
	}

	void PE_the_matchScene::card_Setting(int sum)
	{
		if( sum < 2 )	return ;

		//-----------------------------------------------------------
		//カード
		//-----------------------------------------------------------
		TrumpCard* cd;
		this->player.ChangeCardMax(sum);
		this->player.SetSpecialCardPos(0);
		cd = this->player.GetSpecialCard();
		cd->ChangeDraw( CARD_STATUS_FRONT );
		cd->SetTouchActionS();
		cd->SettingOffCardTouch();

		for( int i=0; i<sum-1; i++)
		{
			enemy[i].ChangeCardMax(sum);
			enemy[i].SetPlayNumber( i+1 );
			enemy[i].SetSpecialCardPos( i+1 );
			cd = this->enemy[i].GetSpecialCard();
			cd->ChangeDraw( CARD_STATUS_FRONT );
			cd->SettingOffCardTouch();
		}

		int siz = (int)(CARD_MAX_PLUSJOCKER / sum);
		if( CARD_MAX_FILTER != 0 && siz > CARD_MAX_FILTER )
			siz = CARD_MAX_FILTER;
		std::vector<int> cardList;
		for(int k=0; k<sum; k++)
		{
			for(int i=0, rnd=0, count=0, okf = 1; i<siz; i++, okf = 1)
			{
				rnd = rand() % CARD_MAX_PLUSJOCKER;
				if( !this->judgements.isUseJocker() &&
					rnd >= 52)
					continue;

				for(int j=0, cdSize = cardList.size(); j<cdSize; j++)
				{
					if( cardList[j] == rnd )
						okf = 0;
				}

				if( okf == 1)
				{
					if( k == 0 )	this->player.SetCardNumber(count, rnd);
					else			this->enemy[k-1].SetCardNumber(count, rnd);
					cardList.push_back( rnd );
				}
				else
				{
					i--;
					continue;
				}

				if( k == 0 )	this->player.SetCardPos( k, count );
				else
				{
					this->enemy[k-1].SetCardPos( k, count );
					this->enemy[k-1].trumps[i].SetActionCard(false);
				}
				count++;
			}
		}

		//---------------------------------------------------------------------------
		//一旦ソート
		this->player.cardSort();
		for( int i=0; i<sum-1; i++)
			enemy[i].cardSort();
		//---------------------------------------------------------------------------
	}

	//----------------------------------------------------------------
	//カード交換
	//----------------------------------------------------------------
	void PE_the_matchScene::card_change(int sum)
	{	
		if( this->judgements.GetGameCount() > 0 )
		{
			this->judgements.playerCardChange_input( &this->player, &this->enemy[0], 
				(this->judgements.GetPlaySum() > 2 ? &enemy[1] : NULL ),
				(this->judgements.GetPlaySum() > 3 ? &enemy[2] : NULL ) );
		
			this->player.cardSort();
			this->player.cardAllFadeIn();
			this->player.cardStatusChange( CARD_STATUS_FRONT );
			for( int i=0; i<sum-1; i++)
			{
				this->enemy[i].cardSort();
				this->enemy[i].cardAllFadeIn();
				this->enemy[i].cardStatusChange( CARD_STATUS_BACK );
			}
		}
	}

	void PE_the_matchScene::card_change_fadeIn(int sum)
	{
		this->judgements.playerCardChange_fadeIn( &this->player, &this->enemy[0], 
			(this->judgements.GetPlaySum() > 2 ? &enemy[1] : NULL ),
			(this->judgements.GetPlaySum() > 3 ? &enemy[2] : NULL ) );

		this->judgements.push_cardChangeEffect();
	}

	//----------------------------------------------------------------
	//アクション
	//----------------------------------------------------------------
	void PE_the_matchScene::Step()
	{
		(this->*_action)();
		//-----------------------------------------
		//ジャッジメントアクション
		//-----------------------------------------
		this->judgements.Step();	

		//-----------------------------------------
		//クリック通知ダイアログのアクション
		//-----------------------------------------
		this->clickDialog->Step();
		this->passclickDialog->Step();

		if( __KEYDATA->trg[KQ] )
			this->judgements.push_specialEffect(CHARA_ERISU);
		
		//-----------------------------------------
		//リストのアクション
		//-----------------------------------------
		this->judgements.effectStep();
	}

	//----------------------------------------------------------------
	//プレイヤーのアクション中
	//----------------------------------------------------------------
	void PE_the_matchScene::action_judgement()
	{
		if( __KEYDATA->trg[ KS ] ||
			(__MOUSEDATA->trg[LBUTTON] && 
			this->selecterDialog->IsAtack_boundingbox_centerBox(
				&Vector2( (float)__MOUSEDATA->mouseX, (float)__MOUSEDATA->mouseY ) ) ) )
		{
			this->Set_gamewaitFadeIn();
			return ;
		}

		//リセット行われてないとき
		if( !this->judgements.checkPassCount() )
		{
			//-----------------------------------------
			//プレイヤー番号によりアクションの制御
			//-----------------------------------------
			int number = this->judgements.GetNowPlayNum();
			switch( number )
			{
			case 0:	//プレイヤー
				this->action_player();
				break;
			default:	//敵
				this->action_enemy( number );
			}
		}
	}

	void PE_the_matchScene::action_player()
	{
		MOUSE* mouse = __MOUSEDATA;

		//--------------------------------------
		//抜けているプレイヤーは飛ばしましょう
		//--------------------------------------
		if( this->player.GetWinnerNumber() > 0 )
		{
			this->action_winnerJump();
			this->passclickDialog->SetDialogName("");
			this->passclickDialog->SetName("");
			this->clickDialog->SetDialogName("");
			this->clickDialog->SetName("");
			return ;
		}	

		this->player.Step();
		//------------------------------------
		//パスしてたら
		//------------------------------------
		if( this->player.isPass() ||
			(mouse->trg[LBUTTON] && 
			this->passDialog->IsAtack_boundingbox_centerBox( 
				&Vector2( (float)mouse->mouseX, (float)mouse->oldMouseY) ) ) )
		{
			this->Set_playerFace( 0, FACE_HURRY );
			this->player.SetPassing( false );
			if( !this->judgements.frontCard.empty() )
				this->action_pass( 0 );
			return ;
		}
				
		//--------------------------------------------
		//クリック処理したかチェック
		//--------------------------------------------
		this->check_clickDialog();

		//--------------------------------------------
		//パスしてないならチェック
		//--------------------------------------------
		( this->action_judgement_trump( &this->player ) ?
			this->Set_playerFace( 0, FACE_SMILE ) : this->Set_playerFace( 0, FACE_AMAZE ) );

		//--------------------------------------------
		//反則等してたら
		//--------------------------------------------
		if( this->judgements.foulFlag )
		{
			this->player.onFoul();
			this->judgements.foulFlag = false;
			this->Set_playerFace( 0, FACE_DAMAGE );
		}

		//スペシャルカード発動
		if( this->player.GetSpecialCard()->GetCardStatus() != CARD_STATUS_DES &&
			this->player.GetSpecialCard()->GetMouseTouch() == CARD_TOUCHSTATUS_CLICK &&
			__MOUSEDATA->trg[RBUTTON] )
		{
			this->judgements.passCnt = 0;
			this->judgements.specialCharaNum = this->judgements.playerPlateList.GetPlayerPlate(0)->GetSelectNumber();
			this->judgements.specialRunkNum = ( !this->judgements.GetGameCount() ? 3 : 
				(*this->judgements.scoreMap.GetOldRunk())[0] );
			
			this->player.GetSpecialCard()->SetCenterMove(0,1);
			this->judgements.push_specialEffect( this->judgements.specialCharaNum );
			this->_action = &PE_the_matchScene::action_specialTime;
		}

		//--------------------------------------------
		//カードがなくなったら抜ける
		//--------------------------------------------
		if( !this->player.GetNowCardMax() )
		{
			this->action_winner( 0 );
			this->Set_playerFace( 0, FACE_LAUGH );
		}
	}

	void PE_the_matchScene::action_enemy(int number)
	{
		//--------------------------------------
		//抜けているプレイヤーは飛ばしましょう
		//--------------------------------------
		if( this->enemy[number-1].GetWinnerNumber() > 0 )
		{
			this->action_winnerJump();
			return ;
		}
				
		//---------------------------------------------------------
		//ＡＩ発動
		//---------------------------------------------------------
		this->throwJudgement( this->enemy[number-1].trumps );
		this->enemy[number-1].Step();
		((Enemy&)this->enemy[number-1]).AIStep( this->judgements );

		//------------------------------------
		//パスしてないならジャッジ
		//------------------------------------
		if( this->action_judgement_trump( &this->enemy[number-1] ) )
		{
			this->Set_playerFace( number, FACE_SMILE );
		}
		else
		{
			this->enemy[ number - 1].SetPassing( true );
			this->Set_playerFace( number, FACE_AMAZE );
		}
			

		//------------------------------------
		//パスしてたら
		//------------------------------------
		if( this->enemy[number-1].isPass() )
		{
			this->action_pass( number );
			this->Set_playerFace( number, FACE_HURRY );
			return ;
		}

		if( this->judgements.foulFlag )
		{
			this->enemy[number-1].onFoul();
			this->judgements.foulFlag = false;
			this->Set_playerFace( number, FACE_DAMAGE );
		}
		//------------------------------------
		//カードがなくなれば抜ける
		//------------------------------------
		if( !this->enemy[number-1].GetNowCardMax() )
		{
			this->Set_playerFace( number, FACE_LAUGH );
			this->action_winner( number );
		}
	}

	//----------------------------------------------------------------
	//カードのジャッジタイム
	//----------------------------------------------------------------
	bool PE_the_matchScene::action_judgement_trump(Gest* gest)
	{
		//-------------------------------------------------------------------
		//バトルしてたら
		//-------------------------------------------------------------------
		if( gest->isBattleMethod() )
		{
			if( !this->throwPlayerCard_inJudgmentCard( gest->trumps ) )
			{
				gest->change_offBattle();
				
				if( gest->GetPlayNumber() != 0 )
					gest->SetPassing( true );
				for(int i=0, siz = gest->trumps.size(); i<siz; i++)
				{
					if( !gest->trumps[i].isCardDes() )
						gest->trumps[i].SettingOffCardTouch();
				}
				return false;
			}

			gest->cardSort();
			if( !this->judgements.isEightcut() )
				this->judgements.playNumberPlus(1);

			this->judgements.judgement_rule();
			gest->change_offBattle();
			this->_action = &PE_the_matchScene::action_wait;
			this->judgements.passCnt = 0;

			SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
			se->Play("urucard");
			return true;
		}
		else
		//-------------------------------------------------------------------
		//ジャッジチェック
			this->throwJudgement( gest->trumps );
		//-------------------------------------------------------------------
		return false;
	}

	void PE_the_matchScene::action_specialTime()
	{
		((Player&)this->player).TrumpStep();

		if( this->frameCnt >= 120 )
		{
			this->judgements.playNumberPlus(1);
			this->_action = &PE_the_matchScene::action_wait;
			this->frameCnt = 60;
		}
		else if( this->frameCnt++ == 60 )
		{
			this->judgements.action_specialCard( &this->player, 
				(this->judgements.GetPlaySum() > 1 ? &this->enemy[0] : NULL ),
				(this->judgements.GetPlaySum() > 2 ? &this->enemy[1] : NULL ),
				(this->judgements.GetPlaySum() > 3 ? &this->enemy[2] : NULL ) );
			( !this->judgements.GetNowPlayNum() ? 
				((Player&)this->player).GetSpecialCard()->ChangeDraw( CARD_STATUS_DES ) :
			((Enemy&)this->enemy[this->judgements.GetNowPlayNum()-1]).GetSpecialCard()->ChangeDraw( CARD_STATUS_DES ) );
		}
	}

	//----------------------------------------------------------------
	//パスアクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_pass(int number)
	{
		this->judgements.passCnt++;	
		this->judgements.playNumberPlus(1);
		this->judgements.pushPassEffect( number );
		this->_action = &PE_the_matchScene::action_wait;

		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play("piron");
	}

	//----------------------------------------------------------------
	//待機アクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_wait()
	{
		((Player&)this->player).TrumpStep();

		int number = this->judgements.GetNowPlayNum();
		if( this->frameCnt++ >= 60 )
		{
			this->_action = &PE_the_matchScene::action_judgement;
			this->frameCnt = 0;

			if( number != 0)
			{
				this->enemy[number-1].SetPassing( false );
				this->enemy[number-1].change_offBattle();
			}
		}
	}

	//----------------------------------------------------------------
	//勝ち上がりジャンプアクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_winnerJump()
	{
		this->judgements.playNumberPlus(1);
		int number = this->judgements.GetNowPlayNum();
		if( number != 0)
		{
			this->enemy[number-1].SetPassing( false );
			this->enemy[number-1].change_offBattle();
		}
	}

	//----------------------------------------------------------------
	//スコア表示アクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_score()
	{
		if( this->frameCnt++ >= 60 )
		{
			this->judgements.scoreMap.inScoreMap();
			std::vector<int> vec = this->judgements.playerPlateList.GetFoulSum();
			this->judgements.runkList_ofRewrite();
			this->judgements.scoreMap.judgeRunk( this->judgements.winnerList, vec[0], vec[1] );
			this->_action = &PE_the_matchScene::action_continue;
			this->frameCnt = 0;

			this->judgements.effectList.Add( new TemplateEffectList<ConfettiEffect>() );

			SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
			se->Play("score");
		}
	}

	//----------------------------------------------------------------
	//続きする？アクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_continue()
	{
		if( __KEYDATA->trg[ KZ ] || __MOUSEDATA->trg[LBUTTON] )
		{
			this->_action = &PE_the_matchScene::action_reSet;
			this->judgements.scoreMap.outScoreMap();

			SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
			se->Play("scoreout");
			se->Stop("score");
		}
		else if( __KEYDATA->trg[ KS ] ||
			__MOUSEDATA->trg[RBUTTON] )
		{
			this->Set_gamewaitFadeIn();
			return ;
		}
	}

	//----------------------------------------------------------------
	//リセットアクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_reSet()
	{
		this->back.SetBackName("back");
		int sum = this->judgements.GetPlaySum();
		//--------------------------
		//Judgement
		//--------------------------
		this->judgements.gameContinue();
		this->player.playerContinue();
		for(int i=0; i<sum-1;i++)
			this->enemy[i].playerContinue();
		this->card_Setting(sum);

		this->clickDialog->SetDialogName("clickMap");
		this->clickDialog->SetName("lclickMap");
		this->passclickDialog->SetDialogName("clickMapR");
		this->passclickDialog->SetName("mclickMap");

		this->_action = &PE_the_matchScene::action_roundStart;
	}

	//----------------------------------------------------------------
	//勝ったときのアクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_winner(int number)
	{
		//抜けたら
		int siz = this->judgements.runkList.GetSize(), not;
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();

		if( siz == 0 )
			se->Play("winner");

		//------------------------------------------------------------------------------
		//都落ち
		//------------------------------------------------------------------------------
		if( this->judgements.isUseCapitaldown() && siz == 0 )
		{
			not = this->judgements.playerPlateList.GetPlayNumber_runk1();
			if( not != 0 && not != number+1 )
			{
				( not-1 == 0 ? this->player.onFoul() : this->enemy[not-2].onFoul() );
				this->judgements.push_winner( 
					( not-1 == 0 ? &this->player : &this->enemy[not-2] ), not-1 );
				this->judgements.playerPlateList.onFoul( not - 1, FOUL_CAPITALDOWN );
				this->judgements.push_foulEffect( not-1, FOUL_CAPITALDOWN );
				( not == 1 ? this->player.allDelCard() : this->enemy[not-2].allDelCard() );
				
				se->Play("bite");
			}		
		}

		this->judgements.push_winner( 
			( number == 0 ? &this->player : &this->enemy[number-1] ), number );
		if( !(number == 0 ? this->player.isFoul() : this->enemy[number-1].isFoul()) )
			this->judgements.push_starEffect( number );
		else
		{
			this->judgements.push_foulEffect( number, FOUL_FOULUP );
			this->judgements.playerPlateList.onFoul( number, FOUL_FOULUP );
			se->Play("roll");
		}

		if( (this->judgements.GetPlaySum() - this->judgements.winSum - this->judgements.foulSum) == 1 )
		{
			not = this->judgements.runkList.GetNottingNumber();
			this->judgements.push_winner( 
			( not == 0 ? &this->player : &this->enemy[not-1] ), not );
			this->_action = &PE_the_matchScene::action_score;
		}
	}

	//----------------------------------------------------------------
	//ラウンド開始のアクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_roundStart()
	{
		if( this->judgements.GetGameCount() > 2)
		{
			this->Set_gameFinish();
			return ;
		}

		bool isCountOnce = (this->judgements.isUseCardChange() && this->judgements.GetGameCount() > 0);
		this->frameCnt++;

		this->player.cardOnlyStep();
		for(int i=0, siz=this->judgements.GetPlaySum()-1; i<siz; i++)
			this->enemy[i].cardOnlyStep();

		//---------------------------------------------------------------------------
		//カード交換しますよ～
		if( isCountOnce )
		{
			if( this->frameCnt == 20 )
			{
				this->card_change_fadeIn( this->judgements.GetPlaySum() );
				SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
				se->Play("shine");
			}
			else if( this->frameCnt == 80 )	this->card_change( this->judgements.GetPlaySum() );
		}

		//---------------------------------------------------------------------------
		//ラウンドエフェクト出しますよ～
		if( this->frameCnt == ( isCountOnce ? 170 : 8 ) )
			this->judgements.pushRoundStart( this->judgements.GetGameCount() + 1 );
		//---------------------------------------------------------------------------
		//さぁゲームスタートです。
		else if( this->frameCnt >= ( isCountOnce ? 300 : 120 ) )
		{
			this->player.SetTouchActions();
			this->frameCnt = 0;
			this->judgements.gameStartFlag = true;
			this->_action = &PE_the_matchScene::action_judgement;
		}
		//---------------------------------------------------------------------------
	}

	//----------------------------------------------------------------
	//タイトルへ戻りますアクション
	//----------------------------------------------------------------
	void PE_the_matchScene::action_gobackToTittle()
	{
		if( ++this->frameCnt >= 30 )
		{
			this->frameCnt = 0;
			this->_action = &PE_the_matchScene::action_notting;
			Scene* sc = NanairoProject::SettingChangeScene(
				CHANGE_FADE, SCENE_TITLE,  this );
			( sc != NULL ? this->GetManager()->Add( sc ) : this->GetManager()->Dispose( this ) );
			this->judgements.WriteData();
		}
	}

	//----------------------------------------------------------------
	//ゲームオプションを開く
	//----------------------------------------------------------------
	void PE_the_matchScene::action_gamewaitFadeIn()
	{
		bool hantei = true;
		for(std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			it != this->dialogList.end(); it++)
		{
			(*it)->Step();	
			if( (*it)->IsWait() )	hantei = false;
		}

		if( hantei )
			this->_action = &PE_the_matchScene::action_gameWait;
	}
	
	void PE_the_matchScene::action_gamewaitFadeOut()
	{
		bool hantei = true;
		for(std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			it != this->dialogList.end(); it++)
		{
			(*it)->Step();	
			if( (*it)->IsWait() )	hantei = false;
		}

		if( hantei )
		{
			std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			while( it != this->dialogList.end() )
			{
				ES_SAFE_DELETE( (*it) );
				it = this->dialogList.erase( it );
			}
	
			this->_action = ( this->judgements.gamewaitFlag ? 
				&PE_the_matchScene::action_gobackToTittle : &PE_the_matchScene::action_judgement );
		}
	}
	
	void PE_the_matchScene::action_gameWait()
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		int count = 0;
		bool hantei = false;

		if( MFunc->GetKey()->GetKey()->trg[ KDOWN ] )
		{
			this->selectNumber = INCREMENT_SPECIAL( this->selectNumber, GAMEWAIT_DIALOGSUM );
			hantei = true;
			//this->updownMusix();
		}
		else if( MFunc->GetKey()->GetKey()->trg[ KUP ] )
		{
			this->selectNumber = DECREMENT_SPECIAL( this->selectNumber, GAMEWAIT_DIALOGSUM );
			hantei = true;
			//this->updownMusix();
		}
		else if( MFunc->GetKey()->GetKey()->trg[ KZ ] ||
			(__MOUSEDATA->trg[LBUTTON] && this->action_gameWait_mouseCheck() ) )
		{
			this->judgements.gamewaitFlag = ( this->selectNumber == 2 );
			this->Set_gamewaitFadeOut();
			//this->okMusic();
		}

		for(std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			count<GAMEWAIT_DIALOGSUM; it++, count++)
		{
			if( count == 0 )	it++;

			( count == this->selectNumber ? 
				((SlidesideDialog*)(*it))->onSelect() : ((SlidesideDialog*)(*it))->offSelect() );	
		}
	}

	bool PE_the_matchScene::action_gameWait_mouseCheck()
	{
		Vector2 vec((float)__MOUSEDATA->mouseX, (float)__MOUSEDATA->mouseY);
		int count = 0;
		for(std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			count<GAMEWAIT_DIALOGSUM+1; it++, count++)
		{
			if( it == this->dialogList.begin() )	continue;

			if( (*it)->IsAtack_boundingbox_centerBox( &vec ) )
			{
				this->selectNumber = count;
				return true;
			}
		}	
		return false;
	}

	void PE_the_matchScene::Set_gamewaitFadeIn()
	{
		this->selectNumber = 0;

		WaitBackDialog* waits = new WaitBackDialog();
		this->dialogList.push_back( waits );

		//---------------------------------------------------------------
		//セレクトダイアログのセッティング
		//---------------------------------------------------------------
		SlidesideDialog* slide;
		for(int i=0; i<GAMEWAIT_DIALOGSUM; i++)
		{
			slide = new SlidesideDialog();
			slide->SetDialogName("dialog1");

			switch( i )
			{
				case 0:	slide->SetName( "gameStart" );			break;
				case 1:	slide->SetName( "gobackTittle" );		break;
			}
			slide->SetNumber( i );
			this->dialogList.push_back( slide );
		}

		//---------------------------------------------------------------
		//タイトルのダイアログ
		//---------------------------------------------------------------
		ExpansionDialog* title;
		title = new ExpansionDialog();
		title->SetDialogName( "titleYousi" );
		title->SetName( "gameStatus" );
		this->dialogList.push_back( title );

		//---------------------------------------------------------------
		//プレイヤーデータのダイアログ
		//---------------------------------------------------------------
		PlayerMapDialog* map;
		for( int i=0; i<4; i++ )
		{
			map = new PlayerMapDialog();
			map->SetNumber( &this->judgements.roomData.charaData[i], i, true );
			map->SetScore(true);
			this->dialogList.push_back( map );
		}
		//---------------------------------------------------------------
		//ルールデータのダイアログ
		//---------------------------------------------------------------
		LookatRuleDialog* look;
		for( int i=0, count=0; i<10; i++ )
		{
			if( (i < 7 && isDataRule( this->judgements.roomData.rule, i ) ) || 
				(i >= 7 && isDataRule( this->judgements.roomData.rule2, i) ) )
			{
				look = new LookatRuleDialog();
				look->SetNumber( count++, i );
				this->dialogList.push_back( look );
			}
		}

		//---------------------------------------------------------------
		//ラウンドのダイアログ
		//---------------------------------------------------------------
		DownSignDialog* sign = new DownSignDialog();
		sign->SetRound( this->judgements.GetGameCount()  );
		this->dialogList.push_back( sign );



		for(std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			it != this->dialogList.end(); it++)
			(*it)->SetFadeIn();

		this->_action = &PE_the_matchScene::action_gamewaitFadeIn;
	}

	void PE_the_matchScene::Set_gamewaitFadeOut()
	{
		for(std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			it != this->dialogList.end(); it++)
			(*it)->SetFadeOut();

		this->_action = &PE_the_matchScene::action_gamewaitFadeOut;
	}

	void PE_the_matchScene::Set_gameFinish()
	{
		this->judgements.roomData.playSum = 2;
		this->judgements.roomData.roundCount = this->judgements.roomData.rule = this->judgements.roomData.rule2 = 0;
		for(int i=0, siz=this->judgements.roomData.charaData.size(); i<siz; i++)
		{
			this->judgements.roomData.charaData[i].charaNum = i;
			this->judgements.roomData.charaData[i].poreFlag = (i==0);
			this->judgements.roomData.charaData[i].runk = i;
			this->judgements.roomData.charaData[i].score = 0;
			this->judgements.roomData.charaData[i].selectFlag = (i==0);
			this->judgements.roomData.charaData[i].spec = 0;
		}

		this->_action = &PE_the_matchScene::action_gobackToTittle;
	}

	void PE_the_matchScene::check_clickDialog()
	{
		bool clickCH = false;
		for(int i=0, siz=this->player.trumps.size(); i<siz; i++)
		{	
			if(	this->player.trumps[i].GetMouseTouch() == CARD_TOUCHSTATUS_CLICK )
			{
				clickCH = true;
				break;
			}
		}

		( clickCH ? this->clickDialog->SetName("rclickMap") : this->clickDialog->SetName("lclickMap") );
	}

	void PE_the_matchScene::Set_playerFace(int playNum, int faceNum)
	{
		PlayerPlate* pt = this->judgements.playerPlateList.GetPlayerPlate(playNum);
		if( !CHECK_NULL(pt) )
			pt->SetFace( faceNum );
	}

	void PE_the_matchScene::inputData(RoomData* _data, bool IsContinue)
	{
		this->judgements.roomData = *_data;
		this->judgements.roomData.charaData.resize(4);
		for(int i=0,siz=_data->charaData.size(); i<siz; i++)
			this->judgements.roomData.charaData[i] = _data->charaData[i];	

		this->judgements.roomData.roundCount = _data->roundCount;
		this->judgements.SettingRule( _data->rule, _data->rule2 );
		this->judgements.SetPlaySum( _data->playSum );
		this->judgements.scoreMap.inputScoreData( this->judgements.roomData, IsContinue );
		if( IsContinue )	this->judgements.SettingNowPlayer2();
	}

	//-----------------------------------------------------------------
	//描画
	//-----------------------------------------------------------------
	void PE_the_matchScene::Draw2D()
	{
		this->back.Draw2D();
		this->judgements.playerPlateList.yousiDraw();
		this->passDialog->Draw2D();
		this->selecterDialog->Draw2D();

		this->player.Draw();
		for( int i=0; i<this->judgements.GetPlaySum()-1; i++)
			enemy[i].Draw();

		if(this->judgements.GetNowPlayNum() == 0)
		{
			this->clickDialog->Draw2D();
			this->passclickDialog->Draw2D();
		}
		
		this->judgements.Draw2D();
		for(std::list<FadeNameDialog*>::iterator it = this->dialogList.begin();
			it != this->dialogList.end(); it++)
			(*it)->Draw2D();
		
		//-----------------------------------------
		//リストの描画
		//-----------------------------------------
		this->judgements.effectList.Draw();
	}

	void PE_the_matchScene::Draw()
	{
		//最初に描画する宣言
		this->GetManager()->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );	

		this->Draw2D();

		this->GetManager()->defaultDraw_afterAction( screen );

		this->GetManager()->DrawScreen( this->screen );
	}
}