#include "stdafx.h"
#include "SpikyMaterial.h"

SpikyMaterial::SpikyMaterial() 
	: Material<SpikyMaterial>(L"Effects/SpikyShader.fx")
{}

SpikyMaterial::~SpikyMaterial()
{}

void SpikyMaterial::InitializeEffectVariables()
{
}

void SpikyMaterial::OnUpdateModelVariables(const SceneContext& , const ModelComponent* ) const
{
	//SetVariable_Texture(L"m_TextureDiffuse", m_pDiffuseTexture->GetShaderResourceView());
}