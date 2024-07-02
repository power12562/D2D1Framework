#pragma once
#include "Core/Component/Transform.h"

#include "Bounds/Bounds.h"

#include <list>
#include <string>

class GameObjectBase
{
public:
	GameObjectBase();
	virtual ~GameObjectBase();
	
	virtual void Start() final;
	virtual void Update() final;
	virtual void LateUpdate() final;
	virtual void Render() final;

	/** Transform*/
	Transform& GetTransform() { return *pTransform; }
	__declspec(property(get = GetTransform)) Transform& transform;

	/** ������Ʈ�� ������Ʈ�� �߰��մϴ�.*/
	template <typename T> T& AddComponent();

	/** ������Ʈ�� �����ɴϴ�.*/
	template <typename T> T& GetComponent();

	/**���� ������ ���� ������Ʈ�� ã���ϴ�.*/
	static GameObjectBase* Find(const wchar_t* name);

	/** ������Ʈ �̸��� �����մϴ�. */
	void SetName(const wchar_t* name);
	const wchar_t* GetName() { return objName.c_str(); }
	__declspec(property(get = GetName, put = SetName)) const wchar_t* name; //������Ƽ

	/** ������Ʈ�� �ٿ�� �ڽ� ���. Pivot�� �̿��� ���մϴ�.*/
	virtual const Bounds& GetBounds();
private:
	Transform* pTransform;
	std::list<ComponentBase*> componentsList;
	std::wstring objName;

	void UpdateBounds();
	Bounds bounds;

};


template<typename T> inline T& GameObjectBase::AddComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");

	T* component = new T(*this);
	if (component)
	{
		componentsList.push_back(component);		
	}
	return *component;
}

template<typename T> inline T& GameObjectBase::GetComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");

	T* component = nullptr;
	for (auto& parentComponent : componentsList)
	{
		component = dynamic_cast<T*>(parentComponent);
		if (component)
			break;
	}
	return *component;
}

