#include "BlockCtrl.h"
#include <Framework/TimeSystem.h>
#include <Core/Component/InputBinding.h>
#include <Core/Component/Movement.h>
#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/Rigidbody2D.h>

using namespace TimeSystem;

BlockCtrl::BlockCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject), ICollider2DNotify(this)
{

}

BlockCtrl::~BlockCtrl()
{

}

void BlockCtrl::Start()
{
	player = nullptr;
	PlayerInput = nullptr;
}

void BlockCtrl::Update()
{
	if (endRot && PlayerInput && PlayerInput->IsKeyDown("Duck"))
	{
		if (pLeft >= mLeft - 2.0f && pRight <= mRight + 2.0f)
		{
			endRot = false;
			elapsedTime = 0;   
			player->GetComponent<Movement>().enabled = false;
			FiniteStateMachine& fsm = player->GetComponent<FiniteStateMachine>();
			fsm.SetState(L"Duck");
			fsm.Transition = false;
			player->GetComponent<Rigidbody2D>().enabled = false;
		}	
	}
	if (!endRot)
	{						   
		float dir = abs(pLeft - mLeft) > abs(pRight - mRight) ? 1.f : -1.f;
		transform.rotation += dir * 180.f * Time.GetDeltatime();
		elapsedTime += Time.GetDeltatime();
		if (elapsedTime >= 1.0f)
		{
			player->GetComponent<Rigidbody2D>().enabled = true;
			endRot = true;
			player->GetComponent<Movement>().enabled = true;
			transform.rotation = 180.f * dir;
			FiniteStateMachine& fsm = player->GetComponent<FiniteStateMachine>();
			fsm.Transition = true;
			fsm.SetState(L"Idle");
			player->transform.SetParent();
			player->transform.rotation = 0.f;
		}
	}	
}


void BlockCtrl::OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{
		player = &otherCollider->gameObject;
		player->transform.SetParent(transform);
		PlayerInput = &player->GetComponent<InputBinding>();
	}
}

void BlockCtrl::OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{
		pLeft = otherCollider->GetLeft();
		pRight = otherCollider->GetRight();
		mLeft = myCollider->GetLeft();
		mRight = myCollider->GetRight();
	}
}

void BlockCtrl::OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (player)
		return;

	if (otherCollider->gameObject.tag == L"Player")
	{
		if (player)
		{
			player->transform.SetParent();
			PlayerInput = nullptr;
			player = nullptr;
		}	
	}
}
