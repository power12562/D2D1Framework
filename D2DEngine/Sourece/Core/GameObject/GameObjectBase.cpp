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
	pTransform->Start();
}

void GameObjectBase::Update()
{
	for (auto& component : componentsList)
	{
		component->Update();
	}
	pTransform->Update();
}

void GameObjectBase::Render()
{	
	for (auto& component : componentsList)
	{
		component->Render();
	}
	pTransform->Render();
}

Transform& GameObjectBase::transform()
{
	return *pTransform;
}








