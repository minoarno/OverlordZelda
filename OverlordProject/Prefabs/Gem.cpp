#include "stdafx.h"
#include "Gem.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

Gem::Gem(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
{
}

void Gem::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Gem.ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Gem.png");
	pModel->SetMaterial(pMaterial);

	GetTransform()->Scale(1.f);
}