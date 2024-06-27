#include "DemoSolarSystem.h"
#include "Core/Component/SpriteRenderer.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"

DemoSolarSystem::DemoSolarSystem(HINSTANCE hinstance)
{
#ifdef _DEBUG
	isDebug = true;
#endif // _DEBUG

	SetClientSize({ 1240 , 1024 });

	Initialize(hinstance);

	auto screenSize = GetClientSize();

	GameObjectBase* bg = new GameObjectBase;
	bg->GetTransform().position = Vector2{screenSize.cx * 0.5f, screenSize.cy * 0.5f};
	bg->AddComponent<SpriteRenderer>();
	bg->GetComponent<SpriteRenderer>().LoadImage(L"Resource/bg.png");

	GameObjectBase* sun = new GameObjectBase;
	sun->GetTransform().scale = Vector2{0.3f, 0.3f};
	sun->GetTransform().position = Vector2{screenSize.cx * 0.5f, screenSize.cy * 0.5f};
	sun->AddComponent<SpriteRenderer>();
	sun->GetComponent<SpriteRenderer>().LoadImage(L"Resource/Sun.png");
	
	GameObjectBase* earth = new GameObjectBase;
	earth->GetTransform().SetParent(sun->GetTransform());
	earth->GetTransform().localPosition = Vector2{1000.f, 0.f};
	earth->AddComponent<SpriteRenderer>();
	earth->GetComponent<SpriteRenderer>().LoadImage(L"Resource/earth.png");

	GameObjectBase* moon = new GameObjectBase;
	moon->GetTransform().SetParent(earth->GetTransform());
	moon->GetTransform().localPosition = Vector2{450.f, 0.f};
	moon->GetTransform().localScale = Vector2{1.5f, 1.5f};
	moon->AddComponent<SpriteRenderer>();
	moon->GetComponent<SpriteRenderer>().LoadImage(L"Resource/moon.png");

	gameObjectList.push_back(bg); //0
	gameObjectList.push_back(sun); //1
	gameObjectList.push_back(earth); //2
	gameObjectList.push_back(moon); //3

	/*
	for (int i = 0; i < 10000; i++)
	{
		GameObjectBase* moon = new GameObjectBase;
		moon->transform().SetParent(earth->transform());
		moon->transform().localPosition = Vector2{ 450.f + i, 0.f };
		moon->transform().localScale = Vector2{ 1.5f, 1.5f };
		moon->AddComponent<SpriteRenderer>();
		moon->GetComponent<SpriteRenderer>().LoadImage(L"Resource/moon.png");

		gameObjectList.push_back(moon);
	}
	*/
}

DemoSolarSystem::~DemoSolarSystem()
{

}

void DemoSolarSystem::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	static const float sunMovespeed = 300.f;
	static const float sunRotSpeed = 25.f;
	static const float earthRotSpeed = 40.f;
	static const float moonRotSpeed = 60.f;

	printf("%.0f\n", Time.GetFrameRate());
	for (auto& obj : gameObjectList)
	{
		obj->Update();
	}

	gameObjectList[1]->GetTransform().rotation += sunRotSpeed * Time.GetDeltatime();
	gameObjectList[2]->GetTransform().localRotation += earthRotSpeed * Time.GetDeltatime();
	gameObjectList[3]->GetTransform().localRotation += moonRotSpeed * Time.GetDeltatime();

	if (Input.IsKey(KeyCode::UpArrow))
	{
		gameObjectList[1]->GetTransform().position += Vector2::Up *sunMovespeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::DownArrow))
	{
		gameObjectList[1]->GetTransform().position += Vector2::Down * sunMovespeed * Time.GetDeltatime();
	}
	if (Input.IsKey(KeyCode::LeftArrow))
	{
		gameObjectList[1]->GetTransform().position += Vector2::Left * sunMovespeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::RightArrow))
	{
		gameObjectList[1]->GetTransform().position += Vector2::Right * sunMovespeed * Time.GetDeltatime();
	}

}

void DemoSolarSystem::Render()
{	
	for (auto& obj : gameObjectList)
	{
		obj->Render();
	}
	static auto textFont = D2DRenderer::CreateD2DFont(L"Consolas", 40.f);
	wchar_t objPos[45];	
	const Vector2 debugPos = gameObjectList[1]->GetTransform().position;
	swprintf_s(objPos, _ARRAYSIZE(objPos), L"position.x : %.03f\nposition.y : %.03f", debugPos.x, debugPos.y);
	D2DRenderer::DrawTextW(objPos, textFont, {0,0,500,500}, D2D1::ColorF(D2D1::ColorF::AliceBlue));
	
}
