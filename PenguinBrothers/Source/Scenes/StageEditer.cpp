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
	if (stagePath == L"")
	{
		stagePath = WinUtility::GetSaveAsFilePath(L"json");
	}

	//나중에 JSON으로 초기화할 값들
	bgPath = L"Resource/Stage/1.png";
	playerSpawnPos = Vector2(-500.f, -195.f);
	EnemyDino0_SpawnCount = 3;
	EnemyDino0_SpawnPos.reserve(EnemyDino0_SpawnCount);
	EnemyDino0_SpawnPos = {
		Vector2{0.f, -195.f},
		Vector2{500.f, -195.f},
		Vector2{250.f, -195.f},
	};

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


	//저장 테스트
	ordered_json mapJson;
	mapJson["bgPath"] = bgPath;
	mapJson["playerSpawnPos"] = { playerSpawnPos.x, playerSpawnPos.y };
	mapJson["EnemyDino0_SpawnCount"] = EnemyDino0_SpawnCount;
	for (int i = 0; i < EnemyDino0_SpawnCount; i++)
	{
		std::string key("EnemyDino0_SpawnPos");
		key += std::to_string(i);
		mapJson[key] ={ EnemyDino0_SpawnPos[i].x, EnemyDino0_SpawnPos[i].y};
	}	

	if(stagePath != L"")
		SaveFlie::ordered_jsonSaveToFile(mapJson, stagePath.c_str());
}

StageEditer::~StageEditer()
{

}
