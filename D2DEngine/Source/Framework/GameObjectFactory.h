#pragma once

#include <iostream>
#include <map>
#include <Framework/WorldManager.h>
#include <functional>

#include <cassert>

class GameObjectBase;

/* 오브젝트의 cpp에서 사용되는 메크로*/
#define REGISTER_GAMEOBJECFT(GameObjectType)\
GameObjectBase* CreateGameObject##GameObjectType() { return new  GameObjectType(); } \
bool Registered##GameObjectType = GameObjectFactory::RegisterGameObject(#GameObjectType, CreateGameObject##GameObjectType);

class GameObjectFactory
{
	using CreatorFunction = std::function<GameObjectBase* ()>;
public:
	/*Class 이름으로 오브젝트를 생성합니다.*/
	static GameObjectBase* CreateGameObject(const std::string& GameObjectType, const std::wstring& ObjectName)
	{
		auto findIter = GetRegistry().find(GameObjectType);
		if (findIter != GetRegistry().end())
		{
			GameObjectBase* gameObject = findIter->second();
			gameObject->objName = ObjectName.c_str();
			WorldManager::addQueueList.push(gameObject);

			WorldManager::ObjListSortFlag = true;
			return gameObject;
		}
		assert(!"존재하지 않는 키값입니다. 오브젝트 cpp에서 매크로 선언을 확인하세요.");
		return nullptr;
	}
	static bool RegisterGameObject(const std::string& GameObjectType, CreatorFunction creator)
	{
		std::map<std::string, CreatorFunction>& registry = GetRegistry();
		registry[GameObjectType] = creator;
		return true;
	}
	static std::map<std::string, CreatorFunction>& GetRegistry()
	{
		static std::map<std::string, CreatorFunction> registry;
		return registry;
	}
private:

};