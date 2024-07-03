#include "MainCamera.h"
#include "Core/Component/Camera.h"

MainCamera::MainCamera()
{	
	GetComponent<Camera>().SetMain();
}

