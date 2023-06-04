#pragma once
class RedGem final : public GameObject
{
public:
	RedGem(PxMaterial* pMaterial, const XMFLOAT4& pos);
	RedGem(const RedGem&) = delete;
	RedGem& operator=(const RedGem&) = delete;
	RedGem(RedGem&&) = delete;
	RedGem& operator=(RedGem&&) = delete;
	~RedGem() override = default;

	bool GetMarkForDelete()const { return m_MarkForDelete; };
	UINT GetLightIndex()const { return m_LightIndex; }
protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext&) override;

	void OnHit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
private:
	bool m_MarkForDelete{ false };
	PxMaterial* m_pMaterial{ nullptr };

	float m_Rotation;
	float m_RotationSpeed{ 90.f };
	XMFLOAT4 m_Position{};
	UINT m_LightIndex;
};