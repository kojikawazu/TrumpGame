#pragma once
//-------------------------------------------------
//CSV����}�b�v�f�[�^����o���ăf�[�^�\�z�����
//-------------------------------------------------
#include <MapReaderCSV.h>
using namespace std;

//--------------------------
//����ǂޒ����
//mapreader���g���ēǂ�
//--------------------------
namespace NanairoLib
{
	inline FieldMap::FieldMap(){}
	inline FieldMap::~FieldMap(){}

	//---------------------------------------------
	//�b�r�u����f�[�^�ǂݍ���
	//---------------------------------------------
	//@inout : �}�b�v�f�[�^�|�C���^
	//@inout : CSV�ǂݍ��݃N���X
	void reading(PMAPDATA map, PMapReaderCSV mrCSV)
	{
		vector<string> tokens;
		int cntY = 0,maxX = 0,maxY = 0;

		while(!mrCSV->Read(tokens))
		{
			int cntX = 0;
			for(UINT i=0; i<tokens.size() && cntX < MAXMAPX ; i++,cntX++)
			{
				LPCSTR str = tokens[i].c_str();
				int in = std::atoi(str);
				
				map->map[cntY][cntX] = in;
			}
			if(maxX == 0 || maxX < cntX) 
				maxX = cntX;

			cntY++;
			if(cntY + 1 >= MAXMAPY)	
				break;
		}

		map->mapMX = maxX;
		map->mapMY = cntY;

		mrCSV->Close();
	}

	//---------------------------------------------
	//�b�r�u����f�[�^�ǂݍ���
	//---------------------------------------------
	//@inout : �}�b�v�f�[�^�|�C���^
	//@inout : CSV�ǂݍ��݃N���X
	void reading(PEMAPDATA map,PMapReaderCSV mrCSV)
	{
		vector<string> tokens;
		int cntY = 0,maxX = 0,maxY = 0;

		while(!mrCSV->Read(tokens)){
			int cntX = 0;
			for(UINT i=0; i<tokens.size() && cntX < MAXMAPX ; i++,cntX++){
				LPCSTR str = tokens[i].c_str();
				int in = std::atoi(str);
				
				map->map[cntY][cntX] = in;
			}
			if(maxX == 0 || maxX < cntX) 
				maxX = cntX;

			cntY++;
			if(cntY + 1 >= MAXMAPY)	
				break;
		}

		map->mapMX = maxX;
		map->mapMY = cntY;

		mrCSV->Close();
	}

	//------------------------------------------------------------------
	
	//----------------------------------------------
	//�}�b�v�t�@�C���ǂݍ���
	//----------------------------------------------
	//@in : �t�@�C���p�X
	//@out : �t�@�C���}�b�v�f�[�^
	MAPDATAA* FieldMap::ReadFile(LPCSTR fileName)
	{
		NanairoLib::MAPDATAA *map;
		MapReaderCSV *mrCSV;	
		std::fstream r(fileName, std::ios::in);
		map = new MAPDATAA();
		memset(map,0,sizeof(MAPDATAA));

		if(r.is_open())
		{
			map->used = true;
			mrCSV = new MapReaderCSV(r);
			reading(map,mrCSV);
			delete mrCSV;
		}
		else	
			map->used = false;
		return map;
	}
	
	//---------------------------------------------------
	//�G�t�@�C���ǂݍ���
	//---------------------------------------------------
	//@in : �t�@�C���p�X
	//@out : �t�@�C���G�f�[�^
	ENEMMAP* FieldMap::ReadFileEnemMap(LPCSTR fileName)
	{
		NanairoLib::ENEMMAP *map;
		MapReaderCSV *mrCSV;	
		std::fstream r(fileName, std::ios::in);
		map = new ENEMMAP();
		memset(map,0,sizeof(ENEMMAP));

		if(r.is_open())
		{
			map->used = true;
			mrCSV = new MapReaderCSV(r);
			reading(map,mrCSV);
			delete mrCSV;
		}
		else	
			map->used = false;
		return map;
	}

}