#include "stdafx.h"
#include "ModelTestScene.h"

#include "Managers/PhysXManager.h"
#include "Components/RigidBodyComponent.h"

#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"

ModelTestScene::ModelTestScene()
	: GameScene{ L"ModelTestScene" }
	, m_pChair{nullptr}
{
}

void ModelTestScene::Initialize()
{
	//GROUND PLANE
	//************
	auto physX = PhysXManager::Get()->GetPhysics();

#pragma warning(push)
#pragma warning(disable:4189)
	auto pBouncyMaterial = physX->createMaterial(0, 0, 1);
	const auto pDefaultMaterial = physX->createMaterial(1.f, 1.f, 0.f);
	auto pGround = new GameObject();
	auto pRigidBodyGround = pGround->AddComponent(new RigidBodyComponent(true));

	pRigidBodyGround->AddCollider(physx::PxPlaneGeometry{}, *pBouncyMaterial, false, physx::PxTransform(physx::PxQuat(DirectX::XM_PIDIV2, physx::PxVec3(0, 0, 1))));
	AddChild(pGround);
#pragma warning(pop)
	//CHAIR OBJECT
	//************
	m_pChair = new GameObject();

	//1. Attach a modelcomponent (chair.ovm)
	//2. Create a ColorMaterial and add it to the material manager
	//3. Assign the material to the previous created modelcomponent
	// Build and Run
	ModelComponent* model = new ModelComponent(L"Meshes/Chair.ovm");
	m_pChair->AddComponent(model);

	DiffuseMaterial* diffuse = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	diffuse->SetDiffuseTexture(L"Textures/Chair_Dark.dds");
	model->SetMaterial(diffuse);

	RigidBodyComponent* pRigidBody{ new RigidBodyComponent{} };
	const auto pChairConvexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Chair.ovpc");
	pRigidBody->AddCollider(PxConvexMeshGeometry{ pChairConvexMesh }, *pDefaultMaterial);
	m_pChair->AddComponent(pRigidBody);

	m_pChair->GetTransform()->Translate(DirectX::XMVECTOR{ 0.f, 10.f, 0.f });

	AddChild(m_pChair);


}

void ModelTestScene::Update()
{}

void ModelTestScene::Draw()
{}

void ModelTestScene::OnGUI()
{
}
