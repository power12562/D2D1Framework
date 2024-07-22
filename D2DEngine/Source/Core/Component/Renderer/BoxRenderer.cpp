#include "BoxRenderer.h"
#include <Framework/D2DRenderer.h>

BoxRenderer::~BoxRenderer()
{
}

void BoxRenderer::Render()
{
	const Vector2 halfSize = size * 0.5f;
	D2DRenderer::DrawRect(
		D2D1::Matrix3x2F::Translation(center.x, center.y) * gameObject.transform.GetCameraMatrix(),
		{ -halfSize.x, -halfSize.y, halfSize.x, halfSize.y},
		color, isFill, alpha
	);
}
