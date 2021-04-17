#ifndef MYDIERCTX_WHEEL_H
#define MYDIERCTX_WHEEL_H

namespace NanairoLib
{
	///360�p�A�i���O���͂𓾂�
	///@param analogX X���͂𓾂�
	///@param analogY Y���͂𓾂�
	///@param ltrigger ���g���K���͂𓾂�
	///@param rtrigger �E�g���K���͂𓾂�
	///@param inputType �����̃p�b�h�ԍ�
	///@note �z�C�[���ƒʏ�̃Q�[���p�b�h�ł̓A�i���O���͂̓x���������Ȃ�Ⴄ�B
	///�z�C�[���̓p�b�h�̔����̔����ȉ����炢�̊��o�ł���
	__IMPOETER extern int GetJoypadAnalogInput360( int* analogX, int* analogY,int* ltrigger, int* rtrigger, int inputType ) ;			// �W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�

	///LR�g���K�[�̒l���擾���܂��B
	///@param left L�g���K�[�l(0�`255)
	///@param right R�g���K�[�l(0�`255)
	///@param inputtype �����̃p�b�h�ԍ�
	__IMPOETER extern	int GetJoypadAnalogInputTrigger(int* left,int* right,int inputType);
	__IMPOETER extern	int	KeyboradBufferProcess( void ) ;											// �L�[�{�[�h�̃o�b�t�@����f�[�^���擾���鏈��
	__IMPOETER extern	int GetJoypadGUID( int PadIndex, GUID *GuidBuffer ) ;						// �W���C�p�b�h�̂f�tI�c�𓾂�
	__IMPOETER extern	int	ConvertKeyCodeToVirtualKey( int KeyCode ) ;								// �c�w���C�u�����̃L�[�R�[�h���� Windows �̉��z�L�[�R�[�h���擾����
	__IMPOETER extern	int	SetJoypadInputToKeyInput( int InputType, int PadInput, int KeyInput1, int KeyInput2 = -1 , int KeyInput3 = -1 , int KeyInput4 = -1  ) ; // �W���C�p�b�h�̓��͂ɑΉ������L�[�{�[�h�̓��͂�ݒ肷��
	__IMPOETER extern	int SetJoypadDeadZone( int InputType, double Zone ) ;						// �W���C�p�b�h�̖����]�[���̐ݒ���s��
	__IMPOETER extern	int	StartJoypadVibration( int InputType, int Power, int Time ) ;// �W���C�p�b�h�̐U�����J�n����
	__IMPOETER extern	int	StartJoypadVibration360( int InputType, int Power) ;

	///360�z�C�[���R���g���[�����ǂ������擾����
	///360�R���g���[���͒ʏ�̃Q�[���p�b�h��z�C�[���R���g���[��������A
	///����������񂺂�Ⴄ���߁A���炩���ߎ擾���Ă����ĈႢ���z������K�v������̂�������Ȃ��B
	///@param inputType �����̃p�b�h�ԍ�
	///@retval true �z�C�[���R���g���[���ł���
	///@retval false ����ȊO
	__IMPOETER extern bool Is360WheelControler(int inputType);

	///�U��������
	///@param InputType �����̃p�b�h�ԍ�
	///@param PowerL ����g���[�^
	///@param PowerR �����g���[�^
	///@note �U���Ɋւ��āA�����g�ƒ���g�̓z�C�[���n���h�����ɂ́A�}�j���A���Ƌt�ɂȂ��Ă�����ۂ�
	///�܂�A���������g�A�E������g�ɂȂ��Ă���悤���B�z�C�[���n���h���f�o�C�X�͐U�����T���߂�
	///�Ȃ��Ă��܂��悤��
	__IMPOETER extern	int StartJoypadVibration360( int InputType, int PowerL,int PowerR) ;
	//extern	int			StopJoypadVibration( int InputType ) ;	// �W���C�p�b�h�̐U�����~����
	__IMPOETER extern	int StopJoypadVibration360(int inputType);
	__IMPOETER extern	int GetJoypadPOVState( int InputType, int POVNumber ) ;						// �W���C�p�b�h�̂o�n�u���͂̏�Ԃ𓾂�( �P�ʂ͊p�x�̂P�O�O�{  ���S�ʒu�ɂ���ꍇ�� -1 ���Ԃ� )
	__IMPOETER extern	int GetJoypadName( int InputType, char *InstanceNameBuffer, char *ProductNameBuffer ) ;	// �W���C�p�b�h�̃f�o�C�X�o�^���Ɛ��i�o�^�����擾����
	__IMPOETER extern	int ReSetupJoypad( void ) ;													// �W���C�p�b�h�̍ăZ�b�g�A�b�v���s��( �V���ɐڑ����ꂽ�W���C�p�b�h������ꍇ�Ɍ��o����� )

}

#endif