#pragma once
//----------------------------------------
//�Œ�p�C�v���C���Őݒ肷�郉�C�g�N���X
//----------------------------------------
#include <DirectLight.h>

namespace NanairoLib
{

	//---------------------------------------------------------------------------------
	//���C�g�̐ݒ���ȒP�ɂ��邽�߂Ƀf�t�H���g��p�ӂ��Ă���
	//�����Ńf�t�H���g�𑝂₵�Ă��n�j�I
	void SetLight1(D3DLIGHT9* lighting)
	{
		//���C�g�̎��
		lighting->Type = D3DLIGHT_DIRECTIONAL;
		//light->Type = D3DLIGHT_POINT;

		//���C�g�̈ʒu
		lighting->Position = D3DXVECTOR3(0,800,0);
	
		//���C�g�̌���
		lighting->Direction = D3DXVECTOR3(0,100,-10);
	
		//���C�g�̂��؂����[
		lighting->Specular = D3DXCOLOR(1,1,1,1);
	
		//���C�g�̒��ڌ�
		lighting->Ambient = D3DXCOLOR(1,1,1,1);
	
		//���C�g�̊���
		lighting->Diffuse = D3DXCOLOR(1,1,1,1);
	}

	void SetLight2(D3DLIGHT9* lighting)
	{

		lighting->Type = D3DLIGHT_SPOT;
		lighting->Position = D3DXVECTOR3(0,0,0);
		lighting->Direction = D3DXVECTOR3(0,1000,0);
		lighting->Specular = D3DXCOLOR(	  0.0f,	1.0f,	0.0f,0.9f);
		lighting->Ambient = D3DXCOLOR(	  0.0f,	1.0f,	0.0f,0.6f);
		lighting->Diffuse = D3DXCOLOR(	  0.0f,	0.1f,	0.0f,0.1f);
		lighting->Range = 10000000.0f;
		lighting->Theta = 0.01f;
		lighting->Phi = 0.9f;
		lighting->Attenuation0 = 0.00001f;
		lighting->Attenuation0 = 0.01f;

	}

	void SetLight3(D3DLIGHT9* lighting)
	{
		//���C�g�̎��
		lighting->Type = D3DLIGHT_DIRECTIONAL;
		//lighting->Type = D3DLIGHT_POINT;

		//���C�g�̈ʒu
		lighting->Position = D3DXVECTOR3(0,0,0);
	
		//���C�g�̌���
		lighting->Direction = D3DXVECTOR3(0,5,0);
	
		//���C�g�̂��؂����[
		lighting->Specular = D3DXCOLOR(1,1,1,1);
	
		//���C�g�̒��ڌ�
		lighting->Ambient = D3DXCOLOR(1,1,1,1);
	
		//���C�g�̊���
		lighting->Diffuse = D3DXCOLOR(1,1,1,1);
	}

	void SetLight4(D3DLIGHT9* lighting)
	{

		lighting->Type = D3DLIGHT_POINT;
		lighting->Position = D3DXVECTOR3(0,0,0);
		lighting->Direction = D3DXVECTOR3(0,1000,0);
		lighting->Specular = D3DXCOLOR(	  1.0f,	1.0f,	0.0f,0.9f);
		lighting->Ambient = D3DXCOLOR(	  1.0f,	1.0f,	0.0f,0.5f);
		lighting->Diffuse = D3DXCOLOR(	  1.0f,	1.0f,	0.0f,0.5f);
		lighting->Range = 1800.0f;
		lighting->Theta = 0.1f;
		lighting->Phi = 0.8f;
		lighting->Attenuation0 = 0.1f;
	}

	//---------------------------------------------------------------------------------
	//light.h

	//----------------------------------------------------
	//�R���X�g���N�^
	//----------------------------------------------------
	//@in : ���C�g�ԍ�
	//@in : �f�t�H���g�ݒ�ԍ�
	#pragma region ���C�g�R���X�g���N�^
	inline Light::Light(int num,int mode)	: number(num)
	{
		lighting = D3DLIGHT9();
		switch(mode)
		{
			case 1:	//�ԍ�1
				SetLight1(&this->lighting);	break;
		}
	}
	
