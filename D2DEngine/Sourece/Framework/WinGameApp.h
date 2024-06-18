#pragma once
#include <Windows.h>
#include <d2d1.h>

//custom message
/** InitDirect2D() 호출시 보내는 커스텀 메시지*/
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

	static void SetClientSize(const SIZE& size);
	static SIZE GetClientSize() { return size; }

	static bool IsResize() { return isResize; }
	
protected:
	bool isDebug = false;

	/** 클래스 스타일.*/
	const UINT winClassStyle = CS_HREDRAW | CS_VREDRAW;

	/** 클라이언트 윈도우 스타일.*/
	const DWORD windowStyle = WS_OVERLAPPEDWINDOW;

	/** 윈도우 클래스 구조체 이름*/
	const LPCWSTR winClassName = L"D2D1_ENGINE";

	/** 윈도우 클라이언트 이름*/
	const LPCWSTR windowName = L"DemoApp";

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

