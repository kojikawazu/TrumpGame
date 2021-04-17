#pragma once

//---------------------------------------------------------
//MyDirectDLL
//---------------------------------------------------------
#include <DebugString.h>

//---------------------------------------------------------
//MYGAME
//---------------------------------------------------------
#include <ResourceFactory.h>
using namespace NanairoLib;

//char ch[256];
//::GetCurrentDirectory( 256, ch );

//---------------------------------------------------------
//
//あらかじめロードするリソースをここに格納
//
//---------------------------------------------------------

namespace MYGAME
{
	bool Text2DFactory::main_loadGraph()
	{
		this->loadGraph( "./Resource/Default/backgroundES.png",	"backES",		512, 512 );
		this->loadGraph( "./Resource/Default/wa.png",					"donut",		128, 128 );

		//this->main_asynLoad();
		return true;
	}
	bool Text2DFactory::main_asynLoad()
	{
		return true;
	}

	bool Model3DFactory::main_loadGraph()
	{
		return true;
	}

	bool Model3DFactory::main_asynLoad()
	{
		return true;
	}

}