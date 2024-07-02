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
		Vector2 worldScale = gameObject.transform.scale;
		const D2D1_MATRIX_3X2_F& camMatrix = gameObject.transform.GetCameraMatrix();
		const Vector2& camScale = Vector2::GetScaleFromMatrix(camMatrix);
		const D2D1_MATRIX_3X2_F& drawMatrix = D2D1::Matrix3x2F::Scale(camScale.x, camScale.y) * D2D1::Matrix3x2F::Translation(camMatrix.dx, camMatrix.dy); //회전 매트릭스 제외
		const D2D1_RECT_F& drawRect = { -bounds.extents.x / worldScale.x , -bounds.extents.y / worldScale.y, bounds.extents.x / worldScale.x, bounds.extents.y / worldScale.y }; //자신의 스케일 제외(위 매트릭스에 이미 포함됨)
		D2DRenderer::DrawRect(drawMatrix, drawRect, D2D1::ColorF(D2D1::ColorF::Green));
	}
}
