#include "WorldBase.h"
#include "Framework/WorldManager.h"

#include "Core/GameObject/MainCamera.h"

#include "Core/Component/Camera.h"


WorldBase::WorldBase()
{
	if (Camera::GetMainCamera() == nullptr)
	{
		WorldManager::AddGameObject<MainCamera>(L"MainCamera");
	}
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
