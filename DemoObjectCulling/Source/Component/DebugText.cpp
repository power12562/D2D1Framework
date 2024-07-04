#include "DebugText.h"

#include "Framework/InputSystem.h"
#include "Framework/WorldManager.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"
#include "Core/Component/TextRenderer.h"

DebugText::DebugText(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

DebugText::~DebugText()
{

}

void DebugText::Start()
{
	textRenderer = &gameObject.AddComponent<TextRenderer>();
	textRenderer->TextColor = ColorF(ColorF::White);
}

void DebugText::Update()
{
	using namespace InputSystem;

	GameObjectBase& mainCam = Camera::GetMainCamera()->gameObject;
	const Bounds& camBounds = mainCam.bounds;

	GameObjectBase& run = *WorldManager::FindGameObject(L"Run");
	const Bounds& runBounds = run.bounds;

	auto& mouseState = Input.GetMouseState();
	Vector2 mouseWorldPos = mouseState.GetWorldPos();

	textRenderer->SetFont(L"Consolas");
	swprintf_s
	(
		debugText, _ARRAYSIZE(debugText),
		L"fps : %.0f\nVram : %llu\nAdd : ArrowUp, ArrowDown\nMoveCamera : w, a, s, d\nDrawObject = %d\nmousePos : %.3f, %.3f",
		//\nCameraBounds : %.1f, %.1f ,%.1f ,%.1f\nRunBounds : %.1f, %.1f ,%.1f ,%.1f\n", 
		TimeSystem::Time.GetFrameRate(),
		D2DRenderer::GetUsedVram(),
		WorldManager::GetRenderCount(),
		(float)mouseWorldPos.x, (float)mouseWorldPos.y
		//,camBounds.leftTop.x, camBounds.leftTop.y, camBounds.rightBottom.x, camBounds.rightBottom.y,
		//runBounds.leftTop.x, runBounds.leftTop.y, runBounds.rightBottom.x, runBounds.rightBottom.y
	);
	textRenderer->Text = debugText;
}
