#include "EnemyDino0.h"
#include "Framework/WorldManager.h"

#include <Core/Component/Rigidbody2D.h>
#include <Core/Component/Collider/BoxCollider2D.h>
#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Movement.h"
#include "Core/Component/AudioClip.h"

#include "Source/Component/Enemy/EnemyDino0Ctrl.h"
#include "Source/Component/GameManagerCtrl.h"

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(EnemyDino0)


EnemyDino0::EnemyDino0()
{
	transform.scale = Vector2(4.0f, 4.0f);
	tag = L"Enemy";

	AddComponent<Rigidbody2D>().enabled = false;
	BoxCollider2D& coll = AddComponent<BoxCollider2D>();
	coll.ColliderSize = Vector2{ 120,120 };
#ifdef _DEBUG
	coll.isDrawCollider = true;
#endif

	AudioClip& audioClip = AddComponent<AudioClip>();
	audioClip.LoadAudio(L"Resource/Enemy/Dino0/Dead.wav");
	audioClip.group = SoundSystem::ChannelGroup::sfx;

	AddComponent<EnemyDino0Ctrl>();
	AddComponent<Movement>();
	auto& animationRenderer = AddComponent<SpriteAnimationRenderer>();
	const wchar_t* dinoPngPath = L"Resource/Enemy/Dino0/EnemyDino0.png";
	animationRenderer.LoadAnimationClip(L"Resource/Enemy/Dino0/Idle.csv", dinoPngPath, L"Idle");
	animationRenderer.LoadAnimationClip(L"Resource/Enemy/Dino0/Walk.csv", dinoPngPath, L"Walk");
	animationRenderer.LoadAnimationClip(L"Resource/Enemy/Dino0/Attack.csv", dinoPngPath, L"Attack");

	auto& fsm = AddComponent<FiniteStateMachine>();
	fsm.CreateState<EnemySpawn>(L"Spawn");
	fsm.CreateState<EnemyIdle>(L"Idle");
	fsm.CreateState<EnemyTracking>(L"Tracking");
	fsm.CreateState<EnemyAttack>(L"Attack");
	fsm.CreateState<EnemyAirborne>(L"Airborne");
	fsm.CreateState<EnemyDead>(L"Dead");

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

void EnemySpawn::Enter()
{
	animationRenderer->SetAnimation(L"Idle", true);
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
		Vector2 dir = player->transform.position - owner.gameObject.transform.position;
		float xDis = abs(dir.x);
		float yDis = abs(dir.y);
		if (xDis <= trackingDis && yDis <= 100.f)
		{
			//추적 모드로 변환
			owner.SetState(L"Tracking");
		}
	}
}


void EnemyTracking::Enter()
{
	player = owner.gameObject.Find(L"Player");
	dir = player->transform.position - owner.gameObject.transform.position;
	float xDis = abs(dir.x);
	float yDis = abs(dir.y);
	dir.y = 0.f;
	dir = dir.Normalized();
	if (yDis <= 100.f)
	{
		movement->SetDirection(dir);
		movement->SetSpeed(150.f);
		animationRenderer->SetAnimation(L"Walk", true);
	}
	else
	{
		owner.SetState(L"Idle");
	}
}

void EnemyTracking::Update()
{
	player = owner.gameObject.Find(L"Player");
	if (player)
	{
		dir = player->transform.position - owner.gameObject.transform.position;
		float xDis = abs(dir.x);
		float yDis = abs(dir.y);
		dir.y = 0.f;
		dir = dir.Normalized();

		if (yDis <= 100.f)
		{
			if (attackDis > xDis)
			{
				owner.SetState(L"Attack");
			}
			movement->SetDirection(dir);
			if (dir.x > 0)
			{
				owner.gameObject.transform.FlipX(true);
			}
			else if (dir.x < 0)
			{
				owner.gameObject.transform.FlipX(false);
			}
		}
		else
		{
			owner.SetState(L"Idle");
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

void EnemyAirborne::Enter()
{
	movement->SetSpeed(0);
	animationRenderer->SetAnimation(L"Idle", true);
}

void EnemyAirborne::Update()
{
	if (owner.GetComponent<Rigidbody2D>().Velocity == Vector2{0, 0})
	{
		owner.SetState(L"Idle");
	}
}

void EnemyDead::Enter()
{
	owner.GetComponent<AudioClip>().Play();
	owner.gameObject.enable = false;
	GameManagerCtrl::EnemyCount--;
	if (GameManagerCtrl::EnemyCount == 0)
	{
		for (auto& p : WorldManager::FindGameObjectsWithTag(L"Player"))
		{
			FiniteStateMachine& fsm = p->GetComponent<FiniteStateMachine>();
			fsm.Transition = true;
			fsm.SetState(L"Win");
		}
	}
}
