#include "Player.h"
#include <Framework/WorldManager.h>

#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/SpriteCollider2D.h"
#include "Core/Component/Movement.h"
#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/Component/Rigidbody2D.h"

#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/PlayerBomb.h"

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Player)

Player::Player()
{
	OderLayer = 1;
	tag = L"Player";
	transform.scale = Vector2(4.0f, 4.0f);

	Input = &AddComponent<InputBinding>();
	Input->BindKey("Left", KeyCode::LeftArrow);
	Input->BindKey("Right", KeyCode::RightArrow);
	Input->BindKey("Duck", KeyCode::DownArrow);
	Input->BindKey("Attack", KeyCode::LeftCtrl);
	Input->BindKey("Attack", KeyCode::Z);
	
	Input->BindKey("Jump", KeyCode::LeftAlt);
	Input->BindKey("Jump", KeyCode::X);

	AddComponent<Movement>();
	AddComponent<SpriteAnimationRenderer>();
	SpriteAnimationRenderer& spriteAnimation = GetComponent<SpriteAnimationRenderer>();
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

Vector2 PlayerState::SpawnPos = Vector2{0, 0};

PlayerState::PlayerState(FiniteStateMachine& _owner, const wchar_t* _name) : FSMState(_owner, _name)
{
	SpawnPos = owner.gameObject.transform.position;
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
		playerCtrl->isJump = false;
	}
}

void Spawn::Exit()
{
	owner.IsComponent<Rigidbody2D>()->enabled = true;
	SpawnPos = owner.gameObject.transform.position;
	playerCtrl->isJump = false;
}


void Idle::Enter()
{
	spriteAnimation->SetAnimation(L"Idle", true);
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

	if (Input->IsKey("Duck") && !playerCtrl->isJump)
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

	if (Input->IsKey("Duck") && !playerCtrl->isJump)
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
	owner.GetComponent<Rigidbody2D>().enabled = false;
	owner.Transition = false;
}
												
void Dead::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		owner.transform.position = SpawnPos;
		owner.Transition = true;
		owner.SetState(L"Spawn");
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
