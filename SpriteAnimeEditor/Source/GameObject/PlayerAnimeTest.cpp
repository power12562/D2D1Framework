#include "PlayerAnimeTest.h"

#include "Core/Component/Renderer/SpriteRenderer.h"
#include "Core/Component/Collider/SpriteCollider2D.h"

#include "Source/Component/PlayerAnimeTestCtrl.h"


PlayerAnimeTest::PlayerAnimeTest()
{
	AddComponent<PlayerAnimeTestCtrl>();
}

PlayerAnimeTest::~PlayerAnimeTest()
{

}
