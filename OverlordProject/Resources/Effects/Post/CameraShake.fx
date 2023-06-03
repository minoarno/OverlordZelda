//=============================================================================
//// Shader uses position and texture
//=============================================================================
//https://defold.com/tutorials/grading/

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};

float2 gTexelSize = float2(1, 1); // The size of a single texel in the source texture
float gShakeAmount = 1; // The amount of camera shake to apply
Texture2D gTexture;

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
    int mipLevel = 0;
    int width = 0;
    int height = 0;
    int numberOfLevels = 0;
    gTexture.GetDimensions(mipLevel, width, height, numberOfLevels);
    
    
	// Step 2: calculate dx and dy (UV space for 1 pixel)
    //float2 texCoord = float2(width * input.TexCoord.x, height * input.TexCoord.y);
    float2 texCoord = input.TexCoord;
    float2 shakeOffset = gTexelSize * gShakeAmount * (float2(0.5, 0.5) - texCoord);

    // Apply the camera shake offset to the current pixel's texture coordinates
    texCoord += shakeOffset;

    // Sample the color from the offset texture coordinates
    float4 color = gTexture.Sample(samLinear, texCoord);

    return color;
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