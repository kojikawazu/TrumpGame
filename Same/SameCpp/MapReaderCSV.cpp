#pragma once

//-------------------------------------------
//
//CSVマップデータを読み込む
//
//------------------------------------------
#include <MapReaderCSV.h>
using namespace std;

namespace NanairoLib
{

	#pragma region コンストラクタ
	inline MapReaderCSV::MapReaderCSV() :
						SEPARATOR(DEFAULT_SEPARATOR),
						QUOTE(DEFAULT_QUOTE_CHARACTER){}

	inline MapReaderCSV::MapReaderCSV(fstream& stream) : 
								SEPARATOR(DEFAULT_SEPARATOR),
								QUOTE(DEFAULT_QUOTE_CHARACTER),
								pstream(&stream){}

	inline MapReaderCSV::MapReaderCSV(fstream& stream,const char sep) : 
								SEPARATOR(sep),
								QUOTE(DEFAULT_QUOTE_CHARACTER),
								pstream(&stream){}

	inline MapReaderCSV::MapReaderCSV(fstream& stream,const char sep,const char quo) :
								SEPARATOR(sep),
								QUOTE(quo),
								pstream(&stream){}
	#pragma endregion

	//--------------------------------------------------
	//CSVファイルを１行読み込んで、分割して配列で返す
	//--------------------------------------------------
	//@inout : トークン
	//@out : 0(成功) -1(失敗)
	int MapReaderCSV::Read(vector<std::string>& tokens)
	{
		tokens.clear();

		string nextLine;
		if(this->GetNextLine(nextLine) <= 0)	return -1;
		this->Parse(nextLine, tokens);
		return 0;
	}
	
	//----------------------------------------------------------
	//ファイルから１行読み込む
	//----------------------------------------------------------
	//@in : 行データ
	//@out >=0(読み込んだデータ長) -1(失敗)
	int MapReaderCSV::GetNextLine(string& line)
	{
		if(!this->pstream || this->pstream->eof())	return -1;
		std::getline(*this->pstream, line);
		int len = (int)line.length();
		return len;
	}
	
	//-----------------------------------------------------------------
	//データをパスする
	//-----------------------------------------------------------------
	//@in : 行データ
	//@inout: パースしたデータの配列(OUT)
	//@out : 0
	int MapReaderCSV::Parse(string& nextLine, vector<string>& tokens)
	{
		string token;
		bool interquotes = false;

		do
		{
			if(interquotes)
			{
				//最初の「"」に到達していたら文字を閉じる
				token += '\n';
				if(this->GetNextLine(nextLine) < 0)
					break;
			}

			for(int i=0; i< (int)nextLine.length(); i++)
			{
				char c = nextLine.at(i);
				//'"'なら
				if(c == QUOTE)
				{
					//最初の「"」に到達する & 一個後が範囲内 & 一個後が「"」に到達
					//例："....""
					if(interquotes && (int)nextLine.length() > (i + 1) &&
						nextLine.at(i + 1) == QUOTE)
					{
						//挿入して読み込んだ文字を飛ばす
						token += nextLine.at(i + 1);
						i++;
					}
					else
					{
						//最初の"に到達
						interquotes = !interquotes;
						//一個前が「,」 & 一個後が範囲内 & 一個後が「,」
						//例：,",
						if(i > 2 && nextLine.at(i - 1) != SEPARATOR && 
							(int)nextLine.length() > (i + 1) &&
							nextLine.at(i + 1) != SEPARATOR)
						{
							//その文字を投入
							token += c;
						}
					}
				}
				//「,」でまだ「"」が到達してないなら
				else if(c == SEPARATOR && !interquotes)
				{
					//分割stringに挿入
					//そして、新たに文字調べるためのクリア
					tokens.push_back(token);
					token.clear();
				}
				else	
					//何もなければどんどん挿入
					token += c;
			}
			//「"」の間は続く
		}while(interquotes);

		tokens.push_back(token);
		return 0;
	}

	//------------------------------------------
	//ファイルストリームをクローズする
	//------------------------------------------
	//@out :  0(成功) -1(失敗)
	int MapReaderCSV::Close()
	{
		if(this->pstream)
		{
			this->pstream->close();
			this->pstream = NULL;
		}
		return 0;
	}
	
}