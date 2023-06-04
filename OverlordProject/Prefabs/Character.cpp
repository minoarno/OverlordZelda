#include "stdafx.h"
#include "Character.h"
#include "Scenegraph/GameObject.h"
#include "Prefabs/Bomb.h"

#include "Materials/Deferred/BasicMaterial_Deferred_Shadow_Skinned.h"
#include "UI/HUD.h"

Character::Character(const CharacterDesc& characterDesc, const XMFLOAT3& cameraOffset, const XMFLOAT3& respawnPosition)
	: m_CharacterDesc{ characterDesc }
	, m_MoveAcceleration(characterDesc.maxMoveSpeed / characterDesc.moveAccelerationTime)
	, m_FallAcceleration(characterDesc.maxFallSpeed / characterDesc.fallAccelerationTime)
	, m_pVisuals{ nullptr }
	, m_CameraOffset{ cameraOffset }
	, m_RespawnPosition{ respawnPosition }
{}

bool Character::PickUpBomb(Bomb* pBomb)
{
	if (m_pBomb == nullptr)
	{
		m_pBomb = pBomb;
		return true;
	}
	return false;
}

void Character::Die()
{
	HUD::Get()->DecreaseHearts();

	SetCharacterAnimation(CharacterAnimation::Dying);
}

void Character::Initialize(const SceneContext& sceneContext)
{
	//Controller
	m_pControllerComponent = AddComponent(new ControllerComponent(m_CharacterDesc.controller));
	SetTag(L"Link");

	m_pGameTime = sceneContext.pGameTime;

	//Camera
	const auto pCamera = AddChild(new FixedCamera());
	m_pCameraComponent = pCamera->GetComponent<CameraComponent>();
	m_pCameraComponent->SetActive(true); //Uncomment to make this camera the active camera

	pCamera->GetTransform()->Translate(0.f, m_CharacterDesc.controller.height * 1.5f, 15.f);
	pCamera->GetTransform()->Rotate(0, 180, 0);
	
	m_pVisuals = AddChild(new GameObject{});
	auto pModel = m_pVisuals->AddComponent(new ModelComponent(L"Meshes/Zelda/Link.ovm"));

	auto pSkinnedMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow_Skinned>();
	pSkinnedMaterial->SetDiffuseMap(L"Textures/Zelda/body.png");
	pModel->SetMaterial(pSkinnedMaterial, 0);
	pSkinnedMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow_Skinned>();
	pSkinnedMaterial->SetDiffuseMap(L"Textures/Zelda/mouth1.png");
	pModel->SetMaterial(pSkinnedMaterial, 1);
	pSkinnedMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow_Skinned>();
	pSkinnedMaterial->SetDiffuseMap(L"Textures/Zelda/pupil.png");
	pModel->SetMaterial(pSkinnedMaterial, 2);
	pSkinnedMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow_Skinned>();
	pSkinnedMaterial->SetDiffuseMap(L"Textures/Zelda/eye1.png");
	pModel->SetMaterial(pSkinnedMaterial, 3);
	pSkinnedMaterial = MaterialManager::Get()->CreateMaterial<BasicMaterial_Deferred_Shadow_Skinned>();
	pSkinnedMaterial->SetDiffuseMap(L"Textures/Zelda/eyebrow1.png");
	pModel->SetMaterial(pSkinnedMaterial, 4);

	m_pVisuals->GetTransform()->Scale(0.0002f);
	m_pVisuals->GetTransform()->Rotate(0, 90, 0);
	m_pVisuals->GetTransform()->Translate(0, -1.4f, 0);

	m_pAnimator = pModel->GetAnimator();
	m_CharacterState = CharacterAnimation::Idle;
	m_pAnimator->SetAnimation(m_CharacterState);
	m_pAnimator->SetAnimationSpeed(m_AnimationSpeed);
	m_pAnimator->Play(); 
}

