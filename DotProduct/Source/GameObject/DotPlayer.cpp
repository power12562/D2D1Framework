#include "DotPlayer.h"
#include <Core/Component/Renderer/SpriteRenderer.h>
#include <Core/Component/Movement.h>

#include "Source/Component/DotPlayerMouseMoveCtrl.h"
#include "Source/Component/CollisionTestComponent.h"

DotPlayer::DotPlayer()
{
	SpriteRenderer& spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer.LoadImage(L"Assets/Image/tank.png");
	AddComponent<Movement>();
	AddComponent<DotPlayerMouseMoveCtrl>();
	//AddComponent<CollisionTestComponent>();
}

DotPlayer::~DotPlayer()
{

}
