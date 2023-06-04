#include "stdafx.h"
#include "GemParticleEmitter.h"

GemParticleEmitter::GemParticleEmitter(const XMFLOAT4& color)
	: GameObject{}
	, m_Color{ color }
	, m_Duration{ 1.5f }
{
}

void GemParticleEmitter::Initialize(const SceneContext& sceneContext)
{
	m_StartCooldown = sceneContext.pGameTime->GetTotal();

	ParticleEmitterSettings settings{};
	settings.color = m_Color;
	settings.useParticleEmitterVelocity = false;
	settings.minEmitterRadius = 1.5f;
	settings.maxEmitterRadius = 3.f;
	settings.minSize = .1f;
	settings.maxSize = 1.6f;
	settings.velocity = { 0,1,0 };
	settings.useParticleEmitterVelocity = true;
	AddComponent(new ParticleEmitterComponent{ L"Textures/Sparkles.png",settings, 10 });

	auto fmodResult = SoundManager::Get()->GetSystem()->createChannelGroup("Sound Effects", &m_pSoundEffectGroup);
	SoundManager::Get()->ErrorCheck(fmodResult);

	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/CollectCoin.mp3", FMOD_DEFAULT, nullptr, &m_pCoinSoundFx);
	SoundManager::Get()->ErrorCheck(fmodResult);

	SoundManager::Get()->GetSystem()->playSound(m_pCoinSoundFx, m_pSoundEffectGroup, false, nullptr);
}

void GemParticleEmitter::Update(const SceneContext& sceneContext)
{
	if (m_StartCooldown + m_Duration < sceneContext.pGameTime->GetTotal())
	{
		SceneManager::Get()->GetActiveScene()->RemoveChild(this, true);
	}
}
