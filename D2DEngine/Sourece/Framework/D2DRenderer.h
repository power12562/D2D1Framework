#pragma once
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <wincodec.h>
#include <comdef.h>
#include <dwrite.h>

class D2DRenderer
{
public:
	/** D2D 초기화 여부*/
	static bool IsInit() { return isInit; }

	/** D2D 사용시 초기화*/
	static bool InitDirect2D();
	/** D2D 사용 종료*/
	static void UninitDirect2D();

	static ID2D1HwndRenderTarget& GetRenderTarget() { return  *pRenderTarget; }
	//static ID2D1Factory& GetD2DFactory() { return  *pD2DFactory; }

	static void BeginDraw();
	static void EndDraw();
	static void Clear(D2D1::ColorF color);
	static void DrawLine(
		D2D1_POINT_2F startPosition, D2D1_POINT_2F endPosition, 
		D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black), 
		float LineWidth = 0.5f
	);	

	static void DrawRect(
		const D2D1_VECTOR_2F& position, const D2D1_SIZE_F& size,
		D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black),
		bool rectFill = false
	);
	static void DrawRect(
		D2D1_RECT_F rectPoint,
		D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black),
		bool rectFill = false
	);

	/** 비트맵 포인터 생성*/
	static ID2D1Bitmap* CreateD2DBitmapFromFile(const wchar_t* filePath);

	/** 비트맵 그리기*/
	static void DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position);
	static void DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const D2D1_VECTOR_2F& scale);
	static void DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const float angle);
	static void DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const D2D1_VECTOR_2F& scale, const float angle);

	/** Vertex 회전 위치 리턴*/
	static D2D1_VECTOR_2F GetRotatedPoint(const D2D1_VECTOR_2F point, const float angle);

	/** Rect에 회전이 적용된 bounds 값 리턴*/
	static void GetRectBounds(D2D1_RECT_F& rect, const float angle);

	static float DegToRad(const float degree);
	static float RadToDeg(const float radian);

	/** 그릴 폰트를 생성합니다. 설치된 폰트만 사용 가능합니다.*/
	static IDWriteTextFormat* CreateD2DFont(const wchar_t* fontName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, float fontSize);

	/** 폰트 그리기.*/
	static void DrawTextW(const wchar_t* text, IDWriteTextFormat*& fontFormat, D2D1_RECT_F drawRect, D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black));

private:
	D2DRenderer() = default;
	~D2DRenderer() = default;

	static bool isInit;
	static ID2D1Factory* pD2DFactory;
	static ID2D1HwndRenderTarget* pRenderTarget;
	static ID2D1SolidColorBrush* pColorBrush;
	static IWICImagingFactory* pWICFactory;
	static IDWriteFactory* pDWriteFactory;

	static D2D1_VECTOR_2F GetRectOrigin(D2D1_RECT_F& rect, const float angle);

	static D2D1_SIZE_F GetDrawPos(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position);
	static D2D1_SIZE_F GetDrawPos(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const D2D1_VECTOR_2F& scale);
	static D2D1_SIZE_F GetDrawPos(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const float angle);
	static D2D1_SIZE_F GetDrawPos(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const D2D1_VECTOR_2F& scale, const float angle);

	static void DrawBitmap_(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_SIZE_F& position);
	static void DrawBitmap_(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_SIZE_F& position, const D2D1_SIZE_F& scale);
	static void DrawBitmap_(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_SIZE_F& position, const float angle, const D2D1_POINT_2F& rotPoint);
	static void DrawBitmap_(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_SIZE_F& position, const D2D1_SIZE_F& scale, const float angle, const D2D1_POINT_2F& rotPoint);
};



