#include "GameManager.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Renderer/SpriteRenderer.h>

#include "Source/Component/GameManagerCtrl.h"

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
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
