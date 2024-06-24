#include "Core/Component/Transform.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

Transform::Transform(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	using namespace D2D1;

	position.InitTVector2(this);
	localPosition.InitTVector2(this);
	mPosition = Matrix3x2F::Identity();

	rotation.InitTFloat(this);
	localRotation.InitTFloat(this);
	mRotation = Matrix3x2F::Identity();

	scale.InitTVector2(this);
	localScale.InitTVector2(this);
	mScale = Matrix3x2F::Identity();
	
	pivot.InitTVector2(this);
	mPivot = Matrix3x2F::Identity();	
	
}

Transform::~Transform()
{
}

void Transform::Update()
{
	if (isTranslation && !childsList.empty())
	{
		UpdateWorldMatrix();
		UpdateChildTransform(*this);
		isTranslation = false;
	}
	else if(isTranslation)
	{
		UpdateWorldMatrix();
		isTranslation = false;
	}
}

void Transform::Render()
{

}

void Transform::UpdateChildTransform(Transform& parent)
{
	for (auto& child : parent.childsList)
	{
		child->UpdateWorldMatrix();
		if (!child->childsList.empty())
		{
			UpdateChildTransform(*child);
		}
	}
}

void Transform::SetParentIsTranslation(Transform& transform)
{
	Transform* topParent = transform.parent;
	while (topParent->parent)
	{
		topParent = topParent->parent;
	}
	topParent->isTranslation = true;
}

void Transform::UpdateWorldMatrix()
{
	using namespace D2D1;

	const SIZE& ScreenSize = WinGameApp::GetClientSize();

	if (!parent)
	{
		mScale = Matrix3x2F::Scale(scale.value.x, scale.value.y);
		mRotation = Matrix3x2F::Rotation(-rotation);
		mPosition = Matrix3x2F::Translation(position.value.x - pivot.value.x, ScreenSize.cy - position.value.y - pivot.value.y);		
	}
	else if (parent)
	{
		mScale = Matrix3x2F::Scale(localScale.value.x, localScale.value.y);
		mRotation = Matrix3x2F::Rotation(-localRotation);
		mPosition = Matrix3x2F::Translation(localPosition.value.x - pivot.value.x, localPosition.value.y - pivot.value.y);
	}
	mPivot = Matrix3x2F::Translation(pivot.value.x, pivot.value.y);
	mInvertPivot = Matrix3x2F::Translation(pivot.value.x, pivot.value.y);
	mInvertPivot.Invert();
	
	worldMatrix = mInvertPivot * mScale * mRotation * mPosition * mPivot;
	if (parent)
	{
		worldMatrix = worldMatrix * parent->worldMatrix;
		Vector2 translation = { worldMatrix._31, WinGameApp::GetClientSize().cy - worldMatrix._32 };		
		position.value = translation;
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
//부모 헤제
void Transform::SetParent(void* ptr)
{
	if (ptr == nullptr && this->parent)
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

Vector2 Transform::TVector2::operator+(const Vector2& other)
{
	return value + other;
}

Transform::TVector2& Transform::TVector2::operator=(const Vector2& other)
{
	return SetTVector(other);
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
	thisTransform->isTranslation = true;
	if (this == &(thisTransform->localPosition))
	{
		if (thisTransform->parent)
		{
			value.operator=(other);
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
	thisTransform->isTranslation = true;
	if (this == &(thisTransform->localRotation))
	{
		if (thisTransform->parent)
		{
			this->angle = rotation;
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
