#include "World1.h"
#include <Framework/WorldManager.h>
#include <Core/GameObject/MainCamera.h>

#include "Source/Component/SoundTest.h"

//원하는 오브젝트들을 추가합니다.
World1::World1()
{
	WorldManager::AddGameObject<MainCamera>(L"MainCamera");
	WorldManager::AddGameObject(L"Sound")->AddComponent<SoundTest>();
}

World1::~World1()
{

}
