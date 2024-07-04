#include "Run.h"
#include "Framework/WinGameApp.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/SpriteRenderer.h"
#include "Core/Component/Collider/BoxCollider2D.h"



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
	runAnime.LoadAnimation(L"../Resource/Run.txt", L"../Resource/run.png", L"Run");
	runAnime.SetAnimation(L"Run", true);
	gameObject.AddComponent<SpriteRenderer>().SetSpriteAnimation(runAnime);
	gameObject.AddComponent<BoxCollider2D>();
	gameObject.GetComponent<BoxCollider2D>().isDrawCollider = true;

	for (int i = 0; i < 10; i++)
	{
		std::wstring name = L"Run";
		name += std::to_wstring(instanceCount);
		GameObjectBase* run = WorldManager::AddGameObject(name.c_str());
		run->transform.position = Vector2{ gameObject.transform.position.x, gameObject.transform.position.y + 90.f * instanceCount++ };

		run->AddComponent<SpriteAnimation>();
		SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
		runAnime.LoadAnimation(L"../Resource/Run.txt", L"../Resource/run.png", L"Run");
		runAnime.SetAnimation(L"Run", true);
		run->AddComponent<SpriteRenderer>().SetSpriteAnimation(runAnime);
		run->AddComponent<BoxCollider2D>();
		run->GetComponent<BoxCollider2D>().isDrawCollider = true;

		runList.push_back(name.c_str());
	}
}

void Run::Update()
{
	using namespace InputSystem;
	using namespace TimeSystem;

	gameObject.transform.rotation += 30.0f * Time.GetDeltatime();
	SIZE screenSize = WinGameApp::GetClientSize();
	
	if (Input.IsKeyDown(KeyCode::UpArrow))
	{
		std::wstring name = L"Run";
		name += std::to_wstring(instanceCount);
		GameObjectBase* run = WorldManager::AddGameObject(name.c_str());
		run->transform.position = Vector2{ gameObject.transform.position.x, gameObject.transform.position.y + 90.f * instanceCount++ };

		run->AddComponent<SpriteAnimation>();
		SpriteAnimation& runAnime = run->GetComponent<SpriteAnimation>();
		runAnime.LoadAnimation(L"../Resource/Run.txt", L"../Resource/run.png", L"Run");
		runAnime.SetAnimation(L"Run", true);
		run->AddComponent<SpriteRenderer>().SetSpriteAnimation(runAnime);
		run->AddComponent<BoxCollider2D>();
		run->GetComponent<BoxCollider2D>().isDrawCollider = true;

		runList.push_back(name.c_str());
	}
	else if (Input.IsKeyDown(KeyCode::DownArrow) && !runList.empty())
	{
		WorldManager::DelGameObject(runList.back().c_str());
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

