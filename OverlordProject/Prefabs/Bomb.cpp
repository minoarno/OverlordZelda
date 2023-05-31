#include "stdafx.h"
#include "Bomb.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

Bomb::Bomb(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
{
}

void Bomb::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Bomb.ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Bomb.png");
	pModel->SetMaterial(pMaterial);
}
