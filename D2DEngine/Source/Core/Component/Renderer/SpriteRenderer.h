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

	/** 출력할 이미지 불러오기*/
	void LoadImage(const wchar_t* path);

	/** 이미지 해제하기*/
	void UnloadImage();

	/** 현재 이미지 크기*/
	D2D1_SIZE_F GetImageSize() const { return currentImageSize; }

protected:
	virtual void Render() override;

private:
	ID2D1Bitmap* const* image = nullptr;

	/**즉시 삭제를 위한 자신의 이터레이터 (노드)*/
	std::list<SpriteRenderer*>::iterator instanceIter;

	/** 마지막으로 불러온 경로 저장하는 버퍼*/
	wchar_t* lastLoadPath = nullptr;

	D2D1_SIZE_F currentImageSize{};
};
