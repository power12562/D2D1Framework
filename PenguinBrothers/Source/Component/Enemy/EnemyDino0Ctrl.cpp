#include "EnemyDino0Ctrl.h"

#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/GameObject/Base/GameObjectUI.h"
#include <Core/Component/Camera.h>
#include <Core/Component/Renderer/TextRenderer.h>
#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/FSM/FSMState.h>
#include <Core/Component/Collider/BoxCollider2D.h>

#include <Source/GameObject/Enemy/EnemyDino0Attack.h>


EnemyDino0Ctrl::EnemyDino0Ctrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
}

EnemyDino0Ctrl::~EnemyDino0Ctrl()
{
}

void EnemyDino0Ctrl::SpawnFire()
{
	GameObjectBase* fire = WorldManager::AddGameObject<EnemyDino0Attack>(L"DinoAttack");
	fire->transform.FlipX(gameObject.transform.flipX);
	fire->transform.position = gameObject.transform.position;
	
	float dir = gameObject.transform.flipX ? 1.f : -1.f;
	fire->transform.position += Vector2(dir * 110.f, 33.f);
}

void EnemyDino0Ctrl::Start()
{
#ifdef _DEBUG
//	GameObjectBase* playerStateDebug = WorldManager::AddGameObject<GameObjectUI>(L"EnemyState");
//	playerStateDebug->transform.SetParent(Camera::GetMainCamera()->gameObject);
//	playerStateDebug->transform.localPosition += Vector2(0.f, -30.f);
//
//	stateDebugText = &playerStateDebug->AddComponent<TextRenderer>();
//	stateDebugText->SetFont(L"Consolas");
//	stateDebugText->TextColor = D2D1::ColorF(D2D1::ColorF::Violet);
//
//	fsm = &gameObject.GetComponent<FiniteStateMachine>();
	GetComponent<BoxCollider2D>().isDrawCollider = true;
#endif 

	gameObject.transform.position += Vector2(0.f, -9.f);
}

void EnemyDino0Ctrl::Update()
{
//#ifdef _DEBUG
//	stateDebugText->Text = L"Enemy State : ";
//	const FSMState* state = fsm->GetCurrState();
//	if (state)
//	{
//		stateDebugText->Text += state->GetName();
//	}								   
//#endif 


}

void EnemyDino0Ctrl::LateUpdate()
{
}

void EnemyDino0Ctrl::Render()
{
}
