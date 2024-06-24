#include "Core/GameObject/GameObjectBase.h"

GameObjectBase::GameObjectBase()
{
	pTransform = new Transform(*this);
}

GameObjectBase::~GameObjectBase()
{
	delete pTransform;
	for (auto& component : componentsList)
	{
		if (component)
		{
			delete component;
		}
	}
	componentsList.clear();
}

void GameObjectBase::Start()
{
	for (auto& component : componentsList)
	{
		component->Start();
	}
}

void GameObjectBase::Update()
{
	pTransform->Update();
	for (auto& component : componentsList)
	{
		component->Update();
	}
}

void GameObjectBase::Render()
{
	pTransform->Render();
	for (auto& component : componentsList)
	{
		component->Render();
	}
}

Transform& GameObjectBase::transform()
{
	return *pTransform;
}








