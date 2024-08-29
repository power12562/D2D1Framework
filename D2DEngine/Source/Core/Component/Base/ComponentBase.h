#pragma once
#include <Vector/Vector2.h>
#include <Utility/JsonUtility.h>
#include <Utility/Debug.h>

class GameObjectBase;

/* Derived default

class Derived : public ComponentBase
{
public:
	Derived(GameObjectBase& gameObject) : ComponentBase(gameObject) 
	{
	
	}
	virtual ~Derived() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;
};

*/
class ComponentBase
{
	friend class GameObjectBase;
public:
	ComponentBase(GameObjectBase& gameObject);
	virtual ~ComponentBase();

	GameObjectBase& gameObject;

	bool enabled = true;

	template<typename T> T& AddComponent();
	template<typename T> T& GetComponent();
	template<typename T> T* IsComponent();

	class Transform& GetTransform() const;
	__declspec(property(get = GetTransform)) Transform& transform;

	/** 게임 오브젝트를 삭제합니다.*/
	void Destroy(GameObjectBase& gameObject);

protected:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();


	/** Json 직렬화화가 필요한 내용을 오버라이딩 해서 작성합니다.*/
	virtual void SerializedJson(ordered_json& jsonObj);
	/** Json 역직렬화가 필요한 내용을 오버라이딩 해서 작성합니다.*/
	virtual void DeSerializedJson(ordered_json& jsonObj);
};


#include <Core/GameObject/Base/GameObjectBase.h>
template<typename T> inline T& ComponentBase::AddComponent()
{
	return gameObject.AddComponent<T>();
}

template<typename T> inline T& ComponentBase::GetComponent()
{
	return gameObject.GetComponent<T>();
}

template<typename T> inline T* ComponentBase::IsComponent()
{
	return gameObject.IsComponent<T>();
}


