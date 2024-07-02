#include "CameraMove.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"

CameraMove::CameraMove(GameObjectBase& gameObject) : ComponentBase(gameObject)
{


}

CameraMove::~CameraMove()
{
	
}

void CameraMove::Start()
{
	moveSpeed = 300.f;
}

void CameraMove::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	if (Input.IsKey(KeyCode::A))
	{
		gameObject.transform.position += Vector2::Left * moveSpeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::D))
	{
		gameObject.transform.position += Vector2::Right * moveSpeed * Time.GetDeltatime();
	}
	if (Input.IsKey(KeyCode::W))
	{
		gameObject.transform.position += Vector2::Up * moveSpeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::S))
	{
		gameObject.transform.position += Vector2::Down * moveSpeed * Time.GetDeltatime();
	}

	if (Input.IsKeyDown(KeyCode::F1))
	{
		gameObject.transform.scale = Vector2(gameObject.transform.scale.x + 0.25f, gameObject.transform.scale.y + 0.25f);
	}
	if (Input.IsKeyDown(KeyCode::F2))
	{
		gameObject.transform.scale = Vector2(gameObject.transform.scale.x - 0.25f, gameObject.transform.scale.y - 0.25f);
	}

}
