#pragma once

class TextureData;

class SpikyMaterial final : public Material<SpikyMaterial>
{
public:
	SpikyMaterial();
	~SpikyMaterial();

protected:
	void InitializeEffectVariables()override;
	void OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModelComponent)const override;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	SpikyMaterial(const SpikyMaterial&obj);
	SpikyMaterial& operator=(const SpikyMaterial& obj);
};

