#pragma once

//---------------------------------------------------------
//NanairoLib
//---------------------------------------------------------
#include <DebugString.h>

//---------------------------------------------------------
//MYGAME
//---------------------------------------------------------
#include <ResourceFactory.h>
using namespace NanairoLib;

namespace MYGAME
{
	Model3DFactory::Model3DFactory() : 
		frameCnt(0), _devices(NULL), modelSum(0), asynOK(false)
	{}

	Model3DFactory::~Model3DFactory(){
		this->releaseModel();
		modelSum = 0;
		this->_devices = NULL;
		this->_shader = NULL;
	}

	//---------------------------------------------------------
	//たいていのロードはここ！
	//---------------------------------------------------------
	bool Model3DFactory::load_model(LPCTSTR pass, LPCTSTR name, int mode)
	{
		::TextFunc func;
		::OutPutStringFunction out;
		if(this->modelTable.find( name ) != this->modelTable.end() )
		{
			out.SameOut_outputString( name );
			return false;
		}

		MyModel* md = new MyModel();
		if( func.LoadModel3D(this->_devices, pass, md->GetModelPoint(), mode) )
		{
			this->modelTable.insert( ModelType( name, md ) );
			this->modelSum++;
			out.Success_outputString(pass, name);
			return true;
		}
		else
		{
			out.Failed_outputString( pass );
			delete md;
			return false;
		}
	}

	bool Model3DFactory::load_model(LPCTSTR pass, LPCTSTR atackpass, LPCTSTR name,int num,int mode)
	{
		if( !this->load_model( pass, name, mode ) )
			return false;
		
		::TextFunc func;
		::OutPutStringFunction out;
		NanairoLib::ATACKH* atacks = new NanairoLib::ATACKH();
		if( func.LoadModelAtack( this->_devices, atackpass, atacks ) ){
			this->atacktable.insert( AtackTable::value_type( name, atacks ) );
			
			out.Success_outputString(atackpass, name);
		}
		else{
			out.Failed_outputString( pass );
			delete atacks;
		}
				
		return true;
	}

	bool Model3DFactory::load_mesh(LPCTSTR pass, LPCTSTR name)
	{
		::OutPutStringFunction out;
		if(this->animTable.find( name ) != this->animTable.end())
		{
			out.SameOut_outputString( name );
			return false;
		}

		NanairoLib::MY_MESH* mesh = new MY_MESH( this->_devices, pass );
		if(mesh != NULL)
		{
			this->animTable.insert( AnimTable::value_type( name, mesh ) );
			out.Success_outputString( pass, name );
			return true;	
		}
		else
		{
			ES_SAFE_DELETE( mesh );
			out.Failed_outputString( pass );
			return false;
		}
	}

	//---------------------------------------------------------
	//リリース
	//---------------------------------------------------------
	void Model3DFactory::releaseModel()
	{
		MYGAME::ModelIterator modelit = this->modelTable.begin();

		while(modelit != this->modelTable.end())
		{
			NanairoLib::MyModel* model = modelit->second;
			modelit = this->modelTable.erase( modelit );
			ES_SAFE_DELETE( model );
		}

		AtackIterator atackit = this->atacktable.begin();

		while(atackit != this->atacktable.end())
		{
			NanairoLib::ATACKH* atack = atackit->second;

			unsigned int sum = atack->meshSum;
			for(DWORD j=0; j<sum; j++){
				atack->meshIndex[(int)j][0] = 0;
				atack->meshIndex[(int)j][1] = 0;
				atack->meshIndex[(int)j][2] = 0;
			}
			
			atackit = this->atacktable.erase( atackit );
			ES_SAFE_DELETE( atack );
		}

		AnimIterator animit = this->animTable.begin();

		while(animit != this->animTable.end())
		{
			NanairoLib::MY_MESH* mesh = animit->second;
			animit = this->animTable.erase( animit );
			ES_SAFE_DELETE(mesh);
		}
	}

	//---------------------------------------------------------
	//ワールド行列の設定
	//---------------------------------------------------------
	void Model3DFactory::SetWorld(LPCTSTR modelName, PCMATRIX mat)
	{
		ModelIterator modelit = this->modelTable.find( modelName );
		if(modelit != this->modelTable.end() )
			(*modelit).second->SettingWorld( this->_devices, mat, this->_shader );
	}
	
	//---------------------------------------------------------
	//モデルの描画
	//---------------------------------------------------------
	void Model3DFactory::draw_model(LPCTSTR modelName, NanairoLib::TEXTUREH* graph)
	{
		ModelIterator modelit = this->modelTable.find( modelName );
		if(modelit != this->modelTable.end() )
			(*modelit).second->drawModel( this->_devices, this->_shader, graph );
	}

	//---------------------------------------------------------
	//モデルの中の情報の取得
	//---------------------------------------------------------
	NanairoLib::MODELH*	Model3DFactory::GetModel(std::string str)
	{
		ModelIterator it = this->modelTable.find( str );
		return ( it != this->modelTable.end() ? it->second->GetModelPoint() : NULL );
	}

	//---------------------------------------------------------
	//モデルの取得
	//---------------------------------------------------------
	NanairoLib::MyModel*	Model3DFactory::GetModelPointer(std::string str)
	{
		ModelIterator it = this->modelTable.find( str );
		return ( it != this->modelTable.end() ? it->second : NULL );
	}

	//---------------------------------------------------------
	//あたり判定用モデル情報の取得
	//---------------------------------------------------------
	NanairoLib::ATACKH*	Model3DFactory::GetAtackModel(std::string str)
	{
		AtackIterator it = this->atacktable.find( str );
		return ( it != this->atacktable.end() ? it->second : NULL );
	}

	//---------------------------------------------------------
	//メッシュの取得
	//---------------------------------------------------------
	NanairoLib::MY_MESH*	Model3DFactory::GetMesh(std::string str)
	{
		MYGAME::AnimIterator it = this->animTable.find( str );
		return ( it != this->animTable.end() ? it->second : NULL );
	}
}