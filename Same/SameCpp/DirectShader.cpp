#pragma once

//----------------------------------------------------
//
//シェーダーを扱うクラス
//
//-----------------------------------------------------

#include <tchar.h>
#include <string>
#include <ResourceDrawer.h>

namespace NanairoLib
{

	//テスト用
	///テクスチャマッピングするシェーダ
#pragma region test source
	char shadersrc[]= 
		"float4x4	WorldViewProj;		\
		float4		LightPos;			\
		float4		Diffuse;			\
		float		LightBrightness;	\
		float		ModelScale;			\
		\
		void VertexShader_Main(								\
		in	float4	inPos		:	POSITION,				\
		in	float4	inNormal	:	NORMAL0,				\
		in	float4	inTexture	:	TEXCOORD0,				\
		\
		out	float4	outPos		:	POSITION,				\
		out	float4	outDiff		:	COLOR0,					\
		out	float4	outTexture	:	TEXCOORD0){				\
			outPos = mul(inPos, WorldViewProj);				\
			\
			float4 vL = LightPos - inPos;										\
			float  lengL = length(vL) * ModelScale;								\
			float4 normL = normalize(vL);										\
			float4 normN = normalize(inNormal);									\
			float  L = LightBrightness * dot(normN, normL) / (lengL * lengL);	\
			outDiff = Diffuse * max(0.7,L);										\
			\
			outTexture = inTexture;							\
		}\
		\
		texture Tex;							\
		sampler TexSampler = sampler_state {	\
			Texture		=	Tex;				\
			MipFilter	=	LINEAR;				\
			MinFilter	=	LINEAR;				\
			MagFilter	=	LINEAR;				\
		};\
		\
		void PixelShader_Texture_Main(						\
			in	float4	inDiff		:	COLOR0,				\
			in	float2	inTexture	:	TEXCOORD0,			\
			\
			out	float4	outDiff		:	COLOR0){\
			outDiff = inDiff * tex2D(TexSampler, inTexture);\
		}\
		\
		void PixelShader_NoTexture_Main(					\
			in	float4	inDiff	:	COLOR0,					\
			\
			out	float4	outDiff	:	COLOR0){				\
			outDiff = inDiff;								\
		}\
		\
		technique TextureTech{											\
			pass Pass0{														\
				ZEnable = TRUE;              \
				MultiSampleAntialias = TRUE;  \
				CullMode = CCW;               \
				ShadeMode = GOURAUD;          \
				\
				VertexShader = compile vs_2_0 VertexShader_Main();			\
				PixelShader = compile ps_2_0 PixelShader_Texture_Main();	\
			}\
		}\
		\
		technique NoTextureTech{											\
			pass Pass0{														\
				ZEnable = TRUE;              \
				MultiSampleAntialias = TRUE;  \
				CullMode = CCW;               \
				ShadeMode = GOURAUD;          \
				\
				VertexShader = compile vs_2_0 VertexShader_Main();			\
				PixelShader = compile ps_2_0 PixelShader_NoTexture_Main();	\
			}\
		}";
#pragma endregion

#pragma region コンストラクタ
Shader::Shader()
{
	this->doingShader = false;
}
Shader::~Shader(){}
#pragma endregion

	//----------------------------------------------
	//シェーダー初期化
	//----------------------------------------------
	//@in : DirectX用デバイス
	void Shader::InitShader(IDirect3DDevice9 *Device, LPCSTR pass)
	{
		LPD3DXBUFFER pErr = NULL;
		texhandle = NULL;
		LPD3DXEFFECT eff;

		//読み込まない時
		/*HRESULT r = ::D3DXCreateEffect(Device,shadersrc,sizeof(shadersrc),
			NULL,NULL,D3DXSHADER_DEBUG,NULL,&eff,&pErr);*/

		HRESULT r = ::D3DXCreateEffectFromFile(Device,_T(pass),NULL,
			NULL,0,NULL,(LPD3DXEFFECT*)&eff,&pErr);
		
		if(pErr != NULL){
			char* s = (char*)(pErr->GetBufferPointer());
			std::string str = s;
			OutputDebugStringA( (const char*)s);
		}
		if(FAILED(r))	
			return;

		eff->CloneEffect(Device, (LPD3DXEFFECT*)&this->Effect);

#ifdef SHADER_DRAWER
		HRESULT hr;
		D3DXHANDLE htech;
		htech = Effect->GetTechniqueByName( SHADER_TECH_ );
		hr = Effect->ValidateTechnique(htech);
		this->doingShader = true;
#endif
	}

}