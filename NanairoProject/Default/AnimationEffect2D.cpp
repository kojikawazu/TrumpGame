#pragma once

///////////////////////////////////////////////////
//MYGAME
#include <ResourceFactory.h>
#include <EffectParts.h>
using namespace NanairoLib;

///////////////////////////////////////////////////
//
//アニメーションエフェクトの基底クラスと
//テンプレートエフェクトリスト
//
///////////////////////////////////////////////////

namespace MYGAME
{
	//////////////////////////////////////////////////////////////////////

	void AnimationEffect2D::SuperInitAnimationEffect2D()
	{
		this->OKFlag = false;
		this->sumCnt = this->animeCnt = 0;
		this->intervalCnt = 5;
	}

	void AnimationEffect2D::SetSumCnt(LPCSTR dname, int dsum)
	{
		this->sumCnt = dsum;
		this->animeName = dname;
		this->OKFlag = true;
	}

	void AnimationEffect2D::Step_and_Checking()
	{
		if( !this->OKFlag || this->delFlag )	return ;

		this->IncrementFrameCnt(1, this->cntSpd);
		if( this->IsNoRemender_FrameCnt( this->intervalCnt ) )
		{
			if( this->Increment(this->animeCnt, this->sumCnt) )
				this->OnDel( true );
		}
	}

	void AnimationEffect2D::Step_and_Checking_repeat()
	{
		if( !this->OKFlag || this->delFlag )	return ;

		this->IncrementFrameCnt(1, this->cntSpd);
		if( this->IsNoRemender_FrameCnt( this->intervalCnt ) )
			this->Increment_repeat( this->animeCnt, this->sumCnt );
	}

	void AnimationEffect2D::Same_draw()
	{
		if( !this->OKFlag || this->delFlag )	return ;

		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans( this->parts.pos, this->parts.scale, this->parts.ang,
			this->animeName, DIRECT_SCALE, this->parts.color.color );
		gh->draw_divGraph( this->animeCnt );
	}

	//////////////////////////////////////////////////////////////////////

	void OnceEffect::Step_and_Checking()
	{
		if( this->IncrementFrameCnt( this->delCnt ) )
			this->OnDel( true );
	}

	void OnceEffect::Action_draw()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		gh->draw_SetTrans(this->parts.pos, this->parts.scale, this->parts.ang,
			word, DIRECT_SCALE, this->parts.color.color );
		gh->draw_graph();
	}

	//////////////////////////////////////////////////////////////

	ObjectList<NanairoLib::PEffect2D>::ObjectList() : objSum(0)
	{
		this->Init();
	}

	ObjectList<NanairoLib::PEffect2D>::~ObjectList()
	{
		this->ListClear();
	}

	void ObjectList<NanairoLib::PEffect2D>::Init()
	{
		this->objSum = 0;
		this->ListClear();
	}

	int ObjectList<NanairoLib::PEffect2D>::Size()
	{
		return this->objSum;
	}

	bool ObjectList<NanairoLib::PEffect2D>::Empty()
	{
		return ( !this->objSum );
	}

	void ObjectList<NanairoLib::PEffect2D>::Add(PEffect2D add)
	{
		this->obList.push_back( add );
		this->objSum++;
	}

	void ObjectList<NanairoLib::PEffect2D>::Insert(PEffect2D add, int number)
	{
		this->obList.insert( this->GetIterator( number ), add );		
		this->objSum++;
	}

	void ObjectList<NanairoLib::PEffect2D>::Insert(PEffect2D add, const PEffect2D index)
	{
		this->obList.insert( this->GetIterator( (PEffect2D)index ), add );
		this->objSum++;
	}

	std::list<NanairoLib::PEffect2D>::iterator ObjectList<NanairoLib::PEffect2D>::GetIterator(int number)
	{
		Effect2DIterator it = this->obList.begin();
		int count = 0;
		while( it != this->obList.end() )
		{
			if( count == number )	
				return it;
			else
			{
				count++;
				it++;
			}
		}
		return this->obList.end();
	}
	
	std::list<NanairoLib::PEffect2D>::iterator ObjectList<NanairoLib::PEffect2D>::GetIterator(PEffect2D number)
	{
		Effect2DIterator it = this->obList.begin();
		while( it != this->obList.end() )
		{
			if( (*it) == number )	return it;
			else					it++;
		}
		return this->obList.end();
	}

	void ObjectList<NanairoLib::PEffect2D>::ListClear()
	{
		Effect2DIterator it = this->obList.begin();
		while( it != this->obList.end() )
		{
			ES_SAFE_DELETE( (*it) );
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	void ObjectList<NanairoLib::PEffect2D>::Dispose(int number)
	{
		Effect2DIterator it = this->GetIterator(number);
		if( it != this->obList.end() )
		{
			(*it)->Dispose();
			ES_SAFE_DELETE( (*it) );
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	void ObjectList<NanairoLib::PEffect2D>::Dispose(PEffect2D obj)
	{
		Effect2DIterator it = this->GetIterator( obj );
		if( it != this->obList.end() )
		{
			(*it)->Dispose();
			ES_SAFE_DELETE( (*it) );
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	PEffect2D ObjectList<NanairoLib::PEffect2D>::Unlink(int number)
	{
		Effect2DIterator it = this->GetIterator(number);
		PEffect2D output = NULL;
		if( it != this->obList.end() )
		{
			output = (*it);
			this->objSum--;
			it = this->obList.erase( it );
		}
		return output;
	}
		
	PEffect2D ObjectList<NanairoLib::PEffect2D>::Unlink(PEffect2D obj)
	{
		Effect2DIterator it = this->GetIterator(obj);
		PEffect2D output = NULL;
		if( it != this->obList.end() )
		{
			output = (*it);
			this->objSum--;
			it = this->obList.erase( it );
		}
		return output;
	}

	void ObjectList<NanairoLib::PEffect2D>::Step()
	{
		for(Effect2DIterator it = this->obList.begin();
			it != this->obList.end(); it++)
			(*it)->Step();
	}

	void ObjectList<NanairoLib::PEffect2D>::ChainStep(CHAIN_TYPE type)
	{
		Effect2DIterator it = this->obList.begin(), old;
		NanairoLib::UIParts2D off1, off2;
		int count = 0;
		while( it != this->obList.end() )
		{
			if( !count )
			{
				off1 = (*(*it)->GetParts());
				(*it)->Step();
			}
			else if( count )
			{
				off2 = (*(*it)->GetParts());
				(*it)->SetAng(off1.ang);
				(*it)->SetScl(off1.scale);
				
				switch( type )
				{
					case CHAIN_POSX:	(*it)->SetPos(Vector2(off1.pos.x, off2.pos.y));	break;
					case CHAIN_POSY:	(*it)->SetPos(Vector2(off2.pos.x, off1.pos.y));	break;
					case CHAIN_POSXY:	(*it)->SetPos(Vector2(off1.pos.x, off1.pos.y));	break;
				}

				off1 = off2;
			}
			old = it;
			it++;
			count++;
		}
	}

	void ObjectList<NanairoLib::PEffect2D>::Draw()
	{
		for(Effect2DIterator it = this->obList.begin();
			it != this->obList.end(); it++)
			(*it)->Draw2D();
	}

	void ObjectList<NanairoLib::PEffect2D>::Del()
	{	
		Effect2DIterator it = this->obList.begin();
		while( it != this->obList.end() )
		{
			if( (*it)->isDel() )
			{
				ES_SAFE_DELETE( (*it) );
				it = this->obList.erase( it );
				this->objSum--;
			}
			else
				it++;
		}
	}
}