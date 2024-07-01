#include "BoxCollider2D.h"

#include "Framework/D2DRenderer.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

BoxCollider2D::BoxCollider2D(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	pivotMatrix = D2D1::Matrix3x2F::Identity();
	trMatrix = D2D1::Matrix3x2F::Identity();

}

BoxCollider2D::~BoxCollider2D()
{

}

void BoxCollider2D::Start()
{

}

void BoxCollider2D::Update()
{
	bounds = gameObject.GetBounds();
	pivotMatrix = D2D1::Matrix3x2F::Translation(gameObject.transform.pivot.x, gameObject.transform.pivot.y) * gameObject.transform.GetCameraMatrix();
	trMatrix = D2D1::Matrix3x2F::Translation(pivotMatrix.dx, pivotMatrix.dy); //회전은 적용 안되도록.
}

void BoxCollider2D::Render()
{
	if (isDrawRect)
	{
		D2DRenderer::DrawRect(trMatrix, { -bounds.extents.x, -bounds.extents.y, bounds.extents.x, bounds.extents.y}, D2D1::ColorF(D2D1::ColorF::Green));
	}
}
