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
	bg->transform().position = Vector2{screenSize.cx * 0.5f, screenSize.cy * 0.5f};
	bg->AddComponent<SpriteRenderer>();
	bg->GetComponent<SpriteRenderer>().LoadImage(L"Resource/bg.png");

	GameObjectBase* sun = new GameObjectBase;
	sun->transform().scale = Vector2{0.3f, 0.3f};
	sun->transform().position = Vector2{screenSize.cx * 0.5f, screenSize.cy * 0.5f};
	sun->transform().rotation = 0;
	sun->AddComponent<SpriteRenderer>();
	sun->GetComponent<SpriteRenderer>().LoadImage(L"Resource/Sun.png");
	
	GameObjectBase* earth = new GameObjectBase;
	earth->transform().SetParent(sun->transform());
	earth->transform().localPosition = Vector2{1000.f, 0.f};
	earth->AddComponent<SpriteRenderer>();
	earth->GetComponent<SpriteRenderer>().LoadImage(L"Resource/earth.png");

	GameObjectBase* moon = new GameObjectBase;
	moon->transform().SetParent(earth->transform());
	moon->transform().scale = Vector2{1.0f, 1.0f};
	moon->transform().localPosition = Vector2{500.f, 0.f};
	moon->AddComponent<SpriteRenderer>();
	moon->GetComponent<SpriteRenderer>().LoadImage(L"Resource/moon.png");

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

	printf("%.0f\n", Time.GetFrameRate());
	for (auto& obj : gameObjectList)
	{
		obj->Update();
	}

	gameObjectList[1]->transform().rotation += sunRotSpeed * Time.GetDeltatime();
	gameObjectList[2]->transform().localRotation += earthRotSpeed * Time.GetDeltatime();
	gameObjectList[3]->transform().localRotation += moonRotSpeed * Time.GetDeltatime();

	if (Input.IsKey(KeyCode::UpArrow))
	{
		gameObjectList[1]->transform().position += Vector2::Up *sunMovespeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::DownArrow))
	{
		gameObjectList[1]->transform().position += Vector2::Down * sunMovespeed * Time.GetDeltatime();
	}
	if (Input.IsKey(KeyCode::LeftArrow))
	{
		gameObjectList[1]->transform().position += Vector2::Left * sunMovespeed * Time.GetDeltatime();
	}
	else if (Input.IsKey(KeyCode::RightArrow))
	{
		gameObjectList[1]->transform().position += Vector2::Right * sunMovespeed * Time.GetDeltatime();
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
	const Vector2 debugPos = gameObjectList[3]->transform().position;
	swprintf_s(objPos, _ARRAYSIZE(objPos), L"position.x : %.03f\nposition.y : %.03f", debugPos.x, debugPos.y);
	D2DRenderer::DrawTextW(objPos, textFont, {0,0,500,500}, D2D1::ColorF(D2D1::ColorF::AliceBlue));
	
}
