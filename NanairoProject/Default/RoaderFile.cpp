#pragma once

//---------------------------------------------------------
//
//�t�@�C�����烊�\�[�X�p�X��ǂݍ���Ń��[�h
//
//�Q�̓ǂݍ��݃��[�_�t�@�C��������
//�e���\�[�X�͓Ɨ����Ă��邱�ƁI
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
	//�R���X�g���N�^
	//----------------------------------------------------------------------
	ResourceRoaderFile::ResourceRoaderFile(LPCSTR filepass) : isReady(false)
	{
		this->passload( filepass );
	}

	//----------------------------------------------------------------------
	//�f�X�g���N�^
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
	//�w�肳�ꂽ���[�f�B���O�p�X����ǂݍ��݂��J�n����
	//----------------------------------------------------------------------
	//@in : �ǂݍ��ޗp�̃��[�f�B���O�p�X
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
	//�p�X���ォ��T��
	//----------------------------------------------------------------------
	//@in : �ǂݍ��񂾕�����
	void ResourceRoaderFile::checkPass(std::string& str)
	{
		//��͏��O-
		if( str.empty() )	return;
		
		//�u//�v�R�����g�������O
		std::string::size_type index = str.find_first_of("//");
		if( index != string::npos )
			return ;
		
		//���́u�F�v��T���܂�
		//�u�F�v�̍��ӂ͎��ʎq�A�E�ӂ͂��̎��ʂ��ꂽ�����̒��g
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
	//�ǂݍ��񂾃f�[�^�ɃL�[���[�h������ΕύX��
	//----------------------------------------------------------------------
	//@in : �ǂݍ��񂾕�����
	//@in : �L�[���[�h�����̂P�O�̃C���f�b�N�X
	void ResourceRoaderFile::SettingPass(std::string& pass, int index)
	{
		std::string answer = pass.substr( index + 1 );
		std::string::size_type i = pass.find("���\�[�X�p�X");

		if( pass.find("�f�t�H���g") != std::string::npos)
			this->resourcePass = answer;
		else if( pass.find("���\�[�X�p�X") != std::string::npos )
			resourcePass_2 = answer;
		else if( pass.find("�ǂݍ��ݎ��ʎq") != std::string::npos )
			resourceKnd = answer;
		else if( pass.find("�g���q") != std::string::npos )
			extension = answer;
		else if( pass.find("�t�@�C����") != std::string::npos )
		{
			if( !this->resourcePass.empty() && !this->resourcePass_2.empty() &&
				!this->resourceKnd.empty() && !this->extension.empty() )
				isReady = true;
		}
	}

	//----------------------------------------------------------------------
	//�摜�ǂݍ��݃f�[�^���烍�[�h���J�n
	//----------------------------------------------------------------------
	//@in : �摜�p�ǂݍ��ݗp�f�[�^
	void ResourceRoaderFile::loadResourceGraph(std::string& word)
	{
		//��͓��R���O
		if( word.empty() )	return;

		short cnt = 0;
		int list[] = {0,0,0,0};
		std::string pass, newName;
		std::string::size_type index = 0, oldIndex = 0;
		
		//�܂��̓R���}�T��
		index = word.find(",", oldIndex);

		while( index != string::npos )
		{
			//����������""�����邩�ǂ���
			std::string::size_type _con = word.find('"', index - 1);
			if( _con != string::npos )
			{
				//�������炱��͕�����ł��[
				( pass.empty() ? pass = word.substr(oldIndex + 1, index - oldIndex - 2) : 
									newName = word.substr(oldIndex + 2, index - oldIndex - 3) );
			}
			else
			{
				//�Ȃ���΂���͐����ł��[
				if(cnt < 4){
					list[cnt] = atoi( word.substr(oldIndex, index - oldIndex).c_str() );
					cnt++;
				}
			}
			oldIndex = index + 1;
			index = word.find(",", oldIndex);
		}

		//������Ă����烍�[�h���悤���E�E�E
		std::string filePass;
		filePass.append( this->resourcePass );
		filePass.append( "/" );
		filePass.append( this->resourcePass_2 );
		filePass.append( "/" );
		filePass.append( pass );
		filePass.append( this->extension );
			
		//�ǂݍ��݊J�n
		MYGAME::Text2DFactory::GetInstance()->loadGraph( 
			filePass.c_str(), newName.c_str(), list[0], list[1], list[2], list[3] );
	}

	//----------------------------------------------------------------------
	//���f���Ȃǂ̓ǂݍ��݃f�[�^���烍�[�h���J�n
	//----------------------------------------------------------------------
	//@in : ���f���Ȃǂ̓ǂݍ��ݗp�f�[�^
	void ResourceRoaderFile::loadResource(std::string& word)
	{
		//��͓��R���O
		if( word.empty() )	return;
		std::string pass, newName;
		std::string::size_type index = 0, oldIndex = 0;
		
		//�܂��̓R���}�T��
		index = word.find(",", oldIndex);

		while( index != string::npos )
		{
			//������ł��[
			( pass.empty() ? pass = word.substr(oldIndex + 1, index - oldIndex - 2) : 
								newName = word.substr(oldIndex + 2, index - oldIndex - 3) );
			oldIndex = index + 1;
			index = word.find(",", oldIndex);
		}

		//������Ă����烍�[�h���悤���E�E�E
		std::string filePass;
		filePass.append( this->resourcePass );
		filePass.append( "/" );
		filePass.append( this->resourcePass_2 );
		filePass.append( "/" );
		filePass.append( pass );
		filePass.append( this->extension );
		
		const char* knd = this->resourceKnd.c_str();
		string::size_type type  = this->resourceKnd.find("���f��");
		if( type == 0 )
			MYGAME::Model3DFactory::GetInstance()->load_model( filePass.c_str(), newName.c_str() );
		else
		{
			type = this->resourceKnd.find("�A�j�����f��");
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
						type = this->resourceKnd.find("�G�t�F�N�g");
						if( type == 0)
							NanairoLib::EffekseerClass::GetInstance()->EffekLoader( filePass.c_str(), newName.c_str() );
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------
	//�L�[���[�h�̒���
	//----------------------------------------------------------------------
	//@in :�@�ǂݍ��݃N���X
	//@in : �ǂݍ��݃f�[�^
	//@out : true(�Ђ���������) false(�����Ђ���������̂͂Ȃ�)
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
	//�L�[���[�h�Ŏw�肵���V�[�������邩�𒲍�
	//----------------------------------------------------------------------
	//@in : �ǂݍ��񂾃f�[�^
	//@in : �L�[���[�h
	//@out : true(�V�[���L�[���[�h�̉E�ς̃C���f�b�N�X) false(-1)
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
	//�L�[���[�h�̒���
	//----------------------------------------------------------------------
	//@in :�@�ǂݍ��݃f�[�^
	//@in : �ǂݍ��݃L�[���[�h
	//@out : ����(�L�[���[�h�̉E�ӂ̃C���f�b�N�X) : ���s(-1)
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
	//���̓ǂݍ��݃f�[�^���I���̍��}���o���Ă��邩
	//----------------------------------------------------------------------
	//@in :�@�ǂݍ��ݕ�����
	//@out : true(�I���̍��}) false(�܂��I����Ă��܂���)
	bool LoaderFunction::checkComment_or_finish(std::string& str)
	{
		string::size_type type;
		//�I���̍��}
		type = str.find_first_of( "<>--" );
		return ( type != string::npos ? true : false );
	}

}