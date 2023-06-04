#pragma once
class PostCameraShake;
class BombExplosion final : public GameObject
{
public:
	BombExplosion(PxMaterial* pMaterial);
	BombExplosion(const BombExplosion&) = delete;
	BombExplosion& operator=(const BombExplosion&) = delete;
	BombExplosion(BombExplosion&&) = delete;
	BombExplosion& operator=(BombExplosion&&) = delete;
	~BombExplosion() override;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;

	void Update(const SceneContext&) override;
	void OnHit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
private:
	float m_StartTime{};
	float m_Duration = 0.5f;
	PostCameraShake* m_pPostCameraShake{ nullptr };
	PxMaterial* m_pMaterial{ nullptr };

	//Audio
	FMOD::Sound* m_pExplosionSoundFx{ nullptr };
	FMOD::ChannelGroup* m_pSoundEffectGroup{ nullptr };
	float m_MusicVolume{ .3f };
};