void Character::Update(const SceneContext& sceneContext)
{
	auto pos = GetTransform()->GetPosition();
	sceneContext.pLights->GetDirectionalLight().position = XMFLOAT4{ pos.x + m_LightOffset.x, pos.y + m_LightOffset.y, pos.z + m_LightOffset.z, m_LightOffset.w };

	if (!sceneContext.pGameTime->IsRunning())return;

	if (m_CharacterState == CharacterAnimation::Dying)
	{
		if (m_LastAnimationTime + m_DeathAnimationDuration > sceneContext.pGameTime->GetTotal()) return;

		if (HUD::Get()->GetAmountOfHearts() < 1)
		{
			SceneManager::Get()->SetActiveGameScene(L"LoseScene");
			return;
		}
		GetTransform()->Translate(m_RespawnPosition);
		SetCharacterAnimation(CharacterAnimation::Idle);
	}

	if (m_pCameraComponent->IsActive())
	{
		constexpr float epsilon{ 0.01f }; //Constant that can be used to compare if a float is near zero

		//***************
		//HANDLE INPUT

		//## Input Gathering (move)
		XMFLOAT2 move{0.f,0.f}; //Uncomment

		//move.y should contain a 1 (Forward) or -1 (Backward) based on the active input (check corresponding actionId in m_CharacterDesc)
		//Optional: if move.y is near zero (abs(move.y) < epsilon), you could use the ThumbStickPosition.y for movement

		if (sceneContext.pInput->IsActionTriggered(m_CharacterDesc.actionId_MoveForward)) //forward
		{
			move.y = 1;
		}
		else if (sceneContext.pInput->IsActionTriggered(m_CharacterDesc.actionId_MoveBackward)) //backward
		{
			move.y = -1;
		}
		if (abs(move.y) < epsilon)
		{
			move.y = sceneContext.pInput->GetThumbstickPosition(true).y;
		}

		//move.x should contain a 1 (Right) or -1 (Left) based on the active input (check corresponding actionId in m_CharacterDesc)
		//Optional: if move.x is near zero (abs(move.x) < epsilon), you could use the Left ThumbStickPosition.x for movement
		
		if (sceneContext.pInput->IsActionTriggered(m_CharacterDesc.actionId_MoveRight)) //right
		{
			move.x = 1;
		}
		else if (sceneContext.pInput->IsActionTriggered(m_CharacterDesc.actionId_MoveLeft)) //left
		{
			move.x = -1;
		}
		if (abs(move.x) < epsilon)
		{
			move.x = sceneContext.pInput->GetThumbstickPosition().x;
		}

		//## Input Gathering (look)
		XMFLOAT2 look{ 0.f, 0.f }; //Uncomment
		//Only if the Left Mouse Button is Down >
		// Store the MouseMovement in the local 'look' variable (cast is required)
		//Optional: in case look.x AND look.y are near zero, you could use the Right ThumbStickPosition for look
		auto mouseMovement = sceneContext.pInput->GetMouseMovement();
		if (sceneContext.pInput->IsMouseButton(InputState::down, VK_LBUTTON))
		{
			look = DirectX::XMFLOAT2{ (float)mouseMovement.x, -(float)mouseMovement.y };
		}
		if (abs(look.x) < epsilon && abs(look.y) < epsilon)
		{
			look = sceneContext.pInput->GetThumbstickPosition(false);
		}

		//************************
		//GATHERING TRANSFORM INFO

		//Retrieve the TransformComponent
		//Retrieve the forward & right vector (as XMVECTOR) from the TransformComponent
		XMVECTOR forward = DirectX::XMLoadFloat3(&m_pCameraComponent->GetGameObject()->GetTransform()->GetForward()) * move.y;
		XMVECTOR right = DirectX::XMLoadFloat3(&m_pCameraComponent->GetGameObject()->GetTransform()->GetRight()) * move.x;

		//***************
		//CAMERA ROTATION

		//Adjust the TotalYaw (m_TotalYaw) & TotalPitch (m_TotalPitch) based on the local 'look' variable
		//Make sure this calculated on a framerate independent way and uses CharacterDesc::rotationSpeed.
		//Rotate this character based on the TotalPitch (X) and TotalYaw (Y)
		float elapsedTime = sceneContext.pGameTime->GetElapsed();
		m_TotalYaw += look.x * m_CharacterDesc.rotationSpeed * elapsedTime;
		m_TotalPitch += look.y * m_CharacterDesc.rotationSpeed * elapsedTime;


		m_TotalPitch = std::clamp(m_TotalPitch, m_MinPitch, m_MaxPitch);
		GetTransform()->Rotate(m_TotalPitch, m_TotalYaw, 0);
		
		//if (look.x < epsilon && look.y < epsilon)
		//{
			AdjustCamera();
		//}

		m_pVisuals->GetTransform()->Rotate(-m_TotalPitch, 0, 0);

		//********
		//MOVEMENT

		//## Horizontal Velocity (Forward/Backward/Right/Left)
		//Calculate the current move acceleration for this frame (m_MoveAcceleration * ElapsedTime)
		//If the character is moving (= input is pressed)
			//Calculate & Store the current direction (m_CurrentDirection) >> based on the forward/right vectors and the pressed input
			//Increase the current MoveSpeed with the current Acceleration (m_MoveSpeed)
			//Make sure the current MoveSpeed stays below the maximum MoveSpeed (CharacterDesc::maxMoveSpeed)
		//Else (character is not moving, or stopped moving)
			//Decrease the current MoveSpeed with the current Acceleration (m_MoveSpeed)
			//Make sure the current MoveSpeed doesn't get smaller than zero
		m_MoveAcceleration += m_MoveAcceleration * elapsedTime;
		if (abs(move.x) > epsilon || abs(move.y) > epsilon)
		{
			XMStoreFloat3(&m_CurrentDirection, (forward + right));

			m_MoveSpeed += m_MoveAcceleration * elapsedTime;
			if (m_MoveSpeed > m_CharacterDesc.maxMoveSpeed)
			{
				m_MoveSpeed = m_CharacterDesc.maxMoveSpeed;
			}
		}
		else
		{
			m_MoveSpeed -= m_MoveAcceleration * elapsedTime;
			if (m_MoveSpeed < epsilon)
			{
				m_MoveSpeed = 0;
			}
		}

		//Now we can calculate the Horizontal Velocity which should be stored in m_TotalVelocity.xz
		//Calculate the horizontal velocity (m_CurrentDirection * MoveSpeed)
		//Set the x/z component of m_TotalVelocity (horizontal_velocity x/z)
		//It's important that you don't overwrite the y component of m_TotalVelocity (contains the vertical velocity)
		m_TotalVelocity.x = m_CurrentDirection.x * m_MoveSpeed;
		m_TotalVelocity.z = m_CurrentDirection.z * m_MoveSpeed;

		//## Vertical Movement (Jump/Fall)
		//If the Controller Component is NOT grounded (= freefall)
			//Decrease the y component of m_TotalVelocity with a fraction (ElapsedTime) of the Fall Acceleration (m_FallAcceleration)
			//Make sure that the minimum speed stays above -CharacterDesc::maxFallSpeed (negative!)
		//Else If the jump action is triggered
			//Set m_TotalVelocity.y equal to CharacterDesc::JumpSpeed
		//Else (=Character is grounded, no input pressed)
			//m_TotalVelocity.y is zero
		if (!m_pControllerComponent->GetCollisionFlags().isSet(PxControllerCollisionFlag::eCOLLISION_DOWN))
		{
			m_TotalVelocity.y -= m_FallAcceleration * elapsedTime;
			if (m_TotalVelocity.y < -m_CharacterDesc.maxFallSpeed)
			{
				m_TotalVelocity.y = -m_CharacterDesc.maxFallSpeed;
			}
		}
		else if (sceneContext.pInput->IsActionTriggered(m_CharacterDesc.actionId_Jump))
		{
			m_TotalVelocity.y = m_CharacterDesc.JumpSpeed;
		}
		else
		{
			m_TotalVelocity.y = 0;
		}

		//************
		//DISPLACEMENT

		//The displacement required to move the Character Controller (ControllerComponent::Move) can be calculated using our TotalVelocity (m/s)
		//Calculate the displacement (m) for the current frame and move the ControllerComponent

		DirectX::XMFLOAT3 displacementFloat3;
		DirectX::XMStoreFloat3(&displacementFloat3, DirectX::XMLoadFloat3(&m_TotalVelocity) * sceneContext.pGameTime->GetElapsed());
		m_pControllerComponent->Move(displacementFloat3, epsilon);

		if (m_pBomb != nullptr)
		{
			m_pBomb->GetTransform()->Translate(pos.x, pos.y + m_CharacterDesc.controller.height * .5f, pos.z);
		}

		//The above is a simple implementation of Movement Dynamics, adjust the code to further improve the movement logic and behaviour.
		//Also, it can be usefull to use a seperate RayCast to check if the character is grounded (more responsive)


		float distance = 1.65f;
		if (m_CharacterState != CharacterAnimation::Throw)
		{
			if (abs(m_TotalVelocity.x) < epsilon && abs(m_TotalVelocity.y) < 1 && abs(m_TotalVelocity.z) < epsilon)
			{
				if (DoesRaycastHitCollisionGroup(CollisionGroup::Group2, distance))
				{
					SetCharacterAnimation(CharacterAnimation::SwimmingIdle);
				}
				else
				{
					SetCharacterAnimation(CharacterAnimation::Idle);
				}
			}
			else if (m_TotalVelocity.y > 1)
			{
				SetCharacterAnimation(CharacterAnimation::Jump);
			}
			else if (m_TotalVelocity.y < -1)
			{
				if (!DoesRaycastHitCollisionGroup(CollisionGroup::Group1, 2))
				{
					SetCharacterAnimation(CharacterAnimation::Falling);
				}
			}
			else
			{
				if (DoesRaycastHitCollisionGroup(CollisionGroup::Group2,distance))
				{
					SetCharacterAnimation(CharacterAnimation::Swimming);
				}
				else
				{
					SetCharacterAnimation(CharacterAnimation::Running);
				}
			}
		}
		else
		{
			if (m_LastAnimationTime + m_AnimationDuration > sceneContext.pGameTime->GetTotal())
			{
				SetCharacterAnimation(CharacterAnimation::Idle);
			}
		}

		if (sceneContext.pInput->IsActionTriggered(m_CharacterDesc.actionId_Throw))
		{
			if (m_CharacterState != CharacterAnimation::Throw)
			{

				SetCharacterAnimation(CharacterAnimation::Throw);

				m_LastAnimationTime = sceneContext.pGameTime->GetTotal();
				ThrowBomb();
			}
		}
	}
}