	inline Light::~Light(){}
	inline Light::Light(){}
	#pragma endregion

	//---------------------------------------------
	//���C�g���p�C�v���C���ɃZ�b�g
	//---------------------------------------------
	void Light::Setlighting(PDirectDevice Device)
	{
		if( number <= 0)	number = 1;
		Device->SetLight(number - 1, &this->lighting);
		Device->LightEnable(number, true);
	}

	inline D3DLIGHT9* Light::GetLight(){	return &this->lighting;	}
	
	//----------------------------------------------------------------------------

	//--------------------------------------
	//�R���X�g���N�^�������ɂ܂Ƃ߂Ă���
	//--------------------------------------
	#pragma region �R���X�g���N�^
	inline Textcolor::Textcolor() : color(Vector4(255,255,255,255)){}
	
	inline Textcolor::Textcolor(PCVector4 col)
	{
		color.x = col->x;
		color.y = col->y;
		color.z = col->z;
		color.w = col->w;
	}

	Textcolor::Textcolor(float da, float dr, float dg, float db)
	{
		color.x = da;
		color.y = dr;
		color.z = dg;
		color.w = db;
	}
	
	inline Textcolor::~Textcolor(){}
	#pragma endregion
	
	//--------------------------------------
	//�R�s�[�n�������ɂ܂Ƃ߂Ă���
	//--------------------------------------
	#pragma region �R�s�[�R���X�g���N�^
	inline Textcolor& Textcolor::operator = (const Textcolor* col)
	{
		color.x = col->color.x;
		color.y = col->color.y;
		color.z = col->color.z;
		color.w = col->color.w;
		return *this;
	}
	inline Textcolor& Textcolor::operator = (const Textcolor col)
	{
		color.x = col.color.x;
		color.y = col.color.y;
		color.z = col.color.z;
		color.w = col.color.w;
		return *this;
	}

	inline Textcolor& Textcolor::operator = (Vector4 col)
	{	//�R�s�[
		color = col;
		return *this;
	}

	inline Textcolor& Textcolor::operator = (PCVector4 col)
	{	//�R�s�[
		color = col;
		return *this;
	}
	#pragma endregion

	//----------------------------------------------------------------------
	//���Z����
	//----------------------------------------------------------------------
	#pragma region ���Z
	inline Textcolor Textcolor::operator - (int a)
	{	//�Ώۂ̒l�����炷
		Textcolor col;
		col.color.x = (color.x - (float)a <= 0.0f ? 0.0f : color.x - (float)a);
		col.color.y = (color.y - (float)a <= 0.0f ? 0.0f : color.y - (float)a);
		col.color.z = (color.z - (float)a <= 0.0f ? 0.0f : color.z - (float)a);
		col.color.w = (color.w - (float)a <= 0.0f ? 0.0f : color.w - (float)a);
		return col;
	}

	inline Textcolor Textcolor::operator - (PCVector4 col)
	{	//�J���[�����炷
		Textcolor c;
		c.color.x = (color.x - col->x <= 0.0f ? 0.0f : color.x - col->x);
		c.color.y = (color.y - col->y <= 0.0f ? 0.0f : color.y - col->y);
		c.color.z = (color.z - col->z <= 0.0f ? 0.0f : color.z - col->z);
		c.color.w = (color.w - col->w <= 0.0f ? 0.0f : color.w - col->w);
		return c;
	}

	Textcolor& Textcolor::operator -= (int a)
	{
		(color.x - (float)a <= 0.0f ? color.x = 0.0f : color.x -= (float)a);
		(color.y - (float)a <= 0.0f ? color.y = 0.0f : color.y -= (float)a);
		(color.z - (float)a <= 0.0f ? color.z = 0.0f : color.z -= (float)a);
		(color.w - (float)a <= 0.0f ? color.w = 0.0f : color.w -= (float)a);
		return *this;
	}

