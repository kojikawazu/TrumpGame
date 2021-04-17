#pragma once
//--------------------------------------------------------------------------
//キャラクタークラスを管理するリストクラス
//<Chara3DctorManagerClass>
//--------------------------------------------------------------------------
#include <OBjectList.h>
using namespace NanairoLib;

namespace MYGAME
{
	template<typename T>ObjectList<T>::ObjectList() : objSum(0)
	{
		this->Init();
	}

	template<typename T>ObjectList<T>::~ObjectList()
	{
		this->ListClear();
	}

	template<typename T>void ObjectList<T>::Init()
	{
		this->objSum = 0;
		this->ListClear();
	}

	template<typename T>int ObjectList<T>::Size()
	{
		return this->objSum;
	}

	template<typename T>bool ObjectList<T>::Empty()
	{
		return ( this->objSum == 0 );
	}

	template<typename T>void ObjectList<T>::Add(T add)
	{
		this->obList.push_back( add );
		this->objSum++;
	}

	template<typename T>void ObjectList<T>::Insert(T add, int number)
	{
		this->obList.insert( this->GetIterator( number ), add );		
		this->objSum++;
	}

	template<typename T>void ObjectList<T>::Insert(T add, const T index)
	{
		this->obList.insert( this->GetIterator( (T)index ), add );
		this->objSum++;
	}

	template<typename T>void ObjectList<T>::ListClear()
	{
		this->obList.clear();
	}

	template<typename T>void ObjectList<T>::Dispose(int number)
	{
		std::list<T>::iterator it = this->GetIterator(number);
		if( it != this->obList.end() )
		{
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	template<typename T>void ObjectList<T>::Dispose(T obj)
	{
		std::list<T>::iterator it = this->GetIterator( obj );
		if( it != this->obList.end() )
		{
			ES_SAFE_DELETE( (*it) );
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	template<typename T>T ObjectList<T>::Unlink(int number)
	{
		std::list<PNormalObject>::iterator it = this->GetIterator(number);
		T output = NULL;
		if( it != this->obList.end() )
		{
			output = (*it);
			this->objSum--;
			it = this->obList.erase( it );
		}
		return output;
	}
		
	template<typename T>T ObjectList<T>::Unlink(T obj)
	{
		std::list<T>::iterator it = this->GetIterator(obj);
		T output = NULL;
		if( it != this->obList.end() )
		{
			output = (*it);
			this->objSum--;
			it = this->obList.erase( it );
		}
		return output;
	}

	//---------------------------------------------------------------------

	ObjectList<PNormalObject>::ObjectList() : objSum(0)
	{
		this->Init();
	}

	ObjectList<PNormalObject>::~ObjectList()
	{
		this->ListClear();
	}

	void ObjectList<PNormalObject>::Init()
	{
		this->objSum = 0;
		this->ListClear();
	}

	int ObjectList<PNormalObject>::Size()
	{
		return this->objSum;
	}

	bool ObjectList<PNormalObject>::Empty()
	{
		return ( this->objSum == 0 );
	}

	void ObjectList<PNormalObject>::Add(PNormalObject add)
	{
		this->obList.push_back( add );
		this->objSum++;
	}

	void ObjectList<PNormalObject>::Insert(PNormalObject add, int number)
	{
		this->obList.insert( this->GetIterator( number ), add );		
		this->objSum++;
	}

	void ObjectList<PNormalObject>::Insert(PNormalObject add, NanairoLib::PCNormalObject index)
	{
		this->obList.insert( this->GetIterator( (PNormalObject)index ), add );
		this->objSum++;
	}

	std::list<PNormalObject>::iterator ObjectList<PNormalObject>::GetIterator(int number)
	{
		NormalIterator it = this->obList.begin();
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
	
	std::list<PNormalObject>::iterator ObjectList<PNormalObject>::GetIterator(PNormalObject number)
	{
		NormalIterator it = this->obList.begin();
		while( it != this->obList.end() )
		{
			if( (*it) == number )	return it;
			else					it++;
		}
		return this->obList.end();
	}

	void ObjectList<PNormalObject>::ListClear()
	{
		NormalIterator it = this->obList.begin();
		while( it != this->obList.end() )
		{
			ES_SAFE_DELETE( (*it) );
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	void ObjectList<PNormalObject>::Dispose(int number)
	{
		NormalIterator it = this->GetIterator(number);
		if( it != this->obList.end() )
		{
			(*it)->Dispose();
			ES_SAFE_DELETE( (*it) );
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	void ObjectList<PNormalObject>::Dispose(PNormalObject obj)
	{
		NormalIterator it = this->GetIterator( obj );
		if( it != this->obList.end() )
		{
			(*it)->Dispose();
			ES_SAFE_DELETE( (*it) );
			this->objSum--;
			it = this->obList.erase( it );
		}
	}

	PNormalObject ObjectList<PNormalObject>::Unlink(int number)
	{
		NormalIterator it = this->GetIterator(number);
		PNormalObject output = NULL;
		if( it != this->obList.end() )
		{
			output = (*it);
			this->objSum--;
			it = this->obList.erase( it );
		}
		return output;
	}
		
	PNormalObject ObjectList<PNormalObject>::Unlink(PNormalObject obj)
	{
		NormalIterator it = this->GetIterator(obj);
		PNormalObject output = NULL;
		if( it != this->obList.end() )
		{
			output = (*it);
			this->objSum--;
			it = this->obList.erase( it );
		}
		return output;
	}

	void ObjectList<PNormalObject>::Step()
	{
		for(NormalIterator it = this->obList.begin();
			it != this->obList.end(); it++)
			(*it)->Step();
	}

	void ObjectList<PNormalObject>::Draw()
	{
		for(NormalIterator it = this->obList.begin();
			it != this->obList.end(); it++)
			(*it)->Draw2D();
	}

	void ObjectList<PNormalObject>::Del()
	{	
		NormalIterator it = this->obList.begin();
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