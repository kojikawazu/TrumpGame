#pragma once
//--------------------------------------------------------------------------------
//
//windows�p�t�H���g��`�悷��N���X
//
//--------------------------------------------------------------------------------

#pragma region �C���N���[�h
#include <DirectFont.h>
#include <tchar.h>
#include <strsafe.h>
#pragma endregion

namespace NanairoLib
{

	//----------------------------------------------------------------------------------
	//�f�R���n
	//----------------------------------------------------------------------------------
	#pragma region �R���X�g���N�^�n
	inline MyFont::MyFont() : OKFlag(false){}

	inline MyFont::MyFont(IDirect3DDevice9 *Device,PCUINT C)
	{
		OKFlag = this->createFont(Device, C);	
	}

	inline MyFont::~MyFont()
	{
		ES_SAFE_RELEASE(font.fontText);
	}
	#pragma endregion

	//----------------------------------------------------------------------------------
	//Getter Setter check
	//----------------------------------------------------------------------------------
	#pragma region Setter
	inline PFONTH MyFont::GetFont() const
	{
		return (PFONTH const)&font;			
	}

	inline const bool MyFont::isOK() const
	{
		return OKFlag;			
	}
	#pragma endregion

	//----------------------------------------------------------------------------------
	//�����p�ɍ쐬�����t�H���g
	//----------------------------------------------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �����R�[�h
	//@out : true(����) false(���s)
	bool MyFont::createFont(IDirect3DDevice9 *Device,PCUINT cd)
	{
		//�t�H���g�̐���
		int fontSize = 500;
		LOGFONT Lf =  {
			fontSize, 0, 0, 0, 32, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,			
			CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, __WordFontType
		};

		HFONT hFont;
		//�����Ŏ��s����Ύg��������
		if(!(hFont = ::CreateFontIndirect(&Lf)))
			return false;
		
		//�f�o�C�X�R���e�L�X�g�擾
		//�f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐����g���Ȃ������ŁE�E�E
		HDC hdc = ::GetDC(NULL);
		HFONT oldFont = (HFONT)::SelectObject(hdc, hFont);

		//�����R�[�h�擾
		UINT code = *cd;
	
		//�t�H���g�r�b�g�}�b�v�擾
		TEXTMETRIC TM;

		//�t�H���g���̎擾
		::GetTextMetrics( hdc, &TM);					
		GLYPHMETRICS GM;
		CONST MAT2 Mat = {{0,1}, {0,0}, {0,0}, {0,1}};

		//�f�o�C�X�R���e�L�X�g�őI������Ă���
		//TrueType �t�H���g�����̃r�b�g�}�b�v�܂��̓A�E�g���C�����擾
		DWORD size = ::GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
		BYTE *ptr = new BYTE[size];
		::GetGlyphOutline(hdc, code , GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

		//�f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
		::SelectObject(hdc, oldFont);
		::DeleteObject(hFont);
		::ReleaseDC(NULL, hdc);

		//�e�N�X�`���쐬
		if(FAILED(Device->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, 
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &this->font.fontText, NULL)))
		{
			if(FAILED(Device->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, 0, 
												D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &this->font.fontText, NULL)))
			{
				return false;									
			}
		}

		//�e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������
		::D3DLOCKED_RECT lockRect;
		if(FAILED(this->font.fontText->LockRect(0, &lockRect, NULL, D3DLOCK_DISCARD)))
		{
			if(FAILED(this->font.fontText->LockRect(0, &lockRect, NULL, 0)))
			{
				return false;
			}
		}

		//�t�H���g���̏�������
		int iOfs_x = GM.gmptGlyphOrigin.x;								//�����o���ʒu�i����jX
		int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;				//�����o���ʒu�i����jY
		int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;	//�t�H���g�r�b�g�}�b�v�̕���(4�o�C�g���ɒ���)
		int iBmp_h = GM.gmBlackBoxY;
		int Level = 17;
		int x, y;
		DWORD alpha, Color;
		font.fontW = iBmp_w;
		font.fontH = iBmp_h;

		FillMemory(lockRect.pBits, lockRect.Pitch * TM.tmHeight, 0);	//�w�肵���Ƃ���ɏ������ށI
		for(y = iOfs_y; y<iOfs_y + iBmp_h; y++)
		{
			for(x = iOfs_x; x<iOfs_x + iBmp_w; x++)
			{
				alpha = (255 * ptr[ (x - iOfs_x) + iBmp_w * (y - iOfs_y) ] ) / ( Level - 1 );
				Color = 0x00ffffff | (alpha << 24);
				::memcpy((BYTE*)lockRect.pBits + (lockRect.Pitch * y) + (4 * x), &Color, sizeof(DWORD));	
			}
		}

		this->font.fontText->UnlockRect(0);
		delete[] ptr;
		return true;
	}

}