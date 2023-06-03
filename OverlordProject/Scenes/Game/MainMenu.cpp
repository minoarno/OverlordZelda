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

	auto inputAction = InputAction(SettingsMoveUp, InputState::pressed, -1, -1, XINPUT_GAMEPAD_DPAD_UP);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(SettingsMoveDown, InputState::pressed, -1, -1, XINPUT_GAMEPAD_DPAD_DOWN);
	m_SceneContext.pInput->AddInputAction(inputAction);
}

void MainMenu::Update()
{
	if (m_SceneContext.pInput->IsActionTriggered(SettingsMoveUp))
	{
		if (m_SelectedButtonIndex == -1)
		{
			m_SelectedButtonIndex = 0;
		}
		else
		{
			m_SelectedButtonIndex--;
			if (m_SelectedButtonIndex < 0) m_SelectedButtonIndex = static_cast<int>(m_pButtons.size()) - 1;
		}
		
		for (size_t i = 0; i < m_pButtons.size(); i++)
		{
			m_pButtons[i]->SetSelect(m_SelectedButtonIndex == i);
		}
	}
	if (m_SceneContext.pInput->IsActionTriggered(SettingsMoveUp))
	{
		if (m_SelectedButtonIndex == -1)
		{
			m_SelectedButtonIndex = 0;
		}
		else
		{
			m_SelectedButtonIndex++;
			if (m_SelectedButtonIndex >= m_pButtons.size()) m_SelectedButtonIndex = 0;
		}

		for (size_t i = 0; i < m_pButtons.size(); i++)
		{
			m_pButtons[i]->SetSelect(m_SelectedButtonIndex == i);
		}
	}

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