void Character::AdjustCamera()
{
	auto player = GetTransform()->GetWorldPosition();
	auto camera = m_pCameraComponent->GetTransform()->GetWorldPosition();
	auto cameraLocalPos = m_pCameraComponent->GetTransform()->GetPosition();

	float distance = PhysxHelper::ToPxVec3(m_CameraOffset).magnitude();

	physx::PxVec3 start = PhysxHelper::ToPxVec3(player);
	physx::PxVec3 end = PhysxHelper::ToPxVec3(camera);
	physx::PxVec3 localOffset = PhysxHelper::ToPxVec3(cameraLocalPos);

	auto direction = (end - start).getNormalized();
	auto localDirection = localOffset.getNormalized();

	physx::PxRaycastBuffer hit{};

	if (direction.magnitude() == 0)
	{
		direction = { 0, 1, 0 };
	}

	physx::PxQueryFilterData filterData{};
	filterData.data.word0 = UINT(CollisionGroup::Group1);

	auto activeScene = SceneManager::Get()->GetActiveScene();
	if (activeScene->GetPhysxProxy()->Raycast(start,
		direction,
		distance,
		hit,
		physx::PxHitFlag::eDEFAULT | physx::PxHitFlag::eMESH_ANY | physx::PxHitFlag::eASSUME_NO_INITIAL_OVERLAP,
		filterData) && hit.hasBlock)
	{
		distance = (hit.block.position - direction * m_CameraNormalOffset - start).magnitude();
	}
	XMFLOAT3 hitPointPos = { localDirection.x * distance, localDirection.y * distance, localDirection.z * distance };
	m_pCameraComponent->GetTransform()->Translate(hitPointPos);
}

