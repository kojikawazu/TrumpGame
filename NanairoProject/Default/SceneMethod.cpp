#pragma once

//---------------------------------------------------------
//MyDirectDLL
//---------------------------------------------------------
#include <MainFunction.h>
#include <fstream>
#include <MusicSound.h>
#include <DebugString.h>

//---------------------------------------------------------
//MYGAME
//---------------------------------------------------------
#include <SceneMethod.h>
#include <ResourceFactory.h>
#include <UseEffect.h>

//---------------------------------------------------------
//色々なシーンの大元のスーパーシーンクラス
//---------------------------------------------------------

using namespace NanairoLib;
using namespace std;

namespace MYGAME
{
	//---------------------------------------------------------
	//ロードのスーパーシーンクラス
	//---------------------------------------------------------
	SuperLoading::~SuperLoading()
	{
		this->word.Clear();
		ES_SAFE_DELETE( this->nextScene );
		ES_SAFE_DELETE( this->graphLoader );
	}

	void SuperLoading::LoadingStep()
	{
		if( !this->isSucceess )
			this->GetManager()->Dispose( this );

		//::WaitForMultipleObjects( 2, (*this->loader.begin())->loadHandle, TRUE, INFINITE );
		if( !isFinished && isFinish() )
			isFinished = !isFinished;
		else if( isFinished && ++this->timeoutCnt > TIMEOUT_MAX )
		{
			if( !CHECK_NULL(this->nextScene) )
			{	
				this->graphLoader->stockStep();
				if(this->graphLoader->finishFlag)
				{
					if(!CHECK_NULL(this->graphLoader != NULL) )
					{
						this->graphLoader->Pushing();
						ES_SAFE_DELETE( this->graphLoader );
					}
					this->GetManager()->Add( this->nextScene );
					this->nextScene = NULL;
					this->isMove = false;
					this->isStep = true;
				}
			}
			else
				this->GetManager()->Dispose( this );
		}
	}

	bool SuperLoading::push(LoadingField* field)
	{
		if( CHECK_NULL(field->loadHandle) )
			return false;
		this->loader.push_back( field );
		return true;
	}

	void SuperLoading::closeLoadingThread()
	{	
		do{}while( !this->isFinish() );
		LoaderIterator it = this->loader.begin();
		LoadingField* fd;
		while( it != this->loader.end() )
		{
			fd = (*it);
			if( fd->loadHandle )
				::CloseHandle( fd->loadHandle );
			it = this->loader.erase( it );
			ES_SAFE_DELETE( fd );
		}
	}

	bool SuperLoading::isFinish()
	{
		LoaderIterator it = this->loader.begin();
		DWORD word;
		while( it != this->loader.end() )
		{
			if( (*it)->loadHandle )
			{
				::GetExitCodeThread( (*it)->loadHandle, &word );
				if( word == STILL_ACTIVE )
					return false;
				else if(word == 1)
					return true;
			}
			it++;
		}
		return true;
	}

	//---------------------------------------------------------
	//SuperChangeSceneクラス
	//---------------------------------------------------------
	void SuperChangeScene::sameInit(MYGAME::Scene* newSC, MYGAME::Scene* oldSC)
	{
		newScene = newSC;
		oldScene = oldSC;
		back.SetBackName( "black" );
		this->timingChange = TIMING_DEFAULT_CHANGE;
		this->timingDispose = TIMING_DEFAULT_DISPOSE;
	}

	void SuperChangeScene::Step()
	{
		if( ++this->frameCnt == this->timingChange )
			this->changeScene();
		else if( this->frameCnt == this->timingDispose )
			this->GetManager()->Dispose( this );
	}

	void SuperChangeScene::Draw()
	{
		//最初に描画する宣言
		this->GetManager()->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );	
		
		Text2DFactory::GetInstance()->SetAlpha( NanairoLib::BLEND_ALPHA1 );
		
		this->Draw2D();

		this->GetManager()->defaultDraw_afterAction( screen );

