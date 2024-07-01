#pragma once
class GameObjectBase;

class ComponentBase
{
	friend class GameObjectBase;
public:
	ComponentBase(GameObjectBase& gameObject);
	virtual ~ComponentBase();

	GameObjectBase& gameObject;

	bool enabled = true;

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();
};
