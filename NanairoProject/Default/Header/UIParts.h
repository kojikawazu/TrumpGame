#ifndef _MYGAME_UIPARTS_H
#define _MYGAME_UIPARTS_H

////////////////////////////////////
//std
#ifndef _STRING_
#include <string>
#endif

////////////////////////////////////
//NanairoLib
#ifndef _NanairoLib_MYVECTOR_H
#include <DirectParts.h>
#endif

#ifndef MYDIRECTX_LIGHTCOLOR_H
#include <DirectLight.h>
#endif

////////////////////////////////////
//MYGAME
#ifndef MYGAME_OBJECTLIST_H
#include <OBjectList.h>
#endif

//---------------------------------------------------------
//
//�����ɂ͕K�v�ȃp�[�c��u���Ă����܂��`
//���̃w�b�_�̓C���N���[�h�K�{�ł�
//
//---------------------------------------------------------
//
//�o�b�N�O���E���h�N���X�͔ėp�I�u�W�F�N�g���p�����Ă���̂�
//�e���v���[�g���X�g�ɒǉ��\
//
//----------------------------------------------------

namespace MYGAME
{
	//------------------------------------------------------
	//�ȈՔw�i��\�����������Ɏg�p
	//------------------------------------------------------
	class BackGround_2D : public NanairoLib::NormalObject
	{
	public:
		std::string				backName;
		NanairoLib::UIParts2D	ui;

	public:
		BackGround_2D(){	this->Init();	}
		BackGround_2D(LPCSTR name);
		virtual	~BackGround_2D(){	this->backName.clear();	}
		
	public:
		///////////////////////////////////////////
		//setter
		//�w�i�̉摜��
		void SetBackName(LPCSTR name){				this->backName = (LPSTR)name;	}
		//�J���[�̃Z�b�g
		void SetColor(NanairoLib::Vector4& col){	this->ui.color = col;			}
		///////////////////////////////////////////
		
		//̧���߲�����烍�[�h
		void loadParts(std::ifstream& fs);

		//̧�ق���ǂݍ��񂾃f�[�^����ق��������擾
		void readParts(std::string& str);

		//�{�c�ɂȂ邩������Ȃ��`��
		//�e�N�X�`���Ȃ��|���`��
		void DrawScreen_NoTexture();

		/////////////////////////////////////////////////
		//virtual
		void Init();
		void Draw2D();
		void Step(){}
		void Dispose(){}
		void Del(){}
	};
	//------------------------------------------------------
}

#endif