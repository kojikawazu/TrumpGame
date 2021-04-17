#ifndef MYDXFUNC_H
#define MYDXFUNC_H

//------------------------------------------------------
//
//DLL�̒��ŕێ����Ă��������N���X��f�[�^�������Ɋi�[
//�V���O���g���Ăяo�����邱�ƂŎg����
//
//------------------------------------------------------
#ifndef NanairoLib_VERTEX_H
#include <ResourceDrawer.h>
#endif

#ifndef NanairoLib_KEYS_H
#include <DirectKey.h>
#endif

namespace NanairoLib
{
	//--------------
	//�O���錾	
	//--------------
	class MYDXData;
	class KEYS;

	class MYDXData
	{
		private:
			short				usedCount;		//�g������
			HWND				hWnd;			//�E�B���h�E�n���h��
			IDirect3D9			*D3d;			//DirectX�̃N���X
			IDirect3DDevice9	*Device;		//�f�o�C�X
			
		private:
			__IMPOETER void init()
			{
				D3d = 0;
				Device = 0;
				this->usedCount++;
			}

		public:
			__IMPOETER MYDXData() : usedCount(0) 
			{
				if(usedCount == 0)	this->init();
			}

			__IMPOETER MYDXData(int counts){
				if(counts == 0)	this->init();
			}

			__IMPOETER ~MYDXData(){}
			
			__IMPOETER  IDirect3DDevice9* GetDevice() const{		return Device;	}
			__IMPOETER  IDirect3DDevice9** GetDeviceT() const{		return (IDirect3DDevice9** const)&Device;	}
			__IMPOETER  IDirect3D9* Get3D9(){					return D3d;		}
			__IMPOETER  IDirect3D9** Get3D9T(){				return &D3d;	}
			__IMPOETER  HWND GetWindow(){						return hWnd;	}
			__IMPOETER  HWND* GetWindowT(){					return &hWnd;	}

			__IMPOETER  void SetDevice(IDirect3DDevice9* D){	this->Device = D;	}
			__IMPOETER  void Set3D9(IDirect3D9* D){			this->D3d = D;		}
			__IMPOETER  void SetWindow(HWND H){				this->hWnd = H;		}
			
	};

	class MainFunction
	{
	private:	
		//----------------------------
		//�V���O���|�C���^
		//----------------------------
		static MainFunction* MainFunc;
	private:	
		//�����Ŏg���t�B�[���h�̓v���C�x�[�g��
		//��O�̓f�o�C�X���炢
		NanairoLib::MYDXData*	DXData;
		NanairoLib::Artisan*	custom;
		
	public:
		//�悭�����̂̓p�u���b�N�ŕۗ�
		D3DXMATRIX				viewMatrix, projMatrix, portMatrix;
		KEYS*					keys;
	private:	
		//------------------------------------------------------
		//�R�s�[�K�[�h
		//------------------------------------------------------
		__IMPOETER MainFunction();
		__IMPOETER MainFunction(const MainFunction& mmmm){}
		__IMPOETER MainFunction& operator= (MainFunction& mmmm)
		{
			return *MainFunc;
		}
	public:	
		//------------------------------------------------------
		//�C���X�^���X�擾
		//------------------------------------------------------
		__IMPOETER static MainFunction* GetInstance()
		{
			if(MainFunc == 0)
				MainFunc = new MainFunction();
			return MainFunc;
		}

		__IMPOETER static void deleteInstance()
		{
			delete MainFunc;
			MainFunc = NULL;
		}

		__IMPOETER ~MainFunction();
	
	public:	
		//-----------------------------------------------------------------------
		//Getter
		//-----------------------------------------------------------------------
		__IMPOETER MYDXData*	GetMYdevice() const{	return this->DXData;	}
		__IMPOETER Artisan*		GetArtisan() const{		return this->custom;	}
		__IMPOETER KEYS*		GetKey() const{			return this->keys;		}
	public:	
		//���W�ϊ�

		//----------------------------------------------------------------------------------------
		//���[���h���W����X�N���[�����W�ɕϊ�
		//----------------------------------------------------------------------------------------
		//@in : �ʒu�x�N�g��
		//@in : ��]�x�N�g��
		//@in : �g�k�x�N�g��
		//@out : �X�N���[�����W
		__IMPOETER D3DXVECTOR3 ChangeToScreen_world(RCVector3 pos,RCVector3 ang,RCVector3 sc);

		//------------------------------------------------------------
		//�X�N���[�����W���烏�[���h���W�ɕϊ�
		//------------------------------------------------------------
		//@in : �X�N���[�����W
		//@out : ���[���h���W
		__IMPOETER D3DXVECTOR3 ChangeToWorld_screen(RCVector3 pos);
		
		//---------------------------------------------
		//DirectX�̏�����
		//---------------------------------------------
		//@in : �C���X�^���X�n���h��
		//@out : true(����) false(���s)
		__IMPOETER bool InitDirectX(HINSTANCE hInst);
			
		//----------------------------------------------
		//�f�t�H���g�ݒ���܂Ƃ߂�
		//----------------------------------------------
		__IMPOETER void SetDefaultMatrix(); 

		//----------------------------------------------
		//���C�g�̃f�t�H���g�ݒ�
		//----------------------------------------------
		__IMPOETER void SetDefaultLight();

		//----------------------------------------------
		//�f�t�H���g�̃J�����ݒ�
		//----------------------------------------------
		__IMPOETER void SetDefaultCamera();
	};

	#define DirectFunc	MainFunction::GetInstance()->
	#define __KEYDATA	MainFunction::GetInstance()->GetKey()->GetKey()
	#define __MOUSEDATA	MainFunction::GetInstance()->GetKey()->GetMouse()
}

#endif