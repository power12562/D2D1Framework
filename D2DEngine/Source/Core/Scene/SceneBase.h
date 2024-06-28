#pragma once
#include <list>
#include <map>
#include <string>

class GameObjectBase;

class SceneBase
{
	friend class SceneManager;
public:
	SceneBase();
	virtual ~SceneBase();

private:
	/** ��ȯ�� ����Ʈ*/
	std::list<GameObjectBase*> gameObjectList;
	/** Ž���� ��*/
	std::map<std::wstring, std::list<GameObjectBase*>::iterator> gameObjectMap;
};

