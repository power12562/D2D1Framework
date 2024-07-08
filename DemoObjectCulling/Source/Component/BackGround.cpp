#include "BackGround.h"
#include "Framework/WinGameApp.h"
#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/BoxCollider2D.h"

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

	gameObject.AddComponent<SpriteAnimationRenderer>();
	SpriteAnimationRenderer& midnightAnime = gameObject.GetComponent<SpriteAnimationRenderer>();
	midnightAnime.LoadAnimation(L"../Resource/Bg.txt", L"../Resource/midnight.png",L"Idle");
	midnightAnime.SetAnimation(L"Idle", true);
	gameObject.AddComponent<BoxCollider2D>().isDrawCollider = true;

	GameObjectBase* run = WorldManager::AddGameObject(L"Test");
	run->transform.SetParent(gameObject.transform);
	run->AddComponent<SpriteAnimationRenderer>();
	SpriteAnimationRenderer& runAnime = run->GetComponent<SpriteAnimationRenderer>();
	runAnime.LoadAnimation(L"../Resource/Run.txt", L"../Resource/run.png", L"Run");
	runAnime.SetAnimation(L"Run", true);
	run->AddComponent<BoxCollider2D>();
	run->GetComponent<BoxCollider2D>().isDrawCollider = true;
}
