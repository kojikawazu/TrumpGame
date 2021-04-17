#pragma once
//----------------------------------------------------
//
//�QD�摜�̕`��̃��\�b�h��u���Ă܂���
//
//----------------------------------------------------
#include <ResourceDrawer.h>

namespace NanairoLib
{
	#pragma region �f�t�H���g�|���S�����
	//-------------------------------------------------------------------
	//�f�t�H���g�|�����
	//-------------------------------------------------------------------
	const static ArtisanVT_2D polgon[4] = 
	{
		{     0.5f,-0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f}, //�E��10
		{     0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f}, //�E��11
		{    -0.5f,-0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f}, //����00
		{    -0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f}  //����01
	};

	const static ArtisanVT_2D polgonLF[4] = 
	{
		{     1.0f,-0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f}, //�E��10
		{     0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f}, //�E��11
		{    -0.5f,-0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f}, //����00
		{    -0.5f, 0.5f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f}  //����01
	};

	//-------------------------------------------------------------------
	//3D���[���h��ɏo�������|�����
	//-------------------------------------------------------------------
	const static ArtisanVT_3D polgon3D[4] = 
	{
		{     0.5f,-0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f}, //�E��
		{     0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f}, //�E��
		{    -0.5f,-0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f}, //����
		{    -0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f}  //����
	};
	#pragma endregion
	
	//--------------------------------------------------------------------------------------------------
	//���������l�ɕϊ�
	//--------------------------------------------------------------------------------------------------
	//@inout : ������
	//@inout : ��������
	//@inout : ���ԍ�
	//@inout : �c�ԍ�
	//@in : ��
	//@in  ����
	//@in : ��������
	//@in : ����������
	void Division(float* divW,float* divH,int* sumW,int* sumH,int num,int wnum,int hnum,int wh,int hei)
	{
		(*divW) = (float)(wh / wnum);
		(*divH) = (float)(hei / hnum);

		if(num == 0)	(*sumW) = (*sumH) = 0;
		else
		{
			(*sumW) = (num % wnum);
			(*sumH) = (num / wnum);
		}
	}
	
	//----------------------------------------------------------------------------------------
	//UV�ݒ�
	//----------------------------------------------------------------------------------------
	//@inout : ���_���
	//@in : ������
	//@in : ��������
	//@in : ���蓖�ĉ��ԍ�
	//@in : ���蓖�ďc�ԍ�
	//@in : ��
	//@in : ����
	void DefaultSetUV(PArtisanVT_2D vertex,float divW,float divH,int sx,int sy,int wid,int hei)
	{
		vertex[0].u = ((divW * sx) + divW) / wid;
		vertex[0].v = (divH * sy) / hei;

		vertex[1].u = ((divW * sx) + divW) / wid;
		vertex[1].v = ((divH * sy) + divH) / hei;
		
		vertex[2].u = (divW * sx) / wid;
		vertex[2].v = (divH * sy) / hei;

		vertex[3].u = (divW * sx) / wid;
		vertex[3].v = ((divH * sy) + divH) / hei;
	}
	
	//----------------------------------------------------------------------------------------
	//UV�ݒ�(3D�o�[�W����)
	//----------------------------------------------------------------------------------------
	//@inout : ���_���
	//@in : ������
	//@in : ��������
	//@in : ���蓖�ĉ��ԍ�
	//@in : ���蓖�ďc�ԍ�
	//@in : ��
	//@in : ����
	void DefaultSetUV_3D(PArtisanVT_3D vertex,float divW,float divH,int sx,int sy,int wid,int hei)
	{
		vertex[0].u = ((divW * sx) + divW) / wid;
		vertex[0].v = (divH * sy) / hei;

		vertex[1].u = ((divW * sx) + divW) / wid;
		vertex[1].v = ((divH * sy) + divH) / hei;
		
		vertex[2].u = (divW * sx) / wid;
		vertex[2].v = (divH * sy) / hei;

		vertex[3].u = (divW * sx) / wid;
		vertex[3].v = ((divH * sy) + divH) / hei;
	}
	
	//-----------------------------------------------
	//�f�t�H���g�J���[UV�ݒ�
	//-----------------------------------------------
	//@inout : ���_���
	//@in : �J���[�A���t�@
	void DefaultColUV(PArtisanVT_2D vertex,UINT alpha)
	{
		for(int i=0; i<4; i++)
		{
			vertex[i].dwColor = alpha;
			vertex[i].u = polgon[i].u;
			vertex[i].v = polgon[i].v;
		}
	}

