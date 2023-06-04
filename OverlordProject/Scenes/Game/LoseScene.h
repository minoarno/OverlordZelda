#pragma once

class LoseScene : public GameScene
{
public:
	LoseScene();
	LoseScene(const LoseScene&) = delete;
	LoseScene& operator=(const LoseScene&) = delete;
	LoseScene(LoseScene&&) = delete;
	LoseScene& operator=(LoseScene&&) = delete;
	~LoseScene();

protected:
	void Initialize() override;
	void Update() override;
};