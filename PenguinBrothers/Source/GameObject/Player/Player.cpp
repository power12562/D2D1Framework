#include "Player.h"
#include <Framework/WorldManager.h>

#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/SpriteCollider2D.h"
#include "Core/Component/Movement.h"
#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/Component/Rigidbody2D.h"

#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/PlayerBomb.h"


Player::Player()
{
	OderLayer = 1;
	tag = L"Player";
	transform.scale = Vector2(4.0f, 4.0f);

	Input = &AddComponent<InputBinding>();
	Input->BindKey("Left", KeyCode::LeftArrow);
	//Input->BindKey("Left", KeyCode::A);
	Input->BindKey("Right", KeyCode::RightArrow);
	//Input->BindKey("Right", KeyCode::D);
	Input->BindKey("Duck", KeyCode::DownArrow);
	//Input->BindKey("Duck", KeyCode::S);

	Input->BindKey("Attack", KeyCode::LeftCtrl);
	Input->BindKey("Attack", KeyCode::Z);
	
	Input->BindKey("Jump", KeyCode::LeftAlt);
	Input->BindKey("Jump", KeyCode::X);


	AddComponent<Movement>();
	AddComponent<SpriteAnimationRenderer>();
	SpriteAnimationRenderer& spriteAnimation = GetComponent<SpriteAnimationRenderer>();
	/*spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Idle.txt", L"Resource/Player/Normal/Normal.png", L"Idle");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Walk.txt", L"Resource/Player/Normal/Normal.png", L"Walk");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Attack.txt", L"Resource/Player/Normal/Normal.png", L"Attack");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Duck.txt", L"Resource/Player/Normal/Normal.png", L"Duck");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Jump.txt", L"Resource/Player/Normal/Normal.png", L"Jump");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Slide.txt", L"Resource/Player/Normal/Normal.png", L"Slide");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Spawn/Spawn.txt", L"Resource/Player/Spawn/Spawn.png", L"Spawn");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Dead/Dead.txt", L"Resource/Player/Dead/Dead.png", L"Dead");*/
	spriteAnimation.LoadAnimationAssetToJson(L"Resource/Player/AnimeAsset.json");

	BoxCollider2D& collider = AddComponent<BoxCollider2D>();
	collider.ColliderSize = Vector2{ 80.f, 80.f };

#ifdef _DEBUG
	collider.isDrawCollider = true;
#endif // DEBUG

	AddComponent<Rigidbody2D>();

	AddComponent<PlayerCtrl>();
	FiniteStateMachine& fsm = AddComponent<FiniteStateMachine>();
	fsm.CreateState<Idle>(L"Idle");
	fsm.CreateState<Spawn>(L"Spawn");
	fsm.CreateState<Walk>(L"Walk");
	fsm.CreateState<Duck>(L"Duck");
	fsm.CreateState<Slide>(L"Slide");
	fsm.CreateState<Attack>(L"Attack");
	fsm.CreateState<Dead>(L"Dead");
	fsm.CreateState<Jump>(L"Jump");

	fsm.SetState(L"Spawn");
}

Player::~Player()
{

}


//state

PlayerState::PlayerState(FiniteStateMachine& _owner, const wchar_t* _name) : FSMState(_owner, _name)
{
	movement = &owner.gameObject.GetComponent<Movement>();
	spriteAnimation = &owner.gameObject.GetComponent<SpriteAnimationRenderer>();
	playerCtrl = &owner.gameObject.GetComponent<PlayerCtrl>();
	Input = &owner.GetComponent<InputBinding>();
}


void Spawn::Enter()
{
	spriteAnimation->SetAnimation(L"Spawn");
	owner.IsComponent<Rigidbody2D>()->enabled = false;	
}

void Spawn::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		owner.SetState(L"Idle");
		playerCtrl->isJump = true;
	}
}

void Spawn::Exit()
{
	owner.IsComponent<Rigidbody2D>()->enabled = true;
}


void Idle::Enter()
{
	spriteAnimation->SetAnimation(L"Idle", true);
	playerCtrl->isJump = false;
}

