#ifndef NanairoLib_DXDX_H
#define NanairoLib_DXDX_H
//各ソースで随時必要になるものをまとめたヘッダ
//-----------------------------------------------------------------

//DirectXのヘッダ
//---------------------
#define _USED_DIRECTX

#ifndef _D3D9_H_
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#endif
//---------------------

//typedef集
//以下の項目は名前を付けておく
//------------------------------------------------------------
//////////////////////////////////////////////////////////////
//DirectX使用するかどうか
#ifdef _USED_DIRECTX
typedef IDirect3DDevice9*		PDirectDevice;
typedef IDirect3DVertexBuffer9* PVertexBuffer;
typedef IDirect3DSurface9*		PSurface;
typedef IDirect3DTexture9*		PTexture;

typedef D3DXMATRIX		MATRIX;
typedef D3DXVECTOR2		VECTOR2;
typedef D3DXVECTOR3		VECTOR3;
typedef D3DXVECTOR4		VECTOR4;
typedef D3DXMATRIXA16	MATRIX16;

typedef D3DXMATRIX*		PMATRIX;
typedef D3DXVECTOR2*	PVECTOR2;
typedef D3DXVECTOR3*	PVECTOR3;
typedef D3DXVECTOR4*	PVECTOR4;
typedef D3DXMATRIXA16*	PMATRIX16;

typedef const D3DXMATRIX*		PCMATRIX;
typedef const D3DXVECTOR2*		PCVECTOR2;
typedef const D3DXVECTOR2&		RCVECTOR2;
typedef const D3DXVECTOR3*		PCVECTOR3;
typedef const D3DXVECTOR3&		RCVECTOR3;
typedef const D3DXVECTOR4*		PCVECTOR4;
typedef const D3DXVECTOR4&		RCVECTOR4;
typedef const D3DXMATRIXA16*	PCMATRIX16;
typedef const UINT*				PCUINT;
#else
#include <Windows.h>
typedef unsigned int			UINT;
typedef const UINT*				PCUINT;
#endif

typedef float*					PFLOAT;
typedef const int*				PCINT;
typedef const int				CINT;
typedef const float*			PCFLOAT;
//////////////////////////////////////////////////////////////
//------------------------------------------------------------

//DLLの使用はインポートかエクスポートか
//--------------------------------------------------------
//#define _IMPORT_DLL
#ifdef _IMPORT_DLL
#define __IMPOETER __declspec(dllimport)
#else
#define __IMPOETER __declspec(dllexport)
#endif
//---------------------------------------------------------

//-------------------------------------------------------------------
//ここを宣言するかによって固定パイプラインかシェーダに分けられる
//#define D3D9_DRAWER
//-------------------------------------------------------------------
#ifdef D3D9_DRAWER
	#define NO_SHADER	0 
#else
	#define SHADER_DRAWER

	#define SHADER_TECH_				"Default_Tech"
	#define SHADER_MATRIX_WORLD_		"matWorld"
	#define SHADER_MATRIX_VIEW_			"matView"
	#define SHADER_MATRIX_PROJ_			"matProjection"
	#define SHADER_MATERIAL_			"sd_material"
	#define SHADER_TEX_ABLE_			"sd_textureRendering"
	#define	SHADER_TEX1_				"sd_texture"
	#define SHADER_LIGHTING_ABLE_		"sd_lighting"		
	#define SHADER_LIGHT_DIR_			"sd_dirLight"
	#define SHADER_LIGHT_DIR_DIFFUSE_	"sd_dirLight_diffuse"
	#define SHADER_LIGHT_DIR_AMBIENT_	"sd_dirLight_ambient"
	#define SHADER_LIGHT_DIR_SPECULAR_	"sd_dirLightSpecular"
#endif

namespace NanairoLib
{
	//---------------------------------------------------
	//簡単ラジアン角.角度変換
	//---------------------------------------------------
	const float PI		= 3.1415926535897932f;

	#define SET_PI(ang)		ang * PI / 180.0f
	#define BACK_PI(ang)	ang * 180.0f / PI	

	//---------------------------------------------------
	//前方クリッピング・後方クリッピング・画角の指定
	//---------------------------------------------------
	#define NEERDIS							1.0f
	#define TALLDIS							1000.0f
	#define GAKAKUS							45.0f
	#define GAKAKU							SET_PI(45.0f)
	#define MAXCOLOR						255
	#define CHANGE_INTERVALCOLOR(interval)	(MAXCOLOR/interval)	

	//---------------------------------------------------
	//画面の幅・高さ
	//---------------------------------------------------
	#define SCRW			800
	#define SCRH			600
	#define SCRW_PERCENT(x)	SCRW * x
	#define SCRH_PERCENT(x)	SCRH * x

	#define RAD_ONE_OUARTER		1.57f
	#define RAD_TWO_OUARTER		3.14f
	#define RAD_THREE_OUARTER	4.71f
	#define RAD_FOURS_OUARTER	6.28f

	//------------------------------------------------------------------------
	//グラフィックモード
	//------------------------------------------------------------------------
	enum _SETTING_SCALE
	{
		GRAPH_SCALE, DIV_SCALE, DIRECT_SCALE,
	};

	//------------------------------------------------------------------------
	//ブレンドタイプ
	//------------------------------------------------------------------------
	enum COLOR_BLEND_NUM
	{
		BNONE, BLEND_ALPHA1, BLEND_ADD1, BLEND_ALPHA2, BLEND_FACTOR1, BLEND_FACTOR2, BLEND_SUB1,
		BLEND_COLORADD1, BLEND_ALPHA3, BLEND_SUB2, BLEND_BLACK, BLEND_SUB3, BLEND_BLACK2 
	};

	//---------------------------------------------------
	//その他もろもろ
	//---------------------------------------------------
	#define CHANGE_HALF(x)					(int)(x * 0.5f)	
	#define CHANGE_HALF_LIFE(x,y)			(int)(x * y)
	#define CHECK_SAMER(x,y)				(x == y)
	#define CHECK_BIGGER(x,y)				(x != y && x > y)			
	#define CHECK_SMALLER(x,y)				(x != y && x < y)
	#define INCREMENT_SPECIAL(point, max)	( ( point + 1 ) % max )
	#define DECREMENT_SPECIAL(point, max)	( ( point + (max - 1) ) % max )
	#define CHECK_NULL(x)					( x == NULL )
	#define CHECK_ZERO(x)					( x == 0 )
	#define CHECK_EQUAL(x, y)				(x == y)

	//---------------------------------------------------
	//app名前
	//---------------------------------------------------
	#define appName "This is DirectXGames"

	//---------------------------------------------------
	//簡単メモリデリート・リリース
	//---------------------------------------------------
	#define ES_SAFE_ADDREF(val)						if ( (val) != NULL ) { (val)->AddRef(); }
	#define ES_SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }
	#define ES_SAFE_DELETE(val)						if ( (val) != NULL ) { delete (val); (val) = NULL; }
	#define ES_SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }

}

#endif