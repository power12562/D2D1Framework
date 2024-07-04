#pragma once
#include "Core/GameObject/Base/GameObjectBase.h"

#include <list>
#include <unordered_map>
#include <string>

class WorldBase
{
	friend class WorldManager;
	friend void GameObjectBase::SetName(const wchar_t* name);
public:
	WorldBase();
	virtual ~WorldBase();

private:
	/** ��ȯ�� ����Ʈ*/
	std::list<GameObjectBase*> gameObjectList;
	/** Ž���� ��*/
	std::unordered_map<std::wstring, std::list<GameObjectBase*>::iterator> gameObjectMap;
};

