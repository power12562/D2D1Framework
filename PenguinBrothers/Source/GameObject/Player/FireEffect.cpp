#include "FireEffect.h"
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>
#include <Core/Component/Collider/BoxCollider2D.h>

#include "Source/Component/Player/FireEffectCtrl.h"
#include "Source/Component/Player/PlayerCtrl.h"

FireEffect::FireEffect()
{
	transform.scale = Vector2(4.3f, 4.3f);

	AddComponent<SpriteAnimationRenderer>();
	AddComponent<FireEffectCtrl>();
	AddComponent<BoxCollider2D>();
}

FireEffect::~FireEffect()
{
}

