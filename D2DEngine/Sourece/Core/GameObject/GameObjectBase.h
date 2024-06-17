#pragma once
#include <list>
#include "Vector/Vector2.h"
#include "Core/Componet/ComponentBase.h"

struct Transform
{
	Vector2 position{0,0};
	float rotation = 0;
	Vector2 scale{1,1};
}; 

class GameObjectBase
{
public:
	GameObjectBase();
	virtual ~GameObjectBase();

	Transform transform;

	virtual void Update();
	virtual void Render();

	void SetParent(GameObjectBase* parent) { this->parent = parent; }
	GameObjectBase* GetParent() { return parent; }

	/** ������Ʈ�� ������Ʈ�� �߰��մϴ�.*/
	template <typename T> T* AddComponent();

	/** ������Ʈ�� �����ɴϴ�.*/
	template <typename T> T* GetComponent();

private:
	GameObjectBase* parent{};
	std::list<GameObjectBase*> childsList;
	std::list<ComponentBase*> componentsList;
};


template<typename T> inline T* GameObjectBase::AddComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
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