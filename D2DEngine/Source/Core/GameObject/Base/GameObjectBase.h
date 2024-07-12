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
	Transform* pTransform; //트렌스폼
	std::list<ComponentBase*> componentsList; //컴포넌트 리스트
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

	/** 컴포넌트를 가져옵니다.*/
	template <typename T> T& GetComponent();

	/**현재 씬에서 게임 오브젝트를 찾습니다.*/
	static GameObjectBase* Find(const wchar_t* name);

	/** 오브젝트 이름을 변경합니다. */
	void SetName(const wchar_t* name);
	const wchar_t* GetName() { return objName.c_str(); }
	__declspec(property(get = GetName, put = SetName)) const wchar_t* name; //프로퍼티

	/** 오브젝트의 바운딩 박스 영역.*/
	Bounds bounds;

	/** Object Type*/
	OBJECT_TYPE GetType() const { return objType; }

	void SetOderLayer(int val);
	int GetOderLayer() const { return oderLayer; }

	/** 같은 타입끼리의 정렬 순서*/
	__declspec(property(get = GetOderLayer, put = SetOderLayer)) int OderLayer;

protected:
	/** componet들의 Update() 이전에 호출되는 함수*/
	virtual void UpdateBounds();

};


template<typename T> inline T& GameObjectBase::AddComponent()
{
	// T가 ComponentBase로부터 상속받는지 확인
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
	// T가 ComponentBase로부터 상속받는지 확인
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