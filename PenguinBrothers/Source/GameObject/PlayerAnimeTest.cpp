#include "PlayerAnimeTest.h"

#include "Core/Component/SpriteRenderer.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/Collider/BoxCollider2D.h"

#include "Source/Component/PlayerAnimeTestCtrl.h"


PlayerAnimeTest::PlayerAnimeTest()
{
	AddComponent<SpriteAnimation>();
	SpriteAnimation& spriteAnimation = GetComponent<SpriteAnimation>();
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Idle.txt", L"Resource/Player/Normal/Normal.png", L"Idle");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Walk.txt", L"Resource/Player/Normal/Normal.png", L"Walk");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Attack.txt", L"Resource/Player/Normal/Normal.png", L"Attack");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Duck.txt", L"Resource/Player/Normal/Normal.png", L"Duck");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Jump.txt", L"Resource/Player/Normal/Normal.png", L"Jump");
	spriteAnimation.LoadAnimation(L"Resource/Player/Normal/Ani/Slide.txt", L"Resource/Player/Normal/Normal.png", L"Slide");
	spriteAnimation.SetAnimation(L"Idle", true);

	AddComponent<SpriteRenderer>().SetSpriteAnimation(spriteAnimation);
	BoxCollider2D& boxCollider2D = AddComponent<BoxCollider2D>();
#ifdef _DEBUG
	boxCollider2D.isDrawCollider = true;
#endif // DEBUG

	AddComponent<PlayerAnimeTestCtrl>();
}

PlayerAnimeTest::~PlayerAnimeTest()
{

}
