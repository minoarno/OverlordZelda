#include "stdafx.h"
#include "RedGem.h"

#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"
#include "UI/HUD.h"

RedGem::RedGem(PxMaterial* pMaterial, UINT lightIndex)
	: GameObject{ }
	, m_pMaterial{ pMaterial }
	, m_LightIndex{ lightIndex }
{
}

void RedGem::Initialize(const SceneContext& )
{
	float scale{ 0.005f };

	auto pModel = AddComponent(new ModelComponent(L"Meshes/Gem.ovm"));

	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Gem.png");
	pMaterial->SetDiffuseColor(XMFLOAT4{ 1,0,0,1 });
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

void RedGem::Update(const SceneContext& sceneContext)
{
	m_Rotation += m_RotationSpeed * sceneContext.pGameTime->GetElapsed();
	if (m_Rotation > 360)m_Rotation -= 360;
	else if (m_Rotation < 0) m_Rotation += 360;

	GetTransform()->Rotate(0, m_Rotation, 0);
}

void RedGem::OnHit(GameObject* , GameObject* pOtherObject, PxTriggerAction )
{
	if (!m_MarkForDelete && pOtherObject->GetTag() == L"Link")
	{
		m_MarkForDelete = true;
		HUD::Get()->IncreaseRedRupees(1);
	}
}