#pragma once
class PostCameraShake : public PostProcessingMaterial
{
public:
	PostCameraShake();
	PostCameraShake(const PostCameraShake&) = delete;
	PostCameraShake& operator=(const PostCameraShake&) = delete;
	PostCameraShake(PostCameraShake&&) = delete;
	PostCameraShake& operator=(PostCameraShake&&) = delete;
	~PostCameraShake() override = default;

	int GetOffset()const { return m_Offset; }
	void SetOffset(int value) { m_Offset = value; }
protected:
	void Initialize(const GameContext& /*gameContext*/) override {}

	void UpdateBaseEffectVariables(const SceneContext& sceneContext, RenderTarget* pSource) override;

	int m_Offset{ 10 };
};
