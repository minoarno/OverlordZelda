#include "stdafx.h"
#include "Tree.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

Tree::Tree(PxMaterial* pMaterial)
	: m_pMaterial{ pMaterial }
{
}

void Tree::Initialize(const SceneContext& )
{
	AddComponent(new ModelComponent(L"Meshes/Tree.ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Tree.png");
}