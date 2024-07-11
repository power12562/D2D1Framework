#include "Core/GameObject/Base/GameObjectBase.h"

#include "Framework/WorldManager.h"

#include "Core/Component/Camera.h"

#include "Bounds/Bounds.h"
#include <cstdlib>

GameObjectBase::GameObjectBase()
{
	pTransform = new Transform(*this);
}

GameObjectBase::~GameObjectBase()
{
	delete pTransform;
	for (auto& component : componentsList)
	{
		if (component)
		{
			delete component;
		}
	}
	componentsList.clear();
}

void GameObjectBase::Start()
{
	for (auto& component : componentsList)
	{
		component->Start();
	}
}

void GameObjectBase::Update()
{
	if (enable)
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->Update();
		}
}

void GameObjectBase::LateUpdate()
{
	if (enable)
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->LateUpdate();
		}
}

void GameObjectBase::Render()
{	
	if (enable)
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->Render();
		}
}


GameObjectBase* GameObjectBase::Find(const wchar_t* name)
{
	return WorldManager::FindGameObject(name);
}

void GameObjectBase::SetName(const wchar_t* name)
{
	std::wstring wsName = WorldManager::GenerateUniqueName(name);
	if (WorldManager::currentWorld)
	{
		auto myIter = WorldManager::currentWorld->gameObjectMap.find(objName);
		if (myIter != WorldManager::currentWorld->gameObjectMap.end())
		{
			if (*myIter->second == this)
			{
				WorldManager::currentWorld->gameObjectMap[name] = myIter->second;
				WorldManager::currentWorld->gameObjectMap.erase(myIter);
			}	
		}
	}
	objName = wsName;
}

void GameObjectBase::SetOderLayer(int val)
{
	oderLayer = val;
	WorldManager::ObjListSortFlag = true;
}

void GameObjectBase::UpdateBounds()
{
	bounds.center = transform.position;

	bounds.extents = transform.pivot;
	bounds.extents.x *= abs(transform.scale.x);
	bounds.extents.y *= abs(transform.scale.y);

	bounds.size = bounds.extents * 2.f;

	bounds.leftTop.x = transform.position.x - bounds.extents.x;
	bounds.leftTop.y = transform.position.y + bounds.extents.y;

	bounds.rightBottom.x = transform.position.x + bounds.extents.x;	
	bounds.rightBottom.y = transform.position.y - bounds.extents.y;

	Bounds::GetRotationBounds(bounds, transform.rotation);
}

