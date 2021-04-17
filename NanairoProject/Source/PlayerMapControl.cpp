#pragma once

/////////////////////////////////////////////
//NanairoLib
/////////////////////////////////////////////
#include <MainFunction.h>
#include <MusicSound.h>

/////////////////////////////////////////////
//NanairoProject
/////////////////////////////////////////////
#include <RoomScene.h>
#include <ChangeScene.h>
#include <Rule_effect.h>
#include <SelectRoomDialog.h>
#include <TrumpCard.h>

using namespace NanairoLib;
using namespace MYGAME;

namespace NanairoProject
{
	PlayerMapControl::PlayerMapControl(RoomScene* _in)
	{
		_parent = _in;
		this->nowPlayermap = this->nextPlayerMap = NULL;
		this->Playermaplist.ListClear();
		this->nextPlayermaplist.ListClear();
	}

	PlayerMapControl::~PlayerMapControl()
	{
		this->Dispose();
	}

	void PlayerMapControl::Init(int playSum)
	{
		this->updownWord = "ok_se";
		this->okWord = "go_se";
		this->charaDataList.resize(playSum);
		for(int i=0; i<playSum; i++)
		{
			this->charaDataList[i].selectFlag = ( i == 0 );
			this->charaDataList[i].charaNum = i;
			this->charaDataList[i].spec = 0;
			this->charaDataList[i].poreFlag = ( i == 0 );
		}
	}

