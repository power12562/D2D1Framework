#include "World1.h"
#include <Framework/WorldManager.h>
#include <Core/Component/Collider/BoxCollider2D.h>

//���ϴ� ������Ʈ���� �߰��մϴ�.
World1::World1()
{
	auto test1 = WorldManager::AddGameObject(L"BoxTest1");
	auto& box = test1->AddComponent<BoxCollider2D>();
	box.isDrawCollider = true;
	box.ColliderSize = Vector2{ 1000.f, 1000.f };
}

World1::~World1()
{

}
