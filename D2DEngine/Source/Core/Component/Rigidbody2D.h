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

	/** �߷� ��.*/
	Vector2 Gravity;

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

	bool currIsGravity; //�̹� ������ �߷� ���� ����

	//float angularVelocity; //ȸ�� �ӵ� (���� ��� ����)

	void AddGravity();

	virtual void OnCollisionEnter2D(GameObjectBase* collision) override;
	virtual void OnCollisionStay2D(GameObjectBase* collision) override;
	virtual void OnCollisionExit2D(GameObjectBase* collision) override;

	virtual void OnTriggerEnter2D(GameObjectBase* collision) override {};
	virtual void OnTriggerStay2D(GameObjectBase* collision) override {};
	virtual void OnTriggerExit2D(GameObjectBase* collision) override {};
};