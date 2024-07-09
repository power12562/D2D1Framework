#include "EnemyDino0AttackCtrl.h"
#include <Framework/WorldManager.h>

#include "Core/GameObject/Base/GameObjectBase.h"
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

EnemyDino0AttackCtrl::EnemyDino0AttackCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
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
