#include "SceneManager.h"
#include "Core/Scene/SceneBase.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include <vector>
#include <cassert>

SceneBase* SceneManager::currentScene = nullptr;
std::queue<std::pair<std::wstring, GameObjectBase*>> SceneManager::addQueueList;
std::set<std::wstring> SceneManager::delNameSetList;

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}

GameObjectBase* SceneManager::AddGameObject(const wchar_t* objectName)
{	
	if (currentScene)
	{
		auto iter = currentScene->gameObjectMap.find(objectName);
		if (iter != currentScene->gameObjectMap.end())
		{
			MessageBox(GetActiveWindow(), L"중복되는 이름입니다.", L"SceneManager::AddGameObject()", MB_OK);
			assert(!"중복되는 오브젝트 이름입니다.");
			return nullptr;
		}
	}
	GameObjectBase* gameObject = new GameObjectBase;
	addQueueList.push(std::pair<std::wstring, GameObjectBase*>(objectName, gameObject));
	return gameObject;
}

void SceneManager::DelGameObject(const wchar_t* objectName)
{
	delNameSetList.insert(objectName);
}

GameObjectBase* SceneManager::FindGameObject(const wchar_t* objectName)
{
	if (currentScene)
	{
		auto findIter = currentScene->gameObjectMap.find(objectName);
		if (findIter != currentScene->gameObjectMap.end())
		{
			return *findIter->second;
		}	
	}
	return nullptr;	
}

void SceneManager::Update()
{
	if (currentScene)
	{
		for (auto& item : currentScene->gameObjectList)
		{
			item->Update();
		}
	}
}

void SceneManager::Render()
{
	if (currentScene)
	{
		for (auto& item : currentScene->gameObjectList)
		{
			item->Render();
		}
	}
}

void SceneManager::AddObjectToQList()
{
	if (currentScene && !addQueueList.empty())
	{
		while (!addQueueList.empty())
		{
			auto& obj = addQueueList.front();
			obj.second->Start();
			currentScene->gameObjectList.push_back(obj.second);
			currentScene->gameObjectMap[obj.first] = std::prev(currentScene->gameObjectList.end());
			addQueueList.pop();
		}
	}
}

void SceneManager::DelObjectToSetList()
{
	if (currentScene && !delNameSetList.empty())
	{
		std::vector<std::wstring> delVectorList;
		delVectorList.reserve(delNameSetList.size());
		for (auto& delObj : delNameSetList)
		{
			delVectorList.push_back(delObj);
		}
		delNameSetList.clear();

		for (int i = 0; i < delVectorList.size(); i++)
		{
			auto findIter = currentScene->gameObjectMap.find(delVectorList[0]);
			if (findIter != currentScene->gameObjectMap.end())
			{
				currentScene->gameObjectList.erase(findIter->second);
				currentScene->gameObjectMap.erase(findIter);
			}				
		}
	}
}
