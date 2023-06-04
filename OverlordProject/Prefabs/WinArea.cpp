#include "stdafx.h"
#include "WinArea.h"

WinArea::WinArea(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
{
}

void WinArea::Initialize(const SceneContext& scenetext)
{
	RigidBodyComponent* pRigidBody = AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry{ 2.f, 2.f, 2.f }, *m_pMaterial, true);

	SetOnTriggerCallBack([=](GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
		{
			OnHit(pTriggerObject, pOtherObject, action);
		});
}

void WinArea::OnHit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pOtherObject->GetTag() == L"Link")
	{
		SceneManager::Get()->SetActiveGameScene(L"WinScene");
	}
}
