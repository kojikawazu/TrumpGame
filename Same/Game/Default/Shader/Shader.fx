
//*****************************************************************
//MyShaderSample
//*****************************************************************

//------------------------------------------------------------------
struct VS_INPUT
{
	float4	Pos		: POSITION;
	float4	Normal	: NORMAL;
	float2	UV		: TEXCOORD0;
};

struct VS_INPUT_2D
{
	float4	Pos		: POSITION;
	float4	Color	: COLOR0;
	float2	UV		: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4	Pos		: POSITION0;
	float4	Diffuse	: COLOR0;
	float2	UV		: TEXCOORD0;
};

struct MATERIAL
{
	float4	Diffuse;
	float4	Ambient;
	float4	Specular;
	float4	Emissive;
	float	Power;
};
//------------------------------------------------------------------

//------------------------------------------------------------------
//WorldField
//------------------------------------------------------------------
float4x4	matWorld		: WORLD;
float4x4	matView			: VIEW;
float4x4	matProjection	: PROJECTION;
int			iBlendNum;

//------------------------------------------------------------------
//LightMember
//light is anable;
//Please member input field;
//------------------------------------------------------------------

bool		sd_lighting			= false;	//���̗L��
float4		sd_dirLight;					//���̐F
float4		sd_dirLightDiffuse;				//���̃f�B�t���[�Y�F
float4		sd_dirLightAmbient;				//���̃A���r�G���g�F
float4		sd_dirLightSpecular;			//���̃X�y�L�����[�F
MATERIAL	sd_material;					//�}�e���A���R�c
float4		sd_ambient2D;					//�}�e���A���Q�c

//------------------------------------------------------------------
//TextureMember
//texture is anable;
//Please member input field;
//------------------------------------------------------------------

bool	sd_textureRendering		= false;
texture	sd_texture;
sampler	MeshTextureSampler = 
sampler_state
{
	Texture		= < sd_texture >;	//�Ώۃe�N�X�`��
	MinFilter	= LINEAR;			//�k�����̃T���v�����O
	MagFilter	= LINEAR;			//�g�厞�̃T���v�����O
	MipFilter	= NONE;				//�~�b�v�}�b�v

	//�t�u�}�b�v
	//�O�`�P�Ƃ��Ĉ���
	AddressU	= Clamp;
	AddressV	= Clamp;
};

//////////////////////////////////////////////////////
//VertexShader----------------------------------------
//////////////////////////////////////////////////////
VS_OUTPUT vs_main( VS_INPUT In )
{
	VS_OUTPUT Out;
	
	Out.Pos = mul( In.Pos, matWorld );
	Out.Pos = mul( Out.Pos, matView );
	Out.Pos = mul( Out.Pos, matProjection );

	Out.Diffuse = float4(1,1,1,1);
	Out.UV		= In.UV;

	return ( Out );
}
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//VertexShader----------------------------------------
//////////////////////////////////////////////////////
VS_OUTPUT vs_main_2D( VS_INPUT_2D In )
{
	VS_OUTPUT Out;
	
	Out.Pos = In.Pos;
	Out.Diffuse = In.Color;
	Out.UV		= In.UV;

	return ( Out );
}
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
//PixelShader-----------------------------------------
//////////////////////////////////////////////////////
float4 ps_main( VS_OUTPUT In ) : COLOR0
{
	float4 Color = In.Diffuse;
	if( sd_textureRendering	)
		Color = tex2D( MeshTextureSampler, In.UV ) * Color;
	return ( clamp( Color, 0.0f, 1.0f ) );
}
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//PixelShader-----------------------------------------
//////////////////////////////////////////////////////
float4 ps_main_default( VS_OUTPUT In ) : COLOR0
{
	float4 Color = In.Diffuse;
	return ( clamp( Color, 0.0f, 1.0f ) );
}
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//PixelShader-----------------------------------------
//////////////////////////////////////////////////////
float4 ps_main_2D( VS_OUTPUT In ) : COLOR0
{
	float4 Color = In.Diffuse;
	if( sd_textureRendering	)
		Color = tex2D( MeshTextureSampler, In.UV ) * Color;
	return ( clamp( Color, 0.0f, 1.0f ) );
}
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//Technique-------------------------------------------
//////////////////////////////////////////////////////
technique Default_Tech
{
	pass pass0
	{
		VertexShader	= compile vs_2_0 vs_main();
		PixelShader		= compile ps_2_0 ps_main();
	}

	pass pass1
	{
		VertexShader	= compile vs_2_0 vs_main();
		PixelShader		= compile ps_2_0 ps_main_default();
	}

	pass pass2
	{
		VertexShader	= compile vs_2_0 vs_main_2D();
		PixelShader		= compile ps_2_0 ps_main_2D();
	}
}
//////////////////////////////////////////////////////