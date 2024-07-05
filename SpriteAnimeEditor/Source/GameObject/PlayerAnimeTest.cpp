#include "PlayerAnimeTest.h"

#include "Core/Component/SpriteRenderer.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/Collider/BoxCollider2D.h"

#include "Source/Component/PlayerAnimeTestCtrl.h"


PlayerAnimeTest::PlayerAnimeTest()
{
	AddComponent<SpriteAnimation>();
	SpriteAnimation& spriteAnimation = GetComponent<SpriteAnimation>();


	AddComponent<SpriteRenderer>().SetSpriteAnimation(spriteAnimation);
	BoxCollider2D& boxCollider2D = AddComponent<BoxCollider2D>();
	boxCollider2D.isDrawCollider = true;

	AddComponent<PlayerAnimeTestCtrl>();
}

PlayerAnimeTest::~PlayerAnimeTest()
{

}
