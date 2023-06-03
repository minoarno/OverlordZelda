#pragma once

class Button;
class MainMenu final : public GameScene
{
public:
	MainMenu();
	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;
	MainMenu(MainMenu&&) = delete;
	MainMenu& operator=(MainMenu&&) = delete;
	~MainMenu() = default;

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