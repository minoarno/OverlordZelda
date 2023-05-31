#include "stdafx.h"
#include "BombSpawner.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

BombSpawner::BombSpawner(PxMaterial* pMaterial)
	: GameObject{}
	, m_pMaterial{ pMaterial }
{
}

void BombSpawner::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/BombLeaves.ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Bomb.png");
	pModel->SetMaterial(pMaterial);
}
