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
#include "Prefabs/RedGem.h"
#include "Prefabs/UI/HUD.h"
#include "Prefabs/BombSpawner.h"
#include "Prefabs/Bridge.h"
#include "Materials/Post/PostCameraShake.h"
#include "Materials/Post/PostBlur.h"

#include "Prefabs/UI/Button.h"

//Audio
#include "Managers/SoundManager.h"

Level1::Level1()
	: GameScene{L"Level1"}
	, m_pCharacter{ nullptr }
	, m_pSea{ nullptr }
	, m_pSeaMaterial{ nullptr }
	, m_pObject{ nullptr }
{
	m_pGems = std::vector<Gem*>();
	m_pRedGems = std::vector<RedGem*>();
}

void Level1::Initialize()
{
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawPhysXDebug = false;

	m_SceneContext.useDeferredRendering = true;

	m_SceneContext.pLights->SetDirectionalLight({ 0,0,0 }, { -160, -66, 20 });

	auto physX = PhysXManager::Get()->GetPhysics();
	m_pDefaultMaterial = physX->createMaterial(1.f, 1.f, 0.f);

	//Level
	AddLevel();
	AddPlayer();
	
	AddSea();
	AddSkyBox();
	
	AddChild(new HUD{});
	
	m_pBridgeCamera = AddChild(new FixedCamera{});
	m_pBridgeCamera->GetTransform()->Translate(0, 47.5, 0);
	m_pBridgeCamera->GetTransform()->Rotate(0, 160, 0);

	//Audio
	/*
	auto fmodResult = SoundManager::Get()->GetSystem()->createChannelGroup("Sound Effects", &m_pSoundEffectGroup);
	SoundManager::Get()->ErrorCheck(fmodResult);
	
	m_MusicVolume = 0.3f;
	
	SoundManager::Get()->GetSystem()->createStream("Resources/Audio/ReadyToFight.mp3", FMOD_DEFAULT, nullptr, &m_pBackgroundSoundFx);
	SoundManager::Get()->ErrorCheck(fmodResult);
	
	SoundManager::Get()->GetSystem()->playSound(m_pBackgroundSoundFx, m_pSoundEffectGroup, false, nullptr);
	m_pSoundEffectGroup->setVolume(m_MusicVolume);
	*/

	//UI
	AddPauseMenu();
	SetPauseMenu(false);

	//AddChild(new GameObject{});
}

void Level1::Update()
{
	if (m_SceneContext.pInput->IsActionTriggered(Settings))
	{
		if (m_SceneContext.pGameTime->IsRunning())
		{
			SetPauseMenu(true);
		}
		else
		{
			SetPauseMenu(false);
		}
		return;
	}

	if (m_SceneContext.pGameTime->IsRunning())
	{
		UpdateScene();
	}
	else
	{
		UpdatePause();
	}
}

GameObject* Level1::AddPlayer()
{
	CharacterDesc characterDesc{ m_pDefaultMaterial, .5f,2.f };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;
	characterDesc.actionId_Throw = ThrowBomb;

	XMFLOAT3 spawnPoint = { 0.f, 5.f, 0.f };
	m_pCharacter = AddChild(new Character(characterDesc, {0,3,15}, spawnPoint));
	m_pCharacter->GetTransform()->Translate(spawnPoint);

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

	inputAction = InputAction(ThrowBomb, InputState::pressed, 'E', -1, XINPUT_GAMEPAD_B);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(Settings, InputState::pressed, VK_ESCAPE, -1, XINPUT_GAMEPAD_START);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(SettingsMoveUp, InputState::pressed, -1, -1, XINPUT_GAMEPAD_DPAD_UP);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(SettingsMoveDown, InputState::pressed, -1, -1, XINPUT_GAMEPAD_DPAD_DOWN);
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(SettingsPress, InputState::pressed, -1, -1, XINPUT_GAMEPAD_A);
	m_SceneContext.pInput->AddInputAction(inputAction);

	return m_pCharacter;
}

GameObject* Level1::AddLevel()
{
	float scale = 2;

	//Island
	GameObject* pLevel = new GameObject();
	ModelComponent* pModelComponent = pLevel->AddComponent(new ModelComponent(L"Meshes/Zelda/SmallIsland.ovm"));

	const auto pTriangleMesh = ContentManager::Load<PxTriangleMesh>(L"Meshes/Zelda/SmallIsland.ovpt");
	auto pRigidBody = pLevel->AddComponent(new RigidBodyComponent{ true });
	pRigidBody->AddCollider(PxTriangleMeshGeometry{ pTriangleMesh, physx::PxMeshScale{ scale } }, *m_pDefaultMaterial);

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

	//Trees
	AddTree({ -9.2f,1.1f,-22.5f }, {}, .01f);
	AddTree({ -30.8f,-.2f,-4.f }, {0,65,0}, .01f);
	AddTree({ -33.1f,3.8f,-4.7f }, {0,135,0}, .01f);
	AddTree({ -71.5f,20.f,-23.3f }, {0,190,0}, .01f);
	AddTree({ 62.f,3.6f,-17.5f }, {0,-38,0}, .01f);
	AddTree({ -3.8f,-0.7f, -4.f }, {0,273,0}, .01f);

	AddBombSpawner({ -10.8f, 2.5f, -4.7f });
	AddBombSpawner({ 42.5f, 1.8f, -34.5f });

	return pLevel;
}

