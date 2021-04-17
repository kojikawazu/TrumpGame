#pragma once

////////////////////////////////////
//NanairoLib
////////////////////////////////////
#include <MainFunction.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <PE_the_matchScene.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//---------------------------------------------------------------------------------------------------------------
	//Init
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::Init()
	{
		this->parts.pos.SetPercentVector( 0.5f, 0.5f );
		this->parts.ang = 0.0f;
		this->parts.scale.SetVector( 0.0f, SCRH_PERCENT(0.9f) );
		this->offSet.SetVector( SCRW_PERCENT(0.9f), 0.0f );
		this->parts.color.SetMaxColor();
		this->parts.color.SettingFadeAlpha();
		this->offSetScale.SetMinVector();
		

		this->Action = &ScoreMap::wait;
		this->ScaleAction = &ScoreMap::scaleFadeIn;

		this->Input_mapTag();
		this->Input_mapPlateTag();
		this->Input_arrowTag();
		this->Input_scoreNumberTag();
		this->Input_playerTag();
		this->Input_bigTag();
		this->Input_scoreTag();
		this->Input_updownTag();
	}

	void ScoreMap::Input_playerTag()
	{
		this->playerTag = new PlayerPlate();
		this->playerTag->SetAng( this->parts.ang );
		this->playerTag->SetNameColor( GetMaxColor() );
	}

	void ScoreMap::Input_scoreNumberTag()
	{
		this->runkNumberTag = new NumbersWord();
		this->runkNumberTag->SetAng( this->parts.ang );
		this->runkNumberTag->SetColor( GetMaxColor() );
	}

	void ScoreMap::Input_arrowTag()
	{
		this->arrowTag = new NameDialog();
		this->arrowTag->SetDialogName( "yajirusi" );
	}

	void ScoreMap::Input_mapTag()
	{
		this->mapTag = new NameDialog();
		this->mapTag->SetScl( this->parts.scale );
		this->mapTag->SetPos( this->parts.pos );
		this->mapTag->SetAng( this->parts.ang );
		this->mapTag->SetDialogName( "map" );
	}

	void ScoreMap::Input_mapPlateTag()
	{
		this->mapPlateTag = new NameDialog();
		this->mapPlateTag->SetPos( this->parts.pos );
		this->mapPlateTag->SetAng( this->parts.ang );
		this->mapPlateTag->SetScl( this->parts.scale );
		this->mapPlateTag->SetNameColor( this->parts.color.color );
		this->mapPlateTag->SetDialogName("scorePlate");
	}

	void ScoreMap::Input_bigTag()
	{
		this->bigTag = new NameDialog();
		this->bigTag->SetAng ( this->parts.ang );
		this->bigTag->SetDialogName("bigger");
		this->bigTag->SetNameColor( this->parts.color.color );
	}

	void ScoreMap::Input_scoreTag()
	{
		this->scoreTag = new NumbersWord();
		this->scoreTag->SetColor( Vector4( this->parts.color.color.x, 0,0,0) );
	}

	void ScoreMap::Input_updownTag()
	{
		this->updownTag = new NameDialog();
		this->updownTag->SetAng(this->parts.ang);
		this->updownTag->SetNameColor( this->parts.color.color );
	}

	void ScoreMap::Dispose()
	{
		this->playerName.clear();
		this->score.clear();
		this->runk.clear();
		this->oldRunk.clear();
		this->oldScore.clear();

		ES_SAFE_DELETE( this->mapPlateTag );
		ES_SAFE_DELETE( this->mapTag );
		ES_SAFE_DELETE( this->scoreTag );
		ES_SAFE_DELETE( this->playerTag );
		ES_SAFE_DELETE( this->arrowTag );
		ES_SAFE_DELETE( this->scoreTag );
		ES_SAFE_DELETE( this->runkNumberTag );
		ES_SAFE_DELETE( this->bigTag );
		ES_SAFE_DELETE( this->updownTag );
	}

	void ScoreMap::scoreContinue()
	{
		this->offSetScale.SetMinVector();
		this->ScaleAction = &ScoreMap::scaleFadeIn;
	}

	//---------------------------------------------------------------------------------------------------------------
	//Setter
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::inScoreMap()
	{
		this->Action = &ScoreMap::fadeIn;
		this->scoreContinue();
	}

	void ScoreMap::outScoreMap()
	{
		this->Action = &ScoreMap::fadeOut;
		this->offSetScale.SetMinVector();
	}

	void ScoreMap::SetPlaySum(int sum)
	{
		this->score.resize( sum );
		this->oldScore.resize( sum );
		this->runk.resize( sum );
		this->oldRunk.resize( sum );

		for(int i=0, siz=this->score.size(); i<siz; i++)
		{
			this->score[i] = this->oldScore[i] = 0;
			this->runk[i] = i;
			this->oldRunk[i] = -1;
		}
	}

	void ScoreMap::SetPlayerName(std::vector<std::string>& str)
	{
		for(int i=0,siz=str.size(); i<siz; i++)
			this->playerName[i] = str[i];
	}

	//---------------------------------------------------------------------------------------------------------------
	//スコアマップのフェードイン
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::fadeIn()
	{
		if( this->parts.scale.x < this->offSet.x )
			this->parts.scale.x += 20.0f;

		if( this->parts.color.FadeIn(5.0f) )
			this->Action = &ScoreMap::buttonWait;
	}

	//---------------------------------------------------------------------------------------------------------------
	//スコアマップのフェードアウト
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::fadeOut()
	{
		if( this->parts.scale.x > 0.0f )
			this->parts.scale.x -= 40.0f;

		if( this->parts.color.FadeOut(5.0f) )	
			this->Action = &ScoreMap::wait;
	}

	//---------------------------------------------------------------------------------------------------------------
	//ギザギザのフェードイン
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::scaleFadeIn()
	{
		this->offSetScale.Add( OFFSET_SCALE_PLUS_SPDX, OFFSET_SCALE_PLUS_SPDY );

		if( this->offSetScale.x > 300.0f &&
			this->offSetScale.y > 200.0f )
			this->ScaleAction = &ScoreMap::scaleFadeOut;
	}

	//---------------------------------------------------------------------------------------------------------------
	//ギザギザのフェードアウト
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::scaleFadeOut()
	{
		this->offSetScale.Sub( OFFSET_SCALE_MANU_SPDX, OFFSET_SCALE_MANU_SPDY );

		if( this->offSetScale.x < 30.0f &&
			this->offSetScale.y < 20.0f )
			this->ScaleAction = &ScoreMap::scaleFadeIn;
	}

	//---------------------------------------------------------------------------------------------------------------
	//ランクによる評価を調整
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::judgeRunk(std::vector<int>& nowRunkList, int capitalSum, int foelSum)
	{
		std::vector<int> list( nowRunkList.size() ), ruk( nowRunkList.size() );
		//順位順に番号を指定されている。
		for(int i=0, siz=nowRunkList.size(); i<siz; i++)
		{
			//プレイヤー番号調査
			for(int j=0; j<siz; j++)
			{
				if( nowRunkList[i] == j )
				{
					switch( i )
					{
						case 0:	list[j] = SCORE_BIG_MILLIONAIRE;	break;
						case 1:	list[j] = SCORE_SMALL_MILLIONAIRE;	break;
						case 2:	list[j] = SCORE_SMALL_POOR;			break;
						case 3:	list[j] = SCORE_BIG_POOR;			break;
					}
					ruk[j] = i+1;
					break;
				}
			}
		}

		this->plusScore( ruk, list, capitalSum, foelSum );
	}

	//---------------------------------------------------------------------------------------------------------------
	//スコアの加算
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::plusScore(std::vector<int>& nowRunkList, std::vector<int>& dscore, int capitalSum, int foelSum)
	{
		for(int i=0, siz=dscore.size(); i<siz; i++)
		{
			this->oldRunk[i] = this->runk[i];
			this->oldScore[ this->runk[i] ] = this->score[i];
		}

		//プレイヤーi番目ルート
		int fouls = 0;
		for(int i=0, siz=dscore.size(); i<siz; i++)
		{
			//順位順に並んだ配列ルート
			for(int j=0; j<siz; j++)
			{
				if( this->runk[j] == i)
				{
					//○位のプレイヤーに加算
					this->score[j] += dscore[ i ];

					if( nowRunkList[i] == this->runk.size() && capitalSum > 0 )
						this->score[j] = (int)( this->score[j] * SCORE_CAPITALDOWN);
					else if( foelSum > 0  && foelSum > fouls && 
						i == nowRunkList[siz - capitalSum - foelSum + fouls] - 1 )
					{
						this->score[j] = (int)( this->score[j] * SCORE_FOEL);
						fouls++;
					}
					break;
				}
			}
		}

		this->Sort();
	}

	//---------------------------------------------------------------------------------------------------------------
	//スコアのソート
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::Sort(bool isUp)
	{
		int sum = 0, temp;
		for(int i=0, siz=this->score.size()-1; i<siz; i++)
		{
			sum = i;
			for(int j=i+1; j<siz+1; j++)
			{
				if( (isUp ? this->score[sum] > this->score[j] :  
							this->score[sum] < this->score[j] ) )
					sum = j;
			}

			if( sum != i )
			{
				temp = this->score[sum];
				this->score[sum] = this->score[i];
				this->score[i] = temp;

				temp = this->runk[sum];
				this->runk[sum] = this->runk[i];
				this->runk[i] = temp;
			}
		}
	}

	//---------------------------------------------------------------------------------------------------------------
	//ランクが上がったか下がったかのチェック
	//---------------------------------------------------------------------------------------------------------------
	int ScoreMap::isRunkUpper(int i)
	{
		if( this->oldRunk[i] == -1 )	return -1;
		int j, k = i, siz = this->runk.size();
		for(j=0; j<siz; j++)
		{
			if( this->oldRunk[j] == this->runk[i] )
				break;
		}

		if( j == k ) return 0;
		return ( j > k ? 1 : 2 );
	}

	//---------------------------------------------------------------------------------------------------------------
	//描画
	//---------------------------------------------------------------------------------------------------------------
	void ScoreMap::Draw()
	{
		this->mapDraw();
		this->plateDraw();
		this->scoreDraw();
	}

	void ScoreMap::mapDraw()
	{		
		this->mapTag->SetScl( Vector2(this->parts.scale.x * 0.8f, this->parts.scale.y * 0.8f ) );
		this->mapTag->SetNameColor( this->parts.color.color );	
		this->mapTag->Draw2D();
	}
	
	void ScoreMap::plateDraw()
	{
		this->mapPlateTag->SetScl( Vector2(this->parts.scale.x * 0.8f, this->parts.scale.y * 0.8f ) );
		this->mapPlateTag->SetNameColor( this->parts.color.color );	
		this->mapPlateTag->Draw2D();
	}
		
	void ScoreMap::scoreDraw()
	{
		float temp = SCRW_PERCENT(0.9f) / this->parts.scale.x;

		this->biggerDraw();
		for(int i=0, siz=this->score.size(), sc; i<siz; i++)
		{
			if( this->oldRunk[i] == -1 )	continue;
			sc = (i == 0 ? 70 : 50 );
			this->scoreDraw_inScore( i, sc, temp );
			this->scoreDraw_inUpper( i, sc, temp );
			this->scoreDraw_inRunker( i, sc, temp );
			this->scoreDraw_inPlayerName( i, sc, temp );
		}
	}

	void ScoreMap::biggerDraw()
	{
		int siz=this->score.size();
		for(int i=0; i<siz; i++)
		{
			if( this->oldRunk[i] == -1 )	continue;
			if( this->score[i] - this->oldScore[ this->runk[i] ] > 0 )
			{
				this->bigTag->SetPos( Vector2(SCRW_PERCENT(0.82f), 
							SCRH_PERCENT(0.42f + 70.0f * i - (i == 0 ? 10.0f : 0.0f) ) ) );
				this->bigTag->SetScl( this->offSetScale );
				this->bigTag->SetNameColor( this->parts.color.color );
				this->bigTag->Draw2D();
			}
		}
	}

	void ScoreMap::scoreDraw_inScore(int i, int sc, float temp)
	{
		//-----------------------------------------------------------------------
		//スコア
		this->scoreTag->SetNumber( this->score[i] );
		this->scoreTag->SetObject( &Vector2(SCRW_PERCENT(0.65f), 
									SCRH_PERCENT(0.4f + 70.0f * i - (i == 0 ? 10.0f : 0.0f) ) ),
									0.0f, &Vector2( (float)(sc * temp), (float)sc) );
		this->scoreTag->SetColor( Vector4(this->parts.color.color.x, 0,0,0) );
		this->scoreTag->Draw2D();
		//-----------------------------------------------------------------------
	}

	void ScoreMap::scoreDraw_inUpper(int i, int sc, float temp)
	{
		this->uppersSumDraw(i, sc, temp);
		//-----------------------------------------------------------------------
		//上昇値
		this->updownDraw(i, sc, temp);
		
		this->arrowDraw( i, sc, temp );
		//----------------------------------------------------------------------
	}

	void ScoreMap::updownDraw(int i, int sc, float temp)
	{
		int ab = this->score[i] - this->oldScore[ this->runk[i] ];
		
		this->updownTag->SetPos( Vector2(SCRW_PERCENT(0.84f), 
									SCRH_PERCENT(0.45f) + 70.0f * i - (i == 0 ? 10.0f : 0.0f) ) );
		this->updownTag->SetScl( Vector2((float)(sc * temp * 0.5f), (float)sc * 0.5f));
		this->updownTag->SetDialogName( ( ab > 0 ? "upper" : "downer" ) );
		this->updownTag->SetNameColor( this->parts.color.color );
		this->updownTag->Draw2D();
	}

	void ScoreMap::uppersSumDraw(int i, int sc, float temp)
	{
		int ab = this->score[i] - this->oldScore[ this->runk[i] ];
		this->scoreTag->SetNumber( abs( ab ) );
		this->scoreTag->SetObject( &Vector2(SCRW_PERCENT(0.8f), 
									SCRH_PERCENT(0.42f) + 70.0f * i - (i == 0 ? 10.0f : 0.0f ) ),
									0.0f, &Vector2( (float)(sc * temp * 0.5f), (float)sc * 0.5f) );
		this->scoreTag->SetColor( Vector4(this->parts.color.color.x, 255, 0, 0) );
		this->scoreTag->Draw2D();
	}

	void ScoreMap::arrowDraw(int i, int sc, float temp)
	{
		int noRunk;
		if( (noRunk = this->isRunkUpper(i)) > 0  )
		{
			this->arrowTag->SetPos( Vector2(SCRW_PERCENT(0.4f), 
					SCRH_PERCENT(0.4f + 70.0f * i - (i == 0 ? 10.0f : 0.0f) ) ) );
			this->arrowTag->SetAng( ( noRunk == 1 ? 0.0f : 3.14f ) );
			this->arrowTag->SetScl( Vector2( (float)(sc * temp * 0.5f), (float)sc * 0.5f ) );
			this->arrowTag->SetNameColor( ( noRunk == 1 ? Vector4( this->parts.color.color.x, 255, 0, 0 ) :
															Vector4( this->parts.color.color.x, 0, 0, 255 ) ) );
			this->arrowTag->Draw2D();
		}
	}

	void ScoreMap::scoreDraw_inRunker(int i, int sc, float temp)
	{
		this->runkNumberTag->SetPos( Vector2(SCRW_PERCENT(0.2f), 
									SCRH_PERCENT(0.4f + 70.0f * i) ) );
		this->runkNumberTag->SetScl( Vector2( (float)(sc * temp), (float)sc) );
		this->runkNumberTag->SetColor( Vector4(this->parts.color.color.x, 255, 255, 0 ) );
		this->runkNumberTag->SetNumber( i+1 );
		this->runkNumberTag->Draw2D();
	}

	void ScoreMap::scoreDraw_inPlayerName(int i, int sc, float temp)
	{
		this->playerTag->SetPos( Vector2(SCRW_PERCENT(0.35f), 
									SCRH_PERCENT(0.4f + 70.0f * i) ) );
		this->playerTag->SetScl( Vector2((float)(sc * temp), (float)sc ) );
		this->playerTag->SetName( NameTagString[this->runk[i]] );
		this->playerTag->SetNameAlpha( this->parts.color.color.x );

		switch( i )
		{
			case 0:	this->playerTag->SetFace(FACE_LAUGH);	break;
			case 1:	this->playerTag->SetFace(FACE_SMILE);	break;
			case 2:	this->playerTag->SetFace(FACE_HURRY);	break;
			case 3:	this->playerTag->SetFace(FACE_LOSE);	break;
		}

		this->playerTag->Draw2D();
	}

	void ScoreMap::inputScoreData(RoomData& _data, bool IsContinue)
	{
		if( !IsContinue )	return ;
		this->SetPlaySum( _data.playSum );
		for(int i=0, count=0; i<4; i++)
		{
			if( _data.charaData[i].selectFlag )
			{
				this->oldRunk[count] = _data.charaData[i].runk;
				this->runk[_data.charaData[i].runk] = count;
				this->oldScore[count] = _data.charaData[i].score;
				this->score[ _data.charaData[i].runk ] = _data.charaData[i].score;
				count++;
			}
		}
	}
	
	int ScoreMap::GetPlayerRunkNumber(int runk)
	{
		for(int i=0,siz=this->runk.size(); i<siz; i++)
		{
			if( this->runk[i] == runk )
				return i;
		}
		return -1;
	}

	void ScoreMap::GetScoreAndRunk(RoomData& _data)
	{
		for(int i=0, count=0; i<4; i++)
		{
			if( _data.charaData[i].selectFlag )
			{
				_data.charaData[i].score = this->score[ this->runk[count] ];
				_data.charaData[i].runk = this->runk[count];
				count++;
			}
		}
	}
}