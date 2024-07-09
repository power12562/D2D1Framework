#include "EnemyDino0Attack.h"

#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

#include "Source/Component/EnemyDino0AttackCtrl.h"

EnemyDino0Attack::EnemyDino0Attack()
{
	transform.scale = Vector2(2.0f, 2.0f);

	AddComponent<EnemyDino0AttackCtrl>();

	SpriteAnimationRenderer& animationRenderer = AddComponent<SpriteAnimationRenderer>();
	animationRenderer.LoadAnimation(L"Resource/Enemy/Dino0/Fire.txt", L"Resource/Enemy/Dino0/EnemyDino0.png", L"Fire");
	animationRenderer.SetAnimation(L"Fire");
}

EnemyDino0Attack::~EnemyDino0Attack()
{
}
