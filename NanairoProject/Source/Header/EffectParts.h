#ifndef _NANAIRO_EFFECTPARTS_H
#define	_NANAIRO_EFFECTPARTS_H

#ifndef _MYGAME_UIPARTS_H
#include <UIParts.h>
#endif

#ifndef MYGAME_OBJECTLIST_H
#include <OBjectList.h>
#endif

//----------------------------------------------------
//
//２Ｄエフェクト
//
//----------------------------------------------------
//
//２Ｄエフェクトは汎用オブジェクトを継承しているので
//テンプレートリストに追加可能
//
//----------------------------------------------------

namespace MYGAME
{
	typedef std::list<NanairoLib::PEffect2D>	Effect2DList;
	typedef Effect2DList::iterator				Effect2DIterator;

	///////////////////////////////////////////////////////////////////////////////
	//アニメーション画像のエフェクト
	class AnimationEffect2D : public NanairoLib::Effect2D
	{
	protected:
		bool OKFlag;
		int sumCnt, animeCnt, intervalCnt;
		LPCSTR animeName;

	public:
		AnimationEffect2D() : OKFlag(false), sumCnt(0), animeCnt(0), intervalCnt(5)
		{
			this->SuperInitAnimationEffect2D();
		}
		~AnimationEffect2D(){}
	
	protected:
		void Same_draw();

	public:

		void SuperInitAnimationEffect2D();
		void Step_and_Checking();
		void Step_and_Checking_repeat();
		void SetSumCnt(LPCSTR dname, int dsum);

		void MoveIntervalCnt(int spd){	this->intervalCnt += spd;	}

		virtual void Init() = 0;
		virtual void Step() = 0;
		virtual void Draw2D() = 0;
		virtual void Del() = 0;
	};

	///////////////////////////////////////////////////////////////////////////////
	//単体画像エフェクトの基本
	class OnceEffect : public NanairoLib::Effect2D
	{
	protected:
		int delCnt;
		LPCSTR word;

	protected:
		void super_OnceEffect(){}
		void Action_draw();
		void Step_and_Checking();
		void SetWord(LPCSTR in){	word = in;	}
		
	public:
		OnceEffect() : delCnt(60){	this->super_OnceEffect();	}
		virtual ~OnceEffect(){}

		virtual void Init() = 0;
		virtual void Step() = 0;
		virtual void Draw2D() = 0;
		virtual void Del() = 0;
	};

	///////////////////////////////////////////////////////////////////////////////
	//エフェクト型リスト
	template<> class ObjectList<NanairoLib::PEffect2D>
	{
	private:
		int objSum;
		Effect2DList obList;

	public:
		
		ObjectList();
		~ObjectList();

		void Init();
		int Size();
		bool Empty();

		Effect2DIterator GetIterator(int number);
		Effect2DIterator GetIterator(NanairoLib::PEffect2D number);

		void Add(NanairoLib::PEffect2D add);
		void Insert(NanairoLib::PEffect2D add, int number);
		void Insert(NanairoLib::PEffect2D add, const NanairoLib::PEffect2D index);

		void ListClear();

		void Dispose(int number);
		void Dispose(NanairoLib::PEffect2D obj);
		NanairoLib::PEffect2D Unlink(int number);
		NanairoLib::PEffect2D Unlink(NanairoLib::PEffect2D obj);

		void Step();
		void ChainStep(CHAIN_TYPE type);
		void Draw();
		void Del();
	};
}

#endif