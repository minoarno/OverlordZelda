#include "stdafx.h"
#include "Level1.h"
#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "Materials/Shadow/DiffuseMaterial_Shadow_Skinned.h"
#include "Materials/Deferred/BasicMaterial_Deferred_Shadow.h"
#include "Materials/Deferred/BasicMaterial_Deferred_Shadow_Skinned.h"
#include "Materials/SkyBoxMaterial.h"
#include "Materials/SeaMaterial.h"
#include "Prefabs/Character.h"
#include "Prefabs/Tree.h"
#include "Prefabs/Rock.h"
#include "Prefabs/Gem.h"

Level1::Level1()
	: GameScene{L"Level1"}
	, m_pCharacter{ nullptr }
	, m_pSea{ nullptr }
	, m_pSeaMaterial{ nullptr }
	, m_pObject{ nullptr }
{
}

void Level1::Initialize()
{
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawPhysXDebug = false;
#ifdef Deferred
	m_SceneContext.useDeferredRendering = true;
#else
	m_SceneContext.useDeferredRendering = false;
#endif

	//m_SceneContext.pLights->SetDirectionalLight({ -95.6139526f,66.1346436f,-41.1850471f }, { 0.740129888f, -0.597205281f, 0.309117377f });
	m_SceneContext.pLights->SetDirectionalLight({ 0,0,0 }, { -160, -66, 20 });

	auto physX = PhysXManager::Get()->GetPhysics();
	const auto pDefaultMaterial = physX->createMaterial(1.f, 1.f, 0.f);

	AddLevel(pDefaultMaterial);
	AddPlayer(pDefaultMaterial);

	AddSea();
	AddSkyBox();
}

GameObject* Level1::AddPlayer(PxMaterial* pDefaultMaterial)
{
	CharacterDesc characterDesc{ pDefaultMaterial, .5f,2.f };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;

	m_pCharacter = AddChild(new Character(characterDesc, {0,3,15}));
	m_pCharacter->GetTransform()->Translate(0.f, 5.f, 0.f);

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

	return m_pCharacter;
}

GameObject* Level1::AddLevel(PxMaterial* pDefaultMaterial)
{
	float scale = 2;

	GameObject* pLevel = new GameObject();
	ModelComponent* pModelComponent = pLevel->AddComponent(new ModelComponent(L"Meshes/Zelda/SmallIsland.ovm"));

	const auto pTriangleMesh = ContentManager::Load<PxTriangleMesh>(L"Meshes/Zelda/SmallIsland.ovpt");
	auto pRigidBody = pLevel->AddComponent(new RigidBodyComponent{ true });
	pRigidBody->AddCollider(PxTriangleMeshGeometry{ pTriangleMesh, physx::PxMeshScale{ scale } }, *pDefaultMaterial);

	pRigidBody->SetCollisionGroup(CollisionGroup::Group0 | CollisionGroup::Group1);

	AddLevelObject(pModelComponent, 0, L"Woods");
	AddLevelObject(pModelComponent, 1, L"Roofs");
	AddLevelObject(pModelComponent, 2, L"Ballustrade");
	AddLevelObject(pModelComponent, 3, L"Bridge");
	AddLevelObject(pModelComponent, 4, L"RockWithGrass");
	AddLevelObject(pModelComponent, 5, L"BigRocks");
	AddLevelObject(pModelComponent, 6, L"Grass");
	AddLevelObject(pModelComponent, 7, L"RandomRocks");

	pLevel->GetTransform()->Scale(scale);
	AddChild(pLevel);

	AddTree({ -9.2f,1.1f,-22.5f }, {}, .01f, pDefaultMaterial);
	AddTree({ -30.8f,-.2f,-4.f }, {0,65,0}, .01f, pDefaultMaterial);
	AddTree({ -33.1f,3.8f,-4.7f }, {0,135,0}, .01f, pDefaultMaterial);
	AddTree({ -71.5f,20.f,-23.3f }, {0,190,0}, .01f, pDefaultMaterial);
	AddTree({ 62.f,3.6f,-17.5f }, {0,-38,0}, .01f, pDefaultMaterial);
	AddTree({ -3.8f,-0.7f, -4.f }, {0,273,0}, .01f, pDefaultMaterial);

	m_pObject = AddBigExplodableRock({ -15.9f,2.6f,-26.4f }, {}, .01f, pDefaultMaterial);


	return pLevel;
}

GameObject* Level1::AddTree(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial)
{
	Tree* pTree = AddChild(new Tree{ pDefaultMaterial });
	pTree->GetTransform()->Translate(position);
	pTree->GetTransform()->Rotate(rotation);
	pTree->GetTransform()->Scale(scale);
	return pTree;
}

void Level1::AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename)
{
#ifdef Deferred
	BasicMaterial_Deferred_Shadow* pMat = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMat->SetDiffuseMap(L"Textures/Zelda/" + filename + L".png");
#else
	DiffuseMaterial_Shadow* pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMat->SetDiffuseTexture(L"Textures/Zelda/" + filename + L".png");
#endif
	pModelComponent->SetMaterial(pMat, id);
}

void Level1::ResetScene()
{
}

void Level1::PostDraw()
{
	//Draw ShadowMap (Debug Visualization)
	if (m_DrawShadowMap) {

		ShadowMapRenderer::Get()->Debug_DrawDepthSRV({ m_SceneContext.windowWidth - 10.f, 10.f }, { m_ShadowMapScale, m_ShadowMapScale }, { 1.f,0.f });
	}
}

