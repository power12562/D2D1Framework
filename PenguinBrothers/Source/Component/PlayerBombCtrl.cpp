#include "PlayerBombCtrl.h"
#include "Framework/WorldManager.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/SpriteRenderer.h"
#include "Core/Component/SpriteAnimation.h"

PlayerBombCtrl::PlayerBombCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

PlayerBombCtrl::~PlayerBombCtrl()
{

}

void PlayerBombCtrl::Start()
{
	spriteAnimation = &gameObject.AddComponent<SpriteAnimation>();
	spriteAnimation->LoadAnimation(L"Resource/bomb/bomb.txt", L"Resource/bomb/blue/bomb.png", L"bomb");
	spriteAnimation->SetAnimation(L"bomb");

	spriteRenderer = &gameObject.AddComponent<SpriteRenderer>();
	spriteRenderer->SetSpriteAnimation(*spriteAnimation);
}

void PlayerBombCtrl::Update()
{
	elapsedTime += TimeSystem::Time.GetDeltatime();
	if (spriteAnimation->CurrentClipEnd)
	{
		WorldManager::DelGameObject(gameObject);
	}
}
