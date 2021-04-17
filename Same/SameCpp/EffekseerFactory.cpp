#pragma once
//--------------------------------------------------------------------------
///���̃v���W�F�N�g�́ueffekseer�v�Ƃ����c�[���ō����
///�G�t�F�N�g�𓮉抴�o�ŗ����Ă�����ʓI�ȃN���X
///effekseer�̑啔���̐ݒ�������ł��Ă���B
///EffekseerManager�N���X(�V���O���g��)
//--------------------------------------------------------------------------
//�C���N���[�h�₻�̑��������`
//**************************************************************************
#include <EffekseerFactory.h>
#if _DEBUG
#pragma comment(lib, "Effekseer.Debug.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Debug.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Debug.lib" )
#else
#pragma comment(lib, "Effekseer.Release.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Release.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Release.lib" )
#endif


//static IXAudio2*							g_xa2 = NULL;
//static IXAudio2MasteringVoice*			g_xa2_master = NULL;
#pragma endregion
//**************************************************************************
namespace NanairoLib
{
	//�C���X�^���X��
	NanairoLib::EffekseerClass* NanairoLib::EffekseerClass::efekseer;

	EffekseerClass::EffekseerClass()
	{
		this->InitXAudio();
	}

	EffekseerClass::~EffekseerClass()
	{
		this->Effektrelease();
		this->EffektDestory();
	}

	EffekseerClass* EffekseerClass::GetInstance()
	{
		if(efekseer == NULL)
			efekseer = new EffekseerClass();
		return efekseer;
	}

	void EffekseerClass::deleteInstance()
	{
		delete efekseer;
		efekseer = NULL;
	}

	//--------------------------------------------------------------------------
	//�G�t�F�N�V�A�̏�����
	//--------------------------------------------------------------------------
	void EffekseerClass::InitXAudio()
	{
		// XAudio2�̏��������s��
		//XAudio2Create( &g_xa2 );

		//g_xa2->CreateMasteringVoice( &g_xa2_master );
	}

	//--------------------------------------------------------------------------
	//�G�t�F�N�g�̏�����
	//--------------------------------------------------------------------------
	//@in : directX�p�f�o�C�X
	void EffekseerClass::EffektInit( PDirectDevice Device )
	{
		this->render = ::EffekseerRenderer::Renderer::Create(Device, 3000);			//�`��p�C���X�^���X�̐���
		this->manager = ::Effekseer::Manager::Create(3000);							//�G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
		this->manager->SetCoordinateSystem(::Effekseer::COORDINATE_SYSTEM_LH);		//����n�Ƀ`�F���W
		this->manager->SetSpriteRenderer(this->render->CreateSpriteRenderer());		//�`��p�C���X�^���X����`��@�\��ݒ�
		this->manager->SetRibbonRenderer(this->render->CreateRibbonRenderer());		//
		this->manager->SetRingRenderer(this->render->CreateRingRenderer());			//

		//�`��p�C���X�^���X����e�N�X�`���̋@�\�@�\��ݒ�
		//�Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		this->manager->SetTextureLoader(this->render->CreateTextureLoader());

		//���Đ��p�C���X�^���X�̐���
		//g_sound = ::EffekseerSound::Sound::Create(g_xa2, 16, 16);

		//���Đ��p�C���X�^���X����Đ��@�\���w��
		//g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());

		//���Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
		//�Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		//g_manager->SetSoundLoader(g_sound->CreateSoundLoader());

		//���e�s���ݒ�
		this->render->SetProjectionMatrix
			(
			::Effekseer::Matrix44().PerspectiveFovLH(GAKAKU,
			(float)(SCRW / SCRH), NEERDIS, TALLDIS)
			);
		this->effekMap.clear();
	}

	//--------------------------------------------------------------------------
	//�A�b�v�f�[�g�̗L���ݒ�
	//--------------------------------------------------------------------------
	///@in : �G�t�F�N�g�Đ����̃n���h��
	///@in : �X�V���邩�A�ۂ�
	void EffekseerClass::SetUpdateEnable(EffekHandle handle, bool isUpdate)
	{
		manager->SetPaused( handle, isUpdate );
	}

