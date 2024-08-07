#include "BombEffect.h"
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

#include "Source/Component/Player/BombEffectCtrl.h"

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(BombEffect)

BombEffect::BombEffect()
{
	tag = L"Attack";
	transform.scale = Vector2{ 2.5f, 2.5f };
	OderLayer = 1;

	AddComponent<BombEffectCtrl>();
}

BombEffect::~BombEffect()
{
}
