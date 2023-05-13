#pragma once

class UberMaterialScene final : public GameScene
{
public:
	UberMaterialScene();
	UberMaterialScene(const UberMaterialScene&) = delete;
	UberMaterialScene& operator=(const UberMaterialScene&) = delete;
	UberMaterialScene(UberMaterialScene&&) = delete;
	UberMaterialScene& operator=(UberMaterialScene&&) = delete;
	~UberMaterialScene() = default;

protected:
	void Initialize() override;
};
