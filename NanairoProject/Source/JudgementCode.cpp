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

	//�J�[�h���o��
	bool GameScene::throwPlayerCard_inJudgmentCard(std::vector<TrumpCard>& plcards)
	{
		bool isSort = false, check = false, isRes = false, isFrontEffect = false;
		int siz = plcards.size(), count = 0, sametemp = 0, jockerCnt = 0, startCnt = 0, 
			resSize = this->judgements.restrainsType.size();

		//------------------------------------------------------------
		//�����`�F�b�N
		if( !this->throwPlayerCard_inJudgmentCard_sameSum( plcards ) )
			return false;
		//------------------------------------------------------------

		std::vector<TrumpCard>	checkTrump;
		std::vector<int>		tempNumber, lis;
		count = 0;
		startCnt = this->judgements.frontCardSum;
		//��x�i�[���悤�B
		for(int i=0; i<siz; i++)
		{
			//�N���b�N��Ԃ̂��
			if(plcards[i].GetMouseTouch() == CARD_TOUCHSTATUS_CLICK &&
				plcards[i].GetCardStatus() != CARD_STATUS_DES )
			{
				//�o���閇������������J�E���g
				//�Q���o�����[�h�`�F���W
				( plcards[i].isJocker() ? jockerCnt++ : count++ );

				//�Ƃ肠�����J�[�h�ƓY�������i�[
				checkTrump.push_back( plcards[i] );
				tempNumber.push_back( i );
			}
		}

		//--------------------------------------------------------------------------
		//�����ă`�F�b�N
		if( !this->throwPlayerCard_inJudgmentCard_check( checkTrump, tempNumber ) )
			return false;
		//--------------------------------------------------------------------------
		
		siz = tempNumber.size();
		//-----------------------------------------------------------
		//�Y�����ړ�
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
		//�J�[�h�̊i�[
		int nowMax = siz;
		for(int i=0; i<siz; i++)
		{
			//�i�[
			checkTrump[i].offSelectOK();
			plcards[ tempNumber[i] ].offSelectOK();
			this->judgements.frontCard.push_back( checkTrump[i] );
			this->judgements.frontCard[this->judgements.frontCard.size() - 1].SetCenterMove(i, siz );
			this->judgements.frontCard[this->judgements.frontCard.size() - 1].parts.color.SetMaxColor();
			plcards[ tempNumber[i] ].ChangeDraw( CARD_STATUS_DES );

			
			//-------------------------------------------------
			//�g�����v�ԍ����u�W�v�̏ꍇ�A8���蔭���I
			if( checkTrump[i].GetCardNumber() == 7 )
				this->judgements.changeEightcut( true );
			//�g�����v�ԍ����u11�v�̏ꍇ�A�C���u���o�b�N�����I
			else if( !isFrontEffect && this->judgements.isUseElevenback() && checkTrump[i].GetCardNumber() == 10 )
			{
				this->judgements.changeElevenback( !this->judgements.isElevenback() );
				( this->judgements.isElevenback() ? 
					this->judgements.plateList.Push( TRUMP_RULE_ELEVENBACK ) : 
					this->judgements.plateList.Pop( TRUMP_RULE_ELEVENBACK ) );
				this->judgements.push_ruleEffect( TRUMP_RULE_ELEVENBACK );
				isFrontEffect = true;
			}
			//�g�����v���u�W���[�J�[�v�̏ꍇ�A�W���[�J�[�~��
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
			//�g�����v�ԍ����u�X�y�[�h�̂R�v�̏ꍇ�A�W���[�J�[�̂ݏ�ɏo�Ă���X�y�R�Ԃ������I
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
			//����`�F�b�N
			if( this->judgements.isUseRestrains() ) 
			{
				CARD_TYPE ty = checkTrump[i].GetCardType();
				if( startCnt == 0 )
					this->judgements.restrainsType.push_back( ty );
				else if( !this->judgements.isRestrains() )
				{
					//-------------------------------------------------
					//�����^�C�v��T��
					bool checker = false;
					for(int j=0; j<resSize; j++)
					{
						if( ty == this->judgements.restrainsType[j])
						{
							//-------------------------------------------------
							//����Ă��Ȃ����T��
							checker = false;
							for(int k=0, liss = lis.size(); k<liss; k++)
							{
								if( lis[k] == j )
								{
									//����Ă�OUT!�������T���I
									checker = true;
									break;
								}
							}
							if(!checker)	//����Ă��Ȃ��Ȃ�I���I
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
		//�����}�[�N����������������
		if( this->judgements.isUseRestrains() )
		{
			if( lis.size() == this->judgements.frontCardSum )
			{	//���肫����
				this->judgements.changeRestrains( true );
				this->judgements.push_ruleEffect( TRUMP_RULE_RESTRAINS );
			}
			else
			{
				//���肱�Ȃ�������A���̃J�[�h�̎�ނɓ���ւ��܂��傤�I
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
	//�J�[�h�`�F�b�N
	void GameScene::throwJudgement(std::vector<TrumpCard>& plcards)
	{
		bool same_or_stairs = false;
		int siz = plcards.size(), temp = -1, count = 0, sametemp, jockerCnt = 0, use_jocker = 0;
		for(int i=0; i<siz; i++)
			plcards[i].offSelectOK();

		//�W���[�J�[�o���ꂽ��ɃX�y�R�Ԃ����ꂽ���΂�
		if( this->judgements.isSpade3() &&
			this->judgements.frontCard[this->judgements.nowCard - 1].isJocker() &&
			this->judgements.frontCard[this->judgements.nowCard].GetCardNumber() == 2 )
			return ;
		
		//�܂��I�����Ă���̂�T����
		for(int i=0; i<siz; i++)
		{
			//�g�p�ς݃J�[�h�͔�΂�
			if( plcards[i].GetCardStatus() == CARD_STATUS_DES )
				continue;

			//�N���b�N�����J�[�h��T��
			if( plcards[i].GetMouseTouch() == CARD_TOUCHSTATUS_CLICK )
			{
				plcards[i].onSelectOK();
				( plcards[i].isJocker() ? jockerCnt++ : count++ );
				
				//�I���J�[�h�Q���ڂŕ����o�����K�i���`�F�b�N
				if( count == 2 )
				{
					same_or_stairs = ( plcards[i].GetCardNumber() == sametemp );
					
					if( !same_or_stairs && jockerCnt == 1)
						use_jocker++;
				}
				//�I���J�[�h�P���ڋL�^
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
		//�����o���{�����J�[�h�Ȃ�
		if( this->judgements.isSame() )
		{
			this->throwJudgement_bysame( plcards, temp, count, jockerCnt,
				same_or_stairs );
		}
		//�����o���{�K�i�Ȃ�
		else if( this->judgements.isStairs() )
		{
			this->throwJudgement_bystairs( plcards, temp, count, jockerCnt,
				same_or_stairs );
		}
		//���̃��[���Ȃ��Ȃ�
		else if( !this->judgements.isSpade3() )
		{
			this->throwJudgement_byno( plcards, temp, count, jockerCnt,
				same_or_stairs );
		}
	}
	
	//��ɕ��ʂȃJ�[�h���o����Ă��鎞�̊֐�
	void GameScene::throwJudgement_byno(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size();
		//�W���b�W��Ȃ�
		if( this->judgements.frontCard.empty() )
		{
			//�I�����Ă�����̂��Ȃ�������
			if( selectNumber == -1 )
			{
				for(int i=0; i<siz; i++)
				{
					if( !plcards[i].isCardDes() )
						plcards[i].onSelectOK();
				}
			}
			//�I�����Ă�����̂���������
			else
			{
				//�������̂𕡐��I�����Ă��邩�A�P���I�����Ă�����
				this->throwJudgement_byno_selectSame( plcards, selectNumber, selectCount, jockerCnt, same_or_stairs );
				this->throwJudgement_byno_selectStairs( plcards, selectNumber, selectCount, jockerCnt, same_or_stairs );
			}
		}
		//�W���b�W�����Ă����
		else if( selectCount + jockerCnt != this->judgements.frontCardSum )
			this->throwJudgement_byno_selecting( plcards, selectNumber, selectCount, jockerCnt, same_or_stairs );

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�������̂𕡐��I�����Ă��邩�A�P���I�����Ă�����
	void GameScene::throwJudgement_byno_selectSame(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int count = 0, siz = plcards.size();
		//�������̂𕡐��I�����Ă��邩�A�P���I�����Ă�����
		if( (selectCount - jockerCnt > 1 && same_or_stairs) || selectCount - jockerCnt == 1 )
		{
			count = 0;
			for(int i=0; i<siz; i++ )
			{	
				//------------------------------------------------------
				//�I�𒆁A�g�p�ς݂͔�΂�
				if( plcards[i].isCardER() )		continue;
				//------------------------------------------------------

				//------------------------------------------------------
				//�I�𒆂̃J�[�h�ƒT���J�[�h�̔ԍ����ꏏ�Ȃ�
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

	//�K�i�I�����Ă��邩�A�P���I�����Ă�����
	void GameScene::throwJudgement_byno_selectStairs(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int count = 0, siz = plcards.size(), temp = 0, jockerDown = jockerCnt,type = 0, sub = 0;
		std::vector<int> lis;
		//�K�i�I�����Ă��邩�A�P���I�����Ă�����
		if( (selectCount - jockerCnt > 1 && !same_or_stairs) || selectCount - jockerCnt == 1 )
		{
			count = 0;
			for(int j=0, left = 0, right = 0; j<2; j++)
			{
				//-------------------------------------------------------
				//�I�����Ă���f�[�^�̔ԍ��ۑ�
				temp = plcards[selectNumber].GetCardNumber(); 
				type = plcards[selectNumber].GetCardType();
				jockerDown = jockerCnt;
				//-------------------------------------------------------
				for(int i=(j == 0 ? selectNumber - 1 : selectNumber + 1), cnt = 0; 
						(j == 0 ? i>=0 : i<siz) && cnt + selectCount <= 3; (j == 0 ? i-- : i++ ) )
				{
					//�g�p�ς݂͓��R��΂�
					if( plcards[i].isCardDes() )	
						continue;

					//-------------------------------------------------------
					//�Y�����ԍ��̃f�[�^��ۑ�
					left = plcards[i].GetCardNumber();
					right = plcards[i].GetCardType();
					//-------------------------------------------------------

					//-------------------------------------------------------
					//�J�[�h�̐�Βl�̍����P�ȏ�A��������ނ̃J�[�h�Ȃ�
					sub = abs( TRUMP_POWER[temp] - TRUMP_POWER[left] );
					if( sub != 0 && sub > 1  && type == right )
					{
						for(int k=0; k<sub-1;k++)
							jockerDown--;
						//�W���[�J�[������Α��v�I�ʂ��܂��傤
						if( jockerDown < 0 )
							break;
					}
					//-------------------------------------------------------

					//-------------------------------------------------------
					//�I������Ă���Ȃ�ۑ����悤����
					if( plcards[i].GetSelectOK() && 
						sub != 0 )
					{
						temp = left;
						continue;
					}	
					//-------------------------------------------------------

					//-------------------------------------------------------
					//�傫���A���͊v�����������̂Ȃ�
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
			//�K�i�Q�����ᐬ�����܂�����
			if( count + selectCount < 3 )
			{
				for(int i=0; i<siz; i++)
					plcards[lis[i]].offSelectOK();
			}
			//--------------------------------------
		}
	}

	//�����o����Ă��Ȃ��A�I������Ă��Ȃ��A
	void GameScene::throwJudgement_byno_selecting(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size();
		//�W���b�W�J�[�h���傫����̂ݑI��OK�I
		for(int i=0; i<siz; i++)
		{	
			//----------------------------------------------------------------------
			//�g�p�ς݁A�I���ł����͔�΂��I
			if( plcards[i].isCardER() )		
				continue;
			//----------------------------------------------------------------------

			//----------------------------------------------------------------------
			//�W���[�J�[�P���o����Ă����
			if( this->judgements.frontCard[ this->judgements.nowCard ].isJocker() )
			{
				//�X�y�[�h�́u�R�v�̂ݑI���\
				if( plcards[i].GetCardNumber() == 2 && 
					plcards[i].GetCardType() == CARD_SPADE )
					plcards[i].onSelectOK();
				continue;
			}
			//----------------------------------------------------------------------

			//----------------------------------------------------------------------
			//�ʏ팟��
			if( ( this->judgements.isRevolution() ? 
				CHECK_TRUMP_BIGGER(this->judgements.frontCard[ this->judgements.nowCard ].GetCardNumber(),
								plcards[i].GetCardNumber() ) : 
				CHECK_TRUMP_SMALLER(this->judgements.frontCard[ this->judgements.nowCard ].GetCardNumber(),
								plcards[i].GetCardNumber() ) ) )
			{
				//------------------------------------------------------------------------------------------------------
				//���胋�[���K�p�̍ہA�����}�[�N��������OK�ł��B
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

	//��ɓ����J�[�h�������o����Ă��鎞�̊֐�
	void GameScene::throwJudgement_bysame(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size(), count, temp, joCnt;
		CARD_TYPE type;
		std::vector<int> typeList;
		if( this->judgements.frontCardSum == 2 &&
			jockerCnt == 2 )
			return ;

		//�W���[�J�[�h�~
		int judcard = ( this->judgements.frontCard[this->judgements.nowCard].isJocker() ?
						this->judgements.frontCard[this->judgements.nowCard + 1].GetCardNumber() :
						this->judgements.frontCard[this->judgements.nowCard].GetCardNumber() );
		if( selectCount - jockerCnt <= 0 )
		{
			for(int i=0; i<siz; i++)
			{
				//�g�p�ς݂͔�΂�
				if( plcards[i].GetCardStatus() == CARD_STATUS_DES )
					continue;

				temp = plcards[i].GetCardNumber();
				type = plcards[i].GetCardType();
				typeList.clear();
				//-----------------------------------------------------------------------------
				//�傫���J�[�h���A���͊v�����������J�[�h��
				if( this->judgements.isRevolution() ? 
					CHECK_TRUMP_BIGGER( judcard, temp) : CHECK_TRUMP_SMALLER( judcard, temp) )
				{
					//���胋�[���̗p���ɌĂ΂��
					if( !this->check_resTrains( type, typeList ) )
						continue;

					//--------------------------------------------------
					//�ׂ�H���ē����J�[�h�����J�E���g���܂�
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
					//�J�E���g�����ƈꏏ�Ȃ�Z���N�g�I
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

	//��ɊK�i���������Ă��鎞�̊֐�
	void GameScene::throwJudgement_bystairs(std::vector<TrumpCard>& plcards, int selectNumber, int selectCount, int jockerCnt, bool same_or_stairs)
	{
		int siz = plcards.size(), count, temp, temp2, lissize, joCnt = jockerCnt, typeTemp = 0;
		int judcard = 0;
		std::vector<int> lis;

		judcard = ( !this->judgements.isRevolution() ? 
						this->judgements.frontCard[this->judgements.nowCard].GetCardNumber() :
			this->judgements.frontCard[this->judgements.nowCard + this->judgements.frontCardSum - 1].GetCardNumber() );

		//�I�����Ă�����̂��Ȃ�������
		if( selectNumber == -1 )
		{
			for(int i=0; i<siz; i++)
			{
				if( plcards[i].GetCardStatus() == CARD_STATUS_DES  ||
					plcards[i].isJocker() )
					continue;
				
				//------------------------------------------------------------------
				//���胋�[���̗p
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
		//�I�����Ă�����̂���������
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

	//���胋�[���̗p���ɌĂ΂��
	bool GameScene::check_resTrains( CARD_TYPE type, std::vector<int>& typeList)
	{
		bool hantei = false, hantei2 = false;
		//----------------------------------------------------------------
		//���胋�[���̗p���ɔ���ꂽ�Ƃ�
		if( this->judgements.isRestrains() &&
			!this->judgements.restrainsType.empty() )
		{
			//���炩���߃^�C�v���X�g��p�ӂ��Ă���̂ŁA
			//���̃��X�g�Œ������A��������ʂ�܂��傤�I
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

	//���胋�[���̗p���ɃW���[�J�[����������A�}�[�N�̕ύX������
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