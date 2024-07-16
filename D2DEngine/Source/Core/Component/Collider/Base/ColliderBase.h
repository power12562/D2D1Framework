#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Framework/ColliderManager.h>

#include <list>
#include <set>

/* Derived default

class Derived : public ColliderBase
{
public:
	Derived(GameObjectBase& gameObject) : ColliderBase(gameObject) {}
	virtual ~Derived() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

*/

class ColliderBase : public ComponentBase
{
	friend class ColliderManager;
public:
	ColliderBase(GameObjectBase& gameObject) : ComponentBase(gameObject) 
	{
		ColliderManager::instanceList.push_back(this);			//��üȭ�� �߰�
		myIter = std::prev(ColliderManager::instanceList.end()); //�ڽ��� ��� ����
	}
	virtual ~ColliderBase() override
	{
		ColliderManager::instanceList.erase(myIter);	//��ü ����Ʈ���� ����
	}
	bool isTrigger = false; //������ ���� (true = ������)

protected:
	enum class Type
	{
		None,
		box,
	}; 
	Type type = Type::None;
	std::set<ColliderBase*> collideStateCurr;	//�ٸ� �ݶ��̴��� ���� �浹 ����
	std::set<ColliderBase*> collideStatePrev;	//�ٸ� �ݶ��̴��� ���� �浹 ����

	virtual bool isCollide(ColliderBase* other) = 0; //���� �ݶ��̴����� ����
	
private:
	std::list<ColliderBase*>::iterator myIter;		//�ݶ��̴� ����Ʈ�� ���� �ڽ��� ���(����)
};
