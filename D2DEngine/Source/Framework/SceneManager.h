#pragma once
#include "Core/Scene/SceneBase.h"
#include "Core/GameObject/Base/GameObjectBase.h"

#include <iostream>
#include <queue>
#include <set>
#include <cassert>

class SceneManager
{
	friend class WinGameApp;
	friend void GameObjectBase::SetName(const wchar_t* name);
public:
	/** ���� �ҷ��ɴϴ�*/
	template<typename T> static void LoadScene();
	
	/** ���� ��ε� �մϴ�*/
	static void UnloadScene();

	/** ���� ���� �⺻ ������Ʈ�� �߰��մϴ�.*/
	static GameObjectBase* AddGameObject(const wchar_t* objectName);
	/** ���� ���� Ư�� ������Ʈ�� �߰��մϴ�.*/
	template<typename T> static GameObjectBase* AddGameObject(const wchar_t* objectName);

	/** ���� ���� ������Ʈ�� �����մϴ�.*/
	static void DelGameObject(const wchar_t* objectName);
	static void DelGameObject(GameObjectBase& gameObject);

	/** ���� ���� ������Ʈ�� �˻��մϴ�.*/
	static GameObjectBase* FindGameObject(const wchar_t* objectName);

	/** ���� ���� ������Ʈ ���� ������ ��ȯ�մϴ�.*/
	static bool IsGameObject(const wchar_t* objectName);

private:
	SceneManager();
	~SceneManager();

	static class SceneBase* currentScene;
	static std::queue<GameObjectBase*> addQueueList;
	static std::set<std::wstring> delNameSetList;

#pragma region WinGameApp->Run()���������� ȣ���ϴ� �Լ���
	/** ���� �� ������Ʈ���� Update() �Լ��� ȣ�����ݴϴ�.*/
	static void Update();
	/** ���� �� ������Ʈ���� LateUpdate() �Լ��� ȣ�����ݴϴ�.*/
	static void LateUpdate();
	/** ���� �� ������Ʈ���� Render() �Լ��� ȣ�����ݴϴ�.*/
	static void Render();
	/** ����� ���� ������Ʈ���� ���� ���� �߰��� ��, ������Ʈ�� Start() �Լ��� ȣ�����ݴϴ�.*/
	static void AddObjectToQList();
	/** ����� ���� ������Ʈ���� ���� ������ �����մϴ�.*/
	static void DelObjectToSetList();
#pragma endregion

};

template<typename T>
inline void SceneManager::LoadScene()
{
	// T�� SceneBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<SceneBase, T>::value, "Is not Scene");

	if (currentScene)
	{
		delete currentScene;
	}
	currentScene = new T;
}

inline void SceneManager::UnloadScene()
{
	if (currentScene)
	{
		delete currentScene;
	}
}

inline GameObjectBase* SceneManager::AddGameObject(const wchar_t* objectName)
{
	GameObjectBase* gameObject = new GameObjectBase;
	gameObject->name = objectName;
	addQueueList.push(gameObject);
	return gameObject;
}

template<typename T>
inline GameObjectBase* SceneManager::AddGameObject(const wchar_t* objectName)
{
	// T�� GameObject�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<GameObjectBase, T>::value, "Is not Object");

	GameObjectBase* gameObject = new T;
	gameObject->name = objectName;
	addQueueList.push(gameObject);
	return gameObject;
}