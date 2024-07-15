#include "BombEffect.h"
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

#include "Source/Component/Player/BombEffectCtrl.h"

BombEffect::BombEffect()
{
	tag = L"Attack";
	transform.scale = Vector2{ 4.0f, 4.0f };
	OderLayer = 1;

	AddComponent<BombEffectCtrl>();
}

BombEffect::~BombEffect()
{
}