	//-----------------------------------------------
	//�f�t�H���g�J���[UV�ݒ�
	//-----------------------------------------------
	//@inout : ���_���
	//@in : �J���[�A���t�@
	void DefaultColUV_3D(PArtisanVT_3D vertex,UINT alpha)
	{
		for(int i=0; i<4; i++)
		{
			vertex[i].dwColor = alpha;
			vertex[i].u = polgon3D[i].u;
			vertex[i].v = polgon3D[i].v;
		}
	}

	//-----------------------------------------------------------------------------
	//���_���̒�����
	//-----------------------------------------------------------------------------
	//@inout : ���_���
	//@in : ����X���W
	//@in : ����Y���W
	//@in : �E��X���W
	//@in : �E��Y���W
	//@in : ����X���W
	//@in : ����Y���W
	//@in : �E��X���W
	//@in : �E��Y���W
	void DirectSetUV(PArtisanVT_2D vx, float lupX,float lupY,float rupX,float rupY,
						float lbotX,float lbotY,float rbotX,float rbotY)
	{
		::memcpy( vx, polgon, sizeof( NanairoLib::ArtisanVT_2D) * 4);
		vx[0].x = rupX;
		vx[0].y = rupY;
		vx[1].x = rbotX;
		vx[1].y = rbotY;
		vx[2].x = lupX;
		vx[2].y = lupY;
		vx[3].x = lbotX;
		vx[3].y = lbotY;
	}

	//private---------------------------------------------------------------------------
	
	//-------------------------------------------------------
	//���ʂɒ��S���Z�b�g���ĕϊ��s��ŕϊ��A�FUV�̓f�t�H���g	
	//-------------------------------------------------------
	#pragma region ���ʒ��_�ϊ�
	void Artisan::TransNormal()
	{
		D3DXVECTOR3 po1,po2;
		po1.z = 0.0f;
		for(int i=0; i<4; i++)
		{
			po1.x = polgon[i].x;	po1.y = polgon[i].y;	
			D3DXVec3TransformCoord(&po2, &po1, &trans);
			vertex[i].x = po2.x;	vertex[i].y = po2.y;
		}
		DefaultColUV(&this->vertex[0], this->alpha);
	}

	void Artisan::TransWorld()
	{
		D3DXVECTOR3 po1, po2;
		for(int i=0; i<4; i++)
		{
			po1.x = polgon3D[i].x;	po1.y = polgon3D[i].y; po1.z = polgon3D[i].z;
			D3DXVec3TransformCoord(&po2, &po1, &trans);
			vertex3D[i].x = po2.x; vertex3D[i].y = po2.y; vertex3D[i].z = po2.z;
			
			vertex3D[i].norX = polgon3D[i].norX;
			vertex3D[i].norY = polgon3D[i].norY;
			vertex3D[i].norZ = polgon3D[i].norZ;
		}
		DefaultColUV_3D( &vertex3D[0], this->alpha );
	}
	#pragma endregion

	//----------------------------------------------------------------------------------------
	//���_���W�𒼐ڃZ�b�g���āA�FUV�̓f�t�H���g
	//----------------------------------------------------------------------------------------
	//@in : ������W
	//@in : �E����W
	//@in : �������W
	//@in : �E�����W
	void Artisan::TransVertex(RCVector2 lup,RCVector2 rup,RCVector2 lbot,RCVector2 rbot)
	{
		::D3DXMatrixIdentity(&trans);

		this->vertex[0].x = rup.x;		this->vertex[0].y = rup.y;		this->vertex[0].z = 0.0f;
		this->vertex[1].x = rbot.x;	this->vertex[1].y = rbot.y;	this->vertex[1].z = 0.0f;
		this->vertex[2].x = lup.x;		this->vertex[2].y = lup.y;		this->vertex[2].z = 0.0f;
		this->vertex[3].x = lbot.x;	this->vertex[3].y = lbot.y;	this->vertex[3].z = 0.0f;

		DefaultColUV(&this->vertex[0], this->alpha);
	}
	
	//------------------------------------------------------------------------------------
	//�O�p�`�Ƃ��Ē��_���W�𒼐ڃZ�b�g���āA�FUV�̓f�t�H���g�i��ʃp���[��������邽�ߗp�j
	//------------------------------------------------------------------------------------
	//@in : ������W
	//@in : �E����W
	//@in : �c��O�p�`���W
	void Artisan::TransTriangle(RCVector2 lup,RCVector2 rup,RCVector2 rbot)
	{
		::D3DXMatrixIdentity(&trans);

		this->vertex[0].x = rup.x;		this->vertex[0].y = rup.y;		this->vertex[0].z = 0.0f;
		this->vertex[1].x = rbot.x;	this->vertex[1].y = rbot.y;	this->vertex[1].z = 0.0f;
		this->vertex[2].x = lup.x;		this->vertex[2].y = lup.y;		this->vertex[2].z = 0.0f;

		DefaultColUV(&this->vertex[0], this->alpha);
	}
	
