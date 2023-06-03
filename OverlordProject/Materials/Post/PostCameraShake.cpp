#include "stdafx.h"
#include "PostCameraShake.h"

PostCameraShake::PostCameraShake()
	: PostProcessingMaterial(L"Effects/Post/CameraShake.fx")
{
}

void PostCameraShake::UpdateBaseEffectVariables(const SceneContext& sceneContext, RenderTarget* pSource)
{
	PostProcessingMaterial::UpdateBaseEffectVariables(sceneContext, pSource);
}
