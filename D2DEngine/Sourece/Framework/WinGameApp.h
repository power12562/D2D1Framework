#pragma once
#include <Windows.h>

//custom message
#define WM_CUSTOM_INITD2D (WM_USER +1)

class WinGameApp
{
public:
	WinGameApp();
	virtual ~WinGameApp();

	void Initialize(HINSTANCE hinstance);
	void Uninitialize();

	/** 기본 메시지 루프*/
	void Run();
	void End() { isEnd = true; }

	virtual void Update() = 0;
	virtual void Render() = 0;

	/**클라이언트를 화면 가운데로 위치 시킨다.*/
	static void WinToScrrenCenter(HWND hwnd);

	static HINSTANCE GetHinstance() { return hInstance; }

	static HWND GetHwnd() { return hwnd; };

	static SIZE GetClientSize() { return size; }

	static bool IsResize() { return isResize; }
	
protected:
	bool isDebug = false;

private:
	void WinInitialize(HINSTANCE hinstance);

	static bool isResize;
	static bool isMaxsize;
	bool isEnd = false;

	/** 클라이언트 사이즈. 기본 값 : 1920, 1080*/
	static SIZE size;

	/** 클래스 스타일.*/
	const UINT winClassStyle = CS_HREDRAW | CS_VREDRAW;

	/** 클라이언트 윈도우 스타일.*/
	const DWORD windowStyle = WS_OVERLAPPEDWINDOW;

	/** 윈도우 클래스 구조체 이름*/
	const LPCWSTR winClassName = L"D2D1_ENGINE";

	/** 윈도우 클라이언트 이름*/
	const LPCWSTR windowName = L"DemoApp";

	static HINSTANCE hInstance;
	static HWND hwnd;

	/**clientSize 변경시 값 수정해준다. WndProc에서만 처리한다. */
	static void ReSizeClient();

	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

