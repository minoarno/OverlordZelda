#pragma once
class BasicMaterial_Deferred_Shadow : public Material<BasicMaterial_Deferred_Shadow>
{
public:
	BasicMaterial_Deferred_Shadow();
	~BasicMaterial_Deferred_Shadow() override = default;

	BasicMaterial_Deferred_Shadow(const BasicMaterial_Deferred_Shadow& other) = delete;
	BasicMaterial_Deferred_Shadow(BasicMaterial_Deferred_Shadow&& other) noexcept = delete;
	BasicMaterial_Deferred_Shadow& operator=(const BasicMaterial_Deferred_Shadow& other) = delete;
	BasicMaterial_Deferred_Shadow& operator=(BasicMaterial_Deferred_Shadow&& other) noexcept = delete;

	void SetDiffuseTexture(const std::wstring& assetFile);
	void SetDiffuseTexture(TextureData* pTextureData);

	void SetDiffuseColor(DirectX::XMFLOAT4 color);

	void SetNormalTexture(const std::wstring& assetFile);
	void SetNormalTexture(TextureData* pTextureData);

	void SetSpecularTexture(const std::wstring& assetFile);
	void SetSpecularTexture(TextureData* pTextureData);

	void UseTransparency(bool enable);
protected:
	void InitializeEffectVariables() override;
	void OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const;
};

