#pragma once
#include <list>

class ColliderBase;

class ColliderManager
{
	friend class ColliderBase;
	friend class WinGameApp;
	friend class GameObjectBase;

	static std::list<ColliderBase*> colliderInstanceList;	//모든 콜라이더 리스트

	static void DeleteCollider(ColliderBase* collider); //콜라이더 컴포넌트 삭제시 이벤트 요청용

	/** 콜라이더들의 충돌 여부를 검사합니다. WinGameApp 에서만 호출합니다. */
	static void CheckCollision();

	static void CallEnterEvent(ColliderBase* i, ColliderBase* j);
	static void CallStayEvent(ColliderBase* i, ColliderBase* j);
	static void CallExitEvent(ColliderBase* i, ColliderBase* j);
};