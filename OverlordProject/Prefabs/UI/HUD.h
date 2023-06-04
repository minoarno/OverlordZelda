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
	void DecreaseHearts();
	int GetAmountOfHearts()const { return m_AmountOfHearts; }

	void SetAmountRupees(int amount);
	void SetAmountRedRupees(int amount);
	void IncreaseRupees(int amount);
	void IncreaseRedRupees(int amount);

	static HUD* Get() { return m_pHUD; };
	void ResetHUD() { m_pHUD = nullptr; };
private:
	static HUD* m_pHUD;
	
	int m_AmountOfRedRupeesCollected{ 0 };
	int m_MaxAmountOfRedRupeesCollected{ 3 };
	SpriteComponent* m_pRedRupee{ nullptr };
	Text* m_pRedRupeesText{ nullptr };
	void UpdateRedRupeesText();

	int m_AmountOfRupeesCollected{ 0 };
	SpriteComponent* m_pRupee{nullptr};
	Text* m_pRupeesText{nullptr};
	void UpdateRupeesText();

	int m_AmountOfHearts{ 3 };
	std::vector<GameObject*> m_pHearts{};
};

