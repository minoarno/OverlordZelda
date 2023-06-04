#pragma once
class WinArea final : public GameObject
{
public:
	WinArea(PxMaterial* pMaterial);
	WinArea(const WinArea&) = delete;
	WinArea& operator=(const WinArea&) = delete;
	WinArea(WinArea&&) = delete;
	WinArea& operator=(WinArea&&) = delete;
	~WinArea() override = default;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;
	void OnHit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
private:
	PxMaterial* m_pMaterial;

	//Audio
	FMOD::Sound* m_pVictorySoundFx{ nullptr };
	FMOD::ChannelGroup* m_pSoundEffectGroup{ nullptr };
	float m_MusicVolume{ .3f };
};