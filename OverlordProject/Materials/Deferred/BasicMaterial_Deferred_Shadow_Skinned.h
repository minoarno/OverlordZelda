#pragma once
#include "BasicMaterial_Deferred_Shadow.h"

class BasicMaterial_Deferred_Shadow_Skinned : public Material<BasicMaterial_Deferred_Shadow_Skinned>
{
public:
	BasicMaterial_Deferred_Shadow_Skinned();
	~BasicMaterial_Deferred_Shadow_Skinned() override = default;

	BasicMaterial_Deferred_Shadow_Skinned(const BasicMaterial_Deferred_Shadow_Skinned& other) = delete;
	BasicMaterial_Deferred_Shadow_Skinned(BasicMaterial_Deferred_Shadow_Skinned&& other) noexcept = delete;
	BasicMaterial_Deferred_Shadow_Skinned& operator=(const BasicMaterial_Deferred_Shadow_Skinned& other) = delete;
	BasicMaterial_Deferred_Shadow_Skinned& operator=(BasicMaterial_Deferred_Shadow_Skinned&& other) noexcept = delete;

	void SetDiffuseMap(const std::wstring& assetFile);
	void SetDiffuseMap(TextureData* pTextureData);

	void SetNormalMap(const std::wstring& assetFile);
	void SetNormalMap(TextureData* pTextureData);

	void SetSpecularMap(const std::wstring& assetFile);
	void SetSpecularMap(TextureData* pTextureData);

	void UseTransparency(bool enable);
protected:
	void InitializeEffectVariables() override;
	void OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const override;
};