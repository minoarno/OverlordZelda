#pragma once
class Button;
class LoseScene : public GameScene
{
public:
	LoseScene();
	LoseScene(const LoseScene&) = delete;
	LoseScene& operator=(const LoseScene&) = delete;
	LoseScene(LoseScene&&) = delete;
	LoseScene& operator=(LoseScene&&) = delete;
	~LoseScene();

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