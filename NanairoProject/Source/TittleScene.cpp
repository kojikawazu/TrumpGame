#pragma once
///////////////////////////////////////////////////////////
//
//タイトルシーンを作ってます
//
///////////////////////////////////////////////////////////

/////////////////////////////////////////////
//NanairoLib
/////////////////////////////////////////////
#include <MainFunction.h>
#include <MusicSound.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <TittleScene.h>
#include <ChangeScene.h>
#include <Rule_anime.h>
#include <TemplateEffectList.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	///////////////////////////////////////////////////////////
	//Init
	///////////////////////////////////////////////////////////
	void TittleScene::Init()
	{
		this->effectList.Init();
		this->SetBGMWord( "death" );

		//-----------------------------------------
		//背景の設定
		this->back.SetBackName("title");
		this->alphaBack.SetBackName("yozora");
		this->alphaBack.SetColor(Vector4(100,255,255,255));
		//-----------------------------------------
		//タイトルの設定
		this->nameDialog.SetName("titleName");
		this->nameDialog.SetObject( 
			Vector2( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.2f) ),
			0.0f, Vector2(450.0f, 120.0f) );
		//-----------------------------------------
		//ゲームスタートの設定
		this->titleStart.SetName("titleStart");
		this->titleStart.SetObject(
					Vector2( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.8f)),
					0.0f, Vector2( 400.0f, 100.0f ) );
		//-----------------------------------------

		//-----------------------------------------
		//星リストの設定
		TemplateEffectList<StarEffect*>* lis = new TemplateEffectList<StarEffect*>();
		lis->SetObject(Vector2(0,0));
		lis->SetDownStarAction();
		this->effectList.Add( lis );

		//タッチアクション
		this->_action = &TittleScene::TouchAction;
	}

	void TittleScene::Dispose()
	{
		this->effectList.ListClear();
		this->BGMStop();
	}

	///////////////////////////////////////////////////////////
	//Action
	///////////////////////////////////////////////////////////
	void TittleScene::TouchAction()
	{
		if(++this->frameCnt == BGM_START_TIMING)	this->BGMStart();

		if( __KEYDATA->trg[ KZ ] || __MOUSEDATA->trg[LBUTTON])
		{
			this->_action = &TittleScene::waitAndGoAction;
			this->InputStarEffect();
			this->SePlay_go();
			this->frameCnt = 0;
			this->InputKirariEffect();
		}
	}
	
	void TittleScene::InputStarEffect()
	{
		MagicstarEffect* ef = new MagicstarEffect();
		this->effectList.Add( ef );
	}

	void TittleScene::SePlay_go()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play("go_se" );
	}

	void TittleScene::InputKirariEffect()
	{
		MouseKirariEffect* ef = new MouseKirariEffect();
		ef->SetObject(Vector2((float)__MOUSEDATA->mouseX, (float)__MOUSEDATA->oldMouseY));
		this->effectList.Add( ef );	
	}

	void TittleScene::waitAndGoAction()
	{
		if( this->IncrementFrameCnt( 30 ) )
			this->back.ui.scale.Add( SCRW_PERCENT(0.01f), SCRH_PERCENT(0.01f) );
			
		if( this->IsInterval( 60 ) )
		{
			this->frameCnt = 0;
			this->_action = &TittleScene::ChangeSceneAction;

			Scene* sc = NanairoProject::SettingChangeScene(
				CHANGE_FADE, SCENE_SELECTROOM,  this );
			
			( sc != NULL ? this->GetManager()->Add( sc ) : this->GetManager()->Dispose( this ) );
		}
	}

	void TittleScene::ChangeSceneAction()
	{
		this->back.ui.scale.Add( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f) );
	}

	void TittleScene::Step()
	{
		this->effectList.Step();
		this->titleStart.Step();

		(this->*_action)();
	}

	///////////////////////////////////////////////////////////
	//Draw
	///////////////////////////////////////////////////////////
	void TittleScene::Draw2D()
	{
		Text2DFactory* gh = __GRAPHFACTORY;
		
		this->back.Draw2D();

		gh->SetAlpha( BLEND_ALPHA2 );
		this->alphaBack.Draw2D();
		gh->SetAlpha( BLEND_ALPHA1 );

		gh->SetAlpha( BLEND_ALPHA2 );		
		this->titleStart.Draw2D();
		this->nameDialog.Draw2D();
		gh->SetAlpha( BLEND_ALPHA1 );
	
		this->effectList.Draw();	
	}

	void TittleScene::Draw()
	{
		SceneManager* mr = this->GetManager();
		//最初に描画する宣言
		mr->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );	

		this->Draw2D();

		mr->defaultDraw_afterAction( screen );

		mr->DrawScreen( this->screen );
	}

	///////////////////////////////////////////////////////////
	//End
	///////////////////////////////////////////////////////////
}