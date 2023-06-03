#include "stdafx.h"
#include "BombSpawner.h"
#include "Bomb.h"

#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"

BombSpawner::BombSpawner(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
	, m_pBomb{ nullptr }
{
}

void BombSpawner::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Bomb/BombLeaves.ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Bomb/Bomb.png");
	pModel->SetMaterial(pMaterial);

	pModel->GetTransform()->Scale(.01f);
}

void BombSpawner::Update(const SceneContext& )
{
	SpawnBomb();
}

void BombSpawner::SpawnBomb()
{
	if (m_pBomb == nullptr)
	{
		m_pBomb = GetScene()->AddChild(new Bomb(m_pMaterial));
		auto pos = GetTransform()->GetPosition();
		m_pBomb->GetTransform()->Translate(pos.x, pos.y, pos.z);
	}
}
