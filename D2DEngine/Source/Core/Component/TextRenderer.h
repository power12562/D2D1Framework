#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <string>
#include <d2d1.h>
#include <dwrite.h>

using D2D1::ColorF;

class TextRenderer : public ComponentBase
{
public:
	TextRenderer(GameObjectBase& gameObject);
	virtual ~TextRenderer() override;

	/** 출력할 텍스트 */
	std::wstring Text;

	/** 그릴 영역 */
	D2D1_RECT_F DrawRect; 

	/** 글자 색 */
	D2D1_COLOR_F TextColor = D2D1::ColorF(D2D1::ColorF::Black); 

	/** 사용할 폰트 선택. 설치된 폰트만 사용 가능 합니다.*/
	void SetFont(const wchar_t* fontName);

	void SetFontSize(float size);
	float GetFontSize() const { return fontSize; }
	/** 폰트 크기.*/
	__declspec(property(get = GetFontSize, put = SetFontSize)) float Size;

	void SetFontWeight(DWRITE_FONT_WEIGHT weight);
	DWRITE_FONT_WEIGHT GetFontWeight() const { return fontWeight; }
	/** 폰트 두께.*/
	__declspec(property(get = GetFontWeight, put = SetFontWeight)) DWRITE_FONT_WEIGHT Weight;

	void SetFontStyle(DWRITE_FONT_STYLE style);
	DWRITE_FONT_STYLE GetFontStyle() const { return fontStyle; }
	/** 폰트 스타일*/
	__declspec(property(get = GetFontStyle, put = SetFontStyle)) DWRITE_FONT_STYLE Style;

	void SetFontStretch(DWRITE_FONT_STRETCH stretch);
	DWRITE_FONT_STRETCH GetFontStretch() const { return fontStretch; }
	/** 폰트 스트레치*/
	__declspec(property(get = GetFontStretch, put = SetFontStretch)) DWRITE_FONT_STRETCH Stretch;

protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;

private:
	/** 현재 정보에 따라 d2d폰트를 생성합니다.*/
	void CreateD2DFont();
	IDWriteTextFormat* currentTextFormat = nullptr; //현재 선택된 D2D폰트의 포인터

	std::wstring fontName; //선택된 폰트 이름
	float fontSize = 30.f; //폰트 크기
	DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_THIN; //글꼴 두께 
	DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL; //글꼴 스타일
	DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL; //글꼴 스트레치
};