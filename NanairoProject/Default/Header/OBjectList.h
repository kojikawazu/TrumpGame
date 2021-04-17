#ifndef MYGAME_OBJECTLIST_H
#define MYGAME_OBJECTLIST_H

///////////////////////////////
//std
#ifndef _LIST_
#include <list>
#endif

///////////////////////////////
//NanairoLib
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef MYDXCHARA_H
#include <Chara.h>
#endif

//------------------------------------------------
//
//キャラクターを管理しているクラス
//
//------------------------------------------------

namespace MYGAME
{
	enum CHAIN_TYPE
	{
		CHAIN_NONE, CHAIN_POSXY, CHAIN_POSX, CHAIN_POSY, 
	};

	typedef std::list<NanairoLib::PNormalObject> NormalList;
	typedef NormalList::iterator NormalIterator;

	//-----------------------------------------
	//オブジェクトリストをテンプレート化成功！
	//-----------------------------------------
	template<typename T>
	class ObjectList
	{
	private:
		int objSum;
		std::list<T> obList;

	public:
		
		ObjectList();
		~ObjectList();

		void Init();
		int Size();
		bool Empty();

		void Add(T add);
		void Insert(T add, int number);
		void Insert(T add, const T index);

		void ListClear();

		void Dispose(int number);
		void Dispose(T obj);
		T Unlink(int number);
		T Unlink(T obj);
	};

	//---------------------------------------------------
	//オブジェクトをリストで管理するクラス
	//テンプレートクラスから特殊化成功！
	//---------------------------------------------------
	template<> class ObjectList<NanairoLib::PNormalObject>
	{
	private:
		int objSum;
		NormalList obList;

	public:
		//Constracter
		ObjectList();
		~ObjectList();

		void Init();
		void Step();
		void Draw();
		void Del();

		int Size();
		bool Empty();

		//Iterator
		NormalIterator GetIterator(int number);
		NormalIterator GetIterator(NanairoLib::PNormalObject number);

		//Add
		void Add(NanairoLib::PNormalObject add);
		void Insert(NanairoLib::PNormalObject add, int number);
		void Insert(NanairoLib::PNormalObject add, NanairoLib::PCNormalObject index);

		//Clear
		void ListClear();

		//Dispose
		void Dispose(int number);
		void Dispose(NanairoLib::PNormalObject obj);
		
		//Unlink
		NanairoLib::PNormalObject Unlink(int number);
		NanairoLib::PNormalObject Unlink(NanairoLib::PNormalObject obj);

		//other
		NormalIterator Begin(){	return this->obList.begin();}
		NormalIterator End(){	return this->obList.end();	}
		NormalIterator Erase(NormalIterator& it){	return this->obList.erase( it );	}
	};
}

#endif