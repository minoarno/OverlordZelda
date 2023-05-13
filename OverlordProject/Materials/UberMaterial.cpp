#include "stdafx.h"
#include "UberMaterial.h"

UberMaterial::UberMaterial()
	: Material(L"Effects/UberShader.fx")
{
}

UberMaterial::~UberMaterial()
{
}

void UberMaterial::SetLightDirection(DirectX::XMFLOAT3 direction)
{
	SetVariable_Vector(L"gLightDirection", direction);
}

void UberMaterial::EnableDiffuseTexture(bool enable)
{
	SetVariable_Scalar(L"gUseTextureDiffuse", enable);
}

void UberMaterial::SetDiffuseTexture(const std::wstring & assetFile)
{
	SetVariable_Texture(L"gTextureDiffuse", ContentManager::Load<TextureData>(assetFile)->GetShaderResourceView());
}

void UberMaterial::SetDiffuseColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gColorDiffuse", color);
}

void UberMaterial::SetSpecularColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gColorSpecular", color);
}

void UberMaterial::EnableSpecularLevelTexture(bool enable)
{
	SetVariable_Scalar(L"gUseTextureSpecularIntensity", enable);
}

void UberMaterial::SetSpecularLevelTexture(const std::wstring & assetFile)
{
	SetVariable_Texture(L"gTextureSpecularIntensity", ContentManager::Load<TextureData>(assetFile)->GetShaderResourceView());
}

void UberMaterial::SetShininess(int shininess)
{
	SetVariable_Scalar(L"gShininess", shininess);
}

void UberMaterial::SetAmbientColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gColorAmbient", color);
}

void UberMaterial::SetAmbientIntensity(float intensity)
{
	SetVariable_Scalar(L"gAmbientIntensity", intensity);
}

void UberMaterial::FlipNormalGreenCHannel(bool flip)
{
	SetVariable_Scalar(L"gFlipGreenChannel", flip);
}

void UberMaterial::EnableNormalMapping(bool enable)
{
	SetVariable_Scalar(L"gUseTextureNormal", enable);
}

void UberMaterial::SetNormalMapTexture(const std::wstring & assetFile)
{
	SetVariable_Texture(L"gTextureNormal", ContentManager::Load<TextureData>(assetFile)->GetShaderResourceView());
}

void UberMaterial::EnableEnvironmentMapping(bool enable)
{
	SetVariable_Scalar(L"gUseTextureEnvironment", enable);
}

void UberMaterial::SetEnvironmentCube(const std::wstring & assetFile)
{
	SetVariable_Texture(L"gCubeEnvironment", ContentManager::Load<TextureData>(assetFile)->GetShaderResourceView());
}

void UberMaterial::SetReflectionStrength(float strength)
{
	SetVariable_Scalar(L"gReflectionStrength", strength);
}

void UberMaterial::SetRefractionStrength(float strength)
{
	SetVariable_Scalar(L"gRefractionStrength", strength);
}

void UberMaterial::SetRefractionIndex(float index)
{
	SetVariable_Scalar(L"gRefractionIndex", index);
}

void UberMaterial::SetOpacity(float opacity)
{
	SetVariable_Scalar(L"gOpacityIntensity", opacity);
}

void UberMaterial::EnableOpacityMap(bool enable)
{
	SetVariable_Scalar(L"gUseTextureOpacity", enable);
}

void UberMaterial::SetOpacityTexture(const std::wstring & assetFile)
{
	SetVariable_Texture(L"gTextureOpacity", ContentManager::Load<TextureData>(assetFile)->GetShaderResourceView());
}

void UberMaterial::EnableSpecularBlinn(bool enable)
{
	SetVariable_Scalar(L"gUseSpecularBlinn", enable);
}

void UberMaterial::EnableSpecularPhong(bool enable)
{
	SetVariable_Scalar(L"gUseSpecularPhong", enable);
}

void UberMaterial::EnableFresnelFaloff(bool enable)
{
	SetVariable_Scalar(L"gUseFresnelFalloff", enable);
}

void UberMaterial::SetFresnelColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gColorFresnel", color);
}

void UberMaterial::SetFresnelPower(float power)
{
	SetVariable_Scalar(L"gFresnelPower", power);
}

void UberMaterial::SetFresnelMultiplier(float multiplier)
{
	SetVariable_Scalar(L"gFresnelMultiplier", multiplier);
}

void UberMaterial::SetFresnelHardness(float hardness)
{
	SetVariable_Scalar(L"gFresnelHardness", hardness);
}

void UberMaterial::InitializeEffectVariables()
{
}