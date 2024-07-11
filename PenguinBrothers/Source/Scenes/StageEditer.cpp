#include "StageEditer.h"
#include "Framework/WorldManager.h"
#include <Framework/WinGameApp.h>
#include <Utility/WinUtility.h>
#include <Utility/FileIO.h>

#include "Core/Component/Renderer/SpriteRenderer.h"
#include <Core/Component/Renderer/TextRenderer.h>

#include "Source/GameObject/Player.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"
#include "Source/GameObject/StageObjectListDebug.h"

std::wstring StageEditer::stagePath;

StageEditer::StageEditer()
{
	LoadStageToJson();

	//JSON 파일 기반으로 물체들 생성
	WorldManager::AddGameObject<StageObjectListDebug>(L"StageObjectListDebug");
	GameObjectBase* stagePathText = WorldManager::AddGameObject<GameObjectUI>(L"stagePath");
	stagePathText->transform.localPosition += Vector2(150.f, 0.f);
	TextRenderer& textRender = stagePathText->AddComponent<TextRenderer>();
	textRender.SetFont(L"Consolas");
	textRender.Text = stagePath;
	textRender.Size = 20;

	GameObjectBase* backGround = WorldManager::AddGameObject(L"Background");
	backGround->AddComponent<SpriteRenderer>().LoadImage(bgPath.c_str());
	backGround->OderLayer = -1;

	GameObjectBase* player = WorldManager::AddGameObject<Player>(L"Player");
	player->transform.position = playerSpawnPos;

	for (unsigned int i = 0; i < EnemyDino0_SpawnCount; i++)
	{
		GameObjectBase* dino = WorldManager::AddGameObject<EnemyDino0>(L"dino0");
		dino->transform.position = EnemyDino0_SpawnPos[i];
	}


	//SaveStageToJson();
}

StageEditer::~StageEditer()
{

}

void StageEditer::LoadStageToJson()
{
	if (stagePath == L"")
	{
		stagePath = WinUtility::GetOpenFilePath(L"json");
	}

	std::string jsonStr = LoadFile::ordered_jsonLoadToFile(stagePath.c_str());
	if (jsonStr != "")
	{
		std::vector<float> points;
		ordered_json stageJson = ordered_json::parse(jsonStr);

		bgPath = stageJson["bgPath"].get<std::wstring>(); //배경 경로

		points = stageJson["playerSpawnPos"].get<std::vector<float>>();
		playerSpawnPos = Vector2{ points[0], points[1] };  //플레이어 시작 위치

		EnemyDino0_SpawnCount = stageJson["EnemyDino0_SpawnCount"]; //EnemyDino0 오브젝트 소환 개수
		EnemyDino0_SpawnPos.resize(EnemyDino0_SpawnCount);
		for (unsigned int i = 0; i < EnemyDino0_SpawnCount; i++)
		{
			std::string key("EnemyDino0_SpawnPos");
			key += std::to_string(i);
			points = stageJson[key].get<std::vector<float>>();
			EnemyDino0_SpawnPos[i] = Vector2(points[0], points[1]);
		};
	}
}

void StageEditer::SaveStageToJson()
{
	//저장 테스트
	ordered_json mapJson;
	mapJson["bgPath"] = bgPath;
	mapJson["playerSpawnPos"] = { playerSpawnPos.x, playerSpawnPos.y };
	mapJson["EnemyDino0_SpawnCount"] = EnemyDino0_SpawnCount;
	for (unsigned int i = 0; i < EnemyDino0_SpawnCount; i++)
	{
		std::string key("EnemyDino0_SpawnPos");
		key += std::to_string(i);
		mapJson[key] = { EnemyDino0_SpawnPos[i].x, EnemyDino0_SpawnPos[i].y };
	}

	std::wstring savePath = WinUtility::GetSaveAsFilePath(L"json");
	if (savePath != L"")
		SaveFlie::ordered_jsonSaveToFile(mapJson, savePath.c_str());
}
