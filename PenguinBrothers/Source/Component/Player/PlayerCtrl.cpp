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

#include <Utility/Debug.h>

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

	fsm = IsComponent<FiniteStateMachine>();
}

void PlayerCtrl::Update()
{
	if (transform.position.y < -450)
	{
		fsm->SetState(L"Dead");
	}
	//Vector2 velocity = GetComponent<Rigidbody2D>().Velocity;
	//DEBUG_PRINT("Velocity { %f, %f }\n", velocity.x, velocity.y);
	DEBUG_PRINT("position { %f, %f }\n", transform.position.x, transform.position.y);
	//DEBUG_PRINT("angle : %f\n", (float)transform.rotation);
}

void PlayerCtrl::OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Ground" || otherCollider->gameObject.tag == L"Block")
	{
		if (myCollider->GetBottom() >= otherCollider->GetTop() - 1.0f)
		{
			isJump = false;
			//DEBUG_PRINT("isJump = %d\n", isJump);
		}
	}
}

void PlayerCtrl::OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Ground" || otherCollider->gameObject.tag == L"Block")
	{
		if (myCollider->GetBottom() >= otherCollider->GetTop() - 1.0f)
		{
			if(fsm->GetCurrState()->GetName() != L"Jump")
				isJump = false;
			//DEBUG_PRINT("isJump = %d\n", isJump);
		}
	}
}

void PlayerCtrl::OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Ground" || otherCollider->gameObject.tag == L"Block")
	{
		if (myCollider->GetBottom() >= otherCollider->GetTop() - 1.0f)
		{
			isJump = true;
			//DEBUG_PRINT("isJump = %d\n", isJump);
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


