#pragma once
#include "Core/Scene/WorldBase.h"
#include "Core/GameObject/Base/GameObjectBase.h"

#include <iostream>
#include <queue>
#include <set>
#include <cassert>

class WorldManager
{
	friend class WinGameApp;
	friend void GameObjectBase::SetName(const wchar_t* name);
public:
	/** ���� �ҷ��ɴϴ�*/
	template<typename T> static void LoadWorld();

	/** ���� ��ε� �մϴ�*/
	static void UnloadWorld();

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

	/** ������ Render �Լ��� ������ ������Ʈ ������ ��ȯ�մϴ�.*/
	static int GetRenderCount() { return renderCount; }

private:
	WorldManager();
	~WorldManager();

	static class WorldBase* currentWorld;
	static std::queue<GameObjectBase*> addQueueList;
	static std::set<std::wstring> delNameSetList;

	static int renderCount;

	static bool isObjectListChange; //������Ʈ ����Ʈ�� ��ȭ�� ����

	/** ������Ʈ�� ���� ���� (�׸��� �켱 ����)*/
	static bool ObjectRenderCompare(const GameObjectBase* a, const GameObjectBase* b);

#pragma region WinGameApp->Run()���������� ȣ���ϴ� �Լ���
	/** ���� �� ������Ʈ���� Ÿ�Ժ��� �����մϴ�.*/
	static void SortObjectList();
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
inline void WorldManager::LoadWorld()
{
	// T�� SceneBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<WorldBase, T>::value, "Is not Scene");

	if (currentWorld)
	{
		delete currentWorld;
	}
	currentWorld = new T;
}

inline void WorldManager::UnloadWorld()
{
	if (currentWorld)
	{
		delete currentWorld;
	}
}

inline GameObjectBase* WorldManager::AddGameObject(const wchar_t* objectName)
{
	GameObjectBase* gameObject = new GameObjectBase;
	gameObject->name = objectName;
	addQueueList.push(gameObject);

	isObjectListChange = true;
	return gameObject;
}

template<typename T>
inline GameObjectBase* WorldManager::AddGameObject(const wchar_t* objectName)
{
	// T�� GameObject�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<GameObjectBase, T>::value, "Is not Object");

	GameObjectBase* gameObject = new T;
	gameObject->name = objectName;
	addQueueList.push(gameObject);

	isObjectListChange = true;
	return gameObject;
}
