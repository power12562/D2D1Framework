#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"
#include "Core/Component/FSM/FSMState.h"

class PlayerCtrl : public ComponentBase
{
	class Movement* movement;
public:
	PlayerCtrl(GameObjectBase& gameObject);
	virtual ~PlayerCtrl();

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:
	Vector2 dir = Vector2::Right;
	float moveSpeed;
	float slideSpeed;
	void SpawnBomb();
};

