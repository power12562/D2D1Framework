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

void SpriteRenderer::SetSpriteAnimation(SpriteAnimation& animationComponet)
{
	pSpriteAnimation = &animationComponet;
	const auto& frame = pSpriteAnimation->GetCurrentFrame();
	gameobject.transform().pivot = Vector2{ frame.source.right - frame.source.left, frame.source.bottom - frame.source.top };
}

void SpriteRenderer::Render()
{
	if (!image || !enabled)
		return;

	if (pSpriteAnimation == nullptr)
	{
		D2DRenderer::DrawBitmap(image, gameobject.transform().GetWorldMatrix());
	}		
	else
	{
		const FrameInfo& frame = pSpriteAnimation->GetCurrentFrame();
		const D2D1_RECT_F& sourceRect = frame.source;
		D2D1_SIZE_F halfSize = { sourceRect.right - sourceRect.left, sourceRect.bottom - sourceRect.top };

		halfSize.width *= 0.5f;
		halfSize.height *= 0.5f;

		D2D1_MATRIX_3X2_F translate = D2D1::Matrix3x2F::Translation(halfSize.width, halfSize.height);

		D2DRenderer::DrawBitmap(image, gameobject.transform().GetWorldMatrix() * translate, sourceRect);		
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
