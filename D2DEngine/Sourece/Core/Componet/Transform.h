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

	/** 부모 오브젝트를 설정합니다. nullptr을 넘기면 헤제됩니다.*/
	void SetParent(Transform& parent);	
	void SetParent(void* ptr);
	Transform& GetParent() { return *parent; }

	virtual void Update() override;
	virtual void Render() override;

private:
	Transform* parent{};
	std::list<Transform*> childsList;
	void UpdateChildTransform(Transform& parent);
};



