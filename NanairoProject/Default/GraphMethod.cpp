#pragma once

//---------------------------------------------------------
//
//2D画像を格納し、描画を行うクラス
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
	Text2DFactory::Text2DFactory() : 
	asynOK(false), frameCnt(0), graphSum(0), _devices(NULL), custom(NULL)
	{
		graphTable.clear();
		fontTable.clear();
	}

	Text2DFactory::~Text2DFactory()
	{
		this->releaseGraph();
		this->_devices = NULL;
		this->custom = NULL;
	}

	//---------------------------------------------------------
	//たいていのロードはこれ！
	//---------------------------------------------------------
	bool Text2DFactory::loadGraph(LPCTSTR str, LPCTSTR name, int width, int height, int sumW, int sumH)
	{
		OutPutStringFunction out;
		if( this->graphTable.find( name ) != this->graphTable.end() )
		{
			out.SameOut_outputString( name );
			return false;
		}
		
		NanairoLib::TextFunc text;
		NanairoLib::MyGraph* gh = new NanairoLib::MyGraph();
		if(	text.LoadGraphIndex( this->_devices, gh->GetTexturePointer(),
			str, width, height, sumW, sumH ) != -1)
		{
			gh->SetDivision( sumW, sumH );
			this->graphTable.insert( GraphType( name, gh ) );
			this->graphSum++;
			out.Success_outputString( str , name );
			return true;
		}
		else
		{
			out.Failed_outputString( str );
			ES_SAFE_DELETE( gh );
			return false;
		}
	}

	//---------------------------------------------------------
	//リリース
	//---------------------------------------------------------
	void Text2DFactory::releaseGraph()
	{
		GraphIterator it = this->graphTable.begin();
		while( it != this->graphTable.end() )
		{
			MyGraph* gh = (MyGraph*)(it->second);
			delete gh;
			it = this->graphTable.erase( it );
		}
		
		FontIterator ft = this->fontTable.begin();
		while( ft != this->fontTable.end() )
		{	
			NanairoLib::MyFont* mft = (MyFont*)(ft->second);
			delete mft;
			ft = this->fontTable.erase( ft );
		}
	}

	//---------------------------------------------------------
	//ロードしてないテクスチャをリストに格納
	//---------------------------------------------------------
	void Text2DFactory::SetTexture(LPCSTR newName,NanairoLib::TEXTUREH* graph)
	{
		if( graph == NULL || graph->graph == NULL )
			return ;
		MyGraph* gh = new MyGraph( graph );
		this->graphTable.insert( GraphType( newName, gh ) );
		this->graphSum++;
	}

	void Text2DFactory::SetMyGraph(LPCSTR pass, NanairoLib::MyGraph* gh)
	{
		this->graphTable.insert( GraphType( pass, gh ) );
		this->graphSum++;
	}

	//-----------------------------------------------------------------------------------------------------------

	//---------------------------------------------------------
	//各種設定
	//---------------------------------------------------------
	bool Text2DFactory::draw_SetTrans(RCVector2 pos, float sc, float ang, std::string name,int mode,const Vector4 color)
	{
		GraphIterator it = this->graphTable.find(name);
		if( it != this->graphTable.end() )
		{
			this->custom->Transform(pos, Vector2(sc,sc), ang, (*it).second->GetTexturePointer(), &color, mode );
			this->SetName = name;
			return true;
		}
		else	
			return false;
	}

	bool Text2DFactory::draw_SetTrans(RCVector2 pos, RCVector2 sc, float ang, std::string name,int mode,const Vector4 color)
	{
		GraphIterator it = this->graphTable.find(name);

		if(it != this->graphTable.end())
		{
			this->custom->Transform(pos, sc, ang, (*it).second->GetTexturePointer(),&color,mode);
			this->SetName = name;
			return true;
		}
		else 
			return false;
	}
	
	bool Text2DFactory::draw_SetTrans(PCVector3 pos, RCVector2 sc, PCVector3 ang, std::string name,int mode,const Vector4 color)
	{
		GraphIterator it = this->graphTable.find(name);
		
		if( it != this->graphTable.end() )
		{
			this->custom->Transform3D(pos, D3DXVECTOR2(sc.x,sc.y), ang, (*it).second->GetTexturePointer(),&color,mode);
			this->SetName = name;
			return true;
		}
		else	
			return false;
	}
	
	bool Text2DFactory::draw_SetTrans(PCVector3 pos, RCVector2 sc, float ang, PCMATRIX board, std::string name,int mode,const Vector4 color)
	{
		GraphIterator it = this->graphTable.find(name);
		
		if( it != this->graphTable.end() )
		{
			this->custom->Transform3D_ofBillboard(pos, D3DXVECTOR2(sc.x,sc.y), ang, (*it).second->GetTexturePointer(), &color, board, mode);
			this->SetName = name;
			return true;
		}
		else	
			return false;
	}
		
	//---------------------------------------------------------
	//カラーだけを設定
	//---------------------------------------------------------
	bool Text2DFactory::draw_SetTrans(const Vector4* color,std::string name)
	{
		this->custom->SetColor(color);
		this->SetName = name;
		return true;
	}

	bool Text2DFactory::draw_SetTrans(RCVector2 pos, RCVector2 sc, float ang)
	{
		this->custom->Transform( pos, sc , ang );
		this->SetName.clear();
		return true;
	}

	//---------------------------------------------------------
	//普通の描画
	//---------------------------------------------------------
	void Text2DFactory::draw_graph()
	{
		GraphIterator it = this->graphTable.find( this->SetName );
		if( it != this->graphTable.end() )
			this->custom->DrawVertexBuffer( (*it).second->GetTexturePointer() );
	}
	
	//---------------------------------------------------------
	//アニメ分割描画
	//---------------------------------------------------------
	void Text2DFactory::draw_divGraph(int animeCnt)
	{
		GraphIterator it = this->graphTable.find( this->SetName );
		if( it != this->graphTable.end() )
			this->custom->DrawVertexBufferIndex( (*it).second->GetTexturePointer(), animeCnt );
	}
	
	//---------------------------------------------------------
	//4点を決めて普通のアニメ分割描画
	//---------------------------------------------------------
	void Text2DFactory::draw_rectDivGraph(RCVector2 pos1,RCVector2 pos2,RCVector2 pos3,RCVector2 pos4,int animeCnt)
	{
		GraphIterator it = this->graphTable.find( this->SetName );
		if( it != this->graphTable.end() )
			this->custom->DrawRectDepGraph(	pos1, pos2, pos3, pos4, animeCnt, (*it).second->GetTexturePointer() );
	}

	//---------------------------------------------------------
	//4点を決めて自分で分割描画
	//---------------------------------------------------------
	void Text2DFactory::draw_modiGraph(RCVector2 pos1,RCVector2 pos2,RCVector2 pos3,RCVector2 pos4,int num,int wnum,int hnum)
	{
		GraphIterator it = this->graphTable.find( this->SetName );
		if( it != this->graphTable.end() )
			this->custom->DrawVertexBufferIndexModi( (*it).second->GetTexturePointer(), pos1, pos2, pos3, pos4, num, wnum, hnum );
	}
	
	//---------------------------------------------------------
	//3点を決めて自分で分割描画(ガラス用)
	//---------------------------------------------------------
	void Text2DFactory::draw_TriangleGraph(RCVector2 pos1,RCVector2 pos2,RCVector2 pos3,int num,int wnum,int hnum,int wid,int hei,bool IsUp,IDirect3DTexture9* text)
	{
		this->custom->DrawIndexGlassHopper(	text, pos1, pos2, pos3, num, wnum, hnum, wid, hei,IsUp );
	}
		
	//---------------------------------------------------------
	//３Ｄの場所に描画
	//---------------------------------------------------------
	void Text2DFactory::draw_worldGraph()
	{
		GraphIterator it = this->graphTable.find( this->SetName);
		if( it != this->graphTable.end() )
			this->custom->DrawVertexGraph_3D( (*it).second->GetTexturePointer() );
	}

	//---------------------------------------------------------
	//テクスチャなしの描画
	//---------------------------------------------------------
	void Text2DFactory::draw_noTexture()
	{
		this->custom->DrawVertexWall();
	}

	//---------------------------------------------------------
	//アルファ設定
	//---------------------------------------------------------
	void Text2DFactory::SetAlpha(COLOR_BLEND_NUM mode,Vector4 wo)
	{
		unsigned int w = ((((int)wo.x) & 0xff) << 24) + ((((int)wo.y) & 0xff) << 16) + 
				((((int)wo.z) & 0xff) << 8) + ((((int)wo.w) & 0xff)); 
		this->custom->SetAlphaMode( mode, w );
	}

	//---------------------------------------------------------
	//文字列描画
	//---------------------------------------------------------
	void Text2DFactory::drawString2D(char* str,RCVector2 pos, float sc, float ang,const Vector4 color)
	{
		float sizeW = 0;
		D3DXVECTOR2 offSet = D3DXVECTOR2( pos.x, pos.y );
		unsigned int size = strlen(str);
		FontIterator it;
		UINT code;
		for(unsigned int i=0; i<size; i++){
			//文字が見つからないと生成
			code = this->GetCharCode(str, &i );

			if((it = this->fontTable.find( code )) == this->fontTable.end()){
				MyFont* ft = new MyFont(this->_devices, &code);
				if(ft->isOK()){
					this->fontTable.insert( FontTable::value_type( code, ft ) );
					it = this->fontTable.find( code );
				}
				else{
					delete ft;
					continue;
				}
			}

			//見つかればその文字で表示しますー
			//1文字表示が主です
			offSet.x += (*it).second->GetFont()->fontW * sc * 0.5f;
	
			this->custom->TransformW(offSet, D3DXVECTOR2( sc, sc), ang, (*it).second, &color);
			this->custom->DrawVertexBuffer( (*it).second );
			
			//その文字分場所をずらすー
			offSet.x += (*it).second->GetFont()->fontW * sc * 0.5f;
		}	
	}

	//---------------------------------------------------------
	//キャラコードの番号の取得
	//---------------------------------------------------------
	UINT Text2DFactory::GetCharCode( const char* ch, UINT* cnt )
	{
		UINT code = 0;
		//ユニコードなら文字コードは単純にワイド文字にのUINT変換
		#if _UNICODE
			code = (UINT)ch[*offSet];
		#else
			//マルチバイト文字の場合
			//１バイト文字のコードは１バイト目のUINT変換
			//２バイト文字のコードは[先導コード]* 256 + [文字コード]です
			if(::IsDBCSLeadByte(ch[*cnt])){
				code = (BYTE)ch[(*cnt)] << 8 | (BYTE)ch[(*cnt) + 1];
				(*cnt)++;
			}
			else{	
				code = ch[*cnt];
				
			}
		#endif
		
		return code;
	}
}

