#include "PlayerCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"

#include "Source/GameObject/PlayerBomb.h"

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
	spriteAnimation->SetAnimation(L"Spawn");

	gameObject.transform.position += Vector2(0.f, -25.f);
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
#ifdef _DEBUG
	if (Input.IsKeyDown(KeyCode::R))
	{
		playerState = State::Dead;
	}
#endif // _DEBUGG
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
	case State::Spawn:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Spawn");
		break;
	case State::Idle:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Idle");
		break;
	case State::Duck:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Duck");
		break;
	case State::Walk:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Walk");
		break;
	case State::Jump:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Jump");
		break;
	case State::Slide:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Slide");
		break;
	case State::Attack:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Attack");
		break;		
	case State::Dead:
		wcscpy_s(currentStateText, _ARRAYSIZE(currentStateText), L"Dead");
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

	if (playerState == State::Attack)
	{
		SpawnBomb();
	}

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
	else if (Input.IsKeyDown(KeyCode::Z) && PlayerBomb::GetObjectCount() == 0)
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
		spriteAnimation->SetAnimation(L"Idle", true);
		break;
	case State::Duck:
		spriteAnimation->SetAnimation(L"Duck", true);
		break;
	case State::Walk:
		spriteAnimation->SetAnimation(L"Walk", true);
		break;
	case State::Jump:
		spriteAnimation->SetAnimation(L"Jump", false);
		break;
	case State::Slide:
		spriteAnimation->SetAnimation(L"Slide", false);
		break;
	case State::Attack:
		spriteAnimation->SetAnimation(L"Attack", false);
		break;
	case State::Dead:
		spriteAnimation->SetAnimation(L"Dead", false);
		break;
	}
	animeState = playerState;
}

void PlayerCtrl::SpawnBomb()
{
	GameObjectBase* bomb = WorldManager::AddGameObject<PlayerBomb>(L"Bomb");
	bomb->transform.position = gameObject.transform.position;
	bomb->transform.scale = gameObject.transform.scale;
}
