#include "Player.h"

#include "Core/Component/SpriteRenderer.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/Collider/BoxCollider2D.h"

#include "Source/Component/PlayerCtrl.h"


Player::Player()
{
	AddComponent<SpriteAnimation>();
	SpriteAnimation& spriteAnimation = GetComponent<SpriteAnimation>();
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Idle.txt", L"Idle");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Walk.txt", L"Walk");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Attack.txt", L"Attack");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Duck.txt", L"Duck");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Jump.txt", L"Jump");
	spriteAnimation.LoadAnimationClip(L"Resource/Player/Normal/Ani/Slide.txt", L"Slide");
	spriteAnimation.SetAnimationClip(L"Idle", true);

	AddComponent<SpriteRenderer>();
	SpriteRenderer& spriteRenderer = GetComponent<SpriteRenderer>();
	spriteRenderer.LoadImage(L"Resource/Player/Normal/Normal.png");
	spriteRenderer.SetSpriteAnimation(spriteAnimation);

	BoxCollider2D& boxCollider2D = AddComponent<BoxCollider2D>();
#ifdef _DEBUG
	boxCollider2D.isDrawCollider = true;
#endif // DEBUG

	AddComponent<PlayerCtrl>();
	transform.scale = Vector2(2.0f, 2.0f);
}

Player::~Player()
{

}
