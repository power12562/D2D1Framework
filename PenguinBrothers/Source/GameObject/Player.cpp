#include "Player.h"
#include "Core/Component/SpriteRenderer.h"
#include "Source/Component/PlayerMove.h"

Player::Player()
{
	AddComponent<SpriteRenderer>();
	GetComponent<SpriteRenderer>().LoadImage(L"Resource/Player/Normal/Idle/0.bmp");

	AddComponent <PlayerMove>();

	transform.scale = Vector2(5.0f, 5.0f);
}

Player::~Player()
{

}
