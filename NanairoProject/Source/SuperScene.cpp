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
//Scene�𐧌䂷��N���X
//---------------------------------------------------------

using namespace NanairoLib;
using namespace std;

namespace MYGAME
{
	//---------------------------------------------------------
	//Scene�X�[�p�[�N���X
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
	//SceneManager�N���X
	//---------------------------------------------------------

	//---------------------------------------------------------
	//�`�悷��O�ɌĂԃ��\�b�h
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_before(short pass)
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		Text2DFactory* text = __GRAPHFACTORY;

		NanairoLib::MYDXData* mx = MFunc->GetMYdevice();
		if( !mx )	return false;
		
		//�`��J�n
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
	//�`�悷��O�ɌĂԃ��\�b�h�i���b�s���O�j
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_beforeAction(int renderPass, int shaderPass,  NanairoLib::PRenderScreen screen)
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		NanairoLib::MYDXData* mx = MFunc->GetMYdevice();
		if( !mx )	return false;

		//�^�[�Q�b�g�����̃V�[���̃T�[�t�F�C�X�ɕς���
		if( screen != NULL)
			screen->ChangeTarGet(mx->GetDevice(), renderPass, 1 );
		
		return ( this->defaultDraw_before( shaderPass ) );
	}

	//---------------------------------------------------------
	//Shader�p�X�`�F���W
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
	//�`��I�����\�b�h
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_after()
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		Text2DFactory* text = __GRAPHFACTORY;

		//�V�F�[�_�̏I��
		NanairoLib::Shader* sh;
		if( (sh = text->GetArtisan()->GetShader()) )
		{
			sh->Effect->EndPass();
			sh->Effect->End();
		}

		//�`��̏I��
		MFunc->GetMYdevice()->GetDevice()->EndScene();
		return true;
	}

	//---------------------------------------------------------
	//�`��I�����\�b�h�i���b�s���O�j
	//---------------------------------------------------------
	bool SceneManager::defaultDraw_afterAction(NanairoLib::PRenderScreen screen)
	{
		this->defaultDraw_after();
		
		//�f�t�H���g�̃o�b�t�@�ɖ߂�
		MainFunction* MFunc = MainFunction::GetInstance();
		if( screen )
			screen->ChangeTarGet( MFunc->GetMYdevice()->GetDevice() );

		Text2DFactory::GetInstance()->SetAlpha( NanairoLib::BLEND_ALPHA1 );
		return true;
	}

	//---------------------------------------------------------
	//�V�[���̒ǉ�
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
	//�V�[���̃C�e���[�^���擾
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
	//�V�[���̒ǉ�
	//---------------------------------------------------------
	void SceneManager::Add(Scene* pass)
	{
		this->SettingManager( pass );
		this->sceneList.push_back( pass );
		this->listSum++;
	}

	//---------------------------------------------------------
	//�V�[���̑}��
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
	//�V�[���̃f���[�g
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
	//�V�[���̐؂藣��
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
	//�V�[������C�ɏ���
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
	//pass�Ԗڂ̃V�[���̎擾
	//---------------------------------------------------------
	Scene* SceneManager::GetScene(int pass)
	{
		SceneIterator it = this->GetPassIte( pass );
		return ( it != this->sceneList.end() ? (Scene*)(*it) : NULL );
	}

	//-------------------------------------------------------------------------

	//---------------------------------------------------------
	//�A�N�V����
	//---------------------------------------------------------
	void SceneManager::Step()
	{
		//--------------------------------------------
		//�V�[���̃A�N�V����
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
	//�V�[���̂����蔻��
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
	//�V�[���̂R�c�`��
	//---------------------------------------------------------
	void SceneManager::Draw()
	{
		MainFunction* MFunc = MainFunction::GetInstance();
		Text2DFactory* text = __GRAPHFACTORY;

		//�N���A
		HRESULT hr = MFunc->GetMYdevice()->GetDevice()->Clear(
			0,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			0x00000000, 1.0f, 0);

		//�`�撆
		for(SceneIterator it = this->sceneList.begin(), end = this->sceneList.end();
			it != end; it++)
		{
			if( (*it)->isDraw )
				(*it)->Draw();
		}
		
		////�N���A���܂�
		//MFunc->GetMYdevice()->GetDevice()->Clear(
		//	0,
		//	NULL,
		//	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//	0x00000000, 1.0f, 0);
		////�I���Ɣ|���ɏ����ꂽ�V�[����h���Ă���
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

		//���f
		MFunc->GetMYdevice()->GetDevice()->Present( NULL, NULL, NULL, NULL );
	}

	//---------------------------------------------------------
	//�ۗ�
	//---------------------------------------------------------
	void SceneManager::SetDefaultMatrix()
	{
		::MainFunction* MFunc = ::MainFunction::GetInstance();
	}

	//---------------------------------------------------------
	//�|���ɕ`�悵���V�[�����o�b�N�o�b�t�@�ɕ`��
	//---------------------------------------------------------
	void SceneManager::DrawScreen(NanairoLib::PRenderScreen screen, COLOR_BLEND_NUM blendNum)
	{
		Text2DFactory* text = __GRAPHFACTORY;
		Artisan* ct = text->GetArtisan();
		
		//�`��̏���
		this->defaultDraw_before( 2 );

		//�A���t�@�l�����O�Ƀ`�F���W
		text->SetAlpha( blendNum );

		//�`��Z�b�e�B���O
		ct->SetScreenTrans( screen );
		ct->SetColor( &screen->color.color );
		
		//�`��
		ct->DrawScreen( screen->GetTexture() );

		//�A���t�@�l��߂�
		text->SetAlpha( NanairoLib::BLEND_ALPHA1 );
		
		//�`��I��
		this->defaultDraw_after();
	}
}