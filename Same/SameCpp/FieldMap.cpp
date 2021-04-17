#pragma once
//-------------------------------------------------
//CSVからマップデータを取出してデータ構築するっ
//-------------------------------------------------
#include <MapReaderCSV.h>
using namespace std;

//--------------------------
//情報を読む仲介役
//mapreaderを使って読む
//--------------------------
namespace NanairoLib
{
	inline FieldMap::FieldMap(){}
	inline FieldMap::~FieldMap(){}

	//---------------------------------------------
	//ＣＳＶからデータ読み込み
	//---------------------------------------------
	//@inout : マップデータポインタ
	//@inout : CSV読み込みクラス
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
	//ＣＳＶからデータ読み込み
	//---------------------------------------------
	//@inout : マップデータポインタ
	//@inout : CSV読み込みクラス
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
	//マップファイル読み込み
	//----------------------------------------------
	//@in : ファイルパス
	//@out : ファイルマップデータ
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
	//敵ファイル読み込み
	//---------------------------------------------------
	//@in : ファイルパス
	//@out : ファイル敵データ
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