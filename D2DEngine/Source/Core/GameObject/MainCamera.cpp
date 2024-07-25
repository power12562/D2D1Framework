#include "MainCamera.h"
#include "Core/Component/Camera.h"
#include <Framework/WorldManager.h>

MainCamera::MainCamera()
{	
	GetComponent<Camera>().SetMain();
}

