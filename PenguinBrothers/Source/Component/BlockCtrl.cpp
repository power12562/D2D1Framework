#include "BlockCtrl.h"
#include <Utility/Debug.h>

#include <Framework/TimeSystem.h>

#include <Core/Component/InputBinding.h>
#include <Core/Component/Movement.h>
#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/Rigidbody2D.h>

using namespace TimeSystem;

BlockCtrl::BlockCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject), ICollider2DNotify(this)
{
	downRot = false;
}

BlockCtrl::~BlockCtrl()
{

}

void BlockCtrl::Init()
{
	player = nullptr;
	PlayerInput = nullptr;
	transform.rotation = 0.f;
	elapsedTime = 0;
}

void BlockCtrl::Start()
{
	Init();
}

void BlockCtrl::Update()
{	
	if (!downRot && PlayerInput && PlayerInput->IsKeyDown("Duck") && abs(pBottom - mTop) <= 1.0f)
	{
		DEBUG_PRINT("%f\n", pBottom - mTop);
		if (pLeft >= mLeft - 2.0f && pRight <= mRight + 2.0f)
		{
			downRot = true;
			elapsedTime = 0;   
			player->GetComponent<Movement>().enabled = false;
			FiniteStateMachine& fsm = player->GetComponent<FiniteStateMachine>();
			fsm.SetState(L"Duck");
			fsm.Transition = false;
			player->GetComponent<Rigidbody2D>().enabled = false;
		}	
	}
	if (downRot)
	{						   
		float dir = abs(pLeft - mLeft) > abs(pRight - mRight) ? 1.f : -1.f;
		transform.rotation += dir * 360.f * Time.GetDeltatime();
		elapsedTime += Time.GetDeltatime();
		if (elapsedTime >= 0.5f)
		{
			if (Rigidbody2D* rb = player->IsComponent<Rigidbody2D>())
			{
				rb->enabled = true;
				rb->Velocity = Vector2::Down * 10.0f;
			}
			
			player->GetComponent<Movement>().enabled = true;
			FiniteStateMachine& fsm = player->GetComponent<FiniteStateMachine>();
			fsm.Transition = true;
			fsm.SetState(L"Airborne");
			player->transform.SetParent();
			player->transform.rotation = 0.f;
			Init();
			downRot = false;			
		}
	}	
}


void BlockCtrl::OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{	
		pLeft = otherCollider->GetLeft();
		pRight = otherCollider->GetRight();
		pTop = otherCollider->GetTop();
		pBottom = otherCollider->GetBottom();

		mLeft = myCollider->GetLeft();
		mRight = myCollider->GetRight();
		mTop = myCollider->GetTop();
		mBottom = myCollider->GetBottom();

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
		pTop = otherCollider->GetTop();
		pBottom = otherCollider->GetBottom();

		mLeft = myCollider->GetLeft();
		mRight = myCollider->GetRight();
		mTop = myCollider->GetTop();
		mBottom = myCollider->GetBottom();
	}
}

void BlockCtrl::OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{
		if (player)
		{
			player->transform.SetParent();
 			Init();
		}	
	}
}