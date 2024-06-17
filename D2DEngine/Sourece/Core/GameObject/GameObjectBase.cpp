#include "Core/GameObject/GameObjectBase.h"
#include "Framework/D2DRenderer.h"

GameObjectBase::GameObjectBase()
{
}

GameObjectBase::~GameObjectBase()
{
	for (auto& component : componentsList)
	{
		if (component)
		{
			delete component;
		}
	}
	componentsList.clear();
}

void GameObjectBase::Update()
{
	for (auto& component : componentsList)
	{
		if (!parent && !childsList.empty())
		{
			UpdateChildTransform(*this);
		}
		component->Update();		
	}
}

void GameObjectBase::Render()
{
	for (auto& component : componentsList)
	{
		component->Render();
	}
}

void GameObjectBase::SetParent(GameObjectBase* parent)
{
#pragma warning(disable:6011)

	if (parent != nullptr)
	{
		for (auto iter = parent->childsList.begin(); iter != parent->childsList.end(); ++iter)
		{
			if (this == *iter)
			{
				parent->childsList.erase(iter);
				parent = nullptr;
			}
		}	
	}
	this->parent = parent;
	parent->childsList.push_back(this);

#pragma warning(default:6011)
}


void GameObjectBase::UpdateChildTransform(GameObjectBase& parent)
{
	for (auto& child : parent.childsList)
	{		
		child->transform.rotation = parent.transform.rotation + child->transform.localRotation;

		D2D1_VECTOR_2F rotPos = D2DRenderer::GetRotatedPoint({ child->transform.localPosition.x, child->transform.localPosition.y }, parent.transform.rotation);
		child->transform.position = Vector2{ rotPos.x, rotPos.y } + parent.transform.position;

		child->transform.scale = { parent.transform.scale.x * child->transform.localScale.x, parent.transform.scale.y * child->transform.localScale.y };
		if (!child->childsList.empty())
		{
			UpdateChildTransform(*child);
		}
	}
}
