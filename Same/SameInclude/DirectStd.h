#ifndef _NanairoLib_STD_H
#define _NanairoLib_STD_H

//--------------------------------------
//std系を自作
//--------------------------------------
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _IOSTREAM_
#include <iostream>
#endif

namespace NanairoLib
{
	//------------------------------------------------------------------------------------
	//必須アイテム
	//------------------------------------------------------------------------------------
	enum SORT_TYPE
	{
		SELECT_SORT, BUBBLE_SORT, INPUT_SORT, QUICK_SORT, 
	};

	//------------------------------------------------------------------------------------
	//自作イテレータ
	//------------------------------------------------------------------------------------
	template<class T>
	class Iterator
	{
	private:
		T* point;

	public:
		__IMPOETER Iterator() : point(NULL){}
		__IMPOETER Iterator(T* begin) : point(begin){}

	public:
		__IMPOETER T* GetPoint()
		{
			return point;
		}

		//---------------------------------------------------
		//実態参照
		//---------------------------------------------------
		__IMPOETER T& operator *()
		{
			return *point;
		}

		__IMPOETER T* operator -> ()
		{
			return point;
		}

		//---------------------------------------------------
		//１つ先へ進める
		//---------------------------------------------------
		__IMPOETER Iterator& operator ++ ()
		{
			++point;
			return *this;
		}

		//---------------------------------------------------
		//後置＋＋オペレータ
		//---------------------------------------------------
		__IMPOETER Iterator operator ++(int)
		{
			//現在の位置を保存しておく
			T* p = point;
			++(*this);
			return Iterator( p );
		}

		//---------------------------------------------------
		//１つ前へ進める
		//---------------------------------------------------
		__IMPOETER Iterator& operator -- ()
		{
			--point;
			return *this;
		}

		//---------------------------------------------------
		//後置＋＋オペレータ
		//---------------------------------------------------
		__IMPOETER Iterator operator --(int)
		{
			//現在の位置を保存しておく
			T* p = point;
			--(*this);
			return Iterator( p );
		}

		//---------------------------------------------------
		//比較演算子
		//---------------------------------------------------
		__IMPOETER const bool operator != ( const Iterator& ite ) const 
		{
			//iteが終端の時？
			if( ite.point == NULL || point == NULL )
				return false;
			return ( point != ite.point );
		}

		//---------------------------------------------------
		//比較演算子
		//---------------------------------------------------
		__IMPOETER const bool operator == ( const Iterator& ite ) const 
		{
			//iteが終端の時？
			if( ite.point == NULL || point == NULL )
				return true;
			return ( point == ite.point );
		}

		//---------------------------------------------------
		//加算演算子
		//---------------------------------------------------
		__IMPOETER Iterator operator + (int num)
		{
			return Iterator( point + num );
		}

		//---------------------------------------------------
		//加算演算子
		//---------------------------------------------------
		__IMPOETER Iterator& operator += (int num)
		{
			point += num;
			return *this;
		}

		//---------------------------------------------------
		//減算演算子
		//---------------------------------------------------
		__IMPOETER Iterator operator - (int num)
		{
			return Iterator( point - num );
		}

		//---------------------------------------------------
		//減算演算子
		//---------------------------------------------------
		__IMPOETER Iterator& operator -= (int num)
		{
			point -= num;
			return *this;
		}

		//---------------------------------------------------
		//文字列表示
		//---------------------------------------------------
		__IMPOETER void ToChar()
		{
			if( point != NULL )
				cout << "Data is " << *point;
			else
				cout << "DataNone";
			cout << endl;
		}

	};
	
	//------------------------------------------------------------------------------------
	//メモリ制御クラス
	//------------------------------------------------------------------------------------
	template<class T>
	class MyMemory
	{
	public:
		__IMPOETER MyMemory(){}
		__IMPOETER ~MyMemory(){}

		//---------------------------------------------------
		//メモリの確保
		//---------------------------------------------------
		__IMPOETER T* MemoryMalloc(UINT size = 1)
		{
			return new T[ size ];
		}

		//---------------------------------------------------
		//配列メモリの削除
		//---------------------------------------------------
		__IMPOETER void MemoryDestroy(T* _memory, UINT _size = 1 )
		{
			ES_SAFE_DELETE_ARRAY( _memory );
		}

