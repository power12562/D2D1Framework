#pragma once	 
class ComponentBase;

/** 콜라이더 이벤트를 사용할 컴포넌트용 인터페이스. 생성자에 this를 넘겨서 컴포넌트 유무를 체크 합니다.*/
class ICollider2DNotify
{
	friend class WorldManager;
	friend class ColliderManager;
public:
	/*this를 넘겨 타입을 체크하세요. */
	template <typename T>
	ICollider2DNotify(T* _this)
	{
		static_assert(std::is_base_of<ComponentBase, T>::value,
			"ICollider2DNotify 클래스는 ComponentBase를 상속받는 클래스에서만 상속 가능 합니다.");
	}
	virtual ~ICollider2DNotify() = default;
protected:
	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) = 0;
	virtual void OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) = 0;
	virtual void OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) = 0;

	virtual void OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) = 0;
	virtual void OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) = 0;
	virtual void OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) = 0;
};									   


/*
	virtual void OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};

	virtual void OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
	virtual void OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider) override {};
*/

#include <Core/Component/Collider/Base/ColliderBase.h>