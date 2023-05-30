#pragma once
class Gem final : public GameObject
{
public:
	Gem(PxMaterial* pMaterial);
	Gem(const Gem&) = delete;
	Gem& operator=(const Gem&) = delete;
	Gem(Gem&&) = delete;
	Gem& operator=(Gem&&) = delete;
	~Gem() = default;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;

private:
	PxMaterial* m_pMaterial;
};