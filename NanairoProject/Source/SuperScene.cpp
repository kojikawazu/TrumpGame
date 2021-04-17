#pragma once

//---------------------------------------------------------
//MyDirectDLL
//---------------------------------------------------------
#include <MainFunction.h>
#include <fstream>
#include <MusicSound.h>

//---------------------------------------------------------
//MYGAME
//---------------------------------------------------------
#include <SceneMethod.h>
#include <ResourceFactory.h>

//---------------------------------------------------------
//Sceneを制御するクラス
//---------------------------------------------------------

using namespace NanairoLib;
using namespace std;

namespace MYGAME
{
	//---------------------------------------------------------
	//Sceneスーパークラス
	//---------------------------------------------------------
	Scene::Scene() : frameCnt(0), isAtack(true), isMove(true), isDraw(true), isRender(true), __manager(NULL), screen(NULL){
		screen = new NanairoLib::RenderScreen( DirectFunc GetMYdevice()->GetDevice(), 0 );
		this->effectList.ListClear();
	}

	Scene::~Scene()
	{
		ES_SAFE_DELETE( this->screen );
		this->effectList.ListClear();
		this->__manager = NULL;
	}

	void Scene::sceneLoad(LPCSTR fileName)
	{
		std::ifstream fs( fileName );
		this->loadObject( fs );
		fs.close();
	}

	void Scene::BGMStart()
	{
		MusicFactory::GetInstance()->GetBGM()->Play( this->bgmWord.c_str() );
	}

	void Scene::BGMStop()
	{
		MusicFactory::GetInstance()->GetBGM()->Stop( this->bgmWord.c_str() );
	}

	//-----------------------------------------------------------------------------------------------

	//---------------------------------------------------------
	//SceneManagerクラス
	//---------------------------------------------------------

	//---------------------------------------------------------
	//描画する前に呼ぶメソッド
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_before(short pass)
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		Text2DFactory* text = __GRAPHFACTORY;

		NanairoLib::MYDXData* mx = MFunc->GetMYdevice();
		if( !mx )	return false;
		
		//描画開始
		mx->GetDevice()->BeginScene();
		
