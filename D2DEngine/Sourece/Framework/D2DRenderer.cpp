#include "D2DRenderer.h"
#include "WinGameApp.h"
#include <directxmath.h>
#include <iostream>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"dxgi.lib")

using namespace D2D1;

//static 맴버
bool D2DRenderer::isInit = false;	

// D2D 개체 인터페이스 포인터 변수
ID2D1Factory* D2DRenderer::pD2DFactory = NULL; //rendertarget 생성을 위한 factory
ID2D1HwndRenderTarget* D2DRenderer::pRenderTarget = NULL;

ID2D1SolidColorBrush* D2DRenderer::pColorBrush = NULL;

IWICImagingFactory* D2DRenderer::pWICFactory = NULL; //bitmap 생성을 위한 factory

IDWriteFactory* D2DRenderer::pDWriteFactory = NULL; //text 생성을 위한 factory

IDXGIFactory* D2DRenderer::pDXGIFactory = NULL;
IDXGIAdapter3* D2DRenderer::pDXGIAdapter = NULL;

//중복 로드 방지용 리소스 맵
std::map<std::wstring, ID2D1Bitmap*> D2DRenderer::ID2D1BitmapResourceMap;

bool D2DRenderer::InitDirect2D()
{
	HWND hwnd = GetActiveWindow();

	UninitDirect2D();

	ReleaseAllID2D1Bitmap();
	
	HRESULT hr = S_OK;
	// 컴포넌트 오브젝트 모델 (COM) 초기화.
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return FALSE;

	/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
		이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
		DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
	*/
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"Error : InitDirect2D", MB_OK);
		return FALSE;
	}

	/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
	*/
	RECT rc;
	GetClientRect(hwnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	// Create a Direct2D render target.
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&pRenderTarget);

	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"Error : InitDirect2D", MB_OK);
		return FALSE;
	}
	
	//CreateBrush
	hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pColorBrush);

	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"Error : InitDirect2D", MB_OK);
		return FALSE;
	}

    // Create WIC factory
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pWICFactory)
	);
	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"Error : InitDirect2D", MB_OK);
		return FALSE;
	}

	// DirectWrite 팩터리를 만듭니다.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory));

	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"Error : InitDirect2D", MB_OK);
		return FALSE;
	}

	// VRAM 정보얻기 위한 개체 생성
	if (SUCCEEDED(hr))
	{
		// Create DXGI factory
		hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&pDXGIFactory);
	}
	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"Error : InitDirect2D", MB_OK);
		return FALSE;
	}

	if (SUCCEEDED(hr))
	{
		pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&pDXGIAdapter));
	}
	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"Error : InitDirect2D", MB_OK);
		return FALSE;
	}

	SendMessage(hwnd, WM_CUSTOM_INITD2D, 0, 0);
	isInit = true;
	return TRUE;
}

void D2DRenderer::UninitDirect2D()
{
	if (isInit == false)
		return;

	if (pDXGIAdapter)
	{
		pDXGIAdapter->Release();
		pDXGIAdapter = nullptr;
	}

	if (pDXGIFactory)
	{
		pDXGIFactory->Release();
		pDXGIFactory = nullptr;
	}

	if (pDWriteFactory)
	{
		pDWriteFactory->Release();
		pDWriteFactory = nullptr;
	}

	if (pColorBrush)
	{
		pColorBrush->Release();
		pColorBrush = nullptr;
	}

	if (pRenderTarget)
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}

	if (pD2DFactory)
	{
		pD2DFactory->Release();
		pD2DFactory = nullptr;
	}

	if (pWICFactory)
	{
		pWICFactory->Release();
		pWICFactory = nullptr;
	}

	CoUninitialize();
}

void D2DRenderer::BeginDraw()
{
	pRenderTarget->BeginDraw();
}

void D2DRenderer::EndDraw()
{
	HRESULT hr = pRenderTarget->EndDraw();
	if (FAILED(hr))
	{
		_com_error err(hr);
		if (0x88990001 != hr) //d2d 초기화 중에는 에러 예외 처리
		{
			::MessageBox(GetActiveWindow(), err.ErrorMessage(), L"Error : D2DEndDraw", MB_OK);
		}		
	}
}

void D2DRenderer::Clear(const D2D1_COLOR_F& color)
{
	pRenderTarget->Clear(color);
}

