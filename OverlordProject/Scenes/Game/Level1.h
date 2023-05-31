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

	GameObject* AddPlayer(PxMaterial* pDefaultMaterial);
	GameObject* AddLevel(PxMaterial* pDefaultMaterial);
	GameObject* AddTree(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial);
	GameObject* AddSmallExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial);
	GameObject* AddMediumExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial);
	GameObject* AddBigExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial);
	GameObject* AddGem(const XMFLOAT3& position, PxMaterial* pDefaultMaterial);
	GameObject* AddSea();
	GameObject* AddSkyBox();
	void AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename);

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
		CharacterJump
	};

	Character* m_pCharacter;
	GameObject* m_pSea;
	SeaMaterial* m_pSeaMaterial;

	GameObject* m_pObject;

	//Shadow map draw
	bool m_DrawShadowMap{ false };
	float m_ShadowMapScale{ 0.3f };
};

