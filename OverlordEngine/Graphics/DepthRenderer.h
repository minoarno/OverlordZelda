#pragma once
struct ID3D11ShaderResourceView;
class DepthRenderer final : public Singleton<DepthRenderer>
{
public:
	DepthRenderer(const DepthRenderer&) = delete;
	DepthRenderer& operator=(const DepthRenderer&) = delete;
	DepthRenderer(DepthRenderer&&) = delete;
	DepthRenderer& operator=(DepthRenderer&&) = delete;

	ID3D11ShaderResourceView* GetRenderTarget()const;
protected:
	void Initialize() override;

private:
	friend class Singleton<DepthRenderer>;
	DepthRenderer() = default;
	~DepthRenderer() = default;
};