#pragma once
#include "Core/GameObject/Base/GameObjectBase.h"

#include <list>
#include <map>
#include <string>

class SceneBase
{
	friend class SceneManager;
	friend void GameObjectBase::SetName(const wchar_t* name);
public:
	SceneBase();
	virtual ~SceneBase();

private:
	/** ��ȯ�� ����Ʈ*/
	std::list<GameObjectBase*> gameObjectList;
	/** Ž���� ��*/
	std::map<std::wstring, std::list<GameObjectBase*>::iterator> gameObjectMap;
};

