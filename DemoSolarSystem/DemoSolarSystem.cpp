#include "DemoSolarSystem.h"
#include "Core/Componet/SpriteRenderer.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Framework/InputSystem.h"
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
	bg->transform().position = Vector2{screenSize.cx * 0.5f, screenSize.cy * 0.5f};
	SpriteRenderer* sprite = bg->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/bg.png");

	GameObjectBase* sun = new GameObjectBase;
	sun->transform().scale = Vector2{0.3f, 0.3f};
	sun->transform().position = Vector2{screenSize.cx * 0.5f, screenSize.cy * 0.5f};
	sun->transform().rotation = 0;
	sprite = sun->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/Sun.png");

	GameObjectBase* earth = new GameObjectBase;
	earth->transform().SetParent(sun->transform());
	earth->transform().localPosition = Vector2{-300, 0};
	sprite = earth->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/earth.png");

	GameObjectBase* moon = new GameObjectBase;
	moon->transform().SetParent(earth->transform());
	moon->transform().localScale = Vector2{2.0f, 2.0f};
	moon->transform().localPosition = Vector2{150, 0};
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
	using namespace InputSystem;

	static const float sunMovespeed = 300.f;
	static const float sunRotSpeed = 25.f;
	static const float earthRotSpeed = -40.f;
	static const float moonRotSpeed = 60.f;

	gameObjectList[2]->transform().position = Vector2{ 320, 512 };

	printf("%.0f\n", Time.GetFrameRate());
	for (auto& obj : gameObjectList)
	{
		obj->Update();
	}

	gameObjectList[1]->transform().rotation += sunRotSpeed * Time.GetDeltatime();
	gameObjectList[2]->transform().localRotation += earthRotSpeed * Time.GetDeltatime();
	gameObjectList[3]->transform().localRotation += moonRotSpeed * Time.GetDeltatime();	
}

void DemoSolarSystem::Render()
{	
	for (auto& obj : gameObjectList)
	{
		obj->Render();
	}
}
