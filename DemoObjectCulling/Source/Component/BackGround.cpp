#include "BackGround.h"
#include "Framework/WinGameApp.h"
#include "Framework/SceneManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/SpriteRenderer.h"
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

	gameObject.AddComponent<SpriteAnimation>();
	SpriteAnimation& midnightAnime = gameObject.GetComponent<SpriteAnimation>();
	midnightAnime.LoadAnimationClip(L"../Resource/Bg.txt", L"../Resource/midnight.png",L"Idle");
	midnightAnime.SetAnimationClip(L"Idle", true);
	gameObject.AddComponent<SpriteRenderer>().SetSpriteAnimation(midnightAnime);
	gameObject.AddComponent<BoxCollider2D>().isDrawCollider = true;

	GameObjectBase* run = SceneManager::AddGameObject(L"Test");
	run->transform.SetParent(gameObject.transform);
	run->AddComponent<SpriteAnimation>();
	SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
	runAnime.LoadAnimationClip(L"../Resource/Run.txt", L"../Resource/run.png", L"Run");
	runAnime.SetAnimationClip(L"Run", true);
	run->AddComponent<SpriteRenderer>().SetSpriteAnimation(runAnime);
	run->AddComponent<BoxCollider2D>();
	run->GetComponent<BoxCollider2D>().isDrawCollider = true;
}
