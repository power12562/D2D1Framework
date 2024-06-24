#include "DemoResourceSharing.h"
#include "Framework/SceneManager.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Core/Component/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"

DemoResourceSharing::DemoResourceSharing()
{
#ifdef _DEBUG
	isDebug = true;
#endif // _DEBUG

}

DemoResourceSharing::~DemoResourceSharing()
{
	
}

void DemoResourceSharing::Update()
{
	__super::Update();
	size_t vram = D2DRenderer::GetUsedVram();
	printf("Vram = %ull\n", vram);
}

void DemoResourceSharing::Render()
{
	__super::Render();

}

Scene1::Scene1()
{
	SIZE screenSize = WinGameApp::GetClientSize();

	GameObjectBase* test1 = new GameObjectBase;
	test1->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	test1->AddComponent<SpriteRenderer>();
	test1->GetComponent<SpriteRenderer>().LoadImage(L"../Resource/moon.png");

	gameObjectList.push_back(test1); //0
}

Scene1::~Scene1()
{

}
