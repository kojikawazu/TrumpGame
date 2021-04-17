#pragma once

//-----------------------------------------------------
//MYGAME
//-----------------------------------------------------
#include <ResourceFactory.h>

//-----------------------------------------------------
//NanairoProject
//-----------------------------------------------------
#include <PlateEffect.h>
#include <TrumpCard.h>
using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	void PlayerPlate::Init()
	{
		this->runkNumber = this->oldRunkNumber = this->foulFlag = this->faceNumber = 0;
		offSet.SetMinVector();
		offSetSpd.SetMinVector();
		this->parts.scale.SetVector( 100, 100 );
		word = "";
		runkWord = "";
	}

	void PlayerPlate::SetObjectNumber(int dnumber, int charaNumber)
	{
		switch( this->playNumber = dnumber )
		{
			case 0:	
				this->parts.pos.SetPercentVector( 0.9f, 0.9f );
				this->yousiPos.SetPercentVector( 0.55f, 0.85f );
				this->yousiScale.SetPercentVector( 0.8f , 0.3f );
				break;
			case 1:	
				this->parts.pos.SetPercentVector( 0.9f, 0.1f );
				this->yousiPos.SetPercentVector( 0.925f, 0.35f );
				this->yousiScale.SetPercentVector( 0.5f, 0.15f );
				break;
			case 2:	
				this->parts.pos.SetPercentVector( 0.1f, 0.1f );
				this->yousiPos.SetPercentVector( 0.3f, 0.075f );
				this->yousiScale.SetPercentVector( 0.55f, 0.15f );
				break;
			case 3:	
				this->parts.pos.SetPercentVector( 0.1f, 0.9f);
				this->yousiPos.SetPercentVector( 0.075f, 0.65f);
				this->yousiScale.SetPercentVector( 0.5f, 0.15f);
				break;
		}

		this->word = NameTagString[charaNumber];
		this->SetFace(0);
	}

	void PlayerPlate::SetContinue()
	{
		this->foulFlag = 0;
		this->oldRunkNumber = this->runkNumber;
		this->SetRunkName();
	}

	void PlayerPlate::SetRunkName()
	{
		switch( this->runkNumber )
		{
			case 1:	this->runkWord = "number1Frame";	break;
			case 2:	this->runkWord = "number2Frame";	break;
			case 3:	this->runkWord = "number3Frame";	break;
			case 4:	this->runkWord = "number4Frame";	break;
		}
	}
	
	void PlayerPlate::Draw2D()
	{
		this->plateDraw();

		if( this->runkNumber > 0 )
			this->runkDraw();

		switch( this->foulFlag )
		{
		case FOUL_CAPITALDOWN:
			this->capitalDownDraw();
			break;
		case FOUL_FOULUP:
			this->foulDraw();
			break;
		}
	}
	
	void PlayerPlate::plateDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos,
			this->parts.scale, this->parts.ang,
			word , DIRECT_SCALE, this->parts.color.color );
		gh->draw_divGraph(this->faceNumber);
	}

	void PlayerPlate::runkDraw()
	{
		if( this->runkWord == "")	return ;

		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos,
			Vector2(this->parts.scale.x * 1.15f, this->parts.scale.y * 1.15f),
			this->parts.ang, this->runkWord, DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	void PlayerPlate::capitalDownDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos,
			D3DXVECTOR2(this->parts.scale.x * 1.15f, this->parts.scale.y * 1.15f),
			this->parts.ang, "capitalDown" , DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}
	
	void PlayerPlate::foulDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos,
			D3DXVECTOR2(this->parts.scale.x * 1.15f, this->parts.scale.y * 1.15f),
			this->parts.ang, "foul" , DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	void PlayerPlate::yousiDraw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->yousiPos.SetD3DVector2(),
			this->yousiScale.SetD3DVector2(), ( this->playNumber == 0 || this->playNumber == 2 ? 0.0f : 1.57f),
			"yousi" , DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}
	
	//--------------------------------------------------------------------------------------

	void PlateList<PlayerPlate*>::Init()
	{
		this->objSum = 0;
		if( !this->list.empty() )
			this->Clear();
	}

	void PlateList<PlayerPlate*>::Step()
	{
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Step();
	}

	int PlateList<PlayerPlate*>::GetPlayNumber_runk1()
	{
		int number = 1;
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
		{
			if( (*it)->GetOldRunkNumber() == 1 )
				return number;
			else
				number++;
		}
		return 0;
	}

	int PlateList<PlayerPlate*>::GetPlayNumber_runk4()
	{
		int number = 1;
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
		{
			if( (*it)->GetOldRunkNumber() == 4 )
				return number;
			else
				number++;
		}
		return 0;
	}

	int PlateList<PlayerPlate*>::GetPlayNumber_runk(int num)
	{
		int number = 1;
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
		{
			if( (*it)->GetOldRunkNumber() == num )
				return number;
			else
				number++;
		}
		return 0;
	}

	std::vector<int> PlateList<PlayerPlate*>::GetFoulSum()
	{
		std::vector<int> vec(2);
		int foul = 0;
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), 
			end = this->list.end(); it != end; it++)
		{
			switch ( foul = (*it)->GetFoulFlag() )
			{
			case FOUL_CAPITALDOWN:
				vec[0]++;
				break;
			case FOUL_FOULUP:
				vec[1]++;
				break;
			}
		}
		return vec;
	}

	PlayerPlate* PlateList<PlayerPlate*>::GetPlayerPlate(int number)
	{
		int count = 0;
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++, count++)
		{
			if( count == number )
				return (*it);
		}
		return NULL;
	}

	void PlateList<PlayerPlate*>::Pusher(int playNumber, int charaNumber)
	{
		this->objSum++;
		PlayerPlate* point = new PlayerPlate();
		point->SetObjectNumber( playNumber, charaNumber );
		this->list.push_back( point );
	}

	void PlateList<PlayerPlate*>::Push(int playNumber, int runkNumber)
	{
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
		{
			if( (*it)->GetPlayerNumber() == playNumber )
			{
				(*it)->SetRunk( runkNumber+1 );
				break;
			}
		}
	}

	void PlateList<PlayerPlate*>::SetContinue()
	{
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->SetContinue();
	}

	void PlateList<PlayerPlate*>::onFoul(int playNumber, int foulNumber)
	{
		int number = 0;
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++, number++)
		{
			if( playNumber == number )
			{
				switch( foulNumber )
				{
					case FOUL_CAPITALDOWN:
						(*it)->onCapitalDown();
						break;
					case FOUL_FOULUP:
						(*it)->onFoulUp();
						break;
				}
				break;
			}
		}
	}

	void PlateList<PlayerPlate*>::Clear()
	{
		std::list<PlayerPlate*>::iterator it = this->list.begin();
		this->objSum = 0;
		while( it != this->list.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->list.erase( it );
		}
	}

	void PlateList<PlayerPlate*>::Draw2D()
	{
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Draw2D();
	}

	void PlateList<PlayerPlate*>::yousiDraw()
	{
		for(std::list<PlayerPlate*>::iterator it = this->list.begin(), 
			end = this->list.end(); it != end; it++)
			(*it)->yousiDraw();
	}
}