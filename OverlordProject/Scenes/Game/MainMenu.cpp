#include "stdafx.h"
#include "MainMenu.h"

#include "Prefabs/UI/Button.h"

MainMenu::MainMenu()
	: GameScene{L"MainMenu"}
{
}

void MainMenu::Initialize()
{
	const auto pCamera = AddChild(new FixedCamera());
	pCamera->GetComponent<CameraComponent>()->SetActive(true);

	auto pButton = AddChild(new Button{ L"Textures/UI/StartButtonNormal.png",L"Textures/UI/StartButtonActivated.png",[&]() 
		{
			SceneManager::Get()->SetActiveGameScene(L"Level1");
		} });
	pButton->GetTransform()->Translate(100, 200, 0);
	m_pButtons.emplace_back(pButton);

	pButton = AddChild(new Button{ L"Textures/UI/ExitButtonNormal.png",L"Textures/UI/ExitButtonActivated.png",[&]() 
		{
			OverlordGame::Stop();
		} });
	pButton->GetTransform()->Translate(100, 400, 0);
	m_pButtons.emplace_back(pButton);
}

void MainMenu::Update()
{
	if (InputManager::IsMouseButton(InputState::pressed, VK_LBUTTON))
	{
		for (Button* button : m_pButtons)
		{
			button->Press(m_SceneContext);
		}
	}
	POINT mousePos = InputManager::GetMousePosition();
	POINT prevMousePos = InputManager::GetMousePosition(true);
	if (mousePos.x != prevMousePos.x || mousePos.y != prevMousePos.y)
	{
		for (Button* button : m_pButtons)
		{
			button->IsHovering(m_SceneContext);
		}
	}
}
