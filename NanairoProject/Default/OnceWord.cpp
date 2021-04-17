#pragma once

#include <DirectParts.h>
#include <Resourcefactory.h>
#include <OnceWord.h>
#include <RoaderFile.h>
using namespace NanairoLib;
using namespace std;

namespace MYGAME
{
	OnceWord::OnceWord(LPCSTR ch)
	{
		this->sameInit();
		parts.word = (LPSTR)ch;
	}

	OnceWord::~OnceWord(){}

	void OnceWord::sameInit()
	{
		parts.isUpdate = parts.isDraw = true;
		parts.pos.SetMinVector();
		parts.ang = 0.0f;
		parts.scale.SetMinVector();
		parts.color.SetMaxColor();
	}

	void OnceWord::SetObject(PCVector2 ps, float ag, PCVector2 sc)
	{
		parts.pos = ps;
		parts.ang = ag;
		parts.scale = sc;
	}

	void OnceWord::loadParts(std::ifstream& fs)
	{
		char letter[256];
		std::string str, answer;
		int index = 0, size = 0;
		LoaderFunction func;

		while( !fs.eof() && !fs.fail() )
		{
			//文字の取得
			fs.getline( letter, sizeof(letter) );
			str = letter;
			size = str.size();
			
			//コメントや終了文字の合図
			if( size <= 2)
				continue;
			else if( func.checkComment_or_finish( str ) )
				break;
			this->readParts( str );
		}
	}

	void OnceWord::readParts(std::string& str)
	{
		int index = 0, size = str.size();
		MYGAME::LoaderFunction func;
		std::string answer;

		//背景の名前取り出し
		if( (index = func.isObject(str, "Name")) != -1 )
		{
			answer = str.substr( index + 1, size - index - 1 );
			this->SetWord( (LPCTSTR)answer.c_str() );
		}
		//名前の位置や角度、スケール取り出し
		else if( (index = func.isObject( str, "Object")) != -1 )
		{
			answer = str.substr( index + 1, size - index - 1 );
			this->splitParts( answer );
		}
	}

	void OnceWord::splitParts(std::string& str)
	{
		float *pass[] = 
			{	&this->parts.pos.x, 
				&this->parts.pos.y,
				&this->parts.ang, 
				&this->parts.scale.x, 
				&this->parts.scale.y 
			};

		string::size_type type = str.find_first_of(",");
		int oldIndex = 0, size = 5, cnter = 0;
		while( cnter < size && type != string::npos )
		{
			(*pass[cnter]) = (float)atof( str.substr( oldIndex, 
							type - oldIndex - 1).c_str() );

			oldIndex = type + 1;
			type = str.find(",", type + 1 );
			cnter++;
		}
	}

	//----------------------------------------------------------------------
	DefaultWord::DefaultWord(LPCSTR ch)
	{
		this->sameInit();
		this->parts.word = (LPSTR)ch;
	}

	void DefaultWord::Draw()
	{
		MYGAME::Text2DFactory* gh = MYGAME::__GRAPHFACTORY;
		gh->drawString2D( (char*)this->parts.word.c_str(), parts.pos,
			this->parts.scale.x, parts.ang, parts.color.color );
	}

	//--------------------------------------------------------------------------
	GraphWord::GraphWord(LPCSTR ch)
	{
		this->sameInit();
		this->parts.word = (LPSTR)ch;
	}

	void GraphWord::Draw2D()
	{
		MYGAME::Text2DFactory* gh = MYGAME::__GRAPHFACTORY;
		gh->draw_SetTrans( this->parts.pos, 
			this->parts.scale, this->parts.ang,
			this->parts.word, 2, this->parts.color.color );
		gh->draw_graph();
	}