		//---------------------------------------------------
		//クラスメモリの削除
		//---------------------------------------------------
		__IMPOETER void MemoryDestroyOne(T* _memory)
		{
			ES_SAFE_DELETE( _memory );
		}

		//---------------------------------------------------
		//メモリを０初期化
		//---------------------------------------------------
		__IMPOETER void MemoryZero(T* _memory, UINT _size = 1 )
		{
			if( _memory != NULL && _size > 0)
				memset( _memory, 0, sizeof(T) * _size );
		}
	};

	//------------------------------------------------------------------------------------
	//自作vector + α クラス
	//------------------------------------------------------------------------------------
	template<class T>
	class MyArray
	{
	private:
		T* _array;
		UINT _size;

	public:
		static const int VALUE_NONE = -1;

	public:
		//---------------------------------------------------
		//デコン系
		//---------------------------------------------------
		__IMPOETER MyArray() : _size(0)
		{
			_array = NULL;
		}

		__IMPOETER MyArray(UINT size) : _size(size)
		{
			::MyMemory<T> mr;
			_array = mr.MemoryMalloc( size );	//配列の確立;
		}

		__IMPOETER ~MyArray()
		{
			::MyMemory<T> mr;
			mr.MemoryDestroy( _array, _size );
			_size = 0;
		}

		//---------------------------------------------------
		//配列の長さを返す
		//---------------------------------------------------
		__IMPOETER UINT Length()
		{
			return _size;
		}

		//---------------------------------------------------
		//内部のデータを表示
		//---------------------------------------------------
		__IMPOETER void ToString()
		{
			if( _size > 0 )
			{
				cout << "value :";
				for(UINT i=0; i<_size; i++)
					cout << _array[i] << " ";
				cout << "size : " << _size << endl;
			}
			else
				cout << "Data none " << endl;
		}

		//---------------------------------------------------
		//内部のデータ１つだけ表示
		//---------------------------------------------------
		__IMPOETER void ToChar(UINT num)
		{
			cout << "number : " << num << "is ";
			if( _array != NULL && _size >= 0 && num >= 0 && num < _size)
				cout << _array[ num ] << " " << endl;
			else
				cout << "None" << endl;
		}

		//---------------------------------------------------
		//大きさチェンジ
		//---------------------------------------------------
		__IMPOETER UINT Resize(UINT size)
		{
			if( _array != NULL )
			{
				if( size > 0 )
				{
					::MyMemory<T> mr;

					T* temp = mr.MemoryMalloc( size );

					for(UINT i=0; i<_size && i<size; i++)
						temp[i] = _array[i];

					mr.MemoryDestroy( _array, _size );
					_size = size;
					_array = temp;
				}
				else
					this->DeleteArray();
			}
			else
			{
				if( size > 0 )
				{
					_array = new T[size];
					_size = size;
				}
				else
					_size = 0;
			}
			return _size;
		}

		//---------------------------------------------------
		//配列をセッティング
		//---------------------------------------------------
		__IMPOETER void SetArray(T lis[], UINT size)
		{
			if( _size < size )
				this->Resize( size );
			for(UINT i=0; i<size; i++)
				_array[i] = lis[i];
		}

		//---------------------------------------------------
		//配列の中をクリア
		//---------------------------------------------------
		__IMPOETER void Clear()
		{
			this->DeleteArray();
		}

		//---------------------------------------------------
		//配列は存在しているか
		//---------------------------------------------------
		__IMPOETER bool Empty()
		{
			return ( _size == 0 ? true : false );
		}
		
		//---------------------------------------------------
		//配列の一番最初
		//---------------------------------------------------
		__IMPOETER T* Begin()
		{
			return ( this->_array != NULL && this->_size > 0 ?
				&this->_array[0] : NULL );
		}

		//---------------------------------------------------
		//配列の語尾（通常は参照してはならない場所を示す）
		//---------------------------------------------------
		__IMPOETER T* End()
		{
			return ( this->_array != NULL && this->_size > 0 ?
				&this->_array[ _size ] : NULL );
		}

