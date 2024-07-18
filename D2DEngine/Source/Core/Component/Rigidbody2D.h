#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Vector/Vector2.h>

#include <list>

class Rigidbody2D : public ComponentBase
{
	friend class ColliderManager;
	friend class GameObjectBase;
public:
	Rigidbody2D(GameObjectBase& gameObject);
	virtual ~Rigidbody2D() override;

	bool isKinematic = false;
	bool useGravity = false;

	/** 중력 값. 기본 : { 0.f, -9.81f }*/
	Vector2 Gravity{ 0.f, -9.81f };

	/** 물체가 이동하는 속도.*/
	Vector2 Velocity;

	/** 물체에 힘을 적용시킵니다.*/
	void AddForce(const Vector2& force);
protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	Vector2 force{ 0, 0 }; //힘
	Vector2 acceleration{0, 0}; //현재 가속도
	float mass = 1.0f;	//질량	

	float angularVelocity; //회전 속도 (아직 사용 안함)

	std::list<Rigidbody2D*>::iterator myIter;
	static std::list<Rigidbody2D*> rigidbodyList;
};