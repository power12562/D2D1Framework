#include "PlayerBombCtrl.h"
#include "Framework/WorldManager.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/SpriteCollider2D.h"

#include "Source/GameObject/Player/PlayerBomb.h"
#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/BombEffect.h"
#include "Source/GameObject/Player/FireEffect.h"

PlayerBombCtrl::PlayerBombCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject), ICollider2DNotify(this)
{

}

PlayerBombCtrl::~PlayerBombCtrl()
{

}

void PlayerBombCtrl::Start()
{
#ifdef _DEBUG
	GetComponent<SpriteCollider2D>().isDrawCollider = true;
#endif // _DEBUG


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
		GameObjectBase* bombEffect = WorldManager::AddGameObject<BombEffect>(L"bombEffect");
		bombEffect->transform.position = gameObject.transform.position;

		FireEffect* fireEffect = (FireEffect*)WorldManager::AddGameObject<FireEffect>(L"fireEffect");
		fireEffect->transform.position = gameObject.transform.position;
		fireEffect->playerCtrl = ((PlayerBomb&)gameObject).playerCtrl;
	}
}

void PlayerBombCtrl::OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Attack")
	{
		spriteAnimation->SetCurrentFrameIndex(spriteAnimation->LastFrameIndex);
	}
}


