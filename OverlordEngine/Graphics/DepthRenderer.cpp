#include "stdafx.h"
#include "DepthRenderer.h"
#include "Misc/RenderTarget.h"

ID3D11ShaderResourceView* DepthRenderer::GetRenderTarget() const
{
	return m_GameContext.pGame->GetRenderTarget()->GetDepthShaderResourceView();
}

void DepthRenderer::Initialize()
{
}