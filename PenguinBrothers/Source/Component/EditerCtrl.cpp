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
#include <Core/Component/Movement.h>

#include <Utility/Ray.h>
#include <Utility/Debug.h>

#include "Source/Component/GameManagerCtrl.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"
#include "Source/GameObject/Ground.h"
#include "Source/GameObject/Block.h"
#include "Source/Component/BlockCtrl.h"

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
	//world = (StageEditer*)WorldManager::GetCurrentWorld();
	Time.timeScale = 0.f;
	editMode = true;
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
				//SetObjectPos(grabObject);
				grabObject = nullptr;
			}
		}

		if (Input.IsKeyDown(KeyCode::F3))
		{
			if(WinUtility::ShowConfirmationDialog(L"경고", L"저장하지 않는 내용은 삭제됩니다."))
			{
				LoadWorld();
				//WorldManager::LoadWorld<StageEditer>(); 구형 로직 사용 x
			}	
		}

		if (Input.IsKeyDown(KeyCode::F4))
		{
			SaveWorld();
			//world->SaveStageToJson();	구형 로직 사용 x
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
		if (Input.IsKeyDown(KeyCode::H))
		{
			AddBlock();
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

	static std::vector<Vector2> initPos{};

	if (_enable)
	{
		//world->PosToSpawnPos();

		Time.timeScale = 0.f;
		editMode = true;

		auto pos = initPos.begin();
		for (auto& i : WorldManager::GetCurrentObjList())
		{
			if(pos != initPos.end() && 
				(i->tag == L"Player" || i->tag == L"Enemy" || i->tag == L"Ground" || i->tag == L"Block")
				)
			{
				i->enable = true;
				if (auto fsm = i->IsComponent<FiniteStateMachine>())
				{
					fsm->Transition = true;
					fsm->SetState(L"Idle");
				}
				i->transform.position = *pos;
				++pos;
			}

			if (Rigidbody2D* rb = i->IsComponent<Rigidbody2D>())
			{
				rb->enabled = false;
			}
			if (BlockCtrl* ctrl = i->IsComponent<BlockCtrl>())
			{
				ctrl->Init();
			}
		}
		GameManagerCtrl::EnemyCount = (int)WorldManager::FindGameObjectsWithTag(L"Enemy").size();

		for (auto& p : WorldManager::FindGameObjectsWithTag(L"Player"))
		{
			p->transform.SetParent();
			p->transform.scale = Vector2(4.0f, 4.0f);
			p->transform.rotation = 0;
			p->GetComponent<Movement>().enabled = true;
		}

		for (auto& b : WorldManager::FindGameObjectsWithTag(L"Block"))
		{
			b->transform.rotation = 0;
		}
	}
	else
	{
		Time.timeScale = 1.0f;
		editMode = false;

		initPos.clear();
		for (auto& i : WorldManager::GetCurrentObjList())
		{
			if (i->tag == L"Player" || i->tag == L"Enemy" || i->tag == L"Ground" || i->tag == L"Block")
			{
				initPos.push_back(i->transform.position);
			}		
			if (Rigidbody2D* rb = i->IsComponent<Rigidbody2D>())
			{
				rb->enabled = true;
			}
		}

		gameObject.Find(L"Player")->GetComponent<FiniteStateMachine>().SetState(L"Spawn");
	}
}

void EditerCtrl::deleteSelObject()
{
	if (selObject->tag == L"Enemy")
	{
		WorldManager::DelGameObject(*selObject);
		return;
	}
	else if (selObject->tag == L"Ground")
	{
		WorldManager::DelGameObject(*selObject);
		return;
	}
	else if (selObject->tag == L"Block")
	{
		WorldManager::DelGameObject(*selObject);
		return;
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
		//world->playerSpawnPos = object->transform.position + Vector2(0.f, 25.f);
	}

	if (object->tag == L"Enemy")
	{
		/*for (int i = 0; i < world->EnemyDino0_SpawnCount; i++)
		{
			if (world->EnemyDino0Objs[i] == object)
			{
				world->EnemyDino0_SpawnPos[i] = object->transform.position + Vector2(0.f, 9.f);;
			}
		}*/

	}

	if (object->tag == L"Ground")
	{
		/*for (int i = 0; i < world->GroundBox_SpawnCount; i++)
		{
			if (world->GroundObjs[i] == object)
			{
				world->GroundBox_SpawnPos[i] = object->transform.position;
			}
		}*/
	}
}

void EditerCtrl::SetDino0()
{
	int result = WinUtility::GetIntFromUser(WinGameApp::GetHwnd(), L"Dino0 Count", L"Count : ");
	if (result >= 0)
	{
		int dinoCount = -1;
		while (true)
		{
			++dinoCount;
			std::wstring dinoKey = L"dino" + std::to_wstring(dinoCount);

			if (GameObjectBase* dino = GameObjectBase::Find(dinoKey.c_str()))
			{
				if(result <= dinoCount)
					WorldManager::DelGameObject(*dino);
			}
			else if(dinoCount < result)
			{
				GameObjectBase* dino = WorldManager::AddGameObject<EnemyDino0>(L"dino0");
				dino->GetComponent<Rigidbody2D>().isKinematic = true;
			}
			else
			{
				break;
			}
		}

		//while (result != world->EnemyDino0Objs.size())
		//{
		//	if (result > world->EnemyDino0Objs.size())
		//	{
		//		GameObjectBase* dino = WorldManager::AddGameObject<EnemyDino0>(L"dino0");
		//		world->EnemyDino0Objs.push_back(dino);
		//		world->EnemyDino0_SpawnPos.push_back(Vector2(0, 0));
		//		world->EnemyDino0Objs.back()->GetComponent<Rigidbody2D>().isKinematic = true;
		//	}
		//	else
		//	{
		//		WorldManager::DelGameObject(*world->EnemyDino0Objs.back());
		//		world->EnemyDino0Objs.pop_back();
		//		world->EnemyDino0_SpawnPos.pop_back();
		//	}
		//}
		//world->EnemyDino0_SpawnCount = result;
	}
}

void EditerCtrl::AddGround()
{
	Vector2 size = WinUtility::GetVector2FromUser(WinGameApp::GetHwnd(), L"Ground Size");
	if (size.x > 0 && size.y > 0)
	{
		DEBUG_PRINT("size : %f, %f\n", size.x, size.y);

		GameObjectBase* ground = WorldManager::AddGameObject<Ground>(L"Ground");
		BoxCollider2D& coll = ground->GetComponent<BoxCollider2D>();
		coll.ColliderSize = size;
		coll.isDrawCollider = true;
		BoxRenderer& boxDraw = ground->GetComponent<BoxRenderer>();
		boxDraw.size = size;
		

		/*world->GroundObjs.push_back(WorldManager::AddGameObject<Ground>(L"Ground"));
		world->GroundObjs.back()->GetComponent<BoxCollider2D>().ColliderSize = size;
		world->GroundBox_Size.push_back(size);
		world->GroundBox_SpawnCount++;
		world->GroundBox_SpawnPos.push_back(Vector2());	

		world->GroundObjs.back()->GetComponent<BoxCollider2D>().isDrawCollider = true;
		BoxRenderer& boxDraw = world->GroundObjs.back()->GetComponent<BoxRenderer>();
		boxDraw.size = world->GroundObjs.back()->GetComponent<BoxCollider2D>().ColliderSize;*/
	}
	else
	{
		printf("바닥 크기는 양수여야 합니다.\n");
	}
}

void EditerCtrl::AddBlock()
{
	DEBUG_PRINT("Add Block!\n");
	GameObjectBase* nlock = WorldManager::AddGameObject<Block>(L"Block");
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
			//world->bgPath = bgPath.c_str();
		}
	}

}

void EditerCtrl::SaveWorld()
{
	std::wstring savePath = WinUtility::GetSaveAsFilePath(L"json");
	if (savePath != L"")
	{
		bool ok = false;
		if (std::wstring::npos == savePath.rfind(L".json"))
		{
			savePath += L".json";
		}
		if (std::filesystem::exists(savePath))
		{
			ok = WinUtility::ShowConfirmationDialog(L"경고", L"파일을 덮어쓰기 하시겠습니까?");
		}
		else
		{
			ok = true;
		}
		if (ok)
		{
			WorldManager::SaveCurrentWorldToJson(savePath.c_str());
		}	
	}
}

void EditerCtrl::LoadWorld()
{
	std::wstring loadPath = WinUtility::GetOpenFilePath(L"json");
	if (loadPath != L"")
	{
		WorldManager::LoadWorldToJson(loadPath.c_str());
	}

}