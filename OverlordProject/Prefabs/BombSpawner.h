#pragma once
class Bomb;
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
	virtual void Update(const SceneContext&) override;
	void SpawnBomb();
private:
	PxMaterial* m_pMaterial;
	Bomb* m_pBomb;
};