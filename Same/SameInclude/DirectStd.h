#ifndef _NanairoLib_STD_H
#define _NanairoLib_STD_H

//--------------------------------------
//std�n������
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
	//�K�{�A�C�e��
	//------------------------------------------------------------------------------------
	enum SORT_TYPE
	{
		SELECT_SORT, BUBBLE_SORT, INPUT_SORT, QUICK_SORT, 
	};

	//------------------------------------------------------------------------------------
	//����C�e���[�^
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
		//���ԎQ��
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
		//�P��֐i�߂�
		//---------------------------------------------------
		__IMPOETER Iterator& operator ++ ()
		{
			++point;
			return *this;
		}

		//---------------------------------------------------
		//��u�{�{�I�y���[�^
		//---------------------------------------------------
		__IMPOETER Iterator operator ++(int)
		{
			//���݂̈ʒu��ۑ����Ă���
			T* p = point;
			++(*this);
			return Iterator( p );
		}

		//---------------------------------------------------
		//�P�O�֐i�߂�
		//---------------------------------------------------
		__IMPOETER Iterator& operator -- ()
		{
			--point;
			return *this;
		}

		//---------------------------------------------------
		//��u�{�{�I�y���[�^
		//---------------------------------------------------
		__IMPOETER Iterator operator --(int)
		{
			//���݂̈ʒu��ۑ����Ă���
			T* p = point;
			--(*this);
			return Iterator( p );
		}

		//---------------------------------------------------
		//��r���Z�q
		//---------------------------------------------------
		__IMPOETER const bool operator != ( const Iterator& ite ) const 
		{
			//ite���I�[�̎��H
			if( ite.point == NULL || point == NULL )
				return false;
			return ( point != ite.point );
		}

		//---------------------------------------------------
		//��r���Z�q
		//---------------------------------------------------
		__IMPOETER const bool operator == ( const Iterator& ite ) const 
		{
			//ite���I�[�̎��H
			if( ite.point == NULL || point == NULL )
				return true;
			return ( point == ite.point );
		}

		//---------------------------------------------------
		//���Z���Z�q
		//---------------------------------------------------
		__IMPOETER Iterator operator + (int num)
		{
			return Iterator( point + num );
		}

		//---------------------------------------------------
		//���Z���Z�q
		//---------------------------------------------------
		__IMPOETER Iterator& operator += (int num)
		{
			point += num;
			return *this;
		}

		//---------------------------------------------------
		//���Z���Z�q
		//---------------------------------------------------
		__IMPOETER Iterator operator - (int num)
		{
			return Iterator( point - num );
		}

		//---------------------------------------------------
		//���Z���Z�q
		//---------------------------------------------------
		__IMPOETER Iterator& operator -= (int num)
		{
			point -= num;
			return *this;
		}

		//---------------------------------------------------
		//������\��
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
	//����������N���X
	//------------------------------------------------------------------------------------
	template<class T>
	class MyMemory
	{
	public:
		__IMPOETER MyMemory(){}
		__IMPOETER ~MyMemory(){}

		//---------------------------------------------------
		//�������̊m��
		//---------------------------------------------------
		__IMPOETER T* MemoryMalloc(UINT size = 1)
		{
			return new T[ size ];
		}

		//---------------------------------------------------
		//�z�񃁃����̍폜
		//---------------------------------------------------
		__IMPOETER void MemoryDestroy(T* _memory, UINT _size = 1 )
		{
			ES_SAFE_DELETE_ARRAY( _memory );
		}

		//---------------------------------------------------
		//�N���X�������̍폜
		//---------------------------------------------------
		__IMPOETER void MemoryDestroyOne(T* _memory)
		{
			ES_SAFE_DELETE( _memory );
		}

		//---------------------------------------------------
		//���������O������
		//---------------------------------------------------
		__IMPOETER void MemoryZero(T* _memory, UINT _size = 1 )
		{
			if( _memory != NULL && _size > 0)
				memset( _memory, 0, sizeof(T) * _size );
		}
	};

	//------------------------------------------------------------------------------------
	//����vector + �� �N���X
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
		//�f�R���n
		//---------------------------------------------------
		__IMPOETER MyArray() : _size(0)
		{
			_array = NULL;
		}

		__IMPOETER MyArray(UINT size) : _size(size)
		{
			::MyMemory<T> mr;
			_array = mr.MemoryMalloc( size );	//�z��̊m��;
		}

		__IMPOETER ~MyArray()
		{
			::MyMemory<T> mr;
			mr.MemoryDestroy( _array, _size );
			_size = 0;
		}

		//---------------------------------------------------
		//�z��̒�����Ԃ�
		//---------------------------------------------------
		__IMPOETER UINT Length()
		{
			return _size;
		}

		//---------------------------------------------------
		//�����̃f�[�^��\��
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
		//�����̃f�[�^�P�����\��
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
		//�傫���`�F���W
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
		//�z����Z�b�e�B���O
		//---------------------------------------------------
		__IMPOETER void SetArray(T lis[], UINT size)
		{
			if( _size < size )
				this->Resize( size );
			for(UINT i=0; i<size; i++)
				_array[i] = lis[i];
		}

		//---------------------------------------------------
		//�z��̒����N���A
		//---------------------------------------------------
		__IMPOETER void Clear()
		{
			this->DeleteArray();
		}

		//---------------------------------------------------
		//�z��͑��݂��Ă��邩
		//---------------------------------------------------
		__IMPOETER bool Empty()
		{
			return ( _size == 0 ? true : false );
		}
		
		//---------------------------------------------------
		//�z��̈�ԍŏ�
		//---------------------------------------------------
		__IMPOETER T* Begin()
		{
			return ( this->_array != NULL && this->_size > 0 ?
				&this->_array[0] : NULL );
		}

		//---------------------------------------------------
		//�z��̌���i�ʏ�͎Q�Ƃ��Ă͂Ȃ�Ȃ��ꏊ�������j
		//---------------------------------------------------
		__IMPOETER T* End()
		{
			return ( this->_array != NULL && this->_size > 0 ?
				&this->_array[ _size ] : NULL );
		}

		//-------------------------------------------------------
		//stl�ł̔z��v�b�V���o�b�N
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
		//stl�ł̃v�b�V���t�����g
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
		//stl�ł̃|�b�v
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
		//stl�ł̃C���T�[�g
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
		//stl�ł̃C���[�X
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
		//stl�ł̃Q�b�^�[
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
		//stl�ł̃X���b�v
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
		//stl�ł̃I�y���[�^
		//---------------------------------------------------
