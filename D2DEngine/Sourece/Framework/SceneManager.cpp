#include "SceneManager.h"
#include "Core/Scene/SceneBase.h"
#include "Core/GameObject/GameObjectBase.h"

SceneBase* SceneManager::currentScene = nullptr;

void SceneManager::Start()
{
	if (currentScene)
	{
		for (auto& item : currentScene->gameObjectList)
		{
			item->Start();
		}
	}
}

void SceneManager::Update()
{
	if (currentScene)
	{
		for (auto& item : currentScene->gameObjectList)
		{
			item->Update();
		}
	}
}

void SceneManager::Render()
{
	if (currentScene)
	{
		for (auto& item : currentScene->gameObjectList)
		{
			item->Render();
		}
	}
}

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}