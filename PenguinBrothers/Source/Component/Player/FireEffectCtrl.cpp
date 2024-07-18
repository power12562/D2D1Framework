#include "FireEffectCtrl.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Collider/SpriteCollider2D.h>
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>
#include <Core/Component/FSM/FiniteStateMachine.h>

#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/FireEffect.h"

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
	switch (((FireEffect&)gameObject).playerCtrl->bombType)
	{
	case BombType::blue:

		break;
	case BombType::red:
		animationRenderer->LoadAnimationClip(L"Resource/bomb/redeffect.txt", L"Resource/bomb/redeffect.png", L"fire");
		break;
	case BombType::green:
		break;
	case BombType::skyblue:
		break;
	default:
		animationRenderer->LoadAnimationClip(L"Resource/bomb/redeffect.txt", L"Resource/bomb/redeffect.png", L"fire");
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
}

void FireEffectCtrl::OnCollisionEnter2D(GameObjectBase* collision)
{
	wprintf(L"Enter!!! %s\n", collision->name);
	if (collision->tag == L"Player")
	{
		collision->GetComponent<FiniteStateMachine>().SetState(L"Dead");
	}
}

void FireEffectCtrl::OnCollisionStay2D(GameObjectBase* collision)
{
	wprintf(L"Stay!!! %s\n", collision->name);
}

void FireEffectCtrl::OnCollisionExit2D(GameObjectBase* collision)
{
	wprintf(L"Exit!!! %s\n", collision->name);
}


