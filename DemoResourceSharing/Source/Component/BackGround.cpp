#include "BackGround.h"
#include "Framework/WinGameApp.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/SpriteRenderer.h"

BackGround::BackGround(GameObjectBase& object) : ComponentBase(object)
{

}

BackGround::~BackGround()
{

}

void BackGround::Start()
{
	SIZE screenSize = WinGameApp::GetClientSize();
	gameObject.GetTransform().scale = Vector2(2.f, 2.f);

	gameObject.AddComponent<SpriteAnimation>();
	SpriteAnimation& midnightAnime = gameObject.GetComponent<SpriteAnimation>();
	midnightAnime.LoadAnimationClip(L"../Resource/Bg.txt", L"Idle");
	midnightAnime.SetAnimationClip(L"Idle", true);

	gameObject.AddComponent<SpriteRenderer>();
	SpriteRenderer& midnightRenderer = gameObject.GetComponent<SpriteRenderer>();
	midnightRenderer.LoadImage(L"../Resource/midnight.png");
	midnightRenderer.SetSpriteAnimation(midnightAnime);
}
