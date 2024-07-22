#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

#include <Vector/Vector2.h>

#include <list>

class Rigidbody2D : public ComponentBase, public ICollider2DNotify
{
	friend class ColliderManager;
	friend class GameObjectBase;
public:
	Rigidbody2D(GameObjectBase& gameObject);
	virtual ~Rigidbody2D() override;

	bool isKinematic = false;
	bool useGravity = true;

	/** 중력 값.*/
	Vector2 Gravity;

	/** 물체가 이동하는 속도.*/
	Vector2 Velocity;

	/** 물체에 힘을 적용시킵니다.*/
	void AddForce(const Vector2& force);
protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	Vector2 force{ 0, 0 }; //힘
	Vector2 acceleration{0, 0}; //현재 가속도
	float mass = 1.0f;	//질량	

	bool currIsGravity; //이번 프레임 중력 적용 여부

	//float angularVelocity; //회전 속도 (아직 사용 안함)

	void AddGravity();

	float disRL = 0;
	float disLR = 0;
	float disTB = 0;
	float disBT = 0;

	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnCollisionStay2D (ColliderBase* myCollider, ColliderBase* otherCollider) override;
	virtual void OnCollisionExit2D (ColliderBase* myCollider, ColliderBase* otherCollider) override;
								
	virtual void OnTriggerEnter2D  (ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerStay2D   (ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerExit2D   (ColliderBase* myCollider, ColliderBase* otherCollider) override {};
};