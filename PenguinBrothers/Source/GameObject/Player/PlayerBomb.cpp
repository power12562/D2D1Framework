#include "PlayerBomb.h"
#include "Source/Component/Player/PlayerBombCtrl.h"

#include "Core/Component/Collider/SpriteCollider2D.h"
#include <Core/Component/Rigidbody2D.h>

#include <string>

int PlayerBomb::objectCount = 0;

PlayerBomb::PlayerBomb()
{
	tag = L"Bomb";

	objectCount++;

	AddComponent<Rigidbody2D>().isKinematic = true;
	AddComponent<PlayerBombCtrl>();
	AddComponent<SpriteCollider2D>().isTrigger = true;

	transform.scale = Vector2{ 4.0f, 4.0f };
	OderLayer = 1;
}

PlayerBomb::~PlayerBomb()
{
	objectCount--;
}
