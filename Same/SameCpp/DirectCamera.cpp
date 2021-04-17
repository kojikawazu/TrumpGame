#pragma once
//-----------------------------------------------
//カメラだね～
//-----------------------------------------------
#include <DirectCamera.h>
#include <DirectFunctionPlus.h>

namespace NanairoLib
{
	//ビューのモード
	//ビューは全部で５つ
	#define CAMERAVIEWSUM	5						

	//ビュー値デフォルト設定
	const float viewArtisan[5][6] = 
	{
		{0.0f, 0.0f, 0.0f, 1000.0f, 100.0f, 360.0f},
		{0.0f, 0.0f, 0.0f,  800.0f,   0.0f,   0.0f},
		{0.0f, 0.0f, 0.0f,  500.0f,   0.0f,   0.0f},
		{0.0f, 0.0f, 0.0f, 7000.0f,3000.0f, 360.0f},
		{0.0f, 0.0f, 0.0f,    0.1f,7000.0f, 360.0f},
	};

	//-------------------------------------------------------------------------------
	//関数ポインタ
	void CAMERA::Camera_keyCheck(PDirectDevice Device,PCKEYS keys)
	{
		(this->*key_action)(Device, keys);	
	}

	#pragma region カメラのコンストラクタ
	//@in : カメラ番号
	inline CAMERA::CAMERA(int cameraNum) : 
				zoom(-500.0f) , cameraUp(100.0f) , cameraAngle(0.0f) , cameraNum(cameraNum) , cameraViewMode(0)
	{
		tarGet				= D3DXVECTOR3(0.0,    0.0f,   0.0f);
		up					= D3DXVECTOR3(0.0f,   1.0f,   0.0f);
		eye					= D3DXVECTOR3(0.0f, 100.0f, 500.0f);
		cameraMatrix		= D3DXMATRIX();

		this->DefaultChange();
		this->key_action = &CAMERA::Keyof_CameraChange;
	}

	//すべての初期化
	inline void CAMERA::ZeroInit()
	{
		this->eye		= D3DXVECTOR3(0.0f,0.0f,0.0f);
		this->tarGet	= D3DXVECTOR3(0.0f,1.0f,0.0f);
		this->up		= D3DXVECTOR3(0.0f,0.0f,500.0f);
		cameramoveFlag = false;
		this->zoom = this->cameraUp = this->cameraAngle = 0.0f;
		cameranooupFlag = cameraViewMode = 0;

		zoom = -500.0f;
		cameraUp = 100.0f;

		this->key_action = &CAMERA::Keyof_CameraChange;
	}
	
	inline CAMERA::~CAMERA(){}
	#pragma endregion

	//--------------------------------------------------------------
	//カメラの直接設定
	//--------------------------------------------------------------
	//@in : 視点ベクトル
	//@in : 注視点ベクトル
	//@in : 上方向ベクトル
	void CAMERA::Seting_Camera(PCVECTOR3 e,PCVECTOR3 t,PCVECTOR3 u)
	{
		this->eye = (*e);	this->tarGet = (*t);	this->up = (*u);
	}
	
	#pragma region フィールドの取得(見るだけしかできない)
	//視点のセット
	PCVector3 CAMERA::GetEYE(){		return &eye;		}
		
	//ターゲットのセット
	PCVector3 CAMERA::GetTARGET(){		return &tarGet;	}

	//上方向のセット
	PCVector3 CAMERA::GetUP(){			return &up;	}

	//カメラ行列の取得
	PCMATRIX CAMERA::GetViewMatrix(){	return &this->cameraMatrix;	}

	//カメラ↑率の取得
	PCFLOAT		CAMERA::GetCameraUp(){			return &this->cameraUp;			}
	PCMATRIX	CAMERA::GetBillboardMatrix(){	return &this->billboardMatrix;	}
	#pragma endregion

	//--------------------------------------------------------
	//内部でカメラの弄り
	//ターゲットからどれだけzoom(離れて)いるか
	//ターゲットからどれだけcameraUp(見下ろして)いるか
	//ターゲットからどれだけcameraAngle(角度ついて)いるか
	//--------------------------------------------------------
	void CAMERA::DefaultChange()
	{
		this->eye.x = tarGet.x + (sin(this->cameraAngle) * this->zoom);
		this->eye.y = tarGet.y + this->cameraUp;
		this->eye.z = tarGet.z + (cos(this->cameraAngle) * this->zoom);
	}
	