		//-------------------------------------------------------
		//stl版の配列プッシュバック
		//---------------------------------------------------
#pragma region push_back
		__IMPOETER UINT Push_back(T value)
		{
			if( _array != NULL )
			{
				this->Resize( this->_size + 1);
				_array[ this->_size - 1 ] = value;
			}
			else
			{
				this->Resize( 1 );
				_array[0] = value;
			}

			return _size;
		}

		__IMPOETER UINT Push_back(T value[], UINT size)
		{
			if( _array != NULL )
			{
				int temp = this->_size;
				this->Resize( this->_size + size);
				for(UINT i=temp, cnt = 0; i<this->_size; i++, cnt++)
					_array[i] = value[cnt];
			}
			else
			{
				this->Resize( size );
				for(int i=0; i<size; i++)
					_array[i] = value[i];
			}

			return _size;
		}
#pragma endregion

		//-------------------------------------------------------
		//stl版のプッシュフロント
		//---------------------------------------------------
#pragma region push_front
		__IMPOETER UINT Push_front(T value)
		{
			if( _array != NULL )
			{
				::MyMemory<T> mr;
				T* temp = mr.MemoryMalloc( _size + 1 );

				temp[0] = value;
				for(UINT i=0; i<_size; i++)
					temp[i+1] = _array[i];

				mr.MemoryDestroy( _array, _size );
				_size++;
				_array = temp;
			}
			else
			{
				this->Resize( 1 );
				_array[0] = value;
			}
			return _size;
		}

		__IMPOETER UINT Push_front(T value[], UINT size)
		{
			if( _array != NULL )
			{
				::MyMemory<T> mr;
				T* temp = mr.MemoryMalloc( _size + size );

				for(UINT i=0; i<size; i++)
					temp[i] = value[i];

				int cnt = 0;
				for(UINT i=size; i<_size + _size; i++, cnt++)
					temp[i] = _array[cnt];

				mr.MemoryDestroy( _array, _size ); 
				_size += size;
				_array = temp;
			}
			else
			{
				this->Resize( size );
				for(int i=0; i<size; i++)
					_array[i] = value[i];
			}
			return _size;
		}
#pragma endregion

		//-------------------------------------------------------
		//stl版のポップ
		//---------------------------------------------------
#pragma region pop
		__IMPOETER UINT Pop_back()
		{
			if( _array != NULL && _size > 0)
			{
				if( _size == 1)
					this->DeleteArray();
				else
					this->Resize( this->_size - 1);
			}
			return _size;
		}

		__IMPOETER UINT pop_front()
		{
			if( _array != NULL && _size > 0 )
			{
				for(UINT i=1;i<_size; i++)
					_array[i-1] = _array[i];
				this->Resize( this->_size - 1);
			}
			return _size;
		}
#pragma endregion
		//-------------------------------------------------------
		//stl版のインサート
		//---------------------------------------------------
#pragma region insert
		__IMPOETER UINT Insert(T value, int num)
		{
			if( _array != NULL )
			{
				::MyMemory<T> mr;
				T* temp = mr.MemoryMalloc( _size + 1 );

				int plus = 0;
				for(UINT i=0; i<_size+1; i++){
					if( i == num && plus == 0)
					{
						temp[i] = value;
						plus++;
						continue;
					}
					temp[i] = _array[i-plus];
				}

				mr.MemoryDestroy( _array, _size );
				_size++;
				_array = temp;
			}
			return _size;
		}

		__IMPOETER UINT Insert(T value[], int num, UINT size)
		{
			if( _array != NULL )
			{
				::MyMemory<T> mr;
				T* temp = mr.MemoryMalloc( _size + size );

				int plus = 0;
				for(UINT i=0; i<_size; i++){
					if( i == num && plus == 0)
					{
						for(UINT j=0; j<size; j++)
						{
							temp[i + j] = value[j];
							plus++;
						}
						temp[i + plus] = _array[i];
						continue;
					}
					temp[i + plus] = _array[i];
				}
				mr.MemoryDestroy( _array, _size );
				_size += size;
				_array = temp;
			}
			return _size;
		}
#pragma endregion
		//-------------------------------------------------------
		//stl版のイレース
		//---------------------------------------------------
#pragma region Erase
		__IMPOETER UINT Erase(T& value)
		{
			UINT number = this->GetNumber( value );
			if( number != VALUE_NONE )
			{
				for(UINT i=number; i<_size - 1; i++)
					_array[i] = _array[i+1];
				this->Resize( _size - 1 );
				return number;
			}
			return VALUE_NONE;
		}

