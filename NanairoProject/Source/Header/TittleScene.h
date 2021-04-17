#ifndef _NANAIRO_TITTLESCENE_H
#define _NANAIRO_TITTLESCENE_H

//-------------------------------------------------------
//
//タイトルクラス
//
//-------------------------------------------------------

///////////////////////////////////////////
//Default
///////////////////////////////////////////
#ifndef MYGAME_REDORCE_H
#include <ResourceFactory.h>
#endif

#ifndef _MYGAME_SHENE_H
#include <SceneMethod.h>
#endif

#ifndef _MYGAME_ONCEWORD_H
#include <OnceWord.h>
#endif

#ifndef _MYGANE_DIALOG_H
#include <Dialog.h>
#endif

///////////////////////////////////////////
//MYGAME
///////////////////////////////////////////
#ifndef _NANAIRO_EFFECTPARTS_H
#include <EffectParts.h>
#endif

namespace NanairoProject
{
	#define BGM_START_TIMING 1

	class TittleScene : public MYGAME::Scene
	{
		private:
			MYGAME::NameDialog								nameDialog;
			MYGAME::FlushingDialog							titleStart;
			MYGAME::BackGround_2D							back, alphaBack;

		public:
			TittleScene(){	this->Init();	}
			~TittleScene(){}

		private:
			void (TittleScene::*_action)();
			void TouchAction();
			void waitAndGoAction();
			void ChangeSceneAction();

			void InputStarEffect();
			void InputKirariEffect();
			void SePlay_go();

		protected:
			void Draw3D(){}
			void Draw2D();
	
		public:
			void Init();
			void Recircle(){}
			void Draw();
			void Atack(){}
			void Step();
			void Dispose();
			void Del(){}
	};


}

#endif