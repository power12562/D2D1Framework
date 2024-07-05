#include "LineRenderer.h"

#include "Framework/D2DRenderer.h"

#include "Core/GameObject/Base/GameObjectBase.h"


LineRenderer::LineRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
}

LineRenderer::~LineRenderer()
{
}

void LineRenderer::Render()
{
	D2DRenderer::DrawLine(gameObject.transform.GetCameraMatrix(), {StartPosition.x, -StartPosition.y}, { EndPosition.x, -EndPosition.y }, Color, Width);
}
			