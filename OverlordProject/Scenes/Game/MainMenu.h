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
	void Initialize() override;
	void Update() override;
	std::vector<Button*> m_pButtons;
};