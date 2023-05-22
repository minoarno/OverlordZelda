#pragma once
class SeaMaterial;
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
	void AddSea();
	void AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename);

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

	GameObject* m_pCharacter;
	GameObject* m_pSea;
	SeaMaterial* m_pSeaMaterial;
};

