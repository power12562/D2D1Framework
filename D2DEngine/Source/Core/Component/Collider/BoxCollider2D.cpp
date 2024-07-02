#include "BoxCollider2D.h"

#include "Framework/D2DRenderer.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

BoxCollider2D::BoxCollider2D(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
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
}

void BoxCollider2D::Render()
{
	if (isDrawRect)
	{
		const D2D1_MATRIX_3X2_F& myMatrix = gameObject.transform.GetCameraMatrix();
		trMatrix = D2D1::Matrix3x2F::Translation(myMatrix.dx, myMatrix.dy); //회전은 적용 안되도록.
		D2DRenderer::DrawRect(trMatrix, { -bounds.extents.x, -bounds.extents.y, bounds.extents.x, bounds.extents.y}, D2D1::ColorF(D2D1::ColorF::Green));
	}
}