	//--------------------------------------------------------------------
	//�`��̗L���ݒ�
	//--------------------------------------------------------------------
	//@in : �G�t�F�N�g�Đ����̃n���h��
	//@in : �`�悷�邩�A�ۂ�
	void EffekseerClass::SetDrawEnable(EffekHandle handle, bool isDraw)
	{
		manager->SetShown(handle, isDraw );
	}
	
	//----------------------------------------------------------
	//�G�t�F�N�g�̗L��
	//----------------------------------------------------------
	///@in : �G�t�F�N�g�Đ����̃n���h��
	///@out : �G�t�F�N�g�����݂��Ă��邩
	bool EffekseerClass::IsEffektHandle(EffekHandle handling)
	{
		return this->manager->Exists( handling );
	}
	
	//---------------------------------------------------------
	//�I�u�W�F�N�g�̃f�[�^�������ŕϊ�
	//---------------------------------------------------------
	//@in : �G�t�F�N�g�Đ����̃n���h�� 
	//@in : �G�t�F�N�g�̈ʒu
	//@in : �G�t�F�N�g�̉�]�p�x
	//@in : �G�t�F�N�g�̊g�嗦
	///</summary>
	void EffekseerClass::EffektUpdateVector(EffekHandle handle, PCVECTOR3 pos,PCVECTOR3 rota, PCVECTOR3 scale)
	{
		this->manager->SetRotation( handle, rota->x,rota->y,rota->z );
		this->manager->SetLocation( handle, Effekseer::Vector3D(pos->x,pos->y,pos->z ) );
		this->manager->SetScale( handle, scale->x, scale->y, scale->z );
	}
	
	//----------------------------------------------------------
	//�s��ŕϊ�
	//----------------------------------------------------------
	//@in : �G�t�F�N�g�Đ����̃n���h�� 
	//@in : �G�t�F�N�g�̈ʒu
	//@in : �G�t�F�N�g�̉�]�p�x
	//@in : �G�t�F�N�g�̊g�嗦
	void EffekseerClass::EffektUpdateMatrix(EffekHandle handle, PCVECTOR3 pos, PCVECTOR3 rota, PCVECTOR3 scale)
	{
		Effekseer::Matrix43 mat;
		Effekseer::Vector3D posi,scal;

		mat.RotationXYZ(rota->x,rota->y,rota->z);
		posi.X = pos->x;
		posi.Y = pos->y;
		posi.Z = pos->z;
		scal.X = scale->x;
		scal.Y = scale->y;
		scal.Z = scale->z;

		mat.SetSRT(scal, mat, posi);
		this->manager->SetMatrix(handle, mat);
	}

	//-----------------------------------------------------------
	//�X�V����
	//-----------------------------------------------------------
	//@in : �X�V���x
	///����1.0f�ŏ[��
	void EffekseerClass::EffektUpdate(float updateSpd)
	{
		this->manager->Update( updateSpd );	//�G�t�F�N�g�̍X�V�������s��
	}

