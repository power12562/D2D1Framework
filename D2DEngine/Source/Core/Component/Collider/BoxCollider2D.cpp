#include "BoxCollider2D.h"

#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Math/OBB.h"
#include "Math/Mathf.h"

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

void BoxCollider2D::Render()
{
	if (isDrawCollider)
	{
		float halfSizeX = ColliderSize.x * 0.5f;
		float halfSizeY = ColliderSize.y * 0.5f;
		halfSizeX /= transform.scale.x;
		halfSizeY /= transform.scale.y;

		D2DRenderer::DrawRect(transform.GetCameraMatrix() * D2D1::Matrix3x2F::Translation(Center.x, -Center.y), { -halfSizeX, -halfSizeY, halfSizeX, halfSizeY }, D2D1::ColorF(D2D1::ColorF::Green));
	}
}

bool BoxCollider2D::isCollide(ColliderBase* other)
{
	if (other->GetType() == Type::box)
	{
		return OBB::CheckOverlap(*this, *static_cast<BoxCollider2D*>(other));
	}
	else
	{
		return false;
	}
}

bool BoxCollider2D::isCollide(const Vector2& point)
{
	return OBB::CheckOverlap(*this, point);
}

float BoxCollider2D::GetTop()
{
	float halfSizeX = ColliderSize.x * 0.5f;
	float halfSizeY = ColliderSize.y * 0.5f;

	Vector2 v1 = Vector2(transform.position.x + halfSizeX, transform.position.y + halfSizeY);
	Vector2 v2 = Vector2(transform.position.x - halfSizeX, transform.position.y + halfSizeY);

	Vector2::GetRotatedPoint(v1, transform.rotation, transform.position);
	Vector2::GetRotatedPoint(v2, transform.rotation, transform.position);

	return Mathf::FindMaxValue(v1.y, v2.y);
}

float BoxCollider2D::GetBottom()
{
	float halfSizeX = ColliderSize.x * 0.5f;
	float halfSizeY = ColliderSize.y * 0.5f;

	Vector2 v1 = Vector2(transform.position.x + halfSizeX, transform.position.y - halfSizeY);
	Vector2 v2 = Vector2(transform.position.x - halfSizeX, transform.position.y - halfSizeY);

	Vector2::GetRotatedPoint(v1, transform.rotation, transform.position);
	Vector2::GetRotatedPoint(v2, transform.rotation, transform.position);

	return Mathf::FindMinValue(v1.y, v2.y);
}

float BoxCollider2D::GetLeft()
{
	float halfSizeX = ColliderSize.x * 0.5f;
	float halfSizeY = ColliderSize.y * 0.5f;

	Vector2 v1 = Vector2(transform.position.x - halfSizeX, transform.position.y + halfSizeY);
	Vector2 v2 = Vector2(transform.position.x - halfSizeX, transform.position.y - halfSizeY);

	Vector2::GetRotatedPoint(v1, transform.rotation, transform.position);
	Vector2::GetRotatedPoint(v2, transform.rotation, transform.position);

	return Mathf::FindMinValue(v1.x, v2.x);
}

float BoxCollider2D::GetRight()
{
	float halfSizeX = ColliderSize.x * 0.5f;
	float halfSizeY = ColliderSize.y * 0.5f;

	Vector2 v1 = Vector2(transform.position.x + halfSizeX, transform.position.y + halfSizeY);
	Vector2 v2 = Vector2(transform.position.x + halfSizeX, transform.position.y - halfSizeY);

	Vector2::GetRotatedPoint(v1, transform.rotation, transform.position);
	Vector2::GetRotatedPoint(v2, transform.rotation, transform.position);

	return Mathf::FindMaxValue(v1.x, v2.x);
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