#pragma region �I�y���[�^
		//�z��I�y���[�^
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
		//stl�ł�vector�֕ϊ�
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
			//�������폜�֐�
			//---------------------------------------------------
			__IMPOETER void DeleteArray()
			{
				::MyMemory<T> mr;
				mr.MemoryDestroy( _array, _size );
				_size = 0;
			}
	};

	//------------------------------------------------------------------------------------
	//�X�R�[�v�h�|�C���^
	//------------------------------------------------------------------------------------
	template<class T>
	class MyScopedPointer
	{
	protected:
		const T point;

	public:
#pragma region �R���X�g���N�^
		__IMPOETER MyScopedPointer(const T in = 0) : point(in)
		{
			cout << in << "�𐶐�" << endl;
		}

		__IMPOETER ~MyScopedPointer()
		{
			if( point != NULL )
			{
				cout << point << "��j��" << endl;
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

#pragma region �|�C���^����
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

#pragma region �R�s�[�h�~
		__IMPOETER MyScopedPointer(const MyScopedPointer& point){}
		__IMPOETER MyScopedPointer& operator = (const MyScopedPointer& point){}
#pragma endregion

	};

	//------------------------------------------------------------------------------------
	//�V�F�[�A�[�h�|�C���^
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
		//�܂���x�|�C���^������
		//NULL����Ȃ���΃J�E���^�P
		//---------------------------------------------------
#pragma region �R���X�g���N�^
		__IMPOETER MySharedPointer(const T* in = NULL) : touchCnt( new int(0) ), threadLock( new bool(false) )
		{
			point = in;
			if( in != NULL )
			{
#if _DEBUG
				cout << in << "�𐶐�" << endl;
#endif
				this->touchIn();
			}
		}

		__IMPOETER MySharedPointer(const MySharedPointer<T>& in)
		{
			this->Copy( in );
			this->touchIn();
		}

		//�X�R�[�v�A�E�g
		__IMPOETER ~MySharedPointer()
		{
			this->Release();
			ES_SAFE_DELETE( touchCnt );
			ES_SAFE_DELETE( threadLock );
		}
#pragma endregion

#pragma region �I�y���[�^
		//�������(����܂łɓ����Ă����|�C���^����X�R�[�v�͂͂����)
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

		//�������(����܂łɓ����Ă����|�C���^����X�R�[�v�͂͂����)
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
			cout << "�Q�Ɖ񐔂� : " << *touchCnt << endl;
		}

		__IMPOETER void toStringValue()
		{
			cout << "�ێ�����Ă���l�� : ";
			if( point != NULL )
				cout << *point << endl;
			else
				cout << "����܂���ł���" << endl;
		}

		__IMPOETER T* GetPoint()
		{
			return ( point != NULL ? (T*)point : NULL );
		}
#pragma endregion

#pragma region �|�C���^����
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
				cout << p << "�𐶐�" << endl;
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
	//�\�[�g�N���X
	//------------------------------------------------------------------------------------
	template<class T>
	class Sorter
	{
	private:
		bool (*func)(T&, T&);

		/*
			//�ȉ��̂悤�Ȋ֐��������Sorting�֐����ĂԂƂ��ɓn���Ă�������
			bool Sort(int& ar1, int& ar2)
			{
				return ( ar1 < ar2 ? true : false );
			}
		*/
	public:
		//---------------------------------------------------
		//�������̌ĂԂ��ƂɂȂ�
		//---------------------------------------------------
		__IMPOETER void Sorting(T* begin, T* end, bool (*function)(T&, T&), SORT_TYPE type = SELECT_SORT )
		{
			func = function;
			switch( type )
			{
				case BUBBLE_SORT:	//�o�u���\�[�g
					BubbleSort( begin, end );
					break;
				case INPUT_SORT:	//�}���\�[�g
					InputSort( begin, end );
					break;
				case QUICK_SORT:	//�N�C�b�N�\�[�g
					QuickSort( begin, end );
					break;
				case SELECT_SORT:	//�ʏ�͑I���\�[�g
				default:
					SelectSort( begin, end );
					break;
			}
		}
	private:	
		
		//---------------------------------------------------
		//���X�g�̃T�C�Y�𓾂�
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
		//���X�g�̕�����\��
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
		//�o�u���\�[�g
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
		//�I���\�[�g
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
		//�}���\�[�g
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
		//�N�C�b�N�\�[�g
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
	//�X���b�h�N���X
	//------------------------------------------------------------------------------------
	class MyThread
	{
	public:
		DWORD ID;
		HANDLE handle;

	public:
		//---------------------------------------------------
		//�f�R���n
		//---------------------------------------------------
		__IMPOETER MyThread() : ID(0), handle(0){}
		__IMPOETER ~MyThread()
		{
			this->CloSethread();
		}

		//---------------------------------------------------
		//�X���b�h�̐���
		//---------------------------------------------------
		//@in : �Ăяo�������֐��|�C���^
		__IMPOETER bool CreateThread( void (*func)() )
		{
			this->handle = ::CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) func, 
				(LPVOID)0, 0, &this->ID );
			return true;
		}

		//---------------------------------------------------
		//�X���b�h���H
		//---------------------------------------------------
		//@in true(����) false(���s)
		__IMPOETER bool NowThread()
		{
			DWORD word;
			::GetExitCodeThread( this->handle, &word );
			return ( word == STILL_ACTIVE ? true : false );
		}

		//---------------------------------------------------
		//�X���b�h�̏I��
		//---------------------------------------------------
		__IMPOETER void CloSethread()
		{
			::CloseHandle( handle );
		}
	};

	//------------------------------------------------------------------------------------
	//������N���X
	//------------------------------------------------------------------------------------
	class StringList
	{
	public:
		std::vector<std::string> _list;
	
		//------------------------
		//�ǉ�
		//------------------------
		__IMPOETER void InputList( std::string in )
		{
			_list.push_back( in );
		}

		//---------------------------------------------
		//�\��
		//---------------------------------------------
		__IMPOETER void showList()
		{
			std::cout << "�A������ : ";
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