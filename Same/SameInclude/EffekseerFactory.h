#ifndef NanairoLib_EFFEKCLASS_H
#define NanairoLib_EFFEKCLASS_H

//-------------------------------------------------------------------------------------
//�G�t�F�N�V�A�𓱓�
//�G�t�F�N�V�A�}�l�[�W���[
//-------------------------------------------------------------------------------------

#pragma region �C���N���[�h

#ifndef	__EFFEKSEER_BASE_PRE_H__
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef NanairoLib_DXDX_H
#include <DirectNeed.h>
#endif

#ifndef NanairoLib_CAMERA_H
#include <DirectCamera.h>
#endif

#pragma endregion

namespace NanairoLib
{

#pragma region ���O�ύX
	//-------------------------------------------------------------------------------------
	//���O�ύX
	//-------------------------------------------------------------------------------------
	typedef Effekseer::Effect*										PEffekt;
	typedef EffekseerRenderer::Renderer*							PEffektRenderer;
	typedef Effekseer::Manager*										PEffektManager;
	typedef Effekseer::Handle										EffekHandle;
	typedef std::map<std::string, Effekseer::Effect*>				efkMap;
	typedef std::map<std::string, Effekseer::Effect*>::iterator		efkIte;
	typedef std::map<std::string, Effekseer::Effect*>::value_type	efkInput;
#pragma endregion

	//-------------------------------------------------------------------------------------
	//�G�t�F�N�V�A�N���X(EffekseerManagerClass)
	//�V���O���g���N���X
	//-------------------------------------------------------------------------------------
	class EffekseerClass
	{
		private:
		//**************************************************************
			static EffekseerClass*			efekseer;				//�V���O���g���|�C���^
			efkMap							effekMap;				//�G�t�F�N�g�}�b�v
			PEffektRenderer					render;					//�G�t�F�N�g�h���[�N���X
			PEffektManager					manager;				//�G�t�F�N�g�Ǘ��N���X
		
		//**************************************************************
		private:
		//�����͊�{�I�Ɉ����Ȃ�
		//**************************************************************
			
			//------------------------------------------------------------------------------------
			//�R�s�[�K�[�h
			//------------------------------------------------------------------------------------
			__IMPOETER EffekseerClass();
			__IMPOETER EffekseerClass(const EffekseerClass& cl);
			__IMPOETER EffekseerClass& operator = (const EffekseerClass& cl){	return (*this);	}
			__IMPOETER ~EffekseerClass();

			//--------------------------------
			//�������Ɉ�x�������s
			//--------------------------------
			__IMPOETER void InitXAudio();	
			__IMPOETER void EffektLoad();

			//--------------------------------
			//�j�����Ɉ�x�������s
			//--------------------------------
			__IMPOETER void EffektDestory();
			__IMPOETER void Effektrelease();
	
		//**************************************************************
		public:
			//---------------------------------------------------
			//�V���O���g���p���\�b�h
			//---------------------------------------------------
			__IMPOETER static EffekseerClass* GetInstance();
			__IMPOETER static void deleteInstance();
			__IMPOETER PEffektManager GetManager() const{	return manager;	}

		public:
			//**************************************************************
			//�Đ�����Ă���G�t�F�N�g�̏����̗L����ݒ肷��B
			//��ʂƂ߂���A�����Ȃ�������Ƃ����������Ɏg�p�B

			//--------------------------------------
			//�X�V�̗L���ݒ�
			//--------------------------------------
			//@�G�t�F�N�g���Đ����̃n���h��
			//@�X�V�̗L��
			__IMPOETER void SetUpdateEnable(EffekHandle handle, bool isUpdate = true);
	
			//--------------------------------------
			//�`��̗L���ݒ�
			//--------------------------------------
			//@�G�t�F�N�g���Đ����̃n���h��
			//@�X�V�̗L��
			__IMPOETER void SetDrawEnable(EffekHandle handle, bool isDraw = true);

			//**************************************************************
			//���̍Đ�����Ă���G�t�F�N�g�̈ʒu�E�g�嗦�E�p�x�̕ύX���X�V
			//�����āA�r���[�X�V
			//���ׂĕύX���ꂽ�Ƃ��ɍX�V����΂n�j�I

			//-----------------------------------------
			//�G�t�F�N�g�̃x�N�g���^�X�V
			//-----------------------------------------
			//@�G�t�F�N�g���Đ����Ă���n���h��
			//@�G�t�F�N�g�̍ŐV�ʒu
			//@�G�t�F�N�g�̍ŐV�p�x
			//@�G�t�F�N�g�̍ŐV�g�k
			__IMPOETER void EffektUpdateVector(EffekHandle handle, PCVECTOR3 pos, PCVECTOR3 rota, PCVECTOR3 scale);
	
