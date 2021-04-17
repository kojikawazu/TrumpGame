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
	//-------------------------------------------------------------------
	//SuperMillionareEffect
	void SuperMillionareEffect::wordDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos,
			this->parts.scale, this->parts.ang,
			word.c_str() , DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	void SuperMillionareEffect::SetObject(int playNumber)
	{	
		this->playNumber = playNumber;

		switch( this->playNumber )
		{
			case 0:	this->parts.pos.SetPercentVector( 0.9f, 0.97f);	break;
			case 1:	this->parts.pos.SetPercentVector( 0.9f, 0.17f);	break;
			case 2:	this->parts.pos.SetPercentVector( 0.1f, 0.17f);	break;
			case 3:	this->parts.pos.SetPercentVector( 0.1f, 0.97f);	break;
		}
	}

	//-------------------------------------------------------------------
	//SuperMillionareEffect static
	SuperMillionareEffect* SuperMillionareEffect::CreateMillionareEffect(int number)
	{	
		switch( number )
		{
			case BIG_MILL_EFFECT:	return new BigMillionareEffect();	
			case SMALL_MILL_EFFECT:	return new SmallMillionareEffect();
			case SMALL_POOR_EFFECT:	return new SmallPoorEffect();
			case BIG_POOR_EFFECT:	return new BigPoorEffect();
		}
		return NULL;
	}

	//------------------------------------------------------------------------
	void BigMillionareEffect::Init()
	{
		this->sameInit();
		this->number = BIG_MILL_EFFECT;
		this->word = "BigMillionaire";
	}

	//------------------------------------------------------------------------
	void SmallMillionareEffect::Init()
	{
		this->sameInit();
		this->number = SMALL_MILL_EFFECT;
		this->word = "SmallMillionaire";
	}

	//------------------------------------------------------------------------
	void SmallPoorEffect::Init()
	{
		this->sameInit();
		this->number = SMALL_POOR_EFFECT;
		this->word = "SmallPoor";
	}

	//------------------------------------------------------------------------
	void BigPoorEffect::Init()
	{
		this->sameInit();
		this->number = BIG_POOR_EFFECT;
		this->word = "BigPoor";
	}

	//------------------------------------------------------------------------

	void PlateList<SuperMillionareEffect*>::Init()
	{
		this->objSum = 0;
		if( !this->list.empty() )
			this->Clear();
	}

	void PlateList<SuperMillionareEffect*>::Step()
	{
		for(std::list<SuperMillionareEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Step();
	}

	void PlateList<SuperMillionareEffect*>::Draw2D()
	{
		for(std::list<SuperMillionareEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Draw2D();
	}

	void PlateList<SuperMillionareEffect*>::Clear()
	{
		std::list<SuperMillionareEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->list.erase( it );
		}
	}

	void PlateList<SuperMillionareEffect*>::Push(int playNumber, int runkNumber)
	{
		SuperMillionareEffect* point = SuperMillionareEffect::CreateMillionareEffect(runkNumber);
		this->objSum++;
		point->SetObject( playNumber );
		this->list.push_back( point );
	}

	void PlateList<SuperMillionareEffect*>::CapitalDownPush(int playNumber)
	{
		SuperMillionareEffect* point =  SuperMillionareEffect::CreateMillionareEffect(0);
		this->objSum++;
		point->SetObject( playNumber );
		this->list.push_back( point );
	}

	int PlateList<SuperMillionareEffect*>::GetNottingNumber(int capNum)
	{
		int number = 0;
		std::list<SuperMillionareEffect*>::iterator it = this->list.begin(), end = this->list.end();
		while( it != end )
		{
			if( (*it)->GetPlayNumber() == number || capNum - 1 == number )
			{		
				number++;
				it = this->list.begin();
			}
			else
				it++;
		}
		return number;
	}

	int PlateList<SuperMillionareEffect*>::GetNumber1()
	{
		std::list<SuperMillionareEffect*>::iterator it = this->list.begin(), end = this->list.end();
		while( it != end )
		{
			if( (*it)->GetRunk() == 0 )
				return (*it)->GetPlayNumber();
			else
				it++;
		}
		return -1;
	}

	std::vector<int> PlateList<SuperMillionareEffect*>::GetRunk()
	{
		std::vector<int> vec( this->list.size() );
		int num = 0;
		std::list<SuperMillionareEffect*>::iterator it = this->list.begin(), end = this->list.end();
		for(int i=0, siz = this->list.size(); i<siz; i++)
		{
			for(std::list<SuperMillionareEffect*>::iterator it = this->list.begin(), end = this->list.end();
				it != end; it++ )
			{
				if( (*it)->GetRunk() == i )
				{	
					vec[i] = (*it)->GetPlayNumber();
					break;
				}
			}
		}
		
		return vec;
	}
}