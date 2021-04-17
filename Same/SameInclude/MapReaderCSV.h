#ifndef NanairoLib_MAPREADER_H
#define NanairoLib_MAPREADER_H

//------------------------------------------------------
//
//CSVからデータを読み込むクラス
//
//------------------------------------------------------

#pragma region インクルード
#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _FSTREAM_
#include <fstream>
#endif
#pragma endregion

namespace NanairoLib
{
	//---------------------------------------------------
	//コンマの識別
	//---------------------------------------------------
	#define DEFAULT_SEPARATOR    ','

	//---------------------------------------------------
	//ダブルクォーテーションの識別
	//---------------------------------------------------	
	#define DEFAULT_QUOTE_CHARACTER    '"'

	//---------------------------------------------------
	//マップ系データ制限
	//---------------------------------------------------
	#define MAXMAPX		  SCRW + 1000
	#define MAXMAPY		         SCRH
	#define MAXENEMMAPX	            8
	#define MAXENEMMAPY            35

	//---------------------------------------------------
	//マップ系データ構造
	//---------------------------------------------------
	typedef struct MAPDATA{
		bool used;						//使用中か
		int mapMX;						//最大X
		int mapMY;						//最大Y
		int map[MAXMAPY][MAXMAPX];		//マップ情報
	}MAPDATAA;

	typedef struct ENEMDATA{
		bool used;
		int mapMX;
		int mapMY;
		int map[MAXENEMMAPY][MAXENEMMAPX];
	}ENEMMAP;

	//---------------------------------------------------
	//マップ系typedef
	//---------------------------------------------------
	typedef MAPDATAA*				PMAPDATA;
	typedef ENEMMAP*				PEMAPDATA;

	//----------------------------------------
	//CSVを読み込むときに内部で使うクラス
	//----------------------------------------
	class MapReaderCSV
	{
	private:
		std::fstream* pstream;
		char SEPARATOR;
		char QUOTE;

	public:
		
		//------------------------------------------------------------------------
		//デコン
		//------------------------------------------------------------------------
		__IMPOETER MapReaderCSV();
		__IMPOETER MapReaderCSV(std::fstream& stream);
		__IMPOETER MapReaderCSV(std::fstream& stream,const char sep);
		__IMPOETER MapReaderCSV(std::fstream& stream,const char sep,const char quo);
		__IMPOETER ~MapReaderCSV(){}

		//--------------------------------------------------
		//CSVファイルを１行読み込んで、分割して配列で返す
		//--------------------------------------------------
		//@inout : トークン
		//@out : 0(成功) -1(失敗)
		__IMPOETER int Read(std::vector<std::string>& tokens);

		//------------------------------------------
		//ファイルストリームをクローズする
		//------------------------------------------
		//@out :  0(成功) -1(失敗)
		__IMPOETER int Close();

	private:
		//----------------------------------------------------------
		//ファイルから１行読み込む
		//----------------------------------------------------------
		//@in : 行データ
		//@out >=0(読み込んだデータ長) -1(失敗)
		__IMPOETER int GetNextLine(std::string& line);

		//-----------------------------------------------------------------
		//データをパスする
		//-----------------------------------------------------------------
		//@in : 行データ
		//@inout: パースしたデータの配列(OUT)
		//@out : 0
		__IMPOETER int Parse(std::string& nextLine, std::vector<std::string>& tokens);
	};
	
	//--------------------------------------------
	//フィールド、敵等をここのクラスで読み込む
	//--------------------------------------------
	class FieldMap
	{
	public:
		//-------------------------
		//デコン
		//-------------------------
		__IMPOETER FieldMap();
		__IMPOETER ~FieldMap();

		//----------------------------------------------
		//マップファイル読み込み
		//----------------------------------------------
		//@in : ファイルパス
		//@out : ファイルマップデータ
		__IMPOETER PMAPDATA		ReadFile(LPCSTR fileName);

		//---------------------------------------------------
		//敵ファイル読み込み
		//---------------------------------------------------
		//@in : ファイルパス
		//@out : ファイル敵データ
		__IMPOETER PEMAPDATA	ReadFileEnemMap(LPCSTR fileName);	
	};

	typedef MapReaderCSV* PMapReaderCSV;
}
#endif