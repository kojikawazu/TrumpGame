#ifndef _NANAIRO_USEEFFECT_H
#define	_NANAIRO_USEEFFECT_H

#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

//----------------------------------------------------
//
//�Q�c�G�t�F�N�g�͔ėp�I�u�W�F�N�g���p�����Ă���̂�
//�e���v���[�g���X�g�ɒǉ��\
//
//----------------------------------------------------

namespace MYGAME
{
	////////////////////////////////////////////////////////////////////////////////
	//8�؂�G�t�F�N�g�f��
	//�J�b�g�G�t�F�N�g
	class CutEffect : public MYGAME::AnimationEffect2D
	{
	public:
		CutEffect(){	this->Init();	}
		~CutEffect(){}

		void SetDirection(int directNum);
		void SetNormalMode();

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//���؋��X�N���[���G�t�F�N�g�f��
	class KaleidoScopeScreenEffect : public MYGAME::AnimationEffect2D
	{
	public:
		KaleidoScopeScreenEffect(){	this->Init();	}
		~KaleidoScopeScreenEffect(){}

		void SetNormalMode();

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//���G�t�F�N�g�f��
	class ArrowEffect : public MYGAME::OnceEffect
	{
	private:
		int delCnt, yajiNum;
		NanairoLib::Vector2 spd;

	public:
		ArrowEffect(): delCnt(60){	this->Init();	}
		~ArrowEffect(){}
		void SetObject(int number);
		void SetYajirusiMove(NanairoLib::RVector2 dspd, NanairoLib::RVector2 dpos, NanairoLib::RVector4 dcol);

		void Init();
		void Draw2D();
		void Step();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�L�΂����G�t�F�N�g�f��
	class LongChainEffect : public MYGAME::OnceEffect
	{
	private:
		int delCnt, yajiNum;
		NanairoLib::Vector2 spd;

	public:
		LongChainEffect() : delCnt(60){	this->Init();	}
		~LongChainEffect(){}

		void SetObject(int number);
		void SetMove(NanairoLib::RVector2 dspd, NanairoLib::RVector2 dpos, float dang);

		void Init();
		void Draw2D();
		void Step();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�񂵍��G�t�F�N�g�f��
	class CircleChainEffect : public MYGAME::OnceEffect
	{
	private:
		int delCnt;
		NanairoLib::Vector2 spd;

	public:
		CircleChainEffect() : delCnt(60){	this->Init();	}
		~CircleChainEffect(){}

		void Init();
		void Draw2D();
		void Step();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�g��G�t�F�N�g�f��
	class RippleEffect : public MYGAME::OnceEffect
	{
	private:
		int delCnt;
		NanairoLib::Vector2 spd;

	public:
		RippleEffect() : delCnt(60){	this->Init();	}
		~RippleEffect(){}

		void Init();
		void Draw2D();
		void Step();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�X�N���[����Ń{�[�����ړ�����G�t�F�N�g�f��
	class BallScreenMoveEffect : public MYGAME::OnceEffect
	{
	private:
		int delCnt, rotaCnt;
		NanairoLib::Vector2 spd;

	public:
		BallScreenMoveEffect() : delCnt(60){	this->Init();	}
		~BallScreenMoveEffect(){}

		void ChangeRota();

		void Init();
		void Draw2D();
		void Step();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//��������A�j���[�V�����G�t�F�N�g�f��
	class DevilEffect : public MYGAME::AnimationEffect2D
	{
	private:
		int waitCnt;
		
	public:
		DevilEffect() : waitCnt(0){	this->Init();	}
		~DevilEffect(){}

		void SetObject(int number);

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//���؂�G�t�F�N�g
	class FireCutEffect : public MYGAME::AnimationEffect2D
	{
	private:
		int number;

	public:
		FireCutEffect(){	this->Init();	}
		~FireCutEffect(){}

		void SetObject(int num);

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�L�����G�t�F�N�g
	class KirariEffect : public MYGAME::AnimationEffect2D
	{
	private:
		int waitCnt;
		
	public:
		KirariEffect() : waitCnt(0){	this->Init();	}
		~KirariEffect(){}

		void SetObject(int number);

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//���G�t�F�N�g�i���ʁj
	class StarEffect : public MYGAME::AnimationEffect2D
	{
	protected:
		int speed;
		NanairoLib::Vector2 offSetSpd;
	public:
		StarEffect(){	this->Init();	}
		virtual ~StarEffect(){}

		NanairoLib::Vector2* GetOffSetVector() const{	return (NanairoLib::Vector2* const)&this->offSetSpd;	}
		void SetMoveAng(float rad);
		
		void Init();
		void Step(){}
		void Del(){}
		void Draw2D();
	};

	////////////////////////////////////////////////////////////////////////////////
	//���G�t�F�N�g�i�����_���ɊO�֓����Ă����j
	class RandomStarEffect : public StarEffect
	{
	public:
		RandomStarEffect(){}
		~RandomStarEffect(){}

		void Init(){}
		void SetObject(NanairoLib::Vector2& vec, int spd);

		void Step();
	};

	////////////////////////////////////////////////////////////////////////////////
	//���G�t�F�N�g�i���֗����ăo�E���h����j
	class DownStarEffect : public StarEffect
	{
	private:
		int topSpd;
		void (DownStarEffect::*_action)();

	public:
		DownStarEffect(){}
		~DownStarEffect(){}

		void FirstDown();
		void Topping();
		void SecondDown();

		void Init(){}
		void SetObject(NanairoLib::Vector2& vec, int spd);
		void Step();
	};

	////////////////////////////////////////////////////////////////////////////////
	//�ԉ΃G�t�F�N�g�f��
	class FireflowerEffect : public MYGAME::AnimationEffect2D
	{
	public:
		FireflowerEffect(){	this->Init();	}
		~FireflowerEffect(){}

		void SetObject(NanairoLib::Vector2& vec);

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//���������Ƃ��̃G�t�F�N�g�f��
	class ConfettiEffect : public MYGAME::AnimationEffect2D
	{
	private:
		NanairoLib::Vector2 offSetSpd;

	public:
		ConfettiEffect(){	this->Init();	}
		~ConfettiEffect(){}

		void SetObject(NanairoLib::Vector2& vec);

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�����@�G�t�F�N�g�f��
	class MagicstarEffect : public MYGAME::AnimationEffect2D
	{
	public:
		MagicstarEffect(){	this->Init();	}
		~MagicstarEffect(){}

		void SetObject(NanairoLib::Vector2& vec);

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};

	////////////////////////////////////////////////////////////////////////////////
	//�}�E�X�^�b�`�G�t�F�N�g�f��
	class MouseKirariEffect : public MYGAME::AnimationEffect2D
	{	
	public:
		MouseKirariEffect(){	this->Init();	}
		~MouseKirariEffect(){}

		void SetObject(NanairoLib::Vector2& vec){	this->parts.pos = (NanairoLib::Vector2)vec;	}

		void Init();
		void Step();
		void Draw2D();
		void Del(){}
	};
}

#endif