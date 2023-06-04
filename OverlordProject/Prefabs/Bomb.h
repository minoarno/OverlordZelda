class BasicMaterial_Deferred_Shadow;
class RigidBodyComponent;
class Bomb final : public GameObject
{
public:
	Bomb(PxMaterial* pMaterial);
	Bomb(const Bomb&) = delete;
	Bomb& operator=(const Bomb&) = delete;
	Bomb(Bomb&&) = delete;
	Bomb& operator=(Bomb&&) = delete;
	~Bomb() = default;

	void StartCountdown();
	void Launch(const XMFLOAT3& forward);
protected:
	virtual void Initialize(const SceneContext& scenetext) override;

	void Update(const SceneContext&) override;
	void OnHit(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
private:
	PxMaterial* m_pMaterial;

	BasicMaterial_Deferred_Shadow* m_pDiffuseMaterialShadow;
	RigidBodyComponent* m_pRigidBody;

	bool m_CanBombBePickedUp{ false };
	bool m_IsPickedUp{ false };
	bool m_IsCountingDown{ false };
	bool m_IsRed{ false };

	float m_LastTimeBlink{};
	float m_StartCountdownTime{};
	float m_TotalBlinkDuration = 5.f;
	float m_BlinkDuration = .8f;
	float m_BlinkDurationShorteningIncrease = .1f;
};