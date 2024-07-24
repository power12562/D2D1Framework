#include "GameManager.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Renderer/SpriteRenderer.h>

#include "Source/Component/GameManagerCtrl.h"

//게임 오브젝트를 상속받는 클래스의 cpp 파일에 다음 해더와 매크로를 추가해야 월드 json 저장이 가능합니다.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(GameManager)



GameManager::GameManager()
{
	int CurrentStage = AddComponent<GameManagerCtrl>().CurrentStage;

	std::wstring bgPath = L"Resource/Stage/Stage" + std::to_wstring(CurrentStage) + L".png";
	GameObjectBase* backGround = WorldManager::AddGameObject(L"Background");
	backGround->AddComponent<SpriteRenderer>().LoadImage(bgPath.c_str());
	backGround->OderLayer = -1;

	

}

GameManager::~GameManager()
{

}
