#ifndef _NANAIRO_RULEEFFECT_H
#define	_NANAIRO_RULEEFFECT_H

#ifndef _MYGAME_ONCEWORD_H
#include <OnceWord.h>
#endif

#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

#ifndef _NANAIRO_RULEANIME_H
#include <Rule_anime.h>
#endif

#ifndef _NANAIRO_USEEFFECT_H
#include <UseEffect.h>
#endif

namespace NanairoProject
{
	///////////////////////////////////////////////////////////////////////////////
	//���[����̃G�t�F�N�g
	class Rule_effect : public NanairoLib::Effect2D
	{
	protected:
		int delCnt;
		float fadeOutSpd;
		NanairoLib::Vector2 offSet, offSetSpd;
		NanairoLib::Textcolor stColor;
		std::string word;

	protected:
		void super_ruleEffect();
		void action_word();
		void Action_draw();
		void Step_and_Checking();
		

	public:
		Rule_effect() : delCnt(60){}
		virtual ~Rule_effect(){}

		virtual void Init() = 0;
		virtual void Step() = 0;
		virtual void Draw2D() = 0;
		virtual void Del() = 0;
	};

	////////////////////////////////////////////////////////////////////////////////
	//8�؂�G�t�F�N�g
	#define eightCutSmallSum 1
	class EightCutEffect : public Rule_effect
	{
	private:
		MYGAME::CutEffect smallEffect[eightCutSmallSum];

	public:
		EightCutEffect(){	this->Init();	}
		~EightCutEffect(){}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�C���u���o�b�N�G�t�F�N�g
	class ElevenbackEffect : public Rule_effect
	{
	private:
		MYGAME::KaleidoScopeScreenEffect smallEffect;
		MYGAME::ArrowEffect* yajirusi;

	public:
		ElevenbackEffect();
		~ElevenbackEffect(){	ES_SAFE_DELETE_ARRAY( yajirusi );}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//����G�t�F�N�g
	#define LONGCHAIN_SUM 4
	class RestrainsEffect : public Rule_effect
	{
	private:
		MYGAME::LongChainEffect* longChain;
		MYGAME::CircleChainEffect* circleChain;

	public:
		RestrainsEffect();
		~RestrainsEffect();

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�v���G�t�F�N�g
	#define DEVIL_EFFECT_SUM 10
	class RevolutionEffect : public Rule_effect
	{
	private:
		MYGAME::DevilEffect*	devilEffect;
		GainEffect*		gainEffect;

	public:
		RevolutionEffect();
		~RevolutionEffect();

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�W���[�J�[�G�t�F�N�g
	#define FIRE_EFFECT_SUM 2
	class JockerEffect : public Rule_effect
	{
	private:
		MYGAME::FireCutEffect* fireEffect1;

	public:
		JockerEffect();
		~JockerEffect();

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�X�y�R�Ԃ��G�t�F�N�g
	#define KIRARI_EFFECT_SUM 5
	class Spade3Effect : public Rule_effect
	{
	private:
		SwordEffect* swordEffect;
		MYGAME::KirariEffect* kirariEffect;
	public:
		Spade3Effect();
		~Spade3Effect();

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�K�i�G�t�F�N�g
	class StairsEffect : public Rule_effect
	{
	private:
		BrustEffect* brustEffect;

	public:
		StairsEffect();
		~StairsEffect();

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�p�X�G�t�F�N�g
	class PassingEffect : public Rule_effect
	{
	public:
		PassingEffect(){	this->Init();	}
		~PassingEffect(){}

		void SetObject(int dnumber);

		void Init();
		void Step();
		void Draw2D(){	this->Action_draw();	}
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�オ��G�t�F�N�g
	class WinnerEffect : public Rule_effect
	{
	public:

		WinnerEffect(){	this->Init();	}
		~WinnerEffect(){}

		void SetObject(int dnumber);

		void Init();
		void Step();
		void Draw2D(){	this->Action_draw();	}
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�s�����G�t�F�N�g
	class CapitalDownEffect : public Rule_effect
	{
	public:
		CapitalDownEffect(){	this->Init();	}
		~CapitalDownEffect(){}

		void SetObject(int dnumber);

		void Init();
		void Step();
		void Draw2D(){	this->Action_draw();	}
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�����オ��G�t�F�N�g
	class FoulUpEffect : public Rule_effect
	{
	public:
		FoulUpEffect(){	this->Init();	}
		~FoulUpEffect(){}

		void SetObject(int dnumber);

		void Init();
		void Step();
		void Draw2D(){	this->Action_draw();	}
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//���E���h�J�n�G�t�F�N�g
	class RoundStartEffect : public Rule_effect
	{
	private:
		int roundNumber;
		MYGAME::NumbersWord numbersWord;

	public:
		RoundStartEffect(){	this->Init();	}
		~RoundStartEffect(){}

		void SetRound(int round){	this->numbersWord.SetNumber( this->roundNumber = round );	}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�J�[�h�����G�t�F�N�g
	class CardChangeEffect : public Rule_effect
	{
	private:
		CardChangeEffect_small	changeEffect;

	public:
		CardChangeEffect(){	this->Init();	}
		~CardChangeEffect(){}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�X�y�V�����J�[�h�G�t�F�N�g
	class SpecialEffect : public Rule_effect
	{
	private:
		float slideSpd;
		int specialInterval, specialCnt;
	
	protected:
		LPCSTR charaWord;

	private:
		void (SpecialEffect::*_SpecialAction)();
		void SpecialFadeIn();
		void SpecialWait();
		void SpecialFadeOut();

	public:
		SpecialEffect(){	this->SpecialInit();	}
		~SpecialEffect(){}

		void SpecialInit();
		void SpecialStep(){	(this->*_SpecialAction)();	}
		void SpecialDraw();
	};

	////////////////////////////////////////////////////////////////////////////////
	//�G���X�p�X�y�V�����J�[�h�G�t�F�N�g
	class ErisuSpecialEffect : public SpecialEffect
	{
	public:
		ErisuSpecialEffect(){	this->Init();	}
		~ErisuSpecialEffect(){}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};


}

#endif
