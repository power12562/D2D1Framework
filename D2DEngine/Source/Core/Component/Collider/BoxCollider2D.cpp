#include "BoxCollider2D.h"

#include "Framework/D2DRenderer.h"

#include "Core/GameObject/Base/GameObjectBase.h"

BoxCollider2D::BoxCollider2D(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

BoxCollider2D::~BoxCollider2D()
{

}

void BoxCollider2D::Start()
{

}

void BoxCollider2D::Update()
{

}

void BoxCollider2D::Render()
{
	if (isDrawRect)
	{
		const Bounds& bounds = gameObject.GetBounds();
		D2DRenderer::DrawRect(gameObject.transform.GetCameraMatrix(), {0, 0, bounds.size.x, bounds.size.y}, D2D1::ColorF(D2D1::ColorF::Green));
	}
}
