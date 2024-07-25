#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>
#include <Core/Component/Collider/Base/ColliderBase.h>

class BlockCtrl : public ComponentBase, public ICollider2DNotify
{
public:
	BlockCtrl(GameObjectBase& gameObject);
	virtual ~BlockCtrl() override;
	
	void Init();

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;




private:
	GameObjectBase* player;
	class InputBinding* PlayerInput;
	bool downRot;
	float elapsedTime;

	float pLeft;
	float pRight;
	float pTop;
	float pBottom;

	float mLeft;
	float mRight;
	float mTop;
	float mBottom;

	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;

	virtual void OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
};