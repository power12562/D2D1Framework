#include "Core/Componet/SpriteRenderer.h"
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
		Vector2& position = gameobject.transform().position; 
		Vector2& scale = gameobject.transform().scale;
		float angle = gameobject.transform().rotation;
		D2DRenderer::DrawBitmap(image, { position.x, WinGameApp::GetClientSize().cy - position.y}, {scale.x, scale.y}, -angle);
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
