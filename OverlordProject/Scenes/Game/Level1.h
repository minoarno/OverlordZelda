#pragma once
class SeaMaterial;
class Character;
class Level1 final : public GameScene
{
public:
	Level1();
	Level1(const Level1&) = delete;
	Level1& operator=(const Level1&) = delete;
	Level1(Level1&&) = delete;
	Level1& operator=(Level1&&) = delete;
	~Level1() = default;

protected:
	void Initialize() override;

	void AddPlayer(PxMaterial* pDefaultMaterial);
	void AddLevel(PxMaterial* pDefaultMaterial);
	void AddTree(const XMFLOAT3& position, PxMaterial* pDefaultMaterial);
	void AddSmallExplodableRock(const XMFLOAT3& position, PxMaterial* pDefaultMaterial);
	void AddMediumExplodableRock(const XMFLOAT3& position, PxMaterial* pDefaultMaterial);
	void AddBigExplodableRock(const XMFLOAT3& position, PxMaterial* pDefaultMaterial);
	void AddGem(const XMFLOAT3& position, PxMaterial* pDefaultMaterial);
	void AddSea();
	void AddSkyBox();
	void AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename);

	void ResetScene();

	void OnGUI() override;
private:
	enum InputIds
	{
		CharacterMoveLeft,
		CharacterMoveRight,
		CharacterMoveForward,
		CharacterMoveBackward,
		CharacterJump
	};

	Character* m_pCharacter;
	GameObject* m_pSea;
	SeaMaterial* m_pSeaMaterial;
};

