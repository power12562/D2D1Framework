#include "BackGround.h"
#include "Framework/WinGameApp.h"
#include "Core/GameObject/GameObjectBase.h"
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

	gameobject.GetTransform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	gameobject.GetTransform().scale = Vector2(2.f, 2.f);

	gameobject.AddComponent<SpriteAnimation>();
	SpriteAnimation& midnightAnime = gameobject.GetComponent<SpriteAnimation>();
	midnightAnime.LoadAnimationClip(L"Bg", L"Idle");
	midnightAnime.SetAnimationClip(L"Idle", true);

	gameobject.AddComponent<SpriteRenderer>();
	SpriteRenderer& midnightRenderer = gameobject.GetComponent<SpriteRenderer>();
	midnightRenderer.LoadImage(L"../Resource/midnight.png");
	midnightRenderer.SetSpriteAnimation(midnightAnime);
}