		this->GetManager()->DrawScreen( this->screen );
	}

	void SuperChangeScene::Dispose()
	{
		oldScene = NULL;
		ES_SAFE_DELETE( newScene );
		newScene = NULL;
	}

	void SuperChangeScene::changeScene()
	{
		if( !CHECK_NULL(this->oldScene) )
		{
			this->GetManager()->Dispose( this->oldScene );
			this->oldScene = NULL;
		}

		if( !CHECK_NULL(this->newScene) )
		{
			this->GetManager()->Add_toScenePass( this->newScene, this );
			this->newScene = NULL;
		}
	}

	//-----------------------------------------------------------------------------------------------
	
	//-----------------------------------------------------------
	//ルームを作るときに継承するルームクラス
	//-----------------------------------------------------------
	void SuperRoom::UpdownMusic()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play( updownWord.c_str() );
	}

	void SuperRoom::okMusic()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play( okWord.c_str() );	
	}

	bool SuperRoom::StandardStep()
	{
		bool hantei = true;
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++)
		{
			(*it)->Step();	
			if( ((FadeNameDialog*)(*it))->IsWait() )	hantei = false;
		}
		return hantei;
	}

	void SuperRoom::Standard_SetFadeIn()
	{
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++)
			((FadeNameDialog*)(*it))->SetFadeIn();
	}

	void SuperRoom::Standard_SetFadeOut()
	{
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++)
			((FadeNameDialog*)(*it))->SetFadeOut();
	}

	void SuperRoom::Standard_Draw2D()
	{
		for(std::list<PNormalObject>::iterator it = this->dialogList.Begin();
			it != this->dialogList.End(); it++)
			(*it)->Draw2D();
	}

	//---------------------------------------------------------------------

	//-----------------------------------------------------------
	//ルームシーンを作る時に継承するルームのシーンクラス
	//-----------------------------------------------------------
	void SuperRoomScene::Init()
	{
		this->effectList.Init();
		this->gameMode = GAMEMODE_NEWGAME;
		this->serverFlag = false;
		this->SEupdown = "ok_se";
		this->SEok = "go_se";
		this->SEback = "no_se";

		//------------------------------------------
		//RoomPointerの初期化
		//------------------------------------------
		this->nowPoint = NULL;
		this->nextPoint = NULL;
		this->yesnoDialog = NULL;

		//------------------------------------------
		//データの初期化
		//------------------------------------------
		this->SetTouchActions();
	}

	void SuperRoomScene::Dispose()
	{
		ES_SAFE_DELETE( this->nowPoint );
		ES_SAFE_DELETE( this->nextPoint );
		ES_SAFE_DELETE( this->yesnoDialog );
		
		this->effectList.ListClear();
		this->BGMStop();
	}

	void SuperRoomScene::playSE_updown()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play( this->SEupdown.c_str() );
	}

	void SuperRoomScene::playSE_ok()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play( this->SEok.c_str() );
	}

	void SuperRoomScene::playSE_back()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play( this->SEback.c_str() );
	}

	void SuperRoomScene::SetBackToTittle()
	{
		this->_action = &SuperRoomScene::WaitAndBackAction;
		this->nowPoint->SetFadeOut();
	}

	void SuperRoomScene::SetGoToGame()
	{
		this->frameCnt = 0;
		this->_action = &SuperRoomScene::waitAndGoAction;
		this->nowPoint->SetFadeOut();
	}

	void SuperRoomScene::SetYesnoDialog()
	{
		this->_action = &SuperRoomScene::YesnoDialogAction;
		this->yesnoDialog = new YesNoDialog();
	}

	void SuperRoomScene::SetChangeDialog(SuperRoom* next)
	{	
		if( CHECK_NULL( next ) )	return ;
		this->nextPoint = next;
		this->_action = &SuperRoomScene::WaitAndChangeDialogAction;
		this->nowPoint->SetFadeOut();
	}

	void SuperRoomScene::Step()
	{
		this->effectList.Step();
		this->afterEffectList.Step();

		if( ++this->frameCnt % 5 == 0 )
		{
			BallScreenMoveEffect* ef = new BallScreenMoveEffect();
			ef->SetColor(Textcolor(50.0f, (float)(rand() % 255), (float)(rand() % 255), (float)(rand() % 255)));
			this->effectList.Add( ef );
		}

		this->effectList.Del();
		this->afterEffectList.Del();

		(this->*_action)();
	}

	void SuperRoomScene::Draw2D()
	{
		this->back.Draw2D();
	
		this->effectList.Draw();
		
		this->nowPoint->Draw2D();

		if( !CHECK_NULL( this->yesnoDialog ) )
			this->yesnoDialog->Draw2D();
		
		this->afterEffectList.Draw();
	}

	void SuperRoomScene::Draw()
	{
		//最初に描画する宣言
		this->GetManager()->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );	

		this->Draw2D();

		this->GetManager()->defaultDraw_afterAction( screen );

		this->GetManager()->DrawScreen( this->screen );
	}
}