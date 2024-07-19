#include "EditerCtrl.h"

#include <Utility/WinUtility.h>

#include <Framework/WinGameApp.h>
#include <Framework/WorldManager.h>
#include <Framework/TimeSystem.h>
#include <Framework/InputSystem.h>

#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/Collider/Base/ColliderBase.h>
#include <Core/Component/Collider/BoxCollider2D.h>

#include <Utility/Ray.h>

#include "Source/Scenes/StageEditer.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"
#include "Source/GameObject/Ground.h"

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
			if(WinUtility::ShowConfirmationDialog(L"경고", L"저장하지 않는 내용은 삭제됩니다."))
			{
				WorldManager::LoadWorld<StageEditer>();
			}	
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

		if (Input.IsKeyDown(KeyCode::G))
		{
			AddGround();
		}
	}


}

void EditerCtrl::deleteSelObject()
{
	if (selObject->tag == L"Enemy")
	{
		auto objIter = world->EnemyDino0Objs.begin();
		auto posIter = world->EnemyDino0_SpawnPos.begin();
		for (int i = 0; i < world->EnemyDino0_SpawnCount; i++)
		{
			if (world->EnemyDino0Objs[i] == selObject)
			{
				world->EnemyDino0Objs.erase(objIter);
				world->EnemyDino0_SpawnPos.erase(posIter);
				world->EnemyDino0_SpawnCount--;
				WorldManager::DelGameObject(*selObject);
				break;
			}
			++objIter;
			++posIter;
		}
	}
	else if (selObject->tag == L"Ground")
	{
		auto objIter = world->GroundObjs.begin();
		auto posIter = world->GroundBox_SpawnPos.begin();
		auto sizeIter = world->GroundBox_Size.begin();
		for (int i = 0; i < world->GroundBox_SpawnCount; i++)
		{
			if (world->GroundObjs[i] == selObject)
			{
				world->GroundObjs.erase(objIter);
				world->GroundBox_SpawnPos.erase(posIter);
				world->GroundBox_Size.erase(sizeIter);
				world->GroundBox_SpawnCount--;
				WorldManager::DelGameObject(*selObject);
				break;
			}
			++objIter;
			++posIter;
			++sizeIter;
		}
	}

	if (grabObject == selObject)
	{
		grabObject = nullptr;
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

	if (object->tag == L"Ground")
	{
		for (int i = 0; i < world->GroundBox_SpawnCount; i++)
		{
			if (world->GroundObjs[i] == object)
			{
				world->GroundBox_SpawnPos[i] = object->transform.position;
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

void EditerCtrl::AddGround()
{
	Vector2 size = WinUtility::GetVector2FromUser(WinGameApp::GetHwnd(), L"Ground Size");
	if (size.x > 0 && size.y > 0)
	{
		printf("size : %f, %f\n", size.x, size.y);

		world->GroundObjs.push_back(WorldManager::AddGameObject<Ground>(L"Ground"));
		world->GroundObjs.back()->GetComponent<BoxCollider2D>().ColliderSize = size;
		world->GroundObjs.back()->GetComponent<BoxCollider2D>().isDrawCollider = true;
		world->GroundBox_Size.push_back(size);
		world->GroundBox_SpawnCount++;
		world->GroundBox_SpawnPos.push_back(Vector2());	
	}
	else
	{
		printf("바닥 크기는 양수여야 합니다.\n");
	}
}