	Textcolor& Textcolor::operator -= (PCVector4 col)
	{
		(color.x - col->x <= 0.0f ? color.x = 0.0f : color.x -= col->x);
		(color.y - col->y <= 0.0f ? color.y = 0.0f : color.y -= col->y);
		(color.z - col->z <= 0.0f ? color.z = 0.0f : color.z -= col->z);
		(color.w - col->w <= 0.0f ? color.w = 0.0f : color.w -= col->w);
		return *this;
	}
	#pragma endregion

	//----------------------------------------------------------------------
	//���Z����
	//----------------------------------------------------------------------
	#pragma region ���Z
	inline Textcolor Textcolor::operator + (int a)
	{	//�Ώۂ̒l�𑝂₷
		Textcolor col;
		col.color.x = (color.x + (float)a >= 255.0f ? 255.0f : color.x + (float)a);
		col.color.y = (color.y + (float)a >= 255.0f ? 255.0f : color.y + (float)a);
		col.color.z = (color.z + (float)a >= 255.0f ? 255.0f : color.z + (float)a);
		col.color.w = (color.w + (float)a >= 255.0f ? 255.0f : color.w + (float)a);
		return col;
	}

	inline Textcolor Textcolor::operator + (PCVector4 col)
	{	//�J���[�𑝂₷
		Textcolor c;
		c.color.x = (color.x + col->x >= 255.0f ? 255.0f : color.x + col->x);
		c.color.y = (color.y + col->y >= 255.0f ? 255.0f : color.y + col->y);
		c.color.z = (color.z + col->z >= 255.0f ? 255.0f : color.z + col->z);
		c.color.w = (color.w + col->w >= 255.0f ? 255.0f : color.w + col->w);
		return c;
	}

	inline Textcolor& Textcolor::operator += (int a)
	{	//�Ώۂ̒l�𑝂₷
		(color.x + (float)a >= 255.0f ? color.x = 255.0f : color.x += (float)a);
		(color.y + (float)a >= 255.0f ? color.y = 255.0f : color.y += (float)a);
		(color.z + (float)a >= 255.0f ? color.z = 255.0f : color.z += (float)a);
		(color.w + (float)a >= 255.0f ? color.w = 255.0f : color.w += (float)a);
		return *this;
	}

	inline Textcolor& Textcolor::operator += (PCVector4 col)
	{	//�J���[�𑝂₷
		(color.x + col->x >= 255.0f ? color.x = 255.0f : color.x += col->x);
		(color.y + col->y >= 255.0f ? color.y = 255.0f : color.y += col->y);
		(color.z + col->z >= 255.0f ? color.z = 255.0f : color.z += col->z);
		(color.w + col->w >= 255.0f ? color.w = 255.0f : color.w += col->w);
		return *this;
	}
	#pragma endregion

	//----------------------------------------------------------------------
	//���Z����
	//----------------------------------------------------------------------
	inline Textcolor& Textcolor::operator -- (int a)
	{	//1���炷
		(color.x - 1.0f <= 0.0f ? color.x = 0.0f : color.x --);
		(color.y - 1.0f <= 0.0f ? color.y = 0.0f : color.y --);
		(color.z - 1.0f <= 0.0f ? color.z = 0.0f : color.z --);
		(color.w - 1.0f <= 0.0f ? color.w = 0.0f : color.w --);
		return *this;
	}

	//----------------------------------------------------------------------
	//���Z����
	//----------------------------------------------------------------------
	inline Textcolor& Textcolor::operator ++ (int a)
	{	//1���₷
		(color.x + 1.0f >= 255.0f ? color.x = 255.0f : color.x ++);
		(color.y + 1.0f >= 255.0f ? color.y = 255.0f : color.y ++);
		(color.z + 1.0f >= 255.0f ? color.z = 255.0f : color.z ++);
		(color.w + 1.0f >= 255.0f ? color.w = 255.0f : color.w ++);
		return *this;
	}

