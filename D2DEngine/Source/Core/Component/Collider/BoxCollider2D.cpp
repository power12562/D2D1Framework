#include "BoxCollider2D.h"

#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

#include <windef.h>
#include <d2d1helper.h>
#include <dcommon.h>

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
	bounds.center = gameObject.transform.position + Center;
	bounds.size = ColliderSize;
	bounds.extents = bounds.size / 2.f;
	bounds.leftTop.x = bounds.center.x - bounds.extents.x;
	bounds.leftTop.y = bounds.center.y + bounds.extents.y;
	bounds.rightBottom.x = bounds.center.x + bounds.extents.x;
	bounds.rightBottom.y = bounds.center.y - bounds.extents.y;
}

void BoxCollider2D::Render()
{
	if (isDrawCollider)
	{
		const SIZE& screenSize = WinGameApp::GetClientSize();
		const D2D1_MATRIX_3X2_F& drawMatrix =
			(
				D2D1::Matrix3x2F::Translation(bounds.center.x, screenSize.cy - bounds.center.y) *
				Camera::GetMainCamera()->GetInvertMatrix()
				); //회전 매트릭스는 제외한 월드 매트릭스 * 카메라 역행렬 매트릭스 (카메라 기준 좌표로)
		D2D1_RECT_F drawRect = {
			-bounds.extents.x, -bounds.extents.y,
			bounds.extents.x, bounds.extents.y
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

bool BoxCollider2D::isCollide(const Vector2& point)
{
	return bounds.PointCollision(point);
}

void BoxCollider2D::SerializedJson(ordered_json& jsonObj)
{
	ordered_json json;
	json["ColliderSize"] = ColliderSize;
	json["Center"] = Center;


	jsonObj["BoxCollider2D"].push_back(json);
}

void BoxCollider2D::DeSerializedJson(ordered_json& jsonObj)
{
	//여러개의 중복 컴포넌트가 존재하면 마지막에 push_back한 값으로 초기화 되는 문제가 있다.
	for (auto& dataJson : jsonObj["BoxCollider2D"]) 
	{
		ColliderSize = dataJson["ColliderSize"].get<JsonUtility::Vector2>();
		Center = dataJson["Center"].get<JsonUtility::Vector2>();
	}
}
