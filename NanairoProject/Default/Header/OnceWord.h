#ifndef _MYGAME_ONCEWORD_H
#define _MYGAME_ONCEWORD_H

#ifndef _LIST_
#include <list>
#endif

#ifndef _MYGAME_UIPARTS_H
#include <UIParts.h>
#endif

//動きのある文字を制作
namespace MYGAME
{
	//-------------------------------------------
	//動きのある文字構造体
	//必要なものをここにっ
	//-------------------------------------------
	class WordParts : public NanairoLib::UIParts2D
	{
	public:
		bool					isUpdate, isDraw;
		std::string				word;
		
		WordParts() : isUpdate(true), isDraw(true)
		{
			this->word = "";
		}
		~WordParts(){}

		WordParts& operator = (WordParts& in)
		{
			this->isUpdate = in.isUpdate;
			this->isDraw = in.isDraw;
			this->word = in.word;
			return *this;
		}
	};

	//-------------------------------------------
	//基本的な動作文字クラス
	//※これを生成してはいけないっ
	//-------------------------------------------
	class OnceWord : public NanairoLib::NormalObject
	{
		public:
			WordParts parts;

		public:
			OnceWord(){	this->sameInit();	}
			OnceWord(LPCSTR ch);
			virtual ~OnceWord();

		public:
			//以下の３つを継承させ、実行したい内容の変更を行う
			void Init(){}
			virtual void Draw2D() = 0;
			void Dispose(){}	
			virtual void Step() = 0;							//アクションをまとめてここで
			
			//ﾌｧｲﾙ読み込みした時に得た文字を代入するので
			//その文字からデータを取り出す
			virtual void readParts(std::string& str);			
		
		public:
			//継承しても変わらない初期化をここにかいてく
			void sameInit();

			//位置、角度、スケール情報を挿入
			void SetObject(NanairoLib::PCVector2 ps, float ag, NanairoLib::PCVector2 sc);
			
			//表示したい文字や画像につけた名前を入れてく
			void SetWord(LPCSTR ch){	this->parts.word = (LPSTR)ch;	}
			void SetChar(char ch){		this->parts.word = ch;	}

			//文字の色を挿入
			void SetColor(NanairoLib::Vector4& vec){this->parts.color.color = vec;	}
			void SetColor(NanairoLib::PCColor color){	this->parts.color = color;	}
			void SetAlpha(float al){	this->parts.color.color.x = al;	}

			//ポジションセット
			void SetPos(NanairoLib::RVector2 ps){	this->parts.pos = (NanairoLib::Vector2)ps;	}
			void SetAng(float ag){					this->parts.ang = ag;	}
			void SetScl(NanairoLib::RVector2 sc){	this->parts.scale = (NanairoLib::Vector2)sc;	}

			//開いたﾌｧｲﾙﾎﾟｲﾝﾀから情報をロードする
			void loadParts(std::ifstream& fs);
			
			//位置、角度、スケール情報から分割して取得
			void splitParts(std::string& str);

	};

	//-------------------------------------------
	//ＰＣ内の文字を使った文字表示を行う
	//動作文字
	//-------------------------------------------
	class DefaultWord : public OnceWord
	{
		public:
			DefaultWord(){	this->sameInit();	}
			DefaultWord(LPCSTR ch);
			virtual ~DefaultWord(){}
		public:
			virtual void Step(){}
			void Draw();
	};

	//-------------------------------------------
	//画像用の文字で動作行うときに使うクラス
	//動作文字
	//-------------------------------------------
	class GraphWord : public OnceWord
	{
		public:
			GraphWord(){	this->sameInit();	}
			GraphWord(LPCSTR ch);
			virtual ~GraphWord(){}

		public:
			virtual void Step(){}
			void Draw2D();
	};

	typedef std::list<OnceWord*>			WordList;
	typedef std::list<OnceWord*>::iterator	WordIterator;

	//-------------------------------------------
	//一つの文字を一括して管理する
	//これもスーパークラスなので
	//継承して制作していく
	//-------------------------------------------
	template<> class ObjectList<OnceWord*>
	{
		protected:
			WordList list;

		public:
			ObjectList(){	this->Clear();	}
			virtual ~ObjectList(){	this->Clear();	}
	
		public:
			void Add(OnceWord* wh){	this->list.push_back( wh );	}
			void Clear();
			OnceWord* GetWord(int number);
			WordIterator GetBeginIterator(){	return this->list.begin();	}

			virtual void Step();
			virtual void ChainStep(CHAIN_TYPE type);
			virtual void Draw();
	};

	//-------------------------------------------
	//数字文字
	//-------------------------------------------
	class NumbersWord : public OnceWord
	{
	private:
		std::string word;
		int numbers, keta;

	private:
		void numbersDraw();

	public:
		NumbersWord(){	this->Init();	}
		~NumbersWord(){}

		int GetKeta();
		void SetNumber(int dnum);
		void Init();
		void Draw2D(){	this->numbersDraw();	}
		void Step(){}
	};

	//-------------------------------------------
	//バウンド文字
	//-------------------------------------------
	class BoundingWord : public DefaultWord
	{
		private:
			NanairoLib::Vector2 boundXY;

		public:
			BoundingWord();
			BoundingWord(LPCSTR ch);
			virtual ~BoundingWord(){}
		public:
			void SetBounding(float bound){	this->boundXY.SetVector(bound*2,-bound);	}

			void Step();
			void Draw2D();
	};
}

#endif