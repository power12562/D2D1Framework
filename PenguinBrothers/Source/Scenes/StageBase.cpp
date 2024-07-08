#include "StageBase.h"
#include "Framework/WorldManager.h"
#include "Core/Component/Renderer/SpriteRenderer.h"

#include "Source/GameObject/Player.h"

StageBase::StageBase()
{
	bgPath = L"Resource/Stage/1.png";
	playerSpawnPos = Vector2(-500.f, -195.f);

	GameObjectBase* backGround = WorldManager::AddGameObject(L"Background");
	backGround->AddComponent<SpriteRenderer>().LoadImage(bgPath.c_str());
	backGround->OderLayer = -1;


	GameObjectBase* player = WorldManager::AddGameObject<Player>(L"Player");
	player->transform.position = playerSpawnPos;
}

StageBase::~StageBase()
{

}
