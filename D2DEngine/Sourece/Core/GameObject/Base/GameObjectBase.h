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

	/** Ʈ������*/
	Transform& GetTransform() { return *pTransform; }
	__declspec(property(get = GetTransform)) Transform& transform;

	/** ������Ʈ�� ������Ʈ�� �߰��մϴ�.*/
	template <typename T> void AddComponent();

	/** ������Ʈ�� �����ɴϴ�.*/
	template <typename T> T& GetComponent();
	
private:	
	Transform* pTransform;
	std::list<ComponentBase*> componentsList;
};


template<typename T> inline void GameObjectBase::AddComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");

	T* component = new T(*this);
	if (component)
	{
		componentsList.push_back(component);
	}
}

template<typename T> inline T& GameObjectBase::GetComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");

	T* component = nullptr;
	for (auto& parentComponent : componentsList)
	{
		component = dynamic_cast<T*>(parentComponent);
	}
	return *component;
}