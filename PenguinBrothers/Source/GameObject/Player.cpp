#include "Player.h"
#include "Framework/InputSystem.h"

#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/BoxCollider2D.h"
#include "Core/Component/Movement.h"
#include "Core/Component/FSM/FiniteStateMachine.h"

#include "Source/Component/PlayerCtrl.h"
#include "Source/GameObject/PlayerBomb.h"


Player::Player()
{
	transform.scale = Vector2(4.0f, 4.0f);

	AddComponent<Movement>();
	AddComponent<SpriteAnimationRenderer>();
	SpriteAnimationRenderer& spriteAnimation = GetComponent<SpriteAnimationRenderer>();
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Idle.txt", L"Resource/Player/Normal/Normal.png", L"Idle");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Walk.txt", L"Resource/Player/Normal/Normal.png", L"Walk");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Attack.txt", L"Resource/Player/Normal/Normal.png", L"Attack");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Duck.txt", L"Resource/Player/Normal/Normal.png", L"Duck");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Jump.txt", L"Resource/Player/Normal/Normal.png", L"Jump");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Slide.txt", L"Resource/Player/Normal/Normal.png", L"Slide");
	spriteAnimation.LoadAnimation(L"Resource/Player/Spawn/Spawn.txt", L"Resource/Player/Spawn/Spawn.png", L"Spawn");
	spriteAnimation.LoadAnimation(L"Resource/Player/Dead/Dead.txt", L"Resource/Player/Dead/Dead.png", L"Dead");

	BoxCollider2D& boxCollider2D = AddComponent<BoxCollider2D>();
#ifdef _DEBUG
	boxCollider2D.isDrawCollider = true;
#endif // DEBUG

	AddComponent<PlayerCtrl>();
	FiniteStateMachine& fsm = AddComponent<FiniteStateMachine>();
	fsm.CreateState<Idle>(L"Idle");
	fsm.CreateState<Spawn>(L"Spawn");
	fsm.CreateState<Walk>(L"Walk");
	fsm.CreateState<Duck>(L"Duck");
	fsm.CreateState<Slide>(L"Slide");
	fsm.CreateState<Attack>(L"Attack");

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
}


void Spawn::Enter()
{
	spriteAnimation->SetAnimation(L"Spawn");
}

void Spawn::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		owner.SetState(L"Idle");
	}
}


void Idle::Enter()
{
	spriteAnimation->SetAnimation(L"Idle", true);
}

void Idle::Update()
{
	using namespace InputSystem;


	if (Input.IsKey(KeyCode::LeftArrow))
	{
		owner.SetState(L"Walk");
		movement->SetDirection(Vector2::Left);
		owner.gameObject.transform.FlipX(true);
	}
	else if (Input.IsKey(KeyCode::RightArrow))
	{
		owner.SetState(L"Walk");
		movement->SetDirection(Vector2::Right);
		owner.gameObject.transform.FlipX(false);
	}

	if (Input.IsKeyDown(KeyCode::LeftCtrl) && PlayerBomb::GetObjectCount() == 0)
	{
		owner.SetState(L"Attack");
	}

	if (Input.IsKey(KeyCode::DownArrow))
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
	using namespace InputSystem;
	if ((!Input.IsKey(KeyCode::LeftArrow) && !Input.IsKey(KeyCode::RightArrow)))
	{
		owner.SetState(L"Idle");
	}

	if (Input.IsKey(KeyCode::LeftArrow))
	{
		movement->SetDirection(Vector2::Left);
		owner.gameObject.transform.FlipX(true);
	}
	else if (Input.IsKey(KeyCode::RightArrow))
	{
		movement->SetDirection(Vector2::Right);
		owner.gameObject.transform.FlipX(false);
	}

	if (Input.IsKeyDown(KeyCode::LeftCtrl) && PlayerBomb::GetObjectCount() == 0)
	{
		owner.SetState(L"Attack");
	}

	if (Input.IsKey(KeyCode::DownArrow))
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
	using namespace InputSystem;
	if (Input.IsKeyUp(KeyCode::DownArrow))
	{
		owner.SetState(L"Idle");
	}

	if (Input.IsKeyDown(KeyCode::LeftAlt))
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
