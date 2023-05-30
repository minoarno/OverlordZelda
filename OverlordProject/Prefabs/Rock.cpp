#include "stdafx.h"
#include "Rock.h"
#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

Rock::Rock(const std::wstring& filepath, PxMaterial* pMaterial)
	: GameObject{}
	, m_Filepath{ filepath }
	, m_pMaterial{ pMaterial }
{
}

void Rock::Initialize(const SceneContext& )
{
	AddComponent(new ModelComponent(L"Meshes/Rocks/" + m_Filepath + L".ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Rocks/WindWaker_Rocks.png");
}
