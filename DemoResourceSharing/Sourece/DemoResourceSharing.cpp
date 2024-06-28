#include "DemoResourceSharing.h"
#include "Framework/SceneManager.h"
#include "Framework/D2DRenderer.h"
#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/GameObject/MainCamera.h"
#include "Core/Component/SpriteRenderer.h"

#include "Component/BackGround.h"
#include "Component/Run.h"
#include "Component/CameraMove.h"

#include <stack>

DemoResourceSharing::DemoResourceSharing()
{
#ifdef _DEBUG
	isDebug = true;
#endif // _DEBUG

}

DemoResourceSharing::~DemoResourceSharing()
{
	
}


void DemoResourceSharing::Render()
{
	__super::Render();
	static auto consolas = D2DRenderer::CreateD2DFont(L"Consolas");
	static wchar_t frameRate[150]{};
	swprintf_s
	(
		frameRate, _ARRAYSIZE(frameRate), 
		L"fps : %.0f\nVram : %llu\nAdd : ArrowUp, ArrowDown\nflip : ArrowLeft, ArrowRight, Space", 
		TimeSystem::Time.GetFrameRate(), D2DRenderer::GetUsedVram()
	);
	D2DRenderer::DrawTextW(frameRate, consolas, { 0,0, _ARRAYSIZE(frameRate) * consolas->GetFontSize(), consolas->GetFontSize() * 3 }, D2D1::ColorF(D2D1::ColorF::AliceBlue));
}

Scene1::Scene1()
{
	GameObjectBase* mainCamera = new MainCamera;
	mainCamera->AddComponent<CameraMove>();
	SceneManager::AddGameObject(mainCamera);

	GameObjectBase* bg = new GameObjectBase;
	bg->AddComponent<BackGround>();
	SceneManager::AddGameObject(bg);

	GameObjectBase* run = new GameObjectBase;
	run->AddComponent<Run>();
	SceneManager::AddGameObject(run);

}

Scene1::~Scene1()
{

}
