#include "DemoResourceSharing.h"
#include "Framework/SceneManager.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"

DemoResourceSharing::DemoResourceSharing()
{
#ifdef _DEBUG
	isDebug = true;
#endif // _DEBUG

}

DemoResourceSharing::~DemoResourceSharing()
{
	
}

void DemoResourceSharing::Update()
{
	__super::Update();
	size_t vram = D2DRenderer::GetUsedVram();
	printf("Vram = %llu\n", vram);
}

void DemoResourceSharing::Render()
{
	__super::Render();

}

Scene1::Scene1()
{
	SIZE screenSize = WinGameApp::GetClientSize();

	GameObjectBase* midnight = new GameObjectBase;
	midnight->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.5f };

	midnight->AddComponent<SpriteAnimation>();
	SpriteAnimation& midnightAnime = midnight->GetComponent<SpriteAnimation>();
	midnightAnime.LoadAnimationClip(L"Bg", L"Idle");
	midnightAnime.SetAnimationClip(L"Idle", true);

	midnight->AddComponent<SpriteRenderer>();
	SpriteRenderer& midnightRenderer = midnight->GetComponent<SpriteRenderer>();
	midnightRenderer.LoadImage(L"../Resource/midnight.png");
	midnightRenderer.SetSpriteAnimation(midnightAnime);

	GameObjectBase* run = new GameObjectBase;
	run->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	run->AddComponent<SpriteAnimation>();
	SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
	runAnime.LoadAnimationClip(L"Run", L"Run");
	runAnime.SetAnimationClip(L"Run", true);

	gameObjectList.push_back(midnight);
	gameObjectList.push_back(run); 
}

Scene1::~Scene1()
{

}
