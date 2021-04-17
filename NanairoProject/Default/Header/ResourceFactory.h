#ifndef MYGAME_REDORCE_H
#define MYGAME_REDORCE_H
//モデルやグラフィックを管理するクラス
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
	//テクスチャ工場
	//----------------------------------------------------------------
	class Text2DFactory
	{
		private:
		//----------------------------------------------------------------
			static Text2DFactory*		_2DGraph;					//シングルトンポインタ
			IDirect3DDevice9*			_devices;					//デバイスポインタ
			NanairoLib::Artisan*		custom;						//板ポリ

			int frameCnt, graphSum;									//カウンタ,テキスト番号
			StdString					SetName;					//画像設置した名前
			GraphTable					graphTable;					//グラフィックマップ
			FontTable					fontTable;					//フォントマップ
		//----------------------------------------------------------------
		public:
		//----------------------------------------------------------------
			bool asynOK;									//非同期フラグ
		//----------------------------------------------------------------
		private:
		//----------------------------------------------------------------
			//コピーガード
			Text2DFactory();
			Text2DFactory(const Text2DFactory& text){}
			Text2DFactory& operator=(const Text2DFactory& text){}
			~Text2DFactory();
		//----------------------------------------------------------------
			
			//非同期読み込み
			//(ファイル名).(保存番号).(画像幅).(画像高さ).(分割横数).(分割縦数)
			//bool load_asyn(LPCTSTR str, LPCTSTR name, int width, int height, int sumW = 0, int sumH = 0);
			
			//リリース
			void releaseGraph();

			void SetTexture(LPCSTR newName, NanairoLib::TEXTUREH* graph);
			
		//----------------------------------------------------------------
		public:	
			//普通読み込み
			//(ファイル名).(新しい名前).(画像幅).(画像高さ).(分割横数).(分割縦数)
			bool loadGraph(LPCTSTR str, LPCTSTR name, int width, int height, int sumW = 0, int sumH = 0);
			
			//メインロード
			bool main_loadGraph();

			//メイン非同期読み込み
			bool main_asynLoad();

			//非同期読み込みアクション
			//void asynaction();
			
			//非同期読み込み消滅
			//void delete_asyn();
		//---------------------------------------------------------------
			NanairoLib::TEXTUREH*	GetText(std::string str);
			NanairoLib::Artisan*	GetArtisan(){	return custom;	}
			void SetMyGraph(LPCSTR pass, NanairoLib::MyGraph* gh);
		//----------------------------------------------------------------
			//描画の時に使う
			//モデルの値を当てはめていく
			bool draw_SetTrans(NanairoLib::RCVector2 pos, float sc, float ang, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			bool draw_SetTrans(NanairoLib::RCVector2 pos, NanairoLib::RCVector2 sc, float ang, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			bool draw_SetTrans(NanairoLib::PCVector3 pos, NanairoLib::RCVector2 sc, NanairoLib::PCVector3 ang, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			bool draw_SetTrans(NanairoLib::PCVector3 pos, NanairoLib::RCVector2 sc, float ang, PCMATRIX board, std::string name,int mode = 0,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			//カラーだけを設定
			bool draw_SetTrans(const NanairoLib::Vector4* color,std::string name);
			bool draw_SetTrans(NanairoLib::RCVector2 pos, NanairoLib::RCVector2 sc, float ang);

			//普通の描画
			void draw_graph();
			//アニメ分割描画
			void draw_divGraph(int animeCnt);
			//4点を決めて普通のアニメ分割描画
			void draw_rectDivGraph(NanairoLib::RCVector2 pos1,NanairoLib::RCVector2 pos2,NanairoLib::RCVector2 pos3,NanairoLib::RCVector2 pos4,int animeCnt);
			//4点を決めて自分で分割描画
			void draw_modiGraph(NanairoLib::RCVector2 pos1,NanairoLib::RCVector2 pos2,NanairoLib::RCVector2 pos3,NanairoLib::RCVector2 pos4,int num,int wnum,int hnum);
			//3点を決めて自分で分割描画(ガラス用)
			void draw_TriangleGraph(NanairoLib::RCVector2 pos1,NanairoLib::RCVector2 pos2,NanairoLib::RCVector2 pos3,int num,int wnum,int hnum,int wid,int hei,bool IsUp,IDirect3DTexture9* text);
			
			void draw_worldGraph();
			void draw_noTexture();

			//アルファ設定
			void SetAlpha(NanairoLib::COLOR_BLEND_NUM mode = NanairoLib::BNONE,NanairoLib::Vector4 wo = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			void SetDevices(IDirect3DDevice9* device){	this->_devices = device;	}
			void SetArtisan(NanairoLib::Artisan* Artisan){	this->custom = Artisan;		}

		//----------------------------------------------------------------
			void drawString2D(char* str,NanairoLib::RCVector2 pos, float sc, float ang,const NanairoLib::Vector4 color = NanairoLib::Vector4(255.0f,255.0f,255.0f,255.0f));
			UINT GetCharCode( const char* ch, UINT* cnt );
	public:
			//インスタンス
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
		IDirect3DDevice9*				_devices;					//デバイスポインタ
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

	//モデル工場
	//----------------------------------------------------------------
	class Model3DFactory
	{
		private:
		//----------------------------------------------------------------
			int frameCnt;
			static Model3DFactory* _3DModel;					//シングルポインタ
			IDirect3DDevice9*		_devices;					//デバイスポインタ
			NanairoLib::Shader*		_shader;
			ModelTable				modelTable;					//モデルテーブル
			AtackTable				atacktable;					//当たり判定用テーブル
			AnimTable				animTable;					//アニメテーブル
			int						modelSum;					//モデル数
		//----------------------------------------------------------------
		public:
		//----------------------------------------------------------------	
			bool asynOK;									//非同期フラグ
		//----------------------------------------------------------------
		private:
		//----------------------------------------------------------------
			//コピーガード
			Model3DFactory();
			Model3DFactory(const Model3DFactory& mmm){}
			Model3DFactory& operator=(const Model3DFactory& mmm){}
			~Model3DFactory();
		//----------------------------------------------------------------

			//非同期ロード
			//(ファイル名).(ウィンドウクラス).(保存番号).(0←アンビエントをデフューズ一緒にする)
			//bool load_modelASYN(LPCTSTR pass, HWND hWnd,int num,int mode = 0);
			
			//当たり判定と一緒に非同期ロード
			//(ファイル名).(当たり判定ファイル名).(ウィンドウクラス).(保存番号).(0←アンビエントをデフューズ一緒にする)
			//bool load_modelASYN(LPCTSTR pass, LPCTSTR atackpass, HWND hWnd,int num,int mode = 0);
			
			//リリース
			void releaseModel();
		//----------------------------------------------------------------
		public:
		//----------------------------------------------------------------
			//普通ロード
			//(ファイル名).(ウィンドウクラス).(保存番号).(0←アンビエントをデフューズ一緒にする)
			bool load_model(LPCTSTR pass, LPCTSTR name, int mode = 0);
			
			//当たり判定つきロード
			//(ファイル名).(当たり判定ファイル名).(ウィンドウクラス).(保存番号).(0←アンビエントをデフューズ一緒にする)
			bool load_model(LPCTSTR pass, LPCTSTR atackpass, LPCTSTR name,int num,int mode = 0);
			
			bool load_mesh(LPCTSTR pass, LPCTSTR name);

			//メインロード
			//hWnd(ウィンドウクラス)
			bool main_loadGraph();
			
			//メイン非同期ロード
			bool main_asynLoad();

			//非同期読み込みアクション
			//void asynaction();

			//非同期読み込みクラス終了
			//void delete_asyn();

			//モデルの描画
			//(モデル番号),（変換行列）
			void SetWorld(LPCTSTR modelName, PCMATRIX mat);
			void draw_model(LPCTSTR modelName, NanairoLib::TEXTUREH* graph = NULL);
		//----------------------------------------------------------------
			#pragma region データの取得
			NanairoLib::MODELH*	GetModel(std::string str);
			NanairoLib::MyModel*	GetModelPointer(std::string str);
			NanairoLib::ATACKH*	GetAtackModel(std::string str);
			NanairoLib::MY_MESH*	GetMesh(std::string str);
			#pragma endregion

			void SetDevices(IDirect3DDevice9* device){	this->_devices = device;	}
			void SetShader(NanairoLib::Shader* sh){		this->_shader = sh;			}

		//----------------------------------------------------------------
			#pragma region インスタンス系
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