#pragma once
class Text;
class HUD : public GameObject
{
public:
	HUD();
	~HUD() override = default;

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) noexcept = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) noexcept = delete;

	void Initialize(const SceneContext&) override;
	void Draw(const SceneContext&) override;

	void SetAmountOfHearts(int amount);

	void SetAmountRupees(int amount);
	void IncreaseRupees(int amount);
	static HUD* Get() { return m_pHUD; };
	void ResetHUD() { m_pHUD = nullptr; };
private:
	static HUD* m_pHUD;
	int m_AmountOfRupeesCollected{ 0 };
	SpriteComponent* m_pRupee{nullptr};
	Text* m_pRupeesText{nullptr};
	void UpdateRupeesText();

	int m_AmountOfHearts{ 3 };
	std::vector<GameObject*> m_pHearts{};
};

