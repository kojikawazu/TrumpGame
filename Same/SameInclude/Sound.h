#pragma once
#ifndef MYDIRECTX_SOUND_H
#define MYDIRECTX_SOUND_H

//-----------------------------------------------------------
//
//���y����N���X
//
//-----------------------------------------------------------
#include <DirectNeed.h>
#include <dsound.h>
#include <map>

namespace MyDirectX
{
	class BGMData;
	class SEData;

	typedef std::map<std::string, MyDirectX::SEData>				BGMMap;
	typedef std::map<std::string, MyDirectX::SEData>::iterator		BGMIterator;
	typedef std::map<std::string, MyDirectX::SEData>::value_type	BGMType;

	typedef std::map<std::string, MyDirectX::BGMData>				SEMap;
	typedef std::map<std::string, MyDirectX::BGMData>::iterator		SEIterator;
	typedef std::map<std::string, MyDirectX::BGMData>::value_type	SEType;

	//-------------------------------------------
	//BGM���N���X
	//-------------------------------------------
	class BGMData
	{
		public:
			bool used,playFlag;
			IDirectSoundBuffer *secondBuffer;
		public:
			__IMPOETER BGMData();
			__IMPOETER BGMData(IDirectSound8 *Dsound8,LPSTR fileName);
			__IMPOETER ~BGMData();
	};

	//--------------------------------------------------
	//���ʉ����N���X
	//--------------------------------------------------
	class SEData
	{
		public:
			bool used,playFlag;
			LPCSTR bgmName;
		public:
			__IMPOETER SEData();
			__IMPOETER SEData(LPCSTR fileName,LPCSTR name);
			__IMPOETER ~SEData();
	};

	//--------------------------------------------------
	//BGM�Ǘ�����N���X
	//--------------------------------------------------
	class BGMFunc
	{
		public:
			//---------------------------------------------------------
			//���̃N���X���g���Ƃ��ɏ���������֐�
			//---------------------------------------------------------
			//@in : �E�B���h�E�n���h��
			//@out : �T�E���h�C���^�[�t�F�C�X
			__IMPOETER	IDirectSound8* InitSound8(HWND hWnd);
			__IMPOETER	IDirectSoundBuffer* SetPrimary(IDirectSound8 *Dsound8,HWND hWnd);
			
			//------------------------------------------------------------------------------------
			//���y�̃����[�X
			//------------------------------------------------------------------------------------
			//@in : �T�E���h����C���^�[�t�F�C�X
			//@in : �T�E���h�o�b�t�@
			//@out : ���� ���s
			__IMPOETER	HRESULT ClearSound(IDirectSound8 *Dsound8,IDirectSoundBuffer *soundBuffer);
			
			//-------------------------------------------------------------------------------
			//���y�̃��[�h
			//-------------------------------------------------------------------------------
			//@in : �T�E���h�C���^�[�t�F�C�X
			//@in : �t�@�C���p�X
			//@out : �T�E���h�o�b�t�@
			__IMPOETER	IDirectSoundBuffer* LoadSoundMX(IDirectSound8 *Dsound8,LPSTR fileName);
			
			//-------------------------------------------------------------------------
			//���y�̍Đ�
			//-------------------------------------------------------------------------
			//@in : �T�E���h�o�b�t�@
			//@in : 0(���[�v�Ȃ�) ����ȊO(���[�v)
			//@in : 0(�ŏ��ɖ߂�) ����ȊO�i�r������j
			//@out : ���� ���s
			__IMPOETER	HRESULT PlaySound(IDirectSoundBuffer *buffer,int mode = 0,int posi = 0);
			
			//-------------------------------------------------------------
			//���y�̒�~
			//-------------------------------------------------------------
			//@in : �T�E���h�o�b�t�@
			//out : ���� ���s
			__IMPOETER	HRESULT StopSound(IDirectSoundBuffer *buffer);
			
			//---------------------------------------------------------------------------
			//�o�b�t�@�̃`�F�b�N
			//---------------------------------------------------------------------------
			//@in : �T�E���h�o�b�t�@
			//@in : �Đ��������ʒu
			//@out : ���� ���s
			__IMPOETER	HRESULT ChangeBuffer(IDirectSoundBuffer *buffer,DWORD posi);
			
