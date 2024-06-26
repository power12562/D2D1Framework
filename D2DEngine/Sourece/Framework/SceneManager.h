#pragma once
#include "Core/Scene/SceneBase.h"
#include <queue>
#include <set>

class SceneManager
{
	friend class WinGameApp;
public:
	/** ���� �ҷ��ɴϴ�*/
	template<typename T> static void LoadScene();
	/** ���� ���� ������Ʈ�� �߰��մϴ�.*/
	static void AddGameObject(GameObjectBase* gameObject);
	/** ���� ���� ������Ʈ�� �����մϴ�.*/
	static void DelGameObject(GameObjectBase* gameObject);

private:
	SceneManager();
	~SceneManager();

	static class SceneBase* currentScene;
	static std::queue<GameObjectBase*> addQueueList;
	static std::set<GameObjectBase*> delSetList;

#pragma region WinGameApp->Run()���������� ȣ���ϴ� �Լ���
	/** ���� �� ������Ʈ���� Update() �Լ��� ȣ�����ݴϴ�.*/
	static void Update();
	/** ���� �� ������Ʈ���� Render() �Լ��� ȣ�����ݴϴ�.*/
	static void Render();
	/** ����� ���� ������Ʈ���� ���� ���� �߰��� ��, ������Ʈ�� Start() �Լ��� ȣ�����ݴϴ�.*/
	static void AddObjectToQList();
	/** ����� ���� ������Ʈ���� ���� ������ �����մϴ�.*/
	static void DelObjectToSetList();
#pragma endregion

};

template<typename T> inline void SceneManager::LoadScene()
{
	// T�� SceneBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<SceneBase, T>::value, "Is not Scene");

	if (currentScene)
	{
		delete currentScene;
	}
	currentScene = new T;
}