	//--------------------------------------------------------------------------
	OnceWord* ObjectList<OnceWord*>::GetWord(int number)
	{
		int cnter = 0;
		WordIterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( cnter == number )
			{
				OnceWord* wh = (OnceWord*)(*it);
				return wh;
			}
			else
				it++;
		}
		return NULL;
	}
	
	void ObjectList<OnceWord*>::Clear()
	{
		WordIterator it = this->list.begin();
		while( it != this->list.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->list.erase( it );
		}
	}

	void ObjectList<OnceWord*>::Step()
	{
		WordIterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( (*it)->parts.isUpdate )
				(*it)->Step();
			it++;
		}
	}

	void ObjectList<OnceWord*>::ChainStep(CHAIN_TYPE type)
	{
		WordIterator it = this->list.begin(), old;
		NanairoLib::UIParts2D off1, off2;
		int count = 0;
		while( it != this->list.end() )
		{
			if( count == 0 )
			{
				off1 = (*it)->parts;
				(*it)->Step();
			}
			else if( count != 0 )
			{
				off2 = (*it)->parts;
				(*it)->parts.pos.y = off1.pos.y;
				(*it)->parts.ang = off1.ang;
				(*it)->parts.scale = (Vector2)off1.scale;
				switch( type )
				{
					case CHAIN_POSX:	(*it)->parts.pos.x = off1.pos.x;	break;
					case CHAIN_POSY:	(*it)->parts.pos.y = off1.pos.y;	break;
					case CHAIN_POSXY:	
						(*it)->parts.pos.x = off1.pos.x;
						(*it)->parts.pos.y = off1.pos.y;	
						break;
				}
				off1 = off2;
			}
			old = it;
			it++;
			count++;
		}
	}

	void ObjectList<OnceWord*>::Draw()
	{
		WordIterator it = this->list.begin();
		while( it != this->list.end() )
		{
			if( (*it)->parts.isDraw )
				(*it)->Draw2D();
			it++;
		}
	}

	//------------------------------------------------------
	void NumbersWord::Init()
	{
		this->numbers = this->keta = 0;
		this->word = "numbers";
		this->parts.pos.SetMinVector();
		this->parts.ang = 0.0f;
		this->parts.scale.SetMinVector();
		this->parts.color.SetMaxColor();
	}

	void NumbersWord::SetNumber(int dnum)
	{
		this->numbers = dnum;
		this->keta = this->GetKeta();
	}

	int NumbersWord::GetKeta()
	{
		if( !this->numbers)	return 1;
		
		int temp = 1, count = 0, dis;
		do
		{
			dis = (int)(this->numbers / temp);
			if( dis )
			{
				count++;
				temp *= 10;
			}else			break;
		}while(true);

		return count;
	}

	void NumbersWord::numbersDraw()
	{
		if( this->keta <= 0 )	return ;
		
		int temp = 1;
		for(int i=0; i<this->keta-1; i++)
			temp *= 10;

		Text2DFactory* gh = __GRAPHFACTORY;
		for(int i=0, num = this->numbers, wod; i<this->keta; i++, num /= 10)
		{
			if( !num )	wod = 0;
			else			wod = num % 10;

			gh->draw_SetTrans( D3DXVECTOR2(this->parts.pos.x - this->parts.scale.x * i, this->parts.pos.y),
				this->parts.scale, 
				this->parts.ang,
				this->word, DIRECT_SCALE, this->parts.color.color );	
			gh->draw_divGraph( wod );
		}
	}

	//----------------------------------------------------------------------------------------
	//バウンドする文字エフェクト
	BoundingWord::BoundingWord()
	{
		this->sameInit();
		this->boundXY.SetVector(0,0);
	}
	
	BoundingWord::BoundingWord(LPCSTR ch)
	{
		this->sameInit();
		this->parts.word = (LPSTR)ch;
		this->boundXY.SetVector(0,0);
	}

	void BoundingWord::Step()
	{
		if( this->boundXY.x >= 0)
		{
			this->boundXY.x--;
			this->parts.pos.y += this->boundXY.y;
			this->boundXY.y++;
		}
	}

	void BoundingWord::Draw2D()
	{
		MYGAME::Text2DFactory* gh = MYGAME::__GRAPHFACTORY;
		gh->drawString2D( (char*)this->parts.word.c_str(), parts.pos,
			this->parts.scale.x, parts.ang, parts.color.color );
	}
}