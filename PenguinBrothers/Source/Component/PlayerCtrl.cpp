#include "PlayerCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

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
	moveSpeed = 150.f;
	slideSpeed = 300.f;
	spriteAnimation = &gameObject.GetComponent<SpriteAnimation>();
}

void PlayerCtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	UpdateState();
	if (playerState == State::Slide)
	{
		gameObject.transform.position += dir * slideSpeed * Time.GetDeltatime();
	}
	else if (playerState == State::Walk)
	{
		gameObject.transform.position += dir * moveSpeed * Time.GetDeltatime();
		
	}
	UpdateAnime();
}

void PlayerCtrl::Render()
{
#ifdef _DEBUG
	SIZE clientSize = WinGameApp::GetClientSize();
	wchar_t outputText[30] = L"state : ";
	wchar_t currentStateText[10]{};
	static auto* font = D2DRenderer::CreateD2DFont(L"Consolas", 50.f);
	switch (playerState)
	{
	case PlayerCtrl::State::Idle:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Idle");
		break;
	case PlayerCtrl::State::Duck:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Duck");
		break;
	case PlayerCtrl::State::Walk:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Walk");
		break;
	case PlayerCtrl::State::Jump:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Jump");
		break;
	case PlayerCtrl::State::Slide:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Slide");
		break;
	case PlayerCtrl::State::Attack:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Attack");
		break;
	}
	lstrcatW(outputText, currentStateText);
	D2DRenderer::DrawTextW(outputText, font, { 0,0, (float)clientSize.cx, 50 });
#endif 



}

void PlayerCtrl::SetState(State state)
{
	if (playerState == state)
		return;

	playerState = state;
}

void PlayerCtrl::UpdateState()
{
	using namespace InputSystem;

	if (!spriteAnimation->CurrentClipEnd)
		return;

	if (Input.IsKey(KeyCode::DownArrow))
	{
		SetState(State::Duck);
		if (Input.IsKeyDown(KeyCode::X))
		{
			SetState(State::Slide);
		}
	}
	else if (Input.IsKeyDown(KeyCode::X))
	{
		SetState(State::Jump);
	}
	else if (Input.IsKeyDown(KeyCode::Z))
	{
		SetState(State::Attack);
	}
	else if (Input.IsKey(KeyCode::LeftArrow))
	{
		SetState(State::Walk);
		dir = Vector2::Left;
		if (!gameObject.transform.flipX)
			gameObject.transform.FlipX(true);
	}
	else if (Input.IsKey(KeyCode::RightArrow))
	{
		SetState(State::Walk);
		dir = Vector2::Right;
		if (gameObject.transform.flipX)
			gameObject.transform.FlipX(false);
	}
	else 
	{
		SetState(State::Idle);
	}
}

void PlayerCtrl::UpdateAnime()
{
	if (playerState == animeState)
		return;

	switch (playerState)
	{
	case State::Idle:
		spriteAnimation->SetAnimationClip(L"Idle", true);
		break;
	case State::Duck:
		spriteAnimation->SetAnimationClip(L"Duck", true);
		break;
	case State::Walk:
		spriteAnimation->SetAnimationClip(L"Walk", true);
		break;
	case State::Jump:
		spriteAnimation->SetAnimationClip(L"Jump", false);
		break;
	case State::Slide:
		spriteAnimation->SetAnimationClip(L"Slide", false);
		break;
	case State::Attack:
		spriteAnimation->SetAnimationClip(L"Attack", false);
		break;
	}
	animeState = playerState;
}
