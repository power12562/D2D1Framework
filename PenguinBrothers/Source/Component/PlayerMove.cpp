#include "PlayerMove.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"

PlayerMove::PlayerMove(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

PlayerMove::~PlayerMove()
{

}

void PlayerMove::Start()
{
	moveSpeed = 300.f;
}

void PlayerMove::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	if (Input.IsKey(KeyCode::LeftArrow))
	{
		gameObject.transform.position += Vector2::Left * moveSpeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::RightArrow))
	{
		gameObject.transform.position += Vector2::Right * moveSpeed * Time.GetDeltatime();
	}


}

void PlayerMove::Render()
{

}
