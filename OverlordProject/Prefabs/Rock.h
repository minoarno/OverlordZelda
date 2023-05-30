#pragma once

class Rock : public GameObject
{
public:
	Rock(const std::wstring& filepath, PxMaterial* pMaterial);
	Rock(const Rock&) = delete;
	Rock& operator=(const Rock&) = delete;
	Rock(Rock&&) = delete;
	Rock& operator=(Rock&&) = delete;
	~Rock() = default;

protected:
	virtual void Initialize(const SceneContext& scenetext) override;

private:
	std::wstring m_Filepath;
	PxMaterial* m_pMaterial;
};