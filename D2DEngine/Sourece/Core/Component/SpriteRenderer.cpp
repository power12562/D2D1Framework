#include "Core/Component/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Core/GameObject/GameObjectBase.h"
#undef LoadImage

std::list<SpriteRenderer*> SpriteRenderer::instanceList;

SpriteRenderer::SpriteRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	instanceList.push_back(this);
}

SpriteRenderer::~SpriteRenderer()
{
	if (lastLoadPath)
	{
		image->Release();
		delete[] lastLoadPath;
		lastLoadPath = nullptr;
	}
}

void SpriteRenderer::Update()
{

}

void SpriteRenderer::Render()
{
	if (!image)
		return;
	else if(enabled)
	{
		D2DRenderer::DrawBitmap(image, gameobject.transform().GetWorldMatrix());
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

	if (image)
	{
		image->Release();
		image = nullptr;
	}
	image = D2DRenderer::CreateD2DBitmapFromFile(path);
	auto size = image->GetSize();
	gameobject.transform().pivot = Vector2{ size.width * 0.5f, size.height * 0.5f};

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