void Character::ThrowBomb()
{
	if (m_pBomb == nullptr) return;

	XMFLOAT3 forward{};
	XMStoreFloat3(&forward, XMLoadFloat3(&GetTransform()->GetForward()) * -1);
	forward.y += .1f;
	XMStoreFloat3(&forward, XMVector3Normalize(XMLoadFloat3(&forward)));
	XMStoreFloat3(&forward, XMLoadFloat3(&forward) * 15);

	XMFLOAT3 bulletPos{ GetTransform()->GetPosition() };
	XMStoreFloat3(&bulletPos, XMVectorAdd(XMLoadFloat3(&bulletPos), XMLoadFloat3(&forward)));
	m_pBomb->GetTransform()->Translate(bulletPos);
	m_pBomb->Launch(forward);

	m_pBomb = nullptr;
}

void Character::SetCharacterAnimation(CharacterAnimation newAnimationState)
{
	if (m_CharacterState == newAnimationState) return;

	switch (newAnimationState)
	{
	case CharacterAnimation::Swimming:
	case CharacterAnimation::SwimmingIdle:
		m_pVisuals->GetTransform()->Translate(0, -2.4f, 0);
		break;
	default:
		m_pVisuals->GetTransform()->Translate(0, -1.4f, 0);
		break;
	}
	
	m_LastAnimationTime = m_pGameTime->GetTotal();

	m_pAnimator->SetAnimation(newAnimationState);
	m_CharacterState = newAnimationState;
}

