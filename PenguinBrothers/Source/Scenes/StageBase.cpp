#include "StageBase.h"
#include "Framework/WorldManager.h"
#include "Core/Component/Renderer/SpriteRenderer.h"

#include "Source/GameObject/Player.h"
#include "Source/GameObject/EnemyDino0.h"

StageBase::StageBase()
{
	//나중에 JSON으로 초기화할 값들
	bgPath = L"Resource/Stage/1.png";
	playerSpawnPos = Vector2(-500.f, -195.f);
	EnemyDino0_SpawnCount = 2;
	EnemyDino0_SpawnPos.resize(EnemyDino0_SpawnCount);
	EnemyDino0_SpawnPos = { 
		Vector2{0.f, -195.f},
		Vector2{500.f, -195.f} 
	};


	//JSON 파일 기반으로 물체들 생성
	GameObjectBase* backGround = WorldManager::AddGameObject(L"Background");
	backGround->AddComponent<SpriteRenderer>().LoadImage(bgPath.c_str());
	backGround->OderLayer = -1;

	GameObjectBase* player = WorldManager::AddGameObject<Player>(L"Player");
	player->transform.position = playerSpawnPos;

	for (int i = 0; i < EnemyDino0_SpawnCount; i++)
	{
		wchar_t dinoNum[11]{};
		swprintf_s(dinoNum, _ARRAYSIZE(dinoNum), L"dino0_%d", i);
		GameObjectBase* dino = WorldManager::AddGameObject<EnemyDino0>(dinoNum);
		dino->transform.position = EnemyDino0_SpawnPos[i];
	}
	

}

StageBase::~StageBase()
{

}
