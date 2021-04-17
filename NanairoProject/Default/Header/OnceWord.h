#ifndef _MYGAME_ONCEWORD_H
#define _MYGAME_ONCEWORD_H

#ifndef _LIST_
#include <list>
#endif

#ifndef _MYGAME_UIPARTS_H
#include <UIParts.h>
#endif

//�����̂��镶���𐧍�
namespace MYGAME
{
	//-------------------------------------------
	//�����̂��镶���\����
	//�K�v�Ȃ��̂������ɂ�
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
	//��{�I�ȓ��앶���N���X
	//������𐶐����Ă͂����Ȃ���
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
			//�ȉ��̂R���p�������A���s���������e�̕ύX���s��
			void Init(){}
			virtual void Draw2D() = 0;
			void Dispose(){}	
			virtual void Step() = 0;							//�A�N�V�������܂Ƃ߂Ă�����
			
			//̧�ٓǂݍ��݂������ɓ���������������̂�
			//���̕�������f�[�^�����o��
			virtual void readParts(std::string& str);			
		
		public:
			//�p�����Ă��ς��Ȃ��������������ɂ����Ă�
			void sameInit();

			//�ʒu�A�p�x�A�X�P�[������}��
			void SetObject(NanairoLib::PCVector2 ps, float ag, NanairoLib::PCVector2 sc);
			
			//�\��������������摜�ɂ������O�����Ă�
			void SetWord(LPCSTR ch){	this->parts.word = (LPSTR)ch;	}
			void SetChar(char ch){		this->parts.word = ch;	}

			//�����̐F��}��
			void SetColor(NanairoLib::Vector4& vec){this->parts.color.color = vec;	}
			void SetColor(NanairoLib::PCColor color){	this->parts.color = color;	}
			void SetAlpha(float al){	this->parts.color.color.x = al;	}

			//�|�W�V�����Z�b�g
			void SetPos(NanairoLib::RVector2 ps){	this->parts.pos = (NanairoLib::Vector2)ps;	}
			void SetAng(float ag){					this->parts.ang = ag;	}
			void SetScl(NanairoLib::RVector2 sc){	this->parts.scale = (NanairoLib::Vector2)sc;	}

			//�J����̧���߲������������[�h����
			void loadParts(std::ifstream& fs);
			
			//�ʒu�A�p�x�A�X�P�[����񂩂番�����Ď擾
			void splitParts(std::string& str);

	};

	//-------------------------------------------
	//�o�b���̕������g���������\�����s��
	//���앶��
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
	//�摜�p�̕����œ���s���Ƃ��Ɏg���N���X
	//���앶��
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
	//��̕������ꊇ���ĊǗ�����
	//������X�[�p�[�N���X�Ȃ̂�
	//�p�����Đ��삵�Ă���
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
	//��������
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
	//�o�E���h����
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