GameObject* Level1::AddTree(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale)
{
	Tree* pTree = AddChild(new Tree{ m_pDefaultMaterial });
	pTree->GetTransform()->Translate(position);
	pTree->GetTransform()->Rotate(rotation);
	pTree->GetTransform()->Scale(scale);
	return pTree;
}

void Level1::AddLevelObject(ModelComponent* pModelComponent, UINT8 id, const std::wstring& filename)
{
	BasicMaterial_Deferred_Shadow* pMat = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow>();
	pMat->SetDiffuseTexture(L"Textures/Zelda/" + filename + L".png");
	pModelComponent->SetMaterial(pMat, id);
}

void Level1::OnSceneActivated()
{
	ResetScene();
}

void Level1::ResetScene()
{
	SetPauseMenu(false);

	HUD::Get()->SetAmountOfHearts(3);
	HUD::Get()->SetAmountRupees(0);

	m_pCharacter->GetTransform()->Translate(0.f,5.f,0.f);
	RemovePostProcessingEffect(m_pCameraShake);

	for (int i = 0; i < m_pGems.size(); i++)
	{
		if (m_pGems[i] != nullptr)
		{
			RemoveChild(m_pGems[i], true);
			m_pGems[i] = nullptr;
		}
	}
	m_pGems.clear();

	AddGem({ -10.f, -10.f, -10.f });
	AddGem({ -9.3f, 3.6f, 4.3f });
	AddGem({ -20.f, 3.6f, 6.4f });
	AddGem({ -29.1f, 3.6f, 5.5f });
	AddGem({ -37.9f, 6.3f, -11.f });
	AddGem({ -49.f, 8.5f, -7.1f });
	AddGem({ -56.7f, 8.5f, -1.7f });
	AddGem({ -54.f, 8.5f, -4.4f });
	AddGem({ -35.5f, 9.3f, -26.6f });

	for (int i = 0; i < m_pRedGems.size(); i++)
	{
		if (m_pRedGems[i] != nullptr)
		{
			RemoveChild(m_pRedGems[i], true);
			m_pRedGems[i] = nullptr;
		}
	}

	m_pObject = AddRedGem({ 10,5,10 });
	AddRedGem({ -13.3f, 5.f,-31.9f });
	AddRedGem({ 44.8f, 5.2f, -39.4f });

	for (int i = 0; i < m_pRocks.size(); i++)
	{
		if (m_pRocks[i] != nullptr)
		{
			RemoveChild(m_pRocks[i], true);
			m_pRocks[i] = nullptr;
		}
	}
	m_pRocks.clear();

	AddSmallExplodableRock({ 43.f, .75f, -22.f }, { }, .01f);
	AddSmallExplodableRock({ -15.9f, .95f, 10.2f }, { }, .01f);
	AddSmallExplodableRock({ 11.3f, .05f, -2.6f }, { }, .01f);
	AddSmallExplodableRock({ -6.f, 1.25f, -26.9f }, { }, .01f);

	AddMediumExplodableRock({ 19.8f, -.4f, -9.7f }, { }, .01f);
	AddMediumExplodableRock({ 9.8f, -.4f, -9.7f }, { }, .01f);
	AddMediumExplodableRock({ -14.8f, 1.6f, -31.7f }, { }, .04f);

	AddBigExplodableRock({ -15.9f,2.6f,-26.4f }, {}, .01f);
	AddBigExplodableRock({ 20,3,7 }, { }, .01f);
	AddBigExplodableRock({ 44.8f, 5.2f, -39.4f }, { }, .01f);

	if (m_pBridge != nullptr) RemoveChild(m_pBridge, true);
}

void Level1::PostDraw()
{
	//Draw ShadowMap (Debug Visualization)
	if (m_DrawShadowMap) {

		ShadowMapRenderer::Get()->Debug_DrawDepthSRV({ m_SceneContext.windowWidth - 10.f, 10.f }, { m_ShadowMapScale, m_ShadowMapScale }, { 1.f,0.f });
	}
}

