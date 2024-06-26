#pragma once
#include "Core/Scene/SceneBase.h"
#include <queue>
#include <set>

class SceneManager
{
	friend class WinGameApp;
public:
	/** 씬을 불러옵니다*/
	template<typename T> static void LoadScene();
	/** 현재 씬에 오브젝트를 추가합니다.*/
	static void AddGameObject(GameObjectBase* gameObject);
	/** 현재 씬에 오브젝트를 삭제합니다.*/
	static void DelGameObject(GameObjectBase* gameObject);

private:
	SceneManager();
	~SceneManager();

	static class SceneBase* currentScene;
	static std::queue<GameObjectBase*> addQueueList;
	static std::set<GameObjectBase*> delSetList;

#pragma region WinGameApp->Run()루프에서만 호출하는 함수들
	/** 현재 씬 오브젝트들의 Update() 함수를 호출해줍니다.*/
	static void Update();
	/** 현재 씬 오브젝트들의 Render() 함수를 호출해줍니다.*/
	static void Render();
	/** 예약된 게임 오브젝트들을 현재 씬에 추가한 뒤, 오브젝트의 Start() 함수를 호출해줍니다.*/
	static void AddObjectToQList();
	/** 예약된 게임 오브젝트들을 현재 씬에서 삭제합니다.*/
	static void DelObjectToSetList();
#pragma endregion

};

template<typename T> inline void SceneManager::LoadScene()
{
	// T가 SceneBase로부터 상속받는지 확인
	static_assert(std::is_base_of<SceneBase, T>::value, "Is not Scene");

	if (currentScene)
	{
		delete currentScene;
	}
	currentScene = new T;
}