		__IMPOETER T Erase(UINT num)
		{
			T type = this->GetArrayValue( num );
			if( type != VALUE_NONE )
			{
				for(UINT i=num; i<_size - 1; i++)
					_array[i] = _array[i+1];
				this->Resize( _size - 1 );
				return type;
			}
			return VALUE_NONE;
		}
#pragma endregion
		//-------------------------------------------------------
		//stl版のゲッター
		//---------------------------------------------------
#pragma region Getter
		__IMPOETER UINT GetNumber(T& value)
		{
			if( _array != NULL )
			{
				for(UINT i=0; i<_size; i++)
				{
					if( _array[i] == value )
						return i;
				}
			}

			return VALUE_NONE;
		}

		__IMPOETER T GetArrayValue(UINT num)
		{
			if( _array != NULL )
			{
				for(UINT i=0; i<_size; i++)
				{
					if( i == num )
						return _array[i];
				}
			}

			return VALUE_NONE;
		}

		__IMPOETER T* GetArray()
		{
			return _array;
		}
#pragma endregion
		//-------------------------------------------------------
		//stl版のスワップ
		//---------------------------------------------------
#pragma region swap
		__IMPOETER UINT Swap(T* list, UINT size )
		{
			::MyMemory<T> mr;
			T* _ar = mr.MemoryMalloc( _size );
			for(UINT i=0; i<_size; i++)
				_ar[i] = _array[i];
			this->Resize( size );
			for(UINT i=0; i<size; i++)
			{
				_array[i] = list[i];
				list[i] = _ar[i];
			}
			mr.MemoryDestroy( _ar );
			return _size;
		}

		__IMPOETER UINT Swap(MyArray<T>& list )
		{
			::MyMemory<T> mr;
			T* _ar1 = mr.MemoryMalloc( _size );
			UINT ar1Siz = _size;
			for(UINT i=0; i<ar1Siz; i++)
				_ar1[i] = _array[i];

			UINT ar2Siz = list.Length();
			T* _ar2 = list.GetArray();

			this->Resize( ar2Siz );
			for(UINT i=0; i<ar2Siz; i++)
				_array[i] = _ar2[i];

			list.Resize( ar1Siz );
			_ar2 = list.GetArray();
			for(UINT i=0; i<ar1Siz; i++)
				_ar2[i] = _ar1[i];

			mr.MemoryDestroy( _ar1 );
			return _size;
		}
#pragma endregion
		//-------------------------------------------------------
		//stl版のオペレータ
		//---------------------------------------------------
#pragma region オペレータ
		//配列オペレータ
		__IMPOETER T& operator[](UINT num)
		{
			return _array[num];
		}

		__IMPOETER void operator += (T& value)
		{
			this->push_back( value );
		}

		__IMPOETER void operator -= (T& value)
		{	
			this->Erase( value );
		}

		__IMPOETER void operator = (MyArray<T>& _ar)
		{
			this->SetArray( _ar.GetArray(), _ar.Length() );
		}
#pragma endregion

		
		//-------------------------------------------------------
		//stl版のvectorへ変換
		//---------------------------------------------------
#ifdef _STD_VECTOR
		__IMPOETER std::vector<T> GetVector()
		{
			std::vector<T> vec;
			::Iterator<T> it = this->Begin();
			while( it != this->End() )
			{
				vec.push_back( *it.GetPoint() );
				it++;
			}
			return vec;
		}
#endif

		private:
			//---------------------------------------------------
			//メモリ削除関数
			//---------------------------------------------------
			__IMPOETER void DeleteArray()
			{
				::MyMemory<T> mr;
				mr.MemoryDestroy( _array, _size );
				_size = 0;
			}
	};

	//------------------------------------------------------------------------------------
	//スコープドポインタ
	//------------------------------------------------------------------------------------
	template<class T>
	class MyScopedPointer
	{
	protected:
		const T point;

