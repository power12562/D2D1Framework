#include "DemoResourceSharing.h"
#include "Framework/SceneManager.h"
#include "Framework/D2DRenderer.h"
#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"

#include "Core/GameObject/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/SpriteRenderer.h"

#include <stack>

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
	using namespace InputSystem;
	__super::Update();

	SIZE screenSize = WinGameApp::GetClientSize();
	static int instanceCount = 2;
	static std::stack<GameObjectBase*> runList;
	if (Input.IsKeyDown(KeyCode::UpArrow))
	{
		GameObjectBase* run = new GameObjectBase;
		run->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.1f * instanceCount++ };

		run->AddComponent<SpriteAnimation>();
		SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
		runAnime.LoadAnimationClip(L"Run", L"Run");
		runAnime.SetAnimationClip(L"Run", true);

		run->AddComponent<SpriteRenderer>();
		SpriteRenderer& runRenderer = run->GetComponent<SpriteRenderer>();
		runRenderer.LoadImage(L"../Resource/Run.png");
		runRenderer.SetSpriteAnimation(runAnime);

		SceneManager::AddGameObject(run);
		runList.push(run);
	}
	if (Input.IsKeyDown(KeyCode::DownArrow) && !runList.empty())
	{
		SceneManager::DelGameObject(runList.top());
		runList.pop();
		instanceCount--;
	}
}

void DemoResourceSharing::Render()
{
	__super::Render();
	static float elapsedTime = 1.f;
	static auto consolas = D2DRenderer::CreateD2DFont(L"Consolas");
	elapsedTime += TimeSystem::Time.GetDeltatime();
	static wchar_t frameRate[30]{};
	if (elapsedTime >= 0.5f)
	{
		swprintf_s(frameRate, _ARRAYSIZE(frameRate), L"fps : %.0f\nVram : %llu", TimeSystem::Time.GetFrameRate(), D2DRenderer::GetUsedVram());
		elapsedTime = 0;
	}
	D2DRenderer::DrawTextW(frameRate, consolas, { 0,0, _ARRAYSIZE(frameRate) * consolas->GetFontSize(), consolas->GetFontSize() }, D2D1::ColorF(D2D1::ColorF::AliceBlue));
}

Scene1::Scene1()
{
	SIZE screenSize = WinGameApp::GetClientSize();

	GameObjectBase* midnight = new GameObjectBase;
	midnight->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	midnight->transform().scale = Vector2(2.f, 2.f);

	midnight->AddComponent<SpriteAnimation>();
	SpriteAnimation& midnightAnime = midnight->GetComponent<SpriteAnimation>();
	midnightAnime.LoadAnimationClip(L"Bg", L"Idle");
	midnightAnime.SetAnimationClip(L"Idle", true);

	midnight->AddComponent<SpriteRenderer>();
	SpriteRenderer& midnightRenderer = midnight->GetComponent<SpriteRenderer>();
	midnightRenderer.LoadImage(L"../Resource/midnight.png");
	midnightRenderer.SetSpriteAnimation(midnightAnime);

	GameObjectBase* run = new GameObjectBase;
	run->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.1f };

	run->AddComponent<SpriteAnimation>();
	SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
	runAnime.LoadAnimationClip(L"Run", L"Run");
	runAnime.SetAnimationClip(L"Run", true);

	run->AddComponent<SpriteRenderer>();
	SpriteRenderer& runRenderer = run->GetComponent<SpriteRenderer>();
	runRenderer.LoadImage(L"../Resource/Run.png");
	runRenderer.SetSpriteAnimation(runAnime);

	SceneManager::AddGameObject(midnight);
	SceneManager::AddGameObject(run);
}

Scene1::~Scene1()
{

}
