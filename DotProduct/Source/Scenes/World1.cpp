#include "World1.h"
#include <Framework/WorldManager.h>
#include <Core/GameObject/MainCamera.h>

#include "Source/GameObject/DotPlayer.h"

//���ϴ� ������Ʈ���� �߰��մϴ�.
World1::World1()
{
	WorldManager::AddGameObject<MainCamera>(L"MainCamera");
	WorldManager::AddGameObject<DotPlayer>(L"Player");
}

World1::~World1()
{

}
