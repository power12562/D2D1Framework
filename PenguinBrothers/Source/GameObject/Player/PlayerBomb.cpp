#include "PlayerBomb.h"
#include "Source/Component/Player/PlayerBombCtrl.h"

#include "Core/Component/Collider/BoxCollider2D.h"

#include <string>

int PlayerBomb::objectCount = 0;

PlayerBomb::PlayerBomb()
{
	tag = L"Bomb";

	objectCount++;
	AddComponent<PlayerBombCtrl>();
	AddComponent<BoxCollider2D>();

	transform.scale = Vector2{ 4.0f, 4.0f };
	OderLayer = 1;
}

PlayerBomb::~PlayerBomb()
{
	objectCount--;
}