	//------------------------------------------------------------------------------------
	//�����摜��UV���蓖�āiTEXTURE�\���̂ɕ��A�����A���������A���������������Ă���̂Łj
	//���蓖�Ă����ԍ����w�肷��΂���UV����������I
	//�������������ł͍ő�A�j���ԍ������Ă����O�����A����͊O�ł���ׂ��I
	//���R�͓�d����h�~
	//------------------------------------------------------------------------------------	
	
	//---------------------------------------------------
	//���ʒ��_�ϊ�
	//---------------------------------------------------
	//@in : ���蓖�Ĕԍ�
	//@in : �e�N�X�`�����
	void Artisan::TransDivisionPoint(int num,PCTEXTUREH text)
	{
		float divW,divH;
		int sx,sy;

		Division(&divW, &divH, &sx, &sy, num, text->sumX, text->sumY, text->width, text->height);
		DefaultSetUV(&this->vertex[0], divW, divH, sx, sy, text->width, text->height);
	}
	
	//----------------------------------------------------------------------
	//�����ŕ��������A���������������߂āA���蓖�Ă����ԍ����w�肷��
	//�������ł��ő�A�j���ԍ��̔���͂����I�@�O�Ŕ��f�I
	//----------------------------------------------------------------------
	//@in : ���蓖�Ĕԍ�
	//@in : ���ԍ����v
	//@in : �c�ԍ����v
	//@in : �e�N�X�`���f�[�^�N���X
	void Artisan::TransModi(int num,int wnum,int hnum,PCTEXTUREH  text)
	{
		float divW,divH;
		int sx,sy;

		Division(&divW, &divH, &sx, &sy, num, wnum, hnum, text->width, text->height);
		DefaultSetUV(&this->vertex[0], divW, divH, sx, sy, text->width, text->height);
	}
	
	//-------------------------------------------------------------------------------------------
	//�O�p�`�Ƃ���UV��ϊ�����B
	//���A�����A���������A�����������A�j���ԍ��������Ō��߂�
	//mode�́��n�����n��
	//-------------------------------------------------------------------------------------------
	//@in : ���蓖�Ĕԍ�
	//@in : ���ԍ����v
	//@in : �c�ԍ����v
	//@in : ��
	//@in : ����
	//@in : ����mode�Q��
	void Artisan::TransTriangleModi(int num,int wnum,int hnum,int width,int height,bool IsUp)
	{
		float divW,divH;
		int sx,sy;

		Division(&divW, &divH, &sx, &sy, num, wnum, hnum, width, height);

		if(!IsUp)
		{
			vertex[0].u = ((divW * sx) + divW) / width;
			vertex[0].v = (divH * sy) / height;

			vertex[1].u = ((divW * sx) + divW * 0.5f) / width;
			vertex[1].v = ((divH * sy) + divH) / height;
		
			vertex[2].u = (divW * sx) / width;
			vertex[2].v = (divH * sy) / height;
		}
		else
		{
			vertex[0].u = (divW * sx) / width;
			vertex[0].v = ((divH * sy) + divH) / height;

			vertex[1].u = ((divW * sx) + divW * 0.5f) / width;
			vertex[1].v = ((divH * sy)) / height;
		
			vertex[2].u = ((divW * sx) + divW) / width;
			vertex[2].v = ((divH * sy) + divH) / height;
		}
	}
	
