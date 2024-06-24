#pragma once
#include <list>

class GameObjectBase;

class SceneBase
{
	friend class SceneManager;
public:
	SceneBase();
	virtual ~SceneBase();

protected:
	std::list<GameObjectBase*> gameObjectList;

};

