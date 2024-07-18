#include "EnemyDino0.h"
#include "Framework/WorldManager.h"

#include <Core/Component/Rigidbody2D.h>
#include "Core/Component/Collider/SpriteCollider2D.h"
#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Movement.h"

#include "Source/Component/Enemy/EnemyDino0Ctrl.h"


EnemyDino0::EnemyDino0()
{
	transform.scale = Vector2(4.0f, 4.0f);
	tag = L"Enemy";

	AddComponent<Rigidbody2D>();
	AddComponent<SpriteCollider2D>();
	AddComponent<EnemyDino0Ctrl>();
	AddComponent<Movement>();
	auto& animationRenderer = AddComponent<SpriteAnimationRenderer>();
	const wchar_t* dinoPngPath = L"Resource/Enemy/Dino0/EnemyDino0.png";
	animationRenderer.LoadAnimationClip(L"Resource/Enemy/Dino0/Idle.txt", dinoPngPath, L"Idle");
	animationRenderer.LoadAnimationClip(L"Resource/Enemy/Dino0/Walk.txt", dinoPngPath, L"Walk");
	animationRenderer.LoadAnimationClip(L"Resource/Enemy/Dino0/Attack.txt", dinoPngPath, L"Attack");

	auto& fsm = AddComponent<FiniteStateMachine>();
	fsm.CreateState<EnemySpawn>(L"Spawn");
	fsm.CreateState<EnemyIdle>(L"Idle");
	fsm.CreateState<EnemyTracking>(L"Tracking");
	fsm.CreateState<EnemyAttack>(L"Attack");

	fsm.SetState(L"Spawn");
}

EnemyDino0::~EnemyDino0()
{

}


GameObjectBase* EnemyState::player = nullptr;
EnemyState::EnemyState(FiniteStateMachine& _owner, const wchar_t* _name) : FSMState(_owner, _name)
{
	this->movement = &owner.gameObject.GetComponent<Movement>();
	this->animationRenderer = &owner.gameObject.GetComponent<SpriteAnimationRenderer>();
	this->trackingDis = 400.f;
	this->attackDis = 200.f;
}

void EnemySpawn::Update()
{
	if (player == nullptr)
	{
		player = WorldManager::FindGameObject(L"Player");
	}
	else
	{
		owner.SetState(L"Idle");
	}
}


void EnemyIdle::Enter()
{
	movement->SetSpeed(0);
	animationRenderer->SetAnimation(L"Idle", true);
}

void EnemyIdle::Update()
{
	player = owner.gameObject.Find(L"Player");
	if (player)
	{
		float toPlayerDis = (player->transform.position - owner.gameObject.transform.position).Magnitude();
		if (toPlayerDis <= trackingDis)
		{
			//추적 모드로 변환
			owner.SetState(L"Tracking");
		}
	}	
}



void EnemyTracking::Enter()
{
	player = owner.gameObject.Find(L"Player");
	if (player)
	{
		animationRenderer->SetAnimation(L"Walk", true);
		movement->SetSpeed(150.f);
		dir = player->transform.position - owner.gameObject.transform.position;
		dir.y = 0.f;
		dir = dir.Normalized();
		movement->SetDirection(dir);
	}
}

void EnemyTracking::Update()
{
	player = owner.gameObject.Find(L"Player");
	if (player)
	{
		dir = player->transform.position - owner.gameObject.transform.position;
		float toPlayerDis = dir.Magnitude();
		dir.y = 0.f;
		dir = dir.Normalized();
		movement->SetDirection(dir);

		if (abs(dir.x) >= 1.f)
		{
			if (toPlayerDis > trackingDis)
			{
				owner.SetState(L"Idle");
			}
			else if (attackDis > toPlayerDis)
			{
				owner.SetState(L"Attack");
			}

			if (dir.x > 0)
			{
				owner.gameObject.transform.FlipX(true);
			}
			else if (dir.x < 0)
			{
				owner.gameObject.transform.FlipX(false);
			}
		}
	}	
	else
	{
		owner.SetState(L"Idle");
	}
}


EnemyAttack::EnemyAttack(FiniteStateMachine& _owner, const wchar_t* _name) : EnemyState(_owner, _name)
{
	dinoCtrl = &owner.gameObject.GetComponent<EnemyDino0Ctrl>();
}

void EnemyAttack::Enter()
{
	attackSpawn = false;
	movement->SetSpeed(0.f);
	animationRenderer->SetAnimation(L"Attack");
}

void EnemyAttack::Update()
{
	if (animationRenderer->CurrentClipEnd)
	{
		owner.SetState(L"Idle");
	}
	if (!attackSpawn && animationRenderer->CurrentFrameIndex == 2)
	{
		dinoCtrl->SpawnFire();
		attackSpawn = true;
	}
}
