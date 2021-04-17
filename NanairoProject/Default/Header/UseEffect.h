#ifndef _NANAIRO_USEEFFECT_H
#define	_NANAIRO_USEEFFECT_H

#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

//----------------------------------------------------
//
//２Ｄエフェクトは汎用オブジェクトを継承しているので
//テンプレートリストに追加可能
//
//----------------------------------------------------

namespace MYGAME
{
	////////////////////////////////////////////////////////////////////////////////
	//8切りエフェクト素材
	//カットエフェクト
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
	//万華鏡スクリーンエフェクト素材
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
	//矢印エフェクト素材
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
	//伸ばし鎖エフェクト素材
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
	//回し鎖エフェクト素材
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
	//波紋エフェクト素材
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
	//スクリーン上でボールが移動するエフェクト素材
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
	//こうもりアニメーションエフェクト素材
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
	//炎切りエフェクト
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
	//キラリエフェクト
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
	//星エフェクト（普通）
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
	//星エフェクト（ランダムに外へ逃げていく）
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
	//星エフェクト（↓へ落ちてバウンドする）
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
	//花火エフェクト素材
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
	//勝利したときのエフェクト素材
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
	//星魔法エフェクト素材
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
	//マウスタッチエフェクト素材
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