void Level1::AddPauseMenu()
{
	auto pButton = AddChild(new Button{ L"Textures/UI/StartButtonNormal.png",L"Textures/UI/StartButtonActivated.png",[&]()
	{
		SetPauseMenu(false);
	} });
	pButton->GetTransform()->Translate(500, 150, 0);
	m_pButtons.emplace_back(pButton);

	pButton = AddChild(new Button{ L"Textures/UI/MainMenuButtonNormal.png",L"Textures/UI/MainMenuButtonActivated.png",[&]()
	{
		SceneManager::Get()->SetActiveGameScene(L"MainMenu");
	} });
	pButton->GetTransform()->Translate(500, 300, 0);
	m_pButtons.emplace_back(pButton);

	pButton = AddChild(new Button{ L"Textures/UI/RestartButtonNormal.png",L"Textures/UI/RestartButtonActivated.png",[&]()
	{
		ResetScene();
	} });
	pButton->GetTransform()->Translate(500, 450, 0);
	m_pButtons.emplace_back(pButton);

	pButton = AddChild(new Button{ L"Textures/UI/ExitButtonNormal.png",L"Textures/UI/ExitButtonActivated.png",[&]()
		{
			OverlordGame::Stop();
		} });
	pButton->GetTransform()->Translate(500, 600, 0);
	m_pButtons.emplace_back(pButton);
}

void Level1::SetPauseMenu(bool isVisible)
{
	if (isVisible)
	{
		for (size_t i = 0; i < m_pButtons.size(); i++)
		{
			m_pButtons[i]->Enable();
		}

		m_SceneContext.pGameTime->Stop();
	}
	else
	{
		m_SceneContext.pGameTime->Start();

		for (size_t i = 0; i < m_pButtons.size(); i++)
		{
			m_pButtons[i]->Disable();
		}
	}
}

GameObject* Level1::AddSmallExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale)
{
	auto pRock = AddChild(new Rock(L"WindWaker_Rock_Small", m_pDefaultMaterial, scale));
	pRock->GetTransform()->Translate(position);
	pRock->GetTransform()->Rotate(rotation);
	pRock->GetTransform()->Scale(scale);

	m_pRocks.emplace_back(pRock);

	return pRock;
}

GameObject* Level1::AddMediumExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale)
{
	auto pRock = AddChild(new Rock(L"WindWaker_Rock_Medium", m_pDefaultMaterial, scale));
	pRock->GetTransform()->Translate(position);
	pRock->GetTransform()->Rotate(rotation);
	pRock->GetTransform()->Scale(scale);

	m_pRocks.emplace_back(pRock);

	return pRock;
}

GameObject* Level1::AddBigExplodableRock(const XMFLOAT3& position, const XMFLOAT3& rotation, float scale)
{
	auto pRock = AddChild(new Rock(L"WindWaker_Rock_Big", m_pDefaultMaterial, scale));
	pRock->GetTransform()->Translate(position);
	pRock->GetTransform()->Rotate(rotation);
	pRock->GetTransform()->Scale(scale);

	m_pRocks.emplace_back(pRock);

	return pRock;
}

GameObject* Level1::AddGem(const XMFLOAT3& position)
{
	Gem* pGem = AddChild(new Gem{ m_pDefaultMaterial });
	pGem->GetTransform()->Translate(position);

	m_pGems.emplace_back(pGem);

	return pGem;
}

GameObject* Level1::AddRedGem(const XMFLOAT3& position)
{
	RedGem* pRedGem = AddChild(new RedGem{ m_pDefaultMaterial });
	pRedGem->GetTransform()->Translate(position);

	m_pRedGems.emplace_back(pRedGem);

	return pRedGem;
}

GameObject* Level1::AddBombSpawner(const XMFLOAT3& position)
{
	BombSpawner* pBombSpawner = AddChild(new BombSpawner{ m_pDefaultMaterial });
	pBombSpawner->GetTransform()->Translate(position);

	return pBombSpawner;
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

	RigidBodyComponent* pRigidBody = m_pSea->AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry{ 500.f,500.f,.5f }, *m_pDefaultMaterial);
	pRigidBody->SetCollisionGroup(CollisionGroup::Group0 | CollisionGroup::Group2);
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

	auto curPos = m_pObject->GetTransform()->GetWorldPosition();
	float pos[3]{ curPos.x, curPos.y, curPos.z};
	ImGui::DragFloat3("Translation", pos, 0.1f, -300, 300);
	m_pObject->GetTransform()->Translate(pos[0], pos[1], pos[2]);
	
	//m_pCharacter->DrawImGui();

	//auto curPos = m_pBridgeCamera->GetTransform()->GetWorldPosition();
	//float pos[3]{ curPos.x, curPos.y, curPos.z };
	//ImGui::DragFloat3("Translation", pos, 0.1f, -300, 300);
	//m_pBridgeCamera->GetTransform()->Translate(pos[0], pos[1], pos[2]);
	//
	//auto curRot = m_pBridgeCamera->GetTransform()->GetWorldRotation();
	//float rot[3]{ curRot.x, curRot.y, curRot.z };
	//ImGui::DragFloat3("Rotation", rot, 0.1f, -300, 300);
	//m_pBridgeCamera->GetTransform()->Rotate(rot[0], rot[1], rot[2]);

	//XMFLOAT4 curPos = m_SceneContext.pLights->GetDirectionalLight().position;
	//float pos[4]{ curPos.x, curPos.y, curPos.z, curPos.w };
	//ImGui::DragFloat4("Translation", pos, 0.1f, -1000, 1000);
	//m_SceneContext.pLights->GetDirectionalLight().position = XMFLOAT4{ pos[0], pos[1], pos[2], pos[3] };
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

