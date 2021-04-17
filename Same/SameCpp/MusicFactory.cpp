#pragma once
//-------------------------------------------------------------------------
//
//���y����ێ�����t�@�N�g���[
//
//-------------------------------------------------------------------------
#include <MusicSound.h>
#include <DebugString.h>

namespace NanairoLib
{
	MusicFactory* MusicFactory::_music;

	#pragma region ���y�H��̃R���X�g���N�^
	MusicFactory::MusicFactory()
	{
		this->_bgm = new BGMFactory();
		this->_sound = new SEFactory();
	}
	MusicFactory::~MusicFactory()
	{
		ES_SAFE_DELETE(this->_bgm);
		ES_SAFE_DELETE(this->_sound);
	}
	#pragma endregion

	#pragma region ���ʉ��̃R���X�g���N�^
	SEFactory::SEFactory()
	{
		this->_se.clear();
	}

	SEFactory::~SEFactory()
	{
		this->AllRelease();
	}
	#pragma endregion
	
	
	//----------------------------------------------------------------------
	//���ʉ��̃��[�h
	//----------------------------------------------------------------------
	//@in : �E�B���h�E�n���h��
	void SEFactory::InitMusic(HWND hWnd)
	{
		BGMFunc func;
		this->_se.clear();

		this->Dsound8 = func.InitSound8(hWnd);
		this->soundBuffer = func.SetPrimary(this->Dsound8, hWnd);
	}

	//----------------------------------------------------------------------
	//���ʉ��̃��[�h
	//----------------------------------------------------------------------
	//@in : �t�@�C����
	//@in : �ۑ��ԍ�
	bool SEFactory::LoadMusic(LPCTSTR str,LPCSTR name)
	{
		OutPutStringFunction out;
		if( this->IsMusic( name ) )
		{
			out.SameOut_outputString( name );
			return false;
		}
		BGMFunc func;
		BGMData mc;
		mc.secondBuffer = func.LoadSoundMX( this->Dsound8,(LPSTR)str );
		
		if(mc.secondBuffer != NULL)
		{
			out.Success_outputString( str, name );
			mc.used = true;
			this->_se.insert( SEType( name, mc ) );
			return true;
		}
		else
		{
			out.Failed_outputString( str );
			return false;
		}
	}
	
