#include "stdafx.h"
#include "BombExplosion.h"
#include "Materials/Post/PostCameraShake.h"
#include "Character.h"
#include "Rock.h"

BombExplosion::BombExplosion(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
{
}

BombExplosion::~BombExplosion()
{
	SceneManager::Get()->GetActiveScene()->RemovePostProcessingEffect(m_pPostCameraShake);
}

void BombExplosion::Initialize(const SceneContext& sceneContext)
{
	m_StartTime = sceneContext.pGameTime->GetTotal();
	m_pPostCameraShake = MaterialManager::Get()->CreateMaterial<PostCameraShake>();
	SceneManager::Get()->GetActiveScene()->AddPostProcessingEffect(m_pPostCameraShake);

	auto pRigidBody = AddComponent(new RigidBodyComponent{ });
	pRigidBody->AddCollider(PxSphereGeometry{ 5.f } , *m_pMaterial, true);
	pRigidBody->SetConstraint(RigidBodyConstraint::All, false);

	SetOnTriggerCallBack([=](GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
		{
			OnHit(pTriggerObject, pOtherObject, action);
		});

	ParticleEmitterSettings particleEmitterSettings{};
	particleEmitterSettings.minSize = 1.5f;
	particleEmitterSettings.maxSize = 5.f;
	particleEmitterSettings.minEmitterRadius = 1.f;
	particleEmitterSettings.minEmitterRadius = 10.f;

	AddComponent(new ParticleEmitterComponent{ L"Textures/Smoke.png", particleEmitterSettings, 50 });

	auto fmodResult = SoundManager::Get()->GetSystem()->createChannelGroup("Sound Effects", &m_pSoundEffectGroup);
	SoundManager::Get()->ErrorCheck(fmodResult);

	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/Explosion.mp3", FMOD_DEFAULT, nullptr, &m_pExplosionSoundFx);
	SoundManager::Get()->ErrorCheck(fmodResult);

	SoundManager::Get()->GetSystem()->playSound(m_pExplosionSoundFx, m_pSoundEffectGroup, false, nullptr);
}

void BombExplosion::Update(const SceneContext& sceneContext)
{
	if (m_StartTime + m_Duration < sceneContext.pGameTime->GetTotal())
	{
		SceneManager::Get()->GetActiveScene()->RemoveChild(this, true);
	}
}

void BombExplosion::OnHit(GameObject* , GameObject* pOtherObject, PxTriggerAction )
{
	if (pOtherObject->GetTag() == L"Link")
	{
		Character* pCharacter = reinterpret_cast<Character*>(pOtherObject);
		pCharacter->Die();
	}
	if (pOtherObject->GetTag() == L"Rock")
	{
		Rock* pRock = reinterpret_cast<Rock*>(pOtherObject);
		pRock->SetMarkForDelete(true);
	}
}
