#include "PlayerBomb.h"
#include "Source/Component/PlayerBombCtrl.h"

#include <string>

int PlayerBomb::objectCount = 0;

PlayerBomb::PlayerBomb()
{
	objectCount++;
	AddComponent<PlayerBombCtrl>();
	transform.scale = Vector2{ 4.0f, 4.0f };
}

PlayerBomb::~PlayerBomb()
{
	objectCount--;
}
