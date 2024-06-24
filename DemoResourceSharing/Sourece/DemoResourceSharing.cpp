#include "DemoResourceSharing.h"
#include "Framework/SceneManager.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Core/Component/SpriteRenderer.h"

DemoResourceSharing::DemoResourceSharing()
{
#ifdef _DEBUG
	isDebug = true;
#endif // _DEBUG

}

DemoResourceSharing::~DemoResourceSharing()
{
	
}

Scene1::Scene1()
{
	SIZE screenSize = WinGameApp::GetClientSize();

	GameObjectBase* bg = new GameObjectBase;
	bg->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	bg->AddComponent<SpriteRenderer>();
	bg->GetComponent<SpriteRenderer>().LoadImage(L"../Resource/bg.png");

	GameObjectBase* sun = new GameObjectBase;
	sun->transform().scale = Vector2{ 0.3f, 0.3f };
	sun->transform().position = Vector2{ screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	sun->transform().rotation = 0;
	sun->AddComponent<SpriteRenderer>();
	sun->GetComponent<SpriteRenderer>().LoadImage(L"../Resource/Sun.png");

	GameObjectBase* earth = new GameObjectBase;
	earth->transform().SetParent(sun->transform());
	earth->transform().localPosition = Vector2{ 1000.f, 0.f };
	earth->AddComponent<SpriteRenderer>();
	earth->GetComponent<SpriteRenderer>().LoadImage(L"../Resource/earth.png");

	GameObjectBase* moon = new GameObjectBase;
	moon->transform().SetParent(earth->transform());
	moon->transform().localPosition = Vector2{ 500.f, 0.f };
	moon->AddComponent<SpriteRenderer>();
	moon->GetComponent<SpriteRenderer>().LoadImage(L"../Resource/moon.png");

	gameObjectList.push_back(bg); //0
	gameObjectList.push_back(sun); //1
	gameObjectList.push_back(earth); //2
	gameObjectList.push_back(moon); //3
}

Scene1::~Scene1()
{

}
