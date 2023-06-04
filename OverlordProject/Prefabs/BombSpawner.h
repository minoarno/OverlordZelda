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
	void Initialize(const SceneContext& scenetext) override;
	void Update(const SceneContext&) override;
private:
	float m_StartBombSpawn{ -20.f };
	float m_BombSpawnDuration{ 5.f };
	PxMaterial* m_pMaterial{ nullptr };
	Bomb* m_pBomb{ nullptr };
	GameTime* m_pGameTime{ nullptr };
};