#include "TextRenderer.h"

#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

TextRenderer::TextRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	DrawRect = { 0, 0, (float)WinGameApp::GetClientSize().cx, 0 };
}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::SetFont(const wchar_t* fontName)
{
	this->fontName = fontName;
	CreateD2DFont();
}

void TextRenderer::SetFontSize(float size)
{
	fontSize = size;
	if (!fontName.empty())
	{
		CreateD2DFont();
	}
}

void TextRenderer::SetFontWeight(DWRITE_FONT_WEIGHT weight)
{
	fontWeight = weight;
	if (!fontName.empty())
	{
		CreateD2DFont();
	}
}

void TextRenderer::SetFontStyle(DWRITE_FONT_STYLE style)
{
	fontStyle = style;
	if (!fontName.empty())
	{
		CreateD2DFont();
	}
}

void TextRenderer::SetFontStretch(DWRITE_FONT_STRETCH stretch)
{
	fontStretch = stretch;
	if (!fontName.empty())
	{
		CreateD2DFont();
	}
}

void TextRenderer::Render()
{
	if (currentTextFormat)
	{
		D2DRenderer::DrawTextW(Text.c_str(), currentTextFormat, gameObject.transform.GetCameraMatrix(), DrawRect, TextColor);
	}
}

void TextRenderer::CreateD2DFont()
{
	if (currentTextFormat)
	{
		currentTextFormat->Release();
		currentTextFormat = nullptr;
	}
	currentTextFormat = D2DRenderer::CreateD2DFont(fontName.c_str(), fontSize, fontWeight, fontStyle, fontStretch);
}
