#pragma once
#include <list>
#include "Core/Component/Transform.h"

class GameObjectBase
{
public:
	GameObjectBase();
	virtual ~GameObjectBase();
	
	virtual void Start();
	virtual void Update();
	virtual void Render();

	/** 트랜스폼*/
	Transform& GetTransform() { return *pTransform; }
	__declspec(property(get = GetTransform)) Transform& transform;

	/** 컴포넌트를 오브젝트에 추가합니다.*/
	template <typename T> void AddComponent();

	/** 컴포넌트를 가져옵니다.*/
	template <typename T> T& GetComponent();
	
private:	
	Transform* pTransform;
	std::list<ComponentBase*> componentsList;
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