#ifndef _MYGAME_SUPERSHENE_H
#define _MYGAME_SUPERSHENE_H

//--------------------------------------------------------
//
//�Q�[���̃V�[���ƃV�[���}�l�[�W���̃N���X�w�b�_
//
//--------------------------------------------------------

//std--------------
#ifndef _LIST_
#include <list>
#endif

//MYGAME-------------
#ifndef _MYGAME_UIPARTS_H
#include <UIParts.h>
#endif

namespace MYGAME
{
	class Scene;
	class SceneManager;

	typedef std::list<Scene*>			SceneList;
	typedef std::list<Scene*>::iterator SceneIterator;

	#define _FIRST_SCENE	"1stLoader"
	#define _CHANGE_SCENE1	"ChangeScene1"

	#define _BACK_GROUND	"BackGround"
	#define _LOAD_NAME		"LoadName"

	enum SHADER_PASS
	{
		SHADER_MODE_3DNORMAL = 0, SHADER_MODE_3DCOLOR, SHADER_MODE_2DNORMAL,
	};

	//-----------------------------------------
	//�Q�[���̃V�[�������Ƃ��ɂ�����p������
	//-----------------------------------------
	class Scene
	{
		private:
			SceneManager*									__manager;
			std::string										bgmWord;
		protected:
			MYGAME::ObjectList<NanairoLib::PNormalObject>		effectList;
		public:
			bool						isAtack, isMove, isDraw, isRender;
			short						frameCnt, screenSum, screenNum;
			
			NanairoLib::PRenderScreen	screen;
			NanairoLib::Textcolor		screenColor;

		protected:

			//3D�`��
			virtual void Draw3D() = 0;
			
			//2D�`��
			virtual void Draw2D() = 0;

			//�t�@�C���e�L�X�g����f�[�^��ǂݍ���
			virtual void loadObject(std::ifstream& fs){}
		
			void sceneLoad(LPCSTR fileName);
		
		public:
			Scene();
			virtual ~Scene();

			//�P�x�ڂ̏�����
			virtual void Init() = 0;
			
			//���x���s��������
			virtual void Recircle() = 0;

			//�A�N�V����
			virtual void Step() = 0;
			
			//�`��
			virtual void Draw() = 0;
			
			//�����蔻�菈��
			virtual void Atack() = 0;

			//delete���Ɉꏏ�ɌĂ΂��
			virtual void Dispose() = 0;

			//�����[�v�̃t�B�[���h��delete���s��
			virtual void Del() = 0;

			void BGMStart();
			void BGMStop();

			//Getter
			SceneManager* GetManager() const{		return this->__manager;	}
			MYGAME::ObjectList<NanairoLib::PNormalObject>* GetEffectList(){	return &this->effectList;	}

			//Setter
			void SetManager(SceneManager* input){	this->__manager = input;	}
			void SetBGMWord(LPCTSTR in){			this->bgmWord = in;	}

			bool IncrementFrameCnt(int IntervalCnt){	return ( ++this->frameCnt >= IntervalCnt );	}
			bool IsInterval(int interval){			return (this->frameCnt >= interval);			}
			
	};

	//---------------------------------------------
	//�Q�[���̃V�[���͂��ׂĂ����ňꌳ�Ǘ����Ă���
	//---------------------------------------------
	class SceneManager
	{
		private:
			SceneList sceneList;
			int listSum;

		private:

			//add
			void Add_insert(Scene* pass,int passNumber);
			
			//Getter
			SceneIterator GetPassIte(short pass);
			SceneIterator GetPassIte(Scene* pass);
			
			//Setter
			void SettingManager(Scene* pass){	pass->SetManager( this );	}
			
			//default
			bool defaultDraw_before(short pass);
			bool defaultDraw_after();
		public:
			SceneManager() : listSum(0){	this->sceneList.clear();	}
			~SceneManager(){				this->listClear();			}

		public:
			void Step();
			void Draw();
			void Atack();
			void Del();

			void Add(Scene* pass);
			void Add_toListNumber(Scene* pass,int passNumber = -1);
			void Add_toScenePass(Scene* pass,Scene* nearPass = NULL);

			void Dispose(int passNumber);
			void Dispose(Scene* pass);
			void listClear();

			Scene* unlink(Scene* pass);
			Scene* unlink(Scene* pass, Scene* newScene);
			Scene* unlink(int pass);
			Scene* GetScene(int pass);
		
		public:
			void SetDefaultMatrix();
			void DrawScreen(NanairoLib::PRenderScreen screen, NanairoLib::COLOR_BLEND_NUM blendNum = NanairoLib::BLEND_ALPHA1 );
			bool defaultDraw_beforeAction(int renderPass = 0, int shaderPass = 0, NanairoLib::PRenderScreen screen = NULL);
			bool changeShaderPass(int passNumber = 0, NanairoLib::PRenderScreen screen = NULL);
			bool defaultDraw_afterAction(NanairoLib::PRenderScreen screen = NULL);
	};

//--------------------
//�p���K�{
//Scene�N���X�p
//--------------------
/*
	void Draw3D(){}
	void Draw2D(){}
	void Init(){}
	void Recircle(){}
	void Step(){}
	void Draw(){}
	void Atack(){}
	void Dispose(){}
	void Del(){}
*/
}

#endif