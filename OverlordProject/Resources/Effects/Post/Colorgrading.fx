//=============================================================================
//// Shader uses position and texture
//=============================================================================
//https://defold.com/tutorials/grading/

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};

Texture2D gTexture;
Texture2D gSampleTexture;
float g_MaxColor = 15.0;
float g_Colors = 16.0;
float g_Width = 2560.0;
float g_Height = 16.0;

/// Create Depth Stencil State (ENABLE DEPTH WRITING)
DepthStencilState depthStencilState
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
};

/// Create Rasterizer State (Backface culling) 
RasterizerState rasterizerState
{
	FillMode = SOLID;
	CullMode = NONE;
};


//IN/OUT STRUCTS
//--------------
struct VS_INPUT
{
    float3 Position : POSITION;
	float2 TexCoord : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD1;
};


//VERTEX SHADER
//-------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	// Set the Position
	output.Position = float4(input.Position, 1.0);

	// Set the TexCoord
	output.TexCoord = input.TexCoord;

	return output;
}


//PIXEL SHADER
//------------
float4 PS(PS_INPUT input): SV_Target
{
	//find the dimensions of the texture (the texture has a method for that)
	int mipLevel = 0;
	int width = 0;
	int height = 0;
	int numberOfLevels = 0;
	gTexture.GetDimensions(mipLevel, width, height, numberOfLevels);

	float4 pixelColor = gTexture.Sample(samPoint, input.TexCoord.xy);

	float cell = floor(pixelColor.z * g_MaxColor);
	
	float2 halfPixel = float2{0.5 / g_Width, 0.5 / g_Height};

	float offsetX = halfPixel.x + pixelColor.x / g_Colors * (g_MaxColor / g_Colors);
	float offsetY = halfPixel.y + pixelColor.y * (g_MaxColor / g_Colors);

	float4 finalColor = gSampleTexture.Sample(samPoint, float2(offsetX,offsetY));

	return finalColor;
}


//TECHNIQUE
//---------
technique11 Blur
{
    pass P0
    {
		// Set states...
		SetRasterizerState(rasterizerState);
		SetDepthStencilState(depthStencilState, 0);

        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}