	//--------------------------------------------------------------------------------
	//プレイ中に変えたい時のセットカメラ
	//--------------------------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : 注視点
	//@in : 角度
	//@in : モード 1(普通の角度) 2(ラジアン角) 3(普通の角度加算)
	void CAMERA::SetPlayerCamera(PDirectDevice Device,PCVECTOR3 t,float angle,CAMERA_ANGLEMODE mode)
	{
		//ビューモード３以上は無効
		if(this->cameraViewMode > 2)	return ;

		this->tarGet = (*t);

		switch(mode)
		{
			case CAMERAANGLE_NORMAL:	this->cameraAngle = (SET_PI(angle));	break;
			case CAMERAANGLE_DIRECTION:	this->cameraAngle = angle;				break;
			case CAMERAANGLE_PLUSANGLE:	this->cameraAngle += (SET_PI(angle));	break;
		}	

		this->DefaultChange();
	}
	
	//--------------------------------------------------------------------------
	//最初や切り替えに変えたい時のセットカメラ
	//--------------------------------------------------------------------------
	//@in : 注視点
	//@in : ズーム値
	//@in : 角度
	//@in : アップ値
	//@in : 1(角度直代入) それ以外(ラジアン角)
	void CAMERA::Seting_CameraS(PCVECTOR3 e,float zo,float ang,float up, bool IsDirectAngle)
	{
		this->tarGet = (*e);

		this->zoom = zo;
		this->cameraUp = up;
		this->cameraAngle = ( IsDirectAngle ? SET_PI(ang) : ang );

		this->DefaultChange();
	}
	
	//-----------------------------------------------------------
	//プレイヤーの正面視点に切り替え
	//-----------------------------------------------------------
	//@in : 正面の角度
	void CAMERA::ChangePlayerCameraFrontLine(float flontang)
	{
		if(this->cameraViewMode > 2)	return ;
		this->frontAng = flontang;	//向かせたい角度が入ってくる
		this->cameraFrontMode = 1;	//正面むかせるモード発動！

		this->key_action = &CAMERA::ChangeFrontLine;
	}
	
	//--------------------------------------------------------------
	//プレイヤーの正面切り替え
	//--------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : キークラス
	void CAMERA::ChangeFrontLine(PDirectDevice Device,PCKEYS keys)
	{
		VectorFunc vec3D;

		//正面のベクトル
		Vector2 vecA = Vector2(1.0f * sin(this->frontAng), 1.0f * cos(this->frontAng));

		//注視点から視点へのベクトル
		Vector2 vecB = vec3D.GetNormal(vec3D.GetVecDistance(vec3D.GetVectorXZ(this->eye), vec3D.GetVectorXZ(this->tarGet)));

		//B × A
		float ang = vec3D.GetCloss(vecB, vecA);
		
		//角度出る
		ang = vec3D.ChangeAngle(ang, 2);

		//(←)向いてたら(→)へ
		if(ang > 0.1f)			this->cameraAngle -= SET_PI(10.0f);
		//(→)向いてたら(←)へ
		else if(ang < -0.1f)	this->cameraAngle += SET_PI(10.0f);
		//正面だったら終了フラグ
		else
		{
			this->cameraFrontMode = 0;
			this->key_action = &CAMERA::Keyof_CameraChange;
		}
	}

	//----------------------------------------------------------------
	//カメラチェンジアクション
	//----------------------------------------------------------------
	//@in : デバイス
	//@in : キー
	void CAMERA::Keyof_CameraChange(PDirectDevice Device, PCKEYS keys)
	{
		bool hantei = false;
		//カメラキー操作ありだったら
		//２以下はあり！
		
		//左向きたい
		if(keys->GetKey()->push[KQ] || keys->GetXPad(this->cameraNum - 1)->ranalogX < -10000)
		{
			hantei = true;
			this->cameraAngle += SET_PI(0.5f);
		}
		//右向きたい
		else if(keys->GetKey()->push[KA] || keys->GetXPad(this->cameraNum - 1)->ranalogX > 10000)
		{
			hantei = true;
			this->cameraAngle -= SET_PI(0.5f);
		}

		//見下ろしたい
		if(keys->GetKey()->push[KW] || keys->GetXPad(this->cameraNum - 1)->ranalogY > 10000)
		{
			hantei = true;
			this->cameraUp += 3.0f;
		}
		//見上げたい
		else if(keys->GetKey()->push[KS] || keys->GetXPad(this->cameraNum - 1)->ranalogY < -10000)
		{
			//見上げてＯＫなら
			if(this->cameranooupFlag == 0)
			{
				hantei = true;
				this->cameraUp -= 3.0f;
			}
			//だめならできない
			else	this->cameranooupFlag = 0;
		}
	
		//ズームインしたい
		if(keys->GetKey()->push[KE])
		{
			hantei = true;
			this->zoom += 3.0f;
		}
		//ズームアウトしたい
		else if(keys->GetKey()->push[KD])
		{
			hantei = true;
			this->zoom -= 3.0f;
		}

		//カメラのビュー切り替えたい
		if( (keys->GetKey()->trg[KP] ||
			(keys->GetXPad(this->cameraNum - 1)->trg[PADBACK])) )
		{
			this->ChangeCameraVIEWMODE(Device, this->cameraViewMode + 1);
			hantei = true;
		}

		//動きがあったらカメラのセットチェンジ
		if(this->cameramoveFlag = hantei)
			this->DefaultChange();
	
	}
	
