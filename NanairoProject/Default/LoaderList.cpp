#pragma once

//---------------------------------------------------------
//
//2DâÊëúÇäiî[ÇµÅAï`âÊÇçsÇ§ÉNÉâÉX
//
//---------------------------------------------------------

//----------------------------------------------------------------------------
//MuDirectXDLL
//----------------------------------------------------------------------------
#include <DebugString.h>
using namespace NanairoLib;

//----------------------------------------------------------------------------
//MYGAME
//----------------------------------------------------------------------------
#include <ResourceFactory.h>

namespace MYGAME
{
	LoaderGraphList::LoaderGraphList(IDirect3DDevice9* in)
	{
		this->finishFlag = false;
		this->frameCnt = 0;
		this->_devices = in;
		this->_devices->AddRef();
		this->list = new std::list<LoaderGraphData*>();
	}

	LoaderGraphList::~LoaderGraphList()
	{
		this->_devices->Release();
		std::list<LoaderGraphData*>::iterator it = this->list->begin();
		while(it != this->list->end())
		{
			if( (*it) != NULL)
			{
				if( (*it)->gh != NULL )
					ES_SAFE_DELETE( (*it)->gh );
				ES_SAFE_DELETE( (*it) );
			}

			it = this->list->erase( it );
		}
		ES_SAFE_DELETE(this->list);
	}

