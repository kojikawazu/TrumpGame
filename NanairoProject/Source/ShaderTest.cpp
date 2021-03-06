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
		//最初に描画する宣言
		this->GetManager()->defaultDraw_beforeAction( 0, SHADER_MODE_2DNORMAL, screen );		
		////2D描画
		//Text2DFactory* text = __GRAPHFACTORY;
		//for(int i=0; i<100; i++)
		//{
		//
		////値を設定
		//text->draw_SetTrans( &D3DXVECTOR2(100,100), &D3DXVECTOR2(100,100), 0.0f ,
		//					"background", DIRECT_SCALE );
		////色の設定
		//text->GetArtisan()->SetColor( &D3DXVECTOR4(255,255,255,255) );
		////普通の２Ｄ描画
		//text->draw_graph();
		//}
		
		////3D描画のためにパスをチェンジ
		//this->GetManager()->changeShaderPass( SHADER_MODE_3DNORMAL, screen );
		////3D描画
		//Model3DFactory* model = Model3DFactory::GetInstance();
		//model->draw_model( "cube" );
		

		//描画終了宣言
		this->GetManager()->defaultDraw_afterAction( screen );

		//描画したスクリーンをバックバッファに描画
		this->GetManager()->DrawScreen( this->screen );
	}

	void TestShader::Dispose()
	{
	
	}
}
