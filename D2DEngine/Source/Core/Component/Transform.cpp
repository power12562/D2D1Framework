#include "Core/Component/Transform.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/Component/Camera.h"

#include <stack>

Transform::Transform(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	using namespace D2D1;

	matrixWorld = Matrix3x2F::Identity();
	matrixInvertWorld = Matrix3x2F::Identity();

	matrixMainCamera = Matrix3x2F::Identity();

	position.InitTVector2(this);
	localPosition.InitTVector2(this);
	matrixTranslation = Matrix3x2F::Identity();

	rotation.InitTFloat(this);
	localRotation.InitTFloat(this);
	matrixRotation = Matrix3x2F::Identity();

	scale.InitTVector2(this);
	localScale.InitTVector2(this);
	matrixScale = Matrix3x2F::Identity();

	pivot.InitTVector2(this);
	matrixPivot = Matrix3x2F::Identity();
	matrixInvertPivot = Matrix3x2F::Identity();
}

Transform::~Transform()
{
}

void Transform::Update()
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

void Transform::Render()
{

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
	if (!parent)
	{
		matrixScale = Matrix3x2F::Scale(scale.value.x, scale.value.y);
		matrixRotation = Matrix3x2F::Rotation(rotation);
		matrixTranslation = Matrix3x2F::Translation(position.value.x, ScreenSize.cy - position.value.y);
	}
	else
	{
		matrixScale = Matrix3x2F::Scale(localScale.value.x, localScale.value.y);
		matrixRotation = Matrix3x2F::Rotation(localRotation);
		matrixTranslation = Matrix3x2F::Translation(localPosition.value.x, ScreenSize.cy - localPosition.value.y);
	}
	matrixPivot = Matrix3x2F::Translation(pivot.value.x, pivot.value.y);
	matrixInvertPivot = Matrix3x2F::Translation(-pivot.value.x, -pivot.value.y);

	matrixWorld = matrixPivot * (matrixInvertPivot * matrixScale * matrixRotation * matrixTranslation);
	matrixInvertWorld = matrixWorld;
	D2D1InvertMatrix(&matrixInvertWorld);
	matrixMainCamera = matrixWorld;
	if (Camera* main = Camera::GetMainCamera())
	{
		matrixMainCamera = matrixMainCamera * main->GetInvertMatrix();
	}
	if (parent)
	{
		matrixWorld = matrixWorld * parent->matrixWorld;
		matrixMainCamera = matrixMainCamera * parent->matrixMainCamera; //matrix

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
			return thisTransform->localPosition;
		}
	}
	else if (this == &(thisTransform->position))
	{
		if (thisTransform->parent)
		{
			thisTransform->position.value = other;
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
			return thisTransform->localScale;
		}
	}
	else if (this == &(thisTransform->scale))
	{
		if (thisTransform->parent)
		{
			thisTransform->scale.value = other;
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
			return;
		}
	}
	else if (this == &(thisTransform->rotation))
	{
		if (thisTransform->parent)
		{
			this->angle = rotation;
			return;
		}
		else
		{
			this->angle = rotation;
			return;
		}
	}
}