	void LoaderGraphList::main_load()
	{
		//--------------------------------------------------------------------------------------------------
		//Default
		this->stockGraph("./Resource/Default/kiriEfect.png",	"kiriEfect",		2160, 360, 9,  1 );
		this->stockGraph("./Resource/Default/kaleidoscope.png",	"kaleidoEfect",		320, 2400, 1, 10 );
		this->stockGraph("./Resource/Default/yajirusi.png",		"yajirusi",			256, 256 );
		this->stockGraph("./Resource/Default/circleChain.png",	"circleChain",		512, 512 );
		this->stockGraph("./Resource/Default/longChain.png",	"longChain",		1024, 451 );
		this->stockGraph("./Resource/Default/devil.png",		"devil",			1200, 120, 10, 1 );
		this->stockGraph("./Resource/Default/fire1.png",		"fireEfect",		1200, 120, 10, 1 );
		this->stockGraph("./Resource/Default/fire2.png",		"fireEfect2",		1200, 120, 10, 1 );
		this->stockGraph("./Resource/Default/kirari.png",		"kirari",			2400, 240, 10, 1 );
		this->stockGraph("./Resource/Default/starEffect.png",		"starEffect",		960, 768, 5, 4 );
		this->stockGraph("./Resource/Default/magicStar.png",		"magictstarEffect",	600, 360, 5, 3 );
		
		//--------------------------------------------------------------------------------------------------
		this->stockGraph("./Resource/Image/Loading/background.png",	"back",		512, 512 );
		this->stockGraph("./Resource/Image/Loading/background2.png",	"back2",		512, 512 );
		this->stockGraph("./Resource/Image/white.png",				"black",		512, 512 );
		this->stockGraph("./Resource/Image/Tittle/yozora.png",	"yozora",		512, 512 );
		
		this->stockGraph("./Resource/Image/Tittle/title.png",		"title",		512, 512 );
		this->stockGraph("./Resource/Image/Tittle/tittleName.png",	"titleName",	256, 64 );
		this->stockGraph("./Resource/Image/Tittle/tittleStart.png",	"titleStart",	256, 128 );
		this->stockGraph("./Resource/Image/Tittle/selectroom.png",	"Selectroom",	512, 512 );
		this->stockGraph("./Resource/Image/Tittle/waitBack.png",		"waitBack",		256, 256, 2, 2 );
		this->stockGraph("./Resource/Image/dialog_1.png",			"dialog1",		256, 128 );
		this->stockGraph("./Resource/Image/Trump/z01.png",			"backcard",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/x02.png",			"jocker",		200, 300 );
		//this->stockGraph("./Resource/Image/Trump/trump.png",		"trumps",		650, 280, 13, 4 ); 

		this->stockGraph("./Resource/Image/Trump/c01.png",			"tpB1",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c02.png",			"tpB2",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c03.png",			"tpB3",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c04.png",			"tpB4",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c05.png",			"tpB5",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c06.png",			"tpB6",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c07.png",			"tpB7",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c08.png",			"tpB8",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c09.png",			"tpB9",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/c10.png",			"tpB10",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/c11.png",			"tpB11",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/c12.png",			"tpB12",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/c13.png",			"tpB13",	200, 300 );
	
		this->stockGraph("./Resource/Image/Trump/d01.png",			"tpC1",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d02.png",			"tpC2",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d03.png",			"tpC3",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d04.png",			"tpC4",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d05.png",			"tpC5",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d06.png",			"tpC6",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d07.png",			"tpC7",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d08.png",			"tpC8",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d09.png",			"tpC9",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/d10.png",			"tpC10",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/d11.png",			"tpC11",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/d12.png",			"tpC12",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/d13.png",			"tpC13",	200, 300 );

		this->stockGraph("./Resource/Image/Trump/h01.png",			"tpA1",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h02.png",			"tpA2",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h03.png",			"tpA3",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h04.png",			"tpA4",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h05.png",			"tpA5",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h06.png",			"tpA6",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h07.png",			"tpA7",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h08.png",			"tpA8",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h09.png",			"tpA9",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/h10.png",			"tpA10",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/h11.png",			"tpA11",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/h12.png",			"tpA12",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/h13.png",			"tpA13",	200, 300 );

		this->stockGraph("./Resource/Image/Trump/s01.png",			"tpD1",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s02.png",			"tpD2",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s03.png",			"tpD3",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s04.png",			"tpD4",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s05.png",			"tpD5",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s06.png",			"tpD6",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s07.png",			"tpD7",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s08.png",			"tpD8",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s09.png",			"tpD9",		200, 300 );
		this->stockGraph("./Resource/Image/Trump/s10.png",			"tpD10",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/s11.png",			"tpD11",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/s12.png",			"tpD12",	200, 300 );
		this->stockGraph("./Resource/Image/Trump/s13.png",			"tpD13",	200, 300 );

		//----------------------------------------------------------------------------------------------------
		//Accessary
		//Frame
		this->stockGraph("./Resource/Image/Accessary/frame/frame.png",		"frame", 400, 256 );

		this->stockGraph("./Resource/Image/Accessary/frame/number1Frame.png",	"number1Frame", 256, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/number2Frame.png",	"number2Frame", 256, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/number3Frame.png",	"number3Frame", 256, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/number4Frame.png",	"number4Frame", 256, 256 );

		this->stockGraph("./Resource/Image/Accessary/frame/map.png",			"map",			1024, 692 );
		this->stockGraph("./Resource/Image/Accessary/frame/scorePlate.png",		"scorePlate",	1024, 692 );
		this->stockGraph("./Resource/Image/Accessary/frame/numbers.png",		"numbers",		320, 128, 5, 2 );
		this->stockGraph("./Resource/Image/Accessary/frame/bigger.png",			"bigger",		256, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/yousi.png",			"yousi",		512, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/titleYousi.png",		"titleYousi",	512, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/noPlayer.png",		"noPlayer",		256, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/checkBox.png",		"checkBox",		256, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/signs.png",			"signs",		256, 256 );
		this->stockGraph("./Resource/Image/Accessary/frame/badge.png",			"badge",		512, 256 );	

		//-------------------------------------------------------------------------------------------------
		//chara
		this->stockGraph("./Resource/Image/Accessary/chara/ayano.png",			"ayanoCard",	200, 300 );
		this->stockGraph("./Resource/Image/Accessary/chara/erisu.png",			"erisuCard",	200, 300 );
		this->stockGraph("./Resource/Image/Accessary/chara/fiona.png",			"fionaCard",	200, 300 );
		this->stockGraph("./Resource/Image/Accessary/chara/rin.png",			"rinCard",		200, 300 );
		this->stockGraph("./Resource/Image/Accessary/chara/yui.png",			"yuiCard",		200, 300 );
		this->stockGraph("./Resource/Image/Accessary/chara/ayano2.png",			"ayano2",		300, 400 );
		this->stockGraph("./Resource/Image/Accessary/chara/erisu2.png",			"erisu2",		300, 400 );
		this->stockGraph("./Resource/Image/Accessary/chara/fiona2.png",			"fiona2",		300, 400 );
		this->stockGraph("./Resource/Image/Accessary/chara/rin2.png",			"rin2",			300, 400 );
		this->stockGraph("./Resource/Image/Accessary/chara/yui2.png",			"yui2",			300, 400 );

		this->stockGraph("./Resource/Image/Accessary/chara/playerAnime1.png",		"platePlayer1", 1024, 512, 4, 2);
		this->stockGraph("./Resource/Image/Accessary/chara/playerAnime2.png",		"platePlayer2", 1024, 512, 4, 2);
		this->stockGraph("./Resource/Image/Accessary/chara/playerAnime3.png",		"platePlayer3", 1024, 512, 4, 2);
		this->stockGraph("./Resource/Image/Accessary/chara/playerAnime4.png",		"platePlayer4", 1024, 512, 4, 2);
		this->stockGraph("./Resource/Image/Accessary/chara/playerAnime5.png",		"platePlayer5", 1024, 512, 4, 2);

		//-------------------------------------------------------------------------------------------------
		//rule
		this->stockGraph("./Resource/Image/Accessary/rule/eightcut.png",		"eightcut",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/elevenback.png",	"elevenback",	256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/restrains.png",	"restrains",	256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/revolution.png",	"revolution",	256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/jocker.png",		"jockerEFF",	256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/spade3.png",		"spade3",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/stairs.png",		"stairs",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/passing.png",		"passing",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/CapitalDown.png",	"capitalDown",	256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/hansoku.png",		"foul",			256, 128 );

		this->stockGraph("./Resource/Image/Accessary/rule/eightCutPlate.png",	"plateEightcut",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/elevenBackPlate.png",	"plateElevenback",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/restrainsPlate.png",	"plateRestrains",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/revolutionPlate.png",	"plateRevolution",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/jockerPlate.png",		"plateJockerEFF",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/stairsPlate.png",		"plateStairs",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/spade3Plate.png",		"plateSpade3",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/capitaldownPlate.png",	"plateCapitaldown",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/hansokuPlate.png",		"plateFoul",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/cardChangePlate.png",	"plateCardchange",	512, 128 );

		this->stockGraph("./Resource/Image/Accessary/rule/number1Plate.png",		"BigMillionaire",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/number2Plate.png",		"SmallMillionaire",	512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/number3Plate.png",		"SmallPoor",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/number4Plate.png",		"BigPoor",			512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/selectPlate1.png",		"selectPlate1",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/selectPlate2.png",		"selectPlate2",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/winnerName.png",		"winnerName",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/upper.png",			"upper",			512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/downer.png",			"downer",			512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/yourtorn.png",			"yourtorn",			512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/roundStart.png",		"roundStart",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/cardChange.png",		"cardChange",		512, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/mainSelect.png",		"mainSelect",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/continueSelect.png",		"continueSelect",	256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/gobackTittle.png",		"gobackTittle",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/newGame.png",			"newGame",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/continueGame.png",		"continueGame",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/netGame.png",		"netGame",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/ruleSelect.png",		"ruleSelect",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/gamestart.png",		"gameStart",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/allselect.png",		"allSelect",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/playerselect.png",		"playerSelect",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/ruleSelect2.png",		"ruleSelect2",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/backselect.png",		"backSelect",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/player.png",			"playerName",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/computer.png",			"computerName",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/easy.png",				"Easy",				256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/normal.png",			"Normal",				256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/strong.png",			"Strong",				256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/playerSelect2.png",	"playerSelect2",		256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/ready.png",			"areyouReady",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/gameStatus.png",		"gameStatus",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/score.png",			"score:",				256, 256 );
		this->stockGraph("./Resource/Image/Accessary/rule/pleasekey.png",		"pleasekey",			256, 256 );
		this->stockGraph("./Resource/Image/Accessary/rule/powerSelect.png",		"powerSelect",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/rule/erisu.png",			"erisu",				512, 256 );
		this->stockGraph("./Resource/Image/Accessary/rule/yui.png",				"yui",				512, 256 );
		this->stockGraph("./Resource/Image/Accessary/rule/rin.png",				"rin",					512, 256 );
		this->stockGraph("./Resource/Image/Accessary/rule/ayano.png",			"ayano",				512, 256 );
		this->stockGraph("./Resource/Image/Accessary/rule/fiona.png",			"fiona",				512, 256 );
		this->stockGraph("./Resource/Image/Accessary/rule/selectblock.png",		"selectBlock",			512, 128 );

		//----------------------------------------------------------------------------------------------------------
		//Effect
		this->stockGraph("./Resource/Image/Efect/kirari2.png",			"kirari2",			960, 120, 8, 1 );
		this->stockGraph("./Resource/Image/Efect/brust.png",			"brust",			320, 1200, 1, 10 );
		this->stockGraph("./Resource/Image/Efect/hanabi.png",			"FireflowerEffect",	1680, 120, 14, 1 );
		this->stockGraph("./Resource/Image/Efect/kamifubuki.png",		"Confetti",			1664, 128, 13, 1 );
		this->stockGraph("./Resource/Image/Efect/startEffect.png",		"startEffect",		320, 3240, 1, 27 );
		

		//----------------------------------------------------------------------------------------------
		//all
		this->stockGraph("./Resource/Image/Accessary/all/yubi.png",			"yubi",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/all/gain.png",			"gain",			659, 1024 );
		this->stockGraph("./Resource/Image/Accessary/all/rotaYaji.png",		"rotaYaji",		271, 271 );
		this->stockGraph("./Resource/Image/Accessary/all/fuki.png",			"fuki",			256, 128 );
		this->stockGraph("./Resource/Image/Accessary/all/efectBall.png",	"ball",			64, 64 );
		this->stockGraph("./Resource/Image/Accessary/all/click.png",		"clickMap",		256, 256 );
		this->stockGraph("./Resource/Image/Accessary/all/lclick.png",		"lclickMap",	256, 256 );
		this->stockGraph("./Resource/Image/Accessary/all/rclick.png",		"rclickMap",	256, 256 );
		this->stockGraph("./Resource/Image/Accessary/all/clickR.png",		"clickMapR",		256, 256 );
		this->stockGraph("./Resource/Image/Accessary/all/mclick.png",		"mclickMap",	256, 256 );

	}

	void LoaderGraphList::loadGraph(LPCSTR pass, LPCSTR newPass, int width, int height, int sumW, int sumH)
	{
		OutPutStringFunction out;
		
		NanairoLib::TextFunc text;
		LoaderGraphData* dt = new LoaderGraphData();
		dt->gh = new NanairoLib::MyGraph();
		if(text.LoadGraphIndex( this->_devices, dt->gh->GetTexturePointer(),
			pass, width, height, sumW, sumH))
		{
			dt->gh->SetDivision(0,0);
			dt->newName = newPass;
			out.Success_outputString( pass , newPass );
			this->list->push_back( dt );
		}
		else
		{
			out.Failed_outputString( pass );
			ES_SAFE_DELETE( dt->gh );
			ES_SAFE_DELETE( dt );
		}
	}

	void LoaderGraphList::stockGraph(LPCSTR pass, LPCSTR newPass, int width, int height, int sumW, int sumH)
	{
		LoaderGraphData* dt = new LoaderGraphData();
		dt->gh = new NanairoLib::MyGraph();
		dt->width = width;
		dt->height = height;
		dt->sumW = sumW;
		dt->sumH = sumH;
		dt->pass = pass;
		dt->newName = newPass;
		this->list->push_back( dt );
	}

	void LoaderGraphList::stockStep()
	{
		if(++this->frameCnt % 60 == 0)
		{
			std::list<LoaderGraphData*>::iterator it = this->list->begin();
			while(it != this->list->end() && (*it)->gh->GetTexture() != NULL)
				it++;
			if(it == this->list->end())
			{
				this->finishFlag = true;
				return ;
			}

			NanairoLib::TextFunc text;
			OutPutStringFunction out;
			for(int i=0; i<30 && it != this->list->end(); i++)
			{
				if(text.LoadGraphIndex( this->_devices, (*it)->gh->GetTexturePointer(),
					(*it)->pass.c_str(), (*it)->width, (*it)->height, (*it)->sumW, (*it)->sumH))
				{
					(*it)->gh->SetDivision((*it)->sumW,(*it)->sumH);
					out.Success_outputString( (*it)->pass.c_str() , (*it)->newName.c_str() );
					it++;
				}
				else
				{
					ES_SAFE_DELETE( (*it) );
					it = this->list->erase( it );
				}
			}

			if(it == this->list->end())
			{
				this->finishFlag = true;
				return ;
			}
		}
	}

	void LoaderGraphList::Pushing()
	{
		Text2DFactory* text = __GRAPHFACTORY;
		std::list<LoaderGraphData*>::iterator it = this->list->begin();
		while(it != this->list->end())
		{
			text->SetMyGraph( (*it)->newName.c_str(), (*it)->gh );
			(*it)->gh = NULL;
			ES_SAFE_DELETE( (*it) );
			it = this->list->erase( it );
		}
		this->list->clear();
	}
}