#ifndef _NANAIRO_PLATEEFFECT_H
#define	_NANAIRO_PLATEEFFECT_H

//-----------------------------------------------------
//std
//-----------------------------------------------------
#ifndef _LIST_
#include <list>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

//-----------------------------------------------------
//MYGAME
//-----------------------------------------------------
#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

#ifndef _MYGANE_DIALOG_H
#include <Dialog.h>
#endif

#ifndef MYGAME_OBJECTLIST_H
#include <OBjectList.h>
#endif
using namespace MYGAME;

namespace NanairoProject
{
	enum MillionareEffect_ENUM
	{
		BIG_MILL_EFFECT, SMALL_MILL_EFFECT, SMALL_POOR_EFFECT, BIG_POOR_EFFECT,
	};

	enum PLAYER_FACE_ENUM
	{
		FACE_NORMAL, FACE_SMILE, FACE_HURRY, FACE_AMAZE, 
		FACE_LAUGH, FACE_DAMAGE, FACE_LOSE, 
	};

	//プレートエフェクトリスト
	template<typename T>
	class PlateList
	{
	private:
		int objSum;
		std::list<T> obList;

	public:
		PlateList() : objSum(0){	this->Init();	}
		~PlateList(){				this->Clear();	}

		void Init();
		int Size(){	return this->objSum;	}
		bool Empty(){	return ( !this->objSum );	}
		void Push(T sub){	this->obList.push_back( sub );	}
		void Clear(){	this->obList.clear();	}
	};

	//-----------------------------------------------------
	//大富豪のプレートエフェクト
	//-----------------------------------------------------
	class PlateEffect : public NanairoLib::Effect2D
	{
	protected:
		int plateType, plateNumber;
		NanairoLib::Vector2 offSet, offSetSpd;
		std::string word;

	public:
		bool delFlag, waitFlag;

	private:
		void (PlateEffect::*Action)();
		void action_up();
		void action_down();
		void action_right();

	public:
		PlateEffect(){	this->Init();	}
		~PlateEffect(){}

		int GetCardType(){				return this->plateType;	}
		void SetCardType(int dtype){	plateType = dtype;		}
		void SetObject(int dtype, int number);
		void SetFadeOut();
		void SetPlateDown(int spd);

		void Init();
		void Step(){	(this->*Action)();	}
		void Draw2D();
		void Del(){}
	};

	//-----------------------------------------------------
	//大富豪のプレートエフェクトリスト
	//-----------------------------------------------------
	template<> class PlateList<PlateEffect*>
	{
	private:
		int objSum;
		std::list<PlateEffect*> list;

	public:
		PlateList() : objSum(0){		this->Init();	}
		~PlateList(){					this->Clear(); }

		void Init();
		int Size(){	return this->objSum;	}
		bool Empty(){	return ( !this->objSum );	}
		void Clear();

		void Step();
		void Draw2D();
		void Del();
		
		void Push(int dtype);
		void Pop(int dtype);
	};

	/////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------
	//番号のプレートエフェクトスーパークラス
	//-----------------------------------------------------
	class SuperMillionareEffect : public NanairoLib::Effect2D
	{
	protected:
		int number, playNumber;
		NanairoLib::Vector2 offSet, offSetSpd;
		std::string word;

	protected:
		void sameInit(){	this->parts.scale.SetVector( 120.0f, 40.0f );	}
		void wordDraw();

	public:
		SuperMillionareEffect() : number(0)
		{
			offSet.SetMinVector();
			offSetSpd.SetMinVector();
			word = "";
		}
		virtual ~SuperMillionareEffect(){}

		virtual void Init() = 0;
		virtual void Step() = 0;
		virtual void Draw2D() = 0;
		virtual void Del() = 0;

		int GetRunk(){			return this->number;		}
		int GetPlayNumber(){	return this->playNumber;	}
		void SetObject(int playNumber);

		static SuperMillionareEffect* CreateMillionareEffect(int number);
	};

	//-----------------------------------------------------
	//大富豪のプレートエフェクト
	//-----------------------------------------------------
	class BigMillionareEffect : public SuperMillionareEffect
	{
	public:
		BigMillionareEffect(){	this->Init();		}
		~BigMillionareEffect(){}

		void Init();
		void Step(){}
		void Draw2D(){	this->wordDraw();	}
		void Del(){}
	};

