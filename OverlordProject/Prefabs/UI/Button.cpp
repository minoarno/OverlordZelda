#include "stdafx.h"
#include "Button.h"
#include "Prefabs/UI/Text.h"

Button::Button(const std::wstring& imgPathNormal, const std::wstring& imgPathActivated, const std::function<void()>& func)
	: GameObject{ }
	, m_Func{ func }
{
	m_pSpriteComponentNormal = AddComponent(new SpriteComponent(imgPathNormal));
	m_pSpriteComponentNormal->SetActive(true);
	m_pSpriteComponentActivated = AddComponent(new SpriteComponent(imgPathActivated));
	m_pSpriteComponentActivated->SetActive(false);
}


void Button::Initialize(const SceneContext&)
{
}

void Button::Update(const SceneContext&)
{
}

void Button::Select()
{
	m_IsSelected = !m_IsSelected;
}

void Button::SetSelect(bool value)
{
	m_IsSelected = value;
}

void Button::Press(const SceneContext& )
{
	if (m_IsSelected)
	{
		m_Func();
	}
}

bool Button::IsHovering(const SceneContext& sceneContext)
{
	auto mousePos = sceneContext.pInput->GetMousePosition();
	auto pos = GetTransform()->GetPosition();
	auto dims = m_pSpriteComponentNormal->GetDimensions();

	m_IsSelected = (pos.x < mousePos.x&& pos.x + dims.x > mousePos.x && pos.y < mousePos.y&& pos.y + dims.y > mousePos.y);
	m_pSpriteComponentActivated->SetActive(m_IsSelected);
	m_pSpriteComponentNormal->SetActive(!m_IsSelected);
	return m_IsSelected;
}
