#ifndef NanairoLib_MAPREADER_H
#define NanairoLib_MAPREADER_H

//------------------------------------------------------
//
//CSV����f�[�^��ǂݍ��ރN���X
//
//------------------------------------------------------

#pragma region �C���N���[�h
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
	//�R���}�̎���
	//---------------------------------------------------
	#define DEFAULT_SEPARATOR    ','

	//---------------------------------------------------
	//�_�u���N�H�[�e�[�V�����̎���
	//---------------------------------------------------	
	#define DEFAULT_QUOTE_CHARACTER    '"'

	//---------------------------------------------------
	//�}�b�v�n�f�[�^����
	//---------------------------------------------------
	#define MAXMAPX		  SCRW + 1000
	#define MAXMAPY		         SCRH
	#define MAXENEMMAPX	            8
	#define MAXENEMMAPY            35

	//---------------------------------------------------
	//�}�b�v�n�f�[�^�\��
	//---------------------------------------------------
	typedef struct MAPDATA{
		bool used;						//�g�p����
		int mapMX;						//�ő�X
		int mapMY;						//�ő�Y
		int map[MAXMAPY][MAXMAPX];		//�}�b�v���
	}MAPDATAA;

	typedef struct ENEMDATA{
		bool used;
		int mapMX;
		int mapMY;
		int map[MAXENEMMAPY][MAXENEMMAPX];
	}ENEMMAP;

	//---------------------------------------------------
	//�}�b�v�ntypedef
	//---------------------------------------------------
	typedef MAPDATAA*				PMAPDATA;
	typedef ENEMMAP*				PEMAPDATA;

	//----------------------------------------
	//CSV��ǂݍ��ނƂ��ɓ����Ŏg���N���X
	//----------------------------------------
	class MapReaderCSV
	{
	private:
		std::fstream* pstream;
		char SEPARATOR;
		char QUOTE;

	public:
		
		//------------------------------------------------------------------------
		//�f�R��
		//------------------------------------------------------------------------
		__IMPOETER MapReaderCSV();
		__IMPOETER MapReaderCSV(std::fstream& stream);
		__IMPOETER MapReaderCSV(std::fstream& stream,const char sep);
		__IMPOETER MapReaderCSV(std::fstream& stream,const char sep,const char quo);
		__IMPOETER ~MapReaderCSV(){}

		//--------------------------------------------------
		//CSV�t�@�C�����P�s�ǂݍ���ŁA�������Ĕz��ŕԂ�
		//--------------------------------------------------
		//@inout : �g�[�N��
		//@out : 0(����) -1(���s)
		__IMPOETER int Read(std::vector<std::string>& tokens);

		//------------------------------------------
		//�t�@�C���X�g���[�����N���[�Y����
		//------------------------------------------
		//@out :  0(����) -1(���s)
		__IMPOETER int Close();

	private:
		//----------------------------------------------------------
		//�t�@�C������P�s�ǂݍ���
		//----------------------------------------------------------
		//@in : �s�f�[�^
		//@out >=0(�ǂݍ��񂾃f�[�^��) -1(���s)
		__IMPOETER int GetNextLine(std::string& line);

		//-----------------------------------------------------------------
		//�f�[�^���p�X����
		//-----------------------------------------------------------------
		//@in : �s�f�[�^
		//@inout: �p�[�X�����f�[�^�̔z��(OUT)
		//@out : 0
		__IMPOETER int Parse(std::string& nextLine, std::vector<std::string>& tokens);
	};
	
	//--------------------------------------------
	//�t�B�[���h�A�G���������̃N���X�œǂݍ���
	//--------------------------------------------
	class FieldMap
	{
	public:
		//-------------------------
		//�f�R��
		//-------------------------
		__IMPOETER FieldMap();
		__IMPOETER ~FieldMap();

		//----------------------------------------------
		//�}�b�v�t�@�C���ǂݍ���
		//----------------------------------------------
		//@in : �t�@�C���p�X
		//@out : �t�@�C���}�b�v�f�[�^
		__IMPOETER PMAPDATA		ReadFile(LPCSTR fileName);

		//---------------------------------------------------
		//�G�t�@�C���ǂݍ���
		//---------------------------------------------------
		//@in : �t�@�C���p�X
		//@out : �t�@�C���G�f�[�^
		__IMPOETER PEMAPDATA	ReadFileEnemMap(LPCSTR fileName);	
	};

	typedef MapReaderCSV* PMapReaderCSV;
}
#endif