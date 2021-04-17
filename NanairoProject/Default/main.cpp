#pragma once
#define _ISUSE__SHADER

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
//-------------------------------------------------------------------------------------
//MyDirectDLL
//-------------------------------------------------------------------------------------
#include <EffekseerFactory.h>
#include <MainFunction.h>
#include <MusicSound.h>
#include <AnimationMesh.h>
#include <DirectWindow.h>
using namespace NanairoLib;

MY_HIERARCHY MY_MESH::hierarchy;
MusicFactory* MusicFactory::_music = 0;
MainFunction* MainFunction::MainFunc = 0;
EffekseerClass* EffekseerClass::efekseer = 0;

//-------------------------------------------------------------------------------------
//MYGANE
//-------------------------------------------------------------------------------------
#include <ResourceFactory.h>
#include <SceneMethod.h>
using namespace MYGAME;

#include <LoadingScene.h>
#include <ShaderTest.h>
using namespace NanairoProject;

Text2DFactory* Text2DFactory::_2DGraph = 0;
Model3DFactory* Model3DFactory::_3DModel = 0;

//**************************************************************************************

//--------------------------------------------------------------------------------------
//������
//--------------------------------------------------------------------------------------
bool init_DirectX(HINSTANCE hInst)
{
	MainFunction* MFunc = MainFunction::GetInstance();
	if( !MFunc->InitDirectX( hInst ) )
	{
		::MessageBoxA( NULL, "Window�G���[�ł��B", "CreateWindow", MB_OK );
		MFunc->deleteInstance();
		return false;
	}

	//----------------------------------------------------------------------------------
	//�����Ɉ�x����������
	//----------------------------------------------------------------------------------
	
	//Artisan
	MFunc->GetArtisan()->InitShader( "./Default/Shader/Shader.fx" );
	MFunc->SetDefaultMatrix();

	//Effekseer
	EffekseerClass::GetInstance()->EffektInit( MFunc->GetMYdevice()->GetDevice() );
	EffekseerClass::GetInstance()->RenderUpdate( &NanairoLib::CAMERA( 0 ) );

	//Music
	MusicFactory::GetInstance()->GetMUSIC()->InitMusic( MFunc->GetMYdevice()->GetWindow() );
	//Graph2D
	Text2DFactory::GetInstance()->SetDevices( MFunc->GetMYdevice()->GetDevice() );
	Text2DFactory::GetInstance()->SetArtisan( MFunc->GetArtisan() );
	//Model3D
	Model3DFactory::GetInstance()->SetDevices( MFunc->GetMYdevice()->GetDevice() );
	Model3DFactory::GetInstance()->SetShader( MFunc->GetArtisan()->GetShader() );
	//Mesh
	MY_MESH::GetHierarchy()->SetDevice( MFunc->GetMYdevice()->GetDevice() );
	MY_MESH::GetHierarchy()->SetShader( MFunc->GetArtisan()->GetShader() );

	//�����_���l������
	srand((unsigned int)::GetTickCount());

	//���[�h
	Text2DFactory::GetInstance()->main_loadGraph();
	Model3DFactory::GetInstance()->main_loadGraph();

	return true;
}

//--------------------------------------------------------------------------------------
//�����[�X
//--------------------------------------------------------------------------------------
void uninit_DirectX(){
	MainFunction* MFunc = MainFunction::GetInstance();
	
	EffekseerClass::deleteInstance();
	MusicFactory::deleteInstance();
	Text2DFactory::deleteInstance();
	Model3DFactory::deleteInstance();

	WinCreate win;
	//�f�o�C�X�̃f���[��
	win.UnInitDirect3D(MFunc->GetMYdevice()->Get3D9(),MFunc->GetMYdevice()->GetDevice());
	
	//DLL�ێ��f�[�^�̍폜
	MainFunction::deleteInstance();
}


