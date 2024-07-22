#include "PlayerCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Framework/WorldManager.h"

#include <Core/Component/Rigidbody2D.h>
#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/GameObject/Base/GameObjectUI.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/TextRenderer.h"
#include "Core/Component/Camera.h"


#include "Source/GameObject/Player/PlayerBomb.h"
#include "Source/GameObject/Player/Player.h"


using namespace TimeSystem;
using namespace InputSystem;
PlayerCtrl::PlayerCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject), ICollider2DNotify(this)
{

}

PlayerCtrl::~PlayerCtrl()
{

}

void PlayerCtrl::Start()
{
	moveSpeed = 350.f;
	slideSpeed = 525.f;
	gameObject.transform.position += Vector2(0.f, -25.f);

	fsm = IsComponent<FiniteStateMachine>();
}

void PlayerCtrl::Update()
{
	//printf("isJump = %s\n", (isJump) ? "true" : "false");


}

void PlayerCtrl::OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Ground")
	{
		if (myCollider->GetBottom() >= otherCollider->GetTop() - 1.0f)
		{
			isJump = false;
		}
	}
}

void PlayerCtrl::OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Ground")
	{
		if (myCollider->GetBottom() >= otherCollider->GetTop() - 1.0f)
		{
			isJump = true;
		}
	}
}

void PlayerCtrl::SpawnBomb()
{
	GameObjectBase* bomb = WorldManager::AddGameObject<PlayerBomb>(L"Bomb");
	((PlayerBomb*)bomb)->playerCtrl = this;
	bomb->transform.position = gameObject.transform.position;
	bomb->transform.scale = gameObject.transform.scale;
}


