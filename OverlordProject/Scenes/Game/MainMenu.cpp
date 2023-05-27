#include "stdafx.h"
#include "MainMenu.h"

#include "Prefabs/UI/Button.h"

MainMenu::MainMenu()
	: GameScene{L"MainMenu"}
{
}

void MainMenu::Initialize()
{
	auto pButton = AddChild(new Button{ L"Textures/UI/StartButtonNormal.png",L"Textures/UI/StartButtonActivated.png",[&]() 
		{
			OverlordGame::Stop();
		} });
	m_pButtons.emplace_back(pButton);
	
	pButton = AddChild(new Button{ L"Textures/UI/StartButtonNormal.png",L"Textures/UI/StartButtonNormal.png",[&]() {
		SceneManager::Get()->SetActiveGameScene(L"Level1");
		} });
	m_pButtons.emplace_back(pButton);
}
