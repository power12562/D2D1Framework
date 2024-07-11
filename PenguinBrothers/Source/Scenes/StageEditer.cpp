#include "StageEditer.h"
#include "Framework/WorldManager.h"
#include <Utility/WinUtility.h>

#include "Core/Component/Renderer/SpriteRenderer.h"

#include "Source/GameObject/Player.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"
#include "Source/GameObject/StageObjectListDebug.h"

std::wstring StageEditer::stagePath;

StageEditer::StageEditer()
{
	if (stagePath == L"")
	{
		stagePath = WinUtility::GetOpenFilePath(L"json");
	}

	WorldManager::AddGameObject<StageObjectListDebug>(L"StageObjectListDebug");

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

}

StageEditer::~StageEditer()
{

}
