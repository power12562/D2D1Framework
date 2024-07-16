#include "BombEffectCtrl.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

BombEffectCtrl::BombEffectCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
}

BombEffectCtrl::~BombEffectCtrl()
{
}

void BombEffectCtrl::Start()
{
	animationRenderer = &AddComponent<SpriteAnimationRenderer>();
	animationRenderer->LoadAnimationClip(L"Resource/bomb/bombeffect.txt", L"Resource/bomb/bombeffect.png", L"effect");
	animationRenderer->SetAnimation(L"effect");
}

void BombEffectCtrl::Update()
{
	if (animationRenderer->CurrentClipEnd)
	{
		WorldManager::DelGameObject(gameObject);
	}
}

