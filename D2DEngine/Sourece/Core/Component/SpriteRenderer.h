#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <Windows.h>
#include <list>
#undef LoadImage

class SpriteRenderer : public ComponentBase
{
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	SpriteRenderer(GameObjectBase& gameObject);
	virtual ~SpriteRenderer() override;

	void LoadImage(const wchar_t* path);

protected:
	virtual void Update() override;
	virtual void Render() override;

private:
	struct ID2D1Bitmap* image = nullptr;

	/** 생성된 컴포넌트 리스트*/
	static std::list<SpriteRenderer*> instanceList;

	/** 마지막으로 불러온 경로 저장하는 버퍼*/
	wchar_t* lastLoadPath = nullptr;

	/** D2D factory 재생성시 호출되는 메서드*/
	static void ReloadImage();
};
