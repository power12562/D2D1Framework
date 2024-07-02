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
	bounds.size.x = (float)clientSize.cx * transform.scale.x;
	bounds.size.y = (float)clientSize.cy * transform.scale.y;

	bounds.extents = bounds.size * 0.5f;

	bounds.leftTop = transform.position;

	bounds.rightBottom.x = bounds.leftTop.x + bounds.size.x;
	bounds.rightBottom.y = bounds.leftTop.y - bounds.size.y;

	bounds.center.x = transform.position.x + bounds.extents.x;
	bounds.center.y = transform.position.y - bounds.extents.y;

	Bounds::GetRotationBounds(bounds, transform.rotation);
}


