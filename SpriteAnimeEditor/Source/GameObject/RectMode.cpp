#include "RectMode.h"

#include <Core/Component/Renderer/SpriteRenderer.h>

#include "Source/Component/RectModeCtrl.h"

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(RectMode)

RectMode::RectMode()
{
	AddComponent<SpriteRenderer>();
	AddComponent<RectModeCtrl>();
}

RectMode::~RectMode()
{

}
