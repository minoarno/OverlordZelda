#include "stdafx.h"
#include "Level1.h"
#include "Materials/DiffuseMaterial.h"
#include "Materials/SeaMaterial.h"
#include "Prefabs/Character.h"

Level1::Level1()
	: GameScene{L"Level1"}
	, m_pCharacter{ nullptr }
	, m_pSea{ nullptr }
	, m_pSeaMaterial{ nullptr }
{
}

void Level1::Initialize()
{
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;

	auto physX = PhysXManager::Get()->GetPhysics();
	const auto pDefaultMaterial = physX->createMaterial(1.f, 1.f, 0.f);

	AddLevel(pDefaultMaterial);
	//AddPlayer(pDefaultMaterial);

	AddSea();
}

void Level1::AddPlayer(PxMaterial* pDefaultMaterial)
{
	CharacterDesc characterDesc{ pDefaultMaterial, .25f,1.f };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;

	m_pCharacter = AddChild(new Character(characterDesc));
	m_pCharacter->GetTransform()->Translate(0.f, 5.f, 0.f);
	m_pCharacter->GetTransform()->Scale(0.5f);

	//Input
	auto inputAction = InputAction(CharacterMoveLeft, InputState::down, 'A');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveRight, InputState::down, 'D');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveForward, InputState::down, 'W');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveBackward, InputState::down, 'S');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterJump, InputState::pressed, VK_SPACE, -1, XINPUT_GAMEPAD_A);
	m_SceneContext.pInput->AddInputAction(inputAction);
}

void Level1::AddLevel(PxMaterial* pDefaultMaterial)
{
	GameObject* pGameObject = AddChild(new GameObject());
	ModelComponent* pModelComponent = pGameObject->AddComponent(new ModelComponent(L"Meshes/Zelda/SmallIsland.ovm"));

	const auto pTriangleMesh = ContentManager::Load<PxTriangleMesh>(L"Meshes/Zelda/SmallIsland.ovpt");
	auto pRigidBody = pGameObject->AddComponent(new RigidBodyComponent{ true });
	pRigidBody->AddCollider(PxTriangleMeshGeometry{ pTriangleMesh }, *pDefaultMaterial);

	AddLevelObject(pModelComponent, 0, L"Woods");
	AddLevelObject(pModelComponent, 1, L"Roofs");
	AddLevelObject(pModelComponent, 2, L"Ballustrade");
	AddLevelObject(pModelComponent, 3, L"Bridge");
	AddLevelObject(pModelComponent, 4, L"RockWithGrass");
	AddLevelObject(pModelComponent, 5, L"BigRocks");
	AddLevelObject(pModelComponent, 6, L"Grass");
	AddLevelObject(pModelComponent, 7, L"RandomRocks");
}

void Level1::AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename)
{
	DiffuseMaterial* pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pMat->SetDiffuseTexture(L"Textures/Zelda/" + filename + L".png");
	pModelComponent->SetMaterial(pMat, id);
}

void Level1::AddSea()
{
	m_pSea = AddChild(new GameObject());
	ModelComponent* pModelComponent = m_pSea->AddComponent(new ModelComponent(L"Meshes/Zelda/Sea.ovm"));
	m_pSea->GetTransform()->Translate(0, 0.5f, 0);
	m_pSea->GetTransform()->Rotate(90, 0, 0);
	m_pSea->GetTransform()->Scale(100);
	m_pSeaMaterial = MaterialManager::Get()->CreateMaterial<SeaMaterial>();
	m_pSeaMaterial->SetWaterColor(DirectX::XMFLOAT4{ 0.2006942f, 0.3961588f, 0.7735849f, 1.f });
	m_pSeaMaterial->SetRippleSpeed(2);
	m_pSeaMaterial->SetRippleDensity(21);
	m_pSeaMaterial->SetRippleSlimness(8);
	m_pSeaMaterial->SetRippleColor(DirectX::XMFLOAT4{ 0.5506853f, 0.8630115f, 0.9339623f, 1.f });
	m_pSeaMaterial->SetWaveSpeed(0.1f);
	m_pSeaMaterial->SetWaveScale(0.1f);
	m_pSeaMaterial->SetFoamAmount(0.79f);
	m_pSeaMaterial->SetFoamCutoff(2.7f);
	m_pSeaMaterial->SetFoamScale(150.f);
	m_pSeaMaterial->SetFoamSpeed(0.03f);
	m_pSeaMaterial->SetFoamColor(DirectX::XMFLOAT4{ 1.f,1.f,1.f, 1.f });
	m_pSeaMaterial->SetPerlinNoise(L"Textures/Zelda/PerlinNoise.jpg");
	pModelComponent->SetMaterial(m_pSeaMaterial);
}

void Level1::OnGUI()
{
	m_pSeaMaterial->DrawImGui();

	auto curPos = m_pSea->GetTransform()->GetWorldPosition();
	float pos[3]{ curPos.x, curPos.y, curPos.z };

	ImGui::DragFloat3("Translation", pos, 0.1f, -300, 300);
	m_pSea->GetTransform()->Translate(pos[0], pos[1], pos[2]);
}
