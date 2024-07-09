#include "WorldManager.h"
#include "Core/Scene/WorldBase.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

#include <vector>
#include <cassert>

WorldBase* WorldManager::currentWorld = nullptr;
std::queue<GameObjectBase*> WorldManager::addQueueList;
std::set<std::wstring> WorldManager::delNameSetList;

int WorldManager::renderCount = 0;

bool WorldManager::ObjListSortFlag = true;

WorldManager::WorldManager()
{

}


WorldManager::~WorldManager()
{

}

void WorldManager::DelGameObject(const wchar_t* objectName)
{
	delNameSetList.insert(objectName);
	ObjListSortFlag = true;
}

void WorldManager::DelGameObject(GameObjectBase& gameObject)
{
	delNameSetList.insert(gameObject.name);
	ObjListSortFlag = true;
}

GameObjectBase* WorldManager::FindGameObject(const wchar_t* objectName)
{
	if (currentWorld)
	{
		auto findIter = currentWorld->gameObjectMap.find(objectName);
		if (findIter != currentWorld->gameObjectMap.end())
		{
			return *findIter->second;
		}	
	}
	return nullptr;	
}

bool WorldManager::IsGameObject(const wchar_t* objectName)
{
	if (currentWorld)
	{
		auto findIter = currentWorld->gameObjectMap.find(objectName);
		if (findIter != currentWorld->gameObjectMap.end())
		{
			return true;
		}
	}
	return false;
}

void WorldManager::Update()
{
	if (currentWorld)
	{
		for (auto& item : currentWorld->gameObjectList)
		{
			item->Update();
		}
	}
}

bool WorldManager::ObjectRenderCompare(const GameObjectBase* a, const GameObjectBase* b)
{
	OBJECT_TYPE typeA = a->GetType();
	OBJECT_TYPE typeB = b->GetType();
	if (typeA == typeB)
	{
		return a->OderLayer < b->OderLayer;
	}
	else
	{
		return typeA < typeB;
	}	
}

void WorldManager::SortObjectList()
{
	if (currentWorld && ObjListSortFlag)
	{
		currentWorld->gameObjectList.sort(WorldManager::ObjectRenderCompare);
		ObjListSortFlag = false;
	}
}

void WorldManager::LateUpdate()
{
	if (currentWorld)
	{
		for (auto& item : currentWorld->gameObjectList)
		{
			item->LateUpdate();
		}
	}
}

void WorldManager::UpdateMatrix()
{
	for (auto& item : currentWorld->gameObjectList)
	{
		item->transform.UpdateMatrix();
	}
}

void WorldManager::UpdateBouds()
{
	for (auto& item : currentWorld->gameObjectList)
	{
		item->UpdateBounds();
	}
}

void WorldManager::Render()
{
	if (currentWorld)
	{		
		if (Camera* mainCam = Camera::GetMainCamera())
		{
			const Bounds& mainCamBounds = mainCam->gameObject.bounds;
			renderCount = 0;		
			for (auto& item : currentWorld->gameObjectList)
			{
				if (&mainCamBounds == &item->bounds) //카메라는 제외
					continue;

				if (mainCamBounds.AABB(item->bounds)) //AABB coulling
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

void WorldManager::AddObjectToQList()
{
	if (currentWorld && !addQueueList.empty())
	{
		while (!addQueueList.empty())
		{		
			auto& obj = addQueueList.front();
			obj->Start();
			if (IsGameObject(obj->name))
			{
				assert(!"중복되는 오브젝트 이름입니다.");
				delete obj;
			}
			else
			{				
				currentWorld->gameObjectList.push_back(obj);
				currentWorld->gameObjectMap[obj->name] = std::prev(currentWorld->gameObjectList.end());
			}		
			addQueueList.pop();
		}
	}
}

void WorldManager::DelObjectToSetList()
{
	if (currentWorld && !delNameSetList.empty())
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
			auto findIter = currentWorld->gameObjectMap.find(delVectorList[0]);
			if (findIter != currentWorld->gameObjectMap.end())
			{
				delete *(findIter->second);
				currentWorld->gameObjectList.erase(findIter->second);
				currentWorld->gameObjectMap.erase(findIter);
			}				
		}
	}
}
