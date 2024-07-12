#pragma once

class GameObjectBase;


/* Derived default

class Derived : public ComponentBase
{
public:
	Derived(GameObjectBase& gameObject) : ComponentBase(gameObject) {}
	virtual ~Derived() override;

protected:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
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

protected:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();	
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



