#include "GameObjectCamera.h"

#include "Framework/WinGameApp.h"

#include "Core/Component/Camera.h"

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
//#include <Framework/GameObjectFactory.h>
//REGISTER_GAMEOBJECFT(GameObjectCamera)

GameObjectCamera::GameObjectCamera()
{
	objType = OBJECT_TYPE::CAMERA;
	AddComponent<Camera>();
}

void GameObjectCamera::UpdateCullingBounds()
{
	const SIZE& clientSize = WinGameApp::GetClientSize();
	cullingBounds.size.x = (float)clientSize.cx * transform.scale.x;
	cullingBounds.size.y = (float)clientSize.cy * transform.scale.y;

	cullingBounds.extents = cullingBounds.size * 0.5f;

	cullingBounds.center = transform.position;

	cullingBounds.leftTop.x = floor(cullingBounds.center.x - cullingBounds.extents.x);
	cullingBounds.leftTop.y = ceil(cullingBounds.center.y + cullingBounds.extents.y);

	cullingBounds.rightBottom.x = ceil(cullingBounds.center.x + cullingBounds.extents.x);
	cullingBounds.rightBottom.y = floor(cullingBounds.center.y - cullingBounds.extents.y);

	Bounds::GetRotationBounds(cullingBounds, transform.rotation);
}
