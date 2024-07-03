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

	/** ����� �ؽ�Ʈ */
	std::wstring Text;

	/** �׸� ���� */
	D2D1_RECT_F DrawRect; 

	/** ���� �� */
	D2D1_COLOR_F TextColor = D2D1::ColorF(D2D1::ColorF::Black); 

	/** ����� ��Ʈ ����. ��ġ�� ��Ʈ�� ��� ���� �մϴ�.*/
	void SetFont(const wchar_t* fontName);

	void SetFontSize(float size);
	float GetFontSize() const { return fontSize; }
	/** ��Ʈ ũ��.*/
	__declspec(property(get = GetFontSize, put = SetFontSize)) float Size;

	void SetFontWeight(DWRITE_FONT_WEIGHT weight);
	DWRITE_FONT_WEIGHT GetFontWeight() const { return fontWeight; }
	/** ��Ʈ �β�.*/
	__declspec(property(get = GetFontWeight, put = SetFontWeight)) DWRITE_FONT_WEIGHT Weight;

	void SetFontStyle(DWRITE_FONT_STYLE style);
	DWRITE_FONT_STYLE GetFontStyle() const { return fontStyle; }
	/** ��Ʈ ��Ÿ��*/
	__declspec(property(get = GetFontStyle, put = SetFontStyle)) DWRITE_FONT_STYLE Style;

	void SetFontStretch(DWRITE_FONT_STRETCH stretch);
	DWRITE_FONT_STRETCH GetFontStretch() const { return fontStretch; }
	/** ��Ʈ ��Ʈ��ġ*/
	__declspec(property(get = GetFontStretch, put = SetFontStretch)) DWRITE_FONT_STRETCH Stretch;

protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;

private:
	/** ���� ������ ���� d2d��Ʈ�� �����մϴ�.*/
	void CreateD2DFont();
	IDWriteTextFormat* currentTextFormat = nullptr; //���� ���õ� D2D��Ʈ�� ������

	std::wstring fontName; //���õ� ��Ʈ �̸�
	float fontSize = 30.f; //��Ʈ ũ��
	DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_THIN; //�۲� �β� 
	DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL; //�۲� ��Ÿ��
	DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL; //�۲� ��Ʈ��ġ
};