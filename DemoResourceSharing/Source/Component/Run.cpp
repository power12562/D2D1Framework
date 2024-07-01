#include "Run.h"
#include "Framework/WinGameApp.h"
#include "Framework/InputSystem.h"
#include "Framework/SceneManager.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/SpriteRenderer.h"

#include <list>
#include <string>

Run::Run(GameObjectBase& object) : ComponentBase(object)
{

}

Run::~Run()
{

}

void Run::Start()
{
	SIZE screenSize = WinGameApp::GetClientSize();

	gameObject.transform.position = Vector2{ 0.f, -screenSize.cy * 0.45f};
	gameObject.AddComponent<SpriteAnimation>();
	SpriteAnimation& runAnime = gameObject.GetComponent<SpriteAnimation>();
	runAnime.LoadAnimationClip(L"../Resource/Run.txt", L"Run");
	runAnime.SetAnimationClip(L"Run", true);

	gameObject.AddComponent<SpriteRenderer>();
	SpriteRenderer& runRenderer = gameObject.GetComponent<SpriteRenderer>();
	runRenderer.LoadImage(L"../Resource/Run.png");
	runRenderer.SetSpriteAnimation(runAnime);
}

void Run::Update()
{
	using namespace InputSystem;

	SIZE screenSize = WinGameApp::GetClientSize();
	static int instanceCount = 1;
	static std::list<std::wstring> runList;
	if (Input.IsKeyDown(KeyCode::UpArrow))
	{
		std::wstring name = L"Run";
		name += std::to_wstring(instanceCount);
		GameObjectBase* run = SceneManager::AddGameObject(name.c_str());
		run->transform.position = Vector2{ gameObject.transform.position.x, gameObject.transform.position.y + 90.f * instanceCount++ };

		run->AddComponent<SpriteAnimation>();
		SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
		runAnime.LoadAnimationClip(L"../Resource/Run.txt", L"Run");
		runAnime.SetAnimationClip(L"Run", true);

		run->AddComponent<SpriteRenderer>();
		SpriteRenderer& runRenderer = run->GetComponent<SpriteRenderer>();
		runRenderer.LoadImage(L"../Resource/Run.png");
		runRenderer.SetSpriteAnimation(runAnime);
		runList.push_back(name.c_str());
	}
	else if (Input.IsKeyDown(KeyCode::DownArrow) && !runList.empty())
	{
		SceneManager::DelGameObject(runList.back().c_str());
		runList.pop_back();
		instanceCount--;
	}
	if (Input.IsKeyDown(KeyCode::LeftArrow))
	{
		gameObject.transform.scale = Vector2(-1.f, 1.f);

		if (!runList.empty())
		{		
			for (auto& item : runList)
			{
				GameObjectBase::Find(item.c_str())->transform.FlipX(true);
			}
		}
	}
	else if (Input.IsKeyDown(KeyCode::RightArrow))
	{
		gameObject.transform.scale = Vector2(1.f, 1.f);
		if (!runList.empty())
		{
			for (auto& item : runList)
			{
				GameObjectBase::Find(item.c_str())->transform.FlipX(false);
			}
		}
	}
	if (Input.IsKeyDown(KeyCode::Space))
	{
		gameObject.transform.FlipY();
		if (!runList.empty())
		{
			for (auto& item : runList)
			{
				GameObjectBase::Find(item.c_str())->transform.FlipY();
			}
		}
	}

}