	//----------------------------------------------------------------------
	//���ʉ��̃����[�X
	//----------------------------------------------------------------------
	//@in : �ۑ����O
	void SEFactory::ReleaseMusic(LPCSTR name)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() )
		{
			if ( this->Check( it->first.c_str() ) )
				func.StopSound( it->second.secondBuffer );
			ES_SAFE_RELEASE( it->second.secondBuffer );
			it = this->_se.erase( it );
		}
	}

	void SEFactory::AllRelease()
	{
		BGMFunc func;
		SEIterator it = this->_se.begin();
		while( it != this->_se.end() )
		{
			if ( this->Check( it->first.c_str() ) )
				func.StopSound( it->second.secondBuffer );
			ES_SAFE_RELEASE( it->second.secondBuffer );
			it++;
		}
		this->_se.clear();
		func.ClearSound(this->Dsound8,this->soundBuffer);
	}

	//----------------------------------------------------------------------
	//�~���[�W�b�N�̎擾
	//----------------------------------------------------------------------
	//@in : ���y�ۑ��ԍ�
	//@inout : �ۑ��|�C���^
	//@out : true(����) fale(���s)
	bool SEFactory::GetMusic(LPCSTR name,NanairoLib::BGMData* SEData)
	{
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() )
		{
			SEData = &(it->second);
			return true;
		}
		return false;
	}
	
	//----------------------------------------------------------------------
	///�~���[�W�b�N�͎g���Ă��邩
	//----------------------------------------------------------------------	
	bool SEFactory::IsMusic(LPCSTR name)
	{
		SEIterator it = this->_se.find( name ); 
		return ( it != this->_se.end() ? true : false);
	}
	
	//----------------------------------------------------------------------
	//�~���[�W�b�N�̃v���C
	//----------------------------------------------------------------------
	//@in : ���y�ۑ��ԍ�
	//@in : 0���炵�؂� ����ȊO�����[�v�Đ�
	//@in : 0���ŏ�����	����ȊO���~�߂��ꏊ����
	void SEFactory::Play(LPCSTR name,int mode,int pos)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() )// && !this->Check( name ) )
			func.PlaySound(it->second.secondBuffer, mode, pos);
	}
	
	//----------------------------------------------------------------------
	//�~���[�W�b�N�̃G���h
	//----------------------------------------------------------------------
	//@in : ���y�ۑ��ԍ�
	void SEFactory::Stop(LPCSTR name)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		if( it != this->_se.end() && this->Check( name ) )
			func.StopSound( it->second.secondBuffer);
	}

	//----------------------------------------------------------------------
	//�~���[�W�b�N�̃`�F�b�N
	//----------------------------------------------------------------------
	///S_OK		���@false ���ĂȂ�
	///S_FALSE	��	true  ���Ă�
	bool SEFactory::Check(LPCSTR name)
	{
		BGMFunc func;
		SEIterator it = this->_se.find( name );
		return (it != this->_se.end() && func.CheckSound( it->second.secondBuffer ) != S_OK );
	}
	
	//-----------------------------------------------------------------------------------
	/////////////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------

	//----------------------------------------------------------------------
	//BGM�R���X�g���N�^
	//----------------------------------------------------------------------
	BGMFactory::BGMFactory()
	{
		this->_bgm.clear();
		this->OnSound();
	}
	
	//----------------------------------------------------------------------
	//�f�X�g���N�^
	//----------------------------------------------------------------------
	BGMFactory::~BGMFactory()
	{
		this->AllRelease();
	}

	//----------------------------------------------------------------------
	//���y�������[�X
	//----------------------------------------------------------------------
	//@in : �ۑ����O
	void BGMFactory::ReleaseMusic(LPCSTR name)
	{
		BGMIterator it = this->_bgm.find( name );

		SEFunc func;
		while( it != this->_bgm.end() )
		{
			this->Stop( (*it).first.c_str() );
			func.ReleaseMusic( (*it).first.c_str() );	
			this->_bgm.erase( it );
		}
	}

	//----------------------------------------------------------------------
	//���ׂă����[�X
	//----------------------------------------------------------------------
	void BGMFactory::AllRelease()
	{
		BGMIterator it = this->_bgm.begin();

		SEFunc func;
		while( it != this->_bgm.end() )
		{
			LPCSTR name = (*it).first.c_str();
			if( this->Check( name ) )
				this->Stop( name );
			func.ReleaseMusic( name );	
			it++;
		}
		this->_bgm.clear();
	}

	//----------------------------------------------------------------------
	//���݂��Ă��邩
	//----------------------------------------------------------------------
	//@in : �ۑ����O
	//@out : true(���ݒ�) false(���݂��Ă��Ȃ�)
	bool BGMFactory::IsMusic(LPCSTR name)
	{
		return !( this->_bgm.find( name ) != this->_bgm.end() );
	}

	//----------------------------------------------------------------------
	//�~���[�W�b�N�̎擾
	//----------------------------------------------------------------------
	//@in : �ۑ����O
	//@inout : �擾����|�C���^
	//@out : true(����) false(���s)
	bool BGMFactory::GetMusic(LPCSTR name,const SEData* bgm)
	{
		BGMIterator it = this->_bgm.find( name );
		if( it != this->_bgm.end() )
		{
			bgm = &(*it).second;
			return true;
		}
		return false;
	}
	
	//----------------------------------------------------------------------
	//���y�����[�h
	//----------------------------------------------------------------------
	//@in : �t�@�C���p�X
	//@in : �ۑ����O
	//@out : true(����) false(���s)
	bool BGMFactory::LoadMusic(LPCTSTR str,LPCTSTR name)
	{
		OutPutStringFunction out;
		if( !IsMusic( name ) )
		{
			out.SameOut_outputString( name );
			return false;	
		}
		SEData bgm;
		if( ( bgm = SEData( str, name ) ).used )
		{
			out.Success_outputString( str, name );
			this->_bgm.insert( BGMType( name, SEData( str, name ) ) );
			return true;
		}
		else
		{
			out.Failed_outputString( str );
			return false;
		}
	}
	
	//----------------------------------------------------------------------
	//�v���C
	//----------------------------------------------------------------------
	//@in : �ۑ����O
	void  BGMFactory::Play(LPCSTR name)
	{
		if( !this->IsSound() )	return ;

		SEFunc func;
		BGMIterator it = this->_bgm.find( name );
		//�g���ĂāA���Ă��Ȃ�������
		if( it != this->_bgm.end() && this->Check( name ) )
			func.PlayMusic( it->second.bgmName );
	}

	//----------------------------------------------------------------------
	//�X�g�b�v
	//----------------------------------------------------------------------
	//@in : �ۑ����O
	void  BGMFactory::Stop(LPCSTR name)
	{
		SEFunc func;
		BGMIterator it = this->_bgm.find( name );
		//�g���ĂāA���Ă��Ȃ�������
		if( it != this->_bgm.end() && !this->Check( name ) )
			func.StopMusic( it->second.bgmName );
	}

	//----------------------------------------------------------------------
	//�`�F�b�N
	//----------------------------------------------------------------------
	//@in : �ۑ����O
	///stopped	���@false ���ĂȂ�
	///noStop	��	true  ���Ă�
	bool  BGMFactory::Check(LPCSTR name)
	{
		SEFunc func;
		BGMIterator it = this->_bgm.find( name );
		return ( it != this->_bgm.end() && func.CheckMusic( it->second.bgmName ) );
	}
	
}