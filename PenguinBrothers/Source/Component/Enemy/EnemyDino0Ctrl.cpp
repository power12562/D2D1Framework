#include "EnemyDino0Ctrl.h"

#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/GameObject/Base/GameObjectUI.h"

#include <Core/Component/Camera.h>
#include <Core/Component/Renderer/TextRenderer.h>
#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/FSM/FSMState.h>
#include <Core/Component/Collider/SpriteCollider2D.h>
#include <Core/Component/Rigidbody2D.h>

#include <Source/GameObject/Enemy/EnemyDino0Attack.h>
#include <Source/GameObject/Enemy/EnemyDino0.h>


EnemyDino0Ctrl::EnemyDino0Ctrl(GameObjectBase& gameObject) : ComponentBase(gameObject), ICollider2DNotify(this)
{
}

EnemyDino0Ctrl::~EnemyDino0Ctrl()
{
}

void EnemyDino0Ctrl::SpawnFire()
{
	EnemyDino0& obj = (EnemyDino0&)gameObject;
	if (obj.myAttack == nullptr)
	{
		EnemyDino0Attack* fire = (EnemyDino0Attack*)WorldManager::AddGameObject<EnemyDino0Attack>(L"DinoAttack");
		fire->transform.FlipX(gameObject.transform.flipX);
		fire->transform.position = gameObject.transform.position;
		fire->myOwner = (EnemyDino0*)&gameObject;

		obj.myAttack = fire;

		float dir = gameObject.transform.flipX ? 1.f : -1.f;
		fire->transform.position += Vector2(dir * 110.f, 33.f);
	}
}

void EnemyDino0Ctrl::Start()
{	
#ifdef _DEBUG
	GetComponent<SpriteCollider2D>().isDrawCollider = true;
#endif // _DEBUG

	GetComponent<Rigidbody2D>().enabled = true;
	gameObject.transform.position += Vector2(0.f, -9.f);
	fsm = gameObject.IsComponent<FiniteStateMachine>();
}


void EnemyDino0Ctrl::Update()
{

}

void EnemyDino0Ctrl::LateUpdate()
{
}

void EnemyDino0Ctrl::Render()
{
}

void EnemyDino0Ctrl::OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{
		//fsm->SetState(L"Idle");
 		//GetComponent<Rigidbody2D>().AddForce((myCollider->transform.position - otherCollider->transform.position).Normalized() * 100.f);

	}

}
