#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

class EnemyDino0Ctrl : public ComponentBase, public ICollider2DNotify
{
	class TextRenderer* stateDebugText;
	class FiniteStateMachine* fsm;
public:
	EnemyDino0Ctrl(GameObjectBase& gameObject);
	virtual ~EnemyDino0Ctrl();

	void SpawnFire();
protected:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:



	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};

	virtual void OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
};