bool Character::DoesRaycastHitCollisionGroup(CollisionGroup collisionGroup, float distance) const
{
	auto activeScene = SceneManager::Get()->GetActiveScene();
	physx::PxVec3 start = PhysxHelper::ToPxVec3(GetTransform()->GetPosition());
	physx::PxRaycastBuffer hit{};
	physx::PxQueryFilterData filterData{};
	filterData.data.word0 = UINT(collisionGroup);

	return activeScene->GetPhysxProxy()->Raycast(start,
		{ 0,-1,0 },
		distance,
		hit,
		physx::PxHitFlag::eDEFAULT | physx::PxHitFlag::eMESH_ANY | physx::PxHitFlag::eASSUME_NO_INITIAL_OVERLAP,
		filterData) && hit.hasBlock;
}

void Character::DrawImGui()
{
	if (ImGui::CollapsingHeader("Character"))
	{
		ImGui::Text(std::format("Move Speed: {:0.1f} m/s", m_MoveSpeed).c_str());
		ImGui::Text(std::format("Fall Speed: {:0.1f} m/s", m_TotalVelocity.y).c_str());

		ImGui::Text(std::format("Move Acceleration: {:0.1f} m/s2", m_MoveAcceleration).c_str());
		ImGui::Text(std::format("Fall Acceleration: {:0.1f} m/s2", m_FallAcceleration).c_str());

		const float jumpMaxTime = m_CharacterDesc.JumpSpeed / m_FallAcceleration;
		const float jumpMaxHeight = (m_CharacterDesc.JumpSpeed * jumpMaxTime) - (0.5f * (m_FallAcceleration * powf(jumpMaxTime, 2)));
		ImGui::Text(std::format("Jump Height: {:0.1f} m", jumpMaxHeight).c_str());

		ImGui::Dummy({ 0.f,5.f });
		if (ImGui::DragFloat("Max Move Speed (m/s)", &m_CharacterDesc.maxMoveSpeed, 0.1f, 0.f, 0.f, "%.1f") ||
			ImGui::DragFloat("Move Acceleration Time (s)", &m_CharacterDesc.moveAccelerationTime, 0.1f, 0.f, 0.f, "%.1f"))
		{
			m_MoveAcceleration = m_CharacterDesc.maxMoveSpeed / m_CharacterDesc.moveAccelerationTime;
		}

		ImGui::Dummy({ 0.f,5.f });
		if (ImGui::DragFloat("Max Fall Speed (m/s)", &m_CharacterDesc.maxFallSpeed, 0.1f, 0.f, 0.f, "%.1f") ||
			ImGui::DragFloat("Fall Acceleration Time (s)", &m_CharacterDesc.fallAccelerationTime, 0.1f, 0.f, 0.f, "%.1f"))
		{
			m_FallAcceleration = m_CharacterDesc.maxFallSpeed / m_CharacterDesc.fallAccelerationTime;
		}

		ImGui::Dummy({ 0.f,5.f });
		ImGui::DragFloat("Jump Speed", &m_CharacterDesc.JumpSpeed, 0.1f, 0.f, 0.f, "%.1f");
		ImGui::DragFloat("Rotation Speed (deg/s)", &m_CharacterDesc.rotationSpeed, 0.1f, 0.f, 0.f, "%.1f");

		bool isActive = m_pCameraComponent->IsActive();
		if(ImGui::Checkbox("Character Camera", &isActive))
		{
			m_pCameraComponent->SetActive(isActive);
		}

		float x = m_pVisuals->GetTransform()->GetPosition().y;
		ImGui::DragFloat("Visual Offset", &x, 0.1f, 0.f, 0.f, "%.1f");
		m_pVisuals->GetTransform()->Translate(0, x, 0);

		ImGui::DragFloat("Camera Normal Offset", &m_CameraNormalOffset, 0.1f, 0.f, 0.f, "%.1f");
	}
}