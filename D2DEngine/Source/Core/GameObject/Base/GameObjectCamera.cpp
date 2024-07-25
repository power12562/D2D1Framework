#include "GameObjectCamera.h"

#include "Framework/WinGameApp.h"

#include "Core/Component/Camera.h"

//게임 오브젝트를 상속받는 클래스의 cpp 파일에 다음 해더와 매크로를 추가해야 월드 json 저장이 가능합니다.
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
