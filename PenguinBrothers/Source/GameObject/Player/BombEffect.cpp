#include "BombEffect.h"
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

#include "Source/Component/Player/BombEffectCtrl.h"

BombEffect::BombEffect()
{
	transform.scale = Vector2{ 4.0f, 4.0f };

	SpriteAnimationRenderer& animationRenderer = AddComponent<SpriteAnimationRenderer>();
	animationRenderer.LoadAnimationClip(L"Resource/bomb/bombeffect.txt", L"Resource/bomb/bombeffect.png", L"effect");
	animationRenderer.SetAnimation(L"effect");

	AddComponent<BombEffectCtrl>();
}

BombEffect::~BombEffect()
{
}
