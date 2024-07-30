#include "WorldManager.h"

#include <Vector/Vector2.h>
#include <Utility/JsonUtility.h>
#include <Utility/Debug.h>
#include <Framework/GameObjectFactory.h>

#include "Core/Scene/WorldBase.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include <Core/GameObject/Base/GameObjectCamera.h>
#include <Core/GameObject/Base/GameObjectUI.h>

#include "Core/Component/Camera.h"
#include <Core/Component/Collider/Base/ColliderBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

#include <vector>
#include <cassert>
#include <cwctype>
#include <iostream>
#include <ios>
#include <istream>
#include <fstream>
#include <sstream>
#include <iosfwd>
#include <filesystem>

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

std::vector<GameObjectBase*> WorldManager::FindGameObjectsWithTag(const wchar_t* tag)
{
	std::vector<GameObjectBase*> list;
	for (auto& obj : currentWorld->gameObjectList)
	{
		if (obj->tag == tag)
			list.push_back(obj);
	}
	return list;
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
		
		//DEBUG_PRINT("render : %d\n", renderCount);
	}
}

void WorldManager::AddObjectToQList()
{
	if (currentWorld && !addQueueList.empty())
	{
		std::queue<GameObjectBase*> addList = addQueueList;
		while (!addList.empty())
		{		
			auto& obj = addList.front();
			if (!obj->DontDestroyOnload)
			{
				obj->Start();
			}			
			obj->objName = WorldManager::GenerateUniqueName(obj->name);
			currentWorld->gameObjectList.push_back(obj);
			currentWorld->gameObjectMap[obj->name] = std::prev(currentWorld->gameObjectList.end());		
			addList.pop();
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
		WorldManager::AddObjectToQList();
		WorldManager::UpdateCullingBouds();
	}
}			

namespace JSON_KEY
{
	constexpr const char* TypeListKey = "GameObjectTypes"; //타입 리스트를 저장하는 키
};

void WorldManager::SaveCurrentWorldToJson(const wchar_t* path)
{
	using namespace JSON_KEY;

	std::wstring savePath{path};
	if (std::wstring::npos == savePath.rfind(L".json"))
	{
		savePath += L".json";
	}

	ordered_json worldJson;
	std::unordered_set<std::string> typeSet;
	worldJson[TypeListKey].push_back("");
	for (auto obj : currentWorld->gameObjectList)
	{
		ordered_json objJson;

		
		std::string objType = typeid(*obj).name();
		if (objType == typeid(GameObjectBase).name() ||
			objType == typeid(GameObjectCamera).name() ||
			objType == typeid(GameObjectUI).name())
		{
			continue; //Base클래스는 저장 x
		}
		//객체 타입 저장
		objType = objType.substr(6, objType.size());
		if (GameObjectFactory::GetRegistry().find(objType) == GameObjectFactory::GetRegistry().end())
		{
			continue; //레지스트리 매크로 플래그가 설정된 오브젝트만 저장
		}
		typeSet.insert(objType);   //중복 없이
		
		//오브젝트 저장
		obj->SerializedJson(objJson);
		worldJson[objType].push_back(objJson);
	}

	for (auto& type : typeSet)
	{
		worldJson[TypeListKey].push_back(type);
	}
	worldJson[TypeListKey].erase(worldJson[TypeListKey].begin());

	std::ofstream ofs(savePath);
	ofs << worldJson.dump(2);
	ofs.close();
}

bool WorldManager::LoadWorldToJson(const wchar_t* path)
{
	using namespace JSON_KEY;

	ordered_json worldJson;

	if (JsonUtility::ordered_jsonLoadToFile(path, worldJson))
	{
		WorldManager::LoadWorld<WorldBase>();
		try
		{
			for (auto& objType : worldJson[TypeListKey])
			{
				std::string typeKey = objType.get<std::string>();
				for (auto& objData : worldJson[typeKey])
				{
					GameObjectBase* object = GameObjectFactory::CreateGameObject(typeKey, objData["name"].get<std::wstring>());

					if (object)
					{
						object->DeSerializedJson(objData);
					}
				}			
			}
			return true;
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			return false;
		}
	}
	else
	{
		return false;
	}
}

void WorldManager::ClearObjectList()
{
	for (auto& obj : currentWorld->gameObjectList)
	{
		delete obj;
	} 
	currentWorld->gameObjectList.clear();
	currentWorld->gameObjectMap.clear();
}

void WorldManager::DontDestroyOnLoad(GameObjectBase& gameObject)
{
	gameObject.dontDestroyOnload = true;
}