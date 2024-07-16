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
	virtual bool isCollide(ColliderBase* other) = 0; //각자 콜라이더에서 구현
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
		ColliderManager::colliderInstanceList.push_back(this);			//객체화시 추가
		myIter = std::prev(ColliderManager::colliderInstanceList.end()); //자신의 노드 저장
	}
	virtual ~ColliderBase() override
	{
		ColliderManager::colliderInstanceList.erase(myIter);	//객체 리스트에서 삭제
	}
	bool isTrigger = false; //오버랩 여부 (true = 오버랩)
	inline Type GetType() const { return type; }
protected:
	Type type = Type::None;
	std::unordered_set<ColliderBase*> collideStateCurr;	//다른 콜라이더와 현재 충돌 상태

	virtual bool isCollide(ColliderBase* other) = 0; //각자 콜라이더에서 구현
	
private:
	std::list<ColliderBase*>::iterator myIter;		//콜라이더 리스트에 대한 자신의 노드(이터)
};
