#include "DemoObjectCulling.h"
#include "Framework/SceneManager.h"
#include "Framework/D2DRenderer.h"
#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/GameObject/MainCamera.h"
#include "Core/Component/SpriteRenderer.h"
#include "Core/Component/Camera.h"

#include "Component/BackGround.h"
#include "Component/Run.h"
#include "Component/CameraMove.h"

#include <stack>

DemoObjectCulling::DemoObjectCulling()
{
#ifdef _DEBUG
	isDebug = true;
#endif // _DEBUG

}

DemoObjectCulling::~DemoObjectCulling()
{
	
}


void DemoObjectCulling::Render()
{
	using namespace InputSystem;

	__super::Render();
	GameObjectBase& mainCam = Camera::GetMainCamera()->gameObject;
	const Bounds& camBounds = mainCam.GetBounds();

	GameObjectBase& run = *SceneManager::FindGameObject(L"Run");
	const Bounds& runBounds = run.GetBounds();

	auto& mouseState = Input.GetMouseState();
	Vector2 mouseWorldPos = mouseState.GetWorldPos();
	
	static auto consolas = D2DRenderer::CreateD2DFont(L"Consolas");
	static wchar_t debug[200]{};
	swprintf_s
	(
		debug, _ARRAYSIZE(debug), 
		L"fps : %.0f\nVram : %llu\nAdd : ArrowUp, ArrowDown\nMoveCamera : w, a, s, d\nDrawObject = %d\nmousePos : %.1f, %.1f",
		//\nCameraBounds : %.1f, %.1f ,%.1f ,%.1f\nRunBounds : %.1f, %.1f ,%.1f ,%.1f\n", 
		TimeSystem::Time.GetFrameRate(), 
		D2DRenderer::GetUsedVram(), 
		SceneManager::GetRenderCount(), 
		(float)mouseWorldPos.x, (float)mouseWorldPos.y
		//,camBounds.leftTop.x, camBounds.leftTop.y, camBounds.rightBottom.x, camBounds.rightBottom.y,
		//runBounds.leftTop.x, runBounds.leftTop.y, runBounds.rightBottom.x, runBounds.rightBottom.y
	);
	D2DRenderer::DrawTextW(debug, consolas, { 0,0, _ARRAYSIZE(debug) * consolas->GetFontSize(), (float)GetClientSize().cy}, D2D1::ColorF(D2D1::ColorF::AliceBlue));
}

Scene1::Scene1()
{
	Camera::GetMainCamera()->gameObject.AddComponent<CameraMove>();

	GameObjectBase* bg = SceneManager::AddGameObject(L"BackGround");
	bg->AddComponent<BackGround>();
	
	GameObjectBase* run = SceneManager::AddGameObject(L"Run");
	run->AddComponent<Run>();

}

Scene1::~Scene1()
{

}
