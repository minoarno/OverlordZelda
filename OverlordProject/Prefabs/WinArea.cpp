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

	auto fmodResult = SoundManager::Get()->GetSystem()->createChannelGroup("Sound Effects", &m_pSoundEffectGroup);
	SoundManager::Get()->ErrorCheck(fmodResult);

	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Victory.mp3", FMOD_DEFAULT, nullptr, &m_pVictorySoundFx);
	SoundManager::Get()->ErrorCheck(fmodResult);
}

void WinArea::OnHit(GameObject* , GameObject* pOtherObject, PxTriggerAction )
{
	if (pOtherObject->GetTag() == L"Link")
	{
		Character* pCharacter = reinterpret_cast<Character*>(pOtherObject);
		pCharacter->Reset();

		SceneManager::Get()->SetActiveGameScene(L"WinScene");
	
		SoundManager::Get()->GetSystem()->playSound(m_pVictorySoundFx, m_pSoundEffectGroup, false, nullptr);
		m_pSoundEffectGroup->setVolume(.2f);
	}
}
