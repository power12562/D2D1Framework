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

	/** �߷� ��. �⺻ : { 0.f, -9.81f }*/
	Vector2 Gravity{ 0.f, -9.81f };

	/** ��ü�� �̵��ϴ� �ӵ�.*/
	Vector2 Velocity;

	/** ��ü�� ���� �����ŵ�ϴ�.*/
	void AddForce(const Vector2& force);
protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	Vector2 force{ 0, 0 }; //��
	Vector2 acceleration{0, 0}; //���� ���ӵ�
	float mass = 1.0f;	//����	

	float angularVelocity; //ȸ�� �ӵ� (���� ��� ����)

	std::list<Rigidbody2D*>::iterator myIter;
	static std::list<Rigidbody2D*> rigidbodyList;
};