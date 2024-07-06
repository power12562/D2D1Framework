#include "PlayerBombCtrl.h"
#include "Framework/WorldManager.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/SpriteRenderer.h"

PlayerBombCtrl::PlayerBombCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

PlayerBombCtrl::~PlayerBombCtrl()
{

}

void PlayerBombCtrl::Start()
{
	spriteRenderer = &gameObject.AddComponent<SpriteRenderer>();
	spriteRenderer->LoadImage(L"Resource/bomb/blue/bomb.png");

}

void PlayerBombCtrl::Update()
{
	elapsedTime += TimeSystem::Time.GetDeltatime();
	if (elapsedTime >= bombTime)
	{
		WorldManager::DelGameObject(gameObject);
	}
}
