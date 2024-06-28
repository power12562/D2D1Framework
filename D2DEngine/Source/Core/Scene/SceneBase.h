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
	/** ¼øÈ¯¿ë ¸®½ºÆ®*/
	std::list<GameObjectBase*> gameObjectList;
	/** Å½»ö¿ë ¸Ê*/
	std::map<std::wstring, std::list<GameObjectBase*>::iterator> gameObjectMap;
};

