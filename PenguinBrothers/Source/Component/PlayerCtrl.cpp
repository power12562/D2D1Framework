#include "PlayerCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Movement.h"
#include "Core/Component/FSM/FiniteStateMachine.h"

#include "Source/GameObject/PlayerBomb.h"
#include "Source/GameObject/Player.h"

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

	movement = &gameObject.GetComponent<Movement>();
}

void PlayerCtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	if (Input.IsKeyDown(KeyCode::LeftArrow))
	{
		movement->SetSpeed(moveSpeed);
		movement->SetDirection(Vector2::Left);
	}
	else if (Input.IsKeyDown(KeyCode::RightArrow))
	{
		movement->SetSpeed(moveSpeed);
		movement->SetDirection(Vector2::Right);
	}


}

void PlayerCtrl::Render()
{

}

void PlayerCtrl::SpawnBomb()
{
	GameObjectBase* bomb = WorldManager::AddGameObject<PlayerBomb>(L"Bomb");
	bomb->transform.position = gameObject.transform.position;
	bomb->transform.scale = gameObject.transform.scale;
}


