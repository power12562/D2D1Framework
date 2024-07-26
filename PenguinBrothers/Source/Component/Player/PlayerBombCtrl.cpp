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
#include "Source/Component/Player/FireEffectCtrl.h"

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
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/blue.csv", L"Resource/bomb/bomb.png", L"bomb");
		break;
	case BombType::red :
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/red.csv", L"Resource/bomb/bomb.png", L"bomb");
		break;
	case BombType::green :
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/green.csv", L"Resource/bomb/bomb.png", L"bomb");
		break;
	case BombType::skyblue :
		spriteAnimation->LoadAnimationClip(L"Resource/bomb/skyblue.csv", L"Resource/bomb/bomb.png", L"bomb");
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
		fireEffect->bombType = ((PlayerBomb&)gameObject).playerCtrl->bombType;

		FireEffectCtrl& fireEffectCtrl = fireEffect->GetComponent<FireEffectCtrl>();
		switch (((PlayerBomb&)gameObject).playerCtrl->bombType)
		{
		case BombType::blue:
			fireEffectCtrl.lefttCount = 1;
			fireEffectCtrl.rightCount = 1;
			break;
		case BombType::red:
			fireEffectCtrl.lefttCount = 3;
			fireEffectCtrl.rightCount = 3;
			break;
		case BombType::green:
			if (transform.flipX == false)
			{
				fireEffectCtrl.lefttCount = 1;
				fireEffectCtrl.rightCount = 5;
			}
			else
			{
				fireEffectCtrl.lefttCount = 5;
				fireEffectCtrl.rightCount = 1;
			}		
			break;
		case BombType::skyblue:
			
			break;
		}

	}
}

void PlayerBombCtrl::OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Attack")
	{
		if (spriteAnimation)
		{
			spriteAnimation->SetCurrentFrameIndex(spriteAnimation->LastFrameIndex);
		}
	}
}


