#include "PlayerCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"

PlayerCtrl::PlayerCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

PlayerCtrl::~PlayerCtrl()
{

}

void PlayerCtrl::Start()
{
	moveSpeed = 300.f;
	spriteAnimation = &gameObject.GetComponent<SpriteAnimation>();
}

void PlayerCtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	if (Input.IsKey(KeyCode::LeftArrow))
	{
		gameObject.transform.position += Vector2::Left * moveSpeed * Time.GetDeltatime();
		SetAnime(PlayerState::Walk);
		if(!gameObject.transform.flipX)
			gameObject.transform.FlipX(true);
	}
	else if (Input.IsKey(KeyCode::RightArrow))
	{
		gameObject.transform.position += Vector2::Right * moveSpeed * Time.GetDeltatime();
		SetAnime(PlayerState::Walk);
		if (gameObject.transform.flipX)
			gameObject.transform.FlipX(false);
	}
	else
	{
		SetAnime(PlayerState::Idle);
	}

	
}

void PlayerCtrl::Render()
{

}

void PlayerCtrl::SetAnime(PlayerState state)
{
	if (playerState == state)
		return;

	switch (state)
	{
	case Idle:
		spriteAnimation->SetAnimationClip(L"Idle", true);
		break;
	case Duck:
		spriteAnimation->SetAnimationClip(L"Duck", true);
		break;
	case Walk:
		spriteAnimation->SetAnimationClip(L"Walk", true);
		break;
	case Jump:
		spriteAnimation->SetAnimationClip(L"Jump", false);
		break;
	case Slide:
		spriteAnimation->SetAnimationClip(L"Slide", false);
		break;
	case Attack:
		spriteAnimation->SetAnimationClip(L"Attack", false);
		break;
	}
	playerState = state;
}
