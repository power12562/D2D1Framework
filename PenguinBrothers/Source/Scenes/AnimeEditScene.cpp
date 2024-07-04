#include "AnimeEditScene.h"
#include "Framework/WorldManager.h"

#include "Core/Component/Camera.h"

#include "Source/GameObject/Player.h"
#include "Source/Component/AnimeEditCameraCtrl.h"

AnimeEditScene::AnimeEditScene()
{
	WorldManager::AddGameObject<Player>(L"Player");
	Camera::GetMainCamera()->gameObject.AddComponent<AnimeEditCameraCtrl>();
	
}

AnimeEditScene::~AnimeEditScene()
{

}
