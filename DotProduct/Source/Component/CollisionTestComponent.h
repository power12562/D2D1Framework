#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

class CollisionTestComponent : public ComponentBase, public ICollider2DNotify
{
public:
	CollisionTestComponent(GameObjectBase& gameObject);
	virtual ~CollisionTestComponent() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;

private:
	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};

	virtual void OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;

private:
	class Rigidbody2D* rb = nullptr;
	class BoxCollider2D* boxCollider = nullptr;
	BoxCollider2D* testBox = nullptr;	
};