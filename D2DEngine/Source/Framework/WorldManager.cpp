#include "WorldManager.h"

#include "Core/Scene/WorldBase.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"
#include <Core/Component/Collider/Base/ColliderBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

#include <vector>
#include <cassert>
#include <cwctype>

WorldBase* WorldManager::currentWorld = nullptr;
WorldBase* WorldManager::nextWorld = nullptr;

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

void WorldManager::UpdateCullingBouds()
{
	for (auto& item : currentWorld->gameObjectList)
	{
		item->UpdateCullingBounds();
	}
}

void WorldManager::Render()
{
	if (currentWorld)
	{		
		if (Camera* mainCam = Camera::GetMainCamera())
		{
			const Bounds& mainCamBounds = mainCam->gameObject.cullingBounds;
			renderCount = 0;		
			for (auto& item : currentWorld->gameObjectList)
			{
				if (&mainCamBounds == &item->cullingBounds) //카메라는 제외
					continue;

				if (mainCamBounds.AABB(item->cullingBounds)) //AABB coulling
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
			obj->objName = WorldManager::GenerateUniqueName(obj->name);
			currentWorld->gameObjectList.push_back(obj);
			currentWorld->gameObjectMap[obj->name] = std::prev(currentWorld->gameObjectList.end());		
			addQueueList.pop();
		}
	}
	return;
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
			auto findIter = currentWorld->gameObjectMap.find(delVectorList[i]);
			if (findIter != currentWorld->gameObjectMap.end())
			{
				delete *(findIter->second);
				currentWorld->gameObjectList.erase(findIter->second);
				currentWorld->gameObjectMap.erase(findIter);
			}				
		}
	}
}

std::wstring WorldManager::GenerateUniqueName(const wchar_t* name)
{
	std::wstring tempName{name};
	while (WorldManager::IsGameObject(tempName.c_str())) {
		size_t lastIndex = tempName.size() - 1;
		bool hasDigitSuffix = false;

		// Check if the name ends with a numeric suffix
		while (lastIndex > 0 && std::iswdigit(tempName[lastIndex]))
		{
			hasDigitSuffix = true;
			lastIndex--;
		}

		if (hasDigitSuffix)
		{
			// Increment the numeric suffix
			size_t digitStartIndex = lastIndex + 1;
			int number = std::stoi(tempName.substr(digitStartIndex)) + 1;
			tempName = tempName.substr(0, digitStartIndex) + std::to_wstring(number);
		}
		else
		{
			// Add the initial numeric suffix
			tempName += L"_0";
		}
	}
	return tempName;
}


void WorldManager::LoadNextWorld()
{
	if (nextWorld)
	{
		UnloadWorld();
		currentWorld = nextWorld;
		nextWorld = nullptr;
	}
}					  