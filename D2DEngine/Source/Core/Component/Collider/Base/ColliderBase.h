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
		ColliderManager::DeleteCollider(this); //콜라이더 삭제시 Exit Event 호출요청
		ColliderManager::colliderInstanceList.erase(myIter);	//객체 리스트에서 삭제		
	}
	bool isTrigger = false; //오버랩 여부 (true = 오버랩)
	inline Type GetType() const { return type; }

	Vector2 Center{ 0, 0 };

	virtual float GetTop() = 0;
	virtual float GetBottom() = 0;
	virtual float GetLeft() = 0;
	virtual float GetRight() = 0;
protected:
	Type type = Type::None;
	std::unordered_set<ColliderBase*> collideStateCurr;	//다른 콜라이더와 현재 충돌 상태

	virtual bool isCollide(ColliderBase* other) = 0; //각자 콜라이더에서 구현
	virtual bool isCollide(const Vector2& point) = 0; //점과 충돌 구현

private:
	std::list<ColliderBase*>::iterator myIter;		//콜라이더 리스트에 대한 자신의 노드(이터)
};
