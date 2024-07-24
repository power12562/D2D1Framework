#include "Core/Component/Transform.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

#include <Utility/Debug.h>
#include <stack>
#include <cassert>

Transform::Transform(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	using namespace D2D1;

	WM = Matrix3x2F::Identity();
	IWM = Matrix3x2F::Identity();

	CM = Matrix3x2F::Identity();

	position.InitTVector2(this);
	localPosition.InitTVector2(this);
	//matrixTranslation = Matrix3x2F::Identity();

	rotation.InitTFloat(this);
	localRotation.InitTFloat(this);
	//matrixRotation = Matrix3x2F::Identity();

	scale.InitTVector2(this);
	localScale.InitTVector2(this);
	//matrixScale = Matrix3x2F::Identity();

	pivot.InitTVector2(this);
	PM = Matrix3x2F::Identity();
	IPM = Matrix3x2F::Identity();

}

Transform::~Transform()
{
	
}

void Transform::UpdateMatrix()
{
	if (parent == nullptr)
	{
		if (!childsList.empty())
		{
			UpdateWorldMatrix();
			UpdateChildTransform();
		}
		else
		{
			UpdateWorldMatrix();
		}
	}
}

void Transform::UpdateChildTransform()
{
	/*for (auto& child : parent.childsList)
	{
		child->UpdateWorldMatrix();
		if (!child->childsList.empty())
		{
			UpdateChildTransform(*child);
		}
	}*/
	std::stack<Transform*> stack;
	stack.push(this);

	while (!stack.empty()) {
		Transform* current = stack.top();
		stack.pop();
		current->UpdateWorldMatrix();

		for (auto iter = current->childsList.rbegin(); iter != current->childsList.rend(); ++iter) {
			stack.push(*iter);
		}
	}
}

void Transform::UpdateWorldMatrix()
{
	using namespace D2D1;

	const SIZE& ScreenSize = WinGameApp::GetClientSize();
	D2D1_MATRIX_3X2_F SM, RM, TM;
	if (!parent)
	{
		SM = Matrix3x2F::Scale(scale.value.x, scale.value.y);
		RM = Matrix3x2F::Rotation(rotation);
		TM = Matrix3x2F::Translation(position.value.x, ScreenSize.cy - position.value.y);
	}
	else
	{
		SM = Matrix3x2F::Scale(localScale.value.x, localScale.value.y);
		RM = Matrix3x2F::Rotation(localRotation);
		TM = Matrix3x2F::Translation(localPosition.value.x, -localPosition.value.y); //부모에서 이미 화면 좌표계로 바꾸기 때문에 자식 로컬은 -localPosition.value.y
	}
	PM = Matrix3x2F::Translation(pivot.value.x, pivot.value.y);
	IPM = Matrix3x2F::Translation(-pivot.value.x, -pivot.value.y);

	WM = IPM * SM * RM * TM;
	Camera* mainCam = Camera::GetMainCamera(); //카메라 확인
	if (mainCam == nullptr || &mainCam->gameObject.transform != this) 
	{
		WM = PM * WM;  //카메라 제외하고 전부다 원위치로
	}
	IWM = WM; 
	D2D1InvertMatrix(&IWM);  //역행렬 계산
	CM = WM;
	if (!parent) //부모일때
	{
		if (mainCam)
		{
			CM = CM * mainCam->GetInvertMatrix(); 
		}
	}
	else //자식 일때
	{		
		CM = CM * parent->CM; 
		WM = WM * parent->WM;
		
		//Local To World
		scale.value.x = parent->scale.value.x * localScale.value.x;
		scale.value.y = parent->scale.value.y * localScale.value.y;

		Vector2 translation = localPosition;
		translation.x *= parent->scale.value.x;
		translation.y *= parent->scale.value.y;

		position.value = parent->position + translation;

		rotation.angle = parent->rotation + localRotation;
	}
}

void Transform::SerializedJson(ordered_json& jsonObj)
{
	ordered_json transformJson;
	transformJson["position"] = gameObject.transform.position;
	transformJson["localPosition"] = gameObject.transform.localPosition;

	transformJson["scale"] = gameObject.transform.scale;
	transformJson["localScale"] = gameObject.transform.localScale;

	transformJson["rotation"] = float(gameObject.transform.rotation);
	transformJson["localRotation"] = float(gameObject.transform.localRotation);

	jsonObj["Transform"].push_back(transformJson);
}

void Transform::DeSerializedJson(ordered_json& jsonObj)
{
	for (auto& transform : jsonObj["Transform"])
	{
		std::vector vec = transform["position"].get<JsonUtility::Vector2>();
		gameObject.transform.position = Vector2{ vec[0], vec[1] };
		vec = transform["localPosition"].get<JsonUtility::Vector2>();
		gameObject.transform.localPosition = Vector2{ vec[0], vec[1] };

		vec = transform["scale"].get<JsonUtility::Vector2>();
		gameObject.transform.scale = Vector2{ vec[0], vec[1] };
		vec = transform["localScale"].get<JsonUtility::Vector2>();
		gameObject.transform.localScale = Vector2{ vec[0], vec[1] };

		gameObject.transform.rotation = transform["rotation"].get<float>();
		gameObject.transform.localRotation = transform["localRotation"].get<float>();
	}
}

void Transform::SetParent(Transform& parent)
{
#pragma warning(disable:6011)

	if (this->parent)
	{
		for (auto iter = this->parent->childsList.begin(); iter != this->parent->childsList.end(); ++iter)
		{
			if (this == *iter)
			{
				this->parent->childsList.erase(iter);
				this->parent = nullptr;
				break;
			}
		}
	}
	this->parent = &parent;
	parent.childsList.push_back(this);

#pragma warning(default:6011)
}

