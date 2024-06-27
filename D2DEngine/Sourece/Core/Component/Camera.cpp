#include "Core/Component/Camera.h"
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Framework/WinGameApp.h"

Camera* Camera::mainCam = nullptr;

Camera::Camera(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	SIZE clientSize = WinGameApp::GetClientSize();

	gameObject.transform.pivot = Vector2(clientSize.cx * 0.5f, clientSize.cy * 0.5f); //ȭ�� ũ�⿡ �߽��� ī�޶� �Ǻ�
}

Camera::~Camera()
{
}

void Camera::SetMain()
{
	mainCam = this;
}

void Camera::Start()
{

}

void Camera::Update()
{

}

void Camera::Render()
{

}
