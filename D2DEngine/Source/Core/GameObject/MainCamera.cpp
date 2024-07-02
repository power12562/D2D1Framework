#include "MainCamera.h"
#include "Core/Component/Camera.h"

#include "Framework/WinGameApp.h"

MainCamera::MainCamera()
{
	AddComponent<Camera>();
	GetComponent<Camera>().SetMain();
}

void MainCamera::UpdateBounds()
{
	const SIZE& clientSize = WinGameApp::GetClientSize();
	bounds.center = transform.position; //카메라의 중심은 자신의 위치

	bounds.size.x = clientSize.cx;
	bounds.size.y = clientSize.cy;

	bounds.extents = bounds.size * 0.5f;

	bounds.leftTop = bounds.center - bounds.extents;
	bounds.rightBottom = bounds.center + bounds.extents;

	Bounds::GetRotationBounds(bounds, transform.rotation);
}


