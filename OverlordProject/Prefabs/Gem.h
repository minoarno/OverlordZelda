#pragma once
class Gem final : public GameObject
{
public:
	Gem(PxMaterial* pMaterial);
	Gem(const Gem&) = delete;
	Gem& operator=(const Gem&) = delete;
	Gem(Gem&&) = delete;
	Gem& operator=(Gem&&) = delete;
	~Gem() = default;

	bool GetMarkForDelete()const { return m_MarkForDelete; };
protected:
	void Initialize(const SceneContext& scenetext) override;
	void Update(const SceneContext&) override;

	void OnHit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
private:
	bool m_MarkForDelete{ false };

	PxMaterial* m_pMaterial;
	float m_Rotation;
	float m_RotationSpeed{90.f};
};