			//---------------------------------------------------------------
			//���y���Đ�����Ă��邩
			//---------------------------------------------------------------
			//@in : �T�E���h�o�b�t�@
			//@out : �Đ����Ă��� �Đ����Ă��Ȃ�
			__IMPOETER	HRESULT CheckSound(IDirectSoundBuffer *buffer);
		public:

			__IMPOETER BGMFunc();
			__IMPOETER ~BGMFunc();
	};

	//--------------------------------------------------
	//���ʉ��Ǘ�����N���X
	//--------------------------------------------------
	class SEFunc
	{
		public:
			//------------------------------------------------------------
			//���y�̃��[�h
			//------------------------------------------------------------
			//@in : �t�@�C���p�X
			//@in : �V�������O
			//@out : ���� ���s
			__IMPOETER HRESULT InitMusic(LPCSTR fileName,LPCSTR bgmName);
			
			//-------------------------------------------------
			//���y�̍Đ�
			//-------------------------------------------------
			//@in : �Đ����������O
			//@out : ���� ���s
			__IMPOETER HRESULT PlayMusic(LPCSTR fileName);
			
			//---------------------------------------------
			//���y�̒�~
			//---------------------------------------------
			//@in : �Đ����Ă��閼�O
			//@out : ���� ���s
			__IMPOETER HRESULT StopMusic(LPCSTR fileName);
			
			//------------------------------------------------
			//���y�̃����[�X
			//------------------------------------------------
			//@in : �ۑ��������O
			//@out : ���� ���s
			__IMPOETER HRESULT ReleaseMusic(LPCSTR fileName);
			
			//-------------------------------------------
			//���y���Đ�����Ă��邩
			//-------------------------------------------
			//@in : �Đ����Ă��閼�O
			//@out : true(�Đ���) false(�Đ����Ă��Ȃ�)
			__IMPOETER bool CheckMusic(LPCSTR fileName);
		public:
			__IMPOETER SEFunc();
			__IMPOETER ~SEFunc();
	};

	//-----------------------------------------------------
	//BGM����ێ��E�Ǘ��E���삷��N���X
	//-----------------------------------------------------
	class BGMFactory
	{
		private:
			bool soundFlag;
			BGMMap	_bgm;
		public:
			//------------------------------------
			//�f�R��
			//------------------------------------
			__IMPOETER BGMFactory();
			__IMPOETER ~BGMFactory();
			__IMPOETER bool IsSound(){	return this->soundFlag;	}
			__IMPOETER void OnSound(){	this->soundFlag = true;	}
			__IMPOETER void OffSound(){	this->soundFlag = false;}
		
			//----------------------------------------------------------------------
			//���y�����[�h
			//----------------------------------------------------------------------
			//@in : �t�@�C���p�X
			//@in : �ۑ����O
			//@out : true(����) false(���s)
			__IMPOETER bool LoadMusic(LPCTSTR str,LPCTSTR name);
			
			//----------------------------------------------------------------------
			//���y�������[�X
			//----------------------------------------------------------------------
			//@in : �ۑ����O
			__IMPOETER void ReleaseMusic(LPCSTR name);
			
			//-------------------------------------------------
			//�I�[�������[�X
			//-------------------------------------------------
			__IMPOETER void AllRelease();

			//----------------------------------------------------------------------
			//�~���[�W�b�N�̎擾
			//----------------------------------------------------------------------
			//@in : �ۑ����O
			//@inout : �擾����|�C���^
			//@out : true(����) false(���s)
			__IMPOETER bool GetMusic(LPCSTR name,const MyDirectX::SEData* bgm);

			//----------------------------------------------------------------------
			//���݂��Ă��邩
			//----------------------------------------------------------------------
			//@in : �ۑ����O
			//@out : true(���ݒ�) false(���݂��Ă��Ȃ�)
			__IMPOETER bool IsMusic(LPCSTR name);

			//----------------------------------------------------------------------
			//�v���C
			//----------------------------------------------------------------------
			//@in : �ۑ����O
			__IMPOETER void Play(LPCSTR name);
			
			//----------------------------------------------------------------------
			//�X�g�b�v
			//----------------------------------------------------------------------
			//@in : �ۑ����O
			__IMPOETER void Stop(LPCSTR name);

