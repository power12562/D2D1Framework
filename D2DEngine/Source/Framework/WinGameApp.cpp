﻿#include "WinGameApp.h"
#include "Framework/D2DRenderer.h"
#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"
#include "Framework/WorldManager.h"
#include "Framework/ColliderManager.h"
#include "Framework/GameObjectFactory.h"
#include "Framework/SoundSystem.h"

#include <Utility/Debug.h>

#include <Core/Scene/WorldBase.h>

#include <Core/GameObject/MainCamera.h>
#include "Core/Component/Transform.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Camera.h"
#include <Core/Component/InputBinding.h>
#include <Core/Component/Collider/Base/ColliderBase.h>

#include <clocale>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//static 변수
HINSTANCE WinGameApp::hInstance = NULL;
HWND WinGameApp::hwnd = NULL;
SIZE WinGameApp::size = {1920, 1080};
bool WinGameApp::isResize = false;
bool WinGameApp::isMaxsize = false;

WinGameApp* WinGameApp::RunApp = nullptr;

void WinGameApp::Initialize(HINSTANCE hinstance)
{
	setlocale(LC_ALL, "");
	if (isDebug)
	{
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	}

	// 컴포넌트 오브젝트 모델 (COM) 초기화.
	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	if(FAILED(hr))
	{
		_com_error er(hr);
		DEBUG_PRINT("%s", (const char*)er.ErrorMessage());
	}
	WinInitialize(hinstance);
	if (!D2DRenderer::InitDirect2D())
	{
		isEnd = true;
	}
	SoundSystem::FMODManager::Init();
	GameObjectFactory::RegisterGameObject("MainCamera", []()->GameObjectBase* {return new MainCamera; });
}

void WinGameApp::Uninitialize()
{
	if (isDebug)
	{
		FreeConsole();
	}
	D2DRenderer::ReleaseAllID2D1Bitmap();
	D2DRenderer::UninitDirect2D();
	CoUninitialize();
}

void WinGameApp::Run()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	RunApp = this;

	//게임용 루프	
	MSG msg;	
	if (WorldManager::nextWorld == nullptr)
	{
		WorldManager::LoadWorld<WorldBase>();
	}
	WorldManager::LoadNextWorld();
	
	Time.UpdateTime();
	while (!isEnd)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			if (msg.message == WM_KEYDOWN && !Input.IsKey(static_cast<KeyCode>(msg.wParam)))
			{
				Input.SetKeyDown(static_cast<KeyCode>(msg.wParam));
			}
			else if (msg.message == WM_SYSKEYDOWN && !Input.IsKey(static_cast<KeyCode>(msg.wParam)))
			{
				Input.SetKeyDown(static_cast<KeyCode>(msg.wParam));
			}
			else if (msg.message == WM_KEYUP && Input.IsKey(static_cast<KeyCode>(msg.wParam)))
			{
				Input.SetKeyUp(static_cast<KeyCode>(msg.wParam));
			}
			else if (msg.message == WM_SYSKEYUP && Input.IsKey(static_cast<KeyCode>(msg.wParam)))
			{
				Input.SetKeyUp(static_cast<KeyCode>(msg.wParam));
			}
			else
			{
				DispatchMessage(&msg);
			}
		}
		else if(!isEnd)
		{
			SoundSystem::FMODManager::system->update();
			Time.UpdateTime();
			Input.UpdateMouse();
			InputBinding::UpdateAllInputBinding();

			WorldManager::SortObjectList();

			WorldManager::Update();
			WorldManager::LateUpdate();
			ColliderManager::CheckCollision();

			WorldManager::UpdateMatrix();
			WorldManager::UpdateCullingBouds();
			D2DRenderer::BeginDraw();
			{
				D2DRenderer::Clear(bgColor);
				WorldManager::Render();
			}
			D2DRenderer::EndDraw();
								
			WorldManager::LoadNextWorld();
			WorldManager::DelObjectToSetList();	
			WorldManager::AddObjectToQList();
		
			Input.ResetInput();
		}
	}

	if (WorldManager::currentWorld)
	{
		WorldManager::UnloadWorld();
	}	
}


