#ifndef _NANAIRO_RULEANIME_H
#define	_NANAIRO_RULEANIME_H

#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

#ifndef _NANAIRO_USEEFFECT_H
#include <UseEffect.h>
#endif

namespace NanairoProject
{
	
	//----------------------------------

	////////////////////////////////////////////////////////////////////////////////
	//�v���G�t�F�N�g�f
	class GainEffect : public MYGAME::OnceEffect
	{
	private:
		int delCnt;
		NanairoLib::Vector2 spd;

	public:
		GainEffect() : delCnt(60){	this->Init();	}
		~GainEffect(){}

		void Init();
		void Draw2D(){	this->Action_draw();	}
		void Step();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�X�y�R�Ԃ��G�t�F�N�g�f��
	class SwordEffect : public MYGAME::AnimationEffect2D
	{
	public:
		SwordEffect(){	this->Init();	}
		~SwordEffect(){}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�K�i�G�t�F�N�g�f��
	class BrustEffect : public MYGAME::AnimationEffect2D
	{
	public:
		BrustEffect(){	this->Init();	}
		~BrustEffect(){}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�J�[�h�����G�t�F�N�g�f��
	class CardChangeEffect_small : public MYGAME::OnceEffect
	{
	private:
		int delCnt;
		NanairoLib::Vector2 spd;

	public:
		CardChangeEffect_small() : delCnt(60){	this->Init();	}
		~CardChangeEffect_small(){}

		void Init();
		void Draw2D(){	this->Action_draw();	}
		void Step();
		void Del(){}
	};

	
}

#endif