	//-----------------------------------------------------
	//カメラの更新
	//-----------------------------------------------------
	//@in : DirectX用デバイス
	D3DXMATRIX CAMERA::CameraUpdate(PDirectDevice Device)
	{
		Direct3DFunc func;
		this->cameraMatrix = func.SetCamera(Device, eye, tarGet, up);

		//ビルボード計算--------------------------------------------------
		D3DXMATRIX mat;  
		D3DXMatrixLookAtLH(&mat, &tarGet.SetD3DVector3(), &tarGet.SetD3DVector3(), &tarGet.SetD3DVector3() );
		D3DXMatrixInverse( &this->billboardMatrix, NULL, &mat );
		//----------------------------------------------------------------

		return this->cameraMatrix;
	}
	
	//--------------------------------------------------------------
	//ビュー切り替え
	//--------------------------------------------------------------
	//@in : DirectX用デバイス
	//@in : モード
	void CAMERA::ChangeCameraVIEWMODE(PDirectDevice Device,int cameraviewMode){
		this->cameraViewMode = cameraviewMode;
		switch(cameraviewMode + 1)
		{
			case CAMERA_VIEWBACK:	//元に戻す
			case CAMERA_VIEW:	//フィールドを映す
			case CAMERA_VIEWUP:	//真上から眺める
				this->tarGet = D3DXVECTOR3(viewArtisan[cameraviewMode][0],viewArtisan[cameraviewMode][1], viewArtisan[cameraviewMode][2]);
				zoom = viewArtisan[cameraviewMode][3];
				cameraUp = viewArtisan[cameraviewMode][4];
				cameraAngle = SET_PI(viewArtisan[cameraviewMode][5]);
				break;
			case CAMERA_VIEWZOOMS:	//ややズーム
			case CAMERA_VIEWZOOML:	//めっちゃズーム
				zoom = viewArtisan[cameraviewMode][3];
				break;
		}

		this->DefaultChange();
		this->key_action = (cameraviewMode >= CAMERA_VIEWZOOML ? &CAMERA::CameraVIEWMODE : &CAMERA::Keyof_CameraChange);
	}

	//-------------------------------------------------------------
	//ビューでアクションおこしたい時に実行
	//-------------------------------------------------------------
	void CAMERA::CameraVIEWMODE(PDirectDevice Device,PCKEYS keys)
	{
		switch(this->cameraViewMode+1)
		{
			case CAMERA_VIEW:	//フィールド眺め くるくる回したいっ
				cameraAngle += SET_PI(1.0f);
				this->cameramoveFlag = true;
				break;
		}
		
		this->DefaultChange();

		//カメラのビュー変更したいかっ
		if( (keys->GetKey()->trg[KP] ||
			(keys->GetXPad(this->cameraNum - 1)->trg[PADBACK])) )
			this->ChangeCameraVIEWMODE(Device, (this->cameraViewMode + 1) % CAMERAVIEWSUM);
	}
	
	//------------------------------------------------
	//ターゲットごとスクロール
	//------------------------------------------------
	void CAMERA::tarGetScroll(float speed, int mode)
	{
		switch(mode + 1){
			//x増やす
			case CAMERA_TARGETX:	this->tarGet.x += speed;	break;
			//y増やす
			case CAMERA_TARGETY:	this->tarGet.y += speed;	break;
			//z増やす
			case CAMERA_TARGETZ:	this->tarGet.z += speed;	break;
		}
	}
}