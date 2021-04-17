#pragma once
//-----------------------------------------------------------------------------------
//
//	�����n��̃N���X
//
//-----------------------------------------------------------------------------------

#pragma region �C���N���[�h
#include <Windows.h>
#include <tchar.h>
#include <DebugString.h>
using namespace std;
#pragma endregion

namespace NanairoLib
{
//----------------------------------------------------------------------------------------------------------
//���O�\���֐��ł�
//��

	//--------------------------------------------
	//�u�����t�@�C���v�Ƃ������Ƃ��������O���\�b�h
	//--------------------------------------------
	//@in : �t�@�C����
	void OutPutStringFunction::SameOut_outputString( LPCTSTR name )
	{
		OutputDebugString( _T("-- FileRead Error : SameName ") );
		OutputDebugString( name );
		OutputDebugString( _T(" --\n") );
	}

	//--------------------------------------------
	//�u�ǂݍ��ݐ����v�Ƃ������Ƃ��������O���\�b�h
	//--------------------------------------------
	//@in : �t�@�C�����A�V�������O
	void OutPutStringFunction::Success_outputString(LPCTSTR pass,LPCTSTR name){
		OutputDebugString( _T("-- FileRead Success : reading ") );
		OutputDebugString( pass );
		OutputDebugString( _T(" �� NewName is : ") );
		OutputDebugString( name );
		OutputDebugString( _T(" --\n") );
	}

	//--------------------------------------------
	//�u�ǂݍ��ݎ��s�v�Ƃ������Ƃ��������O���\�b�h
	//--------------------------------------------
	//@in : �t�@�C����
	void OutPutStringFunction::Failed_outputString(LPCTSTR pass){
		OutputDebugString( _T("-- FileRead Error : NotReading ") );
		OutputDebugString( pass );
		OutputDebugString( _T(" --\n") );
	}

	//--------------------------------------------
	//���O��������ĕ\��
	//--------------------------------------------
	//@in : ���O���X�g
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
//�g�������ȕ֗��@�\��������������N���X�ł���

	//---------------------------------------------------------------------------------
	//��������󔒕����ŕ������ĕԂ����\�b�h
	//---------------------------------------------------------------------------------
	//@in : ����������������
	//@out : ��������������Q
	//@cnt : �񐔐���
	void StringFunction::Split(std::string& in, std::vector<std::string>& out, int cnt)
	{
		this->Split( in, " ", out , cnt );
	}

	//---------------------------------------------------------------------------------
	//��������󔒕����ŕ������ĕԂ����\�b�h
	//---------------------------------------------------------------------------------
	//@in : ����������������
	//@in : �����L�[���[�h
	//@out : ��������������Q
	//@cnt : �񐔐���
	void StringFunction::Split(std::string& in, LPCSTR keyword,std::vector<std::string>& out, int cnt)
	{
		string::size_type type;
		std::string st;
		int oldIndex = 0, cnter = 0;
		bool div = (cnt <= 0 ? true : false );
		type = in.find( keyword , oldIndex );
		//�o�͕����Q���N���A���܂�
		out.clear();
		
		//�i���̕������݂�����) and ( div���}�C�i�X�Ȃ�K�� . div���v���X�Ŏw��񐔈ȉ��Ȃ�)
		while( type != string::npos && (div || cnter < cnt) )
		{
			st = in.substr( oldIndex, type - oldIndex );
			out.push_back( st );

			oldIndex = type + 1;
			type = in.find( keyword , oldIndex );
			cnter++;
		}

		//�c���ꂽ�������Ō�ɓ���Y�ꂸ��
		st = in.substr( oldIndex, in.size() - oldIndex );
		out.push_back( st );
	}

	//----------------------------------------------------
	//�O�̋󔒕������폜���ċl�߂�
	//----------------------------------------------------
	//@inout : �ϊ�������
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
	//�f�t�H���g�ȃp�X��O���֑������ĕԂ�
	//------------------------------------------------------------------------------------------------------
	//@out : �o���オ����������
	//@in : �ϊ���������
	//@in : �Ԃɋ��ޕ�����
	//@in : ���ꍞ�ޕ�����
	void StringFunction::GetDefaultPass(std::string& out, std::string& pass, LPCSTR dotpass, LPCSTR divword)
	{
		out.clear();
		string::size_type type;
		std::vector<std::string> word;
		int cnt = 0;
		//�\�����[�V��������ǂݍ��݂����p�X�܂ł̊Ԃ��擾������
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
	//�����񂩂瓯�����������邩�A����΂��̈ʒu��Ԃ�
	//-------------------------------------------------------------------------
	//@in : �Ώە�����
	//@in : �T��������
	//@out : ������̈ʒu
	int StringFunction::IsSameString(std::string& str, std::string& sameString)
	{
		string::size_type type = 0;
		type = str.find( sameString.c_str() );
		return ( type != string::npos ? type : -1 );
	}

//----------------------------------------------------------------------------------------------------------
//���[�h�Ŏg�������Ȃ��̂��W�߂��X�[�p�[�N���X�ł���
	
	//------------------------------------------------------------------------------------------------------------
	//�t�@�C�����J���ȒP����
	//------------------------------------------------------------------------------------------------------------
	//@inout : �t�@�C�����[�_�[�N���X
	//@in : �t�@�C���p�X
	//@in : true(����) false(�o��)
	//@in : true(�o�C�i��) false(�e�L�X�g)
	//@out : true(����) false(���s)
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
	//�t�@�C�������ȒP����
	//-------------------------------------------------
	void Loader::Close_the_file(std::fstream& fs)
	{
		fs.close();
	}

}