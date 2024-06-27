#include "SceneManager.h"
#include "Core/Scene/SceneBase.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include <vector>

SceneBase* SceneManager::currentScene = nullptr;
std::queue<GameObjectBase*> SceneManager::addQueueList;
std::set<GameObjectBase*> SceneManager::delSetList;

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}

void SceneManager::AddGameObject(GameObjectBase* gameObject)
{
	addQueueList.push(gameObject);
}

void SceneManager::DelGameObject(GameObjectBase* gameObject)
{
	delSetList.insert(gameObject);
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
			GameObjectBase* obj = addQueueList.front();
			obj->Start();
			currentScene->gameObjectList.push_back(obj);
			addQueueList.pop();
		}
	}
}

void SceneManager::DelObjectToSetList()
{
	if (currentScene && !delSetList.empty())
	{
		std::vector<GameObjectBase*> delVectorList;
		delVectorList.reserve(delSetList.size());
		for (auto& delObj : delSetList)
		{
			delVectorList.push_back(delObj);
		}
		delSetList.clear();

		//이름을 이용해서 맵에서 찾도록 변경해야함.
		for (int i = 0; i < delVectorList.size(); i++)
		{
			for (auto iter = currentScene->gameObjectList.begin(); iter != currentScene->gameObjectList.end(); ++iter)
			{
				if (*iter == delVectorList[i])
				{
					currentScene->gameObjectList.erase(iter);
					break;
				}
			}			
		}
	}
}
