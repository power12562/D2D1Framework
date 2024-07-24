#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Framework/ColliderManager.h>
#include <Utility/Ray.h>

#include <list>
#include <unordered_set>

/* Derived default

class Derived : public ColliderBase
{
public:
	Derived(GameObjectBase& gameObject) : ColliderBase(gameObject) {}
	virtual ~Derived() override;

	virtual float GetTop() override;
	virtual float GetBottom() override;
	virtual float GetLeft() override;
	virtual float GetRight() override;
protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	virtual bool isCollide(ColliderBase* other) override; 
    virtual bool isCollide(const Vector2& point) override;
};

*/

class ColliderBase : public ComponentBase
{
	friend class ColliderManager;
	friend class GameObjectBase;
	friend class Rigidbody2D;
	friend ColliderBase* Ray::ShootRayFromPosition(const Vector2& position);
protected:	
	enum class Type
	{
		None,
		box,
	};
public:
	ColliderBase(GameObjectBase& gameObject) : ComponentBase(gameObject)
	{
		ColliderManager::colliderInstanceList.push_back(this);
		this->myIter = std::prev(ColliderManager::colliderInstanceList.end());
	}
	virtual ~ColliderBase() override
	{
		ColliderManager::DeleteCollider(this); //�ݶ��̴� ������ Exit Event ȣ���û
		ColliderManager::colliderInstanceList.erase(myIter);	//��ü ����Ʈ���� ����		
	}
	bool isTrigger = false; //������ ���� (true = ������)
	inline Type GetType() const { return type; }

	Vector2 Center{ 0, 0 };

	virtual float GetTop() = 0;
	virtual float GetBottom() = 0;
	virtual float GetLeft() = 0;
	virtual float GetRight() = 0;
protected:
	Type type = Type::None;
	std::unordered_set<ColliderBase*> collideStateCurr;	//�ٸ� �ݶ��̴��� ���� �浹 ����

	virtual bool isCollide(ColliderBase* other) = 0; //���� �ݶ��̴����� ����
	virtual bool isCollide(const Vector2& point) = 0; //���� �浹 ����

private:
	std::list<ColliderBase*>::iterator myIter;		//�ݶ��̴� ����Ʈ�� ���� �ڽ��� ���(����)
};
