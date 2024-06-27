#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <Windows.h>
#include <list>
#include <d2d1.h>
#undef LoadImage

class SpriteAnimation;

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

	/** 이미지 X축 반전*/
	void FlipX(bool isflip);
	void FlipX();
	/** 이미지 Y축 반전*/
	void FlipY(bool isflip);
	void FlipY();

protected:
	virtual void Render() override;

private:
	struct ID2D1Bitmap* image = nullptr;

	/** 적용시킬 애니메이션 컴포넌트*/
	SpriteAnimation* pSpriteAnimation = nullptr;

	/** 생성된 컴포넌트 리스트*/
	static std::list<SpriteRenderer*> instanceList;

	/** 마지막으로 불러온 경로 저장하는 버퍼*/
	wchar_t* lastLoadPath = nullptr;

	/** D2D factory 재생성시 호출되는 메서드*/
	static void ReloadImage();

	D2D1_SIZE_F currentImageSize{};
};
