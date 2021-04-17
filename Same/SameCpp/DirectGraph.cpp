#pragma once
//----------------------------------------------------
//�Q�c�摜�̕`��̃��\�b�h��u���Ă܂���
//----------------------------------------------------
#include <DirectGraph.h>

namespace NanairoLib
{
	//------------------------------
	//������
	//------------------------------
	inline void MyGraph::sameInit()
	{
		this->parts.used = this->parts.division = false;
		this->parts.graph = NULL;
		this->parts.height = this->parts.width = this->parts.sumX = 
			this->parts.sumY = this->parts.oneH = this->parts.oneW = 0;
		this->color = D3DXVECTOR4( 255,255,255,255 );
		this->art = NULL;
	}

	//------------------------------
	//�f�R���n
	//------------------------------
	#pragma region �f�R���n
	inline MyGraph::MyGraph()
	{
		this->sameInit();
	}

	MyGraph::MyGraph(PTEXTUREH handle)
	{
		this->sameInit();
		this->SetTexture( handle->graph, (float)handle->width, (float)handle->height );
		this->SetDivision( handle->sumX, handle->sumY );
	}


	inline MyGraph::~MyGraph()
	{
		ES_SAFE_RELEASE( this->parts.graph );
	}
	#pragma endregion

	//----------------------------------------------------------------
	//�e�N�X�`���̃Z�b�e�B���O
	//----------------------------------------------------------------
	//@in : �e�N�X�`��
	//@in : ��
	//@in : ����
	void MyGraph::SetTexture(IDirect3DTexture9* gh, float wh, float ht)
	{
		if(gh == NULL)	return ;
		ES_SAFE_RELEASE( this->parts.graph );
		this->parts.graph = gh;
		this->parts.graph->AddRef();

		if( wh == 0 || ht == 0)
		{
			::IDirect3DSurface9* suf;
			D3DSURFACE_DESC desc;
			gh->GetSurfaceLevel( 0, &suf );
			suf->GetDesc( &desc );
			this->parts.width = (int)desc.Width;
			this->parts.height = (int)desc.Height;
			suf->Release();
		}
		else
		{
			this->parts.width = (int)wh;
			this->parts.height = (int)ht;
		}
	}

	//----------------------------------------------
	//�����̃Z�b�e�B���O
	//----------------------------------------------
	//@in : ��������
	//@in : �����c��
	void MyGraph::SetDivision(int divX, int divY)
	{
		if( divX == 0 || divY == 0 ||
			this->parts.width == 0 || this->parts.height == 0 )	
			return ;
		this->parts.sumX = divX;
		this->parts.sumY = divY;

		this->parts.oneW = this->parts.width / this->parts.sumX;
		this->parts.oneH = this->parts.height / this->parts.sumY;

		this->parts.division = true;
	}

	//----------------------------------------------
	//���[�h�e�N�X�`��
	//----------------------------------------------
	//@in : DirectX�p�f�o�C�X
	//@in : �t�@�C���p�X
	//@in : ��
	//@in : ����
	//@in : ��������
	//@in : �����c��
	bool MyGraph::LoadTexture(PDirectDevice Device,PCSTR fileName,int width,int height,int sumW,int sumH)
	{
		TextFunc text;
		if( text.LoadGraphIndex(Device, &this->parts, fileName, width, height, sumW, sumH) == -1)
			return this->parts.used = false;
		return (this->parts.used = true);
	}

	//----------------------------------------------
	//�e�N�X�`���̃����[�X
	//----------------------------------------------
	void MyGraph::ReleaseTexture()
	{
		ES_SAFE_RELEASE( this->parts.graph );
	}

	//----------------------------------------------
	//�e�N�X�`���n���h���̎擾
	//----------------------------------------------
	//@out : �e�N�X�`���n���h��
	PCTEXTUREH MyGraph::GetTextureHandle()
	{
		return &this->parts;
	}

	//----------------------------------------------
	//�e�N�X�`���n���h���|�C���^�̎擾
	//----------------------------------------------
	//@out : �e�N�X�`���n���h��
	PTEXTUREH MyGraph::GetTexturePointer()
	{
		return &this->parts;
	}

	//----------------------------------------------
	//�e�N�X�`���̎擾
	//----------------------------------------------
	//@out : DirectX�p�e�N�X�`��
	const IDirect3DTexture9* MyGraph::GetTexture()
	{
		return this->parts.graph;
	}

	//----------------------------------------------
	//�J���[�̎擾
	//----------------------------------------------
	PCVector4 MyGraph::GetColor()
	{
		return &this->color;
	}