GameObject* Level1::AddSmallExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial)
{
	auto pRock = AddChild(new Rock(L"WindWaker_Rock_Small", pDefaultMaterial));
	pRock->GetTransform()->Translate(position);
	pRock->GetTransform()->Rotate(rotation);
	pRock->GetTransform()->Scale(scale);
	return pRock;
}

GameObject* Level1::AddMediumExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial)
{
	auto pRock = AddChild(new Rock(L"WindWaker_Rock_Medium", pDefaultMaterial));
	pRock->GetTransform()->Translate(position);
	pRock->GetTransform()->Rotate(rotation);
	pRock->GetTransform()->Scale(scale);
	return pRock;
}

GameObject* Level1::AddBigExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale, PxMaterial* pDefaultMaterial)
{
	auto pRock = AddChild(new Rock(L"WindWaker_Rock_Big", pDefaultMaterial));
	pRock->GetTransform()->Translate(position);
	pRock->GetTransform()->Rotate(rotation);
	pRock->GetTransform()->Scale(scale);
	return pRock;
}

GameObject* Level1::AddGem(const XMFLOAT3& position, PxMaterial* pDefaultMaterial)
{
	Gem* pGem = AddChild(new Gem{ pDefaultMaterial });
	pGem->GetTransform()->Translate(position);
	pGem->GetTransform()->Rotate(0,static_cast<float>(rand() % 360), 0);

	return pGem;
}

GameObject* Level1::AddSea()
{
	m_pSea = AddChild(new GameObject());
	ModelComponent* pModelComponent = m_pSea->AddComponent(new ModelComponent(L"Meshes/Zelda/Sea.ovm"));
	m_pSea->GetTransform()->Translate(0, -.5f, 0);
	m_pSea->GetTransform()->Rotate(90, 0, 0);
	m_pSea->GetTransform()->Scale(1000, 1000, 1);
	m_pSeaMaterial = MaterialManager::Get()->CreateMaterial<SeaMaterial>();
	m_pSeaMaterial->SetWaterColor(DirectX::XMFLOAT4{ 0.2006942f, 0.3961588f, 0.7735849f, 1.f });
	m_pSeaMaterial->SetRippleSpeed(2);
	m_pSeaMaterial->SetRippleDensity(359.1f);
	m_pSeaMaterial->SetRippleSlimness(8);
	m_pSeaMaterial->SetRippleColor(DirectX::XMFLOAT4{ 0.5506853f, 0.8630115f, 0.9339623f, 1.f });
	m_pSeaMaterial->SetWaveSpeed(0.01f);
	m_pSeaMaterial->SetWaveScale(1.5f);
	m_pSeaMaterial->SetFoamAmount(0.79f);
	m_pSeaMaterial->SetFoamCutoff(2.7f);
	m_pSeaMaterial->SetFoamScale(150.f);
	m_pSeaMaterial->SetFoamSpeed(0.03f);
	m_pSeaMaterial->SetFoamColor(DirectX::XMFLOAT4{ 1.f,1.f,1.f, 1.f });
	m_pSeaMaterial->SetPerlinNoise(L"Textures/Zelda/PerlinNoise.jpg");
	pModelComponent->SetMaterial(m_pSeaMaterial);

	return m_pSea;
}

GameObject* Level1::AddSkyBox()
{
	auto pSky = AddChild(new GameObject());
	auto pModel = pSky->AddComponent(new ModelComponent(L"Meshes/SkyBox.ovm"));
	auto pMaterial = MaterialManager::Get()->CreateMaterial<SkyBoxMaterial>();
	pMaterial->SetSkyBoxTexture(L"Textures/SkyDawn.dds");
	pModel->SetMaterial(pMaterial);

	return pSky;
}

void Level1::OnGUI()
{
	//m_pSeaMaterial->DrawImGui();

	//auto curPos = m_pObject->GetTransform()->GetWorldPosition();
	//float pos[4]{ curPos.x, curPos.y, curPos.z, curPos.w };
	//ImGui::DragFloat3("Translation", pos, 0.1f, -300, 300);
	//m_pObject->GetTransform()->Translate(pos[0], pos[1], pos[2]);

	m_pCharacter->DrawImGui();

	//auto curPos = m_pCharacter->GetLightOffset();
	//float pos[4]{ curPos.x, curPos.y, curPos.z, curPos.w };
	//ImGui::DragFloat4("Translation", pos, 0.1f, -1000, 1000);
	//m_pCharacter->SetLightOffset(XMFLOAT4{ pos[0], pos[1], pos[2], pos[3] });
	//
	//curPos = m_SceneContext.pLights->GetDirectionalLight().direction;
	//float dir[4]{ curPos.x, curPos.y, curPos.z, curPos.w };
	//ImGui::DragFloat4("Direction", dir, 0.1f, -1000, 1000);
	//m_SceneContext.pLights->GetDirectionalLight().direction = XMFLOAT4{ dir[0], dir[1], dir[2], dir[3]};
	//
	//ImGui::Checkbox("Draw ShadowMap", &m_DrawShadowMap);
	//ImGui::SliderFloat("ShadowMap Scale", &m_ShadowMapScale, 0.f, 1.f);
	//
	//float value = ShadowMapRenderer::Get()->GetFar();
	//ImGui::DragFloat("Far", &value, 0.1f, -1000, 1000);
	//ShadowMapRenderer::Get()->SetFar(value);
	//
	//value = ShadowMapRenderer::Get()->GetNear();
	//ImGui::DragFloat("Near", &value, 0.1f, -1000, 1000);
	//ShadowMapRenderer::Get()->SetNear(value);
	//
	//value = ShadowMapRenderer::Get()->GetSize();
	//ImGui::DragFloat("Size", &value, 0.1f, -1000, 1000);
	//ShadowMapRenderer::Get()->SetSize(value);
}