void Level1::UpdatePause()
{
	if (m_SceneContext.pInput->IsActionTriggered(SettingsMoveUp))
	{
		if (m_SelectedButtonIndex == -1)
		{
			m_SelectedButtonIndex = 0;
		}
		else
		{
			m_SelectedButtonIndex--;
			if (m_SelectedButtonIndex < 0) m_SelectedButtonIndex = static_cast<int>(m_pButtons.size()) - 1;
		}

		for (size_t i = 0; i < m_pButtons.size(); i++)
		{
			m_pButtons[i]->SetSelect(m_SelectedButtonIndex == i);
		}
	}

	if (m_SceneContext.pInput->IsActionTriggered(SettingsMoveDown))
	{
		if (m_SelectedButtonIndex == -1)
		{
			m_SelectedButtonIndex = 0;
		}
		else
		{
			m_SelectedButtonIndex++;
			if (m_SelectedButtonIndex >= m_pButtons.size()) m_SelectedButtonIndex = 0;
		}

		for (size_t i = 0; i < m_pButtons.size(); i++)
		{
			m_pButtons[i]->SetSelect(m_SelectedButtonIndex == i);
		}
	}

	if (m_SceneContext.pInput->IsActionTriggered(SettingsPress))
	{
		for (Button* button : m_pButtons)
		{
			button->Press(m_SceneContext);
		}
	}
	if (m_SceneContext.pInput->IsMouseButton(InputState::pressed, VK_LBUTTON))
	{
		for (Button* button : m_pButtons)
		{
			if (button->IsHovering(m_SceneContext))
			{
				button->Press(m_SceneContext);
			}
		}
	}
	POINT mousePos = InputManager::GetMousePosition();
	POINT prevMousePos = InputManager::GetMousePosition(true);
	if (mousePos.x != prevMousePos.x || mousePos.y != prevMousePos.y)
	{
		m_SelectedButtonIndex = -1;
		for (Button* button : m_pButtons)
		{
			button->IsHovering(m_SceneContext);
		}
	}
}

void Level1::UpdateScene()
{
	for (int i = 0; i < m_pGems.size(); i++)
	{
		if (m_pGems[i] != nullptr && m_pGems[i]->GetMarkForDelete())
		{
			RemoveChild(m_pGems[i], true);
			m_pGems[i] = nullptr;
		}
	}

	for (int i = 0; i < m_pRocks.size(); i++)
	{
		if (m_pRocks[i] != nullptr && m_pRocks[i]->GetMarkForDelete())
		{
			RemoveChild(m_pRocks[i], true);
			m_pRocks[i] = nullptr;
		}
	}

	bool areAllCollected = true;
	for (int i = 0; i < m_pRedGems.size(); i++)
	{
		if (m_pRedGems[i] == nullptr) continue;
		else if (m_pRedGems[i]->GetMarkForDelete())
		{
			RemoveChild(m_pRedGems[i], true);
			m_pRedGems[i] = nullptr;
		}
		else
		{
			areAllCollected = false;
		}
	}

	if (!areAllCollected) return;

	if (!m_HasAlreadyDoneOtherCamera)
	{
		m_pBridgeCamera->GetComponent<CameraComponent>()->SetActive();
		m_StartBridgeCameraTime = m_SceneContext.pGameTime->GetTotal();
		m_HasAlreadyDoneOtherCamera = true;
		
		return;
	}

	if (m_pBridge == nullptr && m_StartBridgeCameraTime + m_TimeBeforeBridgeSpawnsIn < m_SceneContext.pGameTime->GetTotal())
	{
		//Spawn Bridge
		m_pBridge = AddChild(new Bridge{ m_pDefaultMaterial });
		m_pBridge->GetTransform()->Translate(21.9f, 33.8f, -58.2f);
	}
	if (m_StartBridgeCameraTime + m_CameraSwitchDuration < m_SceneContext.pGameTime->GetTotal())
	{
		m_pCharacter->GetCamera()->SetActive();
	}
}
