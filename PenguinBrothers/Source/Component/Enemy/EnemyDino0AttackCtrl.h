#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

class EnemyDino0AttackCtrl : public ComponentBase, public ICollider2DNotify
{
	class SpriteAnimationRenderer* animation;
public:
	EnemyDino0AttackCtrl(GameObjectBase& gameObject);
	virtual ~EnemyDino0AttackCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};

	virtual void OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
};

