#include "stdafx.h"
#include "Bomb.h"
#include "BombExplosion.h"
#include "Character.h"

#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"

Bomb::Bomb(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
{
}

void Bomb::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Bomb/Bomb.ovm"));

	m_pDiffuseMaterialShadow = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	m_pDiffuseMaterialShadow->SetDiffuseTexture(L"Textures/Bomb/Bomb.png");
	pModel->SetMaterial(m_pDiffuseMaterialShadow);

	float scale{ .008f };
	GetTransform()->Scale(scale);

	m_pRigidBody = AddComponent(new RigidBodyComponent());
	m_pRigidBody->AddCollider(PxBoxGeometry{ .5f, 1.f, .5f }, *m_pMaterial, true);
	m_pRigidBody->SetKinematic(true);

	SetOnTriggerCallBack([=](GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
		{
			OnHit(pTriggerObject, pOtherObject, action);
		});

	SetTag(L"Bomb");
}

void Bomb::Update(const SceneContext& sceneContext)
{
	m_CanBombBePickedUp = true;
	if (m_IsCountingDown)
	{
		if (m_StartCountdownTime == 0)
		{
			m_LastTimeBlink = sceneContext.pGameTime->GetTotal();
			m_StartCountdownTime = sceneContext.pGameTime->GetTotal();
		}


		if (m_StartCountdownTime + m_TotalBlinkDuration < sceneContext.pGameTime->GetTotal())
		{
			//Boom
			BombExplosion* pBombExplosion = SceneManager::Get()->GetActiveScene()->AddChild(new BombExplosion(m_pMaterial));
			pBombExplosion->GetTransform()->Translate(GetTransform()->GetWorldPosition());
			m_IsCountingDown = false;
			SceneManager::Get()->GetActiveScene()->RemoveChild(this,true);
			return;
		}

		if (m_LastTimeBlink + m_BlinkDuration < sceneContext.pGameTime->GetTotal())
		{
			m_LastTimeBlink = sceneContext.pGameTime->GetTotal();
			m_BlinkDuration -= m_BlinkDurationShorteningIncrease;
			if (m_BlinkDuration < .1f) m_BlinkDuration = .1f;

			m_IsRed = !m_IsRed;
			if (m_IsRed)
			{
				m_pDiffuseMaterialShadow->SetDiffuseColor({ 1,0,0,1 });
			}
			else
			{
				m_pDiffuseMaterialShadow->SetDiffuseColor({ 1,1,1,1 });
			}
		}
	}
}

void Bomb::OnHit(GameObject* , GameObject* pOtherObject, PxTriggerAction action)
{
	if (m_IsPickedUp || !m_CanBombBePickedUp) return;

	if (pOtherObject->GetTag() == L"Link" && action == PxTriggerAction::ENTER)
	{
		Character* pCharacter = reinterpret_cast<Character*>(pOtherObject);

		if (pCharacter->PickUpBomb(this))
		{
			m_IsPickedUp = true;
			StartCountdown();
		}
	}
}

void Bomb::StartCountdown()
{
	m_IsCountingDown = true;
}

void Bomb::Launch(const XMFLOAT3& forward)
{
	m_pRigidBody->SetKinematic(false);
	m_pRigidBody->SetConstraint(RigidBodyConstraint::AllRot, false);
	m_pRigidBody->AddCollider(PxSphereGeometry{ .5f }, *m_pMaterial);
	m_pRigidBody->AddForce(forward);
}
