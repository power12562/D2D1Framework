#include "EditerCtrl.h"

#include <Utility/WinUtility.h>

#include <Framework/WinGameApp.h>
#include <Framework/WorldManager.h>
#include <Framework/TimeSystem.h>
#include <Framework/InputSystem.h>

#include <Core/Component/Renderer/SpriteRenderer.h>
#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/Collider/Base/ColliderBase.h>
#include <Core/Component/Collider/BoxCollider2D.h>
#include <Core/Component/Rigidbody2D.h>
#include <Core/Component/Renderer/BoxRenderer.h>

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
	world = (StageEditer*)WorldManager::GetCurrentWorld();
	EnableEditMode(true);
}


void EditerCtrl::Update()
{
	if (Input.IsKeyDown(KeyCode::Space))
	{
		EnableEditMode(!editMode);
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


		if (Input.IsKeyDown(KeyCode::B))
		{
			SelectBackgroundPath();
		}
	}


}

void EditerCtrl::EnableEditMode(bool _enable)
{
	if (grabObject != nullptr)
		return;

	if (_enable)
	{
		world->PosToSpawnPos();
		Time.timeScale = 0.f;
		editMode = true;
		for (auto& i : WorldManager::GetCurrentObjList())
		{
			if (Rigidbody2D* rb = i->IsComponent<Rigidbody2D>())
			{
				rb->isKinematic = true;
			}
		}
	}
	else
	{
		Time.timeScale = 1.0f;
		gameObject.Find(L"Player")->GetComponent<FiniteStateMachine>().SetState(L"Spawn");
		editMode = false;
		for (auto& i : WorldManager::GetCurrentObjList())
		{
			if (Rigidbody2D* rb = i->IsComponent<Rigidbody2D>())
			{
				rb->isKinematic = false;
			}
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
		world->GroundBox_Size.push_back(size);
		world->GroundBox_SpawnCount++;
		world->GroundBox_SpawnPos.push_back(Vector2());	

		world->GroundObjs.back()->GetComponent<BoxCollider2D>().isDrawCollider = true;
		world->GroundObjs.back()->GetComponent<BoxCollider2D>().isDrawCollider = true;
		BoxRenderer& boxDraw = world->GroundObjs.back()->GetComponent<BoxRenderer>();
		boxDraw.size = world->GroundObjs.back()->GetComponent<BoxCollider2D>().ColliderSize;
	}
	else
	{
		printf("바닥 크기는 양수여야 합니다.\n");
	}
}


void EditerCtrl::SelectBackgroundPath()
{
	std::wstring bgPath =  WinUtility::GetOpenFilePath(L"png");
	if (L"" != bgPath)
	{
		GameObjectBase* bg = gameObject.Find(L"Background");
		if (bg)
		{
			std::wstring::size_type f = bgPath.find(L"Resource");
			if (f == std::wstring::npos)
			{
				WinUtility::ShowConfirmationDialog(L"오류", L"올바른 리소스 경로가 아닙니다.");
				return;
			}
			bgPath = bgPath.substr(f, bgPath.size());
			bg->GetComponent<SpriteRenderer>().LoadImage(bgPath.c_str());
			world->bgPath = bgPath.c_str();
		}
	}

}
