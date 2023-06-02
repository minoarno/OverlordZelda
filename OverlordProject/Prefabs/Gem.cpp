#include "stdafx.h"
#include "Gem.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"

#include "UI/HUD.h"

Gem::Gem(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
	, m_Rotation{ static_cast<float>(rand() % 360) }
{
}

void Gem::Initialize(const SceneContext& )
{
	float scale{ 0.005f };

	auto pModel = AddComponent(new ModelComponent(L"Meshes/Gem.ovm"));
#ifdef Deferred
	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseMap(L"Textures/Gem.png");
#else
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Gem.png");
#endif // Deferred
	pModel->SetMaterial(pMaterial);

	GetTransform()->Scale(scale);
	
	GetTransform()->Rotate(0, m_Rotation, 0);

	RigidBodyComponent* pRigidBody = AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry{ .5f, .5f, .5f }, *m_pMaterial, true);

	SetOnTriggerCallBack([=](GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
		{
			OnHit(pTriggerObject, pOtherObject, action);
		});
}

void Gem::Update(const SceneContext& sceneContext)
{
	m_Rotation += m_RotationSpeed * sceneContext.pGameTime->GetElapsed();
	if(m_Rotation > 360)m_Rotation -= 360;
	else if(m_Rotation < 0) m_Rotation += 360;

	GetTransform()->Rotate(0, m_Rotation, 0);
}

void Gem::OnHit(GameObject* , GameObject* pOtherObject, PxTriggerAction )
{
	if (!m_MarkForDelete && pOtherObject->GetTag() == L"Link")
	{
		m_MarkForDelete = true;
		HUD::Get()->IncreaseRupees(1);
	}
}
