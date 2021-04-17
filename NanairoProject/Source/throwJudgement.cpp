#pragma once

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//�K�i�́u�R�S�W���[�J�[�v�A�u�W���[�J�[�P�Q�v�͊m��ł���I
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

	//�����̃J�[�h�`�F�b�N
	bool GameScene::throwPlayerCard_inJudgmentCard_check(std::vector<TrumpCard>& judCard, std::vector<int>& sej )
	{
		bool jockerFlag = false, hantei = false, same_or_stairs = false, kakutei = false;
		int siz = judCard.size(), count = 0, jockerCnt = 0, temp = 0, stairs = 0;
		TrumpCard tempCard;

		for(int i=0; i<siz; i++)
		{
			//�o���閇������������J�E���g
			//�Q���o�����[�h�`�F���W
			( (jockerFlag = judCard[i].isJocker()) ? jockerCnt++ : count++ );

			if( count == 1 )
				temp = judCard[i].GetCardNumber();
			else if( count == 2 )
			{
				//--------------------------------------------------
				//�J�[�h�������������ꍇ
				if ( this->judgement_same( judCard, temp, i, jockerCnt ) )
				{
					same_or_stairs = hantei = true;
					break;
				}
				//--------------------------------------------------
				//�Ⴄ�J�[�h�������ꍇ
				else
				{
					stairs = abs( TRUMP_POWER[judCard[i-1].GetCardNumber()] - 
							TRUMP_POWER[judCard[i].GetCardNumber()] );
					switch( jockerCnt )
					{
					case 0:	//J�O�{S�Q
						//�����P���J�[�h���Ȃ���OUT
						if( count + jockerCnt <= 2 || stairs != 1)
						{
							//3456�̂S���̃J�[�h�Ȃǂ������ꍇ
							if( judCard.size() < 3 || stairs != 1 )
								return false;
						}
						break;
					case 1:	//J�P�{S�Q�{���Ƃ����P���J�[�h������B
						switch( stairs )
						{
						case 1:	//�����P�̏ꍇ�A�ׂ��킹�ɂȂ�B
							//---------------------------------------------------------------
							//���̃J�[�h������ꍇ
							//���̃J�[�h�Ƃ̍����R�ȏ��OUT!!
							if( i+1 == siz-1 ) 
							{
								if( abs( judCard[i].GetTrumpNumber() - 
										judCard[i+1].GetTrumpNumber() ) >= 3 )
										return false;
								kakutei = check_34_12( judCard, i+1, jockerCnt + 1 );
							}
							else	//�Ȃ������� 
								//�����ŁA\34��34\ \12��K12
								kakutei = check_34_12( judCard, i, jockerCnt );
							
							//---------------------------------------------------------------
							break;
						case 2://�����Q�̏ꍇ�A�Ԃɗ��邱�ƑO��
							//---------------------------------------------------------------
							//���̃J�[�h������ꍇ
							if( i+1 == siz-1 ) 
							{	//���̃J�[�h�Ƃ̂����P�Ȃ�OK!
								if( abs( judCard[i].GetTrumpNumber() - judCard[i+1].GetTrumpNumber() ) != 1 )
										return false;
							}
							else
							{	//���̃J�[�h���Ȃ��̂ŊԂɗ��邱�Ɗm��I
								judCard[0].SetCardNumber( judCard[1].GetCardNumber() );
								judCard[1].SetCardNumber( judCard[1].GetCardNumber() - 1 );
								kakutei = true;
							}
							//---------------------------------------------------------------
							break;
						default: //�����R�ȏ��OUT
							return false;
						}
						break;
					case 2:	//J�Q�{S�Q����ł��ׂ�
						//-------------------------------
						//���̃J�[�h����������
						//�����S�ȏゾ��OUT!
						if( count + jockerCnt != 4 || stairs >= 4 )
							return false;
						//-------------------------------
						else	
						{
							switch( stairs )
							{
								case 1:	//�����ŁA\\34��34\\ \\12��QK12
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
								case 3:	//�R�̏ꍇ�͂Q���̃W���[�J�[���Ԃɂ��邱�Ɗm��I
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

	//���x�͏o���Ă���J�[�h�`�F�b�N
	bool GameScene::throwPlayerCard_inJudgmentCard_checkOut(std::vector<TrumpCard>& judCard, int count, int jockerCnt, int temp, bool hantei, bool kakutei, bool same_or_stairs)
	{
		int siz = judCard.size();
		//��ɃJ�[�h���Ȃ��ꍇ
		if( this->judgements.frontCard.empty() )
		{
			//------------------------------------------------------------
			//�W���[�J�[�ȊO�������O�`�P�̏ꍇ�̂�
			switch( count )
			{
				case 0:
					//---------------------------------------------------
					//�W���[�J�[�Q�������œ����J�[�h�o�������Ƃ�
					if( jockerCnt > 1 && !kakutei )	
						this->judgements.changeSame( true );
					hantei = true;
					//---------------------------------------------------
					break;
				case 1:
					//---------------------------------------------------
					//�W���[�J�[�����P���ł�����A���̃J�[�h���P���Ȃ��
					if( jockerCnt > 0 )
					{
						//�W���[�J�[�����P���Ȃ瓯���J�[�h��
						if( jockerCnt > 0 )
						{
							//�����J�[�h�ɂ����Ȃ�Ȃ�
							for( int j=0; j<jockerCnt; j++ )
								judCard[j].SetCardNumber( judCard[jockerCnt].GetCardNumber(),
															judCard[jockerCnt].GetCardType() );
							this->judgements.changeSame( true );
						}
						//����ȊO�͊K�i
						else{}
					}
					//---------------------------------------------------
					hantei = true;
					break;
				case 2:	//�Q���������ꍇ,�������������͊K�i�i�W���[�J�[����j�ł��B
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
								//�v�����͑I�񂾃J�[�h�̉����l�[�P�ɂ���
								if( this->judgements.isRevolution() )
								{
									for(int j=0; j<2; j++)
										judCard[j].SetCardNumber( judCard[j+1].GetCardNumber() );
									judCard[2].SetCardNumber( judCard[2].GetCardNumber() - 1 );
								}
								//����ȊO�͑I�񂾃J�[�h�̏���l�{�P�ɂ���
								else
									judCard[0].SetCardNumber( judCard[1].GetCardNumber() + 1 );
								this->judgements.changeStairs( true );
								this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );
								hantei = true;
								break;
							case 2:
								//--------------------------------------------------------------------------
								//�ԂɃW���[�J�[������ꍇ
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
									//�v�����͑I�񂾃J�[�h�̉����l�[�P�ɂ���
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
									//����ȊO�͑I�񂾃J�[�h�̏���l�{�P�ɂ���
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
				case 3:	//�R���������ꍇ�A�c��̓W���[�J�[�P���̉\������
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
						//�ԂɃW���[�J�[������ꍇ
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

						//�ׂ��킹�̏ꍇ
						//--------------------------------------------------------------------------
						if( !kakutei )
						{
							//�v�����͑I�񂾃J�[�h�̉����l�[�P�ɂ���
							if( this->judgements.isRevolution() )
							{
								for(int j=0; j<3; j++)
									judCard[j].SetCardNumber( judCard[j+1].GetCardNumber() );
								judCard[3].SetCardNumber( judCard[3].GetCardNumber() - 1 );
							}
							//����ȊO�͑I�񂾃J�[�h�̏���l�{�P�ɂ���
							else
								judCard[0].SetCardNumber( judCard[1].GetCardNumber() + 1 );
						}
						//--------------------------------------------------------------------------

						this->judgements.changeStairs( true );
						this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );
					}
					hantei = true;
					break;
				case 4:	//�W���[�J�[�͂Ȃ����Ƃ��킩��B
					(same_or_stairs ? this->judgements.changeSame( true ) : this->judgements.changeStairs( true ) );
					if( !same_or_stairs )	this->judgements.push_ruleEffect( TRUMP_RULE_STAIRS );

					//����Ɋv�������
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

			//�����J�[�h�o���͂ق��̏ꏊ�ňꏏ�ɂ��܂��B
			if( !hantei || !kakutei )
			{
				//�K�i�����̂Ƃ�,�ʏ�P���{�W���[�J�[�Q���̎�������
				if( this->judgements.isStairs() )
					hantei = this->judgement_bystairs_onecard( judCard, count, jockerCnt );
				//�W���[�J�[�Q���o��
				else if( this->judgement_bysame_twoJocker( judCard, count, jockerCnt ) )
					return true;
				//�P���o���̎�
				else if( !hantei )
					hantei = this->judgement_byno_onfront( judCard, count, jockerCnt );
			}
		}
		return hantei;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//�J�[�h�̖����`�F�b�N
	bool GameScene::throwPlayerCard_inJudgmentCard_sameSum(std::vector<TrumpCard>& plcards)
	{
		int siz = plcards.size(), count = 0;
		//-------------------------------------------------------------------
		//�J�[�h�̖����������ĂȂ��ƃA�E�g
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

	//�����J�[�h���Q���o����Ă��鎞�ɃW���[�J�[�Q���o��
	bool GameScene::judgement_bysame_twoJocker(std::vector<TrumpCard>& judCard,int count, int jockerCnt)
	{
		return ( count == 0 && jockerCnt == 2 &&
			this->judgements.isSame() );
	}

	//�������̂��o�����̃`�F�b�N�֐�
	bool GameScene::judgement_same(std::vector<TrumpCard>& judCard,int temp, int i, int jockerCnt)
	{
		bool hantei = false;
		int ftemp = 0;
		if( temp == judCard[i].GetCardNumber() )
		{
			//�����o����Ă��Ȃ��Ȃ疳������OK!
			if( judgements.frontCard.empty() )
				hantei = true;
			else
			{
				//-------------------------------------------------------------------
				//�W���[�J�[���Ɩ����I
				if( this->judgements.frontCard[this->judgements.nowCard].isJocker() )
					return false;
				//-------------------------------------------------------------------

				ftemp = this->judgements.frontCard[this->judgements.nowCard].GetCardNumber();
				if( this->judgements.isRevolution() ? 
					CHECK_TRUMP_BIGGER( ftemp, temp ) : CHECK_TRUMP_SMALLER( ftemp, temp ) )	
					hantei = true;
			}

			//����������
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

	//��ɃJ�[�h������ꍇ�A�����ĂP�������J�[�h���o����Ă��Ȃ��ꍇ
	bool GameScene::judgement_byno_onfront(std::vector<TrumpCard>& judCard,int count, int jockerCnt)
	{
		int temp = 0;

		//--------------------------
		//�W���[�J�[�I�𒆂���
		if( jockerCnt == 1 && count == 0 )
			return true;
		//--------------------------
		else if( count == 1 )
		{
			//----------------------------------------------------------------------
			//�W���[�J�[���\�ɏo����Ă�����
			if( this->judgements.frontCard[ this->judgements.nowCard ].isJocker() )
			{
				//�X�y�[�h�R�Ԃ��̂���
				if( judCard[0].GetCardNumber() == 2 &&
					judCard[0].GetCardType() == CARD_SPADE )
					return true;
			}
			//----------------------------------------------------------------------
			else
			{
				//----------------------------------------------------------------------
				//�X�y�R�Ԃ��͉����J�[�h�o���Ȃ�
				if( this->judgements.isSpade3() )
					return false;
				//----------------------------------------------------------------------
				else
				{
					temp = this->judgements.frontCard[ this->judgements.nowCard ].GetCardNumber();

					//-------------------------------------------------------------------
					//���胋�[���̗p���A�����}�[�N�̎�ނ���Ȃ���OUT�I
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
					//��͌���ׂđ傫�������A���͊v���������������Ȃ�OK!
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

	//�K�i�����̂Ƃ�,�ʏ�P���{�W���[�J�[�Q���̎�������
	//�K�i�����̂Ƃ�,�ʏ�Q���{�W���[�J�[�P���̎�������
	bool GameScene::judgement_bystairs_onecard(std::vector<TrumpCard>& judCard,int count, int jockerCnt)
	{
		int type = judCard[2].GetCardType();
		switch( judCard[2].GetCardNumber() )
		{
		case 0:	//A�̂Ƃ�
		case 1:
		case 12:
			judCard[0].SetCardNumber(1, type );
			judCard[1].SetCardNumber(0, type );
			judCard[2].SetCardNumber(12, type );
			return true;
		case 2:	//3�̂Ƃ�
		case 3:	//4�̂Ƃ�
		case 4:	//5�̂Ƃ�
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