#include "SceneBase.h"
#include "Framework/SceneManager.h"

#include "Core/GameObject/MainCamera.h"


SceneBase::SceneBase()
{
	SceneManager::AddGameObject<MainCamera>(L"MainCamera");
}

SceneBase::~SceneBase()
{
	if (!gameObjectList.empty())
	{
		for (auto& item : gameObjectList)
		{
			delete item;
		}
	}
	gameObjectMap.clear();
	gameObjectList.clear();
}
