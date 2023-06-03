#pragma once
struct CharacterDesc
{
	CharacterDesc(
		PxMaterial* pMaterial,
		float radius = .5f,
		float height = 2.f)
	{
		controller.setToDefault();
		controller.radius = radius;
		controller.height = height;
		controller.material = pMaterial;
	}

	float maxMoveSpeed{ 15.f };
	float maxFallSpeed{ 15.f };

	float JumpSpeed{ 15.f };

	float moveAccelerationTime{ .3f };
	float fallAccelerationTime{ .3f };

	PxCapsuleControllerDesc controller{};

	float rotationSpeed{ 60.f };

	int actionId_MoveLeft{ -1 };
	int actionId_MoveRight{ -1 };
	int actionId_MoveForward{ -1 };
	int actionId_MoveBackward{ -1 };
	int actionId_Throw{ -1 };
	int actionId_Jump{ -1 };
};

class Bomb;
class Character : public GameObject
{
public:
	enum CharacterAnimation : uint8_t
	{
		Idle = 0,
		Throw = 1,
		Swimming = 2,
		Running = 3,
		Jump = 4,
		Dying = 5,
		Climbing = 6,
		Falling = 7,
		SwimmingIdle = 8
	};

	Character(const CharacterDesc& characterDesc, const XMFLOAT3& cameraOffset);
	~Character() override = default;

	Character(const Character& other) = delete;
	Character(Character&& other) noexcept = delete;
	Character& operator=(const Character& other) = delete;
	Character& operator=(Character&& other) noexcept = delete;

	void DrawImGui();

	void SetLightOffset(const XMFLOAT4& offset) { m_LightOffset = offset; };
	XMFLOAT4 GetLightOffset()const { return m_LightOffset; };

	bool PickUpBomb(Bomb* pBomb);
protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;

private:
	//Camera
	CameraComponent* m_pCameraComponent{};
	XMFLOAT3 m_CameraOffset{ 0,0,0 };
	//XMFLOAT4 m_LightOffset{ 35.7f,44.3f,-23.2f,0 };
	XMFLOAT4 m_LightOffset{ 35.7f,44.3f,-23.2f,0 };
	ControllerComponent* m_pControllerComponent{};

	//Visuals
	GameObject* m_pVisuals;
	ModelAnimator* m_pAnimator{};

	int m_AnimationClipId{ 0 };
	float m_AnimationSpeed{ 1.f };

	CharacterAnimation m_CharacterState{ CharacterAnimation::Idle };

	CharacterDesc m_CharacterDesc;
	float m_MinPitch{-70}, m_MaxPitch{70};			
	float m_TotalPitch{}, m_TotalYaw{};				//Total camera Pitch(X) and Yaw(Y) rotation
	float m_MoveAcceleration{},						//Acceleration required to reach maxMoveVelocity after 1 second (maxMoveVelocity / moveAccelerationTime)
		m_FallAcceleration{},						//Acceleration required to reach maxFallVelocity after 1 second (maxFallVelocity / fallAccelerationTime)
		m_MoveSpeed{};								//MoveSpeed > Horizontal Velocity = MoveDirection * MoveVelocity (= TotalVelocity.xz)

	XMFLOAT3 m_TotalVelocity{};						//TotalVelocity with X/Z for Horizontal Movement AND Y for Vertical Movement (fall/jump)
	XMFLOAT3 m_CurrentDirection{};					//Current/Last Direction based on Camera forward/right (Stored for deacceleration)

	void AdjustCamera();
	void ThrowBomb();
	void SetCharacterAnimation(CharacterAnimation newAnimationState);
	float m_CameraNormalOffset{.8f};
	bool m_HasHitPreviousTime{ false };

	float m_LastAnimationTime{ }, m_AnimationDuration{ 1.f };

	Bomb* m_pBomb{ nullptr };
};

