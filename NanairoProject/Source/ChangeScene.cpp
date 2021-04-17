#pragma once

//-------------------------------------
//NanairoProject
//-------------------------------------
#include <ChangeScene.h>
#include <TittleScene.h>
#include <PE_the_matchScene.h>
#include <RoomScene.h>

using namespace MYGAME;
using namespace NanairoLib;
using namespace std;

namespace NanairoProject
{
	//----------------------------------------------------------------------------------------------------------
	//static関数
	//
	MYGAME::Scene* SettingChangeScene(LPCSTR changeName, LPCSTR newName, MYGAME::Scene* old)
	{
		Scene* sc = GetScene( string( newName ) );
		return GetChangeScene( string( changeName) , sc, old );
	}

	MYGAME::Scene* GetScene(std::string& scName)
	{
		std::string::size_type type = scName.find( SCENE_TITLE );
		if( type != string::npos )
			return new NanairoProject::TittleScene();
		
		type = scName.find( SCENE_PE_MATCH );
		if( type != string::npos )
			return new NanairoProject::PE_the_matchScene();

		type = scName.find( SCENE_SELECTROOM );
		if( type != string::npos )
			return new NanairoProject::RoomScene();

		return NULL;
	}

	MYGAME::Scene* GetChangeScene(std::string& scName, Scene* nw, MYGAME::Scene* old)
	{
		std::string::size_type type = scName.find("FadeChange");
		if( type != string::npos )
			return new NanairoProject::FadeChangeScene( nw, old );
		return NULL;
	}

	/////////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------------
	/////////////////////////////////////////////////////////////////////////////

	FadeChangeScene::FadeChangeScene(MYGAME::Scene* newSC, MYGAME::Scene* oldSC)
	{
		this->sameInit( newSC, oldSC );
		this->Init();
	}

	void FadeChangeScene::Init()
	{
		this->fadeMove = &FadeChangeScene::fadeIn;
		this->fadeInSpd = this->fadeOutSpd = OFFSET_SPD_OF_CHANGESCREEN;
		this->waitSpd = OFFSET_SPD_OF_WAITSCREEN;
		this->back.ui.color.SettingFadeAlpha();
	}

	void FadeChangeScene::Step()
	{
		//過去になるシーンは最後までアクションさせること！
		if( this->oldScene )
			this->oldScene->Step();

		(this->*fadeMove)();
	}

	void FadeChangeScene::Draw2D()
	{
		this->back.Draw2D();
	}

	void FadeChangeScene::changeFadeSpd_andWaitSpd(float fadeInSpd,float waitSpd,float fadeOutSpd)
	{
		this->fadeInSpd = fadeInSpd;
		this->waitSpd = waitSpd;
		this->fadeOutSpd = fadeOutSpd;
	}

	void FadeChangeScene::fadeIn()
	{
		if( this->back.ui.color.FadeIn( this->fadeInSpd ) )
			this->fadeMove = &FadeChangeScene::Wait;
	}
	
	void FadeChangeScene::Wait()
	{
		if( this->IncrementFrameCnt( (int)this->waitSpd ) )
		{
			this->fadeMove = &FadeChangeScene::fadeOut;
			this->changeScene();
		}
	}
		
	void FadeChangeScene::fadeOut()
	{
		if( this->back.ui.color.FadeOut( this->fadeInSpd ) )
			this->GetManager()->Dispose( this );
	}
}