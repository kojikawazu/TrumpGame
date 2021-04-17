#ifndef NanairoLib_CAMERA_H
#define NanairoLib_CAMERA_H

//------------------------------------------------------
//
//カメラを取り扱うクラス
//
//------------------------------------------------------
#ifndef NanairoLib_FUNC_H
#include <DirectFunction.h>
#endif

#ifndef NanairoLib_KEYS_H
#include <Directkey.h>
#endif

namespace NanairoLib
{
	enum CAMERA_ANGLEMODE
	{
		CAMERAANGLE_NONE, CAMERAANGLE_NORMAL, CAMERAANGLE_DIRECTION, CAMERAANGLE_PLUSANGLE
	};

	enum CAMERA_TARGET_SCROLL
	{
		CAMERA_TARGETNONE, CAMERA_TARGETX, CAMERA_TARGETY, CAMERA_TARGETZ
	};

	enum CAMERA_VIEWMODE
	{
		CAMERA_VIEWNONE, CAMERA_VIEWBACK, CAMERA_VIEWZOOMS, CAMERA_VIEWZOOML, CAMERA_VIEW, CAMERA_VIEWUP
	};

	//-------------
	//前方宣言
	//-------------
	class KEYS;
	class Vector3;

	//-----------------------
	//基本カメラクラス
	//-----------------------
	class SuperCamera
	{
		protected:
			float zoom, cameraAngle, cameraUp, flontAng;
			Vector3 eye, tarGet, up;
			MATRIX cameraMatrix, billboardMatrix;

		public:
			//デフォルトカメラ変換
			//__IMPOETER void			defaultChange();

			//カメラの更新
			//__IMPOETER D3DXMATRIX	cameraUpdate(PDirectDevice Device);
	};

	//--------------------------------------------
	//DirectXカメラクラス
	//--------------------------------------------
	class CAMERA
	{
		private:
		//-------------------------------------------------
			bool  cameramoveFlag;
			short cameraFrontMode, cameraNum, cameraViewMode;			//カメラ正面モード, カメラ番号、カメラビューモード
			short cameranooupFlag;						//カメラ動かしたフラグ,カメラ見上げフラグ
			float zoom, cameraAngle, cameraUp, frontAng;				//ズーム率、カメラ角度、カメラアップ、注視点角度
			Vector3 eye, tarGet, up;									//視点,注視点,上方向
			MATRIX cameraMatrix,billboardMatrix;						//ビュー行列、ビルボード行列
			
		public:	//よく使うメソッド
			//-----------------------------------------------------------------------
			//キーチェック
			//-----------------------------------------------------------------------
			__IMPOETER void			Camera_keyCheck(PDirectDevice Device,PCKEYS keys);

			//--------------------------------------
			//デフォルトカメラ変換
			//--------------------------------------
			__IMPOETER void			DefaultChange();

			//-----------------------------------------------------
			//カメラの更新
			//-----------------------------------------------------
			//@in : DirectX用デバイス
			__IMPOETER D3DXMATRIX	CameraUpdate(PDirectDevice Device);

			//------------------------------------------------
			//ﾃﾞｺﾝ系
			//------------------------------------------------
			__IMPOETER			CAMERA(){}
			__IMPOETER			CAMERA(int cameraNum);
			__IMPOETER			~CAMERA();
			__IMPOETER void 		ZeroInit();
		
			//------------------------------------------------
			//取得系(読み取り専用)
			//------------------------------------------------
			__IMPOETER PCVector3	GetEYE();
			__IMPOETER PCVector3	GetTARGET();
			__IMPOETER PCVector3	GetUP();
			__IMPOETER PCMATRIX		GetViewMatrix();
			__IMPOETER PCFLOAT		GetCameraUp();
			__IMPOETER PCMATRIX		GetBillboardMatrix();

			//-----------------------------------------------------------
			//プレイヤーの正面視点に切り替え
			//-----------------------------------------------------------
			//@in : 正面の角度
			__IMPOETER void ChangePlayerCameraFrontLine(float flontang);
		
			//--------------------------------------------------------------
			//カメラの直接設定
			//--------------------------------------------------------------
			//@in : 視点ベクトル
			//@in : 注視点ベクトル
			//@in : 上方向ベクトル
			__IMPOETER void Seting_Camera(PCVECTOR3 e,PCVECTOR3 t,PCVECTOR3 u);
		
			//--------------------------------------------------------------------------------
			//プレイ中に変えたい時のセットカメラ
			//--------------------------------------------------------------------------------
			//@in : DirectX用デバイス
			//@in : 注視点
			//@in : 角度
			//@in : モード 1(普通の角度) 2(ラジアン角) 3(普通の角度加算)
			__IMPOETER void SetPlayerCamera(PDirectDevice Device,PCVECTOR3 t,float angle = 0.0f,CAMERA_ANGLEMODE mode = CAMERAANGLE_NONE);
		
			//--------------------------------------------------------------------------
			//最初や切り替えに変えたい時のセットカメラ
			//--------------------------------------------------------------------------
			//@in : 注視点
			//@in : ズーム値
			//@in : 角度
			//@in : アップ値
			//@in : 1(角度直代入) それ以外(ラジアン角)
			__IMPOETER void Seting_CameraS(PCVECTOR3 e,float zo,float ang,float up, bool IsDirectAngle = false);

			//------------------------------------------------
			//ターゲットごとスクロール
			//------------------------------------------------
			//0 : x, 1 : y, 2 : z
			__IMPOETER void tarGetScroll(float speed, int mode);

		private:	//内部のみ
			void (CAMERA::*key_action)(PDirectDevice Device,PCKEYS keys);
			
			//関数ポインタに割り当てるのが以下３つ
			
			//----------------------------------------------------------------
			//カメラチェンジアクション
			//キー判定でカメラを動かす
			//----------------------------------------------------------------
			//@in : デバイス
			//@in : キー
			__IMPOETER void	Keyof_CameraChange(PDirectDevice Device,PCKEYS keys);
			
			//--------------------------------------------------------------
			//プレイヤーの正面切り替え
			//--------------------------------------------------------------
			//@in : DirectX用デバイス
			//@in : キークラス
			__IMPOETER void ChangeFrontLine(PDirectDevice Device,PCKEYS keys);

			//-------------------------------------------------------------
			//ビューでアクションおこしたい時に実行
			//-------------------------------------------------------------
			__IMPOETER void CameraVIEWMODE(PDirectDevice Device,PCKEYS keys);
			
			//--------------------------------------------------------------
			//ビュー切り替え
			//--------------------------------------------------------------
			//@in : DirectX用デバイス
			//@in : モード
			__IMPOETER void ChangeCameraVIEWMODE(PDirectDevice Device,int cameraviewMode);
	};

	typedef CAMERA*			PCAMERA;
	typedef const CAMERA*	PCCAMERA;

}
#endif