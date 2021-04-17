#pragma once

//-------------------------------------------
//
//CSV�}�b�v�f�[�^��ǂݍ���
//
//------------------------------------------
#include <MapReaderCSV.h>
using namespace std;

namespace NanairoLib
{

	#pragma region �R���X�g���N�^
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
	//CSV�t�@�C�����P�s�ǂݍ���ŁA�������Ĕz��ŕԂ�
	//--------------------------------------------------
	//@inout : �g�[�N��
	//@out : 0(����) -1(���s)
	int MapReaderCSV::Read(vector<std::string>& tokens)
	{
		tokens.clear();

		string nextLine;
		if(this->GetNextLine(nextLine) <= 0)	return -1;
		this->Parse(nextLine, tokens);
		return 0;
	}
	
	//----------------------------------------------------------
	//�t�@�C������P�s�ǂݍ���
	//----------------------------------------------------------
	//@in : �s�f�[�^
	//@out >=0(�ǂݍ��񂾃f�[�^��) -1(���s)
	int MapReaderCSV::GetNextLine(string& line)
	{
		if(!this->pstream || this->pstream->eof())	return -1;
		std::getline(*this->pstream, line);
		int len = (int)line.length();
		return len;
	}
	
	//-----------------------------------------------------------------
	//�f�[�^���p�X����
	//-----------------------------------------------------------------
	//@in : �s�f�[�^
	//@inout: �p�[�X�����f�[�^�̔z��(OUT)
	//@out : 0
	int MapReaderCSV::Parse(string& nextLine, vector<string>& tokens)
	{
		string token;
		bool interquotes = false;

		do
		{
			if(interquotes)
			{
				//�ŏ��́u"�v�ɓ��B���Ă����當�������
				token += '\n';
				if(this->GetNextLine(nextLine) < 0)
					break;
			}

			for(int i=0; i< (int)nextLine.length(); i++)
			{
				char c = nextLine.at(i);
				//'"'�Ȃ�
				if(c == QUOTE)
				{
					//�ŏ��́u"�v�ɓ��B���� & ��オ�͈͓� & ��オ�u"�v�ɓ��B
					//��F"....""
					if(interquotes && (int)nextLine.length() > (i + 1) &&
						nextLine.at(i + 1) == QUOTE)
					{
						//�}�����ēǂݍ��񂾕������΂�
						token += nextLine.at(i + 1);
						i++;
					}
					else
					{
						//�ŏ���"�ɓ��B
						interquotes = !interquotes;
						//��O���u,�v & ��オ�͈͓� & ��オ�u,�v
						//��F,",
						if(i > 2 && nextLine.at(i - 1) != SEPARATOR && 
							(int)nextLine.length() > (i + 1) &&
							nextLine.at(i + 1) != SEPARATOR)
						{
							//���̕����𓊓�
							token += c;
						}
					}
				}
				//�u,�v�ł܂��u"�v�����B���ĂȂ��Ȃ�
				else if(c == SEPARATOR && !interquotes)
				{
					//����string�ɑ}��
					//�����āA�V���ɕ������ׂ邽�߂̃N���A
					tokens.push_back(token);
					token.clear();
				}
				else	
					//�����Ȃ���΂ǂ�ǂ�}��
					token += c;
			}
			//�u"�v�̊Ԃ͑���
		}while(interquotes);

		tokens.push_back(token);
		return 0;
	}

	//------------------------------------------
	//�t�@�C���X�g���[�����N���[�Y����
	//------------------------------------------
	//@out :  0(����) -1(���s)
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