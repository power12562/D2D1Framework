#include "Player.h"
#include <Framework/WorldManager.h>
#include <Framework/TimeSystem.h>

#include <Core/GameObject/Base/GameObjectUI.h>
#include <Core/Component/Renderer/SpriteRenderer.h>
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/SpriteCollider2D.h"
#include "Core/Component/Movement.h"
#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/Component/AudioClip.h"
#include "Core/Component/Rigidbody2D.h"

#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/PlayerBomb.h"
#include "Source/Component/GameManagerCtrl.h"

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

	AddComponent<AudioClip>();
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
	fsm.CreateState<Win>(L"Win");
	fsm.CreateState<Airborne>(L"Airborne");

	fsm.SetState(L"Spawn");
}

Player::~Player()
{

}


//state

Vector2 PlayerState::SpawnPos = Vector2{0, 0};
Vector2 PlayerState::SpawnScale = Vector2{0, 0};

PlayerState::PlayerState(FiniteStateMachine& _owner, const wchar_t* _name) : FSMState(_owner, _name)
{
	SpawnPos = owner.gameObject.transform.position;
	SpawnScale = owner.gameObject.transform.scale;

	movement = &owner.gameObject.GetComponent<Movement>();
	spriteAnimation = &owner.gameObject.GetComponent<SpriteAnimationRenderer>();
	playerCtrl = &owner.gameObject.GetComponent<PlayerCtrl>();
	Input = &owner.GetComponent<InputBinding>();

	audioClip = &owner.GetComponent<AudioClip>();
	audioClip->group = SoundSystem::ChannelGroup::sfx;
}


void Spawn::Enter()
{
	playerCtrl->isJump = true;
	spriteAnimation->SetAnimation(L"Spawn");
	owner.IsComponent<Rigidbody2D>()->enabled = false;
	owner.IsComponent<Rigidbody2D>()->Velocity = Vector2(0, 0);

	audioClip->LoadAudio(L"Resource/Player/Spawn/spawn.wav");
	audioClip->Play(false);
}

void Spawn::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		owner.SetState(L"Idle");
	}
}

void Spawn::Exit()
{
	owner.IsComponent<Rigidbody2D>()->enabled = true;
	SpawnPos = owner.gameObject.transform.position;
	audioClip->Stop();
}


void Idle::Enter()
{
	spriteAnimation->SetAnimation(L"Idle", true);
	BoxCollider2D& coll = owner.GetComponent<BoxCollider2D>();
	owner.GetComponent<Rigidbody2D>().Velocity.x = 0;
	coll.ColliderSize = { 80.0, 80.0 };
	coll.Center = { 0,0 };
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
	BoxCollider2D& coll = owner.GetComponent<BoxCollider2D>();
	coll.ColliderSize = { 80, 40 };
	coll.Center = { 0, -20 };
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
		if (Input->IsKey("Duck") && !playerCtrl->isJump)
		{
			owner.SetState(L"Duck");
			return;
		}
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

	audioClip->LoadAudio(L"Resource/Player/Dead/Dead.wav");
	audioClip->Play();
}
												
void Dead::Update()
{
	if (spriteAnimation->CurrentClipEnd)
	{
		owner.transform.SetParent();
		owner.transform.position = SpawnPos;
		owner.transform.scale = SpawnScale;
		owner.transform.rotation = 0;

		owner.Transition = true;
		owner.SetState(L"Spawn");
	}
}

void Dead::Exit()
{
	audioClip->Stop();
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

void Jump::Exit()
{
	
}

void Airborne::Enter()
{
	spriteAnimation->SetAnimation(L"Jump");
	playerCtrl->isJump = true;
}

void Airborne::Update()
{
	if (owner.GetComponent<Rigidbody2D>().Velocity == Vector2{0,0})
	{
		owner.SetState(L"Idle");
	}
}

void Win::Enter()
{
	owner.Transition = false;
	owner.GetComponent<Rigidbody2D>().isKinematic = true;
	spriteAnimation->SetAnimation(L"Win");

	GameObjectBase* cool = WorldManager::AddGameObject<GameObjectUI>(L"Cool");
	cool->AddComponent<SpriteRenderer>().LoadImage(L"Resource/COOL.png");
	cool->transform.scale = Vector2(4.0f, 4.0f);;

	audioClip->LoadAudio(L"Resource/Player/Win/Win.wav");
	audioClip->Play(false);
}

void Win::Update()
{
	if(spriteAnimation->CurrentClipEnd)
	{
		owner.gameObject.Find(L"GameManager")->GetComponent<GameManagerCtrl>().LoadNextStage();
	}
}

void Win::Exit()
{
	owner.Transition = true;
	owner.GetComponent<Rigidbody2D>().isKinematic = false;
}

