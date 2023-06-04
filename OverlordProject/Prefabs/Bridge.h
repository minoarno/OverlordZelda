#pragma once
class Bridge : public GameObject
{
public:
	Bridge(PxMaterial* pMaterial);
	Bridge(const Bridge&) = delete;
	Bridge& operator=(const Bridge&) = delete;
	Bridge(Bridge&&) = delete;
	Bridge& operator=(Bridge&&) = delete;
	~Bridge() override = default;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;

	void Update(const SceneContext&) override;
private:
	PxMaterial* m_pMaterial;
};