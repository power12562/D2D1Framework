#include "DebugUI.h"

#include "Source/Component/DebugUICtrl.h"

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(DebugUI)

DebugUI::DebugUI()
{
	DebugUICtrl& debugUICtrl = AddComponent<DebugUICtrl>();

}
