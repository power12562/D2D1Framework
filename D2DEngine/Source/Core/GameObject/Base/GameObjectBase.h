#pragma once
#include "Core/Component/Transform.h"

#include "Bounds/Bounds.h"

#include <list>
#include <string>

enum class OBJECT_TYPE
{
	CAMERA,
	UI,
	OBJECT,
};

class GameObjectBase
{
protected: 
	OBJECT_TYPE objType = OBJECT_TYPE::OBJECT;;

public:
	GameObjectBase();
	virtual ~GameObjectBase();
	
	void Start();
	void Update();
	void LateUpdate();
	void Render();

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

	/** 오브젝트의 바운딩 박스 얻기. Pivot을 이용해 구합니다.*/
	const Bounds& GetBounds();

	/** Object Enable*/
	bool enable = true;

protected:
	/** GetBounds() return 이전에 호출되는 함수*/
	virtual void UpdateBounds();
	Bounds bounds;

private:
	Transform* pTransform;
	std::list<ComponentBase*> componentsList;
	std::wstring objName;
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

