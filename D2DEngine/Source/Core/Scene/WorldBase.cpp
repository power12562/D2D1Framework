#include "WorldBase.h"
#include "Framework/WorldManager.h"
#include <Framework/TimeSystem.h>

#include "Core/GameObject/MainCamera.h"

#include "Core/Component/Camera.h"


WorldBase::WorldBase()
{
	TimeSystem::Time.timeScale = 1.0f;
}

WorldBase::~WorldBase()
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
