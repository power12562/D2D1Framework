#include "EnemyDino0Ctrl.h"

#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/GameObject/Base/GameObjectUI.h"
#include <Core/Component/Camera.h>
#include <Core/Component/Renderer/TextRenderer.h>
#include <Core/Component/FSM/FiniteStateMachine.h>
#include <Core/Component/FSM/FSMState.h>


EnemyDino0Ctrl::EnemyDino0Ctrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
}

EnemyDino0Ctrl::~EnemyDino0Ctrl()
{
}

void EnemyDino0Ctrl::Start()
{
#ifdef _DEBUG
	GameObjectBase* playerStateDebug = WorldManager::AddGameObject<GameObjectUI>(L"EnemyState");
	playerStateDebug->transform.SetParent(Camera::GetMainCamera()->gameObject);
	playerStateDebug->transform.localPosition += Vector2(0.f, -30.f);

	stateDebugText = &playerStateDebug->AddComponent<TextRenderer>();
	stateDebugText->SetFont(L"Consolas");
	stateDebugText->TextColor = D2D1::ColorF(D2D1::ColorF::Violet);

	fsm = &gameObject.GetComponent<FiniteStateMachine>();
#endif // _DEBUG


	gameObject.transform.position += Vector2(0.f, -9.f);

}

void EnemyDino0Ctrl::Update()
{
#ifdef _DEBUG
	stateDebugText->Text = L"Enemy State : ";
	const FSMState* state = fsm->GetCurrState();
	if (state)
	{
		stateDebugText->Text += state->GetName();
	}								   
#endif 
}

void EnemyDino0Ctrl::LateUpdate()
{
}

void EnemyDino0Ctrl::Render()
{
}
