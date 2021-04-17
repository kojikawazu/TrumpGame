#ifndef MYDXCHARA_H
#define MYDXCHARA_H

#ifndef MYDIRECTX_LIGHTCOLOR_H
#include <DirectLight.h>
#endif

namespace NanairoLib
{
	//�O���錾
	class Textcolor;
	class NormalObject;
	class UIParts2D;
	class Chara3D;
	class Effect2D;

	///////////////////////////////////////////////////////////////////////////////
	//typedef
	typedef NormalObject& RNormalObject;
	typedef NormalObject* PNormalObject;
	typedef const PNormalObject PCNormalObject;
	
	typedef UIParts2D& RUIParts2D;
	typedef UIParts2D* PUIParts2D;
	typedef const PUIParts2D PCUIParts2D;

	typedef Chara3D& RChara3D;
	typedef Chara3D* PChara3D;
	typedef const PChara3D PCChara3D;

	typedef Effect2D& REffect2D;
	typedef Effect2D* PEffect2D;
	typedef const PEffect2D PCEffect2D;

	//---------------------------
	//��{�I�u�W�F�N�g�N���X
	//������p�����Ĉ���
	//---------------------------
	class NormalObject
	{
	protected:
		bool delFlag;
		int frameCnt;

	public:
		//Constracter
		__IMPOETER NormalObject() : delFlag(false), frameCnt(0){}
		__IMPOETER virtual ~NormalObject(){}
		
		//Isser
		__IMPOETER bool isDel(){			return this->delFlag;			}
		
		//Setter
		__IMPOETER void OnDel(bool isOn){	this->delFlag = isOn;	}
		
		//Increment
		__IMPOETER void Increment_repeat(int& count, int sum){			count = ((count + 1) % sum);				}
		__IMPOETER bool Increment(int& count, int inter, int spd = 1){	return ((count += spd) >= inter);			}
		__IMPOETER bool IncrementFrameCnt(int inter, int spd = 1){		return ((this->frameCnt += spd) >= inter);	}
		__IMPOETER bool DecrementFrameCnt(int inter, int spd = 1){		return ((this->frameCnt -= spd) >= inter);	}
		__IMPOETER void Decrement_repeat(int& count, int sum){			count = (count + (sum - 1) % sum);			}
		__IMPOETER bool IsNoRemender_FrameCnt(int in){					return ( in && !(this->frameCnt % in) );	}

		//virtual
		__IMPOETER virtual void Init() = 0;
		__IMPOETER virtual void Step() = 0;
		__IMPOETER virtual void Draw2D() = 0;
		__IMPOETER virtual void Dispose() = 0;
	};

	//---------------------------------------------------------
	//UI�Ƃ��ĕK�v�ȃp�[�c
	//�����ɕK�v�ŏ����̂��̂��`
	//---------------------------------------------------------
	class UIParts2D
	{
	public:
		float					ang;
		NanairoLib::Vector2		pos, scale;
		NanairoLib::Textcolor	color;

	public:
		__IMPOETER UIParts2D() : ang(0)
		{
			pos.SetMinVector();
			scale.SetMinVector();
			color.SetMaxColor();
		}
		virtual ~UIParts2D(){}

		__IMPOETER UIParts2D& operator = (NanairoLib::UIParts2D& in)
		{
			ang = in.ang;
			pos = in.pos;
			scale = in.scale;
			color = in.color;
			return *this;
		}
	};

	//---------------------------
	//�L�����̃X�[�p�[�N���X���I
	//---------------------------
	class Chara3D : public NormalObject
	{
		public:
			//�L�����ԍ��A�A�^�b�N�J�E���^�A���\�[�X�ԍ�
			short charaKnd, atackCnt, resorceNum;

		protected:
			//�t���[���J�E���^�A�������[�h�A�����J�E���^
			short moveMode,moveCnt;
			//�g�k�A�p�x
			float scale,angle;
			//�ʒu�A�ߋ��ʒu�A���f���g�k
			Vector3 posi, oldposi, modelscale;
			//�F
			Textcolor color;
			//���[���h�s��
			D3DXMATRIX world;

		public:
			__IMPOETER Chara3D();
			__IMPOETER virtual ~Chara3D();

			__IMPOETER PMATRIX GetWorld(){				return &world;	}
			__IMPOETER PVector3 GetPosi(){				return &posi;	}
			__IMPOETER PVector3 GetOLDPOS(){			return &oldposi;	}
			__IMPOETER PCColor GetColor(){				return &color;		}
			__IMPOETER float GetScale(){				return scale;	}

			__IMPOETER virtual void Init() = 0;
			__IMPOETER virtual void Step() = 0;
			__IMPOETER virtual void Draw3D() = 0;
			__IMPOETER virtual void CheckAtack() = 0;
			__IMPOETER virtual void Draw2D() = 0;
			__IMPOETER virtual void Del() = 0;
			__IMPOETER virtual void Dispose() = 0;
			__IMPOETER void UpdateWorld(PDirectDevice Device);
	};

	///////////////////////////////////////////////////////////////////////////////
	//�G�t�F�N�g�̊�{�@�p���@�ėp�I�u�W�F�N�g
	class Effect2D : public NanairoLib::NormalObject
	{
	protected:
		int						cntSpd;
		UIParts2D				parts;

	protected:
		__IMPOETER void SuperInitEffect2D();

	public:
		//Constracter
		__IMPOETER Effect2D() : cntSpd(1){	this->SuperInitEffect2D();	}
		__IMPOETER virtual ~Effect2D(){}

		//Getter
		__IMPOETER PUIParts2D GetParts() const{	return (NanairoLib::PUIParts2D const)&this->parts;	}
		
		//Setter
		__IMPOETER void SetPos(NanairoLib::RVector2 dpos){	this->parts.pos = dpos;					}
		__IMPOETER void SetAng(float dang){				this->parts.ang = dang;					}
		__IMPOETER void SetScl(NanairoLib::RVector2 dscl){	this->parts.scale = dscl;				}
		__IMPOETER void SetColor(NanairoLib::Textcolor& dcol);
		__IMPOETER void SetObjectParts(NanairoLib::RVector2 dpos, float dang, NanairoLib::RVector2 dscl);
		
		//virtual
		__IMPOETER void Init(){}
		__IMPOETER void Step(){}
		__IMPOETER void Draw2D(){}
		__IMPOETER void Dispose(){}
	};
}
#endif