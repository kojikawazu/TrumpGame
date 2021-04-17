#pragma once

#include <ResourceDrawer.h>
using namespace NanairoLib;

#include <ResourceFactory.h>
using namespace MYGAME;

#include <ShaderTest.h>

namespace NanairoProject
{
	TestShader::TestShader()
	{
		Init();
	}

	void TestShader::Init()
	{
		//2Dtest
		Text2DFactory* text = __GRAPHFACTORY;
		text->loadGraph("./Resource/Image/background.png", "background", 512, 512 );

		//3Dtest
		Model3DFactory* model = Model3DFactory::GetInstance();
		model->load_model("./Resource/Model/cube.x", "cube" );

	}

	void TestShader::Draw()
	{
		//�ŏ��ɕ`�悷��錾
		this->GetManager()->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );		
		////2D�`��
		//Text2DFactory* text = __GRAPHFACTORY;
		//for(int i=0; i<100; i++)
		//{
		//
		////�l��ݒ�
		//text->draw_SetTrans( &D3DXVECTOR2(100,100), &D3DXVECTOR2(100,100), 0.0f ,
		//					"background", DIRECT_SCALE );
		////�F�̐ݒ�
		//text->GetArtisan()->SetColor( &D3DXVECTOR4(255,255,255,255) );
		////���ʂ̂Q�c�`��
		//text->draw_graph();
		//}
		
		////3D�`��̂��߂Ƀp�X���`�F���W
		//this->GetManager()->changeShaderPass( SHADER_MODE_3DNORMAL, screen );
		////3D�`��
		//Model3DFactory* model = Model3DFactory::GetInstance();
		//model->draw_model( "cube" );
		

		//�`��I���錾
		this->GetManager()->defaultDraw_afterAction( screen );

		//�`�悵���X�N���[�����o�b�N�o�b�t�@�ɕ`��
		this->GetManager()->DrawScreen( this->screen );
	}

	void TestShader::Dispose()
	{
	
	}
}
