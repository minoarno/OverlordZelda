#pragma once
class TextureData;

class UberMaterial final : public Material<UberMaterial>
{
public:
	UberMaterial();
	~UberMaterial();

	//LIGHT
	//*****
	void SetLightDirection(DirectX::XMFLOAT3 direction);

	//DIFFUSE
	//*******
	void EnableDiffuseTexture(bool enable);
	void SetDiffuseTexture(const std::wstring& assetFile);
	void SetDiffuseColor(DirectX::XMFLOAT4 color);
	
	//SPECULAR
	//********
	void SetSpecularColor(DirectX::XMFLOAT4 color);
	void EnableSpecularLevelTexture(bool enable);
	void SetSpecularLevelTexture(const std::wstring& assetFile);
	void SetShininess(int shininess);
	
	//AMBIENT
	//*******
	void SetAmbientColor(DirectX::XMFLOAT4 color);
	void SetAmbientIntensity(float intensity);

	//NORMAL MAPPING
	//**************
	void FlipNormalGreenCHannel(bool flip);
	void EnableNormalMapping(bool enable);
	void SetNormalMapTexture(const std::wstring& assetFile);
	
	//ENVIRONMENT MAPPING
	//*******************
	void EnableEnvironmentMapping(bool enable);
	void SetEnvironmentCube(const std::wstring& assetFile);
	void SetReflectionStrength(float strength);
	void SetRefractionStrength(float strength);
	void SetRefractionIndex(float index);

	//OPACITY
	//*******
	void SetOpacity(float opacity);
	void EnableOpacityMap(bool enable);
	void SetOpacityTexture(const std::wstring& assetFile);

	//SPECULAR MODELS
	//***************
	void EnableSpecularBlinn(bool enable);
	void EnableSpecularPhong(bool enable);

	//FRESNEL FALLOFF
	//***************
	void EnableFresnelFaloff(bool enable);
	void SetFresnelColor(DirectX::XMFLOAT4 color);
	void SetFresnelPower(float power);
	void SetFresnelMultiplier(float multiplier);
	void SetFresnelHardness(float hardness);

protected:
	void InitializeEffectVariables() override;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	UberMaterial(const UberMaterial &obj) = delete;
	UberMaterial& operator=(const UberMaterial& obj) = delete;
};