	//----------------------------------------------------------
	//�r���[�̍X�V
	//----------------------------------------------------------
	//@in :  my�J�����N���X
	void EffekseerClass::RenderUpdate(NanairoLib::CAMERA* camera)
	{
		const Vector3 *eye, *tar, *up;
		eye = (camera)->GetEYE();
		tar = (camera)->GetTARGET();
		up = (camera)->GetUP();

		//���_�ʒu���m��
		//�J�����s���ݒ�
		this->render->SetCameraMatrix
			(
			::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(eye->x,eye->y,eye->z), 
												::Effekseer::Vector3D(tar->x,tar->y,tar->z), 
													::Effekseer::Vector3D(up->x,up->y,up->z))
			);
	}

	//----------------------------------------------------------
	//�r���[�̍X�V
	//----------------------------------------------------------
	//@in : ���_
	//@in : �����_
	//@in : ������
	void EffekseerClass::RenderUpdate(PCVECTOR3 eye, PCVECTOR3 tarGet, PCVECTOR3 up)
	{
		//���_�ʒu���m��
		Effekseer::Vector3D eyes = ::Effekseer::Vector3D(eye->x,eye->y,eye->z);
		//�J�����s���ݒ�
		this->render->SetCameraMatrix
			(
			::Effekseer::Matrix44().LookAtLH( eyes, 
								::Effekseer::Vector3D(tarGet->x,tarGet->y,tarGet->z), 
								::Effekseer::Vector3D(up->x,up->y,up->z))
			);
	}
	
	//-----------------------------------
	//�G�t�F�N�g�̕`��
	//-----------------------------------
	void EffekseerClass::EffektRender()
	{

		//�G�t�F�N�g�̕`��J�n�������s���B
		this->render->BeginRendering();

		//�G�t�F�N�g�̕`����s���B
		this->manager->Draw();

		//�G�t�F�N�g�̕`��I���������s���B
		this->render->EndRendering();
	}

	//-----------------------------------------
	//�G�t�F�N�g�̊J�n
	//-----------------------------------------
	//@in  : �ۊǂ��Ă�G�t�F�N�g�f�[�^�ԍ�
	//@in  : �ŐV�ʒu
	//@out : �G�t�F�N�g�̃n���h��
	Effekseer::Handle EffekseerClass::EffektPlay(LPCSTR name, PCVECTOR3 posi)
	{
		D3DXVECTOR3 worldpos = ( posi == NULL ? D3DXVECTOR3() : (*posi) );
		efkIte it = this->effekMap.find( name );
		return ( ( it != this->effekMap.end() ) ? manager->Play( (*it).second, worldpos.x, worldpos.y, worldpos.z ) : -1 );
	}

	//-----------------------------------------------
	//�G�t�F�N�g�̒�~
	//-----------------------------------------------
	//@in : �G�t�F�N�g�Đ����̃n���h�� 
	void EffekseerClass::EffektStop(EffekHandle handle)
	{
		// �G�t�F�N�g�̒�~
		manager->StopEffect( handle );
	}

	//-----------------------------------
	//�G�t�F�N�g�̃I�[���߂�
	//-----------------------------------
	void EffekseerClass::EffektAllstop()
	{
		manager->StopAllEffects();
	}
	
	//-----------------------------------------
	//�G�t�F�N�g�̔p��
	//-----------------------------------------
	void EffekseerClass::Effektrelease()
	{
		// �G�t�F�N�g�̔j��
		efkIte it = this->effekMap.begin();
		while( it != this->effekMap.end() )
		{
			::Effekseer::Effect* efk = it->second;
			ES_SAFE_RELEASE( efk );
			it = this->effekMap.erase( it );
		}
	}
	
	//-------------------------------------
	//�G�t�F�N�g�N���X�̔j��
	//-------------------------------------
	void EffekseerClass::EffektDestory()
	{
		this->manager->StopAllEffects();

		// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
		this->manager->Destroy();

		// ���ɉ��Đ��p�C���X�^���X��j��
		//g_sound->Destory();

		// ���ɕ`��p�C���X�^���X��j��
		this->render->Destory();

		// XAudio2�̉��
		/*if( g_xa2_master != NULL )
		{
			g_xa2_master->DestroyVoice();
			g_xa2_master = NULL;
		}*/
		//ES_SAFE_RELEASE( g_xa2 );
	}
	
	//--------------------------------------------------------------------
	//�G�t�F�N�g�̓ǂݍ���
	//--------------------------------------------------------------------
	//@in : �p�X
	//@in : �V�������O
	void EffekseerClass::EffekLoader( ::LPCSTR filename, ::LPCSTR newname )
	{
		this->effekMap.insert( efkInput( newname, 
			( Effekseer::Effect::Create( this->manager, (const EFK_CHAR*)filename ) ) ) );
	}

}