void D2DRenderer::DrawLine(
	const D2D1_POINT_2F& startPosition, const D2D1_POINT_2F& endPosition,
	const D2D1_COLOR_F& color,
	float LineWidth
)
{
	if (pColorBrush == nullptr)
		return;

	pColorBrush->SetColor(color);

	pRenderTarget->DrawLine(
		startPosition,
		endPosition,
		pColorBrush, 
		LineWidth
	);
}

void D2DRenderer::DrawRect(const D2D1_VECTOR_2F& position, const D2D1_SIZE_F& rectSize, const D2D1_COLOR_F& color, bool rectFill)
{
	if (pColorBrush == nullptr)
		return;

	float halfWidth = rectSize.width * 0.5f;
	float halfHeight = rectSize.height * 0.5f;

	D2D1_RECT_F rectPoint{};
	rectPoint.left = position.x - halfWidth;
	rectPoint.top = position.y - halfHeight;
	rectPoint.right = position.x + halfWidth;
	rectPoint.bottom = position.y + halfHeight;

	pColorBrush->SetColor(color);

	if (rectFill)
	{
		pRenderTarget->FillRectangle(rectPoint, pColorBrush);
	}
	else
	{
		pRenderTarget->DrawRectangle(rectPoint, pColorBrush);
	}
}

void D2DRenderer::DrawRect(const D2D1_RECT_F& rectPoint,const D2D1_COLOR_F& color, bool rectFill)
{

	if (pColorBrush == nullptr)
		return;

	pRenderTarget->SetTransform(Matrix3x2F::Identity());

	pColorBrush->SetColor(color);

	if (rectFill)
	{
		pRenderTarget->FillRectangle(rectPoint, pColorBrush);
	}
	else
	{
		pRenderTarget->DrawRectangle(rectPoint, pColorBrush);
	}

}

ID2D1Bitmap* D2DRenderer::CreateD2DBitmapFromFile(const wchar_t* filePath)
{
	auto iter = ID2D1BitmapResourceMap.find(filePath);
	if (iter != ID2D1BitmapResourceMap.end()) //end가 아니면 찾음
	{
		iter->second->AddRef();
		return iter->second;
	}

	HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = pWICFactory->CreateDecoderFromFilename(
		filePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	ID2D1Bitmap* pID2D1Bitmap = nullptr;
	if (SUCCEEDED(hr))
	{
		hr = pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &pID2D1Bitmap);
	}

	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	if (SUCCEEDED(hr))
	{
		ID2D1BitmapResourceMap[filePath] = pID2D1Bitmap;
		return pID2D1Bitmap;
	}		
	else
	{		
		_com_error err(hr);
		std::wstring message = err.ErrorMessage();
		message += L"\n\"";
		message += filePath;
		message += L"\"";
		::MessageBox(GetActiveWindow(), message.c_str(), L"ERROR", MB_OK);
		return nullptr;
	}

}

void D2DRenderer::ReleaseD2D1Bitmap(const wchar_t* filePath)
{
	auto iter = ID2D1BitmapResourceMap.find(filePath);
	if (iter != ID2D1BitmapResourceMap.end())
	{
		ULONG refCount = iter->second->Release();
		if (refCount == 0)
		{
			ID2D1BitmapResourceMap.erase(iter);
		}
	}
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_MATRIX_3X2_F& worldMatrix)
{
	pRenderTarget->SetTransform(worldMatrix);
	pRenderTarget->DrawBitmap(ID2D1Bitmap);
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_MATRIX_3X2_F& worldMatrix, const D2D1_RECT_F& sourceRect)
{
	pRenderTarget->SetTransform(worldMatrix);
	pRenderTarget->DrawBitmap(ID2D1Bitmap, NULL, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourceRect);
}


void D2DRenderer::DrawBitmap(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_MATRIX_3X2_F& worldMatrix,const D2D1_RECT_F& outRect,const D2D1_RECT_F& sourceRect)
{
	pRenderTarget->SetTransform(worldMatrix);
	pRenderTarget->DrawBitmap(ID2D1Bitmap, outRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourceRect);
}

D2D1_VECTOR_2F D2DRenderer::GetRotatedPoint(const D2D1_VECTOR_2F point, const float angle)
{
	float radian = DirectX::XMConvertToRadians(angle);

	float cos = cosf(radian);
	float sin = sinf(radian);

	float rotX = point.x * cos - point.y * sin;
	float rotY = point.x * sin + point.y * cos;

	return D2D1_VECTOR_2F{ rotX , rotY };
}

