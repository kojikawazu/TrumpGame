#ifndef MYGAME_EFFEKACTIONER_H
#define MYGAME_EFFEKACTIONER_H
//------------------------------------------------------------------------------
//�G�t�F�N�V�A�𐧌䂷��P�̃N���X
//------------------------------------------------------------------------------
#ifndef NanairoLib_EFFEKCLASS_H
#include <EffekseerFactory.h>
#endif

namespace MYGAME
{
	//-----------------------------------------------------------------------------
	//�G�t�F�N�g�P�̃N���X
	//(�G�t�F�N�g�N���X�ɂP�ێ�������)
	//�P�̃G�t�F�N�g���Ǘ�����N���X
	//�Ȉ՗p�ɐ���
	//-----------------------------------------------------------------------------
	class EffekActioner
	{
	private:
		//**************************************************************************
		bool drawEna,updateEna,moveFlag, delFlag;				//�`��L���A�X�V�L��
		short animationCnt, AxisMode;							//�A�j���J�E���^�A�N�H�[�^�j�I�����[�h
		NanairoLib::Vector3 pos, rota, scale, Axis;				//�ʒu�A�p�x�A�g�k�A�C�ӎ�
		Effekseer::Handle handle;								//�G�t�F�N�g�n���h��
		LPSTR effName;

	public:
		//**************************************************************************
																		
		EffekActioner(LPCSTR name);
		EffekActioner(LPCSTR name, NanairoLib::PCVector3 pos, NanairoLib::PCVector3 rota, NanairoLib::PCVector3 scale);		
		~EffekActioner();
		void DeleteOBJ();
		void SameInit();
		//**************************************************************************
	
		//�e�t�B�[���h�̑��
		void SetPosi(NanairoLib::PCVector3 pos);
		void SetRota(NanairoLib::PCVector3 rota);
		void SetScale(NanairoLib::PCVector3 scale);
		NanairoLib::PVector3 GetPosi() const;
		NanairoLib::PVector3 GetAngle() const;
		NanairoLib::PVector3 GetScale() const;

		//**************************************************************************

		//�G�t�F�N�g�̑���
		void EfekPlay();
		void EfekStop();
		bool IsPlaying();
		void ChangeUpdateEnable(bool isUpdate);
		void ChangeDrawsEnable(bool isDraw);

		//**************************************************************************
	
		//�G�t�F�N�g�̍X�V
		void ChangePosAngSclEffect();
		void EfekObjectUpdate();
	
		//**************************************************************************
	
	};

}
#endif