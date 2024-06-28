#pragma once
#include "Core/Component/Transform.h"

#include <list>
#include <string>

class GameObjectBase
{
public:
	GameObjectBase();
	virtual ~GameObjectBase();
	
	virtual void Start() final;
	virtual void Update() final;
	virtual void Render() final;

	/** Transform*/
	Transform& GetTransform() { return *pTransform; }
	__declspec(property(get = GetTransform)) Transform& transform;

	/** 컴포넌트를 오브젝트에 추가합니다.*/
	template <typename T> void AddComponent();

	/** 컴포넌트를 가져옵니다.*/
	template <typename T> T& GetComponent();

	/**현재 씬에서 게임 오브젝트를 찾습니다.*/
	static GameObjectBase* Find(const wchar_t* name);

	/** 오브젝트 이름을 변경합니다. */
	void SetName(const wchar_t* name);
	const wchar_t* GetName() { return objName.c_str(); }
	__declspec(property(get = GetName, put = SetName)) const wchar_t* name; //프로퍼티


private:
	Transform* pTransform;
	std::list<ComponentBase*> componentsList;
	std::wstring objName;
};


template<typename T> inline void GameObjectBase::AddComponent()
{
	// T가 ComponentBase로부터 상속받는지 확인
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");

	T* component = new T(*this);
	if (component)
	{
		componentsList.push_back(component);
	}
}

template<typename T> inline T& GameObjectBase::GetComponent()
{
	// T가 ComponentBase로부터 상속받는지 확인
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");

	T* component = nullptr;
	for (auto& parentComponent : componentsList)
	{
		component = dynamic_cast<T*>(parentComponent);
	}
	return *component;
}

