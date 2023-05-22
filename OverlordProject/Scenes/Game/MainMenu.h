#pragma once

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
};