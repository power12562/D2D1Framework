#pragma once
#include <list>

class ColliderBase;

class ColliderManager
{
	friend class ColliderBase;
	friend class WinGameApp;
	friend class GameObjectBase;

	static std::list<ColliderBase*> colliderInstanceList;	//��� �ݶ��̴� ����Ʈ

	static void DeleteCollider(ColliderBase* collider); //�ݶ��̴� ������Ʈ ������ �̺�Ʈ ��û��

	/** �ݶ��̴����� �浹 ���θ� �˻��մϴ�. WinGameApp ������ ȣ���մϴ�. */
	static void CheckCollision();

	static void CallEnterEvent(ColliderBase* i, ColliderBase* j);
	static void CallStayEvent(ColliderBase* i, ColliderBase* j);
	static void CallExitEvent(ColliderBase* i, ColliderBase* j);
};