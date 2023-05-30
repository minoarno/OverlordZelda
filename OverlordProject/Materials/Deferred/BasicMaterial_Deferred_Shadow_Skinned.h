#pragma once
#include "BasicMaterial_Deferred_Shadow.h"

class BasicMaterial_Deferred_Shadow_Skinned : public BasicMaterial_Deferred_Shadow
{
public:
	BasicMaterial_Deferred_Shadow_Skinned();
	~BasicMaterial_Deferred_Shadow_Skinned() override = default;

	BasicMaterial_Deferred_Shadow_Skinned(const BasicMaterial_Deferred_Shadow_Skinned& other) = delete;
	BasicMaterial_Deferred_Shadow_Skinned(BasicMaterial_Deferred_Shadow_Skinned&& other) noexcept = delete;
	BasicMaterial_Deferred_Shadow_Skinned& operator=(const BasicMaterial_Deferred_Shadow_Skinned& other) = delete;
	BasicMaterial_Deferred_Shadow_Skinned& operator=(BasicMaterial_Deferred_Shadow_Skinned&& other) noexcept = delete;

protected:
	void InitializeEffectVariables() override;
	void OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const;
};