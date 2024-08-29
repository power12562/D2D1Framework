#pragma once
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN    
#include <d2d1.h>

//custom message
/** InitDirect2D() 호출시 보내는 커스텀 메시지*/
#define WM_CUSTOM_INITD2D (WM_USER +1)

class WinGameApp
{
	static WinGameApp* RunApp; //현재 실행중인 앱
public:
	WinGameApp() = default;
	virtual ~WinGameApp() = default;

	void Initialize(HINSTANCE hinstance);
	void Run(); //기본 메시지 루프
	void Uninitialize();

	static void End() { RunApp->isEnd = true; } //루프 종료

	/**클라이언트를 화면 가운데로 위치 시킨다.*/
	static void WinToScrrenCenter(HWND hwnd);

	static HINSTANCE GetHinstance() { return hInstance; }

	static HWND GetHwnd() { return hwnd; };

	static void SetClientSize(const SIZE& size);
	static const SIZE& GetClientSize() { return size; } const

	static bool IsResize() { return isResize; }
	
protected:
	bool isDebug = false;

	/** 클래스 스타일. Initialize() 실행전에만 적용됩니다.*/
	UINT winClassStyle = CS_HREDRAW | CS_VREDRAW;

	/** 클라이언트 윈도우 스타일. Initialize() 실행전에만 적용됩니다.*/
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;

	/** 윈도우 클래스 구조체 이름. Initialize() 실행전에만 적용됩니다.*/
	LPCWSTR winClassName = L"D2D1_ENGINE";

	/** 윈도우 클라이언트 이름. Initialize() 실행전에만 적용됩니다.*/
	LPCWSTR windowName = L"DemoApp";

	/** 배경 색. 기본 값 : 검정*/
	D2D1_COLOR_F bgColor = D2D1::ColorF(D2D1::ColorF::Black);
private:
	/** 클라이언트 사이즈. 기본 값 : 1920, 1080*/
	static SIZE size;

	void WinInitialize(HINSTANCE hinstance);

	static bool isResize;
	static bool isMaxsize;
	bool isEnd = false;

	static HINSTANCE hInstance;
	static HWND hwnd;

	/**clientSize 변경시 값 수정해준다. WndProc에서만 처리한다. */
	static void ReSizeClient();

	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

