#include "FireEffect.h"
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>
#include <Core/Component/Rigidbody2D.h>
#include <Core/Component/Collider/SpriteCollider2D.h>

#include "Source/Component/Player/FireEffectCtrl.h"
#include "Source/Component/Player/PlayerCtrl.h"


FireEffect::FireEffect()
{
	transform.scale = Vector2(4.3f, 4.3f);
	tag = L"Attack";

	AddComponent<SpriteAnimationRenderer>();
	AddComponent<FireEffectCtrl>();

	switch (bombType)
	{
	case BombType::blue:

		break;
	case BombType::red:

		break;
	case BombType::green:

		break;
	case BombType::skyblue:

		break;
	}
	AddComponent<SpriteCollider2D>().isTrigger = true;
}

FireEffect::~FireEffect()
{
}

