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

void BombSpawner::Initialize(const SceneContext& sceneContext)
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Bomb/BombLeaves.ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Bomb/Bomb.png");
	pModel->SetMaterial(pMaterial);
	pModel->GetTransform()->Scale(.01f);
	
	m_pGameTime = sceneContext.pGameTime;

	auto pRigidBody = AddComponent(new RigidBodyComponent());
	pRigidBody->AddCollider(PxBoxGeometry{ 2.f, 2.f, 2.f }, *m_pMaterial, true);
	pRigidBody->SetConstraint(RigidBodyConstraint::All, false);

	m_StartBombSpawn = sceneContext.pGameTime->GetTotal() - 1;
}

void BombSpawner::Update(const SceneContext& )
{
	if (m_pBomb != nullptr)
	{
		if (m_pBomb->IsBombPickedUp())
		{
			m_pBomb = nullptr;
			m_StartBombSpawn = m_pGameTime->GetTotal();
		}
		return;
	}

	if (m_StartBombSpawn + m_BombSpawnDuration < m_pGameTime->GetTotal())
	{
		m_pBomb = GetScene()->AddChild(new Bomb(m_pMaterial));
		auto pos = GetTransform()->GetPosition();
		m_pBomb->GetTransform()->Translate(pos.x, pos.y, pos.z);
	}
}