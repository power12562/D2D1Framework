#include "PlayerAnimeTestCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"

PlayerAnimeTestCtrl::PlayerAnimeTestCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	
}

PlayerAnimeTestCtrl::~PlayerAnimeTestCtrl()
{

}

void PlayerAnimeTestCtrl::Start()
{
	spriteAnimation = &gameObject.GetComponent<SpriteAnimation>();
}

void PlayerAnimeTestCtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;
	//원하는 애니메이션 1프레임씩 재생하는거 필요

}

void PlayerAnimeTestCtrl::Render()
{


}
