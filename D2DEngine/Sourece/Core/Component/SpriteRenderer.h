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

	/** ����� �̹��� �ҷ�����*/
	void LoadImage(const wchar_t* path);
	/** �̹��� �����ϱ�*/
	void UnloadImage();

	/** ���� �̹��� ũ��*/
	D2D1_SIZE_F GetImageSize() const { return currentImageSize; }

	/** �ִϸ��̼� �����ϱ�.*/
	void SetSpriteAnimation(SpriteAnimation& animationComponet);
	/** �ִϸ��̼� �����ϱ�. ���ڿ� �ִϸ��̼� ������Ʈ�� �Ѱ��ָ� ������ �� �ֽ��ϴ�..*/
	void SetSpriteAnimation() { pSpriteAnimation = nullptr; }

	/** �̹��� X�� ����*/
	void FlipX(bool isflip);
	void FlipX();
	/** �̹��� Y�� ����*/
	void FlipY(bool isflip);
	void FlipY();

protected:
	virtual void Render() override;

private:
	struct ID2D1Bitmap* image = nullptr;

	/** �����ų �ִϸ��̼� ������Ʈ*/
	SpriteAnimation* pSpriteAnimation = nullptr;

	/** ������ ������Ʈ ����Ʈ*/
	static std::list<SpriteRenderer*> instanceList;

	/** ���������� �ҷ��� ��� �����ϴ� ����*/
	wchar_t* lastLoadPath = nullptr;

	/** D2D factory ������� ȣ��Ǵ� �޼���*/
	static void ReloadImage();

	D2D1_SIZE_F currentImageSize{};
};
