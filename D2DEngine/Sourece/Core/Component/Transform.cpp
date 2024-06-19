#include "Core/Component/Transform.h"
#include "Framework/D2DRenderer.h"

Transform::Transform(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	position.InitTVector2(this);
	rotation.InitTFloat(this);
	scale.InitTVector2(this);
	
	localPosition.InitTVector2(this);
	localRotation.InitTFloat(this);
	localScale.InitTVector2(this);	
}

Transform::~Transform()
{
}

void Transform::Update()
{
	if (isTranslation && !parent && !childsList.empty())
	{
		UpdateChildTransform(*this);
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
		child->rotation = parent.rotation + child->localRotation;

		D2D1_VECTOR_2F rotPos = D2DRenderer::GetRotatedPoint({ child->localPosition.x, child->localPosition.y }, parent.rotation);
		child->position = Vector2{ rotPos.x, rotPos.y } + parent.position;

		child->scale = Vector2{ parent.scale.x * child->localScale.x, parent.scale.y * child->localScale.y };
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

void Transform::TVector2::InitTVector2(Transform* thisTransform)
{
	if (!pTransform)
	{
		pTransform = thisTransform;
	}
}

Transform::TVector2::TVector2(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
}

Vector2& Transform::TVector2::operator=(const Vector2& other)
{
	if (!pTransform->parent)
	{
		pTransform->isTranslation = true;
		return Vector2::operator=(other);
	}
	else
	{
		SetParentIsTranslation(*pTransform);
		return Vector2::operator=(other);
	}	
}

Vector2& Transform::TVector2::operator+=(const Vector2& other)
{
	if (!pTransform->parent)
	{
		pTransform->isTranslation = true;
		return Vector2::operator+=(other);
	}
	else
	{
		SetParentIsTranslation(*pTransform);
		return Vector2::operator+=(other);
	}
}

Vector2& Transform::TVector2::operator-=(const Vector2& other)
{
	if (!pTransform->parent)
	{
		pTransform->isTranslation = true;
		return Vector2::operator-=(other);
	}
	else
	{
		SetParentIsTranslation(*pTransform);
		return Vector2::operator-=(other);
	}
}

void Transform::TFloat::InitTFloat(Transform* thisTransform)
{
	if (!pTransform)
	{
		pTransform = thisTransform;
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

float& Transform::TFloat::operator=(const float rotation)
{
	pTransform->isTranslation = true;
	this->angle = rotation;
	return this->angle;
}

float& Transform::TFloat::operator+=(const float rotation)
{
	pTransform->isTranslation = true;
	this->angle += rotation;
	return this->angle;
}

float& Transform::TFloat::operator-=(const float rotation)
{
	pTransform->isTranslation = true;
	this->angle -= rotation;
	return this->angle;
}
