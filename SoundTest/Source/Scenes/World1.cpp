#include "World1.h"
#include <Framework/WorldManager.h>
#include <Core/GameObject/MainCamera.h>

#include "Source/Component/SoundTest.h"

//���ϴ� ������Ʈ���� �߰��մϴ�.
World1::World1()
{
	WorldManager::AddGameObject<MainCamera>(L"MainCamera");
	WorldManager::AddGameObject(L"Sound")->AddComponent<SoundTest>();
}

World1::~World1()
{

}
