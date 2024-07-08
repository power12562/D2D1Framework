#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Vector/Vector2.h"

class Movement : public ComponentBase
{
public:
	Movement(GameObjectBase& gameObject);
	virtual ~Movement() override;

	void SetSpeed(float Speed) { speed = Speed; };
	float GetSpeed() const { return speed; };
	virtual void SetDirection(const Vector2& Direction) { direction = Direction; }
	const Vector2& GetDirection() { return direction; };
											    
protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	float speed;
	Vector2 direction;

};