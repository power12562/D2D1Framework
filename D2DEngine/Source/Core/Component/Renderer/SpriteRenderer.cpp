#include "Core/Component/Renderer/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/SpriteAnimation.h"
#include "Core/Component/Camera.h"
#undef LoadImage

SpriteRenderer::SpriteRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

SpriteRenderer::~SpriteRenderer()
{
	if (image != nullptr)
	{
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);
		image = nullptr;
		delete[] lastLoadPath;
		lastLoadPath = nullptr;
	}
}

void SpriteRenderer::SetSpriteAnimation(SpriteAnimation& animationComponet)
{
	pSpriteAnimation = &animationComponet;
	if (pSpriteAnimation->GetCurrentFrame())
	{
		pSpriteAnimation->UpdateCurrentPivot();
	}	
}


void SpriteRenderer::Render()
{
	if (!image && !pSpriteAnimation)
		return;

	Camera* const mainCam = Camera::GetMainCamera();
	D2D1_MATRIX_3X2_F objMatrix = gameObject.transform.GetInvertPivotMatrix() * gameObject.transform.GetCameraMatrix();
	if (pSpriteAnimation == nullptr)
	{	
		D2DRenderer::DrawBitmap(*image, objMatrix);	
	}		
	else
	{	
		if (ID2D1Bitmap* const* image = pSpriteAnimation->GetCurrentImage())
		{
			FrameInfo* const frame = pSpriteAnimation->GetCurrentFrame();
			int flipX = (0 < gameObject.transform.scale.x) ? 1 : -1;
			int flipY = (0 < gameObject.transform.scale.y) ? 1 : -1;
			objMatrix = D2D1::Matrix3x2F::Translation(flipX * frame->center.x,  flipY * -frame->center.y) * objMatrix;
			D2DRenderer::DrawBitmap(*image, objMatrix, frame->source);
		}
	}
}

void SpriteRenderer::LoadImage(const wchar_t* path)
{
	if (path == nullptr)
		return;
	
	if (image != nullptr)
	{
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);
	}

	image = D2DRenderer::CreateD2DBitmapFromFile(path);
	if (image == nullptr)
	{
		return;
	}
		
	if (!pSpriteAnimation)
	{
		currentImageSize = (*image)->GetSize();
		gameObject.GetTransform().pivot = Vector2{ currentImageSize.width * 0.5f, currentImageSize.height * 0.5f };
	}
	
	if (lastLoadPath == nullptr || wcscmp(path, lastLoadPath))
	{
		if (lastLoadPath)
		{		
			delete[] lastLoadPath;
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
