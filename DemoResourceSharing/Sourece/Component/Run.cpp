#include "Run.h"
#include "Framework/WinGameApp.h"
#include "Framework/InputSystem.h"
#include "Framework/SceneManager.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/SpriteRenderer.h"

#include <list>

Run::Run(GameObjectBase& object) : ComponentBase(object)
{

}

Run::~Run()
{

}

void Run::Start()
{
	SIZE screenSize = WinGameApp::GetClientSize();

	gameobject.GetTransform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.1f };

	gameobject.AddComponent<SpriteAnimation>();
	SpriteAnimation& runAnime = gameobject.GetComponent<SpriteAnimation>();
	runAnime.LoadAnimationClip(L"Run", L"Run");
	runAnime.SetAnimationClip(L"Run", true);

	gameobject.AddComponent<SpriteRenderer>();
	SpriteRenderer& runRenderer = gameobject.GetComponent<SpriteRenderer>();
	runRenderer.LoadImage(L"../Resource/Run.png");
	runRenderer.SetSpriteAnimation(runAnime);
}

void Run::Update()
{
	using namespace InputSystem;

	SIZE screenSize = WinGameApp::GetClientSize();
	static int instanceCount = 2;
	static std::list<GameObjectBase*> runList;
	if (Input.IsKeyDown(KeyCode::UpArrow))
	{
		GameObjectBase* run = new GameObjectBase;
		run->transform.position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.1f * instanceCount++ };

		run->AddComponent<SpriteAnimation>();
		SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
		runAnime.LoadAnimationClip(L"Run", L"Run");
		runAnime.SetAnimationClip(L"Run", true);

		run->AddComponent<SpriteRenderer>();
		SpriteRenderer& runRenderer = run->GetComponent<SpriteRenderer>();
		runRenderer.LoadImage(L"../Resource/Run.png");
		runRenderer.SetSpriteAnimation(runAnime);

		SceneManager::AddGameObject(run);
		runList.push_back(run);
	}
	else if (Input.IsKeyDown(KeyCode::DownArrow) && !runList.empty())
	{
		SceneManager::DelGameObject(runList.back());
		runList.pop_back();
		instanceCount--;
	}
	if (Input.IsKeyDown(KeyCode::LeftArrow))
	{
		gameobject.transform.scale = Vector2(-1.f, 1.f);

		if (!runList.empty())
		{		
			for (auto& item : runList)
			{
				item->GetComponent<SpriteRenderer>().FlipX(true);
			}
		}
	}
	else if (Input.IsKeyDown(KeyCode::RightArrow))
	{
		gameobject.transform.scale = Vector2(1.f, 1.f);
		if (!runList.empty())
		{
			for (auto& item : runList)
			{
				item->GetComponent<SpriteRenderer>().FlipX(false);
			}
		}
	}
	if (Input.IsKeyDown(KeyCode::Space))
	{
		gameobject.GetComponent<SpriteRenderer>().FlipY();
		if (!runList.empty())
		{
			for (auto& item : runList)
			{
				item->GetComponent<SpriteRenderer>().FlipY();
			}
		}
	}
}