	//-------------------------------------------------------------
	//�X�N���[���̕����ϊ�
	//(��)2�l�v���C�̎��ɉ�ʂ����ɂQ�������
	//-------------------------------------------------------------
	//@in : �X�N���[���̐�
	//@in : �`�悵�����X�N���[���ԍ�
	void Artisan::TransScreenDivision(int screenSum, int screenNum)
	{
		switch( screenSum )
		{
			case 1:
				DirectSetUV( &vertex[0], 0,0, SCRW, 0, 0, SCRH, SCRW, SCRH);
				break;
			case 2:
				( screenNum == 0 ? DirectSetUV( &vertex[0], 0,0, SCRW_PERCENT(0.5f),0, 0,SCRH, SCRW_PERCENT(0.5f),SCRH) : 
									DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f),0, SCRW,0, SCRW_PERCENT(0.5f),SCRH, SCRW, SCRH) );
				break;
			case 3:
				switch( screenNum )
				{
					case 1:
						DirectSetUV( &vertex[0], 0,0, SCRW,0, 0,SCRH_PERCENT(0.5f), SCRW,SCRH_PERCENT(0.5f) );
						break;
					case 2:
						DirectSetUV( &vertex[0], 0,SCRH_PERCENT(0.5f), SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f), 0, SCRH, SCRW_PERCENT(0.5f), SCRH);
						break;
					case 3:
						DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f), SCRW,SCRH_PERCENT(0.5f), SCRW_PERCENT(0.5f), SCRH, SCRW, SCRH);
						break;
				}
				break;
			case 4:
				switch( screenNum )
				{
					case 1:
						DirectSetUV( &vertex[0], 0,0, SCRW_PERCENT(0.5f),0, 0,SCRH_PERCENT(0.5f), SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f));
						break;
					case 2:
						DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f),0, SCRW,0, SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f), SCRW,SCRH_PERCENT(0.5f));
						break;
					case 3:
						DirectSetUV( &vertex[0], 0,SCRH_PERCENT(0.5f),SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f),0,SCRH,SCRW_PERCENT(0.5f),SCRH);
						break;
					case 4:
						DirectSetUV( &vertex[0], SCRW_PERCENT(0.5f),SCRH_PERCENT(0.5f),SCRW,SCRH_PERCENT(0.5f),SCRW_PERCENT(0.5f),SCRH,SCRW,SCRH);
						break;
				}
				break;
		}
	}

	//public----------------------------------------------------------------------------

	#pragma region �R���X�g���N�^
	inline Artisan::Artisan() : alpha(0) , alphaFlag(false), vertexBuffer(NULL), shader( NULL ), Device(NULL)
	{
		memcpy( &vertex[0], &polgon[0], sizeof(ArtisanVT_2D) * 4 );
		memcpy( &vertex3D[0], &polgon3D[0], sizeof(ArtisanVT_3D) * 4 );
	}

	inline Artisan::~Artisan()
	{
		ES_SAFE_RELEASE( this->vertexBuffer );	
		ES_SAFE_DELETE( this->shader );
	}

	inline void Artisan::InitShader(LPCSTR pass)
	{
		if(Device == NULL)	return ;
		this->shader = new Shader();
		this->shader->InitShader( Device, pass );
		if( !this->shader->doingShader )
			ES_SAFE_DELETE( shader );
	}

	void Artisan::SetDrawShader(PTexture text)
	{
		Device->SetFVF(FVF_Artisan);
#ifdef SHADER_DRAWER
		if( !CHECK_NULL(this->shader) )
		{
			this->shader->Effect->SetMatrix( SHADER_MATRIX_WORLD_, &D3DXMATRIX() );
			this->shader->Effect->SetTexture( SHADER_TEX1_, text );
			this->shader->Effect->SetBool( SHADER_TEX_ABLE_, ( text != NULL ) );
			this->shader->Effect->CommitChanges();
		}
		else
			Device->SetTexture(0, text);
#else
		Device->SetTexture(0, text);					//�e�N�X�`��
#endif
	}

	void Artisan::SetShader(Shader* in)
	{
		this->shader = in;
	}

	Shader* Artisan::GetShader() const
	{
		return this->shader;
	}
	#pragma endregion

	void Artisan::SetScreenTrans(RenderScreen* sc)
	{
		this->TransScreenDivision( sc->screenSum, sc->screenNum );
		this->SetColor( &sc->color.color );
	}

	//----------------------------------------------------------------
	//���_�o�b�t�@���i�[
	//----------------------------------------------------------------
	bool Artisan::SetVertexBuffer()
	{
		if(Device == NULL)
			return false;

		//�|���𐧍�
		if(FAILED(Device->CreateVertexBuffer(
					sizeof(ArtisanVT_2D) * 4,	D3DUSAGE_WRITEONLY,
					FVF_Artisan,				D3DPOOL_MANAGED,
					&this->vertexBuffer,	NULL)))
		{
					return false;
		}

		void *pData;
		if(SUCCEEDED(this->vertexBuffer->Lock(0, sizeof(ArtisanVT_2D) * 4,
										(void**)&pData,0)))
		{
			memcpy(pData, vertex, sizeof(ArtisanVT_2D) * 4);
			this->vertexBuffer->Unlock();
			return true;
		}
		return false;
	}
	
	//---------------------------------------------
	//�v���W�F�N�V�����̐ݒ�
	//---------------------------------------------
	//@in : �v���W�F�N�V�����s��
	inline void Artisan::SetProjection(PCMATRIX p)
	{	
		this->proj = (*p);	

#ifdef SHADER_DRAWER
		if( this->shader != NULL)
			this->shader->Effect->SetMatrix( SHADER_MATRIX_PROJ_, p );
#endif
	}

	//--------------------------------------------------------------------------------------------------------------------
	// �s��ɕϊ�
	//--------------------------------------------------------------------------------------------------------------------
	//@in : �ϊ��ʒu
	//@in : �ϊ��g��k��
	//@in : �ϊ��p�x
	//@in : �e�N�X�`���f�[�^�N���X
	//@in : �J���[���
	//@in : �X�P�[�����[�h
	D3DXMATRIX Artisan::Transform(RCVector2 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,int mode)
	{
		D3DXMATRIX p,r,ps;
		::D3DXMatrixTranslation(&p, pos.x, pos.y, 0.0f);	//�ʒu�̍s��
		::D3DXMatrixRotationZ(&r, angle);					//��]�̍s��
		switch(mode)	//�g��̍s��
		{	
			case GRAPH_SCALE:	//�f�t�H���g�̉摜�ϊ�
				::D3DXMatrixScaling(&ps, scale.x * (float)text->width, scale.y * (float)text->height, 1.0f);
				break;
			case DIV_SCALE:	//�A�j���[�V�����摜�������p�ϊ�
				::D3DXMatrixScaling(&ps, scale.x * (float)(text->width / text->sumX), scale.y * (float)(text->height / text->sumY), 1.0f);
				break;
			default://�����
				::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		}

		this->SetColor(color);
		return this->trans = ((ps * r *  p));
	}

	//--------------------------------------------------------------------------------------------------------------------
	// �s��ɕϊ�
	//--------------------------------------------------------------------------------------------------------------------
	//@in : �ϊ��ʒu
	//@in : �ϊ��g��k��
	//@in : �ϊ��p�x
	D3DXMATRIX Artisan::Transform(RCVector2 pos, RCVector2 scale, float angle)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos.x, pos.y, 0.0f);	//�ʒu�̍s��
		::D3DXMatrixRotationZ(&r, angle);					//��]�̍s��
		::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		
		return this->trans = ((ps * r *  p));
	}

	//--------------------------------------------------------------------------------------------------------------------
	// �s��ɕϊ�
	//--------------------------------------------------------------------------------------------------------------------
	//@in : �ϊ��ʒu
	//@in : �ϊ��g��k��
	//@in : �ϊ��p�x
	//@in : �t�H���g�f�[�^�N���X
	//@in : �J���[���
	//@in : �X�P�[�����[�h
	D3DXMATRIX Artisan::TransformW(RCVector2 pos, RCVector2 scale, float angle,MyFont* text,PCVector4 color,int mode)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos.x, pos.y, 0.0f);	//�ʒu�̍s��
		::D3DXMatrixRotationZ(&r, angle);					//��]�̍s��
		::D3DXMatrixScaling(&ps, scale.x * (float)(text->GetFont()->fontW), scale.y * (float)(text->GetFont()->fontH), 1.0f);

		this->SetColor(color);
		return this->trans = ((ps * r * p));
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//�R�c��ԏ�ɕ\��
	//---------------------------------------------------------------------------------------------------------------------------
	//@in : �ϊ��ʒu
	//@in : �ϊ��g��k��
	//@in : �ϊ��p�x
	//@in : �e�N�X�`���f�[�^�N���X
	//@in : �J���[���
	//@in : �X�P�[�����[�h
	D3DXMATRIX Artisan::Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCTEXTUREH text,PCVector4 color,int mode)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos->x, pos->y, pos->z);	//�ʒu�̍s��
		::D3DXMatrixRotationZ(&r, angle->z);					//��]�̍s��
		switch(mode)
		{	//�g��̍s��
			case GRAPH_SCALE:	//�f�t�H���g�̉摜�ϊ�
				::D3DXMatrixScaling(&ps, scale.x * (float)text->width, scale.y * (float)text->height, 1.0f);
				break;
			case DIV_SCALE:	//�A�j���[�V�����摜�������p�ϊ�
				::D3DXMatrixScaling(&ps, scale.x * (float)(text->width / text->sumX), scale.y * (float)(text->height / text->sumY), 1.0f);
				break;
			default://�����
				::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		}

		this->SetColor(color);
		return this->trans = ((ps * r *  p));
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//�R�c��ԏ�ɕ\��(�r���{�[�h)
	//---------------------------------------------------------------------------------------------------------------------------
	//@in : �ϊ��ʒu
	//@in : �ϊ��g��k��
	//@in : �ϊ��p�x
	//@in : �e�N�X�`���f�[�^�N���X
	//@in : �J���[���
	//@in : �r���{�[�h�s��
	//@in : �X�P�[�����[�h
	D3DXMATRIX Artisan::Transform3D_ofBillboard(PCVector3 pos, RCVector2 scale, float angle,PCTEXTUREH text,PCVector4 color,PCMATRIX board,int mode)
	{
		D3DXMATRIX p,r,ps;
		
		::D3DXMatrixTranslation(&p, pos->x, pos->y, pos->z);	//�ʒu�̍s��
		::D3DXMatrixRotationZ(&r, angle);					//��]�̍s��
		switch(mode)
		{	//�g��̍s��
			case GRAPH_SCALE:	//�f�t�H���g�̉摜�ϊ�
				::D3DXMatrixScaling(&ps, scale.x * (float)text->width, scale.y * (float)text->height, 1.0f);
				break;
			case DIV_SCALE:	//�A�j���[�V�����摜�������p�ϊ�
				::D3DXMatrixScaling(&ps, scale.x * (float)(text->width / text->sumX), scale.y * (float)(text->height / text->sumY), 1.0f);
				break;
			default://�����
				::D3DXMatrixScaling(&ps, scale.x, scale.y, 1.0f);
		}

		this->SetColor(color);
		return this->trans = (( ps * r * (*board) * p));
	}

	//-----------------------------------------------
	//�J���[���̃Z�b�g
	//-----------------------------------------------
	//@in : �J���[���
	void Artisan::SetColor(PCVector4 color)
	{	//�J���[�����Z�b�g�������Ƃ��ɂ���I
		this->alpha = ((((int)color->x) & 0xff) << 24) + ((((int)color->y) & 0xff) << 16) + 
				((((int)color->z) & 0xff) << 8) + ((((int)color->w) & 0xff)); 
		this->SetShaderColor( color );
	}

	//-----------------------------------------------
	//�V�F�[�_�[��ŃJ���[���̃Z�b�g
	//-----------------------------------------------
	//@in : �J���[���
	void Artisan::SetShaderColor(PCVector4 color)
	{
		if( this->shader != NULL )
		{
#ifdef SHADER_DRAWER
			D3DMATERIAL9 mt = {};
			mt.Ambient.a = ( color->x <= 1.0f ? 0.0f : (int)(color->x) / 255);
			mt.Ambient.r = ( color->y <= 1.0f ? 0.0f : (int)(color->y) / 255);
			mt.Ambient.g = ( color->z <= 1.0f ? 0.0f : (int)(color->z) / 255);
			mt.Ambient.b = ( color->w <= 1.0f ? 0.0f : (int)(color->w) / 255);
			this->shader->Effect->SetFloatArray( SHADER_MATERIAL_, (float*)(&mt), 17 );
#endif
		}
	}

	//-----------------------------------------------
	//8bit(rgba)�̃J���[���ɕϊ����Đݒ�
	//-----------------------------------------------
	//@in : �J���[���
	void Change8BitColor(ArtisanVT_2D* vertex, PCVector4 col)
	{
		UINT al = ((((int)col->x) & 0xff) << 24) + ((((int)col->y) & 0xff) << 16) + 
				((((int)col->z) & 0xff) << 8) + ((((int)col->w) & 0xff));
		vertex->dwColor = al;
	}

	//-----------------------------------------------
	//8bit(rgba)�̃J���[���ɕϊ����Đݒ�
	//-----------------------------------------------
	//@in : ����J���[���
	//@in : �E��J���[���
	//@in : �����J���[���
	//@in : �E���J���[���
	void Artisan::Set8BitColor(PCVector4 lup, PCVector4 rup, PCVector4 lbot, PCVector4 rbot)
	{
		Change8BitColor( &this->vertex[0], rup );
		Change8BitColor( &this->vertex[1], rbot );
		Change8BitColor( &this->vertex[2], lup );
		Change8BitColor( &this->vertex[3], lbot );
	}
	
	//-------------------------------------------------------------------------------------------------

	//------------------------------------------------
	//DirectX�p�e�N�X�`���𒼐ݒ肵�ĕ`��
	//------------------------------------------------
	//@in : DirectX�p�e�N�X�`��
	void Artisan::DrawVertexBuffer(PTexture text)
	{
		if( Device == NULL || CHECK_NULL(text) ) return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text );

		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//�`��
	}

	//--------------------------------------------------------
	//�ݒ肵�I������ԂŌ�͉摜��`�悷�邾���̎��͂���I
	//--------------------------------------------------------
	//@in : �e�N�X�`�����
	void Artisan::DrawVertexBuffer(PCTEXTUREH text)
	{
		if( Device == NULL || CHECK_NULL(text->graph) ) return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//�`��
	}

	//--------------------------------------------------------
	//�t�H���g���̕`��
	//--------------------------------------------------------
	//@in : �t�H���g�e�N�X�`�����
	void Artisan::DrawVertexBuffer(PMyFont text)
	{
		if(Device == NULL || CHECK_NULL(text))	return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);	//�QD�J�X�^���Ƀ`�F���W
		this->SetDrawShader( text->GetFont()->fontText );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//�`��
	}

	//--------------------------------------------------------
	//�X�N���[���S�̂̕`��
	//--------------------------------------------------------
	void Artisan::DrawVertexWall()
	{
		if( Device == NULL ) return ;
		this->TransNormal();
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( NULL );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//�`��
	}

	//--------------------------------------------------------
	//�X�N���[���S�̂̕`��
	//--------------------------------------------------------
	//@in : �e�N�X�`�����
	void Artisan::DrawScreen(PTexture text)
	{
		if( Device == NULL || CHECK_NULL(text) ) return ;
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));		//�`��
	}

	//--------------------------------------------------------
	//3D��ԏ�̕`��
	//--------------------------------------------------------
	void Artisan::DrawVertexGraph_3D(PCTEXTUREH text)
	{
		if(Device == NULL || CHECK_NULL(text))	return ;
		this->TransWorld();
		Device->SetFVF( FVF_Artisan3 );
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, this->vertex3D, sizeof(ArtisanVT_3D) );
	}
	
	//--------------------------------------------------------------------------
	//�ݒ肵�I������ԂŃA�j���摜�̔ԍ���ݒ肷�邾���ŃA�j���[�V�����\�ɁI
	//�����`��
	//--------------------------------------------------------------------------
	//@in : �e�N�X�`�����
	//@in : ���蓖�Ĕԍ�
	void Artisan::DrawVertexBufferIndex(PCTEXTUREH text, int number)
	{
		if( Device == NULL || CHECK_NULL(text) || !text->division)	return ;	
		this->TransNormal();
		this->TransDivisionPoint(number, text);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));
	}

	//---------------------------------------------------------------------------------
	//�����Œ��_���W��ݒ肵�āA�����������ݒ�A�����ăA�j���[�V�����ԍ������ĕ`��
	//���ژM�肽���p
	//---------------------------------------------------------------------------------
	//@in : �e�N�X�`�����
	//@in : ������W
	//@in : �E����W
	//@in : �������W
	//@in : �E�����W
	void Artisan::DrawVertexBufferIndexModi(PCTEXTUREH text,RCVector2 p1,
											RCVector2 p2,RCVector2 p3,RCVector2 p4,
												int number, int wnum, int hnum)
	{
		if(Device == NULL || CHECK_NULL(text) || wnum == 0 || hnum == 0)	return ;
		this->TransVertex(p2,p1,p3,p4);
		this->TransModi(number, wnum, hnum, text);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));
	}

	//-------------------------------------------------------------------
	//�����Œ��_���W��ݒ肵�āA�����ăA�j���[�V�����ԍ������ĕ`��
	//�A�j���[�V�������̓f�t�H���g�ɂȂ�܂�
	//-------------------------------------------------------------------
	//@in : ������W
	//@in : �E����W
	//@in : �������W
	//@in : �E�����W
	//@in : ���蓖�Ĕԍ�
	//@in : �e�N�X�`�����
	void Artisan::DrawRectDepGraph(RCVector2 lup,RCVector2 rup,RCVector2 lbot,
								RCVector2 rbot,int num,PCTEXTUREH  text)
	{
		if(Device == NULL || CHECK_NULL(text) || !text->division)	return ;	
		this->TransVertex(lup,rup,lbot,rbot);
		this->TransDivisionPoint(num, text);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text->graph );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(ArtisanVT_2D));
	}

	//-------------------------------------------------------------------------------------------------------------------------
	//���_���W�A�ő啝�����A�����������A���蓖�Ĕԍ���
	//��ʂ����邽�߂����ɂ��郁�\�b�h
	//-------------------------------------------------------------------------------------------------------------------------
	//@in : �e�N�X�`�����
	//@in : ������W
	//@in : �E����W
	//@in : �������W
	//@in : ���蓖�Ĕԍ�
	//@in : ���������v��
	//@in : �����c���v��
	//@in : ��
	//@in : ����
	//@in : ���[�h
	void Artisan::DrawIndexGlassHopper(PTexture text, RCVector2 p1,
										RCVector2 p2,RCVector2 p3,int number, int wnum, int hnum,int width,int height,bool IsUp)
	{
		if(Device == NULL || CHECK_NULL(text) || wnum == 0 || hnum == 0)	return ;
		this->TransTriangle(p2,p1,p3);
		this->TransTriangleModi(number, wnum, hnum, width, height,IsUp);
		Device->SetFVF(FVF_Artisan);
		this->SetDrawShader( text );
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, vertex, sizeof(ArtisanVT_2D));
	 }
	
	//D3DXMATRIX mat1,mat2,mat3;
	//	Device->GetTransform(D3DTS_VIEW, &mat1);
	//	Device->GetTransform(D3DTS_PROJECTION, &mat2);
	//	D3DXMatrixInverse(&mat3, NULL, &(mat1 * mat2));
	//	
	//	//::D3DXMatrixIdentity(&mat2);
	//	//mat2 = mat1 * mat2;
	//	//D3DXMatrixInverse(&mat2, NULL, &mat1);
	//	//Device->SetTransform(D3DTS_VIEW, &mat3);
	//	
	//	evice->SetStreamSource(0,this->vertexBuffer, 0, sizeof(ArtisanVT_2D));
	//	Device->SetFVF(FVF_Artisan);
	//	Device->SetTransform(D3DTS_WORLD, &(this->trans));			//�ϊ��s��
	//	Device->SetTexture(0, text.graph);					//�e�N�X�`��
	//	//Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//Device->SetTransform(D3DTS_VIEW, &mat3);

	//------------------------------------------------
	//�A���t�@���[�h�̃Z�b�e�B���O
	//------------------------------------------------
	void Artisan::SetAlphaMode(COLOR_BLEND_NUM mode,DWORD dwal)
	{
		if( Device == NULL )	return ;
		switch(mode)
		{
			case 1:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:
			case 9:	case 10: case 11: case 12:
				Device->SetRenderState( D3DRS_ZENABLE, TRUE );						//z�e�X�g�L��
				Device->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				//�A���t�@�e�X�g�L��
				Device->SetRenderState( D3DRS_ALPHAREF, 0x01 );						//�A���t�@�Q�ƒl
				Device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL  );		//�A���t�@�e�X�g�
				break;
			case 2:
				Device->SetRenderState( D3DRS_ZENABLE, FALSE );						//z�e�X�g����
				Device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );				//�A���t�@�e�X�g����
				break;
		}

		switch(mode)
		{
			case BLEND_ALPHA1:	//���ʂ̃A���t�@�u�����h
				//���ʂ̃A���t�@
				Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );				//�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );			//���Z����
				Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//SRC�̐ݒ�
				Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//DEST�̐ݒ�
				break;
			case BLEND_ADD1: //�f�t�H���g���Z����
				Device->SetRenderState( D3DRS_ALPHABLENDENABLE,TRUE);				//�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );			//���Z����
				Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE);				//SRC�̐ݒ�
				Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);				//DEST�̐ݒ�
				break;
			case BLEND_ALPHA2:	//�s����
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);					//�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA  );			//SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA  );			//DEST��
				break;
			case BLEND_FACTOR1:	//���R�u�����h
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);        //�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);   //�u�����h�t�@�N�^�[�̒l
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);   //�u�����h�t�@�N�^�[�̋t�̒l
				Device->SetRenderState(D3DRS_BLENDFACTOR,dwal);          //�u�����f�B���O�W���̐ݒ�

				/*
					���摜(argb) - dwal(argb)
					���摜(argb) �� dwal(argb)�@�ɉ������ĕϊ�
				*/
				break;
			case BLEND_FACTOR2:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);        //�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVBLENDFACTOR);   //�u�����h�t�@�N�^�[�̒l
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);   //�u�����h�t�@�N�^�[�̋t�̒l
				Device->SetRenderState(D3DRS_BLENDFACTOR,dwal);          //�u�����f�B���O�W���̐ݒ�
				/*
					���摜(argb) - dwal(argb)
					���摜(argb) �� dwal(argb)�@�ɉ������ĕϊ�
				*/
				
				break;
			case BLEND_SUB1:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);//DEST�̐ݒ�
				break;
			case BLEND_COLORADD1:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);//DEST�̐ݒ�
				break;
			case BLEND_ALPHA3:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);//DEST�̐ݒ�
				break;
			case BLEND_SUB2:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD   );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);//DEST�̐ݒ�
				break;
			case BLEND_BLACK:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);//DEST�̐ݒ�
				break;
			case BLEND_SUB3:
 				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
 				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);//DEST�̐ݒ�
				break;
			case BLEND_BLACK2:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//DEST�̐ݒ�
				break;
			case 13:
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);    //�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);//DEST�̐ݒ�
				break;
			case 14:	//�����Z����
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//�A���t�@�u�����f�B���O�̗L����
				Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);			//SRC�̐ݒ�
				Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//DEST��
				break;
			default:
				Device->SetRenderState( D3DRS_ZENABLE, TRUE );
				Device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);		//�����ӂ��u�����h�̖���
				Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//�A���t�@�e�X�g�̖���
				break;
		}
	}

	//-----------------------------------------
	//�f�o�C�X���Z�b�g����
	//-----------------------------------------
	void Artisan::SetDevice(PDirectDevice Device)
	{
		this->Device = Device;
	}
	
	//------------------------------
	//�ϊ��s��̏�����
	//------------------------------
	void Artisan::InitMatrix()
	{
		this->trans = D3DXMATRIX();
	}

}