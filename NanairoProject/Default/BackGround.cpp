#pragma once

////////////////////////////
//NanairoLib
#include <DirectParts.h>

////////////////////////////
//MYGAME
#include <ResourceFactory.h>
#include <UIParts.h>
#include <RoaderFile.h>
using namespace NanairoLib;
using namespace std;

//--------------------------------------------------------------
//背景など後ろに出すクラスを定義していく
//--------------------------------------------------------------
namespace MYGAME
{
	BackGround_2D::BackGround_2D(LPCSTR name)
	{
		this->Init();
		this->SetBackName( name );
	}

	void BackGround_2D::Init()
	{
		this->ui.pos.SetPercentVector( 0.5f, 0.5f );
		this->ui.ang = 0.0f;
		this->ui.scale.SetMaxScreen();
		this->ui.color.SetMaxColor();
	}

	void BackGround_2D::Draw2D()
	{
		if( !this->backName.empty() )
		{
			Text2DFactory* gh = __GRAPHFACTORY;
			
			gh->draw_SetTrans(this->ui.pos, this->ui.scale, this->ui.ang,
				this->backName , DIRECT_SCALE, this->ui.color.color );
	
			gh->draw_graph();
		}
	}

	void BackGround_2D::DrawScreen_NoTexture()
	{
		Text2DFactory* gh = __GRAPHFACTORY;

		gh->draw_SetTrans(this->ui.pos,this->ui.scale, this->ui.ang );
		gh->GetArtisan()->SetColor( &this->ui.color.color );
		gh->GetArtisan()->DrawVertexWall();
	}

	void BackGround_2D::loadParts(std::ifstream& fs)
	{
		char letter[256];
		std::string str;
		int size = 0;
		MYGAME::LoaderFunction func;

		while( !fs.eof() && !fs.fail() )
		{
			//文字の取得
			fs.getline( letter, sizeof(letter) );
			str = letter;
			size = str.size();
			
			//コメントや終了文字の合図
			if( size <= 2 )
				continue;
			else if( func.checkComment_or_finish( str ) )
				break;
			this->readParts( str );
		}
	}

	void BackGround_2D::readParts(std::string& str)
	{
		int index = 0, size = str.size();
		MYGAME::LoaderFunction func;
		std::string answer;
		//名前
		if( (index = func.isObject(str, "Name")) != -1 )
		{
			answer = str.substr( index + 1, size - index - 1 );
			this->SetBackName( (LPCTSTR)answer.c_str() );
		}
	}

	//-------------------------------------------------------------------------

}