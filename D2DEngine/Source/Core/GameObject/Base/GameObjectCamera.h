#pragma once
#include "GameObjectBase.h"

/* Derived default

class Derived : public GameObjectCamera
{
 public:
	Derived();
	virtual ~Derived() override;
};

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Derived)

*/
class GameObjectCamera : public GameObjectBase
{
public:
	GameObjectCamera();
	//virtual ~MainCamera() override;

	virtual void UpdateCullingBounds() override;
};