void Transform::SetParent(GameObjectBase& parent)
{
	SetParent(parent.transform);
}

//부모 해제
void Transform::SetParent()
{
	if (this->parent)
	{
		std::list<Transform*> parentChilds = this->parent->childsList;
		for (auto iter = parentChilds.begin(); iter != parentChilds.end(); ++iter)
		{
			if (this == *iter)
			{
				parentChilds.erase(iter);
				this->parent = nullptr;
				break;
			}
		}
	}
}

void Transform::FlipX(bool isflip)
{
	float absX = abs(scale.x);
	if (isflip)
	{
		scale = Vector2{ -absX, scale.y };
	}
	else
	{
		scale = Vector2{ absX, scale.y };
	}
	isFlipX = isflip;
}

void Transform::FlipX()
{
	scale = Vector2{ -scale.x, scale.y };
	isFlipX = !isFlipX;
}

void Transform::FlipY(bool isflip)
{
	float absY = abs(scale.y);
	if (isflip)
	{
		scale = Vector2{scale.x, -absY };
	}
	else
	{
		scale = Vector2{scale.x, absY };
	}
	isFlipY = isflip;
}

void Transform::FlipY()
{
	scale = Vector2{ scale.x, -scale.y };
	isFlipY = !isFlipY;
}



Transform::TVector2::TVector2(const TVector2& other)
{
	value = other.value;
}

Transform::TVector2::TVector2(const Vector2& other)
{
	value = other;
}


Transform::TVector2::operator Vector2()
{
	return Vector2(value);
}

Vector2 Transform::TVector2::operator-(const Vector2& other)
{
	return value - other;
}

bool Transform::TVector2::operator!=(const Vector2& other)
{
	return (value.x != other.x || value.y != other.y);
}

bool Transform::TVector2::operator==(const Vector2& other)
{
	return (value.x == other.x && value.y == other.y);
}

Vector2 Transform::TVector2::operator+(const Vector2& other)
{
	return value + other;
}

Transform::TVector2& Transform::TVector2::operator=(const Vector2& other)
{
	return SetTVector(other);
}

Vector2 Transform::TVector2::operator*(const float scala) const
{
	return Vector2(value) * scala;
}

Transform::TVector2& Transform::TVector2::operator*=(const float scala)
{
	value.x *= scala;
	value.y *= scala;
	return *this;
}

Transform::TVector2& Transform::TVector2::operator+=(const Vector2& other)
{
	return SetTVector(value + other);
}

Transform::TVector2& Transform::TVector2::operator-=(const Vector2& other)
{
	return SetTVector(value - other);
}

void Transform::TVector2::InitTVector2(Transform* _thisTransform)
{
	if (!thisTransform)
	{
		thisTransform = _thisTransform;
	}
}

Transform::TVector2& Transform::TVector2::SetTVector(const Vector2& other)
{
	if (this == &(thisTransform->localPosition))
	{
		if (thisTransform->parent)
		{
			value.operator=(other);
			return thisTransform->localPosition;
		}
		else
		{
			DEBUG_PRINT("부모가 없는 오브젝트는 로컬 변경이 불가능 합니다.\n");
			return thisTransform->localPosition;
		}
	}
	else if (this == &(thisTransform->position))
	{
		if (thisTransform->parent)
		{
			DEBUG_PRINT("부모가 없는 오브젝트는 로컬 변경이 불가능 합니다.\n");
			return *this;
		}
		else
		{
			value.operator=(other);
			return *this;
		}
	}
	else if (this == &(thisTransform->localScale))
	{
		if (thisTransform->parent)
		{
			value.operator=(other);
			return thisTransform->localScale;
		}
		else
		{
			DEBUG_PRINT("부모가 없는 오브젝트는 로컬 변경이 불가능 합니다.\n");
			return thisTransform->localScale;
		}
	}
	else if (this == &(thisTransform->scale))
	{
		if (thisTransform->parent)
		{
			DEBUG_PRINT("부모가 없는 오브젝트는 로컬 변경이 불가능 합니다.\n");
			return *this;
		}
		else
		{
			value.operator=(other);
			return *this;
		}
	}
	else
	{
		value.operator=(other);
		return *this;
	}
}

void Transform::TFloat::InitTFloat(Transform* _thisTransform)
{
	if (!thisTransform)
	{
		thisTransform = _thisTransform;
	}
}

Transform::TFloat::TFloat(const float& rotation)
{
	this->angle = rotation;
}

Transform::TFloat::operator float() const
{
	return this->angle;
}

float& Transform::TFloat::operator=(const float& rotation)
{
	SetAngle(rotation);
	return this->angle;
}

float& Transform::TFloat::operator+=(const float& rotation)
{
	SetAngle(angle + rotation);
	return this->angle;
}

float& Transform::TFloat::operator-=(const float& rotation)
{
	SetAngle(angle - rotation);
	return this->angle;
}

void Transform::TFloat::SetAngle(const float& rotation)
{
	if (this == &(thisTransform->localRotation))
	{
		if (thisTransform->parent)
		{
			this->angle = rotation;
			return;
		}
		else
		{
			DEBUG_PRINT("부모가 없는 오브젝트는 로컬 변경이 불가능 합니다.\n");
			return;
		}
	}
	else if (this == &(thisTransform->rotation))
	{
		if (thisTransform->parent)
		{
			DEBUG_PRINT("부모가 없는 오브젝트는 로컬 변경이 불가능 합니다.\n");
			return;
		}
		else
		{
			this->angle = rotation;
			return;
		}
	}
}
