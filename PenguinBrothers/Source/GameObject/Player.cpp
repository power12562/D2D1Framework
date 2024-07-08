#include "Player.h"

#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/BoxCollider2D.h"

#include "Source/Component/PlayerCtrl.h"


Player::Player()
{
	AddComponent<SpriteAnimationRenderer>();
	SpriteAnimationRenderer& spriteAnimation = GetComponent<SpriteAnimationRenderer>();
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Idle.txt", L"Resource/Player/Normal/Normal.png", L"Idle");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Walk.txt", L"Resource/Player/Normal/Normal.png", L"Walk");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Attack.txt", L"Resource/Player/Normal/Normal.png", L"Attack");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Duck.txt", L"Resource/Player/Normal/Normal.png", L"Duck");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Jump.txt", L"Resource/Player/Normal/Normal.png", L"Jump");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Slide.txt", L"Resource/Player/Normal/Normal.png", L"Slide");
	spriteAnimation.LoadAnimation(L"Resource/Player/Spawn/Spawn.txt", L"Resource/Player/Spawn/Spawn.png", L"Spawn");
	spriteAnimation.LoadAnimation(L"Resource/Player/Dead/Dead.txt", L"Resource/Player/Dead/Dead.png", L"Dead");

	BoxCollider2D& boxCollider2D = AddComponent<BoxCollider2D>();
#ifdef _DEBUG
	boxCollider2D.isDrawCollider = true;
#endif // DEBUG

	AddComponent<PlayerCtrl>();
	transform.scale = Vector2(4.0f, 4.0f);
}

Player::~Player()
{

}
