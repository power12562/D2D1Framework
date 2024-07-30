#include "PlayerBomb.h"
#include "Source/Component/Player/PlayerBombCtrl.h"

#include "Core/Component/Collider/SpriteCollider2D.h"
#include <Core/Component/Rigidbody2D.h>				

#include <string>

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(PlayerBomb)


int PlayerBomb::objectCount = 0;

PlayerBomb::PlayerBomb()
{
	tag = L"Bomb";

	objectCount++;

	AddComponent<Rigidbody2D>().isKinematic = false;
	AddComponent<PlayerBombCtrl>();
	SpriteCollider2D& coll = AddComponent<SpriteCollider2D>();
	coll.ExceptionTag.push_back(L"Player");
	coll.ExceptionTag.push_back(L"Enemy");

	transform.scale = Vector2{ 4.0f, 4.0f };
	OderLayer = 1;
}

PlayerBomb::~PlayerBomb()
{
	objectCount--;
}
