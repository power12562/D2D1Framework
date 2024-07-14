#include "RectMode.h"

#include <Core/Component/Renderer/SpriteRenderer.h>

#include "Source/Component/RectModeCtrl.h"

RectMode::RectMode()
{
	AddComponent<SpriteRenderer>();
	AddComponent<RectModeCtrl>();
}

RectMode::~RectMode()
{

}