	//-----------------------------------------------------
	//富豪のプレートエフェクト
	//-----------------------------------------------------
	class SmallMillionareEffect : public SuperMillionareEffect
	{
	public:
		SmallMillionareEffect(){	this->Init();	}
		~SmallMillionareEffect(){}

		void Init();
		void Step(){}
		void Draw2D(){	this->wordDraw();	}
		void Del(){}
	};

	//-----------------------------------------------------
	//貧民のプレートエフェクト
	//-----------------------------------------------------
	class SmallPoorEffect : public SuperMillionareEffect
	{
	public:
		SmallPoorEffect(){	this->Init();	}
		~SmallPoorEffect(){}

		void Init();
		void Step(){}
		void Draw2D(){	this->wordDraw();	}
		void Del(){}
	};

	//-----------------------------------------------------
	//大貧民のプレートエフェクト
	//-----------------------------------------------------
	class BigPoorEffect : public SuperMillionareEffect
	{
	public:
		BigPoorEffect(){	this->Init();	}
		~BigPoorEffect(){}

		void Init();
		void Step(){}
		void Draw2D(){	this->wordDraw();	}
		void Del(){}
	};

	//-----------------------------------------------------
	//大富豪のプレートエフェクトリスト
	//-----------------------------------------------------
	template<> class PlateList<SuperMillionareEffect*>
	{
	private:
		int objSum;
		std::list<SuperMillionareEffect*> list;

	public:
		PlateList() : objSum(0){	this->Init();	}
		~PlateList(){				this->Clear();	}

		int GetNottingNumber(int capNum = -1);
		int GetNumber1();
		bool Empty(){	return (this->objSum == 0);	}
		int GetSize(){	return this->objSum;		}
		std::vector<int> GetRunk();
		
		void Init();
		void Step();
		void Draw2D();
		void Del(){}
		void Clear();

		void Push(int playNumber, int runkNumber);
		void CapitalDownPush(int playNumber);
	};

	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------
	//プレイヤープレート
	//このプレートにプレイヤーのアイコンを張る
	//-----------------------------------------------------------------
	class PlayerPlate : public MYGAME::NameDialog
	{
	private:
		int playNumber, runkNumber, oldRunkNumber, foulFlag, faceNumber;
		NanairoLib::Vector2 offSet, offSetSpd, yousiPos, yousiScale;
		LPCSTR word, runkWord;

	private:
		void plateDraw();
		void runkDraw();
		void capitalDownDraw();
		void foulDraw();
		

	public:
		PlayerPlate() : playNumber(0), runkNumber(0){	this->Init();	}
		~PlayerPlate(){}

		void	onCapitalDown(){	this->foulFlag = 1;	}
		void	onFoulUp(){		this->foulFlag = 2;	}
		int		GetFoulFlag(){		return this->foulFlag;		}
		int		GetRunkNumber(){	return this->runkNumber;	}
		int		GetOldRunkNumber(){	return this->oldRunkNumber;	}
		int		GetPlayerNumber(){	return this->playNumber;	}
		void	SetObjectNumber(int dnumber, int charaNumber);
		void	SetRunk(int drunk){	this->runkNumber = drunk;	}
		void	SetContinue();
		void	SetFace(int number){	this->faceNumber = number;	}
		void	SetName(LPCSTR name){	this->word = name;			}
		void	SetRunkName();
		void Init();
		void Step(){}
		void Draw2D();
		void Del(){}
		
		void yousiDraw();
	};

	//-----------------------------------------------------------------
	//プレイヤープレートリスト
	//-----------------------------------------------------------------
	template<> class PlateList<PlayerPlate*>
	{
	private:
		int objSum;
		std::list<PlayerPlate*> list;

	public:
		PlateList(){	this->Init();	}
		~PlateList(){	this->Clear();	}

		std::vector<int> GetFoulSum();
		int GetPlayNumber_runk(int num);
		int GetPlayNumber_runk1();
		int GetPlayNumber_runk4();
		PlayerPlate* GetPlayerPlate(int number);
		void onFoul(int playNumber, int foulNumber);
		void SetContinue();
		int Size(){		return this->objSum;				}
		bool Empty(){	return (this->objSum == 0);			}

		void Init();
		void Step();
		void Draw2D();
		void Clear();

		void yousiDraw();
		
		void Pusher(int playNumber, int charaNumber);
		void Push(int playNumber, int runkNumber);
		
	};
}

#endif