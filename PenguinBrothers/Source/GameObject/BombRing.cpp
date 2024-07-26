#include "BombRing.h"
#include <Core/Component/Collider/BoxCollider2D.h>
#include <Core/Component/Renderer/SpriteRenderer.h>

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(BombRing)

#include "Source/Component/BombRingCtrl.h"


BombRing::BombRing()
{
	tag = L"Item";

	BoxCollider2D& coll = AddComponent<BoxCollider2D>();
	coll.ColliderSize = Vector2{ 66,66 };
	coll.isTrigger = true;
#ifdef _DEBUG
	coll.isDrawCollider = true;
#endif // _DEBUG	
	AddComponent<SpriteRenderer>();
	AddComponent<BombRingCtrl>();
}

BombRing::~BombRing()
{
}
