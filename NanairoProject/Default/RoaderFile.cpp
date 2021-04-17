#pragma once

//---------------------------------------------------------
//
//ファイルからリソースパスを読み込んでロード
//
//２つの読み込みローダファイルを扱う
//各リソースは独立していること！
//
//---------------------------------------------------------

//---------------------------------------------------------
//MyDirectDLL
//---------------------------------------------------------
#include <ResourceFactory.h>
#include <MusicSound.h>
#include <EffekseerFactory.h>
using namespace NanairoLib;

//---------------------------------------------------------
//MYGAME
//---------------------------------------------------------
#include <RoaderFile.h>
using namespace std;

namespace MYGAME
{

	//----------------------------------------------------------------------
	//コンストラクタ
	//----------------------------------------------------------------------
	ResourceRoaderFile::ResourceRoaderFile(LPCSTR filepass) : isReady(false)
	{
		this->passload( filepass );
	}

	//----------------------------------------------------------------------
	//デストラクタ
	//----------------------------------------------------------------------
	ResourceRoaderFile::~ResourceRoaderFile()
	{
		this->resourceKnd.erase();
		this->extension.erase();
		this->resourceKnd.erase();
		this->resourcePass.erase();
		this->resourcePass_2.erase();
	}

	//----------------------------------------------------------------------
	//指定されたローディングパスから読み込みを開始する
	//----------------------------------------------------------------------
	//@in : 読み込む用のローディングパス
	void ResourceRoaderFile::passload(LPCSTR filepass)
	{
		ifstream ofs( filepass , std::ios::in );
		while( !ofs.fail() || !ofs.eof() )
		{
			char line[256];
			ofs.getline( line, sizeof(line) );
			this->checkPass( std::string(line) );
		}

		ofs.close();
	}

	//----------------------------------------------------------------------
	//パスを上から探索
	//----------------------------------------------------------------------
	//@in : 読み込んだ文字列
	void ResourceRoaderFile::checkPass(std::string& str)
	{
		//空は除外-
		if( str.empty() )	return;
		
		//「//」コメント分も除外
		std::string::size_type index = str.find_first_of("//");
		if( index != string::npos )
			return ;
		
		//次は「：」を探します
		//「：」の左辺は識別子、右辺はその識別された文字の中身
		index = str.find_first_of(":");
		if( index != string::npos )
		{
			this->SettingPass( str , index);
			return ;
		}

		if( this->isReady )
		{
			std::string::size_type siz = this->resourceKnd.find("Image");
			(siz != string::npos ? this->loadResourceGraph( str ) : this->loadResource( str ) );
		}
	}

	//----------------------------------------------------------------------
	//読み込んだデータにキーワードがあれば変更を
	//----------------------------------------------------------------------
	//@in : 読み込んだ文字列
	//@in : キーワード文字の１つ前のインデックス
	void ResourceRoaderFile::SettingPass(std::string& pass, int index)
	{
		std::string answer = pass.substr( index + 1 );
		std::string::size_type i = pass.find("リソースパス");

		if( pass.find("デフォルト") != std::string::npos)
			this->resourcePass = answer;
		else if( pass.find("リソースパス") != std::string::npos )
			resourcePass_2 = answer;
		else if( pass.find("読み込み識別子") != std::string::npos )
			resourceKnd = answer;
		else if( pass.find("拡張子") != std::string::npos )
			extension = answer;
		else if( pass.find("ファイル名") != std::string::npos )
		{
			if( !this->resourcePass.empty() && !this->resourcePass_2.empty() &&
				!this->resourceKnd.empty() && !this->extension.empty() )
				isReady = true;
		}
	}

	//----------------------------------------------------------------------
	//画像読み込みデータからロードを開始
	//----------------------------------------------------------------------
	//@in : 画像用読み込み用データ
	void ResourceRoaderFile::loadResourceGraph(std::string& word)
	{
		//空は当然除外
		if( word.empty() )	return;

		short cnt = 0;
		int list[] = {0,0,0,0};
		std::string pass, newName;
		std::string::size_type index = 0, oldIndex = 0;
		
		//まずはコンマ探し
		index = word.find(",", oldIndex);

		while( index != string::npos )
		{
			//見つかったら""があるかどうか
			std::string::size_type _con = word.find('"', index - 1);
			if( _con != string::npos )
			{
				//あったらこれは文字列ですー
				( pass.empty() ? pass = word.substr(oldIndex + 1, index - oldIndex - 2) : 
									newName = word.substr(oldIndex + 2, index - oldIndex - 3) );
			}
			else
			{
				//なければこれは数字ですー
				if(cnt < 4){
					list[cnt] = atoi( word.substr(oldIndex, index - oldIndex).c_str() );
					cnt++;
				}
			}
			oldIndex = index + 1;
			index = word.find(",", oldIndex);
		}

		//そろっていたらロードしようか・・・
		std::string filePass;
		filePass.append( this->resourcePass );
		filePass.append( "/" );
		filePass.append( this->resourcePass_2 );
		filePass.append( "/" );
		filePass.append( pass );
		filePass.append( this->extension );
			
		//読み込み開始
		MYGAME::Text2DFactory::GetInstance()->loadGraph( 
			filePass.c_str(), newName.c_str(), list[0], list[1], list[2], list[3] );
	}

