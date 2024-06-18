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

	for (auto iter = parent.childsList.begin(); iter != parent.childsList.end(); ++iter)
	{
		if (this == *iter)
		{
			parent.childsList.erase(iter);
			this->parent = nullptr;
		}
	}
	this->parent = &parent;
	parent.childsList.push_back(this);

#pragma warning(default:6011)
}