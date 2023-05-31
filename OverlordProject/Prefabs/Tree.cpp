#include "stdafx.h"
#include "Tree.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"

Tree::Tree(PxMaterial* pMaterial)
	: m_pMaterial{ pMaterial }
{
}

void Tree::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/PalmTree.ovm"));



#ifdef Deferred
	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseMap(L"Textures/PalmTree.png");
#else
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/PalmTree.png");
#endif
	pModel->SetMaterial(pMaterial);

	pModel->GetTransform()->Scale(.01f);
}