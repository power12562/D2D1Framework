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
		ColliderManager::instanceList.push_back(this);			//객체화시 추가
		myIter = std::prev(ColliderManager::instanceList.end()); //자신의 노드 저장
	}
	virtual ~ColliderBase() override
	{
		ColliderManager::instanceList.erase(myIter);	//객체 리스트에서 삭제
	}
	bool isTrigger = false; //오버랩 여부 (true = 오버랩)

protected:
	enum class Type
	{
		None,
		box,
	}; 
	Type type = Type::None;
	std::set<ColliderBase*> collideStateCurr;	//다른 콜라이더와 현재 충돌 상태
	std::set<ColliderBase*> collideStatePrev;	//다른 콜라이더와 이전 충돌 상태

	virtual bool isCollide(ColliderBase* other) = 0; //각자 콜라이더에서 구현
	
private:
	std::list<ColliderBase*>::iterator myIter;		//콜라이더 리스트에 대한 자신의 노드(이터)
};
