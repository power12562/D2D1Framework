#include "AnimeEditCameraCtrl.h"

#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"

AnimeEditCameraCtrl::AnimeEditCameraCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	moveSpeed = 100.f;
}

AnimeEditCameraCtrl::~AnimeEditCameraCtrl()
{

}

void AnimeEditCameraCtrl::Start()
{

}

void AnimeEditCameraCtrl::Update()
{
	using namespace InputSystem;
	using namespace TimeSystem;

	if (Input.IsKeyDown(KeyCode::Minus))
	{
		gameObject.transform.scale = Vector2{ gameObject.transform.scale.x + 0.1f,  gameObject.transform.scale.y + 0.1f };
	}
	if (Input.IsKeyDown(KeyCode::Plus))
	{
		gameObject.transform.scale = Vector2{ gameObject.transform.scale.x - 0.1f,  gameObject.transform.scale.y - 0.1f };
	}

	float speedScale = 1.0f;
	if (Input.IsKey(KeyCode::Shift))
	{
		speedScale = 0.25f;
	}
	if (Input.IsKey(KeyCode::W))
	{
		gameObject.transform.position += Vector2::Up * moveSpeed * Time.GetDeltatime(false) * speedScale;
	}
	else if (Input.IsKey(KeyCode::S))
	{
		gameObject.transform.position += Vector2::Down * moveSpeed * Time.GetDeltatime(false) * speedScale;
	}
	if (Input.IsKey(KeyCode::A))
	{
		gameObject.transform.position += Vector2::Left * moveSpeed * Time.GetDeltatime(false) * speedScale;
	}
	else if (Input.IsKey(KeyCode::D))
	{
		gameObject.transform.position += Vector2::Right * moveSpeed * Time.GetDeltatime(false) * speedScale;
	}
}

void AnimeEditCameraCtrl::Render()
{

}
