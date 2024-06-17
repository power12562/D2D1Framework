#include "DemoSolarSystem.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Core/Componet/SpriteRenderer.h"

DemoSolarSystem::DemoSolarSystem(HINSTANCE hinstance)
{
	Initialize(hinstance);

	auto screenSize = GetClientSize();

	GameObjectBase* bg = new GameObjectBase;
	bg->transform.position = { screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	SpriteRenderer* sprite = bg->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/bg.png");

	GameObjectBase* sun = new GameObjectBase;
	sun->transform.position = { screenSize.cx * 0.5f, screenSize.cy * 0.5f };
	sprite = sun->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/Sun.png");

	GameObjectBase* earth = new GameObjectBase;
	earth->SetParent(sun);
	earth->transform.position = { 500, 0 };
	sprite = earth->AddComponent<SpriteRenderer>();
	sprite->LoadImage(L"Resource/earth.png");

	GameObjectBase* moon = new GameObjectBase;
	moon->SetParent(earth);
	moon->transform.position = { 300, 0 };
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
	for (auto& obj : gameObjectList)
	{
		obj->Update();
	}
}

void DemoSolarSystem::Render()
{
	for (auto& obj : gameObjectList)
	{
		obj->Render();
	}
}
