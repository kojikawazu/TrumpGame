#ifndef _NANAIRO_LOADINGSCENE_H
#define _NANAIRO_LOADINGSCENE_H

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

//ロードシーンをおいていきます
namespace NanairoProject
{
	//nowloadingの１文字ずつの幅
	#define ONCEWORD_WIDTH	30

	//最初にロードするシーン
	class LoadingScene : public MYGAME::SuperLoading
	{		
		protected:
			MYGAME::BackGround_2D							back;
		public:
			LoadingScene(){		this->Init();	}
			~LoadingScene(){	this->effectList.ListClear();	}

		protected:
			void Draw2D();
			void loadObject(std::ifstream& fs);

		public:
			void Init();
			void Step();
			void Draw();
		
		private:
			bool initLoadingThread();
			void SettingWord();
			void Step_intervalRipple();
	};

	//char ch[256];
	//::GetCurrentDirectory( 256, ch );	
		
}


#endif