void Idle::Update()
{
	if (Input->IsKey("Left"))
	{
		owner.SetState(L"Walk");
		movement->SetDirection(Vector2::Left);
		owner.gameObject.transform.FlipX(true);
	}
	else if (Input->IsKey("Right"))
	{
		owner.SetState(L"Walk");
		movement->SetDirection(Vector2::Right);
		owner.gameObject.transform.FlipX(false);
	}

	if (Input->IsKeyDown("Attack") && PlayerBomb::GetObjectCount() == 0)
	{
		owner.SetState(L"Attack");
	}
	else if (Input->IsKeyDown("Jump") && !playerCtrl->isJump)
	{
		owner.SetState(L"Jump");
	}

	if (Input->IsKey("Duck"))
	{
		owner.SetState(L"Duck");
	}
}

void Walk::Enter()
{
	spriteAnimation->SetAnimation(L"Walk", true);
	movement->SetSpeed(playerCtrl->moveSpeed);
}

void Walk::Update()
{
	if ((!Input->IsKey("Left") && !Input->IsKey("Right")))
	{
		owner.SetState(L"Idle");
	}

	if (Input->IsKey("Left"))
	{
		movement->SetDirection(Vector2::Left);
		owner.gameObject.transform.FlipX(true);
	}
	else if (Input->IsKey("Right"))
	{
		movement->SetDirection(Vector2::Right);
		owner.gameObject.transform.FlipX(false);
	}

	if (Input->IsKeyDown("Attack") && PlayerBomb::GetObjectCount() == 0)
	{
		owner.SetState(L"Attack");
	}
	else if (Input->IsKeyDown("Jump") && !playerCtrl->isJump)
	{
		owner.SetState(L"Jump");
	}

	if (Input->IsKey("Duck"))
	{
		owner.SetState(L"Duck");
	}
}

void Walk::Exit()
{
	movement->SetSpeed(0.f);
}


void Duck::Enter()
{
	movement->SetSpeed(0.f);
	spriteAnimation->SetAnimation(L"Duck");
}

void Duck::Update()
{
	if (Input->IsKeyUp("Duck"))
	{
		owner.SetState(L"Idle");
	}

	if (Input->IsKeyDown("Jump"))
	{
		owner.SetState(L"Slide");
	}
}


void Slide::Enter()
{
	movement->SetSpeed(playerCtrl->slideSpeed);
	spriteAnimation->SetAnimation(L"Slide");
}

void Slide::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		owner.SetState(L"Idle");
		spriteAnimation->SetAnimation(L"Idle");
	}
}

void Slide::Exit()
{
	movement->SetSpeed(0.f);
}



void Attack::Enter()
{
	movement->SetSpeed(0.f);
	spriteAnimation->SetAnimation(L"Attack");
}

void Attack::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		owner.SetState(L"Idle");
		playerCtrl->SpawnBomb();
	}
}

void Dead::Enter()
{
	movement->SetSpeed(0.f);
	spriteAnimation->SetAnimation(L"Dead");
	owner.Transition = false;
	owner.GetComponent<Rigidbody2D>().enabled = false;
}
												
void Dead::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		WorldManager::DelGameObject(owner.gameObject);
	}
}

void Jump::Enter()
{
	static constexpr float jumpPower = 1000.f;
	static constexpr float jumpPowerHalf = jumpPower / 2;

	Rigidbody2D& rb = owner.GetComponent<Rigidbody2D>();
	if (Input->IsKey("Left"))
	{
		rb.AddForce(Vector2::Up * jumpPowerHalf);
		rb.AddForce(Vector2::Left * jumpPowerHalf);
	}
	else if (Input->IsKey("Right"))
	{
		rb.AddForce(Vector2::Up * jumpPowerHalf);
		rb.AddForce(Vector2::Right * jumpPowerHalf);
	}
	else
	{
		rb.AddForce(Vector2::Up * jumpPower * 0.7f);
	}

	spriteAnimation->SetAnimation(L"Jump");
	playerCtrl->isJump = true;
}

void Jump::Update()
{
	if (!playerCtrl->isJump)
	{
		owner.SetState(L"Idle");
	}
}
