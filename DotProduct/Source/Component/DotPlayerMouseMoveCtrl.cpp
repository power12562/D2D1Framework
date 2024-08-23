#include "DotPlayerMouseMoveCtrl.h"

#include <Framework/InputSystem.h>
#include <Framework/WorldManager.h>
#include <Framework/WinGameApp.h>
#include <Framework/TimeSystem.h>

#include <Core/GameObject/Base/GameObjectUI.h>
#include <Core/Component/Renderer/TextRenderer.h>
#include <Core/Component/Movement.h>

#include <Math/Mathf.h>
#include <Vector/Vector3.h>

using namespace InputSystem;
using namespace TimeSystem;

DotPlayerMouseMoveCtrl::DotPlayerMouseMoveCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

DotPlayerMouseMoveCtrl::~DotPlayerMouseMoveCtrl()
{
}

void DotPlayerMouseMoveCtrl::Start()
{
	SIZE clientSize = WinGameApp::GetClientSize();
	movement = IsComponent<Movement>();

	GameObjectBase* debugTextUI = WorldManager::AddGameObject<GameObjectUI>(L"debugTextUI");
	debugTextRenderer = &debugTextUI->AddComponent<TextRenderer>();
	debugTextRenderer->SetFont(L"Consolas");
	debugTextRenderer->SetFontSize(30);
	debugTextRenderer->DrawRect = { (float)clientSize.cx, (float)clientSize.cy };
	debugTextRenderer->TextColor = D2D1::ColorF(D2D1::ColorF::BlueViolet);
}

void DotPlayerMouseMoveCtrl::Update()
{
	Vector2 dir = transform.Up;
	const MouseState& mouseState = Input.GetMouseState();
	mouseState.GetWorldPos();
	if (mouseState.isLeftClickDown)
	{
		lastClickPosition = mouseState.GetWorldPos();
		leftClickDir = lastClickPosition - transform.position;
		leftClickDir.Normalize();
		dotProductValue = Vector3::Dot((Vector3)leftClickDir, (Vector3)dir);
		rotationAngle = std::acos(dotProductValue) * Mathf::Rad2Deg; 
		rotationDir = Vector3::Cross((Vector3)leftClickDir, (Vector3)dir).z > 0 ? 1.f : -1.f;
		transform.rotation += rotationDir * rotationAngle;
		movement->SetDirection(transform.Up);
	}

	if ((lastClickPosition - transform.position).Magnitude() < 0.25f)
	{
		movement->SetSpeed(0.f);
	}
	else
	{
		movement->SetSpeed(500.f);
	}

	//텍스트 출력용
	{
		wchar_t debugWSTR[50]{};
		swprintf_s(debugWSTR, L"position : %.03f, %.03f\n", transform.position.x, transform.position.y);
		debugTextRenderer->Text = debugWSTR;

		swprintf_s(debugWSTR, L"LeftClick Position : %.03f, %.03f\n", lastClickPosition.x, lastClickPosition.y);
		debugTextRenderer->Text += debugWSTR;

		swprintf_s(debugWSTR, L"Rotation Angle : %.03f\n", rotationAngle);
		debugTextRenderer->Text += debugWSTR;

		swprintf_s(debugWSTR, L"Rotation Dir : %.03f\n", rotationDir);
		debugTextRenderer->Text += debugWSTR;
	}
}


