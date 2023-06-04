#pragma once
class Bridge final : public GameObject
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
private:
	PxMaterial* m_pMaterial;
};