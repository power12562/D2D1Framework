#include "GameObjectUI.h"

#include "Core/Component/Camera.h"

GameObjectUI::GameObjectUI()
{
	objType = OBJECT_TYPE::UI;
	transform.SetParent(Camera::GetMainCamera()->gameObject.transform);
}
