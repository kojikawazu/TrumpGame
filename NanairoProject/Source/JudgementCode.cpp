#pragma once

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	//カードを出す
	bool GameScene::throwPlayerCard_inJudgmentCard(std::vector<TrumpCard>& plcards)
	{
		bool isSort = false, check = false, isRes = false, isFrontEffect = false;
		int siz = plcards.size(), count = 0, sametemp = 0, jockerCnt = 0, startCnt = 0, 
			resSize = this->judgements.restrainsType.size();

		//------------------------------------------------------------
		//枚数チェック
		if( !this->throwPlayerCard_inJudgmentCard_sameSum( plcards ) )
			return false;
		//------------------------------------------------------------

		std::vector<TrumpCard>	checkTrump;
		std::vector<int>		tempNumber, lis;
		count = 0;
		startCnt = this->judgements.frontCardSum;
		//一度格納しよう。
		for(int i=0; i<siz; i++)
		{
			//クリック状態のやつ
			if(plcards[i].GetMouseTouch() == CARD_TOUCHSTATUS_CLICK &&
				plcards[i].GetCardStatus() != CARD_STATUS_DES )
			{
				//出せる枚数が増えたらカウント
				//２枚出しモードチェンジ
				( plcards[i].isJocker() ? jockerCnt++ : count++ );

				//とりあえずカードと添え字を格納
				checkTrump.push_back( plcards[i] );
				tempNumber.push_back( i );
			}
		}

		//--------------------------------------------------------------------------
		//そしてチェック
		if( !this->throwPlayerCard_inJudgmentCard_check( checkTrump, tempNumber ) )
			return false;
		//--------------------------------------------------------------------------
		
		siz = tempNumber.size();
		//-----------------------------------------------------------
		//添え字移動
		this->judgements.nowCard += this->judgements.frontCardSum;
		this->judgements.frontCardSum = count + jockerCnt;
		//-----------------------------------------------------------

		int foulSum = 0;
		for(int i=0, chSiz = plcards.size(); i<chSiz; i++, foulSum++)
		{
			if( plcards[i].isCardDes() )
				break;
		}

		//------------------------------------------------------------------------------------------------------------
		//カードの格納
		int nowMax = siz;
		for(int i=0; i<siz; i++)
		{
			//格納
			checkTrump[i].offSelectOK();
			plcards[ tempNumber[i] ].offSelectOK();
			this->judgements.frontCard.push_back( checkTrump[i] );
			this->judgements.frontCard[this->judgements.frontCard.size() - 1].SetCenterMove(i, siz );
			this->judgements.frontCard[this->judgements.frontCard.size() - 1].parts.color.SetMaxColor();
			plcards[ tempNumber[i] ].ChangeDraw( CARD_STATUS_DES );

			
			//-------------------------------------------------
			//トランプ番号が「８」の場合、8きり発動！
			if( checkTrump[i].GetCardNumber() == 7 )
				this->judgements.changeEightcut( true );
			//トランプ番号が「11」の場合、イレブンバック発動！
			else if( !isFrontEffect && this->judgements.isUseElevenback() && checkTrump[i].GetCardNumber() == 10 )
			{
				this->judgements.changeElevenback( !this->judgements.isElevenback() );
				( this->judgements.isElevenback() ? 
					this->judgements.plateList.Push( TRUMP_RULE_ELEVENBACK ) : 
					this->judgements.plateList.Pop( TRUMP_RULE_ELEVENBACK ) );
				this->judgements.push_ruleEffect( TRUMP_RULE_ELEVENBACK );
				isFrontEffect = true;
			}
			//トランプが「ジョーカー」の場合、ジョーカー降臨
			else if( !isFrontEffect && checkTrump[i].isJocker() && 
				!this->judgements.isStairs() && !this->judgements.isSame() )
			{
				this->judgements.push_ruleEffect( TRUMP_RULE_JOCKER );
				this->judgements.changeJocker( true );
				isFrontEffect = true;
			}
			else if( !isFrontEffect && checkTrump.size() == 2 && 
				checkTrump[0].isJocker() && checkTrump[1].isJocker() &&
				this->judgements.isSame() )
			{
				this->judgements.push_ruleEffect( TRUMP_RULE_JOCKER );
				this->judgements.changeJocker( true );
				isFrontEffect = true;
			}
			//トランプ番号が「スペードの３」の場合、ジョーカーのみ場に出てたらスペ３返し発動！
			else if( this->judgements.isUseSpade3() && this->judgements.isJocker() &&
				checkTrump[i].GetCardNumber() == 2 && checkTrump[i].GetCardType() == CARD_SPADE )
			{
				this->judgements.changeSpade3( true );
				this->judgements.changeJocker( false );
				this->judgements.plateList.Pop( TRUMP_RULE_JOCKER );
				this->judgements.push_ruleEffect( TRUMP_RULE_SPADE3 );
			}
			//-------------------------------------------------

			//--------------------------------------------------------
			//縛りチェック
			if( this->judgements.isUseRestrains() ) 
			{
				CARD_TYPE ty = checkTrump[i].GetCardType();
				if( startCnt == 0 )
					this->judgements.restrainsType.push_back( ty );
				else if( !this->judgements.isRestrains() )
				{
					//-------------------------------------------------
					//同じタイプを探す
					bool checker = false;
					for(int j=0; j<resSize; j++)
					{
						if( ty == this->judgements.restrainsType[j])
						{
							//-------------------------------------------------
							//被っていないか探す
							checker = false;
							for(int k=0, liss = lis.size(); k<liss; k++)
							{
								if( lis[k] == j )
								{
									//被ってたOUT!もう一回探せ！
									checker = true;
									break;
								}
							}
							if(!checker)	//被っていないなら終了！
								lis.push_back(j);
						}
					}
				}
			}
			//--------------------------------------------------------

			if( this->judgements.isUseFoul() && foulSum - siz == 0 )
			{
				if( checkTrump[i].isJocker() || 
					checkTrump[i].GetCardNumber() == 7 ||
					( this->judgements.isRevolution() ?
					checkTrump[i].GetCardNumber() == 2 : checkTrump[i].GetCardNumber() == 1 ) )
					this->judgements.foulFlag = true;
			}
		}

		//------------------------------------------------
		//同じマークが同じ数あったら
		if( this->judgements.isUseRestrains() )
		{
			if( lis.size() == this->judgements.frontCardSum )
			{	//縛りきたっ
				this->judgements.changeRestrains( true );
				this->judgements.push_ruleEffect( TRUMP_RULE_RESTRAINS );
			}
			else
			{
				//縛りこなかったら、そのカードの種類に入れ替えましょう！
				this->judgements.restrainsType.clear();
				for(int i=0; i<siz; i++)
					this->judgements.restrainsType.push_back( checkTrump[i].GetCardType() );
			}
		}
		//------------------------------------------------

		//------------------------------------------------------------------------------------------------------------

		isSort = true;
		count += jockerCnt;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//カードチェック
	void GameScene::throwJudgement(std::vector<TrumpCard>& plcards)
	{
		bool same_or_stairs = false;
		int siz = plcards.size(), temp = -1, count = 0, sametemp, jockerCnt = 0, use_jocker = 0;
		for(int i=0; i<siz; i++)
			plcards[i].offSelectOK();

		//ジョーカー出された後にスペ３返しされたら飛ばし
		if( this->judgements.isSpade3() &&
			this->judgements.frontCard[this->judgements.nowCard - 1].isJocker() &&
			this->judgements.frontCard[this->judgements.nowCard].GetCardNumber() == 2 )
			return ;
		
		//まず選択しているのを探そう
		for(int i=0; i<siz; i++)
		{
			//使用済みカードは飛ばす
			if( plcards[i].GetCardStatus() == CARD_STATUS_DES )
				continue;

			//クリックしたカードを探す
			if( plcards[i].GetMouseTouch() == CARD_TOUCHSTATUS_CLICK )
			{
				plcards[i].onSelectOK();
				( plcards[i].isJocker() ? jockerCnt++ : count++ );
				
				//選択カード２枚目で複数出しか階段かチェック
				if( count == 2 )
				{
					same_or_stairs = ( plcards[i].GetCardNumber() == sametemp );
					
					if( !same_or_stairs && jockerCnt == 1)
						use_jocker++;
				}
				//選択カード１枚目記録
				else if( count == 1 )
				{
					temp = i;
					sametemp = plcards[i].GetCardNumber();
				}
			}
		}
		if( count >= 4 )
			return ;

		count += jockerCnt;
		jockerCnt -= use_jocker;
		//-------------------------------------------------------------
		//複数出し＋同じカードなら
		if( this->judgements.isSame() )
		{
			this->throwJudgement_bysame( plcards, temp, count, jockerCnt,
				same_or_stairs );
		}
		//複数出し＋階段なら
		else if( this->judgements.isStairs() )
		{
			this->throwJudgement_bystairs( plcards, temp, count, jockerCnt,
				same_or_stairs );
		}
		//何のルールなしなら
		else if( !this->judgements.isSpade3() )
		{
			this->throwJudgement_byno( plcards, temp, count, jockerCnt,
				same_or_stairs );
		}
	}
	
	//場に普通なカードが出されている時の関数
	void GameScene::throwJudgement_byno(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size();
		//ジャッジ空なら
		if( this->judgements.frontCard.empty() )
		{
			//選択しているものがなかったら
			if( selectNumber == -1 )
			{
				for(int i=0; i<siz; i++)
				{
					if( !plcards[i].isCardDes() )
						plcards[i].onSelectOK();
				}
			}
			//選択しているものがあったら
			else
			{
				//同じものを複数選択しているか、１枚選択していたら
				this->throwJudgement_byno_selectSame( plcards, selectNumber, selectCount, jockerCnt, same_or_stairs );
				this->throwJudgement_byno_selectStairs( plcards, selectNumber, selectCount, jockerCnt, same_or_stairs );
			}
		}
		//ジャッジ入っていると
		else if( selectCount + jockerCnt != this->judgements.frontCardSum )
			this->throwJudgement_byno_selecting( plcards, selectNumber, selectCount, jockerCnt, same_or_stairs );

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//同じものを複数選択しているか、１枚選択していたら
	void GameScene::throwJudgement_byno_selectSame(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int count = 0, siz = plcards.size();
		//同じものを複数選択しているか、１枚選択していたら
		if( (selectCount - jockerCnt > 1 && same_or_stairs) || selectCount - jockerCnt == 1 )
		{
			count = 0;
			for(int i=0; i<siz; i++ )
			{	
				//------------------------------------------------------
				//選択中、使用済みは飛ばす
				if( plcards[i].isCardER() )		continue;
				//------------------------------------------------------

				//------------------------------------------------------
				//選択中のカードと探すカードの番号が一緒なら
				if(	!plcards[i].isJocker() &&
					CHECK_SAMER(plcards[selectNumber].GetCardNumber(), 
								plcards[i].GetCardNumber() ) )
				{
					plcards[i].onSelectOK();
					count++;
					if( count + selectCount > 4 )
						break;
				}
				//------------------------------------------------------
			}
		}

	}

	//階段選択しているか、１枚選択していたら
	void GameScene::throwJudgement_byno_selectStairs(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int count = 0, siz = plcards.size(), temp = 0, jockerDown = jockerCnt,type = 0, sub = 0;
		std::vector<int> lis;
		//階段選択しているか、１枚選択していたら
		if( (selectCount - jockerCnt > 1 && !same_or_stairs) || selectCount - jockerCnt == 1 )
		{
			count = 0;
			for(int j=0, left = 0, right = 0; j<2; j++)
			{
				//-------------------------------------------------------
				//選択しているデータの番号保存
				temp = plcards[selectNumber].GetCardNumber(); 
				type = plcards[selectNumber].GetCardType();
				jockerDown = jockerCnt;
				//-------------------------------------------------------
				for(int i=(j == 0 ? selectNumber - 1 : selectNumber + 1), cnt = 0; 
						(j == 0 ? i>=0 : i<siz) && cnt + selectCount <= 3; (j == 0 ? i-- : i++ ) )
				{
					//使用済みは当然飛ばす
					if( plcards[i].isCardDes() )	
						continue;

					//-------------------------------------------------------
					//添え字番号のデータを保存
					left = plcards[i].GetCardNumber();
					right = plcards[i].GetCardType();
					//-------------------------------------------------------

					//-------------------------------------------------------
					//カードの絶対値の差が１以上、かつ同じ種類のカードなら
					sub = abs( TRUMP_POWER[temp] - TRUMP_POWER[left] );
					if( sub != 0 && sub > 1  && type == right )
					{
						for(int k=0; k<sub-1;k++)
							jockerDown--;
						//ジョーカーがあれば大丈夫！通しましょう
						if( jockerDown < 0 )
							break;
					}
					//-------------------------------------------------------

					//-------------------------------------------------------
					//選択されているなら保存しようぜっ
					if( plcards[i].GetSelectOK() && 
						sub != 0 )
					{
						temp = left;
						continue;
					}	
					//-------------------------------------------------------

					//-------------------------------------------------------
					//大きい、又は革命中小さいのなら
					if(	( j == 0 ? CHECK_TRUMP_SMALLER(temp, left) : CHECK_TRUMP_BIGGER(temp, left) ) &&
						type == right )
					{
						plcards[i].onSelectOK();
						temp = left;
						lis.push_back(i);
						count++;
						cnt++;
					}
					//-------------------------------------------------------

				}
			}

			siz = lis.size();
			//--------------------------------------
			//階段２枚じゃ成立しませんよっ
			if( count + selectCount < 3 )
			{
				for(int i=0; i<siz; i++)
					plcards[lis[i]].offSelectOK();
			}
			//--------------------------------------
		}
	}

	//何も出されていない、選択されていない、
	void GameScene::throwJudgement_byno_selecting(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size();
		//ジャッジカードより大きいやつのみ選択OK！
		for(int i=0; i<siz; i++)
		{	
			//----------------------------------------------------------------------
			//使用済み、選択できるやつは飛ばす！
			if( plcards[i].isCardER() )		
				continue;
			//----------------------------------------------------------------------

			//----------------------------------------------------------------------
			//ジョーカー１枚出されていると
			if( this->judgements.frontCard[ this->judgements.nowCard ].isJocker() )
			{
				//スペードの「３」のみ選択可能
				if( plcards[i].GetCardNumber() == 2 && 
					plcards[i].GetCardType() == CARD_SPADE )
					plcards[i].onSelectOK();
				continue;
			}
			//----------------------------------------------------------------------

			//----------------------------------------------------------------------
			//通常検査
			if( ( this->judgements.isRevolution() ? 
				CHECK_TRUMP_BIGGER(this->judgements.frontCard[ this->judgements.nowCard ].GetCardNumber(),
								plcards[i].GetCardNumber() ) : 
				CHECK_TRUMP_SMALLER(this->judgements.frontCard[ this->judgements.nowCard ].GetCardNumber(),
								plcards[i].GetCardNumber() ) ) )
			{
				//------------------------------------------------------------------------------------------------------
				//縛りルール適用の際、同じマークだったらOKです。
				if( this->judgements.isRestrains() &&
					this->judgements.frontCard[ this->judgements.nowCard ].GetCardType() != plcards[i].GetCardType() &&
					!plcards[i].isJocker() )
					continue ;
				//------------------------------------------------------------------------------------------------------
				plcards[i].onSelectOK();
			}
			//----------------------------------------------------------------------
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//場に同じカードが複数出されている時の関数
	void GameScene::throwJudgement_bysame(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size(), count, temp, joCnt;
		CARD_TYPE type;
		std::vector<int> typeList;
		if( this->judgements.frontCardSum == 2 &&
			jockerCnt == 2 )
			return ;

		//ジョーカー防止
		int judcard = ( this->judgements.frontCard[this->judgements.nowCard].isJocker() ?
						this->judgements.frontCard[this->judgements.nowCard + 1].GetCardNumber() :
						this->judgements.frontCard[this->judgements.nowCard].GetCardNumber() );
		if( selectCount - jockerCnt <= 0 )
		{
			for(int i=0; i<siz; i++)
			{
				//使用済みは飛ばす
				if( plcards[i].GetCardStatus() == CARD_STATUS_DES )
					continue;

				temp = plcards[i].GetCardNumber();
				type = plcards[i].GetCardType();
				typeList.clear();
				//-----------------------------------------------------------------------------
				//大きいカードか、又は革命中小さいカードか
				if( this->judgements.isRevolution() ? 
					CHECK_TRUMP_BIGGER( judcard, temp) : CHECK_TRUMP_SMALLER( judcard, temp) )
				{
					//縛りルール採用時に呼ばれる
					if( !this->check_resTrains( type, typeList ) )
						continue;

					//--------------------------------------------------
					//隣を辿って同じカードだけカウントします
					count = 0;
					joCnt = jockerCnt;
					if( plcards[i].isJocker() )
					{
						joCnt--;
						count--;
					}
					for(int j=i+1;j<siz;j++)
					{
						if( plcards[j].GetCardStatus() != CARD_STATUS_DES )
						{
							
							if( temp != plcards[j].GetCardNumber() )
							{
								/*if( joCnt > 0 &&
									(this->judgements.isRevolution() ? 
										CHECK_TRUMP_BIGGER( judcard, plcards[j].GetCardNumber()) : CHECK_TRUMP_SMALLER( judcard, plcards[j].GetCardNumber() ) ) )
								{
									joCnt--;
									count++;
								}*/
							}
							else
							{
								type = plcards[j].GetCardType();
								if( !this->check_resTrains( type, typeList ) )
									continue;
								count++;
							}
						}
					}
					//--------------------------------------------------

					//--------------------------------------------------
					//カウント条件と一緒ならセレクト！
					if( count + 1 + jockerCnt >= this->judgements.frontCardSum )
					{
						for(int j=i;j<i + count + 1;j++)
							plcards[j].onSelectOK();
						i += count;
					}
				}
				//-----------------------------------------------------------------------------
			}
		}
		else if( selectCount < this->judgements.frontCardSum )
		{
			
			temp = plcards[selectNumber].GetCardNumber();
			for(int j=0; j<2; j++)
			{
				for(int i=(j==0 ? selectNumber - 1 : selectNumber + 1);
							(j==0 ? i>=0 : i<siz); (j==0 ? i-- : i++ ) )
				{
					if( plcards[i].GetCardStatus() != CARD_STATUS_DES &&
						temp == plcards[i].GetCardNumber() )
							plcards[i].onSelectOK();
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//場に階段が成立している時の関数
	void GameScene::throwJudgement_bystairs(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size(), count, temp, temp2, lissize, joCnt = jockerCnt, typeTemp = 0;
		int judcard = 0;
		std::vector<int> lis;

		judcard = ( !this->judgements.isRevolution() ? 
						this->judgements.frontCard[this->judgements.nowCard].GetCardNumber() :
			this->judgements.frontCard[this->judgements.nowCard + this->judgements.frontCardSum - 1].GetCardNumber() );

		//選択しているものがなかったら
		if( selectNumber == -1 )
		{
			for(int i=0; i<siz; i++)
			{
				if( plcards[i].GetCardStatus() == CARD_STATUS_DES  ||
					plcards[i].isJocker() )
					continue;
				
				//------------------------------------------------------------------
				//縛りルール採用
				if( this->judgements.isRestrains() &&
					this->judgements.restrainsType[0] != plcards[i].GetCardType() )
					continue;
				//------------------------------------------------------------------

				temp = plcards[i].GetCardNumber();
				joCnt = jockerCnt;
				if( this->judgements.isRevolution() ?  
					CHECK_TRUMP_BIGGER( judcard, temp) : CHECK_TRUMP_SMALLER( judcard, temp ) )
				{
					count = 0;
					typeTemp = plcards[i].GetCardType();
					for(int j=i+1;j<siz;j++)
					{
						temp2 = plcards[j].GetCardNumber();
						if( plcards[j].GetCardStatus() == CARD_STATUS_DES )
							continue;
						if( this->judgements.isRevolution() ?  
							CHECK_TRUMP_BIGGER( judcard, temp2) : CHECK_TRUMP_SMALLER( judcard, temp2 ) &&
							CHECK_TRUMP_BIGGER( temp, temp2 ) &&
							typeTemp == plcards[j].GetCardType() )
						{
							if( abs( TRUMP_POWER[temp2] - TRUMP_POWER[temp]) == 1 )
							{
								count++;
								lis.push_back(j);
								temp = plcards[j].GetCardNumber();
							}
							else if(joCnt > 0 && 
									abs( TRUMP_POWER[temp2] - TRUMP_POWER[temp]) == 2 )
							{
								count++;
								lis.push_back(j);
								temp = plcards[j].GetCardNumber();
								joCnt--;
							}
							
						}
						if( count + jockerCnt + 1 >= this->judgements.frontCardSum )
							break;
					}

					if( (count + jockerCnt + 1 == this->judgements.frontCardSum) ||
						(count + jockerCnt + 1 == this->judgements.frontCardSum) )
					{
						lissize = lis.size();
						plcards[i].onSelectOK();
						for(int j=0;j<lissize;j++)
							plcards[lis[j]].onSelectOK();
					}
					lis.clear();
				}
			}
		}
		//選択しているものがあったら
		else
		{
			count = 0;
			typeTemp = plcards[selectNumber].GetCardType();
			for(int j=0, left = 0; j<2; j++)
			{
				temp = plcards[selectNumber].GetCardNumber(); 
				joCnt = jockerCnt;
				count = 0;
				for(int i=(j == 0 ? selectNumber - 1 : selectNumber + 1); 
						(j == 0 ? i>=0 : i<siz); (j == 0 ? i-- : i++ ) )
				{
					if( (this->judgements.isRevolution() ? 
						CHECK_TRUMP_BIGGER( judcard, plcards[i].GetCardNumber() ) :
						CHECK_TRUMP_SMALLER( judcard, plcards[i].GetCardNumber() ) ) &&
						
						(j == 0 ? CHECK_TRUMP_BIGGER( plcards[i].GetCardNumber(), temp) :
						CHECK_TRUMP_SMALLER( plcards[i].GetCardNumber(), temp) ) &&

						typeTemp == plcards[i].GetCardType() )
					{
						if( abs( TRUMP_POWER[temp] - TRUMP_POWER[plcards[i].GetCardNumber()]) != 1 )
						{
							if( abs( TRUMP_POWER[temp] - TRUMP_POWER[plcards[i].GetCardNumber()]) == 2 &&
								joCnt > 0 )
								joCnt--;
							else
								continue;
						}

						count++;
						lis.push_back(i);
						temp = plcards[i].GetCardNumber();
					}

					if( count + selectCount >= this->judgements.frontCardSum )
						break;
				}

				if( count + selectCount == this->judgements.frontCardSum )
				{
					lissize = lis.size();
					plcards[selectNumber].onSelectOK();
					for(int j=0;j<lissize;j++)
						plcards[lis[j]].onSelectOK();
				}
				lis.clear();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//縛りルール採用時に呼ばれる
	bool GameScene::check_resTrains( CARD_TYPE type, std::vector<int>& typeList)
	{
		bool hantei = false, hantei2 = false;
		//----------------------------------------------------------------
		//縛りルール採用時に縛られたとき
		if( this->judgements.isRestrains() &&
			!this->judgements.restrainsType.empty() )
		{
			//あらかじめタイプリストを用意しているので、
			//そのリストで調査し、あったら通りましょう！
			for(int j=0, tysize=this->judgements.restrainsType.size();
				j<tysize; j++)
			{
				//----------------------------------------------
				if( this->judgements.restrainsType[j] == type )
				{
					if( !typeList.empty() )
					{
						for(int k=0, tysiz=typeList.size(); 
							k<tysiz; k++)
						{
							if( typeList[k] == j)
								break;
						}
					}

					hantei = true;
					typeList.push_back(j);
					break;
				}
				//----------------------------------------------
			}
		}
		else
			return true;
		return hantei;
	}

	//縛りルール採用時にジョーカーがあったら、マークの変更をする
	void GameScene::changeJocker_resTrains(std::vector<TrumpCard>& judCard, int jockerCnt)
	{
		std::vector<int> resType;
		for(int i=judCard.size() - 1; i>=0; i--)
		{
			if( !this->check_resTrains( judCard[i].GetCardType(), resType ) &&
				judCard[i].isJocker() )
			{
				for( int k=0, okf = 0, kres = this->judgements.restrainsType.size() ; k<kres; k++)
				{
					for(int j=0, resSize = resType.size(); j<resSize; j++)
					{
						if( resType[j] != this->judgements.restrainsType[k] )
						{
							judCard[i].SetCardNumber( judCard[jockerCnt].GetCardNumber(), 
								this->judgements.restrainsType[ k ] );
							resType.push_back( k );
							okf = 1;
							break;
						}
					}
					if(okf > 0 )	break;
				}
			}
		}
	}
}