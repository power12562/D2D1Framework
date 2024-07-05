#include "Source/Component/DebugUICtrl.h"

#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/TextRenderer.h"
#include "Core/Component/Renderer/LineRenderer.h"

DebugUICtrl::DebugUICtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

DebugUICtrl::~DebugUICtrl()
{

}

void DebugUICtrl::Start()
{
	SIZE screenSize = WinGameApp::GetClientSize();

	textRenderer = &gameObject.AddComponent<TextRenderer>();
	textRenderer->SetFont(L"consolas");
	textRenderer->Size = 25.f;

	lineRendererX = &gameObject.AddComponent<LineRenderer>();
	lineRendererX->Width = 1.0f;
	lineRendererX->StartPosition = Vector2(0.f, -screenSize.cy * 0.5f);
	lineRendererX->EndPosition = Vector2((float)screenSize.cx, -screenSize.cy * 0.5f);

	lineRendererY = &gameObject.AddComponent<LineRenderer>();
	lineRendererY->Width = 1.0f;
	lineRendererY->StartPosition = Vector2(screenSize.cx * 0.5f, 0.f);
	lineRendererY->EndPosition = Vector2(screenSize.cx * 0.5f, -(float)screenSize.cy);
}

void DebugUICtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	textRenderer->Text = Line[0];
	for (int i = 1; i < Line.size(); i++)
	{
		textRenderer->Text += std::wstring(L"\n") += Line[i];
	}
}
