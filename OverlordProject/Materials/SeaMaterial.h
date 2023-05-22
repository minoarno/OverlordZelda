#pragma once

#include "Misc/Material.h"
class TextureData;
class SeaMaterial : public Material<SeaMaterial>
{
public:
	SeaMaterial();
	~SeaMaterial();

	void SetWaterColor(DirectX::XMFLOAT4 color);
	void SetRippleSpeed(float value);
	void SetRippleDensity(float value);
	void SetRippleSlimness(float value);
	void SetRippleColor(DirectX::XMFLOAT4 color);
	void SetWaveSpeed(float value);
	void SetWaveScale(float value);
	void SetFoamSpeed(float value);
	void SetFoamScale(float value);
	void SetFoamAmount(float value);
	void SetFoamCutoff(float value);
	void SetFoamColor(DirectX::XMFLOAT4 color);
	void SetPerlinNoise(const std::wstring& assetFile);
protected:
	void InitializeEffectVariables()override;
	void OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModelComponent)const override;

private:
	SeaMaterial(const SeaMaterial&) = delete;
	SeaMaterial& operator=(const SeaMaterial&) = delete;
	SeaMaterial(SeaMaterial&&) = delete;
	SeaMaterial& operator=(SeaMaterial&&) = delete;

	TextureData* m_pPerlinNoise;
};