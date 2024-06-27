#include "MainCamera.h"
#include "Core/Component/Camera.h"

MainCamera::MainCamera()
{
	AddComponent<Camera>();
	GetComponent<Camera>().SetMain();
}
