#pragma once
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <wincodec.h>
#include <comdef.h>
#include <dwrite.h>
#include <dxgi1_4.h>
#include <map>
#include <string>

class D2DRenderer
{
public:
	/** D2D 초기화 여부*/
	static bool IsInit() { return isInit; }

	/** D2D 사용시 초기화*/
	static bool InitDirect2D();
	/** D2D 사용 종료*/
	static void UninitDirect2D();

	static ID2D1HwndRenderTarget& GetRenderTarget() { return *pRenderTarget; }
	//static ID2D1Factory& GetD2DFactory() { return  *pD2DFactory; }

	static void BeginDraw();
	static void EndDraw();
	static void Clear(const D2D1_COLOR_F& color);
	static void DrawLine(
		const D2D1_POINT_2F& startPosition, const D2D1_POINT_2F& endPosition, 
		const D2D1_COLOR_F& color = D2D1::ColorF(D2D1::ColorF::Black), 
		float LineWidth = 0.5f
	);	

	static void DrawRect(
		const D2D1_VECTOR_2F& position, const D2D1_SIZE_F& size,
		const D2D1_COLOR_F& color = D2D1::ColorF(D2D1::ColorF::Black),
		bool rectFill = false
	);
	static void DrawRect(
		const D2D1_RECT_F& rectPoint,
		const D2D1_COLOR_F& color = D2D1::ColorF(D2D1::ColorF::Black),
		bool rectFill = false
	);

	/** 비트맵 포인터 생성*/
	static ID2D1Bitmap* CreateD2DBitmapFromFile(const wchar_t* filePath);

	/** 생성된 비트맵 해제*/
	static void ReleaseD2D1Bitmap(const wchar_t* filePath);

	/** 비트맵 그리기*/
	static void DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_MATRIX_3X2_F& worldMatrix);
	static void DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_MATRIX_3X2_F& worldMatrix, const D2D1_RECT_F& sourceRect);
	static void DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_MATRIX_3X2_F& worldMatrix,const D2D1_RECT_F& outRect ,const D2D1_RECT_F& sourceRect);

	/** Vertex 회전 위치 리턴*/
	static D2D1_VECTOR_2F GetRotatedPoint(const D2D1_VECTOR_2F point, const float angle);

	/** Rect에 회전이 적용된 bounds 값 리턴*/
	static void GetRectBounds(D2D1_RECT_F& rect, const float angle);

	static float DegToRad(const float degree);
	static float RadToDeg(const float radian);

	/**
	 * @brief 폰트정보의 포인터를 생성합니다. 설치된 폰트만 사용 가능합니다.
	 * @param fontName : 사용할 폰트 이름.
	 * @param fontWeight : 텍스트 개체의 글꼴 두께 값입니다.
	 * @param fontStyle : 글꼴 스타일을 나타내는 값입니다.
	 * @param fontStretch : 글꼴 스트레치를 나타내는 값입니다.
	 * @param fontSize : DIP 단위로 된 글꼴의 논리적 크기입니다. DIP는 1/96 인치와 같습니다.
	 * @return 생성된 폰트의 정보를 가지고 있는 포인터 객체.
	 */
	static IDWriteTextFormat* CreateD2DFont(
		const wchar_t* fontName, 
		float fontSize = 30.f,
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL	
	);

	/** 폰트 그리기.*/
	static void DrawTextW(const wchar_t* text, IDWriteTextFormat*& fontFormat, const D2D1_RECT_F& drawRect, const D2D1_COLOR_F& color = D2D1::ColorF(D2D1::ColorF::Black));

	/** Vram 사용량 확인하기.*/
	static size_t GetUsedVram();

private:
	D2DRenderer() = default;
	~D2DRenderer() = default;

	static bool isInit;
	static ID2D1Factory* pD2DFactory;
	static ID2D1HwndRenderTarget* pRenderTarget;
	static ID2D1SolidColorBrush* pColorBrush;
	static IWICImagingFactory* pWICFactory;
	static IDWriteFactory* pDWriteFactory;
	static IDXGIFactory* pDXGIFactory;
	static IDXGIAdapter3* pDXGIAdapter;

	static D2D1_VECTOR_2F GetRectOrigin(D2D1_RECT_F& rect, const float angle);

	static D2D1_SIZE_F GetDrawPos(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const D2D1_VECTOR_2F& scale, const float angle);

	static std::map<std::wstring, ID2D1Bitmap*> ID2D1BitmapResourceMap; //리소스 맵

	/** 로드된 모든 리소스 삭제*/
	static void ReleaseAllID2D1Bitmap();
};



