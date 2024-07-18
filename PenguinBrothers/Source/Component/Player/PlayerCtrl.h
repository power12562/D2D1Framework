#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"

enum class BombType
{
	blue,
	red,
	green,
	skyblue
};

class PlayerCtrl : public ComponentBase
{
	class TextRenderer* stateDebugText = nullptr;
	class FiniteStateMachine* fsm;
public:
	PlayerCtrl(GameObjectBase& gameObject);
	virtual ~PlayerCtrl();

	BombType bombType = BombType::red;

	float moveSpeed;
	float slideSpeed;
	void SpawnBomb();

protected:
	virtual void Start();
	virtual void Update();

private:
	Vector2 dir = Vector2::Right;
};
