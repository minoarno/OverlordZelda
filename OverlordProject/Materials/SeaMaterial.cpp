#include "stdafx.h"
#include "SeaMaterial.h"

SeaMaterial::SeaMaterial()
	: Material{ L"Effects/Zelda/SeaMaterial.fx" }
	, m_pPerlinNoise{ nullptr }
{
}

SeaMaterial::~SeaMaterial()
{
}

void SeaMaterial::SetWaterColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gWaterColor", color);
}

void SeaMaterial::SetRippleSpeed(float value)
{
	SetVariable_Scalar(L"gRippleSpeed", value);
}

void SeaMaterial::SetRippleDensity(float value)
{
	SetVariable_Scalar(L"gRippleDensity", value);
}

void SeaMaterial::SetRippleSlimness(float value)
{
	SetVariable_Scalar(L"gRippleSlimness", value);
}

void SeaMaterial::SetRippleColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gRippleColor", color);
}

void SeaMaterial::SetWaveSpeed(float value)
{
	SetVariable_Scalar(L"gWaveSpeed", value);
}

void SeaMaterial::SetWaveScale(float value)
{
	SetVariable_Scalar(L"gWaveScale", value);
}

void SeaMaterial::SetFoamSpeed(float value)
{
	SetVariable_Scalar(L"gFoamSpeed", value);
}

void SeaMaterial::SetFoamScale(float value)
{
	SetVariable_Scalar(L"gFoamScale", value);
}

void SeaMaterial::SetFoamAmount(float value)
{
	SetVariable_Scalar(L"gFoamAmount", value);
}

void SeaMaterial::SetFoamCutoff(float value)
{
	SetVariable_Scalar(L"gFoamCutoff", value);
}

void SeaMaterial::SetFoamColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gFoamColor", color);
}

void SeaMaterial::SetPerlinNoise(const std::wstring& assetFile)
{
	m_pPerlinNoise = ContentManager::Load<TextureData>(assetFile);
	SetVariable_Texture(L"gPerlinNoise", m_pPerlinNoise);
}

void SeaMaterial::InitializeEffectVariables()
{
}

void SeaMaterial::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* ) const
{
	if (!sceneContext.pGameTime->IsRunning())return;

	SetVariable_Scalar(L"gTotalTime", sceneContext.pGameTime->GetTotal());

	//sceneContext.

	//SetVariable_Texture(L"gDepthBuffer", DepthRenderer::Get()->GetRenderTarget());
}