		NanairoLib::Shader* sh;
		if( (sh = text->GetArtisan()->GetShader()) )
		{
			UINT numPass;
			if(SUCCEEDED(sh->Effect->Begin( &numPass, 0 ) ) )
			{
				if(SUCCEEDED(sh->Effect->BeginPass( pass ) ) )
					return true;
			}
		}
		return true;
	}

	//---------------------------------------------------------
	//描画する前に呼ぶメソッド（ラッピング）
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_beforeAction(int renderPass, int shaderPass,  NanairoLib::PRenderScreen screen)
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		NanairoLib::MYDXData* mx = MFunc->GetMYdevice();
		if( !mx )	return false;

		//ターゲットをこのシーンのサーフェイスに変えて
		if( screen != NULL)
			screen->ChangeTarGet(mx->GetDevice(), renderPass, 1 );
		
		return ( this->defaultDraw_before( shaderPass ) );
	}

	//---------------------------------------------------------
	//Shaderパスチェンジ
	//---------------------------------------------------------
	bool SceneManager::changeShaderPass(int passNumber, NanairoLib::PRenderScreen screen)
	{
		if( !screen )	return false;
		Text2DFactory* text = __GRAPHFACTORY;
		NanairoLib::Shader* sh;
		if( (sh = text->GetArtisan()->GetShader()) != NULL )
		{
			sh->Effect->EndPass();
			sh->Effect->BeginPass( passNumber );
			return true;
		}
		else
			return false;
	}

	//---------------------------------------------------------
	//描画終了メソッド
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_after()
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		Text2DFactory* text = __GRAPHFACTORY;

		//シェーダの終了
		NanairoLib::Shader* sh;
		if( (sh = text->GetArtisan()->GetShader()) )
		{
			sh->Effect->EndPass();
			sh->Effect->End();
		}

		//描画の終了
		MFunc->GetMYdevice()->GetDevice()->EndScene();
		return true;
	}

	//---------------------------------------------------------
	//描画終了メソッド（ラッピング）
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_afterAction(NanairoLib::PRenderScreen screen)
	{
		this->defaultDraw_after();
		
		//デフォルトのバッファに戻す
		MainFunction* MFunc = MainFunction::GetInstance();
		if( screen )
			screen->ChangeTarGet( MFunc->GetMYdevice()->GetDevice() );

		Text2DFactory::GetInstance()->SetAlpha( NanairoLib::BLEND_ALPHA1 );
		return true;
	}

	//---------------------------------------------------------
	//シーンの追加
	//---------------------------------------------------------
	void SceneManager::Add_insert(Scene* pass,int passNumber)
	{
		SceneIterator it = this->sceneList.begin();
		int cnter = 0;
		while( it != this->sceneList.end() )
		{
			if( cnter == passNumber ){
				this->sceneList.insert( it , pass );
				return ;
			}
			cnter++;
			it++;
		}
		this->sceneList.push_back( pass );
	}

	//---------------------------------------------------------
	//シーンのイテレータを取得
	//---------------------------------------------------------
	SceneIterator SceneManager::GetPassIte(short pass)
	{
		if( pass < 0 || pass > this->listSum && this->sceneList.empty() )	
			return this->sceneList.end();
		SceneIterator it = this->sceneList.begin();
		int cnter = 0;
		while( it != this->sceneList.end() )
		{
			if( cnter == pass )	return it;
			else				it++;
		}

		return it;
	}

	SceneIterator SceneManager::GetPassIte(Scene* pass)
	{
		if( this->sceneList.empty() )	return this->sceneList.end();
		SceneIterator it = this->sceneList.begin();
		while( it != this->sceneList.end() )
		{
			if( (*it) == pass )	return it;
			else				it++;
		}
		return this->sceneList.end();
	}

	//-------------------------------------------------------------------------

	//---------------------------------------------------------
	//シーンの追加
	//---------------------------------------------------------
	void SceneManager::Add(Scene* pass)
	{
		this->SettingManager( pass );
		this->sceneList.push_back( pass );
		this->listSum++;
	}

	//---------------------------------------------------------
	//シーンの挿入
	//---------------------------------------------------------
	void SceneManager::Add_toListNumber(Scene* pass,int passNumber)
	{
		( (passNumber < -1 || passNumber >= listSum) ? 
			this->sceneList.push_back( pass ) : this->Add_insert( pass, passNumber ) );
		this->SettingManager( pass );
		listSum++;
	}

	void SceneManager::Add_toScenePass(Scene* pass,Scene* nearPass)
	{
		if( !nearPass )
		{
			this->Add( pass );
			return ;
		}
		SceneIterator it = this->sceneList.begin();
		while( it != this->sceneList.end() )
		{
			if( (*it) == nearPass )
			{
				this->SettingManager( pass );
				this->sceneList.insert( it , pass );
				this->listSum++;
				return ;
			}
			it++;
		}
		this->Add( pass );
	}

	//-------------------------------------------------------------------------

	//---------------------------------------------------------
	//シーンのデリート
	//---------------------------------------------------------
	void SceneManager::Dispose(int passNumber)
	{
		SceneIterator it = this->GetPassIte( passNumber );
		if( it != this->sceneList.end() )
		{
			ES_SAFE_DELETE( (*it) );
			it = this->sceneList.erase( it );
		}
	}

	void SceneManager::Dispose(Scene* pass)
	{
		SceneIterator it = this->GetPassIte( pass );
		if( it != this->sceneList.end() )
		{
			(*it)->Dispose();
			ES_SAFE_DELETE( (*it) );
			it = this->sceneList.erase( it );
			this->listSum--;
		}
	}

	//-------------------------------------------------------------------------

	//---------------------------------------------------------
	//シーンの切り離し
	//---------------------------------------------------------
	Scene* SceneManager::unlink(Scene* pass)
	{
		if( this->sceneList.empty() )	return NULL;
		Scene* lik = NULL;
		SceneIterator it = this->sceneList.begin();
		while( it != this->sceneList.end() )
		{
			if( (*it) == pass )
			{
				lik = (Scene*)(*it);
				it = this->sceneList.erase( it );
				this->listSum--;
				break;
			}
			else
				it++;
		}
		return lik;
	}
	
	Scene* SceneManager::unlink(int pass)
	{
		if( this->sceneList.empty() )	return NULL;

		SceneIterator it = this->GetPassIte( pass );
		Scene* lik = NULL;
		if( it != this->sceneList.end() )
		{
			lik = (Scene*)(*it);
			it = this->sceneList.erase( it );
			this->listSum--;
		}
		return lik;
	}

	Scene* SceneManager::unlink(Scene* pass, Scene* newScene)
	{
		if( this->sceneList.empty() )
		{
			this->Add( newScene );
			return NULL;
		}

		SceneIterator it = this->sceneList.begin();
		while( it != this->sceneList.end() )
		{
			if( (*it) == pass )
			{
				it = this->sceneList.insert( it , newScene );
				it = this->sceneList.erase( it );
				this->listSum--;
				return (Scene*)(*it);
			}
			else
				it++;
		}
		this->Add( newScene );
		return NULL;
	
	}
	//-------------------------------------------------------------------------

	//---------------------------------------------------------
	//シーンを一気に消す
	//---------------------------------------------------------
	void SceneManager::listClear()
	{
		if( this->sceneList.empty() )	return ;

		SceneIterator it = this->sceneList.begin();
		while( it != this->sceneList.end() )
		{
			(*it)->Dispose();
			ES_SAFE_DELETE( (*it) );
			it = this->sceneList.erase( it );
			this->listSum--;
		}
	}

	void SceneManager::Del()
	{
		if( this->sceneList.empty() )	return;
		for(SceneIterator it = this->sceneList.begin();
			it != this->sceneList.end(); it++ )
			(*it)->Del();
	}

	//-------------------------------------------------------------------------

	//---------------------------------------------------------
	//pass番目のシーンの取得
	//---------------------------------------------------------
	Scene* SceneManager::GetScene(int pass)
	{
		SceneIterator it = this->GetPassIte( pass );
		return ( it != this->sceneList.end() ? (Scene*)(*it) : NULL );
	}

	//-------------------------------------------------------------------------

	//---------------------------------------------------------
	//アクション
	//---------------------------------------------------------
	void SceneManager::Step()
	{
		//--------------------------------------------
		//シーンのアクション
		//--------------------------------------------
		SceneIterator it = this->sceneList.begin();
		int size = this->sceneList.size();
		while( it != this->sceneList.end() )
		{
			if( (*it)->isMove )
				(*it)->Step();
			if( this->sceneList.empty() || size != this->sceneList.size() )
				break;
			else
			{
				it++;
				size = this->sceneList.size();
			}
		}
	}

	//---------------------------------------------------------
	//シーンのあたり判定
	//---------------------------------------------------------
	void SceneManager::Atack()
	{
		SceneIterator it = this->sceneList.begin();
		int size = this->sceneList.size();
		while( it != this->sceneList.end() )
		{
			if( (*it)->isAtack )
				(*it)->Atack();
			if( this->sceneList.empty() || size == this->sceneList.size() )
				break;
			else
			{
				it++;
				size = this->sceneList.size();
			}
		}
	}

	//---------------------------------------------------------
	//シーンの３Ｄ描画
	//---------------------------------------------------------
	void SceneManager::Draw()
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		Text2DFactory* text = __GRAPHFACTORY;

		//クリア
		HRESULT hr = MFunc->GetMYdevice()->GetDevice()->Clear(
			0,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			0x00000000, 1.0f, 0);

		//描画中
		for(SceneIterator it = this->sceneList.begin(), end = this->sceneList.end();
			it != end; it++)
		{
			if( (*it)->isDraw )
				(*it)->Draw();
		}
		
		////クリアします
		//MFunc->GetMYdevice()->GetDevice()->Clear(
		//	0,
		//	NULL,
		//	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//	0x00000000, 1.0f, 0);
		////終わると板ポリに書かれたシーンを塗っていく
		//if( !this->sceneList.empty() ){
		//	it = this->sceneList.begin();
		//	::Artisan* ct = text->GetArtisan();

		//	Text2DFactory::GetInstance()->SetAlpha( NanairoLib::BLEND_ALPHA1 );
		//	this->defaultDraw_before( 0 );
		//	while( it != end )
		//	{
		//		if( (*it)->isRender )
		//		{
		//			ct->SetScreenTrans( (*it)->screen );
		//			ct->SetColor( &(*it)->screenColor.color );
		//			ct->DrawScreen( (*it)->screen->GetText() );
		//		}
		//		it++;
		//	}
		//	this->defaultDraw_after();
		//	Text2DFactory::GetInstance()->SetAlpha( NanairoLib::BLEND_ALPHA1 );
		//}

		//反映
		MFunc->GetMYdevice()->GetDevice()->Present( NULL, NULL, NULL, NULL );
	}

	//---------------------------------------------------------
	//保留
	//---------------------------------------------------------
	void SceneManager::SetDefaultMatrix()
	{
		::MainFunction* MFunc = ::MainFunction::GetInstance();
	}

	//---------------------------------------------------------
	//板ポリに描画したシーンをバックバッファに描画
	//---------------------------------------------------------
	void SceneManager::DrawScreen(NanairoLib::PRenderScreen screen, COLOR_BLEND_NUM blendNum)
	{
		Text2DFactory* text = __GRAPHFACTORY;
		Artisan* ct = text->GetArtisan();
		
		//描画の準備
		this->defaultDraw_before( 2 );

		//アルファ値を事前にチェンジ
		text->SetAlpha( blendNum );

		//描画セッティング
		ct->SetScreenTrans( screen );
		ct->SetColor( &screen->color.color );
		
		//描画
		ct->DrawScreen( screen->GetTexture() );

		//アルファ値を戻す
		text->SetAlpha( NanairoLib::BLEND_ALPHA1 );
		
		//描画終了
		this->defaultDraw_after();
	}
}