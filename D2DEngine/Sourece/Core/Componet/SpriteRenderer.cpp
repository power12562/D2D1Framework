#include "Core/Componet/SpriteRenderer.h"
#include "Framework/D2DRenderer.h"
#include "Core/GameObject/GameObjectBase.h"
#undef LoadImage

SpriteRenderer::~SpriteRenderer()
{
	
}

void SpriteRenderer::Update()
{

}

void SpriteRenderer::Render()
{
	if (!image)
		return;
	else
	{
		if (gameobject.GetParent())
		{
			Transform parent = gameobject.GetParent()->transform;

			Vector2 position = parent.position + gameobject.transform.position;
			Vector2 scale = { parent.scale.x * gameobject.transform.scale.x, parent.scale.y * gameobject.transform.scale.y };
			float angle = parent.rotation + gameobject.transform.rotation;

			D2DRenderer::DrawBitmap(image, { position.x, position.y }, { scale.x, scale.y }, angle);
		}
		else
		{
			Vector2& position = gameobject.transform.position;
			Vector2& scale = gameobject.transform.scale;
			float angle = gameobject.transform.rotation;

			D2DRenderer::DrawBitmap(image, { position.x, position.y }, { scale.x, scale.y }, angle);
		}		
	}
}

void SpriteRenderer::LoadImage(const wchar_t* path)
{
	if (!image)
	{
		image = D2DRenderer::CreateD2DBitmapFromFile(path);
	}
}
