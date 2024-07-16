#include "Core/GameObject/Base/GameObjectBase.h"

#include "Framework/WorldManager.h"

#include "Core/Component/Camera.h"
#include "Core/Component/Collider/Interface/ICollider2DNotify.h"

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
			EraseColliderNotipyTable(component);
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

void GameObjectBase::UpdateCullingBounds()
{
	cullingBounds.center = transform.position;

	cullingBounds.extents = transform.pivot;
	cullingBounds.extents.x *= abs(transform.scale.x);
	cullingBounds.extents.y *= abs(transform.scale.y);

	cullingBounds.size = cullingBounds.extents * 2.f;

	cullingBounds.leftTop.x = transform.position.x - cullingBounds.extents.x;
	cullingBounds.leftTop.y = transform.position.y + cullingBounds.extents.y;

	cullingBounds.rightBottom.x = transform.position.x + cullingBounds.extents.x;	
	cullingBounds.rightBottom.y = transform.position.y - cullingBounds.extents.y;

	Bounds::GetRotationBounds(cullingBounds, transform.rotation);
}

void GameObjectBase::PushColliderNotipyTable(ComponentBase* component)
{
	collider2DNotifyTable[component] = ((ICollider2DNotify*)component);
}

void GameObjectBase::EraseColliderNotipyTable(ComponentBase* component)
{
	auto findIter = collider2DNotifyTable.find(component);
	if (findIter != collider2DNotifyTable.end())
	{
		collider2DNotifyTable.erase(findIter);
	}
}

