#include "Stage1.h"
#include "Framework/WorldManager.h"
#include "Core/Component/Renderer/SpriteRenderer.h"

#include "Source/GameObject/Player.h"

Stage1::Stage1()
{
	bgPath = L"Resource/Stage/1.png";
	GameObjectBase* backGround = WorldManager::AddGameObject(L"Background");
	backGround->AddComponent<SpriteRenderer>().LoadImage(bgPath.c_str());

	WorldManager::AddGameObject<Player>(L"Player");
}

Stage1::~Stage1()
{

}
