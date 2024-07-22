#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

class FireEffectCtrl : public ComponentBase	, public ICollider2DNotify
{
	friend class PlayerBombCtrl;
public:
	FireEffectCtrl(GameObjectBase& gameObject);
	virtual ~FireEffectCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	static int rightCount;
	static int lefttCount;

	class SpriteAnimationRenderer* animationRenderer = nullptr;
	bool spawnNext = false;	
	void SpawnNext();
	void SpawnFire(const Vector2& nextPos, int dir);
	int bombDir = 0;

	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override{};
	virtual void OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};

	virtual void OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
};



