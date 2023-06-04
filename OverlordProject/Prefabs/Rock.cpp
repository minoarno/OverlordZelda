#include "stdafx.h"
#include "Rock.h"
#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"

Rock::Rock(const std::wstring& filepath, PxMaterial* pMaterial, float scale)
	: GameObject{}
	, m_Filepath{ filepath }
	, m_pMaterial{ pMaterial }
	, m_Scale{ scale }
{
}

void Rock::Initialize(const SceneContext& )
{
	auto pModel = AddComponent(new ModelComponent(L"Meshes/Rocks/" + m_Filepath + L".ovm"));

	auto pMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMaterial->SetDiffuseTexture(L"Textures/Rocks/WindWaker_Rocks.png");

	const auto pTriangleMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Rocks/" + m_Filepath + L".ovpc");
	auto pRigidBody = AddComponent(new RigidBodyComponent{ true });
	pRigidBody->AddCollider(PxConvexMeshGeometry{ pTriangleMesh, physx::PxMeshScale{ m_Scale } }, *m_pMaterial);

	pModel->SetMaterial(pMaterial);
	SetTag(L"Rock");
}
