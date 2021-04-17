#ifndef RESOURCE_FUNCTION_H
#define RESOURCE_FUNCTION_H

//-----------------------------------------
//割り当て型関数クラスをここに記載
//必要な関数を増やしたり使いたい時はここのクラスを使うっ
//※データ保持が必要な場合はこのクラスには入れることはできません＞＜
//-----------------------------------------
#ifndef NanairoLib_FUNC_H
#include <DirectFunction.h>
#endif

namespace NanairoLib
{
	//テクスチャ構造体
	typedef struct TEXTUREHH
	{
		//使用中、分割中
		bool used, division;
		//幅、高さ、横合計、縦合計
		int width, height, sumX, sumY, oneW, oneH;
		//テクスチャ
		IDirect3DTexture9* graph;
	}TEXTUREH;

	//モデル構造体
	typedef struct MODELHH
	{
		bool used;
		int atackNumber;
		int matelSum;
		ID3DXMesh *mesh;
		D3DMATERIAL9 *matel;
		IDirect3DTexture9 **textureX;
	}MODELH;

	//当たり判定構造体
	typedef struct MODELATACKH
	{
		bool		used;
		int			meshIndex[2000][3];
		DWORD		meshSum;
		DWORD		vertexSum;
		D3DXVECTOR3 meshVertex[1000];
		D3DXVECTOR3 meshNormal[1000];
	}ATACKH;

	//フォント構造体
	typedef struct MYFONT
	{
		int fontW,fontH;
		IDirect3DTexture9* fontText;	
	}FONTH;

	//標準頂点シェーダ構造体
	typedef struct COSTOMVERTEX_2D
	{
		float x,y,z;					//頂点座標
		float rhw;						//除算
		DWORD dwColor;					//頂点の色
		float u,v;						//テクスチャ座標
	}ArtisanVT_2D;

	typedef struct COSTOMVERTEX_3D
	{
		float x,y,z;					//頂点座標
		float norX, norY, norZ;			//法線情報
		DWORD dwColor;					//頂点の色
		float u,v;						//テクスチャ座標
	}ArtisanVT_3D;

	typedef MODELH*					PMODELH;
	typedef const MODELH*			PCMODELH;
	typedef TEXTUREH*				PTEXTUREH;
	typedef const TEXTUREH*			PCTEXTUREH;
	typedef const ATACKH*			PCATACKH;
	typedef ATACKH*					PATACKH;

	typedef FONTH*					PFONTH;
	typedef ArtisanVT_2D*			PArtisanVT_2D;
	typedef ArtisanVT_3D*			PArtisanVT_3D;

	//------------------------------------------------------------------
	//テクスチャやモデルのロードを扱うメソッドをここに
	//------------------------------------------------------------------
	class TextFunc
	{
	public:
		//--------------------------------------------
		//テクスチャのロード
		//画像をテクスチャとして読み込む
		//--------------------------------------------
		//@in : DirectXのデバイス
		//@inout : テクスチャの構造体
		//@in : ファイル名
		//@in : 画像の幅
		//@in : 画像の高さ
		//@in : (分割するとき)画像の横に並ぶ数
		//@in : (分割するとき)画像の縦に並ぶ数
		//@out : 失敗すると(-1) 成功すると(1)
		__IMPOETER int LoadGraphIndex(PDirectDevice Device,PTEXTUREH text,LPCSTR fileName,int width,int height,int sumW = 0,int sumH = 0);
		
		//--------------------------------------------
		//画像を非同期読み込みする
		//--------------------------------------------
		//@in : DirectXのデバイス
		//@inout : テクスチャの構造体
		//@in : 読み込む開始位置
		//@in : 読み込むサイズ
		//@out : 失敗(-1) 成功(1)
		__IMPOETER int LoadGraphIndexASYN(PDirectDevice Device,PTEXTUREH text,LPCSTR point,CINT size);
		
		//--------------------------------------------
		//モデルのロード
		//--------------------------------------------
		//@in : DirectX用デバイス
		//@in : ファイル名
		//@out : モデル保存クラス
		//@in : 保存番号
		//@out : true(成功) false(失敗)
		__IMPOETER bool LoadModel3D(PDirectDevice Device,LPCSTR fileName,MODELH *model,int mode = 0);
		
		//--------------------------------------------
		//非同期用モデルのロード
		//--------------------------------------------
		//@in: DirectX用デバイス
		//@in : アドレスポインタ
		//@in : データサイズ
		//@inout : モデルデータ
		//@in : ウィンドウクラス
		//@in : 0(アンビエント = ディフューズ)
		//@out : 1(成功) -1(失敗)
		__IMPOETER int LoadModel3DASYN(PDirectDevice Device,LPCSTR point,int size,PMODELH model,HWND wnd,int mode);
		
		//--------------------------------------------
		//当たり判定用モデルのロード
		//--------------------------------------------
		//@in : DirectX用デバイス
		//@in : ファイルパス
		//@input : あたり判定用モデルデータクラス
		//@out : true(成功) false(失敗)
		__IMPOETER bool LoadModelAtack(PDirectDevice Device,LPCSTR fileName,PATACKH atack);

		//--------------------------------------------
		//非同期用当たり判定のロード
		//--------------------------------------------
		//@in : DirectX用デバイス
		//@in : ファイルパス
		//@in : サイズ
		//@out : あたり判定用データクラス
		//@in : ウィンドウクラス
		//@out : 1(成功) -1(失敗)
		__IMPOETER int LoadModelAtackASYN(PDirectDevice Device,LPCSTR point,int size,PATACKH atack,HWND wnd);
			
		//-----------------------------------------------------------
		//テクスチャから幅と高さを取得
		//-----------------------------------------------------------
		//@in : テクスチャインターフェイス
		//@out : 幅
		//@out : 高さ
		__IMPOETER void SetTextureLong(IDirect3DTexture9* gh, int* wh, int* ht);
			

		//デフォルトコンストラクタ
		__IMPOETER TextFunc();
		//デフォルトデストラクタ
		__IMPOETER ~TextFunc();
	};

}

#endif