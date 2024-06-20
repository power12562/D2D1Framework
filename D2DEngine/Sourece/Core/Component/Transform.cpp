#include "Core/Component/Transform.h"
#include "Framework/D2DRenderer.h"

Transform::Transform(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	using namespace D2D1;

	position.InitTVector2(this);
	rotation.InitTFloat(this);
	scale.InitTVector2(this);
	
	pivot.InitTVector2(this);
	mPivot = Matrix3x2F::Identity();
	
	localPosition.InitTVector2(this);
	mPosition = Matrix3x2F::Identity();

	localRotation.InitTFloat(this);
	mRotation = Matrix3x2F::Identity();

	localScale.InitTVector2(this);	
	mScale = Matrix3x2F::Identity();
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

	if (!parent)
	{
		mScale = Matrix3x2F::Scale(scale.x, scale.y);
		mRotation = Matrix3x2F::Rotation(-rotation);
		mPosition = Matrix3x2F::Translation(position.x - pivot.x, position.y - pivot.y);
		mPivot = Matrix3x2F::Translation(pivot.x, pivot.y);
		mInvertPivot = Matrix3x2F::Translation(pivot.x, pivot.y);
		mInvertPivot.Invert();
	}
	else if (parent)
	{
		mScale = Matrix3x2F::Scale(localScale.x, localScale.y);
		mRotation = Matrix3x2F::Rotation(-localRotation);
		mPosition = Matrix3x2F::Translation(localPosition.x - pivot.x, localPosition.y - pivot.y);
		mPivot = Matrix3x2F::Translation(pivot.x, pivot.y);
		mInvertPivot = Matrix3x2F::Translation(pivot.x, pivot.y);
		mInvertPivot.Invert();
	}
	
	worldMatrix = mInvertPivot * mScale * mRotation * mPosition * mPivot;
	if (parent)
	{
		worldMatrix = worldMatrix * parent->worldMatrix;
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

void Transform::TVector2::InitTVector2(Transform* _thisTransform)
{
	if (!thisTransform)
	{
		thisTransform = _thisTransform;
	}
}

Transform::TVector2::TVector2(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
}

Vector2& Transform::TVector2::operator=(const Vector2& other)
{
	return SetTVector(other);
}

Vector2& Transform::TVector2::operator+=(const Vector2& other)
{
	return SetTVector(*this + other);
}

Vector2& Transform::TVector2::operator-=(const Vector2& other)
{
	return SetTVector(*this - other);
}

Vector2& Transform::TVector2::SetTVector(const Vector2& other)
{
	thisTransform->isTranslation = true;
	if (this == &(thisTransform->localPosition))
	{
		assert(thisTransform->parent && "부모가 없는 Transform은 local을 변경할 수 없습니다.");		
		return Vector2::operator=(other);
	}
	else if(this == &(thisTransform->pivot))
	{
		return Vector2::operator=(other);
	}
	else if (this == &(thisTransform->scale))
	{
		return  Vector2::operator=(other);
	}
	else if (this == &(thisTransform->position))
	{
		if (thisTransform->parent)
		{
			//추가 필요
			

			return thisTransform->position;
		}
		else
		{
			return  Vector2::operator=(other);
		}
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
		assert(thisTransform->parent && "부모가 없는 Transform은 local을 변경할 수 없습니다.");
		this->angle = rotation;
		return;
	}
	else if (this == &(thisTransform->localRotation))
	{
		this->angle = rotation;
	}
	else if (this == &(thisTransform->rotation))
	{
		if (thisTransform->parent)
		{
			//추가 필요

		}
		else
		{
			this->angle = rotation;
		}
	}
}
