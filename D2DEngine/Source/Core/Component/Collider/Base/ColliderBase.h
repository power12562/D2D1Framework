#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Framework/ColliderManager.h>

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
	virtual bool isCollide(ColliderBase* other) = 0; //���� �ݶ��̴����� ����
};

*/

class ColliderBase : public ComponentBase
{
	friend class ColliderManager;
protected:	
	enum class Type
	{
		None,
		box,
	};
public:
	ColliderBase(GameObjectBase& gameObject) : ComponentBase(gameObject) 
	{
		ColliderManager::colliderInstanceList.push_back(this);			//��üȭ�� �߰�
		myIter = std::prev(ColliderManager::colliderInstanceList.end()); //�ڽ��� ��� ����
	}
	virtual ~ColliderBase() override
	{
		ColliderManager::colliderInstanceList.erase(myIter);	//��ü ����Ʈ���� ����
	}
	bool isTrigger = false; //������ ���� (true = ������)
	inline Type GetType() const { return type; }
protected:
	Type type = Type::None;
	std::unordered_set<ColliderBase*> collideStateCurr;	//�ٸ� �ݶ��̴��� ���� �浹 ����

	virtual bool isCollide(ColliderBase* other) = 0; //���� �ݶ��̴����� ����
	
private:
	std::list<ColliderBase*>::iterator myIter;		//�ݶ��̴� ����Ʈ�� ���� �ڽ��� ���(����)
};
