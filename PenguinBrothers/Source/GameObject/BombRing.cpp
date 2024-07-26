#include "BombRing.h"
#include <Core/Component/Collider/BoxCollider2D.h>
#include <Core/Component/Renderer/SpriteRenderer.h>

//게임 오브젝트를 상속받는 클래스의 cpp 파일에 다음 해더와 매크로를 추가해야 월드 json 저장이 가능합니다.
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
