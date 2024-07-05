#include "Core/Component/Camera.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Framework/WinGameApp.h"


Camera* Camera::mainCam = nullptr;
std::list<Camera*> Camera::instanceList;

Camera::Camera(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	instanceList.push_back(this);
	instanceIter = std::prev(instanceList.end());
	
	SIZE clientSize = WinGameApp::GetClientSize();
	gameObject.transform.pivot = Vector2(clientSize.cx * 0.5f, clientSize.cy * 0.5f);
}

Camera::~Camera()
{
	instanceList.erase(instanceIter);
}

void Camera::SetMain()
{
	mainCam = this;
}

const D2D1_MATRIX_3X2_F& Camera::GetMatrix()
{
	return gameObject.transform.WM;
}

const D2D1_MATRIX_3X2_F& Camera::GetInvertMatrix()
{
	return gameObject.transform.IWM;
}

void Camera::ResetCameraPivot()
{
	SIZE clientSize = WinGameApp::GetClientSize();
	for (auto& instance : instanceList)
	{
		instance->gameObject.transform.pivot = Vector2(clientSize.cx * 0.5f, clientSize.cy * 0.5f); //화면 크기에 중심이 카메라 피봇
	}
}


