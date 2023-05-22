#pragma once

class Button;
class MainMenu : public GameScene
{
public:
	MainMenu();
	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;
	MainMenu(MainMenu&&) = delete;
	MainMenu& operator=(MainMenu&&) = delete;
	~MainMenu() = default;

protected:
	virtual void Initialize() override;
	std::vector<Button*> m_pButtons;
};