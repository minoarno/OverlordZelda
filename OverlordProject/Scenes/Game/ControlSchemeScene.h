#pragma once
class Button;
class ControlSchemeScene final : public GameScene
{
public:
	ControlSchemeScene();
	ControlSchemeScene(const ControlSchemeScene&) = delete;
	ControlSchemeScene& operator=(const ControlSchemeScene&) = delete;
	ControlSchemeScene(ControlSchemeScene&&) = delete;
	ControlSchemeScene& operator=(ControlSchemeScene&&) = delete;
	~ControlSchemeScene();

protected:
	enum InputIds
	{
		SettingsMoveUp = 7,
		SettingsMoveDown = 8,
		SettingsPress = 9
	};

	void Initialize() override;
	void Update() override;

private:
	Button* m_pControlSchemeStart{ nullptr };
};