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

	if (Input.IsKeyDown(KeyCode::F1))
	{
		gameObject.transform.scale = Vector2{ gameObject.transform.scale.x + 0.1f,  gameObject.transform.scale.y + 0.1f };
	}
	if (Input.IsKeyDown(KeyCode::F2))
	{
		gameObject.transform.scale = Vector2{ gameObject.transform.scale.x - 0.1f,  gameObject.transform.scale.y - 0.1f };
	}

	if (Input.IsKey(KeyCode::W))
	{
		gameObject.transform.position += Vector2::Up * moveSpeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::S))
	{
		gameObject.transform.position += Vector2::Down * moveSpeed * Time.GetDeltatime();
	}
	if (Input.IsKey(KeyCode::A))
	{
		gameObject.transform.position += Vector2::Left * moveSpeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::D))
	{
		gameObject.transform.position += Vector2::Right * moveSpeed * Time.GetDeltatime();
	}
}

void AnimeEditCameraCtrl::Render()
{

}
