#ifndef MYGAME_REDORCE_H
#define MYGAME_REDORCE_H
//���f����O���t�B�b�N���Ǘ�����N���X
//**************************************************************

#ifndef MYGAME_MESH_H
#include <AnimationMesh.h>
#endif

#ifndef _NanairoLib_MODEL_H
#include <DirectModel.h>
#endif

#ifndef NanairoLib_GRAPH_H
#include <DirectGraph.h>
#endif

#ifndef _LIST
#include <list>
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _STRING_
#include <string>
#endif

//**************************************************************

namespace MYGAME
{
	typedef std::map<std::string, NanairoLib::MyGraph*>	GraphTable;
	typedef std::map<std::string, NanairoLib::MyModel*>	ModelTable;
	typedef std::map<std::string, NanairoLib::ATACKH*>	AtackTable;
	typedef std::map<std::string, NanairoLib::MY_MESH*>	AnimTable;
	typedef std::map<UINT, NanairoLib::MyFont*>			FontTable;
	typedef std::string									StdString;
	
	typedef GraphTable::iterator						GraphIterator;
	typedef ModelTable::iterator						ModelIterator;
	typedef AtackTable::iterator						AtackIterator;
	typedef AnimTable::iterator							AnimIterator;
	typedef FontTable::iterator							FontIterator;

	typedef GraphTable::value_type						GraphType;
	typedef ModelTable::value_type						ModelType;
	typedef AtackTable::value_type						AtackType;
	typedef AnimTable::value_type						AnimType;
	typedef FontTable::value_type						FontType;

	#define DIR_GRAPH	SetCurrentDirectory("Resource/Image/")
	#define DIR_EFK		SetCurrentDirectory("Resource/Effek/")
	#define DIR_MESH	SetCurrentDirectory("Resource/Model/")
	#define DIR_SOUND	SetCurrentDirectory("Resource/Music/")
	#define DIR_UP		SetCurrentDirectory("../../")
	
	#define FILE_LOADER_PASS1	"Resource/Roader/fileLoader_part1.fileLoader"
	#define FILE_LOADER_PASS2	"Resource/Roader/fileLoader_part2.fileLoader"
	#define SCENE_EDITOR_PASS1	"Resource/Roader/sceneEditor_part1.scene"

	struct LoaderGraphData
	{
		NanairoLib::MyGraph* gh;
		std::string			pass, newName;
		int width, height, sumW, sumH;
	};

	//----------------------------------------------------------------
	//�e�N�X�`���H��
	//----------------------------------------------------------------
	class Text2DFactory
	{
		private:
		//----------------------------------------------------------------
			static Text2DFactory*		_2DGraph;					//�V���O���g���|�C���^
			IDirect3DDevice9*			_devices;					//�f�o�C�X�|�C���^
			NanairoLib::Artisan*		custom;						//�|��

			int frameCnt, graphSum;									//�J�E���^,�e�L�X�g�ԍ�
			StdString					SetName;					//�摜�ݒu�������O
			GraphTable					graphTable;					//�O���t�B�b�N�}�b�v
			FontTable					fontTable;					//�t�H���g�}�b�v
		//----------------------------------------------------------------
		public:
		//----------------------------------------------------------------
			bool asynOK;									//�񓯊��t���O
		//----------------------------------------------------------------
		private:
		//----------------------------------------------------------------
			//�R�s�[�K�[�h
			Text2DFactory();
			Text2DFactory(const Text2DFactory& text){}
			Text2DFactory& operator=(const Text2DFactory& text){}
			~Text2DFactory();
		//----------------------------------------------------------------
			
			//�񓯊��ǂݍ���
			//(�t�@�C����).(�ۑ��ԍ�).(�摜��).(�摜����).(��������).(�����c��)
			//bool load_asyn(LPCTSTR str, LPCTSTR name, int width, int height, int sumW = 0, int sumH = 0);
			
			//�����[�X
			void releaseGraph();

			void SetTexture(LPCSTR newName, NanairoLib::TEXTUREH* graph);
			
		//----------------------------------------------------------------
		public:	
			//���ʓǂݍ���
			//(�t�@�C����).(�V�������O).(�摜��).(�摜����).(��������).(�����c��)
			bool loadGraph(LPCTSTR str, LPCTSTR name, int width, int height, int sumW = 0, int sumH = 0);
			
