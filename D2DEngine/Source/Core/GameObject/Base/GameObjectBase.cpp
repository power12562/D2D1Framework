#include "Core/GameObject/Base/GameObjectBase.h"

#include "Framework/SceneManager.h"

#include "Core/Component/Camera.h"

#include "Bounds/Bounds.h"

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
	pTransform->Start();
}

void GameObjectBase::Update()
{
	if (enable)
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->Update();
		}
	pTransform->Update();
}

void GameObjectBase::LateUpdate()
{
	if (enable)
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->LateUpdate();
		}
	pTransform->LateUpdate();
}

void GameObjectBase::Render()
{	
	if (enable)
		for (auto& component : componentsList)
		{
			if (component->enabled)
				component->Render();
		}
	pTransform->Render();
}


GameObjectBase* GameObjectBase::Find(const wchar_t* name)
{
	return SceneManager::FindGameObject(name);
}

void GameObjectBase::SetName(const wchar_t* name)
{
	if (SceneManager::IsGameObject(name))
	{
		return; //이미 있는 이름
	}
	if (SceneManager::currentScene)
	{
		auto myIter = SceneManager::currentScene->gameObjectMap.find(objName);
		if (myIter != SceneManager::currentScene->gameObjectMap.end())
		{
			SceneManager::currentScene->gameObjectMap[name] = myIter->second;
			SceneManager::currentScene->gameObjectMap.erase(myIter);
		}
	}
	objName = name;
}

const Bounds& GameObjectBase::GetBounds()
{
	UpdateBounds();
	return bounds;
}


void GameObjectBase::UpdateBounds()
{
	bounds.center = transform.position;

	bounds.extents = transform.pivot;
	bounds.extents.x *= transform.scale.x;
	bounds.extents.y *= transform.scale.y;

	bounds.size = bounds.extents * 2.f;

	bounds.leftTop.x = transform.position.x - bounds.extents.x;
	bounds.leftTop.y = transform.position.y + bounds.extents.y;

	bounds.rightBottom.x = transform.position.x + bounds.extents.x;
	bounds.rightBottom.y = transform.position.y - bounds.extents.y;

	Bounds::GetRotationBounds(bounds, transform.rotation);
}



