#include "GameObjectCamera.h"

#include "Framework/WinGameApp.h"

#include "Core/Component/Camera.h"

GameObjectCamera::GameObjectCamera()
{
	objType = OBJECT_TYPE::CAMERA;
	AddComponent<Camera>();
}

void GameObjectCamera::UpdateBounds()
{
	const SIZE& clientSize = WinGameApp::GetClientSize();
	bounds.size.x = (float)clientSize.cx * transform.scale.x;
	bounds.size.y = (float)clientSize.cy * transform.scale.y;

	bounds.extents = bounds.size * 0.5f;

	bounds.center = transform.position;

	bounds.leftTop.x = bounds.center.x - bounds.extents.x;
	bounds.leftTop.y = bounds.center.y + bounds.extents.y;

	bounds.rightBottom.x = bounds.center.x + bounds.extents.x;
	bounds.rightBottom.y = bounds.center.y - bounds.extents.y;

	Bounds::GetRotationBounds(bounds, transform.rotation);
}
