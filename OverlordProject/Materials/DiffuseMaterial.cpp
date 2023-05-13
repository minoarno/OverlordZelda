#include "stdafx.h"
#include "DiffuseMaterial.h"
#include "Managers/ContentManager.h"
#include "Misc/TextureData.h"

DiffuseMaterial::DiffuseMaterial()
	: Material(L"Effects/PosNormTex3D.fx")
	, m_pDiffuseTexture{nullptr}
{
}

DiffuseMaterial::~DiffuseMaterial()
{
}

void DiffuseMaterial::SetDiffuseMaterial(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
	SetVariable_Texture(L"gDiffuseMap", m_pDiffuseTexture);
}

void DiffuseMaterial::InitializeEffectVariables()
{
}

void DiffuseMaterial::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModelComponent) const
{
	UNREFERENCED_PARAMETER(sceneContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}
