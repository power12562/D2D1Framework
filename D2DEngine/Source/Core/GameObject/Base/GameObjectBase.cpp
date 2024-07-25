#include "Core/GameObject/Base/GameObjectBase.h"

#include "Framework/WorldManager.h"
#include "Framework/ColliderManager.h"

#include <Core/Component/Rigidbody2D.h>
#include <Core/Component/Base/ComponentBase.h>
#include "Core/Component/Collider/Base/ColliderBase.h"
#include "Core/Component/Camera.h"
#include "Core/Component/Collider/Interface/ICollider2DNotify.h"

#include "Bounds/Bounds.h"
#include <cstdlib>

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
//#include <Framework/GameObjectFactory.h>
//REGISTER_GAMEOBJECFT(GameObjectBase)

GameObjectBase::GameObjectBase()
{
	pTransform = new Transform(*this);
	pRigidbody = nullptr;
}

GameObjectBase::~GameObjectBase()
{
	delete pTransform;
	delete pRigidbody;
	pRigidbodyEvent = nullptr;

;	for (auto& collider : colliderList)
	{
		if (collider)
		{
			EraseColliderNotipyTable(collider);
			delete collider;
		}
	}
	for (auto& component : componentsList)
	{
		if (component)
		{
			EraseColliderNotipyTable(component);
			delete component;
		}
	}
	componentsList.clear();
	colliderList.clear();
}

void GameObjectBase::Start()
{
	for (auto& component : componentsList)
	{
		component->Start();
	}
	for (auto& collider : colliderList)
	{
		collider->Start();
	}
	if (pRigidbody)
	{
		pRigidbody->Start();
	}
}

void GameObjectBase::Update()
{
	if (enable)
	{
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->Update();
		}
		for (auto& collider : colliderList)
		{
			if (collider->enabled)
				collider->Update();
		}
	}
	if (enable && pRigidbody && pRigidbody->enabled)
	{
		pRigidbody->Update();
	}
}

void GameObjectBase::LateUpdate()
{
	if (enable)
	{
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->LateUpdate();
		}
		for (auto& collider : colliderList)
		{
			if (collider->enabled)
				collider->LateUpdate();
		}
	}
	if (enable && pRigidbody && pRigidbody->enabled)
	{
		pRigidbody->LateUpdate();
	}
}

void GameObjectBase::Render()
{	
	if (enable)
	{
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->Render();
		}
		for (auto& collider : colliderList)
		{
			if (collider->enabled)
				collider->Render();
		}
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
	collider2DNotifyTable[component] = dynamic_cast<ICollider2DNotify*>(component);
}

void GameObjectBase::EraseColliderNotipyTable(ComponentBase* component)
{
	auto findIter = collider2DNotifyTable.find(component);
	if (findIter != collider2DNotifyTable.end())
	{
		collider2DNotifyTable.erase(findIter);
	}
}

void GameObjectBase::SerializedJson(ordered_json& jsonObj)
{
	jsonObj["name"] = name;

	pTransform->SerializedJson(jsonObj);

	if(pRigidbody)
		pRigidbody->SerializedJson(jsonObj);

	for (auto& com : componentsList)
	{
		com->SerializedJson(jsonObj);
	}
	for (auto& coll : colliderList)
	{
		coll->SerializedJson(jsonObj);
	}
}

void GameObjectBase::DeSerializedJson(ordered_json& jsonObj)
{
	//������Ʈ�� �����ڿ��� �߰� ���� ������Ʈ�� �ε尡 �ȵǴ� ������ �ִ�.
	objName = jsonObj["name"].get<std::wstring>().c_str();

	pTransform->DeSerializedJson(jsonObj);

	if (pRigidbody)
		pRigidbody->DeSerializedJson(jsonObj);

	for (auto& com : componentsList)
	{
		com->DeSerializedJson(jsonObj);
	}
	for (auto& coll : colliderList)
	{
		coll->DeSerializedJson(jsonObj);
	}
}

template<>
Transform& GameObjectBase::GetComponent()
{
	return *pTransform;
}

template<>
Rigidbody2D& GameObjectBase::AddComponent()
{
	if (pRigidbody == nullptr)
	{
		pRigidbody = new Rigidbody2D(*this);
		pRigidbodyEvent = dynamic_cast<ICollider2DNotify*>(pRigidbody);
	}
	return *pRigidbody;
}

template<>
Rigidbody2D& GameObjectBase::GetComponent()
{
	return *pRigidbody;
}