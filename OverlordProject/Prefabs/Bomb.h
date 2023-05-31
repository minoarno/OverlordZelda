
class Bomb final : public GameObject
{
public:
	Bomb(PxMaterial* pMaterial);
	Bomb(const Bomb&) = delete;
	Bomb& operator=(const Bomb&) = delete;
	Bomb(Bomb&&) = delete;
	Bomb& operator=(Bomb&&) = delete;
	~Bomb() = default;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;

private:
	PxMaterial* m_pMaterial;
};