#include "Block.h"
#include <Core/Component/Renderer/SpriteRenderer.h>
#include <Core/Component/Collider/BoxCollider2D.h>


#include "Source/Component/BlockCtrl.h"

//게임 오브젝트를 상속받는 클래스의 cpp 파일에 다음 해더와 매크로를 추가해야 월드 json 저장이 가능합니다.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Block)

Block::Block()
{
	tag = L"Block";
	AddComponent<SpriteRenderer>().LoadImage(L"Resource/block.png");
	AddComponent<BoxCollider2D>().ColliderSize = Vector2{ 178, 34 };
	AddComponent<BlockCtrl>();

#ifdef _DEBUG
	GetComponent<BoxCollider2D>().isDrawCollider = true;
#endif // _DEBUG
}

Block::~Block()
{

}
