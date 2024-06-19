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

	/** ������ ������Ʈ ����Ʈ*/
	static std::list<SpriteRenderer*> instanceList;

	/** ���������� �ҷ��� ��� �����ϴ� ����*/
	wchar_t* lastLoadPath = nullptr;

	/** D2D factory ������� ȣ��Ǵ� �޼���*/
	static void ReloadImage();
};
