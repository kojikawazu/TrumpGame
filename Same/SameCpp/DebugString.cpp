#pragma once
//-----------------------------------------------------------------------------------
//
//	文字系列のクラス
//
//-----------------------------------------------------------------------------------

#pragma region インクルード
#include <Windows.h>
#include <tchar.h>
#include <DebugString.h>
using namespace std;
#pragma endregion

namespace NanairoLib
{
//----------------------------------------------------------------------------------------------------------
//ログ表示関数です
//↓

	//--------------------------------------------
	//「同じファイル」ということを示すログメソッド
	//--------------------------------------------
	//@in : ファイル名
	void OutPutStringFunction::SameOut_outputString( LPCTSTR name )
	{
		OutputDebugString( _T("-- FileRead Error : SameName ") );
		OutputDebugString( name );
		OutputDebugString( _T(" --\n") );
	}

	//--------------------------------------------
	//「読み込み成功」ということを示すログメソッド
	//--------------------------------------------
	//@in : ファイル名、新しい名前
	void OutPutStringFunction::Success_outputString(LPCTSTR pass,LPCTSTR name){
		OutputDebugString( _T("-- FileRead Success : reading ") );
		OutputDebugString( pass );
		OutputDebugString( _T(" → NewName is : ") );
		OutputDebugString( name );
		OutputDebugString( _T(" --\n") );
	}

	//--------------------------------------------
	//「読み込み失敗」ということを示すログメソッド
	//--------------------------------------------
	//@in : ファイル名
	void OutPutStringFunction::Failed_outputString(LPCTSTR pass){
		OutputDebugString( _T("-- FileRead Error : NotReading ") );
		OutputDebugString( pass );
		OutputDebugString( _T(" --\n") );
	}

	//--------------------------------------------
	//ログをもらって表示
	//--------------------------------------------
	//@in : ログリスト
	void OutPutStringFunction::FreedomString( std::vector<std::string>& word )
	{
		UINT size = word.size();
		for(UINT i=0; i<size; i++)
		{
			::OutputDebugString( word[i].c_str() );
			::OutputDebugString( "\n" );
		}
	}

//----------------------------------------------------------------------------------------------------------
//使いそうな便利機能をもった文字列クラスです↓

	//---------------------------------------------------------------------------------
	//文字列を空白文字で分割して返すメソッド
	//---------------------------------------------------------------------------------
	//@in : 分割したい文字列
	//@out : 分割した文字列群
	//@cnt : 回数制限
	void StringFunction::Split(std::string& in, std::vector<std::string>& out, int cnt)
	{
		this->Split( in, " ", out , cnt );
	}

	//---------------------------------------------------------------------------------
	//文字列を空白文字で分割して返すメソッド
	//---------------------------------------------------------------------------------
	//@in : 分割したい文字列
	//@in : 分割キーワード
	//@out : 分割した文字列群
	//@cnt : 回数制限
	void StringFunction::Split(std::string& in, LPCSTR keyword,std::vector<std::string>& out, int cnt)
	{
		string::size_type type;
		std::string st;
		int oldIndex = 0, cnter = 0;
		bool div = (cnt <= 0 ? true : false );
		type = in.find( keyword , oldIndex );
		//出力文字群をクリアします
		out.clear();
		
		//（その文字がみつかった) and ( divがマイナスなら必ず . divがプラスで指定回数以下なら)
		while( type != string::npos && (div || cnter < cnt) )
		{
			st = in.substr( oldIndex, type - oldIndex );
			out.push_back( st );

			oldIndex = type + 1;
			type = in.find( keyword , oldIndex );
			cnter++;
		}

		//残された文字も最後に入れ忘れずに
		st = in.substr( oldIndex, in.size() - oldIndex );
		out.push_back( st );
	}

	//----------------------------------------------------
	//前の空白文字を削除して詰める
	//----------------------------------------------------
	//@inout : 変換文字列
	void StringFunction::FirstSpaceErase(std::string& str)
	{
		string::size_type type;
		type = str.find_first_of( " " , 0 );
	
		while( type == 0 )
		{	
			str.erase( 0 , 1 );
			type = str.find_first_of( " " , 0 );
		}
	}

	//------------------------------------------------------------------------------------------------------
	//デフォルトなパスを前方へ装備して返す
	//------------------------------------------------------------------------------------------------------
	//@out : 出来上がった文字列
	//@in : 変換元文字列
	//@in : 間に挟む文字列
	//@in : 入れ込む文字列
	void StringFunction::GetDefaultPass(std::string& out, std::string& pass, LPCSTR dotpass, LPCSTR divword)
	{
		out.clear();
		string::size_type type;
		std::vector<std::string> word;
		int cnt = 0;
		//ソリューションから読み込みたいパスまでの間を取得したい
		this->Split( pass , divword , word ); 
		type = word[cnt].find( dotpass );
		while( type == string::npos )
		{
			out.append( word[cnt].c_str() );
			out.append( divword );
			cnt++;
			type = word[cnt].find( dotpass );
		}
	}

	//-------------------------------------------------------------------------
	//文字列から同じ文字があるか、あればその位置を返す
	//-------------------------------------------------------------------------
	//@in : 対象文字列
	//@in : 探す文字列
	//@out : 文字列の位置
	int StringFunction::IsSameString(std::string& str, std::string& sameString)
	{
		string::size_type type = 0;
		type = str.find( sameString.c_str() );
		return ( type != string::npos ? type : -1 );
	}

//----------------------------------------------------------------------------------------------------------
//ロードで使いそうなものを集めたスーパークラスです↓
	
	//------------------------------------------------------------------------------------------------------------
	//ファイルを開く簡単操作
	//------------------------------------------------------------------------------------------------------------
	//@inout : ファイルローダークラス
	//@in : ファイルパス
	//@in : true(入力) false(出力)
	//@in : true(バイナリ) false(テキスト)
	//@out : true(成功) false(失敗)
	bool Loader::Open_the_file(std::fstream& fs,std::string& filePass,bool isIn, bool isBinary)
	{
		( isBinary ? fs.open( filePass.c_str(), ( isIn ? std::ios::in : std::ios::out ) | std::ios::binary ) :
						fs.open( filePass.c_str(), ( isIn ? std::ios::in : std::ios::out ) ) );
		
		if( fs.fail() || fs.eof() )
		{
#if _DEBUG
			OutputDebugString("Cannot open this file. fileName is ");
			OutputDebugString( filePass.c_str() );
			OutputDebugString("\n");
#endif
			return false;
		}
		return true;	
	}
	
	//-------------------------------------------------
	//ファイルを閉じる簡単操作
	//-------------------------------------------------
	void Loader::Close_the_file(std::fstream& fs)
	{
		fs.close();
	}

}