	//----------------------------------------------------------------------
	//��������
	//----------------------------------------------------------------------
	inline void Textcolor::operator * (PCVector4 col)
	{
		float alpha = col->x / 255;
		color.w = col->w * alpha + color.w * (1.0f - alpha);
		color.y = col->y * alpha + color.y * (1.0f - alpha);
		color.z = col->z * alpha + color.z * (1.0f - alpha);
	}

	//----------------------------------------------------------------------
	//���Z����
	//----------------------------------------------------------------------
	inline void Textcolor::operator / (PCVector4 col)
	{
		float alpha = col->x / 255;
		color.w = col->w * alpha - color.w * (1.0f - alpha);
		color.y = col->y * alpha - color.y * (1.0f - alpha);
		color.z = col->z * alpha - color.z * (1.0f - alpha);
	}

	//----------------------------------------------------------------------
	//�J���[�̃Z�b�e�B���O
	//----------------------------------------------------------------------
	#pragma region Setter
	inline void Textcolor::SetColor(int a,int r,int g,int b)
	{
		color = Vector4((float)a, (float)r, (float)g, (float)b);
	}

	inline void Textcolor::SetMaxColor()
	{
		color = Vector4( MAXCOLOR, MAXCOLOR, MAXCOLOR, MAXCOLOR);
	}

	inline void Textcolor::SetMinColor()
	{
		color = Vector4( 0,0,0,0 );
	}

	inline void Textcolor::SetColor(PCVector4 col)
	{
		color = (col);
	}

	inline void Textcolor::SetAlpha(int a)
	{
		color.x = (FLOAT)a;
	}
	#pragma endregion

	//----------------------------------------------------------------------
	//�J���[�̎擾
	//----------------------------------------------------------------------
	#pragma region Getter
	inline float Textcolor::GetColor(int mode)
	{
		switch(mode)
		{
			case 1:	return color.y;
			case 2:	return color.z;
			case 3:	return color.w;
		}
		return 0;
	}

	inline Vector4 Textcolor::GetColor()
	{
		return this->color;
	}

	inline float Textcolor::GetAlpha()
	{
		return color.x;
	}
	#pragma endregion

	//----------------------------------------------------------------------
	//�J���[�̃t�F�[�h�C��
	//----------------------------------------------------------------------
	#pragma region �t�F�[�h�C��
	bool Textcolor::FadeIn(float al)
	{
		color.x += al;
		if( color.x > 255.0f || color.x > target.x )
		{
			color.x = 255.0f;
			return true;
		}
		else
			return false;
	}

	bool Textcolor::FadeIn(PCVector4 col)
	{
		color += (*col);
		if( color.x == 255.0f && color.y == 255.0f &&
				color.z == 255.0f && color.w == 255.0f )
			return true;

		if( color.x >= target.x && color.y >= target.y &&
				color.z >= target.z && color.w >= target.w )
		{
			color = target;
			return true;
		}
		return false;
	}
	#pragma endregion

	//----------------------------------------------------------------------
	//�J���[�̃t�F�[�h�A�E�g
	//----------------------------------------------------------------------
	#pragma region �t�F�[�h�A�E�g
	bool Textcolor::FadeOut(float al)
	{
		color.x -= al;
		if( color.x < 0.0f )
		{
			color.x = 0.0f;
			return true;
		}
		else
			return false;
	}

	bool Textcolor::FadeOut(PCVector4 col)
	{
		color -= (*col);
		if(color.x <= 0.0f && color.y <= 0.0f &&
			color.z <= 0.0f && color.w <= 0.0f)
		{
			this->SetMinColor();
			return true;
		}
		else
			return false;
	}
	#pragma endregion
	
	//----------------------------------------------------------------------
	//�J���[�̃t�F�[�h���邽�߂̃Z�b�e�B���O
	//----------------------------------------------------------------------
	#pragma region SettingFade
	void Textcolor::SettingFadeAlpha()
	{
		target = color;
		color.x = 0.0f;
	}
	
	void Textcolor::SettingTextcolor()
	{
		target = color;
		this->SetMinColor();
	}
	#pragma endregion

}