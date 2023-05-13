#include "stdafx.h"
#include "UberMaterialScene.h"

#include "Materials/UberMaterial.h"
#include "Managers/MaterialManager.h"

UberMaterialScene::UberMaterialScene()
	: GameScene{ L"UberMaterialScene" }
{
}

void UberMaterialScene::Initialize()
{
	auto sceneContext = GetSceneContext();

	//TEAPOT
	//******
	auto pTeapot{ new GameObject() };
	pTeapot->GetTransform()->Translate(DirectX::XMVECTOR{ 0.f, 0.5f, 0.f });
	ModelComponent* pModel{ new ModelComponent{ L"Meshes/Teapot.ovm" } };
	pTeapot->AddComponent(pModel);
	UberMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();
	pMaterial->EnableEnvironmentMapping(true);
	pMaterial->SetEnvironmentCube(L"Textures/Sunol_Cubemap.dds");
	pMaterial->SetReflectionStrength(1.0f);
	pMaterial->SetDiffuseColor(DirectX::XMFLOAT4{ 0.5f, 0.4f, 0.0f, 1.0f });
	pMaterial->EnableSpecularPhong(true);
	pMaterial->SetAmbientIntensity(1);
	pMaterial->EnableDiffuseTexture(true);
	pMaterial->SetDiffuseTexture(L"Textures/Skulls Textures/Skulls_Diffusemap.tga");
	pMaterial->EnableNormalMapping(true);
	pMaterial->SetNormalMapTexture(L"Textures/Skulls Textures/Skulls_Normalmap.tga");
	pMaterial->SetDiffuseColor(DirectX::XMFLOAT4{ 1,0,0,1 });

	pModel->SetMaterial(pMaterial);
	AddChild(pTeapot);
}
