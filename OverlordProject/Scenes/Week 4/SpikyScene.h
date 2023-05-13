#pragma once
class SpikyScene : public GameScene
{
public:
	SpikyScene();
	SpikyScene(const SpikyScene&) = delete;
	SpikyScene& operator=(const SpikyScene&) = delete;
	SpikyScene(SpikyScene&&) = delete;
	SpikyScene& operator=(SpikyScene&&) = delete;
	~SpikyScene() = default;

protected:
	void Initialize() override;
};