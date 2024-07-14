#include "AnimeEditScene.h"
#include "Framework/WorldManager.h"

#include "Core/Component/Camera.h"

#include "Source/Component/AnimeEditCameraCtrl.h"
#include "Source/GameObject/PlayerAnimeTest.h"
#include "Source/GameObject/DebugUI.h"
#include "Source/GameObject/RectMode.h"

AnimeEditScene::AnimeEditScene()
{
	Camera::GetMainCamera()->gameObject.AddComponent<AnimeEditCameraCtrl>();
	WorldManager::AddGameObject<DebugUI>(L"DebugUI");
	WorldManager::AddGameObject<PlayerAnimeTest>(L"AnimeTest");
	WorldManager::AddGameObject<RectMode>(L"RectMode")->enable = false;

}

AnimeEditScene::~AnimeEditScene()
{

}
