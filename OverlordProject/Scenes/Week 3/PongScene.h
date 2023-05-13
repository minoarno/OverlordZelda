#pragma once

class FreeCamera;
class GameObject;
class PongScene final : public GameScene
{
public:
	PongScene();
	PongScene(const PongScene&) = delete;
	PongScene& operator=(const PongScene&) = delete;
	PongScene(PongScene&&) = delete;
	PongScene& operator=(PongScene&&) = delete;
	~PongScene() = default;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;
private:
	void Reset();

	FreeCamera* m_pFixedCamera{};

	GameObject* m_pBall = nullptr;
	GameObject* m_pPeddle1 = nullptr;
	GameObject* m_pPeddle2 = nullptr;
};
