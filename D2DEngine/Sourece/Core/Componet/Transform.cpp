#include "Core/Componet/Transform.h"
#include "Framework/D2DRenderer.h"

Transform::Transform(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

Transform::~Transform()
{
}

void Transform::Update()
{
	if (!parent && !childsList.empty())
	{
		UpdateChildTransform(*this);
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

		child->scale = { parent.scale.x * child->localScale.x, parent.scale.y * child->localScale.y };
		if (!child->childsList.empty())
		{
			UpdateChildTransform(*child);
		}
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
