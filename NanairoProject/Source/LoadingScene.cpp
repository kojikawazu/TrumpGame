#pragma once

//////////////////////////////////////////////////////////////
//NanairoProject
#include <MainFunction.h>
#include <LoadingScene.h>
#include <ChangeScene.h>
#include <UseEffect.h>
#include <ChangeScene.h>

//////////////////////////////////////////////////////////////
//NanairoLib
#include <MusicSound.h>

using namespace MYGAME;
using namespace NanairoLib;
using namespace std;

//-----------------------------------------------------------------------------------
//以下２つはマルチスレッドで呼び出されるメソッド
//１，画像をロードするメソッド
//２，その他リソースをロードするメソッド
CRITICAL_SECTION cs;

void loadingThreadModel(int proc)
{
	::ExitThread( 0 );
}

void loadingThreadGraph(LoaderGraphList* proc)
{
	proc->main_load();
	::ExitThread( 1 );
}

//-----------------------------------------------------------------------------------

namespace NanairoProject
{
	//-------------------------------------------------------------
	void LoadingScene::Init()
	{
		isSucceess = this->initLoadingThread();
		this->SettingWord();
		this->back.SetBackName("backES");
	
		this->SetScene( NanairoProject::SettingChangeScene(
				CHANGE_FADE, SCENE_TITLE,  this ) );
	}

	void LoadingScene::Draw2D()
	{
		this->back.Draw2D();
		this->word.Draw();
		this->effectList.Draw();
	}

	void LoadingScene::Draw()
	{
		//最初に描画する宣言
		this->GetManager()->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );	
		
		this->Draw2D();

		//描画終了宣言
		this->GetManager()->defaultDraw_afterAction( screen );

		//描画したスクリーンをバックバッファに描画
		this->GetManager()->DrawScreen( this->screen );
	}

	//-------------------------------------------------------------

	bool LoadingScene::initLoadingThread()
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		LoadingField* ld1 = new LoadingField();
		LoadingField* ld2 = new LoadingField();
		this->graphLoader = new LoaderGraphList(MFunc->GetMYdevice()->GetDevice());


		ld1->loadHandle = ::CreateThread( NULL, 0 , 
			(::LPTHREAD_START_ROUTINE) loadingThreadModel,
			(LPVOID)0, 0, &ld1->threadID );
		if( !this->push( ld1 ) )
		{
			delete ld1;
			return false;
		}

		ld2->loadHandle = ::CreateThread( NULL, 0 , 
			(::LPTHREAD_START_ROUTINE) loadingThreadGraph,
			(LPVOID)this->graphLoader, 0, &ld2->threadID );
		if( !this->push( ld2 ) )
		{
			delete ld2;
			return false;
		}
		return true;
	}

	void LoadingScene::SettingWord()
	{
		std::string wd = "Now Loading";
		char ch=0;
		BoundingWord* bound;
		for(int i=0,siz=wd.size(); i<siz; i++)
		{
			ch = wd.at(i);
			bound = new BoundingWord();
			bound->SetChar(ch);
			bound->SetObject(&Vector2(SCRW_PERCENT(0.5f) + ONCEWORD_WIDTH * i, SCRH_PERCENT(0.8f)),
								0.0f, &Vector2(0.2f, 0.2f));
			this->word.Add(bound);
		}
	}

	void LoadingScene::Step()
	{
		if( !this->isStep )
			this->LoadingStep();

		this->effectList.Step();
		this->word.ChainStep(CHAIN_POSY);
		this->Step_intervalRipple();
		this->effectList.Del();
	}

	//-----------------------------------------------------------------------
	//波動っぽいエフェクトを１秒ごとに発生させる	
	void LoadingScene::Step_intervalRipple()
	{
		if( ++this->frameCnt % 60 == 0 )
		{
			MYGAME::RippleEffect* rp = new RippleEffect();
			rp->SetPos(Vector2(SCRW * 0.8f, SCRH * 0.8f));
			rp->SetColor(Textcolor(255,255,0,255));
			this->effectList.Add(rp);

			((BoundingWord*)(*this->word.GetBeginIterator()))->SetBounding(20);
		}

	}

	void LoadingScene::loadObject(std::ifstream& fs)
	{
		
	}

}
