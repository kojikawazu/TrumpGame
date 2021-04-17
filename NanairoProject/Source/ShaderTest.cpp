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
		//Å‰‚É•`‰æ‚·‚ééŒ¾
		this->GetManager()->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );		
		////2D•`‰æ
		//Text2DFactory* text = __GRAPHFACTORY;
		//for(int i=0; i<100; i++)
		//{
		//
		////’l‚ðÝ’è
		//text->draw_SetTrans( &D3DXVECTOR2(100,100), &D3DXVECTOR2(100,100), 0.0f ,
		//					"background", DIRECT_SCALE );
		////F‚ÌÝ’è
		//text->GetArtisan()->SetColor( &D3DXVECTOR4(255,255,255,255) );
		////•’Ê‚Ì‚Q‚c•`‰æ
		//text->draw_graph();
		//}
		
		////3D•`‰æ‚Ì‚½‚ß‚ÉƒpƒX‚ðƒ`ƒFƒ“ƒW
		//this->GetManager()->changeShaderPass( SHADER_MODE_3DNORMAL, screen );
		////3D•`‰æ
		//Model3DFactory* model = Model3DFactory::GetInstance();
		//model->draw_model( "cube" );
		

		//•`‰æI—¹éŒ¾
		this->GetManager()->defaultDraw_afterAction( screen );

		//•`‰æ‚µ‚½ƒXƒNƒŠ[ƒ“‚ðƒoƒbƒNƒoƒbƒtƒ@‚É•`‰æ
		this->GetManager()->DrawScreen( this->screen );
	}

	void TestShader::Dispose()
	{
	
	}
}
