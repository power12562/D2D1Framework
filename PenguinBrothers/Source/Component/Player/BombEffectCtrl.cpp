#include "BombEffectCtrl.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

BombEffectCtrl::BombEffectCtrl(GameObjectBase& gameObject): ComponentBase(gameObject) 
{
}

BombEffectCtrl::~BombEffectCtrl()
{
}

void BombEffectCtrl::Start()
{
	animationRenderer = &GetComponent<SpriteAnimationRenderer>();
}

void BombEffectCtrl::Update()
{
	if (animationRenderer->CurrentClipEnd)
	{
		WorldManager::DelGameObject(gameObject);
	}
}
