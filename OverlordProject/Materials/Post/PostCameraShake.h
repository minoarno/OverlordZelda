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

protected:
	void Initialize(const GameContext& /*gameContext*/) override {}
};
