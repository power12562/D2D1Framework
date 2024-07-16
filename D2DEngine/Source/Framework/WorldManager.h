#pragma once
#include "Core/Scene/WorldBase.h"
#include "Core/GameObject/Base/GameObjectBase.h"

#include <typeinfo>
#include <queue>
#include <set>

class WorldManager
{
	friend class WinGameApp;
	friend void GameObjectBase::SetName(const wchar_t* name);
public:
	/** 씬을 불러옵니다*/
	template<typename T> static void LoadWorld();

	/** 씬을 언로드 합니다*/
	static void UnloadWorld();

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

	/** 실제로 Render 함수를 실행한 오브젝트 개수를 반환합니다.*/
	static int GetRenderCount() { return renderCount; }

	/** 오브젝트의 정렬이 필요할때 활성화 합니다. 정렬 후 false로 초기화됩니다.*/
	static bool ObjListSortFlag;

	/** 읽기전용 오브젝트 리스트를 반환합니다.*/
	static const std::list<GameObjectBase*>& GetCurrentObjList() { return currentWorld->gameObjectList; }

	/** 중복된 이름이면 번호를 붙여 이름을 재생성 해줍니다.*/
	static std::wstring GenerateUniqueName(const wchar_t* name);

	/** 현재 월드를 가져옵니다.*/
	static WorldBase* GetCurrentWorld() { return currentWorld; }

private:
	WorldManager();
	~WorldManager();

	static class WorldBase* currentWorld;
	static std::queue<GameObjectBase*> addQueueList;
	static std::set<std::wstring> delNameSetList;

	static int renderCount;

	/** 오브젝트의 정렬 기준 (그리는 우선 순위)*/
	static bool ObjectRenderCompare(const GameObjectBase* a, const GameObjectBase* b);

#pragma region WinGameApp->Run()루프에서만 호출하는 함수들
	/** 현재 씬 오브젝트들을 타입별로 정렬합니다.*/
	static void SortObjectList();

	/** 현재 씬 오브젝트들의 Update() 함수를 호출해줍니다.*/
	static void Update();

	/** 현재 씬 오브젝트들의 LateUpdate() 함수를 호출해줍니다.*/
	static void LateUpdate();

	/** 현재 씬 오브젝트들의 Matrix를 계산합니다.*/
	static void UpdateMatrix();

	/** 현재 씬 오브젝트들의 CullingBounds 영역을 계산합니다.*/
	static void UpdateCullingBouds();

	/** 현재 씬 오브젝트들의 Render() 함수를 호출해줍니다.*/
	static void Render();

	/** 예약된 게임 오브젝트들을 현재 씬에 추가한 뒤, 오브젝트의 Start() 함수를 호출해줍니다.*/
	static void AddObjectToQList();

	/** 예약된 게임 오브젝트들을 현재 씬에서 삭제합니다.*/
	static void DelObjectToSetList();
#pragma endregion

};

template<typename T>
inline void WorldManager::LoadWorld()
{
	// T가 SceneBase로부터 상속받는지 확인
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
	gameObject->objName = objectName;
	addQueueList.push(gameObject);

	ObjListSortFlag = true;
	return gameObject;
}

template<typename T>
inline GameObjectBase* WorldManager::AddGameObject(const wchar_t* objectName)
{
	// T가 GameObject로부터 상속받는지 확인
	static_assert(std::is_base_of<GameObjectBase, T>::value, "Is not Object");

	GameObjectBase* gameObject = new T;
	gameObject->objName = objectName;
	addQueueList.push(gameObject);

	ObjListSortFlag = true;
	return gameObject;
}

