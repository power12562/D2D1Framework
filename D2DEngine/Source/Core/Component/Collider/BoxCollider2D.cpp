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
	if (isDrawCollider)
	{
		const D2D1_MATRIX_3X2_F& camMatrix = gameObject.transform.GetCameraMatrix();
		float scaleX = sqrtf(camMatrix._11 * camMatrix._11 + camMatrix._12 * camMatrix._12);
		float scaleY = sqrtf(camMatrix._21 * camMatrix._21 + camMatrix._22 * camMatrix._22);
		const D2D1_MATRIX_3X2_F& drawMatrix =
			D2D1::Matrix3x2F::Translation(camMatrix.dx, camMatrix.dy) *
			D2D1::Matrix3x2F::Scale(scaleX, scaleY);
		D2DRenderer::DrawRect(drawMatrix, {-bounds.extents.x, -bounds.extents.y, bounds.extents.x, bounds.extents.y}, D2D1::ColorF(D2D1::ColorF::Green));
	}
}
