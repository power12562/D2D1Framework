#include "PlayerBombCtrl.h"
#include "Framework/WorldManager.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Collider/SpriteCollider2D.h"
#include "Core/Component/Rigidbody2D.h"
#include "Core/Component/AudioClip.h"

#include "Source/GameObject/Player/PlayerBomb.h"
#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/BombEffect.h"
#include "Source/GameObject/Player/FireEffect.h"
#include "Source/Component/Player/FireEffectCtrl.h"
#include "Source/Component/Player/BombSoundCtrl.h"

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

	rb = &GetComponent<Rigidbody2D>();
	if (transform.flipX)
	{
		rb->AddForce(Vector2(-180.f, 300.f));
	}
	else
	{
		rb->AddForce(Vector2(180.f, 300.f));
	}
}

void PlayerBombCtrl::Update()
{
	elapsedTime += TimeSystem::Time.GetDeltatime();
	if (spriteAnimation->CurrentClipEnd)
	{
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
		WorldManager::DelGameObject(gameObject);
		GameObjectBase* bombSound = WorldManager::AddGameObject(L"BombSound");
		bombSound->AddComponent<AudioClip>();
		bombSound->AddComponent<BombSoundCtrl>();
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


