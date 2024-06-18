#include "DemoSolarSystem.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Core/Componet/SpriteRenderer.h"
#include "Framework/TimeSystem.h"

DemoSolarSystem::DemoSolarSystem(HINSTANCE hinstance)
{
#ifdef _DEBUG
	isDebug = true;
#endif // _DEBUG

	SetClientSize({ 1240 , 1024 });

	Initialize(hinstance);

	auto screenSize = GetClientSize();

	GameObjectBase* bg = new GameObjectBase;
	bg->transform.position = { screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	SpriteRenderer* sprite = bg->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/bg.png");

	GameObjectBase* sun = new GameObjectBase;
	sun->transform.scale = { 0.3f, 0.3f };
	sun->transform.position = { screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	sun->transform.rotation = 0;
	sprite = sun->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/Sun.png");

	GameObjectBase* earth = new GameObjectBase;
	earth->SetParent(sun);
	earth->transform.localPosition = { -300, 0 };
	sprite = earth->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/earth.png");

	GameObjectBase* moon = new GameObjectBase;
	moon->SetParent(earth);
	moon->transform.localScale = { 2.0f, 2.0f };
	moon->transform.localPosition = { 150, 0 };
	sprite = moon->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/moon.png");

	gameObjectList.push_back(bg); //0
	gameObjectList.push_back(sun); //1
	gameObjectList.push_back(earth); //2
	gameObjectList.push_back(moon); //3
}

DemoSolarSystem::~DemoSolarSystem()
{
	for (auto& obj : gameObjectList)
	{
		delete obj;
	}
}

void DemoSolarSystem::Update()
{
	using namespace TimeSystem;

	static const float sunRotSpeed = 25.f;
	static const float earthRotSpeed = -40.f;
	static const float moonRotSpeed = 60.f;

	printf("%.0f\n", Time.GetFrameRate());
	for (auto& obj : gameObjectList)
	{
		obj->Update();
	}
	gameObjectList[1]->transform.rotation += sunRotSpeed * Time.GetDeltatime();
	gameObjectList[2]->transform.localRotation += earthRotSpeed * Time.GetDeltatime();
	gameObjectList[3]->transform.localRotation += moonRotSpeed * Time.GetDeltatime();
}

void DemoSolarSystem::Render()
{	
	for (auto& obj : gameObjectList)
	{
		obj->Render();
	}
}
