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

//게임 오브젝트를 상속받는 클래스의 cpp 파일에 다음 해더와 매크로를 추가해야 월드 json 저장이 가능합니다.
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
	Transform* pTransform; //트렌스폼
	class Rigidbody2D* pRigidbody; //리지드바디
	std::list<ComponentBase*> componentsList; //컴포넌트 리스트
	std::list<ColliderBase*> colliderList; //콜라이더 리스트
	std::unordered_map<ComponentBase*, ICollider2DNotify*> collider2DNotifyTable;
	std::wstring objName; //오브젝트 이름
	int oderLayer = 0; //같은 오브젝트끼리의 정렬 기준

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

	/** 컴포넌트를 오브젝트에 추가합니다.*/
	template <typename T> T& AddComponent();
	template<> Rigidbody2D& AddComponent();

	/** 컴포넌트를 가져옵니다. *존재 유무를 알고싶으면 IsComponent를 통해 null 체크를 해야합니다.*/
	template <typename T> T& GetComponent();
	template<> Rigidbody2D& GetComponent();
	
	/** 컴포넌트를 포인터로 반환합니다. 존재하지 않는 컴포넌트면 nullptr을 반환합니다.*/
	template <typename T> T* IsComponent();
	template<> Rigidbody2D* IsComponent<Rigidbody2D>();

	/**현재 씬에서 게임 오브젝트를 찾습니다.*/
	static GameObjectBase* Find(const wchar_t* name);

	/** 오브젝트 이름을 변경합니다. */
	void SetName(const wchar_t* name);
	const wchar_t* GetName() { return objName.c_str(); }
	__declspec(property(get = GetName, put = SetName)) const wchar_t* name; //프로퍼티

	/** 오브젝트의 바운딩 박스 영역.*/
	Bounds cullingBounds;

	/** Object Type*/
	OBJECT_TYPE GetType() const { return objType; }

	void SetOderLayer(int val);
	int GetOderLayer() const { return oderLayer; }

	/** 같은 타입끼리의 정렬 순서*/
	__declspec(property(get = GetOderLayer, put = SetOderLayer)) int OderLayer;

protected:
	/** 컬링용 바운딩 박스의 정보를 갱신한다.*/
	virtual void UpdateCullingBounds();

private:
	void PushColliderNotipyTable(ComponentBase* component);
	void EraseColliderNotipyTable(ComponentBase* component);

	/** Json 직렬화 */
	void SerializedJson(ordered_json& jsonObj);
	/** Json 역직렬화 */
	void DeSerializedJson(ordered_json& jsonObj);
};

template<typename T> inline T& GameObjectBase::AddComponent()
{
	// T가 ComponentBase로부터 상속받는지 확인
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

		if constexpr (std::is_base_of<ICollider2DNotify, T>::value) //콜라이더 이벤트 사용하는 컴포넌트인지 확인
		{
			PushColliderNotipyTable(component);
		}
	}
	return *component;
}

template<typename T>inline T& GameObjectBase::GetComponent()
{
	// T가 ComponentBase로부터 상속받는지 확인
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
	// T가 ComponentBase로부터 상속받는지 확인
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

