#include "FireEffectCtrl.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Collider/SpriteCollider2D.h>
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>
#include <Core/Component/FSM/FiniteStateMachine.h>

#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/FireEffect.h"
#include "Source/Component/GameManagerCtrl.h"

int FireEffectCtrl::rightCount = 0;
int FireEffectCtrl::lefttCount = 0;

FireEffectCtrl::FireEffectCtrl(GameObjectBase& gameObject)
	: ComponentBase(gameObject), ICollider2DNotify(this)
{
	
}

FireEffectCtrl::~FireEffectCtrl()
{
}

void FireEffectCtrl::Start()
{
#ifdef _DEBUG
	GetComponent<SpriteCollider2D>().isDrawCollider = true;
#endif 
	animationRenderer = &GetComponent<SpriteAnimationRenderer>();
	if (bombDir < 0)
	{
		transform.FlipX(true);
	}

	switch (((FireEffect&)gameObject).bombType)
	{
	case BombType::blue:
		animationRenderer->LoadAnimationClip(L"Resource/bomb/blueeffect.csv", L"Resource/bomb/blueeffect.png", L"fire");
		break;
	case BombType::red:
		animationRenderer->LoadAnimationClip(L"Resource/bomb/redeffect.csv", L"Resource/bomb/redeffect.png", L"fire");
		break;
	case BombType::green:
		animationRenderer->LoadAnimationClip(L"Resource/bomb/greeneffect.csv", L"Resource/bomb/greeneffect.png", L"fire");
		break;
	case BombType::skyblue:

		break;
	default:
		animationRenderer->LoadAnimationClip(L"Resource/bomb/redeffect.csv", L"Resource/bomb/redeffect.png", L"fire");
		break;
	}
	animationRenderer->SetAnimation(L"fire");	
}

void FireEffectCtrl::Update()
{
	if (animationRenderer->CurrentClipEnd)
	{
		WorldManager::DelGameObject(gameObject);
	}
	if(!spawnNext && animationRenderer->CurrentFrameIndex == animationRenderer->LastFrameIndex / 3)
	{
		SpawnNext();
	}
}

void FireEffectCtrl::SpawnNext()
{
	constexpr float interval = 50.0f;
	if (bombDir > 0 && rightCount > 0)
	{
		SpawnFire(transform.position + Vector2::Right * interval, 1);
		--rightCount;
		//printf("rightCount : %d\n", rightCount);
	}
	else if (bombDir < 0 && lefttCount > 0)
	{
		SpawnFire(transform.position + Vector2::Left * interval, -1);
		--lefttCount;
		//printf("leftCount : %d\n", lefttCount);
	}
	if (bombDir == 0)
	{
		if (rightCount > 0)
		{
			SpawnFire(transform.position + Vector2::Right * interval, 1);
			--rightCount;
			//printf("rightCount : %d\n", rightCount);
		}
		if (lefttCount > 0)
		{
			SpawnFire(transform.position + Vector2::Left * interval, -1);
			--lefttCount;
			//printf("leftCount : %d\n", lefttCount);
		}
	}
	spawnNext = true;
}

void FireEffectCtrl::SpawnFire(const Vector2& nextPos, int dir)
{
	FireEffect* fireEffect = (FireEffect*)WorldManager::AddGameObject<FireEffect>(L"fireEffect");
	fireEffect->transform.position = nextPos;
	fireEffect->bombType = ((FireEffect&)gameObject).bombType;
	fireEffect->GetComponent<FireEffectCtrl>().bombDir = dir;

}


void FireEffectCtrl::OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{
		otherCollider->GetComponent<FiniteStateMachine>().SetState(L"Dead");
	}
	if (otherCollider->gameObject.tag == L"Enemy")
	{
		otherCollider->gameObject.enable = false;
		GameManagerCtrl::EnemyCount--;
		if (GameManagerCtrl::EnemyCount == 0)
		{
			for (auto& p : WorldManager::FindGameObjectsWithTag(L"Player"))
			{
				FiniteStateMachine& fsm = p->GetComponent<FiniteStateMachine>();
				fsm.Transition = true;
				fsm.SetState(L"Win");
			}
		}
	}
}


