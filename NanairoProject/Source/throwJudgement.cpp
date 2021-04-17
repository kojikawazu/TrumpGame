#pragma once

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//階段の「３４ジョーカー」、「ジョーカー１２」は確定できる！
	bool check_34_12(std::vector<TrumpCard>& judCard, int i, int sum)
	{
		int type = judCard[i-1].GetCardType();
		switch( sum )
		{
		case 1:
			if( judCard[i-1].GetCardNumber() == 1 && judCard[i].GetCardNumber() == 0 )
			{
				judCard[0].SetCardNumber( 1 , type );
				judCard[1].SetCardNumber( 0 ,type );
				judCard[2].SetCardNumber( 12 ,type );
				return true;
			}
			else if( judCard[i-1].GetCardNumber() == 3 && judCard[i].GetCardNumber() == 2 )
			{
				judCard[0].SetCardNumber( 4, type );
				judCard[1].SetCardNumber( 3, type );
				judCard[2].SetCardNumber( 2, type );
				return true;
			}
			break;
		case 2:
			if( judCard[i-1].GetCardNumber() == 1 && judCard[i].GetCardNumber() == 0 )
			{
				judCard[0].SetCardNumber( 1, type );
				judCard[1].SetCardNumber( 0, type );
				judCard[2].SetCardNumber( 12, type );
				judCard[3].SetCardNumber( 11, type );
				return true;
			}
			else if( judCard[i-1].GetCardNumber() == 3 && judCard[i].GetCardNumber() == 2 )
			{
				judCard[0].SetCardNumber( 5, type );
				judCard[1].SetCardNumber( 4, type );
				judCard[2].SetCardNumber( 3, type );
				judCard[3].SetCardNumber( 2, type );
				return true;
			}
			break;
		}
	
		return false;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//自分のカードチェック
	bool GameScene::throwPlayerCard_inJudgmentCard_check(std::vector<TrumpCard>& judCard, std::vector<int>& sej )
	{
		bool jockerFlag = false, hantei = false, same_or_stairs = false, kakutei = false;
		int siz = judCard.size(), count = 0, jockerCnt = 0, temp = 0, stairs = 0;
		TrumpCard tempCard;

		for(int i=0; i<siz; i++)
		{
			//出せる枚数が増えたらカウント
			//２枚出しモードチェンジ
			( (jockerFlag = judCard[i].isJocker()) ? jockerCnt++ : count++ );

			if( count == 1 )
				temp = judCard[i].GetCardNumber();
			else if( count == 2 )
			{
				//--------------------------------------------------
				//カードが同じだった場合
				if ( this->judgement_same( judCard, temp, i, jockerCnt ) )
				{
					same_or_stairs = hantei = true;
					break;
				}
				//--------------------------------------------------
				//違うカードだった場合
				else
				{
					stairs = abs( TRUMP_POWER[judCard[i-1].GetCardNumber()] - 
							TRUMP_POWER[judCard[i].GetCardNumber()] );
					switch( jockerCnt )
					{
					case 0:	//J０＋S２
						//もう１枚カードがないとOUT
						if( count + jockerCnt <= 2 || stairs != 1)
						{
							//3456の４枚のカードなどがきた場合
							if( judCard.size() < 3 || stairs != 1 )
								return false;
						}
						break;
					case 1:	//J１＋S２＋あともう１枚カードがある。
						switch( stairs )
						{
						case 1:	//差が１の場合、隣あわせになる。
							//---------------------------------------------------------------
							//次のカードがある場合
							//次のカードとの差が３以上はOUT!!
							if( i+1 == siz-1 ) 
							{
								if( abs( judCard[i].GetTrumpNumber() - 
										judCard[i+1].GetTrumpNumber() ) >= 3 )
										return false;
								kakutei = check_34_12( judCard, i+1, jockerCnt + 1 );
							}
							else	//なかったら 
								//ここで、\34→34\ \12→K12
								kakutei = check_34_12( judCard, i, jockerCnt );
							
							//---------------------------------------------------------------
							break;
						case 2://差が２の場合、間に来ること前提
							//---------------------------------------------------------------
							//次のカードがある場合
							if( i+1 == siz-1 ) 
							{	//次のカードとのさが１ならOK!
								if( abs( judCard[i].GetTrumpNumber() - judCard[i+1].GetTrumpNumber() ) != 1 )
										return false;
							}
							else
							{	//次のカードがないので間に来ること確定！
								judCard[0].SetCardNumber( judCard[1].GetCardNumber() );
								judCard[1].SetCardNumber( judCard[1].GetCardNumber() - 1 );
								kakutei = true;
							}
							//---------------------------------------------------------------
							break;
						default: //差が３以上はOUT
							return false;
						}
						break;
					case 2:	//J２＋S２これですべて
						//-------------------------------
						//他のカードがあったり
						//差が４以上だとOUT!
						if( count + jockerCnt != 4 || stairs >= 4 )
							return false;
						//-------------------------------
						else	
						{
							switch( stairs )
							{
								case 1:	//ここで、\\34→34\\ \\12→QK12
									 check_34_12(judCard, i, 3);
									break;
								case 2:
									if( judCard[i-1].GetCardNumber() == 1 && judCard[i].GetCardNumber() == 12 )
									{
										judCard[0].SetCardNumber( 1 );
										judCard[1].SetCardNumber( 0 );
										judCard[2].SetCardNumber( 12 );
										judCard[3].SetCardNumber( 11 );
										kakutei = true;
									}
									else if( judCard[i-1].GetCardNumber() == 4 && judCard[i].GetCardNumber() == 2 )
									{
										judCard[0].SetCardNumber( 5 );
										judCard[1].SetCardNumber( 4 );
										judCard[2].SetCardNumber( 3 );
										judCard[3].SetCardNumber( 2 );
										kakutei = true;
									}
									break;
								case 3:	//３の場合は２枚のジョーカーが間にくること確定！
									for(int j=0;j<2;j++)
										judCard[j].SetCardNumber( judCard[i].GetCardNumber() + j + 1 );
									tempCard = judCard[0];
									judCard[0] = judCard[i-1];
									judCard[i-1] = tempCard;
									kakutei = true;
									break;
							}
						}
						break;
					}
					
					same_or_stairs = false;
					hantei = true;
				}
			}
		}

		return hantei = this->throwPlayerCard_inJudgmentCard_checkOut( judCard, count, jockerCnt, temp, hantei, kakutei, same_or_stairs );
	}

	//今度は出しているカードチェック
	bool GameScene::throwPlayerCard_inJudgmentCard_checkOut(std::vector<TrumpCard>& judCard, int count, int jockerCnt, int temp, bool hantei, bool kakutei, bool same_or_stairs)
	{
		int siz = judCard.size();
		//場にカードがない場合
		if( this->judgements.frontCard.empty() )
		{
			//------------------------------------------------------------
			//ジョーカー以外枚数が０～１の場合のみ
			switch( count )
			{
				case 0:
					//---------------------------------------------------
					//ジョーカー２枚だしで同じカード出したことに
					if( jockerCnt > 1 && !kakutei )	
						this->judgements.changeSame( true );
					hantei = true;
					//---------------------------------------------------
					break;
				case 1:
					//---------------------------------------------------
					//ジョーカー枚数１枚でもあり、他のカードが１枚ならば
					if( jockerCnt > 0 )
					{
						//ジョーカー枚数１枚なら同じカードに
						if( jockerCnt > 0 )
						{
							//同じカードにしかならない
							for( int j=0; j<jockerCnt; j++ )
								judCard[j].SetCardNumber( judCard[jockerCnt].GetCardNumber(),
															judCard[jockerCnt].GetCardType() );
							this->judgements.changeSame( true );
						}
						//それ以外は階段
						else{}
					}
					//---------------------------------------------------
					hantei = true;
					break;
				case 2:	//２枚だった場合,同じかもしくは階段（ジョーカー次第）です。
					if( same_or_stairs )
						this->judgements.changeSame( true );
					else
					{
						if( kakutei )
						{
							this->judgements.changeStairs( true );
							this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );
							hantei = true;
						}
						else
						{
							switch( jockerCnt )
							{
							case 1:
								//革命中は選んだカードの下限値ー１にする
								if( this->judgements.isRevolution() )
								{
									for(int j=0; j<2; j++)
										judCard[j].SetCardNumber( judCard[j+1].GetCardNumber() );
									judCard[2].SetCardNumber( judCard[2].GetCardNumber() - 1 );
								}
								//それ以外は選んだカードの上限値＋１にする
								else
									judCard[0].SetCardNumber( judCard[1].GetCardNumber() + 1 );
								this->judgements.changeStairs( true );
								this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );
								hantei = true;
								break;
							case 2:
								//--------------------------------------------------------------------------
								//間にジョーカーを入れる場合
								for(int j=2, siz = judCard.size()-1, jud = jockerCnt; j<siz; j++ )
								{
									if( abs( judCard[j].GetTrumpNumber() - judCard[j+1].GetTrumpNumber()) > 1)
									{
										for(int k=jud-1; k<j; k++)
											judCard[k].SetCardNumber( judCard[k+1].GetCardNumber() );
										judCard[j].SetCardNumber( judCard[j-1].GetCardNumber() - 1 );		
										jud--;
										if( jud == 0)
										{
											kakutei = true;
											break;
										}
									}
								}
								//--------------------------------------------------------------------------

								if( !kakutei )
								{
									//革命中は選んだカードの下限値ー１にする
									if( this->judgements.isRevolution() )
									{
										if( judCard[2].GetCardNumber() == 2 )
										{
											for(int j=0; j<4; j++)
												judCard[j].SetCardNumber( 5-j, judCard[2].GetCardType() );
										}
										else
										{
											for(int j=0; j<3; j++)
												judCard[j].SetCardNumber( judCard[j+1].GetCardNumber() );
											judCard[3].SetCardNumber( judCard[3].GetCardNumber() - 1 );
										}
									}
									//それ以外は選んだカードの上限値＋１にする
									else
									{
										if( judCard[2].GetCardNumber() == 1 )
										{
											judCard[0].SetCardNumber( 1, judCard[2].GetCardType() );
											judCard[1].SetCardNumber( 0, judCard[0].GetCardType() );
											judCard[2].SetCardNumber( 12, judCard[0].GetCardType() );
											judCard[3].SetCardNumber( 11, judCard[0].GetCardType() );
										}
										else
										{
											for(int j=0; j<2; j++)
												judCard[j].SetCardNumber( judCard[2].GetCardNumber() + 2 - j );
										}
									}
								}
								this->judgements.changeStairs( true );
								this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );
								hantei = true;
								break;
							}
						}
					}
					break;
				case 3:	//３枚だった場合、残りはジョーカー１枚の可能性あり
					if( jockerCnt == 0 )
					{
						if( !same_or_stairs && !kakutei)
						{
							for(int i=0; i<siz-1; i++)
							{
								if( abs( judCard[i].GetTrumpNumber() - judCard[i+1].GetTrumpNumber() ) != 1 )
									return false;
							}
						}

						(same_or_stairs ? this->judgements.changeSame( true ) : this->judgements.changeStairs( true ) );
						if( !same_or_stairs )	this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );
						kakutei = true;
					}
					else
					{
						//--------------------------------------------------------------------------
						//間にジョーカーを入れる場合
						for(int j=1, siz = judCard.size()-1; j<siz; j++ )
						{
							if( abs( judCard[j].GetTrumpNumber() - judCard[j+1].GetTrumpNumber()) > 1)
							{
								for(int k=0; k<j; k++)
									judCard[k].SetCardNumber( judCard[k+1].GetCardNumber() );
								judCard[j].SetCardNumber( judCard[j-1].GetCardNumber() - 1 );
								kakutei = true;
								break;
							}
						}
						//--------------------------------------------------------------------------

						//隣あわせの場合
						//--------------------------------------------------------------------------
						if( !kakutei )
						{
							//革命中は選んだカードの下限値ー１にする
							if( this->judgements.isRevolution() )
							{
								for(int j=0; j<3; j++)
									judCard[j].SetCardNumber( judCard[j+1].GetCardNumber() );
								judCard[3].SetCardNumber( judCard[3].GetCardNumber() - 1 );
							}
							//それ以外は選んだカードの上限値＋１にする
							else
								judCard[0].SetCardNumber( judCard[1].GetCardNumber() + 1 );
						}
						//--------------------------------------------------------------------------

						this->judgements.changeStairs( true );
						this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );
					}
					hantei = true;
					break;
				case 4:	//ジョーカーはないことがわかる。
					(same_or_stairs ? this->judgements.changeSame( true ) : this->judgements.changeStairs( true ) );
					if( !same_or_stairs )	this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );

					//さらに革命だよね
					this->judgements.changeRevolution( !this->judgements.isRevolution() );
					if( this->judgements.isRevolution() )
					{
						this->judgements.plateList.Push( TRUMP_RULE_REVOLUTION );
						this->back.SetBackName("back2");
					}
					else
					{
						this->judgements.plateList.Pop( TRUMP_RULE_REVOLUTION );
						this->back.SetBackName("back");
					}

					this->judgements.push_ruleEffect( TRUMP_RULE_REVOLUTION );
					hantei = true;
					break;
			}
			//------------------------------------------------------------
		}
		else
		{
			int judNumber = ( this->judgements.isRevolution() ?
			this->judgements.frontCard[this->judgements.nowCard + this->judgements.frontCardSum - 1].GetCardNumber() :
			this->judgements.frontCard[this->judgements.nowCard].GetCardNumber() );

			//同じカード出しはほかの場所で一緒にやります。
			if( !hantei || !kakutei )
			{
				//階段だしのとき,通常１枚＋ジョーカー２枚の時がある
				if( this->judgements.isStairs() )
					hantei = this->judgement_bystairs_onecard( judCard, count, jockerCnt );
				//ジョーカー２枚出し
				else if( this->judgement_bysame_twoJocker( judCard, count, jockerCnt ) )
					return true;
				//１枚出しの時
				else if( !hantei )
					hantei = this->judgement_byno_onfront( judCard, count, jockerCnt );
			}
		}
		return hantei;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//カードの枚数チェック
	bool GameScene::throwPlayerCard_inJudgmentCard_sameSum(std::vector<TrumpCard>& plcards)
	{
		int siz = plcards.size(), count = 0;
		//-------------------------------------------------------------------
		//カードの枚数があってないとアウト
		for(int i=0; i<siz; i++)
		{
			if(plcards[i].GetMouseTouch() == CARD_TOUCHSTATUS_CLICK &&
				plcards[i].GetCardStatus() != CARD_STATUS_DES )
				count++;
		}

		if( count == 0 )	return false;
		return !( this->judgements.frontCardSum != 0 &&
			count != this->judgements.frontCardSum );
		//-------------------------------------------------------------------
	}

	//同じカードが２枚出されている時にジョーカー２枚出し
	bool GameScene::judgement_bysame_twoJocker(std::vector<TrumpCard>& judCard,int count, int jockerCnt)
	{
		return ( count == 0 && jockerCnt == 2 &&
			this->judgements.isSame() );
	}

	//同じものを出す時のチェック関数
	bool GameScene::judgement_same(std::vector<TrumpCard>& judCard,int temp, int i, int jockerCnt)
	{
		bool hantei = false;
		int ftemp = 0;
		if( temp == judCard[i].GetCardNumber() )
		{
			//何も出されていないなら無条件にOK!
			if( judgements.frontCard.empty() )
				hantei = true;
			else
			{
				//-------------------------------------------------------------------
				//ジョーカーだと無理！
				if( this->judgements.frontCard[this->judgements.nowCard].isJocker() )
					return false;
				//-------------------------------------------------------------------

				ftemp = this->judgements.frontCard[this->judgements.nowCard].GetCardNumber();
				if( this->judgements.isRevolution() ? 
					CHECK_TRUMP_BIGGER( ftemp, temp ) : CHECK_TRUMP_SMALLER( ftemp, temp ) )	
					hantei = true;
			}

			//成功したら
			if( hantei )
			{
				std::vector<int> resType;
				for(int i=judCard.size()-1; i>=0; i--)
				{
					if( !judCard[i].isJocker() )
						resType.push_back( judCard[i].GetCardType() );
					else
					{
						for(int k=0, okf = 0; k<4; k++)
						{
							okf = 1;
							for(int j=0, jsiz = resType.size(); j<jsiz; j++)
							{
								if( resType[j] == k )
								{
									okf = 0;
									break;
								}
							}
							if( okf )
							{
								judCard[i].SetCardNumber( 
									judCard[jockerCnt].GetCardNumber(), k );
								break;
							}
						}
					}
				}

				if( judCard.size() == 4 )
				{
					this->judgements.changeRevolution( !this->judgements.isRevolution() );
					if( this->judgements.isRevolution() )
					{
						this->judgements.plateList.Push( TRUMP_RULE_REVOLUTION );
						this->back.SetBackName("back2");
					}
					else
					{
						this->judgements.plateList.Pop( TRUMP_RULE_REVOLUTION );
						this->back.SetBackName("back");
					}
					this->judgements.push_ruleEffect( TRUMP_RULE_REVOLUTION );
				}
			}
		}
		
		return hantei;
	}

	//場にカードがある場合、そして１枚しかカードが出されていない場合
	bool GameScene::judgement_byno_onfront(std::vector<TrumpCard>& judCard,int count, int jockerCnt)
	{
		int temp = 0;

		//--------------------------
		//ジョーカー選択中だと
		if( jockerCnt == 1 && count == 0 )
			return true;
		//--------------------------
		else if( count == 1 )
		{
			//----------------------------------------------------------------------
			//ジョーカーが表に出されていたら
			if( this->judgements.frontCard[ this->judgements.nowCard ].isJocker() )
			{
				//スペード３返しのため
				if( judCard[0].GetCardNumber() == 2 &&
					judCard[0].GetCardType() == CARD_SPADE )
					return true;
			}
			//----------------------------------------------------------------------
			else
			{
				//----------------------------------------------------------------------
				//スペ３返しは何もカード出せない
				if( this->judgements.isSpade3() )
					return false;
				//----------------------------------------------------------------------
				else
				{
					temp = this->judgements.frontCard[ this->judgements.nowCard ].GetCardNumber();

					//-------------------------------------------------------------------
					//縛りルール採用時、同じマークの種類じゃないとOUT！
					if( this->judgements.isRestrains() &&
						!(this->judgements.restrainsType[0] == judCard[jockerCnt].GetCardType() ||
						( this->judgements.restrainsType.size() == 2 && this->judgements.restrainsType[1] == judCard[jockerCnt].GetCardType() ) ) )
						return false;
					//-------------------------------------------------------------------

					if( jockerCnt > 0 )
					{
						if( this->judgements.isRevolution() ?
							CHECK_TRUMP_BIGGER( temp, judCard[jockerCnt].GetCardNumber() ) :
							CHECK_TRUMP_SMALLER(  temp, judCard[jockerCnt].GetCardNumber() ) )
						{	
							if( judgements.isRestrains() )
								this->changeJocker_resTrains( judCard, jockerCnt );
							else
							{
								for(int i=0; i<jockerCnt; i++)
									judCard[i].SetCardNumber( judCard[jockerCnt].GetCardNumber(), judCard[jockerCnt].GetCardType() );
							}
							return true;
						}
						else 
							return false;
					}


					//-------------------------------------------------------------------
					//後は見比べて大きい数字、又は革命中小さい数字ならOK!
					if( this->judgements.isRevolution() ?
						CHECK_TRUMP_BIGGER( temp, judCard[0].GetCardNumber() ) :
						CHECK_TRUMP_SMALLER(  temp, judCard[0].GetCardNumber() ) )
						return true;
					//-------------------------------------------------------------------
				}
			}
		}

		return false;
	}

	//階段だしのとき,通常１枚＋ジョーカー２枚の時がある
	//階段だしのとき,通常２枚＋ジョーカー１枚の時がある
	bool GameScene::judgement_bystairs_onecard(std::vector<TrumpCard>& judCard,int count, int jockerCnt)
	{
		int type = judCard[2].GetCardType();
		switch( judCard[2].GetCardNumber() )
		{
		case 0:	//Aのとき
		case 1:
		case 12:
			judCard[0].SetCardNumber(1, type );
			judCard[1].SetCardNumber(0, type );
			judCard[2].SetCardNumber(12, type );
			return true;
		case 2:	//3のとき
		case 3:	//4のとき
		case 4:	//5のとき
			judCard[0].SetCardNumber(4, type );
			judCard[1].SetCardNumber(3, type );
			judCard[2].SetCardNumber(2, type );
			return true;
		}

		switch( count )
		{
		case 1:
			if( this->judgements.isRevolution() )
			{
				judCard[0].SetCardNumber(judCard[2].GetCardNumber(), type );
				judCard[1].SetCardNumber(judCard[0].GetCardNumber() - 1, type );
				judCard[2].SetCardNumber(judCard[0].GetCardNumber() - 2, type );
			}
			else
			{
				for(int i=0; i<2; i++)
					judCard[i].SetCardNumber(judCard[2].GetCardNumber() + 2-i, type );
			}
			return true;
		case 2:
			if( this->judgements.isRevolution() )
			{
				judCard[0].SetCardNumber(judCard[1].GetCardNumber(), type );
				judCard[1].SetCardNumber(judCard[2].GetCardNumber(), type );
				judCard[2].SetCardNumber(judCard[1].GetCardNumber() - 1, type );
			}
			else
				judCard[0].SetCardNumber(judCard[1].GetCardNumber() + 1, type );
			return true;
		}

		return false;
	}
}