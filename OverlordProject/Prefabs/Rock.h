#pragma once

class Rock final: public GameObject
{
public:
	Rock(const std::wstring& filepath, PxMaterial* pMaterial, float scale = 1.f);
	Rock(const Rock&) = delete;
	Rock& operator=(const Rock&) = delete;
	Rock(Rock&&) = delete;
	Rock& operator=(Rock&&) = delete;
	~Rock() override = default;

	bool GetMarkForDelete()const { return m_MarkForDelete; };
	void SetMarkForDelete(bool value) { m_MarkForDelete = value; }
protected:
	virtual void Initialize(const SceneContext& scenetext) override;

	void Update(const SceneContext&) override;
private:
	bool m_MarkForDelete{ false };

	std::wstring m_Filepath;
	PxMaterial* m_pMaterial;
	float m_Scale{1};
};