	//----------------------------------------------
	//�J���[�̃Z�b�e�B���O
	//----------------------------------------------
	//@in : argb
	void MyGraph::SetColor(float a, float r, float g, float b)
	{
		this->color.x = a;
		this->color.y = r;
		this->color.z = g;
		this->color.w = b;
	}

	//----------------------------------------------
	//�J���[�̃Z�b�e�B���O
	//----------------------------------------------
	//@in : argb�J���[�x�N�g��
	void MyGraph::SetColor(PCVector4 col)
	{
		this->color = col;
	}

	//----------------------------------------------
	//�e�N�X�`���̕��ʂɕ`��
	//----------------------------------------------
	//@in : �`���p�N���X
	void MyGraph::Draw_Graph(Artisan* Artisan)
	{
		Artisan->DrawVertexBuffer( &this->parts );
	}

	//----------------------------------------------
	//�e�N�X�`���̃A�j���[�V�����`��
	//----------------------------------------------
	//@in : �`���p�N���X
	//@in : ���蓖�Ĕԍ�
	void MyGraph::Draw_Animation_Graph(int number)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawVertexBufferIndex( &this->parts, number );
	}

	//----------------------------------------------
	//�e�N�X�`���̒����W�ݒ�E�������`��
	//----------------------------------------------
	//@in : �`���p�N���X
	//@in : �l�p�̍��W�x�N�g��
	//@in : ��������
	//@in : �����c��
	//@in : ���蓖�Ĕԍ�
	void MyGraph::Draw_Modi_div_Animation_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number, int divXSum, int divYSum)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawVertexBufferIndexModi( &this->parts, lup, rup, lbot, rbot, number, divXSum, divYSum );
	}

	//----------------------------------------------
	//�e�N�X�`���̒����W�ݒ�E�A�j���[�V�����`��
	//----------------------------------------------
	//@in : �`���p�N���X
	//@in : �l�p�̍��W�x�N�g��
	//@in : ���蓖�Ĕԍ�
	void MyGraph::Draw_Modi_Animation_Graph( RCVector2 lup, RCVector2 rup, RCVector2 lbot, RCVector2 rbot,int number)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawRectDepGraph( lup, rup, lbot, rbot, number, &this->parts );
	}

	//----------------------------------------------
	//�e�N�X�`���̃K���X�̂悤�ȕ`��
	//----------------------------------------------
	//@in : �`���p�N���X
	//@in : �O�p�`�̍��W�x�N�g��
	//@in : ������
	//@in : ��������
	//@in : ��������
	//@in : �����c��
	//@in : ���蓖�Ĕԍ�
	void MyGraph::Draw_Grass_Graph(RCVector2 lup, RCVector2 rup, RCVector2 lbot,int number, int divXSum, int divYSum, int width, int height,bool IsUp)
	{
		if( CHECK_NULL(art) )	return ;
		art->DrawIndexGlassHopper( this->parts.graph, lup, rup, lbot, number, divXSum, divYSum , width, height, IsUp );
	}

	//----------------------------------------------
	//�`��̃g�����X�t�H�[��
	//----------------------------------------------
	//@in : �`���p�N���X
	//@in : �ʒu
	//@in : �X�P�[��
	//@in : �p�x
	//@in : �F���
	//@in : �X�P�[�����[�h
	void MyGraph::Transform(RCVector2 pos, RCVector2 scale, float angle,PCVector4 color,int mode)
	{
		if( CHECK_NULL(art) )	return ;
		art->Transform( pos, scale, angle, &this->parts, color, mode );
		this->color = (color);
	}

	//----------------------------------------------
	//�`��̃g�����X�t�H�[��(3D�p)
	//----------------------------------------------
	//@in : �`���p�N���X
	//@in : �ʒu
	//@in : �X�P�[��
	//@in : �p�x
	//@in : �F���
	//@in : �X�P�[�����[�h
	void MyGraph::Transform3D(PCVector3 pos, RCVector2 scale, PCVector3 angle,PCVector4 color,int mode)
	{
		if( CHECK_NULL(art) )	return ;
		art->Transform3D( pos, scale, angle, &this->parts, color, mode );
		this->color = color;

	}

	//----------------------------------------------
	//�`��̃g�����X�t�H�[��(�r���{�[�h�p)
	//----------------------------------------------
	//@in : �`���p�N���X
	//@in : �ʒu
	//@in : �X�P�[��
	//@in : �p�x
	//@in : �F���
	//@in : �r���{�[�h�s��
	//@in : �X�P�[�����[�h
	void MyGraph::TransformBillboard(PCVector3 pos, RCVector2 scale, float angle,PCVector4 color, PCMATRIX board, int mode)
	{
		if( CHECK_NULL(art) )	return ;
		art->Transform3D_ofBillboard( pos, scale, angle, &this->parts, color, board, mode );
		this->color = color;
	}
}