#include "Player.h"
#include "Framework/InputSystem.h"

#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/BoxCollider2D.h"
#include "Core/Component/Movement.h"
#include "Core/Component/FSM/FiniteStateMachine.h"

#include "Source/Component/PlayerCtrl.h"


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
	if (movement->GetSpeed() != 0)
	{
		owner.SetState(L"Walk");
	}
}

void Walk::Enter()
{
	spriteAnimation->SetAnimation(L"Walk", true);
}

void Walk::Update()
{
	using namespace InputSystem;

	Vector2 dir = movement->GetDirection();
	if (dir == Vector2::Left)
	{
		owner.gameObject.transform.FlipX(true);
	}
	else
	{
		owner.gameObject.transform.FlipX(false);
	}

	if ((!Input.IsKey(KeyCode::LeftArrow) && !Input.IsKey(KeyCode::RightArrow)))
	{
		owner.SetState(L"Idle");
	}
}

void Walk::Exit()
{
	movement->SetSpeed(0.f);
}
