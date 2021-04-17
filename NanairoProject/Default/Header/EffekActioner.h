#ifndef MYGAME_EFFEKACTIONER_H
#define MYGAME_EFFEKACTIONER_H
//------------------------------------------------------------------------------
//エフェクシアを制御する単体クラス
//------------------------------------------------------------------------------
#ifndef NanairoLib_EFFEKCLASS_H
#include <EffekseerFactory.h>
#endif

namespace MYGAME
{
	//-----------------------------------------------------------------------------
	//エフェクト単体クラス
	//(エフェクトクラスに１つ保持させる)
	//１つのエフェクトを管理するクラス
	//簡易用に制作
	//-----------------------------------------------------------------------------
	class EffekActioner
	{
	private:
		//**************************************************************************
		bool drawEna,updateEna,moveFlag, delFlag;				//描画有無、更新有無
		short animationCnt, AxisMode;							//アニメカウンタ、クォータニオンモード
		NanairoLib::Vector3 pos, rota, scale, Axis;				//位置、角度、拡縮、任意軸
		Effekseer::Handle handle;								//エフェクトハンドル
		LPSTR effName;

	public:
		//**************************************************************************
																		
		EffekActioner(LPCSTR name);
		EffekActioner(LPCSTR name, NanairoLib::PCVector3 pos, NanairoLib::PCVector3 rota, NanairoLib::PCVector3 scale);		
		~EffekActioner();
		void DeleteOBJ();
		void SameInit();
		//**************************************************************************
	
		//各フィールドの代入
		void SetPosi(NanairoLib::PCVector3 pos);
		void SetRota(NanairoLib::PCVector3 rota);
		void SetScale(NanairoLib::PCVector3 scale);
		NanairoLib::PVector3 GetPosi() const;
		NanairoLib::PVector3 GetAngle() const;
		NanairoLib::PVector3 GetScale() const;

		//**************************************************************************

		//エフェクトの操作
		void EfekPlay();
		void EfekStop();
		bool IsPlaying();
		void ChangeUpdateEnable(bool isUpdate);
		void ChangeDrawsEnable(bool isDraw);

		//**************************************************************************
	
		//エフェクトの更新
		void ChangePosAngSclEffect();
		void EfekObjectUpdate();
	
		//**************************************************************************
	
	};

}
#endif