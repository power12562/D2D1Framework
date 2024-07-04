#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <Windows.h>
#include <list>
#include <d2d1.h>
#undef LoadImage

class SpriteAnimation;
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

	/** 애니메이션 적용하기.*/
	void SetSpriteAnimation(SpriteAnimation& animationComponet);
	/** 애니메이션 사용안하기. 인자에 애니메이션 컴포넌트를 넘겨주면 적용할 수 있습니다..*/
	void SetSpriteAnimation() { pSpriteAnimation = nullptr; }

protected:
	virtual void Render() override;

private:
	ID2D1Bitmap* const* image = nullptr;

	/**즉시 삭제를 위한 자신의 이터레이터 (노드)*/
	std::list<SpriteRenderer*>::iterator instanceIter;

	/** 적용시킬 애니메이션 컴포넌트*/
	SpriteAnimation* pSpriteAnimation = nullptr;

	/** 마지막으로 불러온 경로 저장하는 버퍼*/
	wchar_t* lastLoadPath = nullptr;

	D2D1_SIZE_F currentImageSize{};
};
