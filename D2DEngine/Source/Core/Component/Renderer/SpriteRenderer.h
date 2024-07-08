#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <Windows.h>
#include <list>
#include <d2d1.h>
#undef LoadImage

class SpriteAnimationRenderer;
struct ID2D1Bitmap;

class SpriteRenderer : public ComponentBase
{
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	SpriteRenderer(GameObjectBase& gameObject);
	virtual ~SpriteRenderer() override;

	/** ����� �̹��� �ҷ�����*/
	void LoadImage(const wchar_t* path);

	/** �̹��� �����ϱ�*/
	void UnloadImage();

	/** ���� �̹��� ũ��*/
	D2D1_SIZE_F GetImageSize() const { return currentImageSize; }

protected:
	virtual void Render() override;

private:
	ID2D1Bitmap* const* image = nullptr;

	/**��� ������ ���� �ڽ��� ���ͷ����� (���)*/
	std::list<SpriteRenderer*>::iterator instanceIter;

	/** ���������� �ҷ��� ��� �����ϴ� ����*/
	wchar_t* lastLoadPath = nullptr;

	D2D1_SIZE_F currentImageSize{};
};
