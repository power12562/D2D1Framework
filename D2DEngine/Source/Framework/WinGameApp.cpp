#include "WinGameApp.h"
#include "Framework/D2DRenderer.h"
#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"
#include "Framework/SceneManager.h"
#include "Core/Component/SpriteRenderer.h"
#include "Core/Component/Camera.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//static 변수
HINSTANCE WinGameApp::hInstance = NULL;
HWND WinGameApp::hwnd = NULL;
SIZE WinGameApp::size = {1920, 1080};
bool WinGameApp::isResize = false;
bool WinGameApp::isMaxsize = false;


void WinGameApp::Initialize(HINSTANCE hinstance)
{
	WinInitialize(hinstance);

	if (isDebug)
	{
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	}

	if (!D2DRenderer::InitDirect2D())
	{
		isEnd = true;
	}
}

void WinGameApp::Uninitialize()
{
	if (isDebug)
	{
		FreeConsole();
	}
	D2DRenderer::UninitDirect2D();
}

void WinGameApp::Run()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	//게임용 루프	
	MSG msg;
	Time.UpdateTime();
	SceneManager::AddObjectToQList();
	while (!isEnd)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			if (msg.message == WM_KEYDOWN && !Input.IsKey(static_cast<KeyCode>(msg.wParam)))
			{
				Input.SetKeyDown(static_cast<KeyCode>(msg.wParam));
			}
			else if (msg.message == WM_KEYUP && Input.IsKey(static_cast<KeyCode>(msg.wParam)))
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
			Time.UpdateTime();
			Input.UpdateMouse();

			SceneManager::SortObjectList();
			Update();		
			LateUpdate();
			D2DRenderer::BeginDraw();
			D2DRenderer::Clear(bgColor);
			Render();
			D2DRenderer::EndDraw();
			
			SceneManager::AddObjectToQList();
			SceneManager::DelObjectToSetList();

			Input.ResetInput();
		}
	}

	if (SceneManager::currentScene)
	{
		SceneManager::UnloadScene();
	}	
}

#pragma region WinGameApp->Run() 게임 루프에서 호출되는 함수들.

void WinGameApp::Update()
{
	SceneManager::Update();
}

void WinGameApp::LateUpdate()
{
	SceneManager::LateUpdate();
}

void WinGameApp::Render()
{
	SceneManager::Render();
}

#pragma endregion

void WinGameApp::WinToScrrenCenter(HWND hwnd)
{
	int x, y, width, height;
	RECT rtDesk, rtWindow;
	GetWindowRect(GetDesktopWindow(), &rtDesk);
	GetWindowRect(hwnd, &rtWindow);
	width = rtWindow.right - rtWindow.left;
	height = rtWindow.bottom - rtWindow.left;
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
		case SIZE_MAXSHOW:
			SendMessage(hwnd, WM_EXITSIZEMOVE, 0, 0);
		}
		break;

	case WM_EXITSIZEMOVE:
		WinGameApp::isResize = true;
		WinGameApp::ReSizeClient();
		D2DRenderer::InitDirect2D();
		break;

	case WM_CUSTOM_INITD2D:	
		SpriteRenderer::ReloadImage();
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