	//----------------------------------------------------------------------
	//モデルなどの読み込みデータからロードを開始
	//----------------------------------------------------------------------
	//@in : モデルなどの読み込み用データ
	void ResourceRoaderFile::loadResource(std::string& word)
	{
		//空は当然除外
		if( word.empty() )	return;
		std::string pass, newName;
		std::string::size_type index = 0, oldIndex = 0;
		
		//まずはコンマ探し
		index = word.find(",", oldIndex);

		while( index != string::npos )
		{
			//文字列ですー
			( pass.empty() ? pass = word.substr(oldIndex + 1, index - oldIndex - 2) : 
								newName = word.substr(oldIndex + 2, index - oldIndex - 3) );
			oldIndex = index + 1;
			index = word.find(",", oldIndex);
		}

		//そろっていたらロードしようか・・・
		std::string filePass;
		filePass.append( this->resourcePass );
		filePass.append( "/" );
		filePass.append( this->resourcePass_2 );
		filePass.append( "/" );
		filePass.append( pass );
		filePass.append( this->extension );
		
		const char* knd = this->resourceKnd.c_str();
		string::size_type type  = this->resourceKnd.find("モデル");
		if( type == 0 )
			MYGAME::Model3DFactory::GetInstance()->load_model( filePass.c_str(), newName.c_str() );
		else
		{
			type = this->resourceKnd.find("アニメモデル");
			if( type == 0)
				MYGAME::Model3DFactory::GetInstance()->load_mesh( filePass.c_str(), newName.c_str() );
			else
			{
				type = this->resourceKnd.find("BGM");
				if( type == 0)
					NanairoLib::MusicFactory::GetInstance()->GetBGM()->LoadMusic( filePass.c_str(), newName.c_str() );
				else
				{
					type = this->resourceKnd.find("SE");
					if( type == 0)
						NanairoLib::MusicFactory::GetInstance()->GetMUSIC()->LoadMusic( filePass.c_str(), newName.c_str() );
					else
					{
						type = this->resourceKnd.find("エフェクト");
						if( type == 0)
							NanairoLib::EffekseerClass::GetInstance()->EffekLoader( filePass.c_str(), newName.c_str() );
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------
	//キーワードの調査
	//----------------------------------------------------------------------
	//@in :　読み込みクラス
	//@in : 読み込みデータ
	//@out : true(ひっかかった) false(何もひっかかるものはない)
	bool LoaderFunction::checkScene(std::ifstream& fs, LPCSTR sceneName)
	{
		char letter[256];
		std::string str;
		std::string::size_type type;
		
		while( !fs.eof() && !fs.fail() )
		{
			fs.getline(	letter , sizeof(letter) );
			str = letter;
			type = str.find_first_of("//");
			if( type != string::npos )
				continue;
			else if( this->isScene( str, sceneName ) != -1 )
				return true;
		}
		return false;
	}

	//----------------------------------------------------------------------
	//キーワードで指定したシーンがあるかを調査
	//----------------------------------------------------------------------
	//@in : 読み込んだデータ
	//@in : キーワード
	//@out : true(シーンキーワードの右変のインデックス) false(-1)
	int LoaderFunction::isScene( string& str , LPCSTR sceneName )
	{
		std::string::size_type type;
		int num = type = str.find_first_of( ":" );
		if( type != string::npos )
		{
			type = str.find("Scene");
			if( type != string::npos ){
				type = str.find( sceneName );
				if( type != string::npos )
					return num;
			}
		}
		return -1;
	}

	//----------------------------------------------------------------------
	//キーワードの調査
	//----------------------------------------------------------------------
	//@in :　読み込みデータ
	//@in : 読み込みキーワード
	//@out : 成功(キーワードの右辺のインデックス) : 失敗(-1)
	int LoaderFunction::isObject( std::string& str , LPCSTR objectName )
	{
		std::string::size_type type;
		int num = type = str.find_first_of( ":" );
		if( type != string::npos )
		{
			type = str.find( objectName );
			if( type != string::npos )
				return num;
		}
		return -1;
	}

	//----------------------------------------------------------------------
	//その読み込みデータが終了の合図を出しているか
	//----------------------------------------------------------------------
	//@in :　読み込み文字列
	//@out : true(終了の合図) false(まだ終わっていません)
	bool LoaderFunction::checkComment_or_finish(std::string& str)
	{
		string::size_type type;
		//終了の合図
		type = str.find_first_of( "<>--" );
		return ( type != string::npos ? true : false );
	}

}