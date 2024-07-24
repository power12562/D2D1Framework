#pragma once
#include <Bounds/Bounds.h>
#include <Utility/Ray.h>
#include <Utility/JsonUtility.h>

#include <type_traits>
#include <typeinfo>
#include <list>
#include <unordered_map>
#include <string>

class Transform;
class ComponentBase;
class ColliderBase;
class ICollider2DNotify;

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

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Derived)

*/

class GameObjectBase
{
	friend class GameObjectFactory;
	friend class WorldManager;
	friend class ColliderManager;
	friend ColliderBase* Ray::ShootRayFromPosition(const Vector2& position);
private:
	Transform* pTransform; //Ʈ������
	class Rigidbody2D* pRigidbody; //������ٵ�
	std::list<ComponentBase*> componentsList; //������Ʈ ����Ʈ
	std::list<ColliderBase*> colliderList; //�ݶ��̴� ����Ʈ
	std::unordered_map<ComponentBase*, ICollider2DNotify*> collider2DNotifyTable;
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
	template<> Rigidbody2D& AddComponent();

	/** ������Ʈ�� �����ɴϴ�. *���� ������ �˰������ IsComponent�� ���� null üũ�� �ؾ��մϴ�.*/
	template <typename T> T& GetComponent();
	template<> Rigidbody2D& GetComponent();
	
	/** ������Ʈ�� �����ͷ� ��ȯ�մϴ�. �������� �ʴ� ������Ʈ�� nullptr�� ��ȯ�մϴ�.*/
	template <typename T> T* IsComponent();
	template<> Rigidbody2D* IsComponent<Rigidbody2D>();

	/**���� ������ ���� ������Ʈ�� ã���ϴ�.*/
	static GameObjectBase* Find(const wchar_t* name);

	/** ������Ʈ �̸��� �����մϴ�. */
	void SetName(const wchar_t* name);
	const wchar_t* GetName() { return objName.c_str(); }
	__declspec(property(get = GetName, put = SetName)) const wchar_t* name; //������Ƽ

	/** ������Ʈ�� �ٿ�� �ڽ� ����.*/
	Bounds cullingBounds;

	/** Object Type*/
	OBJECT_TYPE GetType() const { return objType; }

	void SetOderLayer(int val);
	int GetOderLayer() const { return oderLayer; }

	/** ���� Ÿ�Գ����� ���� ����*/
	__declspec(property(get = GetOderLayer, put = SetOderLayer)) int OderLayer;

protected:
	/** �ø��� �ٿ�� �ڽ��� ������ �����Ѵ�.*/
	virtual void UpdateCullingBounds();

private:
	void PushColliderNotipyTable(ComponentBase* component);
	void EraseColliderNotipyTable(ComponentBase* component);

	/** Json ����ȭ */
	void SerializedJson(ordered_json& jsonObj);
	/** Json ������ȭ */
	void DeSerializedJson(ordered_json& jsonObj);
};

template<typename T> inline T& GameObjectBase::AddComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");
	static_assert(!std::is_base_of<Transform, T>::value, "Transform is always exist. Please use the GameObjectBase.transform");

	T* component = new T(*this);
	if (component)
	{
		if constexpr (std::is_base_of<ColliderBase, T>::value)
		{
			colliderList.push_back(component);
		}
		else
		{
			componentsList.push_back(component);
		}

		if constexpr (std::is_base_of<ICollider2DNotify, T>::value) //�ݶ��̴� �̺�Ʈ ����ϴ� ������Ʈ���� Ȯ��
		{
			PushColliderNotipyTable(component);
		}
	}
	return *component;
}

template<typename T>inline T& GameObjectBase::GetComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");
	static_assert(!std::is_base_of<Transform, T>::value, "Transform is always exist. Please use the GameObjectBase.transform");

	T* component = nullptr;
	if constexpr (std::is_base_of<ColliderBase, T>::value)
	{
		for (auto& parentCollider : colliderList)
		{
			if (typeid(*parentCollider) == typeid(T))
			{
				component = static_cast<T*>(parentCollider);
				break;
			}
		}
	}
	else
	{
		for (auto& parentComponent : componentsList)
		{
			if (typeid(*parentComponent) == typeid(T))
			{
				component = static_cast<T*>(parentComponent);
				break;
			}
		}
	}
	return *component;
}

template<typename T>
inline T* GameObjectBase::IsComponent()
{
	// T�� ComponentBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<ComponentBase, T>::value, "Is not component");
	static_assert(!std::is_base_of<Transform, T>::value, "Transform is always exist. Please use the GameObjectBase.transform");
	
	T* component = nullptr;
	if constexpr (std::is_base_of<ColliderBase, T>::value)
	{
		for (auto& parentCollider : colliderList)
		{
			if (typeid(*parentCollider) == typeid(T))
			{
				component = static_cast<T*>(parentCollider);
				break;
			}
		}
	}
	else
	{
		for (auto& parentComponent : componentsList)
		{
			if (typeid(*parentComponent) == typeid(T))
			{
				component = static_cast<T*>(parentComponent);
				break;
			}
		}
	}
	return component;
}

template<> 
inline Rigidbody2D* GameObjectBase::IsComponent<Rigidbody2D>()
{
	return pRigidbody;
}

#include <Core/Component/Transform.h>

