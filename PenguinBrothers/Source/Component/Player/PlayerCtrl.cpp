#include "PlayerCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Framework/WorldManager.h"

#include "Core/Component/FSM/FiniteStateMachine.h"
#include "Core/GameObject/Base/GameObjectUI.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/TextRenderer.h"
#include "Core/Component/Camera.h"

#include "Source/GameObject/Player/PlayerBomb.h"
#include "Source/GameObject/Player/Player.h"

PlayerCtrl::PlayerCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
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

//#ifdef _DEBUG
//	GameObjectBase* playerStateDebug = WorldManager::AddGameObject<GameObjectUI>(L"PlayerState");
//	playerStateDebug->transform.SetParent(Camera::GetMainCamera()->gameObject);
//
//	stateDebugText = &playerStateDebug->AddComponent<TextRenderer>();
//	stateDebugText->SetFont(L"Consolas");
//	stateDebugText->TextColor = D2D1::ColorF(D2D1::ColorF::Violet);
//
//	fsm = &gameObject.GetComponent<FiniteStateMachine>();
//#endif
}

void PlayerCtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

//#ifdef _DEBUG
//	stateDebugText->Text = L"Player State : ";
//	const FSMState* state = fsm->GetCurrState();
//	if (state)
//	{
//		stateDebugText->Text += state->GetName();
//	}
//#endif 
}

void PlayerCtrl::SpawnBomb()
{
	GameObjectBase* bomb = WorldManager::AddGameObject<PlayerBomb>(L"Bomb");
	((PlayerBomb*)bomb)->playerCtrl = this;
	bomb->transform.position = gameObject.transform.position;
	bomb->transform.scale = gameObject.transform.scale;
}


