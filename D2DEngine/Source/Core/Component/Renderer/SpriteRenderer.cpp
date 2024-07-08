#include "Core/Component/Renderer/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

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

void SpriteRenderer::Render()
{
	if (!image)
		return;

	D2D1_MATRIX_3X2_F objMatrix = gameObject.transform.GetInvertPivotMatrix() * gameObject.transform.GetCameraMatrix();
	D2DRenderer::DrawBitmap(*image, objMatrix);		
}

void SpriteRenderer::LoadImage(const wchar_t* path)
{
	if (path == nullptr)
		return;
	
	if (image != nullptr)
	{
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);
	}

	if (image = D2DRenderer::CreateD2DBitmapFromFile(path))
	{
		currentImageSize = (*image)->GetSize();
		gameObject.GetTransform().pivot = Vector2{ currentImageSize.width * 0.5f, currentImageSize.height * 0.5f };

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
