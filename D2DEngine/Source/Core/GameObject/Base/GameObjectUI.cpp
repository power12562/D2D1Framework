#include "GameObjectUI.h"

#include "Core/Component/Camera.h"

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(GameObjectUI)

GameObjectUI::GameObjectUI()
{
	objType = OBJECT_TYPE::UI;
	transform.SetParent(Camera::GetMainCamera()->gameObject.transform);
}
