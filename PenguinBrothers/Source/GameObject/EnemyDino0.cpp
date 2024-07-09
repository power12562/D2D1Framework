#include "EnemyDino0.h"
#include "Framework/WorldManager.h"

#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Movement.h"


EnemyDino0::EnemyDino0()
{
	transform.scale = Vector2(3.0f, 3.0f);

	AddComponent<Movement>();
	auto& animationRenderer = AddComponent<SpriteAnimationRenderer>();
	const wchar_t* dinoPngPath = L"Resource/Enemy/Dino0/EnemyDino0.png";
	animationRenderer.LoadAnimation(L"Resource/Enemy/Dino0/Idle.txt", dinoPngPath, L"Idle");
	animationRenderer.LoadAnimation(L"Resource/Enemy/Dino0/Walk.txt", dinoPngPath, L"Walk");
	animationRenderer.LoadAnimation(L"Resource/Enemy/Dino0/Attack.txt", dinoPngPath, L"Attack");

	auto& fsm = AddComponent<FiniteStateMachine>();
	fsm.CreateState<EnemyIdle>(L"Idle");
	fsm.SetState(L"Idle");
}

EnemyDino0::~EnemyDino0()
{

}

EnemyState::EnemyState(FiniteStateMachine& _owner, const wchar_t* _name) : FSMState(_owner, _name)
{
	this->movement = &owner.gameObject.GetComponent<Movement>();
	this->animationRenderer = &owner.gameObject.GetComponent<SpriteAnimationRenderer>();
}

void EnemyIdle::Enter()
{
	movement->SetSpeed(0);
	animationRenderer->SetAnimation(L"Idle", true);
}

void EnemyIdle::Update()
{
	if (player)
	{
		float toPlayerDis = (player->transform.position - owner.gameObject.transform.position).Magnitude();
		if (toPlayerDis < playerTrackingDis)
		{
			
		}
	}
	else
	{
		player = WorldManager::FindGameObject(L"Player");
	}
}

void EnemyIdle::Exit()
{

}
