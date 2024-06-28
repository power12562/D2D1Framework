#include "Core/GameObject/Base/GameObjectBase.h"
#include "Framework/SceneManager.h"

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


GameObjectBase* GameObjectBase::Find(const wchar_t* name)
{
	return SceneManager::FindGameObject(name);
}

void GameObjectBase::SetName(const wchar_t* name)
{
	if (SceneManager::IsGameObject(name))
	{
		return; //이미 있는 이름
	}
	if (SceneManager::currentScene)
	{
		auto myIter = SceneManager::currentScene->gameObjectMap.find(objName);
		if (myIter != SceneManager::currentScene->gameObjectMap.end())
		{
			SceneManager::currentScene->gameObjectMap[name] = myIter->second;
			SceneManager::currentScene->gameObjectMap.erase(myIter);
		}
	}
	objName = name;
}




