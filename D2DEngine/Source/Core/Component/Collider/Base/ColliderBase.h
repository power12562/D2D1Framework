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

protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;
	virtual bool isCollide(ColliderBase* other) override; //���� �ݶ��̴����� ����
    virtual bool isCollide(const Vector2& point) override;
};

*/

class ColliderBase : public ComponentBase
{
	friend class ColliderManager;
	friend class GameObjectBase;
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
		ColliderManager::colliderInstanceList.erase(myIter);	//��ü ����Ʈ���� ����
		ColliderManager::DeleteCollider(this); //�ݶ��̴� ������ Exit Event ȣ���û
	}
	bool isTrigger = false; //������ ���� (true = ������)
	inline Type GetType() const { return type; }
protected:
	Type type = Type::None;
	std::unordered_set<ColliderBase*> collideStateCurr;	//�ٸ� �ݶ��̴��� ���� �浹 ����

	virtual bool isCollide(ColliderBase* other) = 0; //���� �ݶ��̴����� ����
	virtual bool isCollide(const Vector2& point) = 0; //���� �浹 ����
	
private:
	std::list<ColliderBase*>::iterator myIter;		//�ݶ��̴� ����Ʈ�� ���� �ڽ��� ���(����)
};
