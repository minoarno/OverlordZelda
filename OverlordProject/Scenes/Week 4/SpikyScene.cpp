#include "stdafx.h"
#include "SpikyScene.h"

#include "Materials/SpikyMaterial.h"

SpikyScene::SpikyScene()
	:GameScene{ L"SpikyScene" }
{
}

void SpikyScene::Initialize()
{
	auto pSphere = new GameObject();
	ModelComponent* model = new ModelComponent(L"Meshes/Teapot.ovm");
	pSphere->AddComponent(model);

	SpikyMaterial* spikyMat = MaterialManager::Get()->CreateMaterial<SpikyMaterial>();
	model->SetMaterial(spikyMat);

	AddChild(pSphere);
}