			//----------------------------------------------------------------------
			//�`�F�b�N
			//----------------------------------------------------------------------
			//@in : �ۑ����O
			///stopped	���@false ���ĂȂ�
			///noStop	��	true  ���Ă�
			__IMPOETER bool Check(LPCSTR name);
		
	};

	//-----------------------------------------------------
	//���ʉ�����ێ��E�Ǘ��E���삷��N���X
	//-----------------------------------------------------
	class SEFactory
	{
		private:
			IDirectSound8		*Dsound8;		//���C���T�E���h
			IDirectSoundBuffer	*soundBuffer;	//�o�b�t�@
			SEMap				_se;
		private:
			__IMPOETER void AllRelease();

		public:
			__IMPOETER SEFactory();
			__IMPOETER ~SEFactory();
			__IMPOETER void InitMusic(HWND hWnd);

			//----------------------------------------------------------------------
			//���ʉ��̃��[�h
			//----------------------------------------------------------------------
			//@in : �t�@�C����
			//@in : �ۑ��ԍ�
			__IMPOETER bool LoadMusic(LPCTSTR str,LPCSTR name);

			//----------------------------------------------------------------------
			//���ʉ��̃����[�X
			//----------------------------------------------------------------------
			//@in : �ۑ����O
			__IMPOETER void ReleaseMusic(LPCSTR name);
		
			//----------------------------------------------------------------------
			//�~���[�W�b�N�̎擾
			//----------------------------------------------------------------------
			//@in : ���y�ۑ��ԍ�
			//@inout : �ۑ��|�C���^
			//@out : true(����) fale(���s)
			__IMPOETER bool GetMusic(LPCSTR name,MyDirectX::BGMData* SEData);
		
			//----------------------------------------------------------------------
			///�~���[�W�b�N�͎g���Ă��邩
			//----------------------------------------------------------------------	
			__IMPOETER bool IsMusic(LPCSTR name);
		
			//----------------------------------------------------------------------
			//�~���[�W�b�N�̃v���C
			//----------------------------------------------------------------------
			//@in : ���y�ۑ��ԍ�
			//@in : 0���炵�؂� ����ȊO�����[�v�Đ�
			//@in : 0���ŏ�����	����ȊO���~�߂��ꏊ����
			__IMPOETER void Play(LPCSTR name,int mode = 0,int pos = 0);
			
			//----------------------------------------------------------------------
			//�~���[�W�b�N�̃G���h
			//----------------------------------------------------------------------
			//@in : ���y�ۑ��ԍ�
			__IMPOETER void Stop(LPCSTR name);

			//----------------------------------------------------------------------
			//�~���[�W�b�N�̃`�F�b�N
			//----------------------------------------------------------------------
			///S_OK		���@false ���ĂȂ�
			///S_FALSE	��	true  ���Ă�
			__IMPOETER bool Check(LPCSTR name);
		
	};

	//--------------------------------------------------------
	//���y�Đ��H��N���X
	//<�V���O���g��>
	//���y���Ǘ�����N���X
	//--------------------------------------------------------
	class MusicFactory{
		private:
		//********************************************************
			static MusicFactory* _music;	//�V���O���g���|�C���^
			BGMFactory *_bgm;						//BGM�|�C���^
			SEFactory *_sound;				//���ʉ��|�C���^i
		//********************************************************
		private:
			//********************************************************
			//�R�s�[�K�[�h����
			__IMPOETER MusicFactory();
			__IMPOETER MusicFactory(const MusicFactory& text){}
			__IMPOETER MusicFactory& operator=(const MusicFactory& text){	return *this;	}
			__IMPOETER ~MusicFactory();

			//********************************************************
		public:
			//********************************************************
			//�ǂݎ��p
			__IMPOETER BGMFactory* GetBGM(){			return	_bgm;			}
			__IMPOETER SEFactory* GetMUSIC(){			return _sound;			}
			//********************************************************
			
			//********************************************************
			//�C���X�^���X�擾
			__IMPOETER static MusicFactory* getInstance(){
				if( _music == 0) _music = new MusicFactory();
				return  _music;
			}
			__IMPOETER static void deleteInstance(){
				delete _music;	_music = NULL;
			}
			//********************************************************
	};
}
#endif
