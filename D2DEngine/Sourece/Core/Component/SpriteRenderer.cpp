#include "Core/Component/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/Camera.h"
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
	const D2D1_RECT_F& sourceRect = frame.source;
	gameObject.GetTransform().pivot = Vector2{ frame.source.right - frame.source.left, frame.source.bottom - frame.source.top };
	currentImageSize = { sourceRect.right - sourceRect.left, sourceRect.bottom - sourceRect.top };
}


void SpriteRenderer::Render()
{
	if (!image || !enabled)
		return;
	Camera* const mainCam = Camera::mainCamera();
	const D2D1_MATRIX_3X2_F& objMatrix = gameObject.GetTransform().GetWorldMatrix();
	if (pSpriteAnimation == nullptr)
	{
		if (mainCam)
		{
			D2DRenderer::DrawBitmap(image, objMatrix * mainCam->gameObject.transform.matrixInvertPivot);
		}
		else
		{ 
			D2DRenderer::DrawBitmap(image, objMatrix);
		}	
	}		
	else
	{
		const FrameInfo& frame = pSpriteAnimation->GetCurrentFrame();
		const D2D1_RECT_F& sourceRect = frame.source;
		currentImageSize = { sourceRect.right - sourceRect.left, sourceRect.bottom - sourceRect.top };
		D2D1_SIZE_F halfSize{};
		halfSize.width = currentImageSize.width * 0.5f;
		halfSize.height = currentImageSize.height * 0.5f;
		D2D1_MATRIX_3X2_F pivotCenter = D2D1::Matrix3x2F::Translation(halfSize.width + frame.center.x, halfSize.height + frame.center.y);

		if (mainCam)
		{
			D2DRenderer::DrawBitmap(image, (pivotCenter * objMatrix) * mainCam->gameObject.transform.InvertWorldMatrix, sourceRect);
		}
		else
		{
			D2DRenderer::DrawBitmap(image, pivotCenter * objMatrix, sourceRect);
		}
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
	gameObject.GetTransform().pivot = Vector2{ currentImageSize.width * 0.5f, currentImageSize.height * 0.5f};

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
		gameObject.GetTransform().pivot = Vector2( 0,0 );
	}
}
