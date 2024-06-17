#include "DemoApp.h"
#include <iostream>
#include "Framework/D2DRenderer.h"
#include "Framework/TimeSystem.h"
#include "Framework/InputSystem.h"

DemoApp::DemoApp(bool _Debug)
{
	isDebug = _Debug;
}

DemoApp::~DemoApp()
{

}

void DemoApp::Update()
{

}

void DemoApp::Render()
{
	using namespace D2D1;
	using namespace TimeSystem;
	using namespace InputSystem;

	const float fontSize = 50.f;

	static D2D1_SIZE_F clientSize = D2DRenderer::GetRenderTarget().GetSize();
	static ID2D1Bitmap* testBitmap1 = D2DRenderer::CreateD2DBitmapFromFile(L"Resource/test.png");
	static IDWriteTextFormat* fontFormat = D2DRenderer::CreateD2DFont(L"Consolelas", DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize);

	D2DRenderer::Clear(D2D1::ColorF::Violet);
	D2DRenderer::DrawLine({ 0, clientSize.height * 0.5f }, { clientSize.width, clientSize.height * 0.5f }, ColorF(ColorF::Blue), 15.f);
	D2DRenderer::DrawRect(
		{ clientSize.width / 2.f - 100.f, clientSize.height / 2.f - 100.f
		,clientSize.width / 2.f + 100.f, clientSize.height / 2.f + 100.f }, 
		ColorF(ColorF::AliceBlue), true
	);
	D2DRenderer::DrawRect(
		{ clientSize.width / 2.f - 100.f, clientSize.height / 2.f - 100.f
		,clientSize.width / 2.f + 100.f, clientSize.height / 2.f + 100.f }
	);

	if (IsResize())
	{
		D2DRenderer::InitDirect2D();
		clientSize = D2DRenderer::GetRenderTarget().GetSize();
		testBitmap1 = D2DRenderer::CreateD2DBitmapFromFile(L"Resource/test.png");
		IDWriteTextFormat* fontFormat = D2DRenderer::CreateD2DFont(L"Cooper", DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize);
	}
	if (testBitmap1)
	{
		static float elapsedTime = Time.GetDeltatime();
		elapsedTime += Time.GetDeltatime();

		const float bit1Angle = 20;
		const float bit1scale = 1.4f;

		static float elapsedAngle = bit1Angle;
		elapsedAngle += Time.GetDeltatime() * bit1Angle;

		D2D1_RECT_F bounds{0, 0,  testBitmap1->GetSize().width, testBitmap1->GetSize().height };
		D2DRenderer::GetRectBounds(bounds, elapsedAngle);
		D2D1_VECTOR_2F size = { (bounds.right - bounds.left) * bit1scale, (bounds.bottom - bounds.top) * bit1scale };
		
		D2DRenderer::DrawRect(D2D1_VECTOR_2F{ clientSize.width * 0.5f,  clientSize.height * 0.5f }, D2D1_SIZE_F{ size.x, size.y }, ColorF(ColorF::Black), false);
		D2DRenderer::DrawBitmap(testBitmap1, { clientSize.width * 0.5f,  clientSize.height * 0.5f }, { bit1scale, bit1scale }, elapsedAngle);
	}

	static float elapsedTime = Time.GetDeltatime();
	static wchar_t frameText[15];
	static wchar_t deltaText[30];
	static wchar_t inputKeyText[30];
	elapsedTime += Time.GetDeltatime();
	if (0.5f < elapsedTime)
	{
		swprintf_s(frameText, ARRAYSIZE(frameText), L"frame : %.0f", Time.GetFrameRate());
		
		elapsedTime = 0.f;
	}
	swprintf_s(deltaText, ARRAYSIZE(deltaText), L"deltaTime : %.06f", Time.GetDeltatime());
	const MouseState& mouse = Input.GetMouseState();
	if (mouse.isLeftClick)
	{
		swprintf_s(inputKeyText, ARRAYSIZE(inputKeyText), L"Left Click");
	}
	else if(mouse.isRightClick)
	{
		swprintf_s(inputKeyText, ARRAYSIZE(inputKeyText), L"Right Click");
	}
	else if (mouse.isMiddleClick)
	{
		swprintf_s(inputKeyText, ARRAYSIZE(inputKeyText), L"Middle Click");
	}
	else if (Input.IsAnyKey())
	{
		swprintf_s(inputKeyText, ARRAYSIZE(inputKeyText), L"Keyboard");
	}
	else
	{
		swprintf_s(inputKeyText, ARRAYSIZE(inputKeyText), L"Input null");
	}
	D2DRenderer::DrawTextW(frameText, fontFormat, { 0, 0 , clientSize.width, 500}, ColorF(ColorF::Black));
	D2DRenderer::DrawTextW(deltaText, fontFormat, { 0, fontSize , clientSize.width, 500}, ColorF(ColorF::Black));
	D2DRenderer::DrawTextW(inputKeyText, fontFormat, { 0, fontSize * 2, clientSize.width, 500 });
	

}

