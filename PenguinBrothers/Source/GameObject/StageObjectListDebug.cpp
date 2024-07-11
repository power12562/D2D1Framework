#include "StageObjectListDebug.h"
#include <Framework/WorldManager.h>

#include "Source/Component/StageObjectListDebug_Ctrl.h"

StageObjectListDebug::StageObjectListDebug()
{
	AddComponent<StageObjectListDebug_Ctrl>();
}

StageObjectListDebug::~StageObjectListDebug()
{
}