void LoadMusic()
{
	BGMFactory* bgm = MusicFactory::GetInstance()->GetBGM();
	bgm->LoadMusic("Resource/Music/BGM/cafe.mp3", "cafe");
	bgm->LoadMusic("Resource/Music/BGM/death_tone.mp3", "death");
	bgm->LoadMusic("Resource/Music/BGM/vibrationheart.mp3", "viheart");
	SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
	se->LoadMusic("Resource/Music/SE/ok_se.wav", "ok_se");
	se->LoadMusic("Resource/Music/SE/go_se.wav", "go_se");
	se->LoadMusic("Resource/Music/SE/no_se.wav", "no_se");
	se->LoadMusic("Resource/Music/SE/card.wav", "urucard");
	se->LoadMusic("Resource/Music/SE/piron.wav", "piron");
	se->LoadMusic("Resource/Music/SE/hakusyu.wav", "winner");
	se->LoadMusic("Resource/Music/SE/kansei.wav", "score");
	se->LoadMusic("Resource/Music/SE/kiri.wav", "kiri");
	se->LoadMusic("Resource/Music/SE/back.wav", "back");
	se->LoadMusic("Resource/Music/SE/shakin.wav", "shakin");
	se->LoadMusic("Resource/Music/SE/shock.wav", "shock");
	se->LoadMusic("Resource/Music/SE/brake.wav", "brake");
	se->LoadMusic("Resource/Music/SE/fuwari.wav", "furari");
	se->LoadMusic("Resource/Music/SE/ban.wav", "ban");
	se->LoadMusic("Resource/Music/SE/bite.wav", "bite");
	se->LoadMusic("Resource/Music/SE/roll.wav", "roll");
	se->LoadMusic("Resource/Music/SE/shine.wav", "shine");
	se->LoadMusic("Resource/Music/SE/scoreout.wav", "scoreout");
}

//--------------------------------------------------------------------------------------
//���C��
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, char *lpCmdLine, int nCmdShow){
	::MainFunction* MFunc = MainFunction::GetInstance();
	//�f�o�b�O�t���O�BDEBUG���s���Ƀ��������[�N����������ƁA
#if _DEBUG
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	if( !::init_DirectX(hInst) )
		return -1;

	//--------------------------------------
	//FPS
	//--------------------------------------
	bool isDoing = true;
	unsigned int startTick = GetTickCount();
	int FPS = 0;

	//--------------------------------------
	//�V�[���}�l�[�W����V���ɓ���
	//--------------------------------------
	SceneManager* manager = new SceneManager();
	::LoadMusic();
	manager->Add( new LoadingScene() );
	
	EffekseerClass* efk = EffekseerClass::GetInstance();
	

	while( isDoing )
	{
		::Sleep(0);	//OS�ɂ��������񂵂Ă�����B
		MSG msg;
		while(::PeekMessageA(&msg,NULL,0U,0U,PM_REMOVE) != 0){
			::DispatchMessageA(&msg);
			if(msg.message == WM_QUIT)	
				isDoing = false;
		}
		if( !isDoing )	break;

		//-------------------
		//�L�[�`�F�b�N
		//-------------------
		MFunc->GetKey()->CheckKeys( MFunc->GetMYdevice()->GetWindow() );

		//-------------------
		//�A�N�V����
		//-------------------
		manager->Step();
		manager->Atack();

		//-------------------
		//Effekseer�̍X�V
		//-------------------
		efk->EffektUpdate();

		//-------------------
		//�`��
		//-------------------
		manager->Draw();

		//-------------------------
		//�L�����I�u�W�F�N�g�̍폜
		//-------------------------
		manager->Del();

		//-------------------
		// FPS�\��
		//-------------------
		unsigned int nowTick = GetTickCount();
		if(nowTick-startTick > 1000){
			char str[256];
			sprintf_s(str, "FPS: %d\n", FPS);

			OutputDebugString(str);
			FPS = 0;
			startTick = nowTick;
		}else FPS++;
	}
	
	//-----------------------
	//�I������
	//-----------------------
	ES_SAFE_DELETE( manager );			
	::uninit_DirectX();					//DirectX�̃f���[�g
	return 0;
}
#pragma endregion


