#include "EnemyDino0AttackCtrl.h"
#include <Framework/WorldManager.h>

#include "Core/GameObject/Base/GameObjectBase.h"
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>
#include <Core/Component/FSM/FiniteStateMachine.h>


EnemyDino0AttackCtrl::EnemyDino0AttackCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject), ICollider2DNotify(this)
{

}

EnemyDino0AttackCtrl::~EnemyDino0AttackCtrl()
{
}

void EnemyDino0AttackCtrl::Start()
{
	animation = &gameObject.GetComponent<SpriteAnimationRenderer>();
}

void EnemyDino0AttackCtrl::Update()
{
	if (animation->CurrentClipEnd)
	{
		WorldManager::DelGameObject(gameObject);
	}
}

void EnemyDino0AttackCtrl::OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{
		otherCollider->GetComponent<FiniteStateMachine>().SetState(L"Dead");
	}
}
