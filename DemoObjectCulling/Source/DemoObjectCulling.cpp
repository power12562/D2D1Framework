#include "DemoObjectCulling.h"
#include "Framework/WorldManager.h"
#include "Framework/D2DRenderer.h"
#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/GameObject/Base/GameObjectUI.h"
#include "Core/GameObject/MainCamera.h"
#include "Core/Component/SpriteRenderer.h"
#include "Core/Component/Camera.h"

#include "Component/BackGround.h"
#include "Component/Run.h"
#include "Component/CameraMove.h"
#include "Component/DebugText.h"

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
	__super::Render();
}

Scene1::Scene1()
{
	Camera::GetMainCamera()->gameObject.AddComponent<CameraMove>();

	GameObjectBase* bg = WorldManager::AddGameObject(L"BackGround");
	bg->AddComponent<BackGround>();
	
	GameObjectBase* run = WorldManager::AddGameObject(L"Run");
	run->AddComponent<Run>();

	GameObjectBase* debug = WorldManager::AddGameObject<GameObjectUI>(L"debug");
	debug->AddComponent<DebugText>();
	debug->transform.SetParent(Camera::GetMainCamera()->gameObject.transform);
}

Scene1::~Scene1()
{

}
