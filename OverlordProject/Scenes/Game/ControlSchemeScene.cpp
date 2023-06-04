#include "stdafx.h"
#include "ControlSchemeScene.h"

#include "Prefabs/UI/Button.h"

ControlSchemeScene::ControlSchemeScene()
	: GameScene{L"ControlSchemeScene"}
{
}

ControlSchemeScene::~ControlSchemeScene()
{
}

void ControlSchemeScene::Initialize()
{
	m_pControlSchemeStart = AddChild(new Button{ L"Textures/UI/StartButtonNormal.png",L"Textures/UI/StartButtonActivated.png",[&]()
	{
		SceneManager::Get()->SetActiveGameScene(L"Level1");
	} });
	m_pControlSchemeStart->GetTransform()->Translate(500, 600, 0);

	auto inputAction = InputAction(SettingsMoveUp, InputState::pressed, -1, -1, XINPUT_GAMEPAD_DPAD_UP);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(SettingsMoveDown, InputState::pressed, -1, -1, XINPUT_GAMEPAD_DPAD_DOWN);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(SettingsPress, InputState::pressed, -1, VK_LBUTTON, XINPUT_GAMEPAD_A);
	m_SceneContext.pInput->AddInputAction(inputAction);

	auto pControlSchemeBackground = AddChild(new GameObject{})->AddComponent(new SpriteComponent{ L"Textures/UI/ControlScheme.png" });
	pControlSchemeBackground->GetTransform()->Scale(1.5);
}

void ControlSchemeScene::Update()
{
	if (m_SceneContext.pInput->IsActionTriggered(SettingsMoveUp) || m_SceneContext.pInput->IsActionTriggered(SettingsPress))
	{
		m_pControlSchemeStart->SetSelect(true);
	}

	if (m_SceneContext.pInput->IsActionTriggered(SettingsPress))
	{
		m_pControlSchemeStart->Press(m_SceneContext);
	}

	if (m_SceneContext.pInput->IsMouseButton(InputState::pressed, VK_LBUTTON))
	{
		if (m_pControlSchemeStart->IsHovering(m_SceneContext))
		{
			m_pControlSchemeStart->Press(m_SceneContext);
		}
	}

	POINT mousePos = InputManager::GetMousePosition();
	POINT prevMousePos = InputManager::GetMousePosition(true);
	if (mousePos.x != prevMousePos.x || mousePos.y != prevMousePos.y)
	{
		m_pControlSchemeStart->IsHovering(m_SceneContext);
	}
}