#pragma once

///////////////////////////////////////////
//MYGAME
#include <ResourceFactory.h>
#include <TemplateEffectList.h>
using namespace NanairoLib;

///////////////////////////////////////////
//
//使うだろうエフェクトを定義して
//再利用化できるようにしよう。
//
///////////////////////////////////////////

namespace MYGAME
{
	void TemplateEffectList<StarEffect*>::Init()
	{
		this->offSet.SetMinVector();
		this->Clear();
		this->SetRandomStarAction();
	}

	void TemplateEffectList<StarEffect*>::SetRandomStarAction()
	{
		this->Action = &TemplateEffectList<StarEffect*>::move;
	}

	void TemplateEffectList<StarEffect*>::SetDownStarAction()
	{
		this->Action = &TemplateEffectList<StarEffect*>::downMove;
	}

	void TemplateEffectList<StarEffect*>::Step()
	{
		(this->*Action)();
		
		if( this->list.empty() )	return ;

		for(std::list<StarEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Step();
		this->Del();
	}

	void TemplateEffectList<StarEffect*>::move()
	{
		if( this->IncrementFrameCnt( 200 ) )
			this->Action = &TemplateEffectList<StarEffect*>::fadeout;
		if( this->IsNoRemender_FrameCnt( 10 ) )
			this->PushRandomStar();
	}
	
	void TemplateEffectList<StarEffect*>::downMove()
	{
		++this->frameCnt;
		if( this->IsNoRemender_FrameCnt( 10 ))
			this->PushDownStar();
	}

	void TemplateEffectList<StarEffect*>::fadeout()
	{
		if(	this->list.empty() )
			this->delFlag = true;
	}

	void TemplateEffectList<StarEffect*>::PushRandomStar()
	{
		RandomStarEffect* point = new RandomStarEffect();
		point->SetObject( this->offSet, 5 );
		this->list.push_back( point );
	}

	void TemplateEffectList<StarEffect*>::PushDownStar()
	{
		DownStarEffect* point = new DownStarEffect();
		point->SetObject( Vector2( 50.0f + (float)(rand() % (int)(SCRW * 0.8f)), this->offSet.y), 5 );
		this->list.push_back( point );
	}

	void TemplateEffectList<StarEffect*>::Draw2D()
	{
		for(std::list<StarEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Draw2D();
	}
	
	void TemplateEffectList<StarEffect*>::Del()
	{
		std::list<StarEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( (*it)->isDel() )
			{
				ES_SAFE_DELETE( (*it) );
				it = this->list.erase(it);
			}
			else
				it++;
		}
	}

	void TemplateEffectList<StarEffect*>::Clear()
	{
		std::list<StarEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->list.erase(it);
		}
	}

	//----------------------------------------------------------------

	void TemplateEffectList<FireflowerEffect*>::Init()
	{
		this->Clear();
		this->Action = &TemplateEffectList<FireflowerEffect*>::move;
	}

	void TemplateEffectList<FireflowerEffect*>::Step()
	{
		for(std::list<FireflowerEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Step();
		
		(this->*Action)();
		this->Del();
	}

	void TemplateEffectList<FireflowerEffect*>::move()
	{
		if( ++this->frameCnt == 1 )
		{
			for(int i=0; i<10; i++ )
				this->Push();
		}
		if( this->frameCnt >= 10 )
			this->Action = &TemplateEffectList<FireflowerEffect*>::fadeout;
	}
	
	void TemplateEffectList<FireflowerEffect*>::fadeout()
	{
		if(	this->list.empty() )
			this->delFlag = true;
	}

	void TemplateEffectList<FireflowerEffect*>::Push()
	{
		FireflowerEffect* point = new FireflowerEffect();
		point->SetObject( this->parts.pos );
		this->list.push_back( point );
	}

	void TemplateEffectList<FireflowerEffect*>::Draw2D()
	{
		for(std::list<FireflowerEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Draw2D();
	}
	
	void TemplateEffectList<FireflowerEffect*>::Del()
	{
		std::list<FireflowerEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( (*it)->isDel() )
			{
				ES_SAFE_DELETE( (*it) );
				it = this->list.erase(it);
			}
			else
				it++;
		}
	}

	void TemplateEffectList<FireflowerEffect*>::Clear()
	{
		std::list<FireflowerEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->list.erase(it);
		}
	}

	//---------------------------------------------------------------------

	void TemplateEffectList<ConfettiEffect*>::Init()
	{
		this->Clear();
		this->Action = &TemplateEffectList<ConfettiEffect*>::move;
	}

	void TemplateEffectList<ConfettiEffect*>::Step()
	{
		for(std::list<ConfettiEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Step();
	
		(this->*Action)();
		
		this->Del();
	}

	void TemplateEffectList<ConfettiEffect*>::SetFadeOut()
	{
		this->Action = &TemplateEffectList<ConfettiEffect*>::fadeout;
	}

	void TemplateEffectList<ConfettiEffect*>::move()
	{
		++this->frameCnt;
		if( this->IsNoRemender_FrameCnt( 30 ) )
			this->Push();
	}
	
	void TemplateEffectList<ConfettiEffect*>::fadeout()
	{
		if(	this->list.empty() )
			this->delFlag = true;
	}

	void TemplateEffectList<ConfettiEffect*>::Push()
	{
		ConfettiEffect* point = new ConfettiEffect();
		point->SetObject( Vector2( (float)(rand() % SCRW), -10.0f ) );
		this->list.push_back( point );
	}

	void TemplateEffectList<ConfettiEffect*>::Draw2D()
	{
		for(std::list<ConfettiEffect*>::iterator it = this->list.begin(), end = this->list.end();
			it != end; it++)
			(*it)->Draw2D();
	}
	
	void TemplateEffectList<ConfettiEffect*>::Del()
	{
		std::list<ConfettiEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( (*it)->isDel() )
			{
				ES_SAFE_DELETE( (*it) );
				it = this->list.erase(it);
			}
			else
				it++;
		}
	}

	void TemplateEffectList<ConfettiEffect*>::Clear()
	{
		std::list<ConfettiEffect*>::iterator it = this->list.begin();
		while( it != this->list.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->list.erase(it);
		}
	}
}