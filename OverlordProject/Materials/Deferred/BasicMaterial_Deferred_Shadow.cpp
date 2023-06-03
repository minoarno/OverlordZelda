#include "stdafx.h"
#include "BasicMaterial_Deferred_Shadow.h"

BasicMaterial_Deferred_Shadow::BasicMaterial_Deferred_Shadow()
	: Material{ L"Effects/Deferred/BasicEffect_Deferred_Shadow.fx" }
{
}

void BasicMaterial_Deferred_Shadow::SetDiffuseTexture(const std::wstring& assetFile)
{
	SetDiffuseTexture(ContentManager::Load<TextureData>(assetFile));
}

void BasicMaterial_Deferred_Shadow::SetDiffuseTexture(TextureData* pTextureData)
{
	SetVariable_Scalar(L"gUseDiffuseMap", pTextureData != nullptr);
	SetVariable_Texture(L"gDiffuseMap", pTextureData);
}

void BasicMaterial_Deferred_Shadow::SetDiffuseColor(DirectX::XMFLOAT4 color)
{
	SetVariable_Vector(L"gDiffuseColor", color);
}

void BasicMaterial_Deferred_Shadow::SetNormalTexture(const std::wstring& assetFile)
{
	SetNormalTexture(ContentManager::Load<TextureData>(assetFile));
}

void BasicMaterial_Deferred_Shadow::SetNormalTexture(TextureData* pTextureData)
{
	SetVariable_Scalar(L"gUseNormalMap", pTextureData != nullptr);
	SetVariable_Texture(L"gNormalMap", pTextureData);
}

void BasicMaterial_Deferred_Shadow::SetSpecularTexture(const std::wstring& assetFile)
{
	SetSpecularTexture(ContentManager::Load<TextureData>(assetFile));
}

void BasicMaterial_Deferred_Shadow::SetSpecularTexture(TextureData* pTextureData)
{
	SetVariable_Scalar(L"gUseSpecularMap", pTextureData != nullptr);
	SetVariable_Texture(L"gSpecularMap", pTextureData);
}

void BasicMaterial_Deferred_Shadow::UseTransparency(bool /*enable*/)
{
	//SetTechnique(enable ? L"Default_Alpha" : L"Default");
}

void BasicMaterial_Deferred_Shadow::InitializeEffectVariables()
{
	SetVariable_Scalar(L"gUseDiffuseMap", false);
	SetVariable_Scalar(L"gUseNormalMap", false);
	SetVariable_Scalar(L"gUseSpecularMap", false);
}

void BasicMaterial_Deferred_Shadow::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const
{
	// Update The Shader Variables
	// 1. Update the LightWVP > Used to Transform a vertex into Light clipping space
	// 	LightWVP = model_world * light_viewprojection
	// 	(light_viewprojection [LightVP] can be acquired from the ShadowMapRenderer)*/
	auto LightWVP = XMMatrixMultiply(XMLoadFloat4x4(&pModel->GetTransform()->GetWorld()), XMLoadFloat4x4(&ShadowMapRenderer::Get()->GetLightVP()));
	SetVariable_Matrix(L"gWorldViewProj_Light", reinterpret_cast<const float*>(LightWVP.r));

	//2. Update the ShadowMap texture
	SetVariable_Texture(L"gShadowMap", ShadowMapRenderer::Get()->GetShadowMap());

	//3. Update the Light Direction (retrieve the direction from the LightManager > sceneContext)
	SetVariable_Vector(L"gLightDirection", sceneContext.pLights->GetDirectionalLight().direction);
}