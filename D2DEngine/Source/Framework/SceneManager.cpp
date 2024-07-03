#include "SceneManager.h"
#include "Core/Scene/SceneBase.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

#include <vector>

SceneBase* SceneManager::currentScene = nullptr;
std::queue<GameObjectBase*> SceneManager::addQueueList;
std::set<std::wstring> SceneManager::delNameSetList;

int SceneManager::renderCount = 0;

bool SceneManager::isObjectListChange = true;

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}

void SceneManager::DelGameObject(const wchar_t* objectName)
{
	delNameSetList.insert(objectName);
	isObjectListChange = true;
}

void SceneManager::DelGameObject(GameObjectBase& gameObject)
{
	delNameSetList.insert(gameObject.name);
	isObjectListChange = true;
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

bool SceneManager::IsGameObject(const wchar_t* objectName)
{
	if (currentScene)
	{
		auto findIter = currentScene->gameObjectMap.find(objectName);
		if (findIter != currentScene->gameObjectMap.end())
		{
			return true;
		}
	}
	return false;
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

bool SceneManager::ObjectRenderCompare(const GameObjectBase* a, const GameObjectBase* b)
{
	return a->GetType() < b->GetType();
}

void SceneManager::SortObjectList()
{
	if (currentScene && isObjectListChange)
	{
		currentScene->gameObjectList.sort(SceneManager::ObjectRenderCompare);
		isObjectListChange = false;
	}
}

void SceneManager::LateUpdate()
{
	if (currentScene)
	{
		for (auto& item : currentScene->gameObjectList)
		{
			item->LateUpdate();
		}
	}
}

void SceneManager::Render()
{
	if (currentScene)
	{	
		if (Camera* mainCam = Camera::GetMainCamera())
		{
			renderCount = 0;
			const Bounds& mainCamBounds = mainCam->gameObject.GetBounds(); 
			for (auto& item : currentScene->gameObjectList)
			{
				if (&mainCamBounds == &item->GetBounds()) //카메라는 제외
					continue;

				if (mainCamBounds.AABB(item->GetBounds())) //AABB coulling
				{
					renderCount++;
					item->Render();
				}			
			}
		}
		else
		{
			assert(!"MainCamera is nullptr.");
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
			if (IsGameObject(obj->name))
			{
				assert(!"중복되는 오브젝트 이름입니다.");
				delete obj;
			}
			else
			{
				obj->Start();
				currentScene->gameObjectList.push_back(obj);
				currentScene->gameObjectMap[obj->name] = std::prev(currentScene->gameObjectList.end());
			}		
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
				delete *(findIter->second);
				currentScene->gameObjectList.erase(findIter->second);
				currentScene->gameObjectMap.erase(findIter);
			}				
		}
	}
}
