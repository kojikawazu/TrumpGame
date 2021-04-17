#pragma once

/////////////////////////////////////////////////
//NanairoLib
#include <DirectParts.h>
#include <MainFunction.h>
using namespace NanairoLib;

/////////////////////////////////////////////////
//MYGAME
#include <ResourceFactory.h>
#include <Dialog.h>
#include <RoaderFile.h>


//２Dダイアログで普通から特殊なものまで取得していくっ
namespace MYGAME
{
	//-------------------------------------------------------------
	//はい・いいえ型ダイアログ
	//-------------------------------------------------------------
	YesNoDialog::~YesNoDialog()
	{
		ES_SAFE_DELETE( this->checkBox );
		ES_SAFE_DELETE( this->okBox );
	}

	void YesNoDialog::Init()
	{
		this->selectNumber = 1;
		this->delFlag = false;
		
		this->parts.color.SetColor( 255, 255, 255, 255 );
		this->SetObject( Vector2( SCRW_PERCENT( 0.5f ), SCRH_PERCENT(0.5f) ), 0.0f, Vector2( 0.0f, 0.0f ) );
		this->SetMoveObject_ofScale( Vector2( 0.0f, 0.0f), Vector2(SCRW_PERCENT(0.8f), SCRH_PERCENT(0.8f)), 6 ); 
		this->SetDialogName( "map" );

		this->Input_checkBox();
		this->Input_okBox();
	}

	void YesNoDialog::Input_okBox()
	{
		this->okBox = new NameDialog();
		this->okBox->SetObject( this->parts.pos, this->parts.ang, Vector2(this->parts.scale.x * 1.2f + this->offSetScale.x, this->parts.scale.y * 1.2f + this->offSetScale.y) );
		this->okBox->SetDialogName( "areyouReady" );
		this->okBox->SetNameColor( Vector4( 255,0,0,0) );
	}

