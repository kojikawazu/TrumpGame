#ifndef _NANAIRO_CHANGESCENE_H
#define _NANAIRO_CHANGESCENE_H

///////////////////////////////////////////
//DirectStandard and std
///////////////////////////////////////////
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef _LIST_
#include <list>
#endif

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

namespace NanairoProject
{
	//////////////////////////////////////////////
	//ChangeŒQ
	//////////////////////////////////////////////
	#define CHANGE_FADE			"FadeChange"

	//////////////////////////////////////////////
	//SceneŒQ
	//////////////////////////////////////////////
	#define SCENE_TITLE			"TittleScene"
	#define SCENE_PE_MATCH		"PE_MatchScene"
	#define SCENE_SELECTROOM	"RoomScene"

	//////////////////////////////////////////////
	//OFFSET
	//////////////////////////////////////////////
	#define OFFSET_SPD_OF_CHANGESCREEN	5
	#define OFFSET_SPD_OF_WAITSCREEN	3

	extern MYGAME::Scene* SettingChangeScene(LPCSTR changeName, LPCSTR newName, MYGAME::Scene* old);
	extern MYGAME::Scene* GetScene(std::string& scName);
	extern MYGAME::Scene* GetChangeScene(std::string& scName, MYGAME::Scene* nw, MYGAME::Scene* old);

	class FadeChangeScene : public MYGAME::SuperChangeScene
	{
		private:
			float fadeInSpd, waitSpd, fadeOutSpd;
		public:
			FadeChangeScene(){}
			FadeChangeScene(MYGAME::Scene* newSC, MYGAME::Scene* oldSC = NULL);
		public:
			void Init();
			void Step();
			void Draw2D();

		public:
			void changeFadeSpd_andWaitSpd(float fadeInSpd,float waitSpd,float fadeOutSpd);

		private:
			void (FadeChangeScene::*fadeMove)();
			void fadeIn();
			void Wait();
			void fadeOut();
	};
}

#endif