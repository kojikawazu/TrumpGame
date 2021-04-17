#pragma once
//--------------------------------------
//BGM�������N���X
//--------------------------------------
#pragma region �C���N���[�h
#include <MusicSound.h>

#include <dsound.h>
#include <MMSystem.h>

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")
#pragma endregion

namespace NanairoLib
{
	//---------------------------------------------------------
	//�f�R��
	//---------------------------------------------------------
	inline BGMFunc::BGMFunc(){}
	inline BGMFunc::~BGMFunc(){}

	//---------------------------------------------------------
	//���̃N���X���g���Ƃ��ɏ���������֐�
	//---------------------------------------------------------
	//@in : �E�B���h�E�n���h��
	//@out : �T�E���h�C���^�[�t�F�C�X
	#pragma region ���y�̏�����
	 IDirectSound8* BGMFunc::InitSound8(HWND hWnd)
	 {
		IDirectSound8 *sound;
		 //IDirectSound8�I�u�W�F�N�g�̃|�C���^���擾
		::DirectSoundCreate8(
			NULL,		//GUID�ɂ��f�o�C�X�w��BNULL�Ńf�t�H���g�f�o�C�X���w��
			&sound,	//Direct�T�E���h�I�u�W�F�N�g���󂯎��|�C���^�̃A�h���X
			NULL		//�\��̈�B���NULL
			);
		if(sound == NULL)	
			return sound;

		sound->SetCooperativeLevel(
			hWnd,			//����炷�E�B���h�E���w��
			DSSCL_NORMAL	//�n�[�h�E�F�A��L���x���B�قƂ�ǐ�L���Ȃ��ݒ�
			);

		//����ŏo�͂̐ݒ���f�t�H���g�i8bits,22KHz,��ڵ�j
		return sound;
	}

	IDirectSoundBuffer* BGMFunc::SetPrimary(IDirectSound8 *Dsound8,HWND hWnd){
		IDirectSoundBuffer* sound;
		DSBUFFERDESC Desc;	//�o�b�t�@
		::memset(&Desc,0,sizeof(Desc));
		Desc.dwSize = sizeof(Desc);
		Desc.dwFlags = DSBCAPS_PRIMARYBUFFER;	//�v���C�}���o�b�t�@
		//��͔ӂ�{�����[���̃R���g���[�����K�v�ȂƂ��Ƀt���O��ݒ肷��B

		Dsound8->CreateSoundBuffer(
			&Desc,			//DSBUFFERDESC�^�̕ϐ�
			&sound,	//IDirectSoundBuffer�I�u�W�F�N�g���󂯎��|�C���^�A�h���X
			NULL);			//�\��B���NULL	

		WAVEFORMATEX waveM;	//�o�̓t�H�[�}�b�g
		::memset(&waveM,0,sizeof(waveM));
		waveM.cbSize			= sizeof(waveM);
		waveM.wFormatTag		= WAVE_FORMAT_PCM;	//�g�`�t�H�[�}�b�g�̎w��B�����k�̐��g�`
		waveM.nChannels			= DSSCL_NORMAL;	//�o�̓`�����l�����̎w��B�Q�i��ڵ�j�ŌŒ�
		waveM.nSamplesPerSec	= DSSCL_NORMAL;	//�T���v�����O���[�g�̎w��B22050(22KHz)�ŌŒ�
		waveM.wBitsPerSample	= DSSCL_NORMAL;	//�ʎq�����x���̎w��B8�r�b�g�i256�i�K�j�ŌŒ�
	
		//�u���b�N�T�C�Y�B�ʎq���ibyte�P�ʁj* �`�����l�����Ŏw��
		waveM.nBlockAlign		= (waveM.wBitsPerSample >> 3) * waveM.nChannels;
		//�P�b�Ԃ̃u���b�N�T�C�Y�B�u���b�N�T�C�Y * �T���v�����O���[�g�Ŏw��B
		waveM.nAvgBytesPerSec	= waveM.cbSize * waveM.nSamplesPerSec;
	
		//�t�H�[�}�b�g�w��
		sound->SetFormat(&waveM);

		return sound;
	}
	#pragma endregion

