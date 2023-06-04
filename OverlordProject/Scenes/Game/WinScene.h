#pragma once
class Button;
class WinScene final : public GameScene
{
public:
	WinScene();
	WinScene(const WinScene&) = delete;
	WinScene& operator=(const WinScene&) = delete;
	WinScene(WinScene&&) = delete;
	WinScene& operator=(WinScene&&) = delete;
	~WinScene() override = default;
protected:
	enum InputIds
	{
		SettingsMoveUp = 7,
		SettingsMoveDown = 8,
		SettingsPress = 9
	};

	void Initialize() override;
	void Update() override;

	std::vector<Button*> m_pButtons;
	int m_SelectedButtonIndex = -1;
};

