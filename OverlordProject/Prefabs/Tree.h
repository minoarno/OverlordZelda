#pragma once
class Tree final : public GameObject
{
public:
	Tree(PxMaterial* pMaterial);
	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;
	Tree(Tree&&) = delete;
	Tree& operator=(Tree&&) = delete;
	~Tree() = default;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;

private:
	PxMaterial* m_pMaterial;
};
