#include "Block.h"

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Block)

#include <Core/Component/Renderer/SpriteRenderer.h>
#include <Core/Component/Collider/BoxCollider2D.h>


Block::Block()
{
	tag = L"Ground";
	AddComponent<SpriteRenderer>().LoadImage(L"Resource/block.png");
	AddComponent<BoxCollider2D>().ColliderSize = Vector2{ 178, 34 };

}

Block::~Block()
{

}
