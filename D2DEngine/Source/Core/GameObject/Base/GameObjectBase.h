#pragma once
#include "Bounds/Bounds.h"

#include <list>
#include <string>


class Transform;
class ComponentBase;

enum class OBJECT_TYPE
{
	CAMERA,
	OBJECT,
	UI,
};

/* Derived default 

class Derived : public GameObjectBase 
{
 public:
	Derived();
	virtual ~Derived() override;
}; 

*/
class GameObjectBase
{
	friend class WorldManager;
private:
	Transform* pTransform; //Ʈ������
	std::list<ComponentBase*> componentsList; //������Ʈ ����Ʈ
	std::wstring objName; //������Ʈ �̸�
	int oderLayer = 0; //���� ������Ʈ������ ���� ����

protected: 
	OBJECT_TYPE objType = OBJECT_TYPE::OBJECT;

public:
	GameObjectBase();
	virtual ~GameObjectBase();
	
	void Start();
	void Update();
	void LateUpdate();
	void Render();

	/** Object Enable*/
	bool enable = true;

	/** Tag*/
	std::wstring tag;

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

	/** ������Ʈ�� �ٿ�� �ڽ� ����.*/
	Bounds bounds;

	/** Object Type*/
	OBJECT_TYPE GetType() const { return objType; }

	void SetOderLayer(int val);
	int GetOderLayer() const { return oderLayer; }

	/** ���� Ÿ�Գ����� ���� ����*/
	__declspec(property(get = GetOderLayer, put = SetOderLayer)) int OderLayer;

protected:
	/** componet���� Update() ������ ȣ��Ǵ� �Լ�*/
	virtual void UpdateBounds();

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


#include <Core/Component/Transform.h>