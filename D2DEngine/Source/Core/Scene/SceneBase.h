#pragma once
#include "Core/GameObject/Base/GameObjectBase.h"

#include <list>
#include <unordered_map>
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
	std::unordered_map<std::wstring, std::list<GameObjectBase*>::iterator> gameObjectMap;
};

