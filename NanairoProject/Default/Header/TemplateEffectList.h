#ifndef _NANAIRO_TEMPEFFECTLIST_H
#define	_NANAIRO_TEMPEFFECTLIST_H

#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

#ifndef _NANAIRO_USEEFFECT_H
#include <UseEffect.h>
#endif

namespace MYGAME
{
	//---------------------------------------------------------------------
	//�G�t�F�N�g���܂Ƃ߂ĂP�̃I�u�W�F�N�g�ɂ��鎞�Ɏg�p
	//---------------------------------------------------------------------
	template<typename T> class TemplateEffectList : public MYGAME::AnimationEffect2D
	{
	private:
		std::list<T>	list;
		
	public:
		TemplateEffectList(){}
		~TemplateEffectList(){}

		void Init(){}
		void Step(){}
		void Draw2D(){}
		void Del(){}
		void Clear(){}
		void Push(){}
	};

	template<typename T> class StatePatterns
	{
	private:
		//�֐��|�C���^
		void (StatePatterns::*_action)(T* const obj);

	public:
		StatePatterns(void (StatePatterns::*_in)(T* const obj))
		{
			_action = _in;
		}

		void SetAction(void (StatePatterns::*_in)(T* const obj))
		{
			_action = _in;
		}

		void Step(T* const obj)
		{
			if( this->_action != NULL ) 
				(this->*_action)(obj);
		}
	};

	////////////////////////////////////////////////////////////////////////////////
	//���G�t�F�N�g���X�g
	template<> class TemplateEffectList<MYGAME::StarEffect*> : public MYGAME::AnimationEffect2D
	{
	private:
		std::list<MYGAME::StarEffect*>	list;
		NanairoLib::Vector2		offSet;

	public:
		TemplateEffectList(){	this->Init();	}
		~TemplateEffectList(){	this->Clear();	}

		void SetRandomStarAction();
		void SetDownStarAction();
		void SetObject(NanairoLib::Vector2& vec){	this->offSet = (NanairoLib::Vector2)vec;	}
		void (TemplateEffectList::*Action)();
		void move();
		void downMove();
		void fadeout();

		void Init();
		void Step();
		void Draw2D();
		void Del();
		void Clear();
		void PushRandomStar();
		void PushDownStar();
	};

	//�����G�t�F�N�g
	template<> class TemplateEffectList<ConfettiEffect*> : public MYGAME::AnimationEffect2D
	{
	private:
		std::list<ConfettiEffect*>	list;

	public:
		TemplateEffectList(){	this->Init();	}
		~TemplateEffectList(){	this->Clear();	}

		void SetFadeOut();
		void (TemplateEffectList::*Action)();
		void move();
		void fadeout();

		void Init();
		void Step();
		void Draw2D();
		void Del();
		void Clear();
		void Push();
	};

	//�ԉ΃G�t�F�N�g
	template<> class TemplateEffectList<FireflowerEffect*> : public MYGAME::AnimationEffect2D
	{
	private:
		std::list<FireflowerEffect*>	list;

	public:
		TemplateEffectList(){	this->Init();	}
		~TemplateEffectList(){	this->Clear();	}

		void SetObject(NanairoLib::Vector2& vec){	this->parts.pos = (NanairoLib::Vector2)vec;	}
		void (TemplateEffectList::*Action)();
		void move();
		void fadeout();

		void Init();
		void Step();
		void Draw2D();
		void Del();
		void Clear();
		void Push();
	};
}

#endif