			//--------------------------------------
			//�G�t�F�N�g�̍s��^�X�V
			//--------------------------------------
			//@�G�t�F�N�g���Đ����Ă���n���h��
			//@�G�t�F�N�g�̍ŐV�ʒu
			//@�G�t�F�N�g�̍ŐV�p�x
			//@�G�t�F�N�g�̍ŐV�g�k
			__IMPOETER void EffektUpdateMatrix(EffekHandle handle, PCVECTOR3 pos, PCVECTOR3 rota, PCVECTOR3 scale);
	
			//------------------------------------------
			//�J�����N���X�Ńr���[�X�V
			//------------------------------------------
			__IMPOETER void RenderUpdate(PCAMERA camera);
	
			//------------------------------------------
			//���ڑ���r���[�X�V
			//------------------------------------------
			//@�X�V���鎋�_
			//@�X�V���钍���_
			//@�X�V���遪����
			__IMPOETER void RenderUpdate(PCVECTOR3 eye, PCVECTOR3 tarGet, PCVECTOR3 up);
	
			//**************************************************************
			//�i��T�C�N���Ɉ�x�̏����j

			//--------------------------------
			//�G�t�F�N�g�̃I�[���`��
			//--------------------------------
			__IMPOETER void EffektRender();

			//--------------------------------
			//�G�t�F�N�g�̍X�V
			//--------------------------------
			//@in : �X�V����e���|
			__IMPOETER void EffektUpdate(float updateSpd = 1.0f);
	
			//**************************************************************
			//�G�t�F�N�g���Đ�������n���h������ɓ���A
			//���̃n���h���𑀍삷��B
			//�Đ������ƃn���h���͑��݂��Ă��āA�Đ��I���Ƃ��̃n���h���͎g���Ȃ��Ȃ�B

			//---------------------------------------------------------------
			//�G�t�F�N�g�̍Đ�
			//---------------------------------------------------------------
			//@in	: �Đ����������O(���[�h�������O�����Ă�������
			//@in	: �Đ�����ʒu�i��{�I�Ɍ��_�j
			//@out	: �G�t�F�N�g�𐧌䂷��n���h��
			__IMPOETER Effekseer::Handle EffektPlay( LPCSTR name, PCVECTOR3 posi = NULL );
	
			//-------------------------------------------------
			//�G�t�F�N�g�̒�~
			//-------------------------------------------------
			//@in : ��~�������G�t�F�N�g�n���h��
			__IMPOETER void EffektStop(EffekHandle handle);

			//------------------------------------------------------------
			//�G�t�F�N�g�̂��̃n���h���͂܂����݂��H�A�Đ�����Ă��邩�H
			//------------------------------------------------------------
			//@in : �`�F�b�N�������G�t�F�N�g�n���h��
			//out : true(�Đ���) false(�Đ����Ă��Ȃ�)
			__IMPOETER bool IsEffektHandle(EffekHandle handling);
	
			//-------------------------------
			//�G�t�F�N�g�̃I�[���X�g�b�v
			//-------------------------------
			__IMPOETER void EffektAllstop();

			//------------------------------------------------
			//�n�߂̏�����
			//------------------------------------------------
			//@in : directX�p�f�o�C�X
			__IMPOETER void EffektInit(PDirectDevice Device);

			//------------------------------------------------
			//�G�t�F�N�g�̃��[�h
			//------------------------------------------------
			//@in : ���[�h�������p�X
			//@in : �V�������O��t����
			__IMPOETER void EffekLoader(::LPCSTR filename, ::LPCSTR newname);
			//**************************************************************
	};

	#define Effek EffekseerClass::GetInstance()->

	//-----------------------------------------------------------------
	//�g�p��
	//-----------------------------------------------------------------
	//���K�����Ȃ���Ȃ�Ȃ�����
	//�܂��͂��̃V���O���g���̏�������
	//Effek effectInit( DirectX�p�f�o�C�X );
	//
	//�S�̃G�t�F�N�g�̍X�V
	//Effek effectUpdate( �Đ��X�s�[�h ���1�~��s );
	//
	//�S�̃G�t�F�N�g�̕`��
	//Effek effectRender();
	//-----------------------------------------------------------------

	//�G�t�F�N�g(.efk)�t�@�C�������[�h
	//Effek effekLoader( �t�@�C���p�X , �V�������O��t���� );
	//
	//�ǂݍ��񂾃G�t�F�N�g���Đ�
	//�i�߂�l�j�n���h�� = Effek effectPlay( �������O , �Đ��������|�W�V���� );
	//
	//�Đ������G�t�F�N�g�̃|�W�V������A���O���A�X�P�[����ύX
	//Effek effectUpdateVector( �Đ������n���h��, �|�W�V�����A�A���O���A�X�P�[�� );
	//
	//�J�����̍X�V
	//Effek renderUpdate( �Đ������n���h��, ���_, �����_, ����� );
	//
	//�Đ����Ă��邩�`�F�b�N
	//Effek isEffectHandle(�@�Đ������n���h�� ) ? �Đ����Ă��� : �Đ��I��
	//
	//�G�t�F�N�g�̒�~�i�ꎞ��~����Ȃ��j
	//Effek effectStop();
	//-----------------------------------------------------------------
}

#endif