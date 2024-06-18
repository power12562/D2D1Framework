#pragma once

class GameObjectBase;

class ComponentBase
{
	friend GameObjectBase;
public:
	ComponentBase(GameObjectBase& gameObject);
	virtual ~ComponentBase();

	bool enabled = true;
protected:
	virtual void Update() = 0;
	virtual void Render() = 0;

	class GameObjectBase& gameObject() { return gameobject; }
protected:
	GameObjectBase& gameobject;
};

