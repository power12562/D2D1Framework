#pragma once

#include "Core/GameObject/Base/GameObjectBase.h"

/* Derived default

class Derived : public GameObjectUI
{
 public:
	Derived();
	virtual ~Derived() override;
};

//���� ������Ʈ�� ��ӹ޴� Ŭ������ cpp ���Ͽ� ���� �ش��� ��ũ�θ� �߰��ؾ� ���� json ������ �����մϴ�.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Derived)

*/
class GameObjectUI : public GameObjectBase
{
public:
	GameObjectUI();
	//virtual ~GameObjectUI() override;
};