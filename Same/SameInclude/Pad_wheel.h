#ifndef MYDIERCTX_WHEEL_H
#define MYDIERCTX_WHEEL_H

namespace NanairoLib
{
	///360用アナログ入力を得る
	///@param analogX X入力を得る
	///@param analogY Y入力を得る
	///@param ltrigger 左トリガ入力を得る
	///@param rtrigger 右トリガ入力を得る
	///@param inputType いつものパッド番号
	///@note ホイールと通常のゲームパッドではアナログ入力の度合いがかなり違う。
	///ホイールはパッドの反応の半分以下くらいの感覚でいい
	__IMPOETER extern int GetJoypadAnalogInput360( int* analogX, int* analogY,int* ltrigger, int* rtrigger, int inputType ) ;			// ジョイパッドのアナログ的なスティック入力情報を得る

	///LRトリガーの値を取得します。
	///@param left Lトリガー値(0～255)
	///@param right Rトリガー値(0～255)
	///@param inputtype いつものパッド番号
	__IMPOETER extern	int GetJoypadAnalogInputTrigger(int* left,int* right,int inputType);
	__IMPOETER extern	int	KeyboradBufferProcess( void ) ;											// キーボードのバッファからデータを取得する処理
	__IMPOETER extern	int GetJoypadGUID( int PadIndex, GUID *GuidBuffer ) ;						// ジョイパッドのＧＵIＤを得る
	__IMPOETER extern	int	ConvertKeyCodeToVirtualKey( int KeyCode ) ;								// ＤＸライブラリのキーコードから Windows の仮想キーコードを取得する
	__IMPOETER extern	int	SetJoypadInputToKeyInput( int InputType, int PadInput, int KeyInput1, int KeyInput2 = -1 , int KeyInput3 = -1 , int KeyInput4 = -1  ) ; // ジョイパッドの入力に対応したキーボードの入力を設定する
	__IMPOETER extern	int SetJoypadDeadZone( int InputType, double Zone ) ;						// ジョイパッドの無効ゾーンの設定を行う
	__IMPOETER extern	int	StartJoypadVibration( int InputType, int Power, int Time ) ;// ジョイパッドの振動を開始する
	__IMPOETER extern	int	StartJoypadVibration360( int InputType, int Power) ;

	///360ホイールコントローラかどうかを取得する
	///360コントローラは通常のゲームパッドやホイールコントローラ等あり、
	///反応具合がぜんぜん違うため、あらかじめ取得しておいて違いを吸収する必要があるのかもしれない。
	///@param inputType いつものパッド番号
	///@retval true ホイールコントローラである
	///@retval false それ以外
	__IMPOETER extern bool Is360WheelControler(int inputType);

	///振動させる
	///@param InputType いつものパッド番号
	///@param PowerL 低周波モータ
	///@param PowerR 高周波モータ
	///@note 振動に関して、高周波と低周波はホイールハンドル時には、マニュアルと逆になっているっぽい
	///つまり、左が高周波、右が低周波になっているようだ。ホイールハンドルデバイスは振動も控えめに
	///なってしまうようだ
	__IMPOETER extern	int StartJoypadVibration360( int InputType, int PowerL,int PowerR) ;
	//extern	int			StopJoypadVibration( int InputType ) ;	// ジョイパッドの振動を停止する
	__IMPOETER extern	int StopJoypadVibration360(int inputType);
	__IMPOETER extern	int GetJoypadPOVState( int InputType, int POVNumber ) ;						// ジョイパッドのＰＯＶ入力の状態を得る( 単位は角度の１００倍  中心位置にある場合は -1 が返る )
	__IMPOETER extern	int GetJoypadName( int InputType, char *InstanceNameBuffer, char *ProductNameBuffer ) ;	// ジョイパッドのデバイス登録名と製品登録名を取得する
	__IMPOETER extern	int ReSetupJoypad( void ) ;													// ジョイパッドの再セットアップを行う( 新たに接続されたジョイパッドがある場合に検出される )

}

#endif