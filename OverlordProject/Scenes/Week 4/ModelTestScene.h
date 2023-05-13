#pragma once

class ModelTestScene final : public GameScene
{
public:
	ModelTestScene();
	ModelTestScene(const ModelTestScene&) = delete;
	ModelTestScene& operator=(const ModelTestScene&) = delete;
	ModelTestScene(ModelTestScene&&) = delete;
	ModelTestScene& operator=(ModelTestScene&&) = delete;
	~ModelTestScene() = default;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;
private:
	GameObject* m_pChair;
};