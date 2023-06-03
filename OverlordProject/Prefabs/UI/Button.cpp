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
	if (m_Disabled)return;
	m_IsSelected = !m_IsSelected;
}

void Button::SetSelect(bool value)
{
	if (m_Disabled)return;
	m_IsSelected = value;
	UpdateSprites();
}

void Button::Press(const SceneContext& )
{
	if (m_Disabled)return;
	if (m_IsSelected)
	{
		m_Func();
	}
}

bool Button::IsHovering(const SceneContext& sceneContext)
{
	if (m_Disabled)
	{
		m_IsSelected = false;
		return false;
	}
	auto mousePos = sceneContext.pInput->GetMousePosition();
	auto pos = GetTransform()->GetPosition();
	auto dims = m_pSpriteComponentNormal->GetDimensions();

	m_IsSelected = (pos.x < mousePos.x&& pos.x + dims.x > mousePos.x && pos.y < mousePos.y&& pos.y + dims.y > mousePos.y);
	UpdateSprites();
	return m_IsSelected;
}

void Button::Enable()
{
	m_Disabled = false;
	//UpdateSprites();
	m_pSpriteComponentActivated->SetActive(true);
	m_pSpriteComponentNormal->SetActive(true);
}

void Button::Disable()
{
	m_Disabled = true;
	m_pSpriteComponentActivated->SetActive(false);
	m_pSpriteComponentNormal->SetActive(false);
}

void Button::UpdateSprites()
{
	m_pSpriteComponentActivated->SetActive(m_IsSelected);
	m_pSpriteComponentNormal->SetActive(!m_IsSelected);
}
