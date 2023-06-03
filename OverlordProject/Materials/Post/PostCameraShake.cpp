#include "stdafx.h"
#include "PostCameraShake.h"

PostCameraShake::PostCameraShake()
	: PostProcessingMaterial(L"Effects/Post/CameraShake.fx")
{
}

void PostCameraShake::UpdateBaseEffectVariables(const SceneContext& , RenderTarget* pSource)
{
	//Set Source Texture
	const auto pSourceSRV = pSource->GetColorShaderResourceView();
	m_pBaseEffect->GetVariableByName("gTexture")->AsShaderResource()->SetResource(pSourceSRV);
	//From this point on, pSource (RenderTarget) is bound as an SRV (ShaderResourceView, read from) to the pipeline
	//In case we want to use pSource as a RTV (RenderTargetView, render to) we have to unbind it first as an SRV

	float dampener{ 10 };
	XMFLOAT2 pDirection{ (rand() % (m_Offset * 2) - m_Offset) / float(m_Offset * dampener),(rand() % (m_Offset * 2) - m_Offset) / float(m_Offset * dampener) };
	m_pBaseEffect->GetVariableByName("gTexelSize")->AsVector()->SetFloatVector(reinterpret_cast<float*>(&pDirection));
}
