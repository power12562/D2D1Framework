#include "PlayerAnimeTestCtrl.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"

PlayerAnimeTestCtrl::PlayerAnimeTestCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

PlayerAnimeTestCtrl::~PlayerAnimeTestCtrl()
{

}

void PlayerAnimeTestCtrl::Start()
{
	spriteAnimation = &gameObject.GetComponent<SpriteAnimation>();
}

void PlayerAnimeTestCtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;
	//원하는 애니메이션 1프레임씩 재생하는거 필요

}

void PlayerAnimeTestCtrl::Render()
{
#ifdef _DEBUG
	SIZE clientSize = WinGameApp::GetClientSize();
	wchar_t outputText[30] = L"clip : ";
	wchar_t currentStateText[10]{};
	static auto* font = D2DRenderer::CreateD2DFont(L"Consolas", 50.f);
	//현재 선택된 애니메이션 디버깅 필요

	lstrcatW(outputText, currentStateText);
	D2DRenderer::DrawTextW(outputText, font, { 0,0, (float)clientSize.cx, 50 });
#endif 



}
