#include "EditerCtrl.h"
#include <Framework/WorldManager.h>
#include <Framework/TimeSystem.h>
#include <Framework/InputSystem.h>

#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/Collider/Base/ColliderBase.h>

#include <Utility/Ray.h>

#include "Source/Scenes/StageEditer.h"

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

		if (Input.IsKeyDown(KeyCode::F4))
		{
			world->SaveStageToJson();
		}
	}


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
