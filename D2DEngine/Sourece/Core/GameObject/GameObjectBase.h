#pragma once
#include <list>
#include "Vector/Vector2.h"
#include "Core/Componet/Base/ComponentBase.h"
#include "Core/Componet/Transform.h"

class GameObjectBase
{
	friend class Transform;
public:
	GameObjectBase();
	virtual ~GameObjectBase();
	
	virtual void Update();
	virtual void Render();

	/** 트랜스폼*/
	Transform& transform();

	/** 컴포넌트를 오브젝트에 추가합니다.*/
	template <typename T> T* AddComponent();

	/** 컴포넌트를 가져옵니다.*/
	template <typename T> T* GetComponent();
	
private:	
	Transform* pTransform;
	std::list<ComponentBase*> componentsList;
};


template<typename T> inline T* GameObjectBase::AddComponent()
{
	// T가 ComponentBase로부터 상속받는지 확인
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");

	T* component = new T(*this);
	if (component)
	{
		componentsList.push_back(component);

		return component;
	}

	return nullptr;
}

template<typename T> inline T* GameObjectBase::GetComponent()
{
	T* component = nullptr;
	for (auto& parentComponent : componentsList)
	{
		component = dynamic_cast<T*>(parentComponent);
	}
	return component;
}