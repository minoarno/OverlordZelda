#include "stdafx.h"
#include "HUD.h"
#include "Prefabs/UI/Text.h"

HUD* HUD::m_pHUD{ nullptr };

HUD::HUD()
	: GameObject{ }
	, m_AmountOfRupeesCollected{ 0 }
	, m_pRupeesText{ nullptr }
{
}

void HUD::Initialize(const SceneContext&)
{
	float x{ 1000 };
	m_pRupeesText = AddChild(new Text{ "" });
	m_pRupeesText->GetTransform()->Translate(x, 20.f, 0.f);
	UpdateRupeesText();

	auto go = AddChild(new GameObject{});
	m_pRupee = go->AddComponent(new SpriteComponent{ L"Textures/UI/Rupees.png" });
	go->GetTransform()->Translate(x - 45.f, 10.f, 0.f);
	go->GetTransform()->Scale(.25f, .25f, 0.5f);

	//Hearts
	for (size_t i = 0; i < m_AmountOfHearts; i++)
	{
		m_pHearts.emplace_back(AddChild(new GameObject{}));
		m_pHearts[i]->AddComponent(new SpriteComponent{L"Textures/UI/Heart.png"});
		m_pHearts[i]->GetTransform()->Translate(45.f + 50 * i, 10.f, 0.f);
		m_pHearts[i]->GetTransform()->Scale(.05f, .05f, 0.5f);
	}

	if (m_pHUD == nullptr)
	{
		m_pHUD = this;
	}
}

void HUD::Draw(const SceneContext& sceneContext)
{
	m_pRupeesText->Draw(sceneContext);
}

void HUD::SetAmountOfHearts(int amount)
{
	m_AmountOfHearts = amount;

	for (size_t i = 0; i < m_pHearts.size(); i++)
	{
		m_pHearts[i]->GetComponent<SpriteComponent>()->SetActive(m_AmountOfHearts > i);
	}
}

void HUD::SetAmountRupees(int amount)
{
	m_AmountOfRupeesCollected = amount;
	UpdateRupeesText();
}

void HUD::IncreaseRupees(int amount)
{
	m_AmountOfRupeesCollected += amount;
	UpdateRupeesText();
}

void HUD::UpdateRupeesText()
{
	m_pRupeesText->SetText(std::to_string(m_AmountOfRupeesCollected));
}