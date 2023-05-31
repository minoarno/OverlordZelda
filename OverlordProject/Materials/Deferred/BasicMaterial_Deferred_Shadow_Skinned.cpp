#include "stdafx.h"
#include "BasicMaterial_Deferred_Shadow_Skinned.h"

BasicMaterial_Deferred_Shadow_Skinned::BasicMaterial_Deferred_Shadow_Skinned()
	: Material{L"Effects/Deferred/BasicEffect_Deferred_Shadow_Skinned.fx"}
{
}

void BasicMaterial_Deferred_Shadow_Skinned::SetDiffuseMap(const std::wstring& assetFile)
{
	SetDiffuseMap(ContentManager::Load<TextureData>(assetFile));
}

void BasicMaterial_Deferred_Shadow_Skinned::SetDiffuseMap(TextureData* pTextureData)
{
	SetVariable_Scalar(L"gUseDiffuseMap", pTextureData != nullptr);
	SetVariable_Texture(L"gDiffuseMap", pTextureData);
}

void BasicMaterial_Deferred_Shadow_Skinned::SetNormalMap(const std::wstring& assetFile)
{
	SetNormalMap(ContentManager::Load<TextureData>(assetFile));
}

void BasicMaterial_Deferred_Shadow_Skinned::SetNormalMap(TextureData* pTextureData)
{
	SetVariable_Scalar(L"gUseNormalMap", pTextureData != nullptr);
	SetVariable_Texture(L"gNormalMap", pTextureData);
}

void BasicMaterial_Deferred_Shadow_Skinned::SetSpecularMap(const std::wstring& assetFile)
{
	SetSpecularMap(ContentManager::Load<TextureData>(assetFile));
}

void BasicMaterial_Deferred_Shadow_Skinned::SetSpecularMap(TextureData* pTextureData)
{
	SetVariable_Scalar(L"gUseSpecularMap", pTextureData != nullptr);
	SetVariable_Texture(L"gSpecularMap", pTextureData);
}

void BasicMaterial_Deferred_Shadow_Skinned::InitializeEffectVariables()
{
	SetVariable_Scalar(L"gUseDiffuseMap", false);
	SetVariable_Scalar(L"gUseNormalMap", false);
	SetVariable_Scalar(L"gUseSpecularMap", false);
}

void BasicMaterial_Deferred_Shadow_Skinned::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const
{
	// Update The Shader Variables
	// 1. Update the LightWVP > Used to Transform a vertex into Light clipping space
	// 	LightWVP = model_world * light_viewprojection
	// 	(light_viewprojection [LightVP] can be acquired from the ShadowMapRenderer)*/
	auto LightWVP = XMMatrixMultiply(XMLoadFloat4x4(&pModel->GetTransform()->GetWorld()), XMLoadFloat4x4(&ShadowMapRenderer::Get()->GetLightVP()));
	SetVariable_Matrix(L"gWorldViewProj_Light", reinterpret_cast<const float*>(LightWVP.r));

	// 2. Update the ShadowMap texture
	SetVariable_Texture(L"gShadowMap", ShadowMapRenderer::Get()->GetShadowMap());

	// 3. Update the Light Direction (retrieve the direction from the LightManager > sceneContext)
	SetVariable_Vector(L"gLightDirection", sceneContext.pLights->GetDirectionalLight().direction);

	// 4. Update Bones
	auto animator = pModel->GetAnimator();
	ASSERT_NULL_(animator);

	SetVariable_MatrixArray(L"gBones", (float*)animator->GetBoneTransforms().data(), (UINT)animator->GetBoneTransforms().size());

}
