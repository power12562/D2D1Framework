#include "BoxCollider2D.h"

#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

BoxCollider2D::BoxCollider2D(GameObjectBase& gameObject) :
	ColliderBase(gameObject)
{
	type = Type::box;
}

BoxCollider2D::~BoxCollider2D()
{

}

void BoxCollider2D::Update()
{
	bounds.center = gameObject.transform.position;
	bounds.size = ColliderSize;
	bounds.extents = bounds.size / 2.f;
	bounds.leftTop.x = bounds.center.x -= bounds.extents.x;
	bounds.leftTop.y = bounds.center.y += bounds.extents.y;
	bounds.rightBottom.x = bounds.center.x += bounds.extents.x;
	bounds.rightBottom.y = bounds.center.y -= bounds.extents.y;
}

void BoxCollider2D::Render()
{
	if (isDrawCollider)
	{
		const SIZE& screenSize = WinGameApp::GetClientSize();

		Vector2 worldScale = gameObject.transform.scale;
		worldScale.x = abs(worldScale.x);
		worldScale.y = abs(worldScale.y);
		const D2D1_MATRIX_3X2_F& objMatrix = gameObject.transform.GetWorldMatrix();
		const Vector2& objScale = Vector2::GetScaleFromMatrix(objMatrix);
		const D2D1_MATRIX_3X2_F& drawMatrix =
			(
				D2D1::Matrix3x2F::Scale(objScale.x, objScale.y) *
				D2D1::Matrix3x2F::Translation(bounds.center.x, screenSize.cy - bounds.center.y) *
				Camera::GetMainCamera()->GetInvertMatrix()
				); //회전 매트릭스는 제외한 월드 매트릭스 * 카메라 역행렬 매트릭스 (카메라 기준 좌표로)
		D2D1_RECT_F drawRect = {
			-ColliderSize.x, -ColliderSize.y,
			ColliderSize.x, ColliderSize.y
		};
		D2DRenderer::DrawRect(drawMatrix, drawRect, D2D1::ColorF(D2D1::ColorF::Green));
	}
}

bool BoxCollider2D::isCollide(ColliderBase* other)
{
	if (other->GetType() == Type::box)
	{
		const Bounds& otherBD = ((BoxCollider2D*)other)->bounds;
		return bounds.AABB(otherBD);
	}
	else
	{
		return false;
	}
}
