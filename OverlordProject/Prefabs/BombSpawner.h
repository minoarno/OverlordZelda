#pragma once
class BombSpawner final : public GameObject
{
public:
	BombSpawner(PxMaterial* pMaterial);
	BombSpawner(const BombSpawner&) = delete;
	BombSpawner& operator=(const BombSpawner&) = delete;
	BombSpawner(BombSpawner&&) = delete;
	BombSpawner& operator=(BombSpawner&&) = delete;
	~BombSpawner() = default;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;

private:
	PxMaterial* m_pMaterial;
};