void D2DRenderer::GetRectBounds(D2D1_RECT_F& rect, const float angle)
{
	D2D1_VECTOR_2F point[4];
	point[0].x = rect.left;
	point[0].y = rect.top;

	point[1].x = rect.left;
	point[1].y = rect.bottom;

	point[2].x = rect.right;
	point[2].y = rect.top;

	point[3].x = rect.right;
	point[3].y = rect.bottom;

	for (int i = 0; i < 4; i++)
	{
		point[i] = GetRotatedPoint(point[i], angle);
	}
	D2D1_VECTOR_2F min = { FLT_MAX, }, max = { FLT_MIN, };
	for (int i = 0; i < 4; i++)
	{
		min.x = (min.x > point[i].x) ? point[i].x : min.x;
		min.y = (min.y > point[i].y) ? point[i].y : min.y;

		max.x = (max.x < point[i].x) ? point[i].x : max.x;
		max.y = (max.y < point[i].y) ? point[i].y : max.y;
	}

	rect.left = min.x;
	rect.top = min.y;
	rect.right = max.x;
	rect.bottom = max.y;
}

float D2DRenderer::DegToRad(const float degree)
{
	return DirectX::XMConvertToRadians(degree);
}

float D2DRenderer::RadToDeg(const float radian)
{
	return DirectX::XMConvertToDegrees(radian);
}

IDWriteTextFormat* D2DRenderer::CreateD2DFont(const wchar_t* fontName, float fontSize, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch)
{
	IDWriteTextFormat* pDWriteTextFormat = nullptr;

	// DirectWrite 텍스트 형식 개체를 만듭니다.
	HRESULT hr = pDWriteFactory->CreateTextFormat(
		fontName, // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		NULL,
		fontWeight,
		fontStyle,
		fontStretch,
		fontSize,   // Font Size
		L"", //locale
		&pDWriteTextFormat
	);
	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(GetActiveWindow(), err.ErrorMessage(), L"Error CreateD2DFont", MB_OK);
		return nullptr;
	}

	return pDWriteTextFormat;
}

void D2DRenderer::DrawTextW(const wchar_t* text, IDWriteTextFormat*& fontFormat, const D2D1_RECT_F& drawRect, const D2D1_COLOR_F& color)
{
	pRenderTarget->SetTransform(Matrix3x2F::Identity());

	pColorBrush->SetColor(color);

	size_t bufferSize = wcslen(text);

	pRenderTarget->DrawText(
		text,
		bufferSize,
		fontFormat,
		drawRect,
		pColorBrush
	);
}

size_t D2DRenderer::GetUsedVram()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}


//private:
D2D1_VECTOR_2F D2DRenderer::GetRectOrigin(D2D1_RECT_F& rect, const float angle)
{
	D2D1_VECTOR_2F point[2];
	point[0].x = rect.left;
	point[0].y = rect.top;

	point[1].x = rect.right;
	point[1].y = rect.bottom;

	for (int i = 0; i < 2; i++)
	{
		point[i] = GetRotatedPoint(point[i], angle);
	}

	return D2D1_VECTOR_2F{ (point[1].x - point[0].x) * 0.5f, (point[1].y - point[0].y) * 0.5f};
}

D2D1_SIZE_F D2DRenderer::GetDrawPos(ID2D1Bitmap*& ID2D1Bitmap, const D2D1_VECTOR_2F& position, const D2D1_VECTOR_2F& scale, const float angle)
{
	D2D1_SIZE_F size = ID2D1Bitmap->GetSize();

	D2D1_VECTOR_2F halfSize{ size.width * 0.5f * scale.x, size.height * 0.5f * scale.y };

	D2D1_RECT_F rect{ 0, 0, halfSize.x, halfSize.y };
	GetRectOrigin(rect, angle);

	halfSize.x = rect.right - rect.left;
	halfSize.y = rect.bottom - rect.top;
	
	D2D1_SIZE_F drPos{ position.x - halfSize.x, position.y - halfSize.y };

	return drPos;
}

void D2DRenderer::ReleaseAllID2D1Bitmap()
{
	if (!ID2D1BitmapResourceMap.empty())
	{
		for (auto& item : ID2D1BitmapResourceMap)
		{
			ULONG refCount = item.second->Release();
			while (refCount != 0)
			{
				refCount = item.second->Release();
			}
		}
		ID2D1BitmapResourceMap.clear();
	}
}
