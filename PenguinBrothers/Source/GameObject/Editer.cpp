#include "Editer.h"
#include "Source/Component/EditerCtrl.h"


#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Editer)

Editer::Editer()
{
	AddComponent<EditerCtrl>();
}

Editer::~Editer()
{
}
