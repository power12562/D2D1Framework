#include "StageEditer.h"
#include "Framework/WorldManager.h"
#include <Framework/WinGameApp.h>
#include <Utility/WinUtility.h>
#include <Utility/JsonUtility.h>

#include <Core/Component/FSM/FiniteStateMachine.h>
#include "Core/Component/Renderer/SpriteRenderer.h"
#include <Core/Component/Renderer/TextRenderer.h>
#include <Core/Component/Rigidbody2D.h>

#include "Source/GameObject/Player/Player.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"
#include "Source/GameObject/StageObjectListDebug.h"	   
#include "Source/GameObject/Editer.h"
#include "Source/GameObject/Ground.h"

#include <Core/Component/Collider/BoxCollider2D.h>

StageEditer::StageEditer()
{
	LoadStageToJson();
	SpawnSceneObjects(); //JSON 파일 기반으로 물체들 생성
	SpawnEditerObj();


}

StageEditer::StageEditer(const wchar_t* _stagePath)
{
	stagePath = _stagePath;
	LoadStageToJson();
	SpawnSceneObjects(); //JSON 파일 기반으로 물체들 생성
	//SpawnEditerObj();

}

StageEditer::~StageEditer()
{

}

void StageEditer::LoadStageToJson()
{
	try
	{
		if (stagePath == L"")
		{
			stagePath = WinUtility::GetOpenFilePath(L"json");
		}

		std::string jsonStr = JsonUtiliy::ordered_jsonLoadToFile(stagePath.c_str());
		if (jsonStr != "")
		{
			std::vector<float> points;
			ordered_json stageJson = ordered_json::parse(jsonStr);

			bgPath = stageJson["bgPath"].get<std::wstring>(); //배경 경로

			playerSpawnPos = JsonUtiliy::JsonGetVector2(stageJson["playerSpawnPos"]);

			EnemyDino0_SpawnCount = stageJson["EnemyDino0_SpawnCount"]; //EnemyDino0 오브젝트 소환 개수
			EnemyDino0_SpawnPos.resize(EnemyDino0_SpawnCount);
			for (int i = 0; i < EnemyDino0_SpawnCount; i++)
			{
				std::string key("EnemyDino0_SpawnPos");
				key += std::to_string(i);
				EnemyDino0_SpawnPos[i] = JsonUtiliy::JsonGetVector2(stageJson[key]);
			};
			GroundBox_SpawnCount = stageJson["GroundBox_SpawnCount"];
			GroundBox_SpawnPos.resize(GroundBox_SpawnCount);
			for (int i = 0; i < GroundBox_SpawnCount; i++)
			{
				std::string key("GroundBox_SpawnPos");
				key += std::to_string(i);
				GroundBox_SpawnPos[i] = JsonUtiliy::JsonGetVector2(stageJson[key]);
			};
			GroundBox_Size.resize(GroundBox_SpawnCount);
			for (int i = 0; i < GroundBox_SpawnCount; i++)
			{
				std::string key("GroundBox_Size");
				key += std::to_string(i);
				GroundBox_Size[i] = JsonUtiliy::JsonGetVector2(stageJson[key]);
			};
		}
	}
	catch (detail::type_error& exc)
	{
		printf("%s\n", exc.what());
	}
}

void StageEditer::SpawnSceneObjects()
{
	GameObjectBase* backGround = WorldManager::AddGameObject(L"Background");
	backGround->AddComponent<SpriteRenderer>().LoadImage(bgPath.c_str());
	backGround->OderLayer = -1;

	playerObj = WorldManager::AddGameObject<Player>(L"Player");
	playerObj->transform.position = playerSpawnPos;

	for (int i = 0; i < GroundBox_SpawnCount; i++)
	{
		GroundObjs.push_back(WorldManager::AddGameObject<Ground>(L"Ground"));
		GroundObjs[i]->transform.position = GroundBox_SpawnPos[i];
		GroundObjs[i]->GetComponent<BoxCollider2D>().ColliderSize = GroundBox_Size[i];

		GroundObjs[i]->GetComponent<BoxCollider2D>().isDrawCollider = true;
	}

	for (int i = 0; i < EnemyDino0_SpawnCount; i++)
	{
		EnemyDino0Objs.push_back(WorldManager::AddGameObject<EnemyDino0>(L"dino0"));
		EnemyDino0Objs[i]->transform.position = EnemyDino0_SpawnPos[i];
		
	}
}

void StageEditer::PosToSpawnPos()
{
	WorldManager::DelGameObject(L"Player");
	playerObj = WorldManager::AddGameObject<Player>(L"Player");
	playerObj->transform.position = playerSpawnPos;
	playerObj->GetComponent<Rigidbody2D>().isKinematic = true;
	playerObj->GetComponent<FiniteStateMachine>().SetState(L"Idle");
	for (int i = 0; i < EnemyDino0Objs.size(); i++)
	{
		EnemyDino0Objs[i]->transform.position = EnemyDino0_SpawnPos[i];
		EnemyDino0Objs[i]->Start();
		EnemyDino0Objs[i]->enable = true;
	}
}

void StageEditer::SaveStageToJson()
{
	//저장 테스트
	ordered_json mapJson;
	mapJson["bgPath"] = bgPath;
	mapJson["playerSpawnPos"] = { playerSpawnPos.x, playerSpawnPos.y };
	mapJson["EnemyDino0_SpawnCount"] = EnemyDino0_SpawnCount;
	for (int i = 0; i < EnemyDino0_SpawnCount; i++)
	{
		std::string key("EnemyDino0_SpawnPos");
		key += std::to_string(i);
		mapJson[key] = { EnemyDino0_SpawnPos[i].x, EnemyDino0_SpawnPos[i].y };
	}

	mapJson["GroundBox_SpawnCount"] = GroundBox_SpawnCount;
	for (int i = 0; i < GroundBox_SpawnCount; i++)
	{
		std::string key("GroundBox_SpawnPos");
		key += std::to_string(i);
		mapJson[key] = { GroundBox_SpawnPos[i].x, GroundBox_SpawnPos[i].y };
	};
	for (int i = 0; i < GroundBox_SpawnCount; i++)
	{
		std::string key("GroundBox_Size");
		key += std::to_string(i);
		mapJson[key] = { GroundBox_Size[i].x, GroundBox_Size[i].y };
	};






	std::wstring savePath = WinUtility::GetSaveAsFilePath(L"json");
	if (savePath != L"")
		JsonUtiliy::ordered_jsonSaveToFile(mapJson, savePath.c_str());
}

void StageEditer::SpawnEditerObj()
{
	WorldManager::AddGameObject<StageObjectListDebug>(L"StageObjectListDebug");
	GameObjectBase* stagePathText = WorldManager::AddGameObject<GameObjectUI>(L"stagePath");
	stagePathText->transform.localPosition += Vector2(150.f, 0.f);
	TextRenderer& textRender = stagePathText->AddComponent<TextRenderer>();
	textRender.SetFont(L"Consolas");
	textRender.Text = stagePath;
	textRender.Size = 20;

	WorldManager::AddGameObject<Editer>(L"editer");
}
