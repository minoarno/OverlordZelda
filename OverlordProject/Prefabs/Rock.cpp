#include "stdafx.h"
#include "Rock.h"
#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"

Rock::Rock(const std::wstring& filepath, PxMaterial* pMaterial)
	: GameObject{}
	, m_Filepath{ filepath }
	, m_pMaterial{ pMaterial }
{
}

void Rock::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Rocks/" + m_Filepath + L".ovm"));

#ifdef Deferred
	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseMap(L"Textures/Rocks/WindWaker_Rocks.png");
#else
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Rocks/WindWaker_Rocks.png");
#endif

	pModel->SetMaterial(pMaterial);

}