	public:
#pragma region コンストラクタ
		__IMPOETER MyScopedPointer(const T in = 0) : point(in)
		{
			cout << in << "を生成" << endl;
		}

		__IMPOETER ~MyScopedPointer()
		{
			if( point != NULL )
			{
				cout << point << "を破棄" << endl;
				this->Destroy();
			}
		}
#pragma endregion

#pragma region Getter
		__IMPOETER T GetPoint()
		{
			return ( point != NULL ? (T*)point : NULL );
		}
#pragma endregion

#pragma region operator
		__IMPOETER T operator -> ()
		{
			return point;
		}

		__IMPOETER const bool operator == (T arPoint)
		{
			return (point == arPoint);
		}

		__IMPOETER const bool operator != (T arPoint)
		{
			return (point != arPoint);
		}
#pragma endregion

#pragma region ポインタ制御
		__IMPOETER void Release()
		{
			if( point != NULL )
				this->Destroy();
		}

		__IMPOETER void NewPointer(T p)
		{
			this->Destroy();
			point = p;
		}

		__IMPOETER void ReSet(T in = NULL)
		{
			if( in == NULL )
			{
				if( point != NULL )
					this->Destroy();
			}
			else
				this->NewPointer( in );
		}
#pragma endregion
	
	private:
		__IMPOETER void Destroy()
		{
			::MyMemory<T> mr;
			mr.MemoryDestroyOne( point );
		}

#pragma region コピー防止
		__IMPOETER MyScopedPointer(const MyScopedPointer& point){}
		__IMPOETER MyScopedPointer& operator = (const MyScopedPointer& point){}
#pragma endregion

	};

	//------------------------------------------------------------------------------------
	//シェーアードポインタ
	//------------------------------------------------------------------------------------
	template<class T>
	class MySharedPointer
	{
	private:
		const T* point;
		int* touchCnt;
		bool* threadLock;

	public:
		//---------------------------------------------------
		//まず一度ポインタを入れる
		//NULLじゃなければカウンタ１
		//---------------------------------------------------
#pragma region コンストラクタ
		__IMPOETER MySharedPointer(const T* in = NULL) : touchCnt( new int(0) ), threadLock( new bool(false) )
		{
			point = in;
			if( in != NULL )
			{
#if _DEBUG
				cout << in << "を生成" << endl;
#endif
				this->touchIn();
			}
		}

		__IMPOETER MySharedPointer(const MySharedPointer<T>& in)
		{
			this->Copy( in );
			this->touchIn();
		}

		//スコープアウト
		__IMPOETER ~MySharedPointer()
		{
			this->Release();
			ES_SAFE_DELETE( touchCnt );
			ES_SAFE_DELETE( threadLock );
		}
#pragma endregion

#pragma region オペレータ
		//代入あり(それまでに入っていたポインタからスコープははずれる)
		__IMPOETER MySharedPointer& operator = (MySharedPointer& point)
		{
			T* tempPoint = point.GetPoint();
			if( tempPoint == NULL || tempPoint == this->point )
				return *this;

			this->Release();
			
			this->Copy( point );
			point.touchIn();

			return *this;
		}

		//代入あり(それまでに入っていたポインタからスコープははずれる)
		__IMPOETER MySharedPointer& operator = (const MySharedPointer* point)
		{
			this->Release();

			this->Copy( *point );
			point.touchIn();

			return *this;
		}
#pragma endregion
		
#pragma region Getter
		__IMPOETER int* IsTouchCnter(){	return this->touchCnt;	}
		__IMPOETER bool* GetThreadLock(){	return this->threadLock;}
		
		__IMPOETER void ToStringCnter()
		{
			cout << "参照回数は : " << *touchCnt << endl;
		}

		__IMPOETER void toStringValue()
		{
			cout << "保持されている値は : ";
			if( point != NULL )
				cout << *point << endl;
			else
				cout << "ありませんでした" << endl;
		}

		__IMPOETER T* GetPoint()
		{
			return ( point != NULL ? (T*)point : NULL );
		}
#pragma endregion

#pragma region ポインタ制御
		__IMPOETER void Release()
		{
			if( *this->touchCnt > 0)
			{
				this->touchOut();
				this->unLock();
				
				if( *touchCnt == 0 && point != NULL )
				{
					ES_SAFE_DELETE( point );
					ES_SAFE_DELETE( touchCnt );
					ES_SAFE_DELETE( threadLock );
				}

				this->point = NULL;
				this->touchCnt = new int(0);
				this->threadLock = new bool(false);
			}
		}

