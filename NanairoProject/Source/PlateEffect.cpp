#pragma once

//////////////////////////////////////////////////
//MYGAME
//////////////////////////////////////////////////
#include <ResourceFactory.h>

//////////////////////////////////////////////////
//NanairoProject
//////////////////////////////////////////////////
#include <PlateEffect.h>
#include <TrumpCard.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	//---------------------------------------------------------------
	void PlateEffect::Init()
	{
		this->delFlag = this->waitFlag = false;
		this->offSet.SetMinVector();
		this->offSetSpd.SetMinVector();
		this->plateType = 0;

		this->parts.scale.SetVector( 120.0f, 60.0f );
		this->Action = &PlateEffect::action_up;
	}

	void PlateEffect::SetObject(int dtype, int number)
	{
		switch( dtype )
		{
			case TRUMP_RULE_EIGHTCUT:	this->word = "plateEightcut";	break;
			case TRUMP_RULE_ELEVENBACK:	this->word = "plateElevenback";	break;
			case TRUMP_RULE_RESTRAINS:	this->word = "plateRestrains";	break;
			case TRUMP_RULE_REVOLUTION:	this->word = "plateRevolution";	break;
			case TRUMP_RULE_JOCKER:		this->word = "plateJockerEFF";	break;
			case TRUMP_RULE_SPADE3:		this->word = "plateSpade3";		break;
			case TRUMP_RULE_STAIRS:		this->word = "plateStairs";		break;
		}
	
		this->plateType = dtype;
		this->plateNumber = number;

		this->parts.scale.SetMinVector();
		this->parts.pos.SetPercentVector( 0.7f, 0.6f );
		this->offSet.SetVector( 120 / 10, 60 / 10 );
		this->offSetSpd.SetVector( 10, 0 );
	}

	void PlateEffect::SetFadeOut()
	{
		this->waitFlag = true;
		this->offSet.SetVector( -this->parts.scale.x / 10, -this->parts.scale.y / 10 );
		this->offSetSpd.SetVector( 10, 0 );
		this->Action = &PlateEffect::action_right;
	}

	void PlateEffect::SetPlateDown(int spd)
	{
		this->plateNumber -= spd;
		this->offSet.SetVector( 0.0f, ((100.0f + this->plateNumber * 50.0f) - 
								this->parts.pos.y ) / 10 );
		this->offSetSpd.SetVector( 0, 10 );
	}

	void PlateEffect::action_down()
	{
		if( this->offSetSpd.y > 0.0f )
		{
			this->parts.pos.y += this->offSet.y;
			this->offSetSpd.y -= 1.0f;
		}
	}

	void PlateEffect::action_up()
	{
		this->parts.scale.Add( this->offSet );
		this->offSetSpd.x -= 1.0f;
		
		if( this->offSetSpd.x <= 0.0f )
		{
			this->offSet.SetVector( 0.0f, ((200.0f + this->plateNumber * 50.0f) - 
								this->parts.pos.y ) / 10 );
			this->offSetSpd.SetVector( 0, 10 );
			this->Action = &PlateEffect::action_down;
		}
	}

	void PlateEffect::action_right()
	{
		this->parts.scale.Add( this->offSet );
		this->offSetSpd.x -= 1.0f;
		
		if( this->offSetSpd.x <= 0.0f )
			this->delFlag = true;
	}

	void PlateEffect::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos,
			this->parts.scale, this->parts.ang,
			word.c_str() , DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	//--------------------------------------------------------------------------------

	void PlateList<PlateEffect*>::Init()
	{
		if( !this->list.empty() )
			this->Clear();
	}

	void PlateList<PlateEffect*>::Step()
	{
		for(std::list<PlateEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Step();
	}
	
	void PlateList<PlateEffect*>::Draw2D()
	{
		for(std::list<PlateEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Draw2D();
	}
	
	void PlateList<PlateEffect*>::Del()
	{
		std::list<PlateEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( (*it)->delFlag ) 
			{
				ES_SAFE_DELETE( (*it) );
				it = this->list.erase( it );
				this->objSum--;
			}
			else
				it++;
		}
	}

	void PlateList<PlateEffect*>::Clear()
	{
		std::list<PlateEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->list.erase( it );
		}
	}

	void PlateList<PlateEffect*>::Push(int dtype)
	{
		int number = 0;
		for(std::list<PlateEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
		{
			if( (*it)->waitFlag )
				number++;
		}

		PlateEffect* point = new PlateEffect();
		point->SetObject( dtype, this->list.size() - number );
		this->list.push_back( point );
	}

	void PlateList<PlateEffect*>::Pop(int dtype)
	{
		std::list<PlateEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( (*it)->GetCardType() == dtype )
			{
				(*it)->SetFadeOut();		
				it++;
				while( it != this->list.end() )
				{
					(*it)->SetPlateDown(1);
					it++;
				}
				break;
			}
			else
				it++;
		}
	}

}