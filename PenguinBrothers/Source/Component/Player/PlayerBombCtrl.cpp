#include "PlayerBombCtrl.h"
#include "Framework/WorldManager.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"

#include "Source/GameObject/Player/PlayerBomb.h"
#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/BombEffect.h"

PlayerBombCtrl::PlayerBombCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

PlayerBombCtrl::~PlayerBombCtrl()
{

}

void PlayerBombCtrl::Start()
{
	spriteAnimation = &gameObject.AddComponent<SpriteAnimationRenderer>();
	switch (((PlayerBomb&)gameObject).playerCtrl->bombType)
	{
	case BombType::blue :
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/blue.txt", L"Resource/bomb/bomb.png", L"bomb");
		break;
	case BombType::red :
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/red.txt", L"Resource/bomb/bomb.png", L"bomb");
		break;
	case BombType::green :
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/green.txt", L"Resource/bomb/bomb.png", L"bomb");
		break;
	case BombType::skyblue :
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/skyblue.txt", L"Resource/bomb/bomb.png", L"bomb");
		break;
	}
	spriteAnimation->SetAnimation(L"bomb");
}

void PlayerBombCtrl::Update()
{
	elapsedTime += TimeSystem::Time.GetDeltatime();
	if (spriteAnimation->CurrentClipEnd)
	{
		WorldManager::DelGameObject(gameObject);
		GameObjectBase* effect = WorldManager::AddGameObject<BombEffect>(L"effect");
		effect->transform.position = gameObject.transform.position;
		effect->transform.position += Vector2(0.0f, 15.0f);
	}
}
