#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

enum class BombType
{
	blue,
	red,
	green,
	skyblue
};

class PlayerCtrl : public ComponentBase, public ICollider2DNotify
{
	class TextRenderer* stateDebugText = nullptr;
	class FiniteStateMachine* fsm;
public:
	PlayerCtrl(GameObjectBase& gameObject);
	virtual ~PlayerCtrl();

	BombType bombType = BombType::red;

	bool isJump;
	float moveSpeed;
	float slideSpeed;
	void SpawnBomb();

protected:
	virtual void Start();
	virtual void Update();

private:
	Vector2 dir = Vector2::Right;

	virtual void OnCollisionEnter2D(GameObjectBase* collision) override;
	virtual void OnCollisionStay2D(GameObjectBase* collision) override {};
	virtual void OnCollisionExit2D(GameObjectBase* collision) override {};

	virtual void OnTriggerEnter2D(GameObjectBase* collision) override {};
	virtual void OnTriggerStay2D(GameObjectBase* collision) override {};
	virtual void OnTriggerExit2D(GameObjectBase* collision) override {};
};

