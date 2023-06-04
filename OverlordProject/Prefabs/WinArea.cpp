#include "stdafx.h"
#include "WinArea.h"

#include "Character.h"

WinArea::WinArea(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
{
}

void WinArea::Initialize(const SceneContext& )
{
	RigidBodyComponent* pRigidBody = AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry{ 2.f, 2.f, 2.f }, *m_pMaterial, true);

	SetOnTriggerCallBack([=](GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
		{
			OnHit(pTriggerObject, pOtherObject, action);
		});
}

void WinArea::OnHit(GameObject* , GameObject* pOtherObject, PxTriggerAction )
{
	if (pOtherObject->GetTag() == L"Link")
	{
		Character* pCharacter = reinterpret_cast<Character*>(pOtherObject);
		pCharacter->Reset();

		SceneManager::Get()->SetActiveGameScene(L"WinScene");
	}
}
