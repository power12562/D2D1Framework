#include "Core/Component/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Core/GameObject/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#undef LoadImage

std::list<SpriteRenderer*> SpriteRenderer::instanceList;

SpriteRenderer::SpriteRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	instanceList.push_back(this);
}

SpriteRenderer::~SpriteRenderer()
{
	if (lastLoadPath != nullptr)
	{
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);
	}
}

void SpriteRenderer::Render()
{
	if (!image || !enabled)
		return;

	if (pSpriteAnimation == nullptr)
	{
		D2D1_RECT_F pivotRect;

		Vector2 pivot = gameobject.transform().pivot;
		pivotRect.left = -pivot.x * 0.5f;
		pivotRect.top = -pivot.y * 0.5f;
		pivotRect.right = currentImageSize.width;
		pivotRect.bottom = currentImageSize.height;

		D2DRenderer::DrawBitmap(image, gameobject.transform().GetWorldMatrix(), pivotRect);
	}		
	else
	{
		const FrameInfo& frame = pSpriteAnimation->GetCurrentFrame();
		D2D1_RECT_F sourceRect = frame.source;
		sourceRect.left -= frame.center.x;
		sourceRect.right += frame.center.x;
		sourceRect.top -= frame.center.y;
		sourceRect.bottom += frame.center.y;

		D2D1_RECT_F pivotRect;
		Vector2 pivot = gameobject.transform().pivot;
		pivotRect.left = -pivot.x * 0.5f;
		pivotRect.top = -pivot.y * 0.5f;
		pivotRect.right = sourceRect.right - sourceRect.left;
		pivotRect.bottom = sourceRect.bottom - sourceRect.top;

		D2DRenderer::DrawBitmap(image, gameobject.transform().GetWorldMatrix(),pivotRect, sourceRect);
	}
}

void SpriteRenderer::ReloadImage()
{
	for (auto& component : instanceList)
	{
		component->LoadImage(component->lastLoadPath);
	}
}

void SpriteRenderer::LoadImage(const wchar_t* path)
{
	if (path == nullptr)
		return;
	
	if(lastLoadPath != nullptr)
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);

	image = D2DRenderer::CreateD2DBitmapFromFile(path);
	currentImageSize = image->GetSize();
	gameobject.transform().pivot = Vector2{ currentImageSize.width * 0.5f, currentImageSize.height * 0.5f};

	if (lastLoadPath == nullptr || wcscmp(path, lastLoadPath))
	{
		if (lastLoadPath)
		{			
			lastLoadPath = nullptr;
		}
		size_t size = wcslen(path) + 1;
		lastLoadPath = new wchar_t[size];
		wcscpy_s(lastLoadPath, size, path);
	}
}

void SpriteRenderer::UnloadImage()
{
	if (image == nullptr)
		return;
	else
	{
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);
		image = nullptr;
		gameobject.transform().pivot = Vector2( 0,0 );
	}
}
