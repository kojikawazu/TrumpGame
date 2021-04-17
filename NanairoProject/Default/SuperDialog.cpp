#pragma once

#include <DirectParts.h>
#include <ResourceFactory.h>
#include <Dialog.h>
#include <RoaderFile.h>
using namespace NanairoLib;


//２Dダイアログで普通から特殊なものまで取得していくっ
namespace MYGAME
{
	void SuperDialog::sameInit()
	{
		this->delFlag = false;
		this->selectNumber = 0;
		this->parts.isDraw = this->parts.isUpdate = true;
		this->parts.ang = 0.0f;
		this->parts.width = this->parts.height = 50;
		this->parts.pos.SetMinVector();
		this->parts.scale.SetVector(1,1);
		this->parts.color.SetMaxColor();
	}

	void SuperDialog::SetTagObject(RVector2 pos, float ang, RVector2 sc)
	{
		this->parts.pos = (Vector2)pos;
		this->parts.ang = ang;
		this->parts.scale = (Vector2)sc;
		this->parts.width = (int)sc.x;
		this->parts.height = (int)sc.y;
	}
	//-------------------------------------------------------------------

	bool SuperDialog::IsAtack_boundingbox_leftBox(PCVector2 atackPoint)
	{
		return ( (atackPoint->x > this->parts.pos.x &&
					atackPoint->x < this->parts.pos.x + (float)this->parts.scale.x &&
						atackPoint->y > this->parts.pos.y && 
						atackPoint->y < this->parts.pos.y + (float)this->parts.scale.y ) ? 
							true : false );
	}

	bool SuperDialog::IsAtack_boundingbox_centerBox(PCVector2 atackPoint)
	{
		return ( (atackPoint->x > this->parts.pos.x - (float)this->parts.scale.x * 0.5f &&
					atackPoint->x < this->parts.pos.x + (float)this->parts.scale.x * 0.5f &&
						atackPoint->y > this->parts.pos.y - (float)this->parts.scale.y * 0.5f && 
						atackPoint->y < this->parts.pos.y + (float)this->parts.scale.y * 0.5f ) ? 
							true : false );
	}

	bool SuperDialog::IsAtack_circle(PCVector2 atackPoint, PCVector2 widhei)
	{
		Vector2 distance;
		distance.SetVector( this->parts.pos.x - atackPoint->x, this->parts.pos.y - atackPoint->y ).ChangeAbs();
		return ( ( distance.x < (float)this->parts.width + widhei->x &&
					distance.y < (float)this->parts.height + widhei->y ) ? true : false );

	}
	//-------------------------------------------------------------------

	void SuperDialog::drawDialog()
	{
		if( this->parts.isDraw && this->parts.word != "" )
		{
			Text2DFactory* text = __GRAPHFACTORY;
			text->draw_SetTrans(
				this->parts.pos,
				D3DXVECTOR2( this->parts.scale.x + this->offSetScale.x, this->parts.scale.y + this->offSetScale.y),
				this->parts.ang, this->parts.word, ::DIRECT_SCALE,
				this->parts.color.color );
			text->draw_graph();
		}
	}

	//-------------------------------------------------------------------

	NameDialog::NameDialog()
	{
		this->sameInit();
		this->nameWord = "";
	}

	void NameDialog::SetObject(NanairoLib::RVector2 pos, float ang, NanairoLib::RVector2 sc)
	{
		this->SetTagObject( pos, ang, sc);
		this->offSetScale.SetVector(0,0);
	}

	void NameDialog::DrawNameTag()
	{
		//-----------------------------------------------------------------------------
		//名前の描画
		//-----------------------------------------------------------------------------
		if( this->GetParts()->isDraw )
		{
			this->drawDialog();
			Text2DFactory* text = __GRAPHFACTORY;
			text->draw_SetTrans(
				this->parts.pos.SetD3DVector2(),
				D3DXVECTOR2( this->parts.scale.x * 0.8f + this->offSetScale.x, this->parts.scale.y * 0.8f + this->offSetScale.y), 
				this->parts.ang, this->nameWord, ::DIRECT_SCALE,
				this->parts.color.color );
			text->draw_graph();
		}
	}

	void NameDialog::Draw2D()
	{
		//-----------------------------------------------------------------------------
		//タグの描画
		//-----------------------------------------------------------------------------
		this->drawDialog();
		this->DrawNameTag();
	}

	//--------------------------------------------------------------------------------

	//-------------------------------------------------------------
	//フェードの基本ダイアログ
	//-------------------------------------------------------------

	FadeNameDialog::FadeNameDialog() : waitFlag(false), selectFlag(false), interval(0), fadeSpd(0.0f), saveInterval(0)
	{
		this->ExpansionVector.SetVector(0,0);
		this->speed.SetVector(0,0);
		this->SetFadeIn();
	}

	void FadeNameDialog::SetMoveObject_ofPos(NanairoLib::RCVector2 start, NanairoLib::RCVector2 goal, int inInterval)
	{
		this->parts.pos = (Vector2)start;
		this->interval = inInterval;
		this->speed.SetVector( (goal.x - start.x) / this->interval, (goal.y - start.x) / this->interval );
	}

	void FadeNameDialog::SetMoveObject_ofScale(RCVector2 start, RCVector2 goal, int inInterval)
	{
		this->parts.scale = (Vector2)start;
		this->interval = inInterval;
		this->speed.SetVector( (goal.x - start.x) / this->interval, (goal.y - start.x) / this->interval );
		
	}

	//--------------------------------------------------------------------------------
}