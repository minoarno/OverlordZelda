#pragma once
class SeaMaterial;
class Character;
class Gem;
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

	void Update() override;

	GameObject* AddPlayer();
	GameObject* AddLevel();
	GameObject* AddTree(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale);
	GameObject* AddSmallExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale);
	GameObject* AddMediumExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale);
	GameObject* AddBigExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale);
	GameObject* AddGem(const XMFLOAT3& position);
	GameObject* AddBombSpawner(const XMFLOAT3& position);
	GameObject* AddSea();
	GameObject* AddSkyBox();
	void AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename);

	void OnSceneActivated() override;
	void ResetScene();

	void PostDraw() override;

	void OnGUI() override;
private:
	enum InputIds
	{
		CharacterMoveLeft,
		CharacterMoveRight,
		CharacterMoveForward,
		CharacterMoveBackward,
		CharacterJump,
		ThrowBomb,
		Settings,
		SettingsMoveUp,
		SettingsMoveDown
	};

	Character* m_pCharacter;
	GameObject* m_pSea;
	SeaMaterial* m_pSeaMaterial;

	std::vector<Gem*> m_pGems;

	GameObject* m_pObject;

	//Shadow map draw
	bool m_DrawShadowMap{ false };
	float m_ShadowMapScale{ 0.3f };

	PxMaterial* m_pDefaultMaterial;
};