	void PlayerMapControl::UpdownMusic()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play( updownWord.c_str() );
	}

	void PlayerMapControl::okMusic()
	{
		SEFactory* se = MusicFactory::GetInstance()->GetMUSIC();
		se->Play( okWord.c_str() );	
	}

	void PlayerMapControl::Input_playerMapDialog(int playSum)
	{
		this->playSum = playSum;
		PlayerMapDialog* map;
		for( int i=0; i<this->playSum; i++ )
		{
			map = new PlayerMapDialog();
			map->SetNumber( &this->charaDataList[i], i, !_parent->IsNetGame() );
			this->nextPlayermaplist.Add( map );
		}
	}

	void PlayerMapControl::Dispose()
	{
		ES_SAFE_DELETE( this->nowPlayermap );
		ES_SAFE_DELETE( this->nextPlayerMap );
		this->Playermaplist.ListClear();
		this->nextPlayermaplist.ListClear();
	}

	void PlayerMapControl::NewAllPlayerMap()
	{
		PlayerMapDialog* map;
		for( int i=0; i<this->playSum; i++ )
		{
			map = new PlayerMapDialog();
			map->SetNumber( &this->charaDataList[i], i, !_parent->IsNetGame() );
			this->nextPlayermaplist.Add( map );
		}
	}

	void PlayerMapControl::NewSelectPlayerMap(int selectNum, bool IsContinue)
	{
		if( CHECK_NULL(this->nextPlayerMap) )
		{
			this->nextPlayerMap = new PlayerMapDialog();
			this->nextPlayerMap->SetNumber( &this->charaDataList[ selectNum ], selectNum, false, IsContinue );
		}
	}

	bool PlayerMapControl::FadeIn()
	{
		bool hantei = true;
		for(int i=0; i<2; i++)
		{
			for(std::list<PNormalObject>::iterator lis=
				(i==0 ? this->Playermaplist.Begin() :  this->nextPlayermaplist.Begin());
				(i==0 ? lis != this->Playermaplist.End() : lis != this->nextPlayermaplist.End());
				lis++)
			{
				(*lis)->Step();
				if( ((FadeNameDialog*)(*lis))->IsWait() )	hantei = false;
			}
		}
		return hantei;
	}

	bool PlayerMapControl::Step()
	{
		//プレイヤーマップのアクション
		std::list<PNormalObject>::iterator lis = this->Playermaplist.Begin();
		while( lis != this->Playermaplist.End() )
		{
			(*lis)->Step();
			if( (*lis)->isDel() )
			{
				ES_SAFE_DELETE( (*lis) );
				lis = this->Playermaplist.Erase( lis );
			}
			else					lis++;
		}

			//４つ入るともう１つのリストに移し替え
		lis = this->nextPlayermaplist.Begin();
		if(this->nextPlayermaplist.Size() > 3)
		{
			while( lis != this->nextPlayermaplist.End() )
			{
				this->Playermaplist.Add( (*lis) );
				lis = this->nextPlayermaplist.Erase( lis );
			}
		}

		if( !CHECK_NULL(this->nowPlayermap) )
		{
			if( !this->nowPlayermap->isDel() )	this->nowPlayermap->Step();
			else								ES_SAFE_DELETE( this->nowPlayermap );
		}
		else if( !CHECK_NULL(this->nextPlayerMap) )
		{
			this->nowPlayermap = this->nextPlayerMap;
			this->nextPlayerMap = NULL;
		}
			
		if( !CHECK_NULL(this->nextPlayerMap) )
		{
			if( !this->nextPlayerMap->isDel() )	this->nextPlayerMap->Step();
			else								ES_SAFE_DELETE( this->nextPlayerMap );
		}

		if( ( !CHECK_NULL(this->nowPlayermap) && this->nowPlayermap->isMove()) || 
			( !CHECK_NULL(this->nextPlayerMap) && this->nextPlayerMap->isMove()) )
			return true;
		return false;
	}

	bool PlayerMapControl::Step_SelectPlayer(int selectNum)
	{
		if( CHECK_NULL(this->nowPlayermap) )	return false;
		this->nowPlayermap->FukidasiStep();

		//-------------------------------------------------------------------------------------------
		//キーセレクト
		//-------------------------------------------------------------------------------------------
		if( __KEYDATA->trg[ KRIGHT ] )
		{
			this->nowPlayermap->downPlayNameNumber();
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KLEFT ] )
		{
			this->nowPlayermap->upPlayNameNumber();
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KZ ] ||
			(__MOUSEDATA->trg[LBUTTON] && this->nowPlayermap->GetPlayerFukidasiDialog()->IsMouseAtack() ) )
		{
			this->okMusic();
			this->nowPlayermap->stopPlayNameNumber();
			this->charaDataList[selectNum].charaNum = this->nowPlayermap->GetCharaData()->charaNum;
			return true;
		}
		return false;
	}

	bool PlayerMapControl::Step_SelectRule(int selectNum)
	{
		if( CHECK_NULL(this->nowPlayermap) )	return false;
		this->nowPlayermap->FukidasiStep();

		//-------------------------------------------------------------------------------------------
		//キーセレクト
		//-------------------------------------------------------------------------------------------
		if( __KEYDATA->trg[ KRIGHT ] )
		{
			this->nowPlayermap->downPowerNumber();
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KLEFT ] )
		{
			this->nowPlayermap->upPowerNumber();
			this->UpdownMusic();
		}
		else if( __KEYDATA->trg[ KZ ] ||
			(__MOUSEDATA->trg[LBUTTON] && this->nowPlayermap->GetPowerFukidasiDialog()->IsMouseAtack() ))
		{
			this->okMusic();
			this->nowPlayermap->stopPowerNumber();
			this->charaDataList[selectNum].spec = this->nowPlayermap->GetCharaData()->spec;
			return true;
		}
		return false;
	}

	bool PlayerMapControl::MouseCheck()
	{
		return false;
	}

	bool PlayerMapControl::FadeOut()
	{
		bool hantei = true;
		for(int i=0; i<2; i++)
		{
			for(std::list<PNormalObject>::iterator lis=
				(i==0 ? this->Playermaplist.Begin() :  this->nextPlayermaplist.Begin());
				(i==0 ? lis != this->Playermaplist.End() : lis != this->nextPlayermaplist.End());
				lis++)
			{
				(*lis)->Step();
				if( ((FadeNameDialog*)(*lis))->IsWait() )	hantei = false;	
			}
		}
		return hantei;
	}

	void PlayerMapControl::SetFadeIn()
	{
		if( !CHECK_NULL(this->nowPlayermap) )	this->nowPlayermap->SetFadeIn();
		if( !CHECK_NULL(this->nextPlayerMap) )	this->nextPlayerMap->SetFadeIn();
		
		for(int i=0; i<2; i++)
		{
			for(std::list<PNormalObject>::iterator lis=
				(i==0 ? this->Playermaplist.Begin() :  this->nextPlayermaplist.Begin());
				(i==0 ? lis != this->Playermaplist.End() : lis != this->nextPlayermaplist.End());
				lis++)
					((FadeNameDialog*)(*lis))->SetFadeIn();
		}
	}

	void PlayerMapControl::SetFadeOut()
	{
		if( !CHECK_NULL(this->nowPlayermap) )	this->nowPlayermap->SetFadeOut();
		if( !CHECK_NULL(this->nextPlayerMap) )	this->nextPlayerMap->SetFadeOut();
		this->SetFadeOutList();
	}

	void PlayerMapControl::SetNowPlayerMap_FadeOut()
	{
		if( !CHECK_NULL(this->nowPlayermap) )
			this->nowPlayermap->SetFadeOut();

	}

	void PlayerMapControl::SetFadeOutList()
	{
		for(int i=0; i<2; i++)
		{
			for(std::list<PNormalObject>::iterator lis=
				(i==0 ? this->Playermaplist.Begin() :  this->nextPlayermaplist.Begin());
				(i==0 ? lis != this->Playermaplist.End() : lis != this->nextPlayermaplist.End());
				lis++)
					((FadeNameDialog*)(*lis))->SetFadeOut();
		}
	}

	void PlayerMapControl::ChangePlayerMap(int selectNum, bool IsContinue)
	{
		this->SetFadeOutList();
		this->charaDataList[ selectNum ].selectFlag = !this->charaDataList[ selectNum ].selectFlag;
		if( CHECK_NULL(this->nextPlayerMap) )
		{
			this->nextPlayerMap = new PlayerMapDialog();
			this->nextPlayerMap->SetNumber( &this->charaDataList[ selectNum ], selectNum, false, IsContinue );
		}
					
		if( !CHECK_NULL(this->nowPlayermap) )
			this->nowPlayermap->SetFadeOut();
	}

	void PlayerMapControl::ChangeAllPlayerMap()
	{
		for( int i=1, siz=this->charaDataList.size(); i<siz; i++ )
		{
			if( !this->charaDataList[i].selectFlag )
				this->charaDataList[i].selectFlag = !this->charaDataList[i].selectFlag;
		}
	}

	void PlayerMapControl::SwitchDialog()
	{
		if( CHECK_NULL( this->nowPlayermap ) && !CHECK_NULL( this->nextPlayerMap ) )
		{
			this->nowPlayermap = this->nextPlayerMap;
			this->nextPlayerMap = NULL;
		}
	}

	void PlayerMapControl::Draw2D()
	{
		if( !CHECK_NULL(this->nowPlayermap) )	this->nowPlayermap->Draw2D();
		if( !CHECK_NULL(this->nextPlayerMap) )	this->nextPlayerMap->Draw2D();

		for(int i=0; i<2; i++)
		{
			for(std::list<PNormalObject>::iterator lis=
				(i==0 ? this->Playermaplist.Begin() :  this->nextPlayermaplist.Begin());
				(i==0 ? lis != this->Playermaplist.End() : lis != this->nextPlayermaplist.End());
				lis++)
					(*lis)->Draw2D();
		}
	}

	void PlayerMapControl::InputRule(std::vector<CharaData>* _list)
	{
		for(int i=0,siz=this->charaDataList.size(); i<siz; i++)
			this->charaDataList[i] = (*_list)[i];
	}

	int PlayerMapControl::OutputRule(std::vector<CharaData>* _list)
	{
		int count = 0;
		for(int i=0,siz=this->charaDataList.size(); i<siz; i++)
		{
			(*_list)[i] = this->charaDataList[i];
			if( this->charaDataList[i].selectFlag )	count++;
		}
		return count;
	}

}