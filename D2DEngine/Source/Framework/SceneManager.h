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
	/** 씬을 불러옵니다*/
	template<typename T> static void LoadScene();
	
	/** 씬을 언로드 합니다*/
	static void UnloadScene();

	/** 현재 씬에 기본 오브젝트를 추가합니다.*/
	static GameObjectBase* AddGameObject(const wchar_t* objectName);
	/** 현재 씬에 특정 오브젝트를 추가합니다.*/
	template<typename T> static GameObjectBase* AddGameObject(const wchar_t* objectName);

	/** 현재 씬에 오브젝트를 삭제합니다.*/
	static void DelGameObject(const wchar_t* objectName);
	static void DelGameObject(GameObjectBase& gameObject);

	/** 현재 씬에 오브젝트를 검색합니다.*/
	static GameObjectBase* FindGameObject(const wchar_t* objectName);

	/** 현재 씬에 오브젝트 존재 유무를 반환합니다.*/
	static bool IsGameObject(const wchar_t* objectName);

private:
	SceneManager();
	~SceneManager();

	static class SceneBase* currentScene;
	static std::queue<GameObjectBase*> addQueueList;
	static std::set<std::wstring> delNameSetList;

#pragma region WinGameApp->Run()루프에서만 호출하는 함수들
	/** 현재 씬 오브젝트들의 Update() 함수를 호출해줍니다.*/
	static void Update();
	/** 현재 씬 오브젝트들의 LateUpdate() 함수를 호출해줍니다.*/
	static void LateUpdate();
	/** 현재 씬 오브젝트들의 Render() 함수를 호출해줍니다.*/
	static void Render();
	/** 예약된 게임 오브젝트들을 현재 씬에 추가한 뒤, 오브젝트의 Start() 함수를 호출해줍니다.*/
	static void AddObjectToQList();
	/** 예약된 게임 오브젝트들을 현재 씬에서 삭제합니다.*/
	static void DelObjectToSetList();
#pragma endregion

};

template<typename T>
inline void SceneManager::LoadScene()
{
	// T가 SceneBase로부터 상속받는지 확인
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
	// T가 GameObject로부터 상속받는지 확인
	static_assert(std::is_base_of<GameObjectBase, T>::value, "Is not Object");

	GameObjectBase* gameObject = new T;
	gameObject->name = objectName;
	addQueueList.push(gameObject);
	return gameObject;
}