		__IMPOETER void NewPointer(T* p)
		{
			this->Destroy();
			point = p;
			this->touchIn();
#if _DEBUG
			if( p != NULL )
				cout << p << "を生成" << endl;
#endif
		}

		__IMPOETER void ReSet(T* in = NULL)
		{
			if( in == NULL )
			{
				if( point != NULL )
					this->Destroy();
			}
			else
				this->NewPointer( in );
		}
#pragma endregion

		__IMPOETER bool IsThreadLock(){	return (*this->threadLock);	}
		__IMPOETER void Lock(){			(*this->threadLock) = true;		}
		__IMPOETER void UnLock(){			(*this->threadLock) = false;	}
	private:
		__IMPOETER void TouchIn(){		(*this->touchCnt)++;		}
		__IMPOETER void TouchOut(){	(*this->touchCnt)--;		}
		__IMPOETER void Destroy()
		{
			MyMemory<T> mr;
			if( *touchCnt > 0 )
			{
				mr.MemoryDestroyOne( (T*)point );
				point = NULL;
				(*touchCnt)--;
				(*this->threadLock) = false;
			}
		}

		__IMPOETER void Copy(const MySharedPointer<T>& in)
		{
			point = ((MySharedPointer<T>&)in).GetPoint();

			ES_SAFE_DELETE ( touchCnt );
			ES_SAFE_DELETE( threadLock );

			touchCnt = ((MySharedPointer<T>&)in).isTouchCnter();
			threadLock = ((MySharedPointer<T>&)in).GetThreadLock();
		}
	};
	
	//------------------------------------------------------------------------------------
	//ソートクラス
	//------------------------------------------------------------------------------------
	template<class T>
	class Sorter
	{
	private:
		bool (*func)(T&, T&);

		/*
			//以下のような関数を作ってSorting関数を呼ぶときに渡してください
			bool Sort(int& ar1, int& ar2)
			{
				return ( ar1 < ar2 ? true : false );
			}
		*/
	public:
		//---------------------------------------------------
		//ここを大体呼ぶことになる
		//---------------------------------------------------
		__IMPOETER void Sorting(T* begin, T* end, bool (*function)(T&, T&), SORT_TYPE type = SELECT_SORT )
		{
			func = function;
			switch( type )
			{
				case BUBBLE_SORT:	//バブルソート
					BubbleSort( begin, end );
					break;
				case INPUT_SORT:	//挿入ソート
					InputSort( begin, end );
					break;
				case QUICK_SORT:	//クイックソート
					QuickSort( begin, end );
					break;
				case SELECT_SORT:	//通常は選択ソート
				default:
					SelectSort( begin, end );
					break;
			}
		}
	private:	
		
		//---------------------------------------------------
		//リストのサイズを得る
		//---------------------------------------------------
		__IMPOETER UINT GetListSum( T* begin, T* end )
		{
			Iterator<T> before;
			UINT cnter = 0;

			before = begin;
			while( before != end )
			{
				cnter++;
				before++;
			}
			return cnter;
		}
		
		//---------------------------------------------------
		//リストの文字列表示
		//---------------------------------------------------
		__IMPOETER void ToString( T* begin, T* end )
		{
			Iterator<T> before;
			before = begin;
			cout << "value : ";
			while( begin != end )
			{
				cout << *begin << " ";
				begin++;
			}
			cout << endl;
		}
	private:
		//---------------------------------------------------
		//バブルソート
		//---------------------------------------------------
		__IMPOETER void BubbleSort( T* begin, T* end )
		{
			Iterator<T> before, after = begin, temp, temp2;
			T tm;

			before = after++;
			while( after != end )
			{
				temp = end - 1;
				temp2 = temp - 1;
				while( temp != before )
				{
					if( func( *temp2, *temp ) )
					{
						tm = *temp;
						*temp = *temp2;
						*temp2 = tm;
					}
					temp--;
					temp2--;
				}
				before = after++;
			}
		}

