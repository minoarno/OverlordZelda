#pragma once
class GemParticleEmitter : public GameObject
{
public:
	GemParticleEmitter(const XMFLOAT4& color);
	GemParticleEmitter(const GemParticleEmitter&) = delete;
	GemParticleEmitter& operator=(const GemParticleEmitter&) = delete;
	GemParticleEmitter(GemParticleEmitter&&) = delete;
	GemParticleEmitter& operator=(GemParticleEmitter&&) = delete;
	~GemParticleEmitter() override = default;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
private:
	XMFLOAT4 m_Color{};

	float m_StartCooldown{};
	float m_Duration{1.5f};

	//Audio
	FMOD::Sound* m_pCoinSoundFx{ nullptr };
	FMOD::ChannelGroup* m_pSoundEffectGroup{ nullptr };
	float m_MusicVolume{.3f};
};