	//------------------------------------------------------------------------------------
	//���y�̃����[�X
	//------------------------------------------------------------------------------------
	//@in : �T�E���h����C���^�[�t�F�C�X
	//@in : �T�E���h�o�b�t�@
	//@out : ���� ���s
	HRESULT BGMFunc::ClearSound(IDirectSound8 *Dsound8,IDirectSoundBuffer *soundBuffer)
	{
		ES_SAFE_RELEASE( soundBuffer );
		ES_SAFE_RELEASE( Dsound8 );
		return S_OK;
	}
	
	//-------------------------------------------------------------------------------
	//���y�̃��[�h
	//-------------------------------------------------------------------------------
	//@in : �T�E���h�C���^�[�t�F�C�X
	//@in : �t�@�C���p�X
	//@out : �T�E���h�o�b�t�@
	IDirectSoundBuffer* BGMFunc::LoadSoundMX(IDirectSound8 *Dsound8,LPSTR fileName)
	{
		IDirectSoundBuffer *secondBuffer = NULL;
		//wave�t�@�C���̓ǂݍ���
		HMMIO mio = ::mmioOpenA(
			fileName,	//�ǂݍ���WAV�t�@�C����
			NULL,		//�ǉ��p�����[�^�ݒ�BNULL��
			MMIO_ALLOCBUF | MMIO_READ);
		//MMIO_READ - �t�@�C����ǂݍ��݃��[�h�ŊJ��
		//MMIO_ALLOCBUF - �t�@�C��IO�o�b�t�@�������ō쐬����
		if(mio == NULL)	
			return NULL;

		//WAV�t�@�C���̃t�H�[�}�b�g������T�����ǂݍ���
		MMCKINFO info;
		::mmioDescend(
			mio,	//�I�[�v�������t�@�C���̃n���h��
			&info,	//�`�����N���̓��o�͐�
			NULL,	//�e�`�����N���
			0);		//�����t���O
		//�T���t���O�@ : 0 �ŏ��Ɍ������`�����N
		//�A : MMIO_FINDCHUNK lpck���Ɍ����`�����N��񂪂���B
		if(info.ckid != FOURCC_RIFF || info.fccType != mmioFOURCC('W','A','V','E'))
			goto LOAD_SE_EXIT;

		MMCKINFO check;
		//�t�H�[�}�b�g�����Ɂ��������Ă���̂ŁA�������ǂ������ׂ�
		check.ckid = mmioFOURCC('f','m','t',' ');
		int err = ::mmioDescend(mio,&check,&info,MMIO_FINDCHUNK);
		if(err != 0)	
			goto LOAD_SE_EXIT;
		if(check.cksize < (long)sizeof(PCMWAVEFORMAT))	
			goto LOAD_SE_EXIT;
	
		//�t�H�[�}�b�g�����̓ǂݍ���
		WAVEFORMATEX w; 
		::memset(&w,0,sizeof(w));
		//�f�[�^�̓ǂݍ���
		::mmioRead(
			mio,			//�ǂݎ��t�@�C���̃t�@�C���n���h��
			(char*)&w,		//�t�@�C������ǂݎ��ꂽ�f�[�^������o�b�t�@�̃A�h���X
			check.cksize);	//�t�@�C������ǂݎ��o�C�g��
		::mmioAscend(mio,&check,0);

		//�f�[�^�����܂Ői�݁A�����f�[�^�������i�[
		check.ckid = mmioFOURCC('d','a','t','a');
		::mmioDescend(mio,&check,&info,MMIO_FINDCHUNK);

		//�f�[�^�i�[��o�b�t�@���쐬
		DSBUFFERDESC desk;
		::memset(&desk,0,sizeof(desk));
		desk.dwSize			= sizeof(desk);
		desk.dwFlags		= DSBCAPS_GETCURRENTPOSITION2;	//�G�~�����[�V�������ɂ�萳�m�ȍĐ��J�[�\�����擾
		desk.dwBufferBytes	= check.cksize;
		desk.lpwfxFormat	= &w;

		Dsound8->CreateSoundBuffer(
			&desk,			//�o�b�t�@�̐ݒ�
			&secondBuffer,	//�Z�J���_���o�b�t�@�ɃA�h���X���w��
			NULL);			//�\��
		if(secondBuffer == NULL)	
			goto LOAD_SE_EXIT;

		//WAV�̃f�[�^���쐬�����o�b�t�@�ɓǂݍ���
		void *p;	//���b�N���ꂽ�o�b�t�@�̃|�C���^�i�[��
		DWORD size;	//���b�N���ꂽ�����̃T�C�Y
		secondBuffer->Lock(
			0,					//���b�N�J�n�ʒu
			desk.dwBufferBytes,	//���b�N�T�C�Y���w��
			&p,					//�ŏ��Ƀ��b�N���ꂽ�����ւ̃|�C���^���󂯎��
			&size,				//�T�C�Y���󂯎��
			NULL,				//��A���b�N�ANULL
			NULL,				//��A�T�C�Y�ANULL
			0);					//���b�N�C�x���g��ύX����t���O�A�O

		//���b�N��̃A�h���X�Ƀf�[�^��ǂݍ���
		::mmioRead(mio,(HPSTR)p,check.cksize);

		//�A�����b�N
		secondBuffer->Unlock(&p,size,NULL,NULL);

	//�G���[�������͐���������K��������ʂ��ĕ���B
	LOAD_SE_EXIT:
		::mmioClose(mio,0);
		return secondBuffer;
	}

