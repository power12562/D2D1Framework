#pragma once

#include <iostream>
#include <map>
#include <functional>

#include <cassert>

class GameObjectBase;

/* ������Ʈ�� cpp���� ���Ǵ� ��ũ��*/
#define REGISTER_GAMEOBJECFT(GameObjectType)\
GameObjectBase* CreateGameObject##GameObjectType() { return new  GameObjectType(); } \
bool Registered##GameObjectType = GameObjectFactory::RegisterGameObject(#GameObjectType, CreateGameObject##GameObjectType);

class GameObjectFactory
{
	using CreatorFunction = std::function<GameObjectBase* ()>;
public:
	/*Class �̸����� ������Ʈ�� �����մϴ�.*/
	static GameObjectBase* CreateGameObject(const std::string& GameObjectType)
	{
		auto findIter = GetRegistry().find(GameObjectType);
		if (findIter != GetRegistry().end())
		{
			return findIter->second();
		}
		assert(!"�������� �ʴ� Ű���Դϴ�. ������Ʈ cpp���� ��ũ�� ������ Ȯ���ϼ���.");
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