#include "stdafx.h"
#include "Bridge.h"


#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"

Bridge::Bridge(PxMaterial* pMaterial)
	: GameObject{ }
	, m_pMaterial{ pMaterial }
{
}

void Bridge::Initialize(const SceneContext& )
{
	float scale{ .01f };
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Bridge.ovm"));

	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Bridge.png");

	pModel->SetMaterial(pMaterial);
	pModel->GetTransform()->Scale(scale);

	const auto pTriangleMesh = ContentManager::Load<PxTriangleMesh>(L"Meshes/Bridge.ovpt");
	auto pRigidBody = AddComponent(new RigidBodyComponent{ true });
	pRigidBody->AddCollider(PxTriangleMeshGeometry{ pTriangleMesh, physx::PxMeshScale{ scale } }, *m_pMaterial);
}

void Bridge::Update(const SceneContext&)
{
}
