float4x4 gWorld : WORLD;
float4x4 gWorldViewProj : WORLDVIEWPROJECTION; 
float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

float4 gWaterColor = float4(1, 1, 1, 1);
float gRippleSpeed = 1;
float gRippleDensity = 1;
float gRippleSlimness = 1;
float4 gRippleColor = float4(1, 1, 1, 1);
float gWaveSpeed = 1;
float gWaveScale = 1;
float gFoamSpeed = 1;
float gFoamScale = 1;
float gFoamAmount = 1;
float gFoamCutoff = 1;
float4 gFoamColor = float4(1, 1, 1, 1);
float gTotalTime = 0;
Texture2D gDepthBuffer;
Texture2D gPerlinNoise;

struct VS_INPUT
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
    float2 texCoord : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
    float2 texCoord : TEXCOORD;
    float depth : DEPTH;
};

DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap; // or Mirror or Clamp or Border
    AddressV = Wrap; // or Mirror or Clamp or Border
};

RasterizerState NoCulling
{
	CullMode = NONE;
};

BlendState EnableBlending
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
    float3 offset = float3(0, 0, gWaveScale);
    offset = 0;
    output.pos = mul(float4(input.pos + offset, 1.0f), gWorldViewProj);
	output.normal = normalize(mul(input.normal, (float3x3)gWorld));

    output.color = input.color;
    output.texCoord = input.texCoord;
    output.depth = input.pos.z;
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------


//https://docs.unity3d.com/Packages/com.unity.shadergraph@6.9/manual/Voronoi-Node.html
//Generates a Voronoi, or Worley, noise based on input UV. 
//Voronoi noise is generated by calculating distances between a pixel and a lattice of points.
//By offsetting these points by a pseudo-random number, controlled by input Angle Offset, a cluster of cells can be generated.
//The scale of these cells, and the resulting noise, is controlled by input Cell Density. The output Cells contains the raw cell data

inline float2 unity_voronoi_noise_randomVector(float2 UV, float offset)
{
    float2x2 m = float2x2(15.27, 47.63, 99.41, 89.98);
    UV = frac(sin(mul(UV, m)) * 46839.32);
    return float2(sin(UV.y * +offset) * 0.5 + 0.5, cos(UV.x * offset) * 0.5 + 0.5);
}
void Unity_Voronoi_float(float2 UV, float AngleOffset, float CellDensity, out float Out, out float Cells)
{
    float2 g = floor(UV * CellDensity);
    float2 f = frac(UV * CellDensity);
    float t = 8.0;
    float3 res = float3(8.0, 0.0, 0.0);

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 lattice = float2(x, y);
            float2 offset = unity_voronoi_noise_randomVector(lattice + g, AngleOffset);
            float d = distance(lattice + offset, f);
            if (d < res.x)
            {
                res = float3(d, offset.x, offset.y);
                Out = res.x;
                Cells = res.y;
            }
        }
    }
}

float DepthFade(VS_OUTPUT input)
{
    //return saturate((input.depth - input.pos.z) / gFoamAmount) * gFoamCutoff;
    return gDepthBuffer.Sample(samLinear, input.texCoord);
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float voronoi = 0, cells = 0;
    Unity_Voronoi_float(input.texCoord, gTotalTime * gRippleSpeed, gRippleDensity, voronoi, cells);
    
    float4 finalColor = gWaterColor + gRippleColor * pow(voronoi, gRippleSlimness);
    
    float depthFade = DepthFade(input);
    //return float4(depthFade,depthFade,depthFade,1);
    return finalColor;
}

//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique11 Default
{
    pass P0
    {
		SetRasterizerState(NoCulling);
		SetDepthStencilState(EnableDepth, 0);

        SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}