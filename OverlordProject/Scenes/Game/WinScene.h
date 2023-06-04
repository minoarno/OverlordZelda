#pragma once
class WinScene final : public GameScene
{
public:
	WinScene();
	WinScene(const WinScene&) = delete;
	WinScene& operator=(const WinScene&) = delete;
	WinScene(WinScene&&) = delete;
	WinScene& operator=(WinScene&&) = delete;
	~WinScene();
protected:
	void Initialize() override;
	void Update() override;
};

