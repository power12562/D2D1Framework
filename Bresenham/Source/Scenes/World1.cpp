#include "World1.h"

#include <Framework/WinGameApp.h>
#include <Framework/WorldManager.h>
#include <Core/GameObject/MainCamera.h>

#include "Source/GameObject/BresenhamTest.h"

//원하는 오브젝트들을 추가합니다.
World1::World1()
{
	SIZE clientSize = WinGameApp::GetClientSize();

	GameObjectBase* mainCam = WorldManager::AddGameObject<MainCamera>(L"MainCamera");
	mainCam->transform.position += Vector2{ 400, 400 };

	WorldManager::AddGameObject<BresenhamTest>(L"BresenhamTest");
}

World1::~World1()
{

}