		//---------------------------------------------------
		//選択ソート
		//---------------------------------------------------
		__IMPOETER void SelectSort( T* begin, T* end )
		{
			Iterator<T> before, after = begin, temp, temp2;
			T tm;

			before = after++;
			while( after != end )
			{
				temp = before;
				temp2 = after;
				while( temp2 != end )
				{
					if( func( *temp, *temp2 ) )
						temp = temp2;
					temp2++;
				}

				if( temp != before )
				{
					tm = *before;
					*before = *temp;
					*temp = tm;
				}
				before = after++;
			}
		}

		//---------------------------------------------------
		//挿入ソート
		//---------------------------------------------------
		__IMPOETER void InputSort( T* begin, T* end )
		{
			Iterator<T> before, after, temp, temp2;
			T tm;

			before = begin + 1;
			while( before != end )
			{
				temp = before;
				temp2 = begin;
				tm = *temp;
				while( temp != temp2 )
				{
					if( func( *temp2, *temp ) )
					{
						while( temp2 != temp )
						{
							*temp = *( temp - 1 );
							temp--;
						}
						*temp2 = tm;
						break;
					}
					temp2++;
				}
				before++;
			}
		}

		//---------------------------------------------------
		//クイックソート
		//---------------------------------------------------
		__IMPOETER void QuickSort( T* begin, T* end)
		{
			if( begin == end )
				return ;

			Iterator<T> before, after, pit;
			UINT pivot = this->GetListSum( begin, end );
			T tm;
			before = begin;
			after = end - 1;
			pit = begin + (UINT)(pivot * 0.5f);
			//0 1 2 3 5
			while( before != after )
			{
				while( before != pit )
				{
					if( func( *before, *pit ) )
						break;
					before++;
				}

				while( after != pit )
				{
					if( func( *pit, *after ) )
						break;
					after--;
				}

				if( before != after )
				{
					tm = *before;
					*before = *after;
					*after = tm;

					before = begin;
					after = end - 1;
				}
			}
			if( pivot == 1)
				return ;

			before = pit;
			after = pit + 1;
			//this->toString( begin, end );
			//this->QuickSort( begin, before.GetPoint() );
			//this->QuickSort( after.GetPoint(), end );
		}

	};

	//------------------------------------------------------------------------------------
	//スレッドクラス
	//------------------------------------------------------------------------------------
	class MyThread
	{
	public:
		DWORD ID;
		HANDLE handle;

	public:
		//---------------------------------------------------
		//デコン系
		//---------------------------------------------------
		__IMPOETER MyThread() : ID(0), handle(0){}
		__IMPOETER ~MyThread()
		{
			this->CloSethread();
		}

		//---------------------------------------------------
		//スレッドの生成
		//---------------------------------------------------
		//@in : 呼び出したい関数ポインタ
		__IMPOETER bool CreateThread( void (*func)() )
		{
			this->handle = ::CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) func, 
				(LPVOID)0, 0, &this->ID );
			return true;
		}

		//---------------------------------------------------
		//スレッド中？
		//---------------------------------------------------
		//@in true(成功) false(失敗)
		__IMPOETER bool NowThread()
		{
			DWORD word;
			::GetExitCodeThread( this->handle, &word );
			return ( word == STILL_ACTIVE ? true : false );
		}

		//---------------------------------------------------
		//スレッドの終了
		//---------------------------------------------------
		__IMPOETER void CloSethread()
		{
			::CloseHandle( handle );
		}
	};

	//------------------------------------------------------------------------------------
	//文字列クラス
	//------------------------------------------------------------------------------------
	class StringList
	{
	public:
		std::vector<std::string> _list;
	
		//------------------------
		//追加
		//------------------------
		__IMPOETER void InputList( std::string in )
		{
			_list.push_back( in );
		}

		//---------------------------------------------
		//表示
		//---------------------------------------------
		__IMPOETER void showList()
		{
			std::cout << "連結文字 : ";
			unsigned int _size = _list.size();
			for(unsigned int cnt=0; cnt<_size; cnt++)
			{
				std::cout << _list[ cnt ];
			}
			std::cout << std::endl;
		}

		__IMPOETER void deleteList()
		{
			_list.clear();
		}
	};
}

#endif