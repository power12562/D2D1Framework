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
	/** ¼øÈ¯¿ë ¸®½ºÆ®*/
	std::list<GameObjectBase*> gameObjectList;
	/** Å½»ö¿ë ¸Ê*/
	std::map<std::wstring, std::list<GameObjectBase*>::iterator> gameObjectMap;
};

