#include "World1.h"
#include <Framework/WorldManager.h>
#include <Core/GameObject/MainCamera.h>

//���ϴ� ������Ʈ���� �߰��մϴ�.
World1::World1()
{
	WorldManager::AddGameObject<MainCamera>(L"MainCamera");

}

World1::~World1()
{

}
