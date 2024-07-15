#include "FireEffectCtrl.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

#include "Source/Component/Player/PlayerCtrl.h"
#include "Source/GameObject/Player/FireEffect.h"

FireEffectCtrl::FireEffectCtrl(GameObjectBase& gameObject)
	: ComponentBase(gameObject) 
{
	
}

FireEffectCtrl::~FireEffectCtrl()
{
}

void FireEffectCtrl::Start()
{
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
