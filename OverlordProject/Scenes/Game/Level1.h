#pragma once
class Gem;
class Rock;
class Button;
class RedGem;
class Bridge;
class WinArea;
class PostBlur;
class Character;
class SeaMaterial;
class PostCameraShake;
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
	GameObject* AddRedGem(const XMFLOAT4& position);
	GameObject* AddBombSpawner(const XMFLOAT3& position);
	GameObject* AddSea();
	GameObject* AddSkyBox();
	void AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename);

	void OnSceneActivated() override;
	void ResetScene();

	void PostDraw() override;

	void AddPauseMenu();
	void SetPauseMenu(bool isVisible);

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
		SettingsMoveDown,
		SettingsPress
	};

	Character* m_pCharacter;
	GameObject* m_pSea;
	SeaMaterial* m_pSeaMaterial;

	std::vector<Gem*> m_pGems;
	std::vector<RedGem*> m_pRedGems;
	std::vector<Rock*> m_pRocks;

	GameObject* m_pObject;

	//Shadow map draw
	bool m_DrawShadowMap{ false };
	float m_ShadowMapScale{ 0.3f };

	PxMaterial* m_pDefaultMaterial;

	//Audio
	FMOD::Sound* m_pBackgroundSoundFx;
	FMOD::ChannelGroup* m_pSoundEffectGroup;
	float m_MusicVolume{};

	void UpdateScene();

	void UpdatePause();
	std::vector<Button*> m_pButtons;
	int m_SelectedButtonIndex = -1;

	Button* m_pControlSchemeStart{ nullptr };
	SpriteComponent* m_pControlSchemeBackground{ nullptr };

	PostCameraShake* m_pCameraShake{nullptr};

	WinArea* m_pWinArea;
	Bridge* m_pBridge{ nullptr };
	FixedCamera* m_pBridgeCamera{ nullptr };
	float m_StartBridgeCameraTime{}, m_CameraSwitchDuration{3.f}, m_TimeBeforeBridgeSpawnsIn{1.5f};
	bool m_HasAlreadyDoneOtherCamera{};
};

