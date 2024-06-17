#include "Core/GameObject/GameObjectBase.h"

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