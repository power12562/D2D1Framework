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
	instanceIter = std::prev(instanceList.end()); //마지막 이터를 자신의 이터레이터로 저장
}

SpriteRenderer::~SpriteRenderer()
{
	if (image != nullptr)
	{
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);
		delete[] lastLoadPath;
		lastLoadPath = nullptr;
	}
	instanceList.erase(instanceIter); //자신을 인스턴스 리스트에서 제거
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
	const D2D1_MATRIX_3X2_F& objMatrix = gameObject.transform.GetInvertPivotMatrix() * gameObject.transform.GetCameraMatrix();
	if (pSpriteAnimation == nullptr)
	{	
		D2DRenderer::DrawBitmap(image, objMatrix);	
	}		
	else
	{	
		if (ID2D1Bitmap* image = pSpriteAnimation->GetCurrentImage())
		{
			D2DRenderer::DrawBitmap(image, objMatrix, pSpriteAnimation->GetCurrentFrame()->source);
		}
	}
}

void SpriteRenderer::ReloadImage()
{
	for (auto& component : instanceList)
	{
		component->image = nullptr;
		component->LoadImage(component->lastLoadPath);
	}
}

void SpriteRenderer::LoadImage(const wchar_t* path)
{
	if (path == nullptr)
		return;
	
	if(image != nullptr)
		D2DRenderer::ReleaseD2D1Bitmap(lastLoadPath);

	image = D2DRenderer::CreateD2DBitmapFromFile(path);
	if (image == nullptr)
	{
		return;
	}
		
	if (!pSpriteAnimation)
	{
		currentImageSize = image->GetSize();
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
