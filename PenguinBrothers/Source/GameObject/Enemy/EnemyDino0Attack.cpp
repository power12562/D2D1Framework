#include "EnemyDino0Attack.h"

#include <Core/Component/Renderer/SpriteAnimationRenderer.h>
#include <Core/Component/Collider/SpriteCollider2D.h>

#include "Source/Component/Enemy/EnemyDino0AttackCtrl.h"

EnemyDino0Attack::EnemyDino0Attack()
{
	tag = L"Attack";
	transform.scale = Vector2(2.0f, 2.0f);

	AddComponent<EnemyDino0AttackCtrl>();

	SpriteAnimationRenderer& animationRenderer = AddComponent<SpriteAnimationRenderer>();
	animationRenderer.LoadAnimationClip(L"Resource/Enemy/Dino0/Fire.txt", L"Resource/Enemy/Dino0/EnemyDino0.png", L"Fire");
	animationRenderer.SetAnimation(L"Fire");

	SpriteCollider2D& coll = AddComponent<SpriteCollider2D>();
	coll.isDrawCollider = true;
	coll.isTrigger = true;
}

EnemyDino0Attack::~EnemyDino0Attack()
{
}
