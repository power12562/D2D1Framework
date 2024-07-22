#include "StageObjectListDebug.h"
#include <Framework/WorldManager.h>

#include "Source/Component/StageObjectListDebug_Ctrl.h"

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(StageObjectListDebug)

StageObjectListDebug::StageObjectListDebug()
{
	AddComponent<StageObjectListDebug_Ctrl>();
}

StageObjectListDebug::~StageObjectListDebug()
{
}
