#pragma once

#include "Misc/Material.h"
class TextureData;
class DiffuseMaterial : public Material<DiffuseMaterial>
{
public:
	DiffuseMaterial();
	~DiffuseMaterial();

	void SetDiffuseTexture(const std::wstring& assetFile);
protected:
	void InitializeEffectVariables()override;
	void OnUpdateModelVariables(const SceneContext& sceneContext,const ModelComponent* pModelComponent)const override;
private:
	TextureData* m_pDiffuseTexture;

	DiffuseMaterial(const DiffuseMaterial& other) noexcept = delete;
	DiffuseMaterial& operator=(const DiffuseMaterial& other) noexcept = delete;
	DiffuseMaterial(DiffuseMaterial&& other) noexcept = delete;
	DiffuseMaterial& operator=(DiffuseMaterial&& other) noexcept = delete;
};