	//-------------------------------------------------------------------------
	//���y�̍Đ�
	//-------------------------------------------------------------------------
	//@in : �T�E���h�o�b�t�@
	//@in : 0(���[�v�Ȃ�) ����ȊO(���[�v)
	//@in : 0(�ŏ��ɖ߂�) ����ȊO�i�r������j
	//@out : ���� ���s
	HRESULT BGMFunc::PlaySound(IDirectSoundBuffer *buffer,int mode,int posi)
	{
		//�炵�؂�//���[�v�Đ�
		DWORD flag = ((mode == 0) ? 0 : DSBPLAY_LOOPING);

		if(posi == 0)	
			this->ChangeBuffer(buffer,0);

		HRESULT check = buffer->Play(
			0,		//�\��ς�
			0,		//�T�E���h�̗D��x
			flag);	//�o�b�t�@�̍Đ����@
		return check;
	}
	
	//-------------------------------------------------------------
	//���y�̒�~
	//-------------------------------------------------------------
	//@in : �T�E���h�o�b�t�@
	//out : ���� ���s
	inline HRESULT BGMFunc::StopSound(IDirectSoundBuffer *buffer)
	{
		return buffer->Stop();
	}
	
	//---------------------------------------------------------------------------
	//�o�b�t�@�̃`�F�b�N
	//---------------------------------------------------------------------------
	//@in : �T�E���h�o�b�t�@
	//@in : �Đ��������ʒu
	//@out : ���� ���s
	inline HRESULT BGMFunc::ChangeBuffer(IDirectSoundBuffer *buffer,DWORD posi)
	{
		return (*buffer).SetCurrentPosition(posi);
	}
	
	//---------------------------------------------------------------
	//���y���Đ�����Ă��邩
	//---------------------------------------------------------------
	//@in : �T�E���h�o�b�t�@
	//@out : �Đ����Ă��� �Đ����Ă��Ȃ�
	inline HRESULT BGMFunc::CheckSound(IDirectSoundBuffer *buffer)
	{
		ULONG status;
		buffer->GetStatus(&status);
		return ((DSBSTATUS_PLAYING & status) != 0);
	}
	
	#pragma region �R���X�g���N�^
	inline BGMData::BGMData(){}
	inline BGMData::~BGMData(){}

	BGMData::BGMData(IDirectSound8 *Dsound8,LPSTR fileName) : used(true) , playFlag(false)
	{
		BGMFunc mm;
		this->secondBuffer = mm.LoadSoundMX(Dsound8,fileName);
		this->used = true;
		this->playFlag = false;
	}
	#pragma endregion

}