#pragma once
#include "Core/Componet/Base/ComponentBase.h"
#include "Vector/Vector2.h"
#include <list>

class Transform : public ComponentBase
{
public:
	Transform(GameObjectBase& gameObject);
	~Transform();

	Vector2 position{ 0,0 };
	float rotation = 0;
	Vector2 scale{ 1,1 };

	Vector2 localPosition{ 0,0 };
	float localRotation = 0;
	Vector2 localScale{ 1,1 };

	void SetParent(Transform& parent);
	Transform& GetParent() { return *parent; }

	virtual void Update() override;
	virtual void Render() override;

private:
	Transform* parent{};
	void UpdateChildTransform(Transform& parent);
	std::list<Transform*> childsList;
};



