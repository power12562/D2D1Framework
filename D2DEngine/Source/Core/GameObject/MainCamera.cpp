#include "MainCamera.h"
#include "Core/Component/Camera.h"

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(MainCamera)

MainCamera::MainCamera()
{	
	GetComponent<Camera>().SetMain();
}

