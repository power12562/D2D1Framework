#include "EditerCtrl.h"

#include <Utility/WinUtility.h>

#include <Framework/WinGameApp.h>
#include <Framework/WorldManager.h>
#include <Framework/TimeSystem.h>
#include <Framework/InputSystem.h>

#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/Collider/Base/ColliderBase.h>

#include <Utility/Ray.h>

#include "Source/Scenes/StageEditer.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"

using namespace InputSystem;
using namespace TimeSystem;
EditerCtrl::EditerCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject) 
{

}


EditerCtrl::~EditerCtrl()
{

}

void EditerCtrl::Start()
{
	TimeSystem::Time.timeScale = 0.f;
	world = (StageEditer*)WorldManager::GetCurrentWorld();
	gameObject.Find(L"Player")->GetComponent<FiniteStateMachine>().SetState(L"Idle");
}


void EditerCtrl::Update()
{
	if (Input.IsKeyDown(KeyCode::Space))
	{
		if (Time.timeScale == 0.f)
		{
			Time.timeScale = 1.0f;
			gameObject.Find(L"Player")->GetComponent<FiniteStateMachine>().SetState(L"Spawn");
			editMode = false;
		}
		else
		{
			world->PosToSpawnPos();
			Time.timeScale = 0.f;
			editMode = true;
		}
	}

	if (editMode)
	{
		auto& mouse = Input.GetMouseState();
		if (mouse.isLeftClickDown)
		{
			if (ColliderBase* collision = Ray::ShootRayFromPosition(mouse.GetWorldPos()))
			{
				grabObject = &collision->gameObject;
				selObject = grabObject;
			}
		}
		if (grabObject)
		{
			grabObject->transform.position = mouse.GetWorldPos();
			if (mouse.isLeftClickUp)
			{
				SetObjectPos(grabObject);
				grabObject = nullptr;
			}
		}

		if (Input.IsKeyDown(KeyCode::F3))
		{
			WorldManager::LoadWorld<StageEditer>();
		}

		if (Input.IsKeyDown(KeyCode::F4))
		{
			world->SaveStageToJson();
		}

		if (Input.IsKeyDown(KeyCode::Num1))
		{
			SetDino0();
		}

		if (selObject && Input.IsKeyDown(KeyCode::Delete))
		{
			deleteSelObject();
		}
	}


}

void EditerCtrl::deleteSelObject()
{
	if (selObject->tag == L"Enemy")
	{
		auto posIter = world->EnemyDino0_SpawnPos.begin();
		for (int i = 0; i < world->EnemyDino0_SpawnCount; i++)
		{
			if (world->EnemyDino0Objs[i] == selObject)
			{
				world->EnemyDino0_SpawnPos.erase(posIter);
				world->EnemyDino0_SpawnCount--;
				WorldManager::DelGameObject(*selObject);
				break;
			}
			++posIter;
		}
	}
	selObject = nullptr;
}

void EditerCtrl::SetObjectPos(GameObjectBase* object)
{
	if (object->tag == L"Player")
	{
		world->playerSpawnPos = object->transform.position + Vector2(0.f, 25.f);
	}

	if (object->tag == L"Enemy")
	{
		for (int i = 0; i < world->EnemyDino0_SpawnCount; i++)
		{
			if (world->EnemyDino0Objs[i] == object)
			{
				world->EnemyDino0_SpawnPos[i] = object->transform.position + Vector2(0.f, 9.f);;
			}
		}

	}
}

void EditerCtrl::SetDino0()
{
	int result = WinUtility::GetIntFromUser(WinGameApp::GetHwnd(), L"Dino0 Count", L"Count : ");
	if (result >= 0)
	{
		while (result != world->EnemyDino0Objs.size())
		{
			if (result > world->EnemyDino0Objs.size())
			{
				GameObjectBase* dino = WorldManager::AddGameObject<EnemyDino0>(L"dino0");
				world->EnemyDino0Objs.push_back(dino);
				world->EnemyDino0_SpawnPos.push_back(Vector2(0, 0));
			}
			else
			{
				WorldManager::DelGameObject(*world->EnemyDino0Objs.back());
				world->EnemyDino0Objs.pop_back();
				world->EnemyDino0_SpawnPos.pop_back();
			}
		}
		world->EnemyDino0_SpawnCount = result;
	}
}