void WinGameApp::WinToScrrenCenter(HWND hwnd)
{
	int x, y, width, height;
	RECT rtDesk, rtWindow;
	GetWindowRect(GetDesktopWindow(), &rtDesk);
	GetWindowRect(hwnd, &rtWindow);
	width = rtWindow.right - rtWindow.left;
	height = rtWindow.bottom - rtWindow.top;
	x = (rtDesk.right - width) / 2;
	y = (rtDesk.bottom - height) / 2;
	MoveWindow(hwnd, x, y, width, height, TRUE);
}

void WinGameApp::SetClientSize(const SIZE& size)
{
	WinGameApp::size = size;
	MoveWindow(hwnd, 0, 0, size.cx, size.cy, TRUE);

	WinToScrrenCenter(GetHwnd());
}

void WinGameApp::WinInitialize(HINSTANCE hinstance)
{
	//static hInstance
	if (WinGameApp::hInstance == NULL)
	{
		WinGameApp::hInstance = hInstance;
	}

	// 윈도우 클래스 구조체 초기화
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = winClassStyle;
	wc.lpfnWndProc = WndProc;	// 윈도우 프로시저 함수
	wc.hInstance = hInstance;   // 인스턴스 핸들
	// NULL을 사용하면 현재 실행 중인 프로그램의 인스턴스 핸들을 사용하게 됩니다.두 번째 인자는 로드할 커서의 ID입니다.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = winClassName;

	// 윈도우 클래스 등록
	if (!RegisterClassEx(&wc))
	{
		int error = GetLastError();
		wchar_t errorStr[25]{};
		swprintf_s(errorStr, L"윈도우 클래스 등록 실패. 에러 : %d", error);

		MessageBox(NULL, errorStr, L"에러", MB_OK | MB_ICONERROR);
		isEnd = false;
		return;
	}

	// 원하는 크기가 조정되어 리턴
	SIZE clientSize = WinGameApp::size;
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, windowStyle, FALSE);

	// 윈도우 생성
	WinGameApp::hwnd = CreateWindowEx(
		0,
		winClassName,
		windowName,
		windowStyle,
		0, 0,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
		NULL, NULL, hInstance, NULL
	);

	if (!hwnd)
	{
		int error = GetLastError();
		wchar_t errorStr[25]{};

		swprintf_s(errorStr, L"윈도우 생성 실패. 에러 : %d", error);
		MessageBox(NULL, errorStr, L"에러", MB_OK | MB_ICONERROR);
		isEnd = false;
		return;
	}

	// 윈도우 표시
	ShowWindow(hwnd, 10);
	UpdateWindow(hwnd);
	
	if (isDebug)
	{
		RECT rc;
		GetClientRect(hwnd, &rc);
		int sx = rc.right - rc.left;
		int sy = rc.bottom - rc.top;
		printf("ClientSize : %d, %d\n", sx, sy);
	}
}

void WinGameApp::ReSizeClient()
{
	RECT rc;
	GetClientRect(hwnd, &rc);

	size = {rc.right - rc.left, rc.bottom - rc.top};	
}

// 윈도우 프로시저 함수 정의
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		WinGameApp::WinToScrrenCenter(hwnd);
		break;

	case WM_SIZE:
		switch (wParam)
		{	
		case SIZE_RESTORED:
			if (WinGameApp::isMaxsize)
			{
				WinGameApp::isMaxsize = false;
				SendMessage(hwnd, WM_EXITSIZEMOVE, 0, 0);
			}
			break;
		case SIZE_MAXIMIZED:
			WinGameApp::isMaxsize = true;
			[[fallthrough]];
		case SIZE_MAXSHOW:
			SendMessage(hwnd, WM_EXITSIZEMOVE, 0, 0);
			break;
		}
		break;

	case WM_EXITSIZEMOVE:
		WinGameApp::isResize = true;
		WinGameApp::ReSizeClient();
		D2DRenderer::InitDirect2D();
		break;

	case WM_CUSTOM_INITD2D:	//D2DInit 완전히 끝나면 처리되는 메시지
		D2DRenderer::ReloadAllID2D1Bitmap();
		Camera::ResetCameraPivot();
		WinGameApp::isResize = false;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