			//���C�����[�h
			bool main_loadGraph();

			//���C���񓯊��ǂݍ���
			bool main_asynLoad();

			//�񓯊��ǂݍ��݃A�N�V����
			//void asynaction();
			
			//�񓯊��ǂݍ��ݏ���
			//void delete_asyn();
		//---------------------------------------------------------------
			NanairoLib::TEXTUREH*	GetText(std::string str);
			NanairoLib::Artisan*	GetArtisan(){	return custom;	}
			void SetMyGraph(LPCSTR pass, NanairoLib::MyGraph* gh);
		//----------------------------------------------------------------
			//�`��̎��Ɏg��
			//���f���̒l�𓖂Ă͂߂Ă���
			bool draw_SetTrans(NanairoLib::RCVector2 pos, float sc, float ang, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			bool draw_SetTrans(NanairoLib::RCVector2 pos, NanairoLib::RCVector2 sc, float ang, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			bool draw_SetTrans(NanairoLib::PCVector3 pos, NanairoLib::RCVector2 sc, NanairoLib::PCVector3 ang, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			bool draw_SetTrans(NanairoLib::PCVector3 pos, NanairoLib::RCVector2 sc, float ang, PCMATRIX board, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			//�J���[������ݒ�
			bool draw_SetTrans(const NanairoLib::Vector4* color,std::string name);
			bool draw_SetTrans(NanairoLib::RCVector2 pos, NanairoLib::RCVector2 sc, float ang);

			//���ʂ̕`��
			void draw_graph();
			//�A�j�������`��
			void draw_divGraph(int animeCnt);
			//4�_�����߂ĕ��ʂ̃A�j�������`��
			void draw_rectDivGraph(NanairoLib::RCVector2 pos1,NanairoLib::RCVector2 pos2,NanairoLib::RCVector2 pos3,NanairoLib::RCVector2 pos4,int animeCnt);
			//4�_�����߂Ď����ŕ����`��
			void draw_modiGraph(NanairoLib::RCVector2 pos1,NanairoLib::RCVector2 pos2,NanairoLib::RCVector2 pos3,NanairoLib::RCVector2 pos4,int num,int wnum,int hnum);
			//3�_�����߂Ď����ŕ����`��(�K���X�p)
			void draw_TriangleGraph(NanairoLib::RCVector2 pos1,NanairoLib::RCVector2 pos2,NanairoLib::RCVector2 pos3,int num,int wnum,int hnum,int wid,int hei,bool IsUp,IDirect3DTexture9* text);
			
			void draw_worldGraph();
			void draw_noTexture();

			//�A���t�@�ݒ�
			void SetAlpha(NanairoLib::COLOR_BLEND_NUM mode = NanairoLib::BNONE,NanairoLib::Vector4 wo = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			void SetDevices(IDirect3DDevice9* device){	this->_devices = device;	}
			void SetArtisan(NanairoLib::Artisan* Artisan){	this->custom = Artisan;		}

		//----------------------------------------------------------------
			void drawString2D(char* str,NanairoLib::RCVector2 pos, float sc, float ang,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			UINT GetCharCode( const char* ch, UINT* cnt );
	public:
			//�C���X�^���X
			static Text2DFactory* GetInstance(){
				if(_2DGraph == 0)	_2DGraph = new Text2DFactory();
				return _2DGraph;
			}
			static void deleteInstance(){
				ES_SAFE_DELETE( _2DGraph );
			}
		//----------------------------------------------------------------
	};
	//----------------------------------------------------------------

	class LoaderGraphList
	{
	private:
		int	frameCnt;
		IDirect3DDevice9*				_devices;					//�f�o�C�X�|�C���^
		std::list<LoaderGraphData*>*	list;

	public:
		bool finishFlag;

	public:
		LoaderGraphList(IDirect3DDevice9* in);
		~LoaderGraphList();

		void main_load();
		void loadGraph(LPCSTR pass, LPCSTR newPass, int width, int height, int sumW = 0, int sumH = 0);
		void stockGraph(LPCSTR pass, LPCSTR newPass, int width, int height, int sumW = 0, int sumH = 0);
		void stockStep();
		void Pushing();
		std::list<LoaderGraphData*>* GetListPointer() const{	return (std::list<LoaderGraphData*>* const)&this->list;}
	};

	//���f���H��
	//----------------------------------------------------------------
	class Model3DFactory
	{
		private:
		//----------------------------------------------------------------
			int frameCnt;
			static Model3DFactory* _3DModel;					//�V���O���|�C���^
			IDirect3DDevice9*		_devices;					//�f�o�C�X�|�C���^
			NanairoLib::Shader*		_shader;
			ModelTable				modelTable;					//���f���e�[�u��
			AtackTable				atacktable;					//�����蔻��p�e�[�u��
			AnimTable				animTable;					//�A�j���e�[�u��
			int						modelSum;					//���f����
		//----------------------------------------------------------------
		public:
		//----------------------------------------------------------------	
			bool asynOK;									//�񓯊��t���O
		//----------------------------------------------------------------
		private:
		//----------------------------------------------------------------
			//�R�s�[�K�[�h
			Model3DFactory();
			Model3DFactory(const Model3DFactory& mmm){}
			Model3DFactory& operator=(const Model3DFactory& mmm){}
			~Model3DFactory();
		//----------------------------------------------------------------

			//�񓯊����[�h
			//(�t�@�C����).(�E�B���h�E�N���X).(�ۑ��ԍ�).(0���A���r�G���g���f�t���[�Y�ꏏ�ɂ���)
			//bool load_modelASYN(LPCTSTR pass, HWND hWnd,int num,int mode = 0);
			
			//�����蔻��ƈꏏ�ɔ񓯊����[�h
			//(�t�@�C����).(�����蔻��t�@�C����).(�E�B���h�E�N���X).(�ۑ��ԍ�).(0���A���r�G���g���f�t���[�Y�ꏏ�ɂ���)
			//bool load_modelASYN(LPCTSTR pass, LPCTSTR atackpass, HWND hWnd,int num,int mode = 0);
			
			//�����[�X
			void releaseModel();
		//----------------------------------------------------------------
		public:
		//----------------------------------------------------------------
			//���ʃ��[�h
			//(�t�@�C����).(�E�B���h�E�N���X).(�ۑ��ԍ�).(0���A���r�G���g���f�t���[�Y�ꏏ�ɂ���)
			bool load_model(LPCTSTR pass, LPCTSTR name, int mode = 0);
			
			//�����蔻������[�h
			//(�t�@�C����).(�����蔻��t�@�C����).(�E�B���h�E�N���X).(�ۑ��ԍ�).(0���A���r�G���g���f�t���[�Y�ꏏ�ɂ���)
			bool load_model(LPCTSTR pass, LPCTSTR atackpass, LPCTSTR name,int num,int mode = 0);
			
			bool load_mesh(LPCTSTR pass, LPCTSTR name);

			//���C�����[�h
			//hWnd(�E�B���h�E�N���X)
			bool main_loadGraph();
			
			//���C���񓯊����[�h
			bool main_asynLoad();

			//�񓯊��ǂݍ��݃A�N�V����
			//void asynaction();

			//�񓯊��ǂݍ��݃N���X�I��
			//void delete_asyn();

			//���f���̕`��
			//(���f���ԍ�),�i�ϊ��s��j
			void SetWorld(LPCTSTR modelName, PCMATRIX mat);
			void draw_model(LPCTSTR modelName, NanairoLib::TEXTUREH* graph = NULL);
		//----------------------------------------------------------------
			#pragma region �f�[�^�̎擾
			NanairoLib::MODELH*	GetModel(std::string str);
			NanairoLib::MyModel*	GetModelPointer(std::string str);
			NanairoLib::ATACKH*	GetAtackModel(std::string str);
			NanairoLib::MY_MESH*	GetMesh(std::string str);
			#pragma endregion

			void SetDevices(IDirect3DDevice9* device){	this->_devices = device;	}
			void SetShader(NanairoLib::Shader* sh){		this->_shader = sh;			}

		//----------------------------------------------------------------
			#pragma region �C���X�^���X�n
			static Model3DFactory* GetInstance(){
				if(_3DModel == 0)	_3DModel = new Model3DFactory();
				return _3DModel;
			}
			static void deleteInstance(){
				delete _3DModel;	_3DModel = NULL;
			}
			#pragma endregion
		//----------------------------------------------------------------
	};
	//----------------------------------------------------------------

	#define __GRAPHFACTORY Text2DFactory::GetInstance()
	#define __MODELFACTORY Model3DFactory::GetInstance()

}

#endif