	void YesNoDialog::Input_checkBox()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->checkBox = new NameDialog();
		this->checkBox->SetObject( Vector2(_pt->pos.x - _pt->scale.x * 0.2f + _pt->scale.x * 0.35f * this->selectNumber, _pt->pos.y + _pt->scale.y * 0.15f),
			_pt->ang, Vector2(_pt->scale.x * 0.4f + this->offSetScale.x, _pt->scale.x * 0.3f + this->offSetScale.y) );
		this->checkBox->SetNameColor( _pt->color.color );
		this->checkBox->SetDialogName("checkBox");
	}
	
	void YesNoDialog::FadeIn()
	{
		this->parts.scale.Add( this->speed );
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void YesNoDialog::Wait()
	{
		if( __KEYDATA->trg[ KLEFT ] )
			this->downPlayNameNumber();
		else if( __KEYDATA->trg[ KRIGHT ] )
			this->upPlayNameNumber();
	}

	void YesNoDialog::FadeOut()
	{
		this->parts.scale.Sub( this->speed );
		this->parts.scale.SubCut();

		if( this->IncrementInterval(6) )	
		{
			this->SetWait();
			this->delFlag = true;
		}
	}

	bool YesNoDialog::MouseCheck()
	{
		Vector2 vec( (float)__MOUSEDATA->mouseX, (float)__MOUSEDATA->mouseY );
		NanairoLib::PUIParts2D _pt = this->GetParts();
		for(int i=0; i<2; i++)
		{
			this->checkBox->SetPos( Vector2(_pt->pos.x - _pt->scale.x * 0.2f + _pt->scale.x * 0.35f * i, _pt->pos.y + _pt->scale.y * 0.15f) );
			if( this->checkBox->IsAtack_boundingbox_centerBox( &vec ) )
			{
				this->selectNumber = i;
				return true;
			}
		}
		return false;	
	}


	void YesNoDialog::Draw2D()
	{
		//-----------------------------------------------------------------------------
		//タグの描画
		//-----------------------------------------------------------------------------
		this->drawDialog();

		//-----------------------------------------------------------------------------
		//プレイヤーの描画
		//-----------------------------------------------------------------------------
		this->PlayerDraw();

		//-----------------------------------------------------------------------------
		//セレクト枠の描画
		//-----------------------------------------------------------------------------
		this->SelecterDraw();
	}

	void YesNoDialog::PlayerDraw()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->okBox->SetScl( Vector2(_pt->scale.x * 0.6f + this->offSetScale.x, _pt->scale.x * 0.5f + this->offSetScale.y) );
		this->okBox->Draw2D();
	}
	
	void YesNoDialog::SelecterDraw()	
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		this->checkBox->SetPos( Vector2(_pt->pos.x - _pt->scale.x * 0.2f + _pt->scale.x * 0.35f * this->selectNumber, _pt->pos.y + _pt->scale.y * 0.15f) );
		this->checkBox->SetScl(	Vector2(_pt->scale.x * 0.4f + this->offSetScale.x, _pt->scale.x * 0.3f + this->offSetScale.y) );
		this->checkBox->Draw2D();
	}

	//-------------------------------------------------------------
	//待ち型ダイアログ
	//-------------------------------------------------------------
	void WaitBackDialog::Init()
	{
		this->delFlag = false;
		this->parts.color.SettingFadeAlpha();
		this->fadeSpd = 255.0f/10;

		this->SetObject( Vector2( 0.0f, 0.0f ), 0.0f, 
			Vector2( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f) ) );
		this->SetMoveObject_ofPos( Vector2( 0.0f, 0.0f ), Vector2(SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f) ), 10 );
		this->SetDialogName( "waitBack" );
	}
	
	void WaitBackDialog::FadeIn()
	{
		this->parts.pos.Add( this->speed );
		this->parts.color.FadeIn( this->fadeSpd );
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void WaitBackDialog::FadeOut()
	{
		this->parts.pos.Add( this->speed );
		this->parts.color.FadeOut( this->fadeSpd );
		if( this->IncrementInterval(10) )	
		{
			this->SetWait();
			this->delFlag = true;
		}
	}

	void WaitBackDialog::Draw2D()
	{
		NanairoLib::PUIParts2D _pt = this->GetParts();
		Vector2 dpos;
		for(int i=0; i<4; i++)
		{
			switch(i)
			{
				case 0:	dpos.SetVector( SCRW_PERCENT(0.25f)				, SCRH_PERCENT(0.75f) - _pt->pos.y );	break;
				case 1:	dpos.SetVector( SCRW_PERCENT(0.25f) + _pt->pos.x	, SCRH_PERCENT(0.25f) );			break;
				case 2:	dpos.SetVector( SCRW_PERCENT(0.75f) - _pt->pos.x	, SCRH_PERCENT(0.75f) );			break;
				case 3:	dpos.SetVector( SCRW_PERCENT(0.75f)				, SCRH_PERCENT(0.25f) + _pt->pos.y );	break;
			}
		
			//-----------------------------------------------------------------------------
			//タグの描画
			//-----------------------------------------------------------------------------
			Text2DFactory* text = __GRAPHFACTORY;
			text->draw_SetTrans(
				dpos.SetD3DVector2(),
				D3DXVECTOR2( _pt->scale.x + this->offSetScale.x, _pt->scale.y + this->offSetScale.y),
				_pt->ang, this->parts.word, ::DIRECT_SCALE,
				_pt->color.color );
			text->draw_divGraph(i);
		}
	}

	//-------------------------------------------------------------
	//点滅ダイアログ
	//-------------------------------------------------------------
	void FlushingDialog::Init()
	{
		this->delFlag = false;
		this->parts.color.SettingFadeAlpha();
		this->fadeSpd = 255.0f/100;
	}

	//-------------------------------------------------------------
	//←画面外から→へスライドするフェード型ダイアログ
	//-------------------------------------------------------------
	void SlidesideDialog::Init()
	{
		this->ExpansionVector.SetVector(100, 30);
		this->SetObject( Vector2( SCRW_PERCENT( -0.3f), 0.0f), 0.0f, Vector2( 350.0f, 120.0f ) );
		this->interval = this->saveInterval = 10;
		this->speed.SetVector( (SCRW_PERCENT(0.1f) - this->parts.pos.x) / this->interval, 0.0f );
	}

	void SlidesideDialog::onSelect()
	{
		this->selectFlag = true;
		this->offSetScale = (Vector2)this->ExpansionVector;
	}
	
	void SlidesideDialog::offSelect()
	{
		this->selectFlag = false;
		this->offSetScale.SetMinVector();
	}
		
	void SlidesideDialog::FadeIn()
	{
		this->parts.pos.x += this->speed.x;
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void SlidesideDialog::FadeOut()
	{
		this->parts.pos.x -= this->speed.x;
		if( this->IncrementInterval(this->saveInterval) )	this->SetWait();
	}

	//-------------------------------------------------------------
	//羊皮紙拡大型ダイアログ
	//-------------------------------------------------------------
	void ExpansionDialog::Init()
	{
		this->SetObject( Vector2( SCRW_PERCENT( 0.5f ), SCRH_PERCENT(0.1f) ), 0.0f, Vector2( 0.0f, 0.0f ) );
		this->interval = 6;
		this->speed.SetVector( ((int)SCRW_PERCENT(0.8f)) / this->interval, SCRH_PERCENT(0.15f) / this->interval );
	}

	void ExpansionDialog::FadeIn()
	{
		this->parts.scale.Add( this->speed );
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void ExpansionDialog::FadeOut()
	{
		this->parts.scale.Sub( this->speed );
		if( this->IncrementInterval(6) )	this->SetWait();
	}

	//-------------------------------------------------------------
	//→画面外から←へスライドするフェード型ダイアログ
	//-------------------------------------------------------------
	void SlidesideDialogLeft::Init()
	{
		this->touchFlag = false;
		this->selectNumber = 0;
		this->selectSpd = 5;
		this->interval = 10;
		this->touchisWord = "selectPlate1";
		this->touchnoWord = "selectPlate2";
		
		this->ExpansionVector.SetVector(100, 30);
		this->SetObject( Vector2( SCRW_PERCENT( 1.3f), 0.0f), 0.0f, Vector2( 350.0f, 120.0f ) );
		this->speed.SetVector( (SCRW_PERCENT(0.7f) - this->parts.pos.x) / this->interval, 0.0f );
		this->selectVec = (Vector2)this->parts.pos;
		this->SetDialogName( this->touchnoWord.c_str() );
	}

	void SlidesideDialogLeft::SetNumber(int num, int dialogSum)
	{
		this->selectNumber = num;
		this->dialogSum = dialogSum;
		this->parts.pos.y = 200.0f + (num-dialogSum) * 100.0f;
		this->selectVec = (Vector2)this->parts.pos;
	}

	void SlidesideDialogLeft::onSelect()
	{
		this->selectFlag = true;
		this->offSetScale = (Vector2)this->ExpansionVector;
	}
	
	void SlidesideDialogLeft::offSelect()
	{
		this->selectFlag = false;
		this->offSetScale.SetMinVector();
	}
		
	void SlidesideDialogLeft::upSelect()
	{
		this->selectVec.y -= 100.0f;
		this->selectSpd = 10;
	}

	void SlidesideDialogLeft::downSelect()
	{
		this->selectVec.y += 100.0f;
		this->selectSpd = 10;
	}

	void SlidesideDialogLeft::normalSelect()
	{
		this->selectVec.y = 200.0f + (this->selectNumber-this->dialogSum) * 100.0f;
		this->selectSpd = 10;
	}

	void SlidesideDialogLeft::specSelect()
	{
		this->selectVec.y = 200.0f -(100.0f * 9.0f) + (this->selectNumber-this->dialogSum) * 100.0f;
		this->selectSpd = 10;
	}

	void SlidesideDialogLeft::onTouch()
	{
		this->touchFlag = !this->touchFlag;
		( this->touchFlag ? this->SetDialogName( this->touchisWord.c_str() ) :
			this->SetDialogName( this->touchnoWord.c_str() ) );
	}

	void SlidesideDialogLeft::FadeIn()
	{
		this->parts.pos.x += this->speed.x;
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void SlidesideDialogLeft::Wait()
	{
		if( this->parts.pos.y > this->selectVec.y )
			this->parts.pos.y -= this->selectSpd;
		else if( this->parts.pos.y < this->selectVec.y )
			this->parts.pos.y += this->selectSpd;
	}

	void SlidesideDialogLeft::FadeOut()
	{
		this->parts.pos.x -= this->speed.x;
		if( this->IncrementInterval(10) )	this->SetWait();
	}

	//-------------------------------------------------------------
	//←画面外から→へスライドするフェード型ダイアログ
	//-------------------------------------------------------------
	void NoticeDialog::Init()
	{
		this->boundFlag = false;
		this->ExpansionVector.SetVector(100, 30);
		this->SetObject( Vector2( SCRW_PERCENT(0.5f), SCRH_PERCENT(0.5f)), 0.0f, Vector2( 0.0f, 0.0f ) );
		this->interval = this->saveInterval = 10;
		this->speed.SetVector( SCRW_PERCENT(0.3f) / this->interval, SCRH_PERCENT(0.3f) / this->interval );
		this->SetDialogName("fuki");
	}
		
	void NoticeDialog::FadeIn()
	{
		this->parts.scale.Add(this->speed);		
		if( this->DecrementInterval(0) )	this->SetWait();
	}

	void NoticeDialog::Wait()
	{
		if( !this->boundFlag )
		{
			this->parts.scale.Add(Vector2(this->speed.x * 0.2f, this->speed.y * 0.2f));
			if( this->DecrementInterval((int)(this->saveInterval * 0.5f)) )	
				this->boundFlag = !this->boundFlag;
		}
		else
		{
			this->parts.scale.Sub(Vector2(this->speed.x * 0.2f, this->speed.y * 0.2f));
			if( this->IncrementInterval(this->saveInterval) )	
				this->boundFlag = !this->boundFlag;
		}
		
	}

	void NoticeDialog::FadeOut()
	{
		this->parts.scale.Sub(this->speed);
		if( this->IncrementInterval(this->saveInterval) )
			this->parts.scale.SetVector(0,0);
	}
}